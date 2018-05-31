//
// Created by alexis on 5/25/18.
//

#ifndef NOMAD_FIREWALL_MODULECONTROLLER_H
#define NOMAD_FIREWALL_MODULECONTROLLER_H

#include <QObject>
#include <QList>
#include <RuleListModel.h>

#include <entities/ThreeStepsFirewall.h>

class ModuleController : public QObject {
Q_OBJECT
    Q_PROPERTY(ThreeStepsFirewall::Profile profile READ getProfile WRITE setProfile NOTIFY profileChanged)
    Q_PROPERTY(RuleListModel* rules READ getRulesModel NOTIFY rulesChanged)
    Q_PROPERTY(bool isInSync READ isInSync NOTIFY isInSyncChanged)
    ThreeStepsFirewall* firewall;
    ThreeStepsFirewall::Profile profile;
    RuleListModel *rulesModel;
    bool sync;

public:
    ModuleController(QObject* parent = nullptr);
    const ThreeStepsFirewall* getFirewall() const;
    void setFirewall(ThreeStepsFirewall* firewall);
    ThreeStepsFirewall::Profile getProfile() const;
    void setProfile(ThreeStepsFirewall::Profile profile);
    RuleListModel* getRulesModel() const;
    bool isInSync() const;

public slots:
    void applyConfig();
    void resetConfig();

signals:
    void profileChanged(ThreeStepsFirewall::Profile profile);
    void rulesChanged(RuleListModel* rules);


    bool isInRange(int index) const;
    void isInSyncChanged(bool isInSync);

protected slots:
    void updateIsInSync();
};

#endif //NOMAD_FIREWALL_MODULECONTROLLER_H
