//
// Created by alexis on 5/10/18.
//

#ifndef NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H
#define NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H


#include <QVariantMap>
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


    static QVariantMap toVariant(const RuleSet& ruleSet);
    static QVariantMap toVariant(const Rule& rule);
    static RuleSet toRuleSet(const QVariantMap& variantMap);

    static QVariantList getPortsToVariant(const QList<int>& portsList);
};

#endif //NOMAD_FIREWALL_QVARIANTRULESETCONVERTER_H
