#include <KAuth/KAuth>
#include <QDebug>
#include <QCoreApplication>
#include <QVariantList>

void testApply()
{
    KAuth::Action applyAction(QLatin1String("org.maui.mfw.apply"));
    applyAction.setHelperId("org.maui.mfw");

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