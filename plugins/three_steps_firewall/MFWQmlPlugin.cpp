//
// Created by alexis on 5/22/18.
//

#include "MFWQmlPlugin.h"
#include <entities/ThreeStepsFirewall.h>
#include "NetFilterToolKauthInterface.h"
#include "SettingsManagerKauthInterface.h"

#include <QtQml/QtQml>

// Second, define the singleton type provider function (callback).
static QObject *three_steps_firewall_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    auto fw = new ThreeStepsFirewall();
    auto netfilter = new NetFilterToolKauthInterface();
    auto settings = new SettingsManagerKauthInterface("/etc/mfw_rules.json");

    fw->setNetfilterTool(netfilter);
    fw->setSettingsManager(settings);
    return fw;
}


void MFWQmlPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri==QLatin1String("org.maui.mfw"));

    qmlRegisterSingletonType<ThreeStepsFirewall>(uri, 1, 0, "ThreeStepsFirewall", three_steps_firewall_singletontype_provider);

}
