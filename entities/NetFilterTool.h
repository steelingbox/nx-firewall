//
// Created by alexis on 5/10/18.
//

#ifndef NOMAD_FIREWALL_NETWORKFILTERINGMANAGEMENTTOOL_H
#define NOMAD_FIREWALL_NETWORKFILTERINGMANAGEMENTTOOL_H

#include <QObject>
#include "../entities/RuleSet.h"

class NetFilterTool : public QObject {
Q_OBJECT

public:
    virtual bool isAvailable() = 0;
    virtual void apply(const RuleSet& ruleSet) = 0;
};

#endif //NOMAD_FIREWALL_NETWORKFILTERINGMANAGEMENTTOOL_H
