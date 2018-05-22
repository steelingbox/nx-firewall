//
// Created by alexis on 5/17/18.
//

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

#include "JsonSettings.h"
void JsonSettings::save(const QVariantMap settings)
{
    auto settingsJson = QJsonObject::fromVariantMap(settings);

    QJsonDocument d;
    d.setObject(settingsJson);
    auto data = d.toJson();

    QDir parent(path);
    parent.mkpath(parent.dirName());

    QFile f(path);
    if (f.open(QIODevice::WriteOnly))
        f.write(data);
}
const QVariantMap JsonSettings::load()
{
    QFile f(path);
    if (f.open(QIODevice::ReadOnly)) {
        auto data = f.readAll();
        auto settingsJson = QJsonDocument::fromJson(data).object();
        auto settings = settingsJson.toVariantMap();
        return settings;
    }
    return QVariantMap();
}
JsonSettings::JsonSettings(const QString& path)
        :path(path) { }
