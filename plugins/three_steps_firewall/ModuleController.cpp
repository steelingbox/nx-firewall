//
// Created by alexis on 5/25/18.
//

#include "ModuleController.h"
ModuleController::ModuleController(QObject* parent)
        :QObject(parent), rulesModel(new RuleListModel()) { }

void ModuleController::applyConfig()
{
    firewall->setCustomRules(rulesModel->getRules());
    firewall->setCurrentProfile(profile);

    firewall->resetProfile();
}
void ModuleController::resetConfig()
{
    setProfile(firewall->getCurrentProfile());
    rulesModel->setRules(firewall->getCustomRules());
}
const ThreeStepsFirewall* ModuleController::getFirewall() const
{
    return firewall;
}
void ModuleController::setFirewall(ThreeStepsFirewall* firewall)
{
    ModuleController::firewall = firewall;
    disconnect(this, &ModuleController::profileChanged, nullptr, nullptr);
//    disconnect(this, &ModuleController::rulesChanged, nullptr, nullptr);

    connect(firewall, &ThreeStepsFirewall::profileChanged, this, &ModuleController::profileChanged);
//    connect(firewall, &ThreeStepsFirewall::customRulesChanged, [this]() {
//      emit rulesChanged(getRuleListProperty());
//    });
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
