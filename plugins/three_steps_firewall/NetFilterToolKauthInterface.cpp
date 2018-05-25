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

    KAuth::Action applyAction(QLatin1String("org.nomad.firewall.apply"));
    applyAction.setHelperId("org.nomad.firewall");
    applyAction.setArguments(ruleSetVariant);

    KAuth::ExecuteJob* job = applyAction.execute();
    connect(job, &KAuth::ExecuteJob::finished, [this](KJob* kjob) {
      auto job = qobject_cast<KAuth::ExecuteJob*>(kjob);
      if (job->error())
          qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();

      job->deleteLater();
    });

    job->start();
}
