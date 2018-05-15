//
// Created by alexis on 5/15/18.
//

#ifndef NOMAD_FIREWALL_THREESTEPSFIREWALL_H
#define NOMAD_FIREWALL_THREESTEPSFIREWALL_H
#include <QObject>

#include "RuleSet.h"
#include "NetFilterTool.h"

class ThreeStepsFirewall {
Q_GADGET
public:
    enum Profile { PERMISSIVE, STEALTH, PARANOID };
    Q_ENUM(Profile);

    ThreeStepsFirewall();
    Profile getCurrentProfile() const;
    void setCurrentProfile(Profile currentProfile);

    void setNetfilterTool(NetFilterTool* netfilterTool);
    const QList<Rule>& getCustomRules() const;
    void setCustomRules(const QList<Rule>& customRules);
protected:
    RuleSet getPermissiveSetup();
    RuleSet getStealthSetup();
    RuleSet getParanoidSetup();

private:
    Profile currentProfile;
    QList<Rule> customRules;
    NetFilterTool *netfilterTool;
};

#endif //NOMAD_FIREWALL_THREESTEPSFIREWALL_H
