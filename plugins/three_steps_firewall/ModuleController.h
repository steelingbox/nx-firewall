//
// Created by alexis on 5/25/18.
//

#ifndef NOMAD_FIREWALL_MODULECONTROLLER_H
#define NOMAD_FIREWALL_MODULECONTROLLER_H

#include <QObject>
#include <entities/ThreeStepsFirewall.h>
#include "RuleListModel.h"

class ModuleController : public QObject {
Q_OBJECT
    RuleListModel rulesModel;
    ThreeStepsFirewall firewall;


public:


};

#endif //NOMAD_FIREWALL_MODULECONTROLLER_H
