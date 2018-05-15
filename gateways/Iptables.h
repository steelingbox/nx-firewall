//
// Created by alexis on 5/9/18.
//

#ifndef NOMAD_FIREWALL_IPTABLES_H
#define NOMAD_FIREWALL_IPTABLES_H

#include "../entities/NetFilterTool.h"

class Iptables : public NetFilterTool {
Q_OBJECT
public slots:
    bool isAvailable() override;
    void apply(const RuleSet& ruleSet) override;

protected:
    QStringList generateIptablesInstructions(const RuleSet& ruleSet) const;
    void runIptableInstructions(const QStringList& iptablesInstructions) const;

    QString getBinaryPath() const;
    QStringList generateIptableRules(const RuleSet& ruleSet) const;
    Rule::Action
    getOppositeChainPolicy(const Rule::Action& incomingPolicy, const Rule::Action& outgoingPolicy,
            const Rule& rule) const;
    bool areReverseConnectionsPossible(const Rule::Action& oppositeChainPolicy) const;
};

#endif //NOMAD_FIREWALL_IPTABLES_H
