//
// Created by alexis on 5/18/18.
//

#ifndef NOMAD_FIREWALL_SETTINGS_H
#define NOMAD_FIREWALL_SETTINGS_H

#include <QVariantMap>

class SettingsManager {
public:
    virtual void save(const QVariantMap settings) = 0;
    virtual const QVariantMap load() = 0;
};

#endif //NOMAD_FIREWALL_SETTINGS_H
