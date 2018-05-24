#include <QDebug>
#include <KAuth>
#include <KAuthExecuteJob>

#include <entities/QVariantRuleSetConverter.h>
#include "NetFilterToolKauthInterface.h"

NetFilterToolKauthInterface::NetFilterToolKauthInterface() { }

bool NetFilterToolKauthInterface::isAvailable()
{
    return true;
}

void NetFilterToolKauthInterface::apply(const RuleSet& ruleSet)
{
    auto ruleSetVariant = QVariantRuleSetConverter::toVariant(ruleSet);

    KAuth::Action applyAction(QLatin1String("org.maui.mfw.apply"));
    applyAction.setHelperId("org.maui.mfw");

    KAuth::ExecuteJob* job = applyAction.execute();
    job->setProperty("ruleset", ruleSetVariant);
    connect(job, &KAuth::ExecuteJob::finished, [this](KJob* kjob) {
      auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
      if (job->error())
          qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();

      job->deleteLater();
    });

    job->start();
}
