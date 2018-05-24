//
// Created by alexis on 5/22/18.
//

#ifndef NOMAD_FIREWALL_MFWQMLPLUGIN_H
#define NOMAD_FIREWALL_MFWQMLPLUGIN_H

#include <QQmlExtensionPlugin>

class MFWQmlPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    virtual void registerTypes(const char* uri);
};

#endif //NOMAD_FIREWALL_MFWQMLPLUGIN_H
