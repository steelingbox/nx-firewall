//
// Created by alexis on 5/25/18.
//

#include <QDebug>
#include <QMetaEnum>
#include "RuleListModel.h"

QHash<int, QByteArray> RuleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Direction] = "direction";
    roles[SourceAddr] = "sourceAddr";
    roles[SourcePorts] = "sourcePorts";
    roles[DestinationAddr] = "destinationAddr";
    roles[DestinationPorts] = "destinationPorts";
    roles[Protocol] = "protocol";
    roles[Interface] = "iface";
    roles[Action] = "action";

    return roles;
}

QModelIndex RuleListModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}
int RuleListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return rules.size();
}
int RuleListModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 1;
}
QVariant RuleListModel::data(const QModelIndex& index, int role) const
{
    if (index.row()>=rules.size())
        return QVariant();

    auto rule = rules.at(index.row());

    if (role==Direction) {
        auto directionEnum = QMetaEnum::fromType<Rule::Direction>();
        return directionEnum.valueToKey(rule->getDirection());
    }

    if (role==SourceAddr)
        return rule->getSourceAddr();

    if (role==SourcePorts) {
        auto ports = rule->getSourcePorts();
        return getPortListStr(ports);;
    }

    if (role==DestinationAddr)
        return rule->getDestinationAddr();

    if (role==DestinationPorts) {
        auto ports = rule->getDestinationPorts();
        return getPortListStr(ports);
    }

    if (role==Protocol)
        return rule->getProtocol();

    if (role==Interface) {
        qWarning() << "INTERFACE" << rule->getInterface();
        return rule->getInterface();
    }


    if (role==Action) {
        auto actionEnum = QMetaEnum::fromType<Rule::Action>();
        return actionEnum.valueToKey(rule->getAction());
    }

    return QVariant();
}
QString RuleListModel::getPortListStr(const QList<int>& ports) const
{
    QStringList portsStr;
    for (const int& port : ports)
        portsStr << QString::number(port);

    return portsStr.join(",");
}
const QList<Rule*>& RuleListModel::getRules() const
{
    return rules;
}
void RuleListModel::setRules(const QList<Rule*>& rules)
{
    beginResetModel();
    RuleListModel::rules = rules;
    endResetModel();
}
void RuleListModel::append(Rule* newRule)
{
    beginInsertRows(QModelIndex(), rules.size(), rules.size());
    rules.append(newRule);
    endInsertRows();
}
