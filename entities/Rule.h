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

    Direction direction;
    QString source_addr, source_port;
    QString destination_addr, destination_port;

    QString protocol;
    QString service_name;
    Action action;

public:
    Direction getDirection() const;
    void setDirection(Direction direction);
    const QString& getSource_addr() const;
    void setSource_addr(const QString& source_addr);
    const QString& getSource_port() const;
    void setSource_port(const QString& source_port);
    const QString& getDestination_addr() const;
    void setDestination_addr(const QString& destination_addr);
    const QString& getDestination_port() const;
    void setDestination_port(const QString& destination_port);
    const QString& getProtocol() const;
    void setProtocol(const QString& protocol);
    const QString& getService_name() const;
    void setService_name(const QString& service_name);
    Action getAction() const;
    void setAction(Action action);
};

#endif //NOMAD_FIREWALL_RULE_H
