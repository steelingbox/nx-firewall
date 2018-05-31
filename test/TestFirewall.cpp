#include <QTest>
#include <QObject>
#include <QSignalSpy>
#include <QConstOverload>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTcpSocket>

#include "../entities/Firewall.h"
#include "../gateways/Iptables.h"

class TestFirewall : public QObject {
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
        Firewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(Firewall::PERMISSIVE);

        auto reply = manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
        QSignalSpy spyFinished(reply, &QNetworkReply::finished);
        QSignalSpy spyError(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error));

        QTRY_COMPARE(0, spyError.count());
        QTRY_COMPARE(1, spyFinished.count());

    }

    void stealth()
    {
        Iptables iptables;
        Firewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(Firewall::STEALTH);

        auto reply = manager->get(QNetworkRequest(QUrl("http://qt-project.org")));
        QSignalSpy spyFinished(reply, &QNetworkReply::finished);
        QSignalSpy spyError(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error));

        QTRY_COMPARE(0, spyError.count());
        QTRY_COMPARE(1, spyFinished.count());
    }

    void paranoid()
    {
        Iptables iptables;
        Firewall firewall;
        firewall.setNetfilterTool(&iptables);

        firewall.setCurrentProfile(Firewall::PARANOID);

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

QTEST_MAIN(TestFirewall)
#include "TestFirewall.moc"