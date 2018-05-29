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
    ThreeStepsFirewall* firewall;
    ThreeStepsFirewall::Profile profile;
    RuleListModel *rulesModel;
public:
    ModuleController(QObject* parent = nullptr);
    const ThreeStepsFirewall* getFirewall() const;
    void setFirewall(ThreeStepsFirewall* firewall);
    ThreeStepsFirewall::Profile getProfile() const;
    void setProfile(ThreeStepsFirewall::Profile profile);
    RuleListModel* getRulesModel() const;

public slots:
    void applyConfig();
    void resetConfig();


signals:
    void profileChanged(ThreeStepsFirewall::Profile profile);
    void rulesChanged(RuleListModel* rules);


    bool isInRange(int index) const;
};

#endif //NOMAD_FIREWALL_MODULECONTROLLER_H
