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
const QList<Rule*>& RuleSet::getRules() const
{
    return rules;
}
void RuleSet::setRules(const QList<Rule*>& incomingRules)
{
    RuleSet::rules = incomingRules;
}
bool RuleSet::operator==(const RuleSet& rhs) const
{
    bool equals = defaultIncomingPolicy==rhs.defaultIncomingPolicy &&
            defaultOutgoingPolicy==rhs.defaultOutgoingPolicy;
    if (equals && rules.length() == rhs.rules.length()) {
        for (int i = 0; i < rules.length() && equals; i++) {
            equals = (*rules.at(i) == *rhs.rules.at(i));
        }
    } else
        return false;
    return equals;

}
bool RuleSet::operator!=(const RuleSet& rhs) const
{
    return !(rhs==*this);
}
