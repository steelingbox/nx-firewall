#include <QTest>
#include <QObject>

#include "../entities/Rule.h"
#include "../backends/IptablesRulesComposer.h"

class TestIptablesRulesComposer : public QObject {
Q_OBJECT
private slots:

    void composeRuleDirection()
    {
        IptablesRulesComposer composer;
        Rule r;
        r.setDirection(Rule::INCOMING);

        QString iptablesRule = composer.composeDirection(r);
        QString expected = "-A INPUT";
        QCOMPARE(iptablesRule, expected);

        r.setDirection(Rule::OUTGOING);

        iptablesRule = composer.composeDirection(r);
        expected = "-A OUTPUT";
        QCOMPARE(iptablesRule, expected);
    }

    void composeRulePorts()
    {
        IptablesRulesComposer composer;

        QString iptablesRule = composer.composeSourcePorts({});
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeSourcePorts({22});
        expected = "--sport 22";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeSourcePorts({80, 443});
        expected = "-m multiport --sports 80,443";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeDestinationPorts({});
        expected = QString();
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeDestinationPorts({22});
        expected = "--dport 22";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeDestinationPorts({80, 443});
        expected = "-m multiport --dports 80,443";
        QCOMPARE(iptablesRule, expected);
    }

    void composeRuleAction()
    {
        IptablesRulesComposer composer;
        Rule r;

        QString iptablesRule = composer.composeRuleAction(Rule::DENY);
        QString expected = "-j DROP";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeRuleAction(Rule::ALOW);
        expected = "-j ACCEPT";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeRuleAction(Rule::REJECT);
        expected = "-j REJECT";
        QCOMPARE(iptablesRule, expected);
    }

    void composeRuleProtocol()
    {
        IptablesRulesComposer composer;
        Rule r;

        QString iptablesRule = composer.composeRuleProtocol(QString());
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeRuleProtocol("tcp");
        expected = "-p tcp";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = composer.composeRuleProtocol("udp");
        expected = "-p udp";
        QCOMPARE(iptablesRule, expected);
    }

    void composeRule()
    {
        Rule r;
        r.setDirection(Rule::INCOMING);
        r.setDestinationPorts({21});
        r.setAction(Rule::Action::DENY);
        r.setProtocol("tcp");

        IptablesRulesComposer composer;
        QString iptablesRule = composer.compose(r);
        QString expected = "-A INPUT -p tcp --dport 21 -j DROP";
        QCOMPARE(iptablesRule, expected);
    }
};

QTEST_MAIN(TestIptablesRulesComposer)
#include "TestIptablesRulesComposer.moc"