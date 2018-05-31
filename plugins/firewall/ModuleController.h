//
// Created by alexis on 5/25/18.
//

#ifndef NOMAD_FIREWALL_MODULECONTROLLER_H
#define NOMAD_FIREWALL_MODULECONTROLLER_H

#include <QObject>
#include <QList>
#include <RuleListModel.h>

#include <entities/Firewall.h>
#include <KAuth/KAuth>

class ModuleController : public QObject {
Q_OBJECT
    Q_PROPERTY(Firewall::Profile profile READ getProfile WRITE setProfile NOTIFY profileChanged)
    Q_PROPERTY(RuleListModel* rules READ getRulesModel NOTIFY rulesChanged)
    Q_PROPERTY(bool isInSync READ isInSync NOTIFY isInSyncChanged)
    Firewall firewall;
    SettingsManager *settingsManager;
    Firewall::Profile profile;
    RuleListModel *rulesModel;
    bool sync;

public:
    ModuleController(QObject* parent = nullptr);
    Firewall::Profile getProfile() const;
    void setProfile(Firewall::Profile profile);
    RuleListModel* getRulesModel() const;
    bool isInSync() const;

    SettingsManager* getSettingsManager() const;
    void setSettingsManager(SettingsManager* settingsManager);

public slots:
    void applyConfig();
    void resetConfig();

signals:
    void profileChanged(Firewall::Profile profile);
    void rulesChanged(RuleListModel* rules);

    void isInSyncChanged(bool isInSync);

protected slots:
    void updateIsInSync();

private:
    KAuth::Action* getKAuthActionApply() const;
};

#endif //NOMAD_FIREWALL_MODULECONTROLLER_H
