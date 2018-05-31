//
// Created by alexis on 5/25/18.
//

#ifndef NOMAD_FIREWALL_RULELISTMODEL_H
#define NOMAD_FIREWALL_RULELISTMODEL_H

#include <QList>
#include <QAbstractListModel>

#include <entities/Rule.h>

class RuleListModel : public QAbstractListModel {
Q_OBJECT
    QList<Rule*> rules;
public:
    enum RuleListRoles {
      Direction = Qt::UserRole+1,
      SourceAddr,
      SourcePorts,
      DestinationAddr,
      DestinationPorts,
      Protocol,
      Interface,
      Action
    };

    QHash<int, QByteArray> roleNames() const;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

    const QList<Rule*>& getRules() const;
    void setRules(const QList<Rule*>& rules);

    public slots:
    void append(Rule * newRule);

    QString getPortListStr(const QList<int>& ports) const;
};

#endif //NOMAD_FIREWALL_RULELISTMODEL_H
