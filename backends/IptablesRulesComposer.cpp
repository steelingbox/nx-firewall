#include "IptablesRulesComposer.h"

QString IptablesRulesComposer::compose(const Rule& rule)
{
    QStringList ruleString;
    ruleString.append(composeDirection(rule));
    ruleString.append(composeRuleProtocol(rule.getProtocol()));
    ruleString.append(composeSourceAddress(rule.getSourceAddr()));
    ruleString.append(composeSourcePorts(rule.getSourcePorts()));
    ruleString.append(composeDestinationAddress(rule.getDestinationAddr()));
    ruleString.append(composeDestinationPorts(rule.getDestinationPorts()));
    ruleString.append(composeRuleAction(rule.getAction()));

    ruleString.removeAll(QString());

    QString ipTablesRule = ruleString.join(" ");
    return ipTablesRule;
}

QString IptablesRulesComposer::composeDirection(const Rule& rule) const
{
    QString direction = "-A ";
    if (rule.getDirection()==Rule::INCOMING)
        direction += "INPUT";

    if (rule.getDirection()==Rule::OUTGOING)
        direction += "OUTPUT";

    return direction;
}
QString IptablesRulesComposer::composeSourcePorts(const QList<int>& list)
{
    QString ports;
    const int n = list.size();
    if (n>0) {
        if (n==1)
            ports = QString("--sport %1").arg(list.first());
        else
            ports = "-m multiport --sports "+composePortList(list);
    }

    return ports;
}
QString IptablesRulesComposer::composePortList(const QList<int>& list) const
{
    QString portList;
    for (const int& p: list)
        portList += QString("%1,").arg(p);
    portList.remove(portList.size()-1, 1);
    return portList;
}
QString IptablesRulesComposer::composeDestinationPorts(const QList<int>& list)
{
    QString ports;
    const int n = list.size();
    if (n>0) {
        if (n==1)
            ports = QString("--dport %1").arg(list.first());
        else
            ports = "-m multiport --dports "+composePortList(list);
    }

    return ports;
}
QString IptablesRulesComposer::composeRuleAction(const Rule::Action& action)
{
    QString actionRule = "-j ";
    if (action==Rule::ALOW)
        actionRule += "ACCEPT";

    if (action==Rule::DENY)
        actionRule += "DROP";

    if (action==Rule::REJECT)
        actionRule += "REJECT";

    return actionRule;
}
QString IptablesRulesComposer::composeRuleProtocol(const QString& p)
{
    if (!p.isEmpty())
        return QString("-p %1").arg(p.toLower());
    else
        return QString();
}

QString IptablesRulesComposer::composeSourceAddress(const QString& address)
{
    if (isAMatchAllAddress(address))
        return QString();

    return QString("-s %1").arg(address);
}

QString IptablesRulesComposer::composeDestinationAddress(const QString& address)
{
    if (isAMatchAllAddress(address))
        return QString();

    return QString("-d %1").arg(address);
}

bool IptablesRulesComposer::isAMatchAllAddress(const QString& address) const
{
    return address.isEmpty() || address=="0/0";
}