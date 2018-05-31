#include <QDebug>
#include <KAuth>
#include "SettingsManagerKauthInterface.h"

SettingsManagerKauthInterface::SettingsManagerKauthInterface(const QString& path)
        :JsonSettings(path) { }

void SettingsManagerKauthInterface::save(const QVariantMap& settings)
{
    KAuth::Action applyAction(QLatin1String("org.nomad.firewall.save"));
    applyAction.setHelperId("org.nomad.firewall");
    applyAction.setArguments(settings);

    KAuth::ExecuteJob* job = applyAction.execute();
    QObject::connect(job, &KAuth::ExecuteJob::finished, [this](KJob* kjob) {
      auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
      if (job->error())
          qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();

      job->deleteLater();
    });

    job->start();
}

