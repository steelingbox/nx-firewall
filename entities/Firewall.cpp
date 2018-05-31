//
// Created by alexis on 5/15/18.
//

#include <QMap>
#include <QVariant>
#include <QMetaEnum>
#include <QDebug>

#include "Firewall.h"
#include "../entities/QVariantRuleSetConverter.h"

Firewall::Firewall(QObject* parent)
        :QObject(parent), netfilterTool(nullptr) { }

RuleSet Firewall::getPermissiveSetup() const
{
    RuleSet ruleSet;
    ruleSet.setDefaultIncomingPolicy(Rule::ALLOW);
    ruleSet.setDefaultOutgoingPolicy(Rule::ALLOW);
    ruleSet.setRules(customRules);

    return ruleSet;
}
RuleSet Firewall::getStealthSetup() const
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
Rule* Firewall::getAllowIncomingOnLoRule() const
{
    auto allowIncomingOnLo = new Rule();
    allowIncomingOnLo->setInterface("lo");
    allowIncomingOnLo->setDirection(Rule::INCOMING);
    allowIncomingOnLo->setAction(Rule::ALLOW);
    return allowIncomingOnLo;
}
RuleSet Firewall::getParanoidSetup() const
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
Rule* Firewall::getAllowDNSRule() const
{
    auto allowDomain = new Rule();
    allowDomain->setDirection(Rule::OUTGOING);
    allowDomain->setProtocol("udp");
    allowDomain->setDestinationPorts({53});
    allowDomain->setAction(Rule::ALLOW);
    return allowDomain;
}
Rule* Firewall::getAllowHttpRule() const
{
    auto allowHttp = new Rule();
    allowHttp->setDirection(Rule::OUTGOING);
    allowHttp->setAction(Rule::ALLOW);
    allowHttp->setProtocol("tcp");
    allowHttp->setDestinationPorts({80, 443});
    return allowHttp;
}
Firewall::Profile Firewall::getCurrentProfile() const
{
    return currentProfile;
}
void Firewall::setCurrentProfile(Firewall::Profile currentProfile)
{
    Firewall::currentProfile = currentProfile;
    emit profileChanged(currentProfile);
}
void Firewall::setNetfilterTool(NetFilterTool* netfilterTool)
{
    Firewall::netfilterTool = netfilterTool;
}
const QList<Rule*>& Firewall::getCustomRules() const
{
    return customRules;
}
void Firewall::setCustomRules(const QList<Rule*>& customRules)
{
    Firewall::customRules = customRules;
    emit customRulesChanged(customRules);
}

void Firewall::loadCustomRules(const QVariantMap& map)
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
void Firewall::loadProfile(const QVariantMap& map)
{
    Profile profile;

    auto profileStr = map.value("profile").toString().toStdString().c_str();
    auto profileEnum = QMetaEnum::fromType<Profile>();

    bool succeeded = true;
    profile = static_cast<Profile>(profileEnum.keyToValue(profileStr, &succeeded));

    if (succeeded) {
        Firewall::currentProfile = profile;
        emit profileChanged(profile);
    }
    else {
        qWarning() << "Unable to parse settings profile, setting PERMISSIVE mode as fallback";
        setCurrentProfile(PERMISSIVE);
    }
}

void Firewall::setSettingsManager(SettingsManager* settingsManager)
{
    Firewall::settingsManager = settingsManager;
}
QVariantMap Firewall::getSettings() const
{
    QVariantMap settings;

    auto profileEnum = QMetaEnum::fromType<Profile>();
    settings["profile"] = profileEnum.key(currentProfile);

    QVariantList variantRules;
    for (auto rule: customRules)
                variantRules << QVariantRuleSetConverter::toVariant(rule);

    settings["rules"] = variantRules;
    return settings;
}

void Firewall::setSettings(const QVariantMap& settings)
{
    try {
        loadCustomRules(settings);
        loadProfile(settings);
    }
    catch (QVariantRuleSetConverter::ConversionException exception) {
        qWarning() << "Malformed settings file";
    }
}
RuleSet Firewall::getRuleSet() const
{
    RuleSet ruleSet;
    if (currentProfile==PERMISSIVE)
        ruleSet = getPermissiveSetup();

    if (currentProfile==STEALTH)
        ruleSet = getStealthSetup();

    if (currentProfile==PARANOID)
        ruleSet = getParanoidSetup();

    return ruleSet;
}
