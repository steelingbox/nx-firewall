//
// Created by alexis on 5/7/18.
//

#ifndef NOMAD_FIREWALL_SERVICE_H
#define NOMAD_FIREWALL_SERVICE_H

#include "RuleSet.h"

#include <QObject>
class Service : public QObject {
Q_OBJECT
    Q_PROPERTY(bool isDeployed MEMBER isDeployed NOTIFY isDeployedChanged)
    Q_PROPERTY(bool isEnabled MEMBER isEnabled NOTIFY isEnabledChanged)
    bool isDeployed;
    bool isEnabled;

public:
public slots:
    void start();
    void stop();

    void deploy();
    void remove();

    void updateRules(const RuleSet &ruleSet);

signals:
    void isDeployedChanged(bool isDeployed);
    void isEnabledChanged(bool isEnabled);

    void startRequested();
    void stopRequested();

    void deployRequested();
    void removeRequested();

    void updateRulesRequested(const RuleSet &ruleSet);
    void rulesUpdatedSuccessfuly();
    void rulesUpdateFaile(const QString &err);
};

#endif //NOMAD_FIREWALL_SERVICE_H
