//
// Created by alexis on 5/8/18.
//

#ifndef NOMAD_FIREWALL_IPTABLESRULESGENERATOR_H
#define NOMAD_FIREWALL_IPTABLESRULESGENERATOR_H

#include <QList>
#include <QString>

#include "../entities/Rule.h"

class IptablesRuleGenerator {

public:
    QString generateRule(const Rule& rule);
    QStringList generateTwoWayCommunicationRules(const Rule& rule);
    QString generateDefaultPolicy(const QString& chain, const Rule::Action& action);

protected:
    QString generateDirectionSection(const Rule::Direction& direction) const;
    QString generateSourcePortsSection(const QList<int>& list);
    QString generatePortListSection(const QList<int>& list) const;
    QString generateDestinationPortsSection(const QList<int>& list);
    QString generateRuleActionSection(const Rule::Action& action);
    QString generateRuleProtocolSection(const QString& p);
    QString generateSourceAddressSection(const QString& address);
    QString generateDestinationAddressSection(const QString& address);
    bool isAMatchAllAddress(const QString& address) const;
    Rule::Direction getOppositeDirection(const Rule::Direction& direction) const;

    QString generateRuleForNewConnections(const Rule& rule);
    QString generateReverseRuleForEstablishedConnections(const Rule& rule);
    QString translateAction(const Rule::Action& action) const;
};

#endif //NOMAD_FIREWALL_IPTABLESRULESGENERATOR_H
