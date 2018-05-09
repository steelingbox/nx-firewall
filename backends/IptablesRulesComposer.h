//
// Created by alexis on 5/8/18.
//

#ifndef NOMAD_FIREWALL_IPTABLESRULESCOMPOSER_H
#define NOMAD_FIREWALL_IPTABLESRULESCOMPOSER_H

#include <QList>
#include <QString>

#include "../entities/Rule.h"

class IptablesRulesComposer {

public:
    QString compose(const Rule& rule);
    QString composeDirection(const Rule& rule) const;
    QString composeSourcePorts(const QList<int>& list);
    QString composePortList(const QList<int>& list) const;
    QString composeDestinationPorts(const QList<int>& list);
    QString composeRuleAction(const Rule::Action& action);
    QString composeRuleProtocol(const QString& p);
};

#endif //NOMAD_FIREWALL_IPTABLESRULESCOMPOSER_H
