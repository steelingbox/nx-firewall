//
// Created by alexis on 5/15/18.
//

#ifndef NOMAD_FIREWALL_THREESTEPSFIREWALL_H
#define NOMAD_FIREWALL_THREESTEPSFIREWALL_H
#include <QObject>

#include "RuleSet.h"
#include "NetFilterTool.h"
#include "SettingsManager.h"

class ThreeStepsFirewall : public QObject {
Q_OBJECT
public:
    enum Profile { PERMISSIVE, STEALTH, PARANOID };
    Q_ENUM(Profile);

    ThreeStepsFirewall(QObject* parent = nullptr);
    Profile getCurrentProfile() const;
    void setCurrentProfile(Profile currentProfile);

    void setNetfilterTool(NetFilterTool* netfilterTool);
    void setSettingsManager(SettingsManager* settingsManager);

    const QList<Rule*>& getCustomRules() const;
    void setCustomRules(const QList<Rule*>& customRules);

public slots:
    void loadSettings();
    void resetProfile();

signals:
    void profileChanged(Profile profile);
    void customRulesChanged(QList<Rule*> customRules);

protected:
    RuleSet getPermissiveSetup();
    RuleSet getStealthSetup();
    RuleSet getParanoidSetup();

private:
    Profile currentProfile;
    QList<Rule*> customRules;
    NetFilterTool* netfilterTool;
    SettingsManager* settingsManager;
    Rule* getAllowIncomingOnLoRule() const;
    void loadProfile(const QVariantMap& map);
    void loadCustomRules(const QVariantMap& map);

    Rule* getAllowHttpRule() const;
    Rule* getAllowDNSRule() const;
};

#endif //NOMAD_FIREWALL_THREESTEPSFIREWALL_H
