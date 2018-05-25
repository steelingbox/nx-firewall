//
// Created by alexis on 5/23/18.
//

#ifndef NOMAD_FIREWALL_MFW_HELPER_H
#define NOMAD_FIREWALL_MFW_HELPER_H

#include <QVariantMap>
#include <KAuth>
#include <QObject>

using namespace KAuth;
class NomadFirewallKAuthHelper : public QObject {
Q_OBJECT

public:
    NomadFirewallKAuthHelper();
public Q_SLOTS:
    ActionReply apply(const QVariantMap data);
    ActionReply save(const QVariantMap settings);

};

#endif //NOMAD_FIREWALL_MFW_HELPER_H
