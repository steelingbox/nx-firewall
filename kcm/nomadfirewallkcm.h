#ifndef NOMADFIREWALLKCM_H
#define NOMADFIREWALLKCM_H


#include <KQuickAddons/ConfigModule>

class NomadFirewallKCM : public KQuickAddons::ConfigModule
{
    Q_OBJECT
public:
    explicit NomadFirewallKCM(QObject *parent, const QVariantList &args);

    void save() override;
    void load() override;
    void defaults() override;

    ~NomadFirewallKCM();

signals:
    void saveRequested();
    void loadRequested();
    void defaultsResetRequested();

};

#endif // NOMADFIREWALLKCM_H
