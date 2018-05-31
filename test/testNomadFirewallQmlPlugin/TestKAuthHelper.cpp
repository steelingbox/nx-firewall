#include <KAuth/KAuth>
#include <QDebug>
#include <QCoreApplication>
#include <QVariantList>
#include <QVariantMap>
#include "entities/Rule.h"
#include "entities/RuleSet.h"
#include "entities/QVariantRuleSetConverter.h"

void testApply()
{
    RuleSet ruleSet;
    ruleSet.setDefaultIncomingPolicy(Rule::ALLOW);
    ruleSet.setDefaultOutgoingPolicy(Rule::ALLOW);
    QVariantMap arguments = QVariantRuleSetConverter::toVariant(ruleSet);

    KAuth::Action applyAction(QLatin1String("org.nomad.firewall.apply"));
    applyAction.setHelperId("org.nomad.firewall");
    applyAction.setArguments(arguments);

    KAuth::ExecuteJob* job = applyAction.execute();


    job->exec();
    if (job->error())
        qWarning() << "BACKEND ERROR: " << job->error() << job->errorText();

    job->deleteLater();
}

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    testApply();
    return app.exec();
}