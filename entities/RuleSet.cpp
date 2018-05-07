//
// Created by alexis on 5/7/18.
//

#include "RuleSet.h"
Rule::Action RuleSet::getDefaultIncomingPolicy() const
{
    return defaultIncomingPolicy;
}
void RuleSet::setDefaultIncomingPolicy(Rule::Action defaultIncomingPolicy)
{
    RuleSet::defaultIncomingPolicy = defaultIncomingPolicy;
}
Rule::Action RuleSet::getDefaultOutgoingPolicy() const
{
    return defaultOutgoingPolicy;
}
void RuleSet::setDefaultOutgoingPolicy(Rule::Action defaultOutgoingPolicy)
{
    RuleSet::defaultOutgoingPolicy = defaultOutgoingPolicy;
}
RuleSet::~RuleSet()
{

}
const QList<Rule>& RuleSet::getIncomingRules() const
{
    return incomingRules;
}
const QList<Rule>& RuleSet::getOutgoingRules() const
{
    return outgoingRules;
}
void RuleSet::setIncomingRules(const QList<Rule>& incomingRules)
{
    RuleSet::incomingRules = incomingRules;
}
void RuleSet::setOutgoingRules(const QList<Rule>& outgoingRules)
{
    RuleSet::outgoingRules = outgoingRules;
}
