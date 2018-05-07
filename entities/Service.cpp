//
// Created by alexis on 5/7/18.
//

#include "Service.h"
void Service::start()
{
    emit startRequested();
}
void Service::remove()
{
    emit removeRequested();
}
void Service::deploy()
{
    emit deployRequested();
}
void Service::stop()
{
    emit stopRequested();
}
void Service::updateRules(const RuleSet &ruleSet)
{
    emit updateRulesRequested(ruleSet);
}
