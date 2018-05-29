//
// Created by alexis on 5/22/18.
//

#include "NomadFirewallQmlPlugin.h"
#include <entities/ThreeStepsFirewall.h>
#include "NetFilterToolKauthInterface.h"
#include "SettingsManagerKauthInterface.h"
#include "RuleListModel.h"
#include "ModuleController.h"

#include <QtQml/QtQml>

// Second, define the singleton type provider function (callback).
static QObject *firewall_controller_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto fw = new ThreeStepsFirewall();
    auto netfilter = new NetFilterToolKauthInterface();
    auto settings = new SettingsManagerKauthInterface("/etc/nomad_firewall_rules.json");

    fw->setNetfilterTool(netfilter);
    fw->setSettingsManager(settings);

    auto moduleController = new ModuleController();
    moduleController->setFirewall(fw);

    return moduleController;
}


void NomadFirewallQmlPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri==QLatin1String("org.nomad.firewall"));

    qmlRegisterSingletonType<ModuleController>(uri, 1, 0, "Controller", firewall_controller_singletontype_provider);
    qmlRegisterType<Rule>(uri, 1, 0, "Rule");
}
