//
// Created by alexis on 5/10/18.
//

#include <QMetaEnum>
#include <QVariantList>
#include "QVariantRuleSetConverter.h"

QVariantMap QVariantRuleSetConverter::toVariant(const RuleSet& ruleSet)
{
    QVariantMap res;
    return res;
}
RuleSet QVariantRuleSetConverter::toRuleSet(const QVariantMap& variantMap)
{
    return RuleSet();
}
QVariantMap QVariantRuleSetConverter::toVariant(const Rule& rule)
{
    QVariantMap res;

    auto actionEnum = QMetaEnum::fromType<Rule::Action>();
    auto directionEnum = QMetaEnum::fromType<Rule::Direction>();

    res[KEY_DIRECTION] = directionEnum.valueToKey(rule.getDirection());
    res[KEY_PROTOCOL] = rule.getProtocol();

    if (!rule.getSourceAddr().isEmpty())
        res[KEY_SOURCE_ADDR] = rule.getSourceAddr();

    if (!rule.getSourcePorts().isEmpty())
        res[KEY_SOURCE_PORTS] = getPortsToVariant(rule.getSourcePorts());

    if (!rule.getDestinationAddr().isEmpty())
        res[KEY_DESTINATION_ADDR] = rule.getDestinationAddr();

    if (!rule.getDestinationPorts().isEmpty())
        res[KEY_DESTINATION_PORTS] = getPortsToVariant(rule.getDestinationPorts());

    res[KEY_ACTION] = actionEnum.valueToKey(rule.getAction());

    return res;
}
QVariantList QVariantRuleSetConverter::getPortsToVariant(const QList<int>& portsList)
{
    QVariantList portsVariant;
    for (int port : portsList)
        portsVariant << port;
    return portsVariant;
}
