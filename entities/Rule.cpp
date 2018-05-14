//
// Created by alexis on 5/4/18.
//

#include "Rule.h"
Rule::Direction Rule::getDirection() const
{
    return direction;
}
void Rule::setDirection(Rule::Direction direction)
{
    Rule::direction = direction;
}

const QString& Rule::getProtocol() const
{
    return protocol;
}
void Rule::setProtocol(const QString& protocol)
{
    Rule::protocol = protocol;
}
Rule::Action Rule::getAction() const
{
    return action;
}
void Rule::setAction(Rule::Action action)
{
    Rule::action = action;
}

Rule::Rule()
        :direction(INCOMING), action(DENY) { }

const QString& Rule::getSourceAddr() const
{
    return sourceAddr;
}
void Rule::setSourceAddr(const QString& sourceAddr)
{
    Rule::sourceAddr = sourceAddr;
}
const QList<int>& Rule::getSourcePorts() const
{
    return sourcePorts;
}
void Rule::setSourcePorts(const QList<int>& sourcePorts)
{
    Rule::sourcePorts = sourcePorts;
}
const QString& Rule::getDestinationAddr() const
{
    return destinationAddr;
}
void Rule::setDestinationAddr(const QString& destinationAddr)
{
    Rule::destinationAddr = destinationAddr;
}
const QList<int>& Rule::getDestinationPorts() const
{
    return destinationPorts;
}
void Rule::setDestinationPorts(const QList<int>& destinationPorts)
{
    Rule::destinationPorts = destinationPorts;
}
bool Rule::operator==(const Rule& rhs) const
{
    return direction==rhs.direction &&
            sourceAddr==rhs.sourceAddr &&
            sourcePorts==rhs.sourcePorts &&
            destinationAddr==rhs.destinationAddr &&
            destinationPorts==rhs.destinationPorts &&
            protocol==rhs.protocol &&
            action==rhs.action;
}
bool Rule::operator!=(const Rule& rhs) const
{
    return !(rhs==*this);
}
