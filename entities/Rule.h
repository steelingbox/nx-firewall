//
// Created by alexis on 5/4/18.
//

#ifndef NOMAD_FIREWALL_RULE_H
#define NOMAD_FIREWALL_RULE_H

#include <QObject>
#include <QString>
#include <cstdint>
#include <linux/netfilter.h>

class Rule {
Q_GADGET
public:
    enum Action {
      ALOW,
      DENY,
      REJECT
    };
    Q_ENUM(Action)

    enum Direction {
      INCOMING,
      OUTGOING
    };
    Q_ENUM(Direction)
    Rule();
    Direction getDirection() const;
    void setDirection(Direction direction);
    const QString& getSourceAddr() const;
    void setSourceAddr(const QString& sourceAddr);
    const QList<int>& getSourcePorts() const;
    void setSourcePorts(const QList<int>& sourcePorts);

    const QString& getDestinationAddr() const;
    void setDestinationAddr(const QString& destinationAddr);
    const QList<int>& getDestinationPorts() const;
    void setDestinationPorts(const QList<int>& destinationPorts);

    const QString& getProtocol() const;
    void setProtocol(const QString& protocol);
    const QString& getServiceName() const;
    void setServiceName(const QString& service_name);
    Action getAction() const;
    void setAction(Action action);

private:
    Direction direction;
    QString sourceAddr;
    QList<int> sourcePorts;
    QString destinationAddr;
    QList<int> destinationPorts;
    QString protocol;
    QString serviceName;
    Action action;
};

#endif //NOMAD_FIREWALL_RULE_H
