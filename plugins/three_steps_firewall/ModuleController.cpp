//
// Created by alexis on 5/25/18.
//
#include <QDebug>
#include "ModuleController.h"
ModuleController::ModuleController(QObject* parent)
        :QObject(parent), rulesModel(new RuleListModel()) {

    connect(rulesModel, &RuleListModel::modelReset, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::rowsInserted, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::rowsRemoved, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::dataChanged, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
}

void ModuleController::applyConfig()
{
    firewall->setCustomRules(rulesModel->getRules());
    firewall->setCurrentProfile(profile);

    firewall->saveSettings();
}
void ModuleController::resetConfig()
{
    setProfile(firewall->getCurrentProfile());
    rulesModel->setRules(firewall->getCustomRules());
}

void ModuleController::updateIsInSync() {
    auto oldSync = sync;
    sync = (profile == firewall->getCurrentProfile()) &&
            (rulesModel->getRules() == firewall->getCustomRules());

    if (oldSync != sync)
        emit isInSyncChanged(sync);
}
const ThreeStepsFirewall* ModuleController::getFirewall() const
{
    return firewall;
}
void ModuleController::setFirewall(ThreeStepsFirewall* firewall)
{
    disconnect(this, &ModuleController::profileChanged, nullptr, nullptr);

    connect(firewall, &ThreeStepsFirewall::profileChanged, this, &ModuleController::profileChanged);
    connect(this, &ModuleController::profileChanged, this, &ModuleController::updateIsInSync, Qt::DirectConnection);

    ModuleController::firewall = firewall;

    firewall->loadSettings();

    setProfile(firewall->getCurrentProfile());
    rulesModel->setRules(firewall->getCustomRules());
}
ThreeStepsFirewall::Profile ModuleController::getProfile() const
{
    return profile;
}
void ModuleController::setProfile(ThreeStepsFirewall::Profile profile)
{
    ModuleController::profile = profile;
    emit profileChanged(profile);
}

RuleListModel* ModuleController::getRulesModel() const
{
    return rulesModel;
}

bool ModuleController::isInSync() const
{
    return sync;
}
