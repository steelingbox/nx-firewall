//
// Created by alexis on 5/10/18.
//

#ifndef NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H
#define NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H

#include <QVariantMap>
#include <ostream>
#include "../entities/RuleSet.h"

class QVariantRuleSetConverter {
public:
    static constexpr const char* const KEY_DIRECTION = "DIRECTION";
    static constexpr const char* const KEY_PROTOCOL = "PROTOCOL";
    static constexpr const char* const KEY_ACTION = "ACTION";
    static constexpr const char* const KEY_SOURCE_ADDR = "SOURCE_ADDR";
    static constexpr const char* const KEY_SOURCE_PORTS = "SOURCE_PORTS";
    static constexpr const char* const KEY_DESTINATION_ADDR = "DESTINATION_ADDR";
    static constexpr const char* const KEY_DESTINATION_PORTS = "DESTINATION_PORTS";

    struct ConversionException : public std::exception { };

    static QVariantMap toVariant(const RuleSet& ruleSet);
    static QVariantMap toVariant(const Rule& rule);
    static RuleSet toRuleSet(const QVariantMap& variantMap);

    static Rule toRule(QVariantMap map);
protected:
    static QVariantList getPortsToVariant(const QList<int>& portsList);
    static Rule::Direction getRuleDirection(const QVariantMap& map);
    static Rule::Action getRuleAction(const QVariantMap& map);
    static QList<int> getPortsList(const QList<QVariant>& variantList);
};

#endif //NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H
