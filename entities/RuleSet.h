//
// Created by alexis on 5/7/18.
//

#ifndef NOMAD_FIREWALL_RULESET_H
#define NOMAD_FIREWALL_RULESET_H

#include <QList>
#include "Rule.h"

class RuleSet {
    Rule::Action defaultIncomingPolicy;
    Rule::Action defaultOutgoingPolicy;

    QList<Rule> rules;
public:
    virtual ~RuleSet();

    Rule::Action getDefaultIncomingPolicy() const;
    void setDefaultIncomingPolicy(Rule::Action defaultIncomingPolicy);

    Rule::Action getDefaultOutgoingPolicy() const;
    void setDefaultOutgoingPolicy(Rule::Action defaultOutgoingPolicy);

    void setRules(const QList<Rule>& incomingRules);
    const QList<Rule>& getRules() const;
};

#endif //NOMAD_FIREWALL_RULESET_H
