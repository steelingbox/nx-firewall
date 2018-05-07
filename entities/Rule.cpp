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
const QString& Rule::getSource_addr() const
{
    return source_addr;
}
void Rule::setSource_addr(const QString& source_addr)
{
    Rule::source_addr = source_addr;
}
void Rule::setSource_port(const QString& source_port)
{
    Rule::source_port = source_port;
}
const QString& Rule::getDestination_addr() const
{
    return destination_addr;
}
void Rule::setDestination_addr(const QString& destination_addr)
{
    Rule::destination_addr = destination_addr;
}
const QString& Rule::getDestination_port() const
{
    return destination_port;
}
void Rule::setDestination_port(const QString& destination_port)
{
    Rule::destination_port = destination_port;
}
const QString& Rule::getProtocol() const
{
    return protocol;
}
void Rule::setProtocol(const QString& protocol)
{
    Rule::protocol = protocol;
}
const QString& Rule::getService_name() const
{
    return service_name;
}
void Rule::setService_name(const QString& service_name)
{
    Rule::service_name = service_name;
}
Rule::Action Rule::getAction() const
{
    return action;
}
void Rule::setAction(Rule::Action action)
{
    Rule::action = action;
}
const QString& Rule::getSource_port() const
{
    return source_port;
}
