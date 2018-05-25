//
// Created by alexis on 5/15/18.
//

#include <QMap>
#include <QVariant>
#include <QMetaEnum>
#include <QDebug>

#include "ThreeStepsFirewall.h"
#include "../entities/QVariantRuleSetConverter.h"

ThreeStepsFirewall::ThreeStepsFirewall(QObject* parent)
        :QObject(parent), netfilterTool(nullptr) { }

RuleSet ThreeStepsFirewall::getPermissiveSetup()
{
    RuleSet ruleSet;
    ruleSet.setDefaultIncomingPolicy(Rule::ALLOW);
    ruleSet.setDefaultOutgoingPolicy(Rule::ALLOW);
    ruleSet.setRules(customRules);

    return ruleSet;
}
RuleSet ThreeStepsFirewall::getStealthSetup()
{
    RuleSet ruleSet;
    ruleSet.setDefaultIncomingPolicy(Rule::DENY);
    ruleSet.setDefaultOutgoingPolicy(Rule::ALLOW);

    QList<Rule*> rules;
    rules << customRules;

    // By explicitly allowing outgoing connection we ensure that the netfilter tool will generate a reverse rule to
    // allow stabilised connection replies
    auto allowOutgoing = new Rule();
    allowOutgoing->setDirection(Rule::OUTGOING);
    allowOutgoing->setAction(Rule::ALLOW);

    auto allowIncomingOnLo = getAllowIncomingOnLoRule();

    rules << allowOutgoing << allowIncomingOnLo;
    ruleSet.setRules(rules);
    return ruleSet;
}
Rule* ThreeStepsFirewall::getAllowIncomingOnLoRule() const
{
    auto allowIncomingOnLo = new Rule();
    allowIncomingOnLo->setInterface("lo");
    allowIncomingOnLo->setDirection(Rule::INCOMING);
    allowIncomingOnLo->setAction(Rule::ALLOW);
    return allowIncomingOnLo;
}
RuleSet ThreeStepsFirewall::getParanoidSetup()
{
    RuleSet ruleSet;
    ruleSet.setDefaultIncomingPolicy(Rule::DENY);
    ruleSet.setDefaultOutgoingPolicy(Rule::DENY);

    QList<Rule*> rules;
    rules << customRules;

    rules << getAllowHttpRule();
    rules << getAllowDNSRule();
    rules << getAllowIncomingOnLoRule();

    ruleSet.setRules(rules);
    return ruleSet;
}
Rule* ThreeStepsFirewall::getAllowDNSRule() const
{
    auto allowDomain = new Rule();
    allowDomain->setDirection(Rule::OUTGOING);
    allowDomain->setProtocol("udp");
    allowDomain->setDestinationPorts({53});
    allowDomain->setAction(Rule::ALLOW);
    return allowDomain;
}
Rule* ThreeStepsFirewall::getAllowHttpRule() const
{
    auto allowHttp = new Rule();
    allowHttp->setDirection(Rule::OUTGOING);
    allowHttp->setAction(Rule::ALLOW);
    allowHttp->setProtocol("tcp");
    allowHttp->setDestinationPorts({80, 443});
    return allowHttp;
}
ThreeStepsFirewall::Profile ThreeStepsFirewall::getCurrentProfile() const
{
    return currentProfile;
}
void ThreeStepsFirewall::setCurrentProfile(ThreeStepsFirewall::Profile currentProfile)
{
    ThreeStepsFirewall::currentProfile = currentProfile;
    resetProfile();
}
void ThreeStepsFirewall::setNetfilterTool(NetFilterTool* netfilterTool)
{
    ThreeStepsFirewall::netfilterTool = netfilterTool;
}
const QList<Rule*>& ThreeStepsFirewall::getCustomRules() const
{
    return customRules;
}
void ThreeStepsFirewall::setCustomRules(const QList<Rule*>& customRules)
{
    ThreeStepsFirewall::customRules = customRules;
    emit customRulesChanged(customRules);
}

void ThreeStepsFirewall::loadCustomRules(const QVariantMap& map)
{
    auto rulesVariantList = map.value("rules").toList();
    QList<Rule*> ruleList;
    for (const QVariant& variant: rulesVariantList) {
        auto ruleVariant = variant.toMap();
        auto newRule = QVariantRuleSetConverter::toRule(ruleVariant);
        ruleList << newRule;
    }

    customRules = ruleList;
}
void ThreeStepsFirewall::loadProfile(const QVariantMap& map)
{
    Profile profile;

    auto profileStr = map.value("profile").toString().toStdString().c_str();
    auto profileEnum = QMetaEnum::fromType<Profile>();

    bool succeeded = true;
    profile = static_cast<Profile>(profileEnum.keyToValue(profileStr, &succeeded));

    if (succeeded) {
        ThreeStepsFirewall::currentProfile = profile;
        emit profileChanged(profile);
    }
    else {
        qWarning() << "Unable to parse settings profile, setting PERMISSIVE mode as fallback";
        setCurrentProfile(PERMISSIVE);
    }
}

void ThreeStepsFirewall::setSettingsManager(SettingsManager* settingsManager)
{
    ThreeStepsFirewall::settingsManager = settingsManager;
}
void ThreeStepsFirewall::loadSettings()
{
    if (settingsManager) {
        try {
            auto map = settingsManager->load();
            loadCustomRules(map);
            loadProfile(map);
        }
        catch (QVariantRuleSetConverter::ConversionException exception) {
            qWarning() << "Malformed settings file";
        }
    }
    else
        qWarning() << "No settings manager set.";
}
void ThreeStepsFirewall::resetProfile()
{
    RuleSet ruleSet;
    if (currentProfile==PERMISSIVE)
        ruleSet = getPermissiveSetup();

    if (currentProfile==STEALTH)
        ruleSet = getStealthSetup();

    if (currentProfile==PARANOID)
        ruleSet = getParanoidSetup();

    if (netfilterTool)
        netfilterTool->apply(ruleSet);

    emit profileChanged(currentProfile);
}
