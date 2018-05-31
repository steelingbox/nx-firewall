//
// Created by alexis on 5/17/18.
//

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "JsonSettings.h"
void JsonSettings::save(const QVariantMap& settings)
{
    auto d = QJsonDocument::fromVariant(settings);
    auto data = d.toJson();

    QFile f(path);
    if (f.open(QIODevice::WriteOnly))
        f.write(data);
    else
        qCritical() << "Unable to write settings to " << path;
}
const QVariantMap JsonSettings::load()
{
    QFile f(path);
    if (f.open(QIODevice::ReadOnly)) {
        auto data = f.readAll();
        auto settingsJson = QJsonDocument::fromJson(data).object();
        auto settings = settingsJson.toVariantMap();
        return settings;
    } else
        qCritical() << "Unable to read settings from " << path;
    return QVariantMap();
}
JsonSettings::JsonSettings(const QString& path)
        :path(path) { }
JsonSettings::JsonSettings(): path(SettingsManager::SETTINGS_PATH)
{
}
