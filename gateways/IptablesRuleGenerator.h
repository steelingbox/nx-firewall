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
    static QString generateRule(const Rule* rule);
    static QStringList generateTwoWayCommunicationRules(const Rule* rule);
    static QString generateDefaultPolicy(const QString& chain, const Rule::Action& action);

protected:
    static QString generateDirectionSection(const Rule::Direction& direction);
    static QString generateRuleInterfaceSection(const QString& iface);
    static QString generateSourcePortsSection(const QList<int>& list);
    static QString generatePortListSection(const QList<int>& list) ;
    static QString generateDestinationPortsSection(const QList<int>& list);
    static QString generateRuleActionSection(const Rule::Action& action);
    static QString generateRuleProtocolSection(const QString& p);
    static QString generateSourceAddressSection(const QString& address);
    static QString generateDestinationAddressSection(const QString& address);
    static bool isAMatchAllAddress(const QString& address) ;
    static Rule::Direction getOppositeDirection(const Rule::Direction& direction) ;

    static QString generateRuleForNewConnections(const Rule* rule);
    static QString generateReverseRuleForEstablishedConnections(const Rule* rule);
    static QString translateAction(const Rule::Action& action);
};

#endif //NOMAD_FIREWALL_IPTABLESRULESGENERATOR_H
