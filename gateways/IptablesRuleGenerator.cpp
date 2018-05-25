#include "IptablesRuleGenerator.h"

QString IptablesRuleGenerator::generateRule(const Rule* rule)
{
    QStringList ruleSections;
    ruleSections.append(generateDirectionSection(rule->getDirection()));
    ruleSections.append(generateRuleInterfaceSection(rule->getInterface()));
    ruleSections.append(generateRuleProtocolSection(rule->getProtocol()));
    ruleSections.append(generateSourceAddressSection(rule->getSourceAddr()));
    ruleSections.append(generateSourcePortsSection(rule->getSourcePorts()));
    ruleSections.append(generateDestinationAddressSection(rule->getDestinationAddr()));
    ruleSections.append(generateDestinationPortsSection(rule->getDestinationPorts()));

    ruleSections.append(generateRuleActionSection(rule->getAction()));

    ruleSections.removeAll(QString());
    QString ruleString = ruleSections.join(" ");
    return ruleString;
}

Rule::Direction IptablesRuleGenerator::getOppositeDirection(const Rule::Direction& direction)
{
    Rule::Direction opposite;
    if (direction==Rule::INCOMING)
        opposite = Rule::OUTGOING;

    if (direction==Rule::OUTGOING)
        opposite = Rule::INCOMING;
    return opposite;
}

QString IptablesRuleGenerator::generateDirectionSection(const Rule::Direction& direction)
{
    QString directionStr = "-A ";
    if (direction==Rule::INCOMING)
        directionStr += "INPUT";

    if (direction==Rule::OUTGOING)
        directionStr += "OUTPUT";

    return directionStr;
}

QString IptablesRuleGenerator::generateSourcePortsSection(const QList<int>& list)
{
    QString ports;
    const int n = list.size();
    if (n>0) {
        if (n==1)
            ports = QString("--sport %1").arg(list.first());
        else
            ports = "-m multiport --sports "+generatePortListSection(list);
    }

    return ports;
}

QString IptablesRuleGenerator::generatePortListSection(const QList<int>& list)
{
    QString portList;
    for (const int& p: list)
        portList += QString("%1,").arg(p);
    portList.remove(portList.size()-1, 1);
    return portList;
}

QString IptablesRuleGenerator::generateDestinationPortsSection(const QList<int>& list)
{
    QString ports;
    const int n = list.size();
    if (n>0) {
        if (n==1)
            ports = QString("--dport %1").arg(list.first());
        else
            ports = "-m multiport --dports "+generatePortListSection(list);
    }

    return ports;
}

QString IptablesRuleGenerator::generateRuleActionSection(const Rule::Action& action)
{
    QString actionRule = "-j "+translateAction(action);
    return actionRule;
}

QString IptablesRuleGenerator::translateAction(const Rule::Action& action)
{
    QString actionString;
    if (action==Rule::ALLOW)
        return "ACCEPT";

    if (action==Rule::DENY)
        return "DROP";

    if (action==Rule::REJECT)
        return "REJECT";

    return QString();
}

QString IptablesRuleGenerator::generateRuleInterfaceSection(const QString& iface)
{
    if (!iface.isEmpty())
        return QString("-i %1").arg(iface.toLower());
    else
        return QString();
}

QString IptablesRuleGenerator::generateRuleProtocolSection(const QString& p)
{
    if (!p.isEmpty())
        return QString("-p %1").arg(p.toLower());
    else
        return QString();
}

QString IptablesRuleGenerator::generateSourceAddressSection(const QString& address)
{
    if (isAMatchAllAddress(address))
        return QString();

    return QString("-s %1").arg(address);
}

QString IptablesRuleGenerator::generateDestinationAddressSection(const QString& address)
{
    if (isAMatchAllAddress(address))
        return QString();

    return QString("-d %1").arg(address);
}

bool IptablesRuleGenerator::isAMatchAllAddress(const QString& address)
{
    return address.isEmpty() || address=="0/0";
}

QStringList IptablesRuleGenerator::generateTwoWayCommunicationRules(const Rule* rule)
{
    QStringList rules;

    rules << generateRuleForNewConnections(rule);
    rules << generateReverseRuleForEstablishedConnections(rule);

    return rules;
}

QString IptablesRuleGenerator::generateRuleForNewConnections(const Rule* rule)
{
    QStringList ruleSections;
    ruleSections.append(generateDirectionSection(rule->getDirection()));
    ruleSections.append(generateRuleProtocolSection(rule->getProtocol()));
    ruleSections.append(generateSourceAddressSection(rule->getSourceAddr()));
    ruleSections.append(generateSourcePortsSection(rule->getSourcePorts()));
    ruleSections.append(generateDestinationAddressSection(rule->getDestinationAddr()));
    ruleSections.append(generateDestinationPortsSection(rule->getDestinationPorts()));

    ruleSections.append("-m conntrack --ctstate NEW,ESTABLISHED,RELATED");

    ruleSections.append(generateRuleActionSection(rule->getAction()));

    ruleSections.removeAll(QString());
    QString ruleString = ruleSections.join(" ");
    return ruleString;
}

QString IptablesRuleGenerator::generateReverseRuleForEstablishedConnections(const Rule* rule)
{
    QStringList ruleSections;
    const Rule::Direction opositeDirection = getOppositeDirection(rule->getDirection());
    ruleSections.append(generateDirectionSection(opositeDirection));

    ruleSections.append(generateRuleProtocolSection(rule->getProtocol()));

    // Notice that source and destination values are switched
    ruleSections.append(generateSourceAddressSection(rule->getDestinationAddr()));
    ruleSections.append(generateSourcePortsSection(rule->getDestinationPorts()));

    ruleSections.append(generateDestinationAddressSection(rule->getSourceAddr()));
    ruleSections.append(generateDestinationPortsSection(rule->getSourcePorts()));

    ruleSections.append("-m conntrack --ctstate ESTABLISHED,RELATED");

    ruleSections.append(generateRuleActionSection(rule->getAction()));

    ruleSections.removeAll(QString());
    QString ruleString = ruleSections.join(" ");
    return ruleString;
}
QString IptablesRuleGenerator::generateDefaultPolicy(const QString& chain, const Rule::Action& action)
{
    const QString temp = "--policy %1 %2";
    return temp.arg(chain).arg(translateAction(action));

}
