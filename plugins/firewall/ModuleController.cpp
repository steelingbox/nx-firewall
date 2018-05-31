//
// Created by alexis on 5/25/18.
//
#include <QDebug>
#include <entities/QVariantRuleSetConverter.h>
#include <KAuth/KAuth>
#include "ModuleController.h"
ModuleController::ModuleController(QObject* parent)
        :QObject(parent), rulesModel(new RuleListModel())
{

    connect(rulesModel, &RuleListModel::modelReset, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::rowsInserted, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::rowsRemoved, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
    connect(rulesModel, &RuleListModel::dataChanged, this, &ModuleController::updateIsInSync, Qt::DirectConnection);

    connect(&firewall, &Firewall::profileChanged, this, &ModuleController::profileChanged);
    connect(this, &ModuleController::profileChanged, this, &ModuleController::updateIsInSync, Qt::DirectConnection);
}

void ModuleController::applyConfig()
{
    auto oldProfile = firewall.getCurrentProfile();
    auto oldRules = firewall.getCustomRules();

    firewall.setCurrentProfile(profile);
    firewall.setCustomRules(rulesModel->getRules());

    auto applyAction = getKAuthActionApply();
    auto applyJob = applyAction->execute();

    QObject::connect(applyJob, &KAuth::ExecuteJob::finished, [this, oldRules, oldProfile](KJob* kjob) {
      auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
      if (job->error()) {
          qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();
          firewall.setCustomRules(oldRules);
          firewall.setCurrentProfile(oldProfile);

          updateIsInSync();
      }

      job->deleteLater();
    });

    applyJob->start();
    delete (applyAction);
}
KAuth::Action* ModuleController::getKAuthActionApply() const
{
    auto settings = firewall.getSettings();

    auto applyAction = new KAuth::Action(QLatin1String("org.nomad.firewall.apply"));
    applyAction->setHelperId("org.nomad.firewall");
    applyAction->setArguments(settings);
    return applyAction;
}

void ModuleController::resetConfig()
{
    auto settings = settingsManager->load();
    firewall.setSettings(settings);

    setProfile(firewall.getCurrentProfile());
    rulesModel->setRules(firewall.getCustomRules());
}

void ModuleController::updateIsInSync()
{
    auto oldSync = sync;
    sync = (profile==firewall.getCurrentProfile()) &&
            (rulesModel->getRules()==firewall.getCustomRules());

    if (oldSync!=sync)
            emit isInSyncChanged(sync);
}
Firewall::Profile ModuleController::getProfile() const
{
    return profile;
}
void ModuleController::setProfile(Firewall::Profile profile)
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
SettingsManager* ModuleController::getSettingsManager() const
{
    return settingsManager;
}
void ModuleController::setSettingsManager(SettingsManager* settingsManager)
{
    ModuleController::settingsManager = settingsManager;
}