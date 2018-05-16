#include <QTest>
#include <QObject>
#include <QSignalSpy>
#include <QConstOverload>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>

#include "../entities/ThreeStepsFirewall.h"
#include "../gateways/Iptables.h"

class TestTreeStepsFirewall : public QObject {
Q_OBJECT
    QNetworkAccessManager* manager;
private slots:
    void initTestCase()
    {
        manager = new QNetworkAccessManager(this);
    }
    void permissive()
    {
        Iptables iptables;
        ThreeStepsFirewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(ThreeStepsFirewall::PERMISSIVE);

        auto reply = manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
        QSignalSpy spyFinished(reply, &QNetworkReply::finished);
        QSignalSpy spyError(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error));

        QTRY_COMPARE(0, spyError.count());
        QTRY_COMPARE(1, spyFinished.count());

    }

    void stealth()
    {
        Iptables iptables;
        ThreeStepsFirewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(ThreeStepsFirewall::STEALTH);

        auto reply = manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
        QSignalSpy spyFinished(reply, &QNetworkReply::finished);
        QSignalSpy spyError(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error));

        QTRY_COMPARE(0, spyError.count());
        QTRY_COMPARE(1, spyFinished.count());
    }

    void paranoid()
    {
        Iptables iptables;
        ThreeStepsFirewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(ThreeStepsFirewall::PARANOID);

        auto reply = manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
        QSignalSpy spyFinished(reply, &QNetworkReply::finished);
        QSignalSpy spyError(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error));

        QTRY_COMPARE(0, spyError.count());
        QTRY_COMPARE(1, spyFinished.count());
    }

    void cleanupTestCase()
    {
//        permissive();
        manager->deleteLater();
    }
};

QTEST_MAIN(TestTreeStepsFirewall)
#include "TestTreeStepsFirewall.moc"