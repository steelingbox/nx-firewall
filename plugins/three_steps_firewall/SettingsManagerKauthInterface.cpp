#include <QDebug>
#include <KAuth>
#include "SettingsManagerKauthInterface.h"

SettingsManagerKauthInterface::SettingsManagerKauthInterface(const QString& path)
        :JsonSettings(path) { }

void SettingsManagerKauthInterface::save(const QVariantMap& settings)
{
    KAuth::Action applyAction(QLatin1String("org.maui.mfw.save"));
    applyAction.setHelperId("org.maui.mfw");

    KAuth::ExecuteJob* job = applyAction.execute();
    job->setProperty("settings", settings);
    QObject::connect(job, &KAuth::ExecuteJob::finished, [this](KJob* kjob) {
      auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
      if (job->error())
          qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();

      job->deleteLater();
    });

    job->start();
}

