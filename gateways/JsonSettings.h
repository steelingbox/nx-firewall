//
// Created by alexis on 5/17/18.
//

#ifndef NOMAD_FIREWALL_JSONSETTINGS_H
#define NOMAD_FIREWALL_JSONSETTINGS_H
#include <QVariant>
#include <QVariantMap>
#include "../entities/SettingsManager.h"
class JsonSettings : public SettingsManager {
    QString path;
public:
    JsonSettings();
    explicit JsonSettings(const QString& path);
    void save(const QVariantMap& settings) override;
    const QVariantMap load() override;
};

#endif //NOMAD_FIREWALL_JSONSETTINGS_H
