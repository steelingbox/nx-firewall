//
// Created by alexis on 5/23/18.
//

#ifndef NOMAD_FIREWALL_SETTINGSMANAGERKAUTHINTERFACE_H
#define NOMAD_FIREWALL_SETTINGSMANAGERKAUTHINTERFACE_H

#include <entities/SettingsManager.h>
#include <gateways/JsonSettings.h>

class SettingsManagerKauthInterface : public JsonSettings {
public:
    SettingsManagerKauthInterface(const QString& path);
    void save(const QVariantMap& settings) override;
};

#endif //NOMAD_FIREWALL_SETTINGSMANAGERKAUTHINTERFACE_H
