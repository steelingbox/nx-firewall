//
// Created by alexis on 5/25/18.
//

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
    roles[Interface] = "interface";
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

    return QVariant();
}
