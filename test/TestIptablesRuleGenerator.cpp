#include <QTest>
#include <QObject>

#include "../entities/Rule.h"
#include "../gateways/IptablesRuleGenerator.h"

class TestIptablesRuleGenerator : public QObject {
Q_OBJECT
    class IptablesRuleGeneratorWrapper : public IptablesRuleGenerator {
        friend class TestIptablesRuleGenerator;
    };
private slots:

    void generateRuleDirection()
    {
        IptablesRuleGeneratorWrapper generator;
        QString iptablesRule;
        iptablesRule = generator.generateDirectionSection(Rule::INCOMING);
        QString expected = "-A INPUT";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDirectionSection(Rule::OUTGOING);
        expected = "-A OUTPUT";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRulePorts()
    {
        IptablesRuleGeneratorWrapper generator;

        QString iptablesRule;
        iptablesRule = generator.generateSourcePortsSection({});
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateSourcePortsSection({22});
        expected = "--sport 22";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateSourcePortsSection({80, 443});
        expected = "-m multiport --sports 80,443";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDestinationPortsSection({});
        expected = QString();
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDestinationPortsSection({22});
        expected = "--dport 22";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDestinationPortsSection({80, 443});
        expected = "-m multiport --dports 80,443";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRuleAction()
    {
        IptablesRuleGeneratorWrapper generator;
        Rule r;

        QString iptablesRule = generator.generateRuleActionSection(Rule::DENY);
        QString expected = "-j DROP";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateRuleActionSection(Rule::ALLOW);
        expected = "-j ACCEPT";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateRuleActionSection(Rule::REJECT);
        expected = "-j REJECT";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRuleProtocol()
    {
        IptablesRuleGeneratorWrapper generator;

        QString iptablesRule = generator.generateRuleProtocolSection(QString());
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateRuleProtocolSection("tcp");
        expected = "-p tcp";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateRuleProtocolSection("udp");
        expected = "-p udp";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRuleSourceAddress()
    {
        IptablesRuleGeneratorWrapper generator;

        QString iptablesRule = generator.generateSourceAddressSection(QString());
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateSourceAddressSection("15.15.15.15");
        expected = "-s 15.15.15.15";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRuleDestinationAddress()
    {
        IptablesRuleGeneratorWrapper generator;

        QString iptablesRule = generator.generateDestinationAddressSection(QString());
        QString expected;
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDestinationAddressSection("15.15.15.15");
        expected = "-d 15.15.15.15";
        QCOMPARE(iptablesRule, expected);
    }

    void generateBlockIncomingTcpOnPortRule()
    {
        Rule r;
        r.setDirection(Rule::INCOMING);
        r.setDestinationPorts({21});
        r.setAction(Rule::Action::DENY);
        r.setProtocol("tcp");

        IptablesRuleGeneratorWrapper generator;
        auto iptablesRule = generator.generateRule(r);
        auto expected = "-A INPUT -p tcp --dport 21 -j DROP";
        QCOMPARE(iptablesRule, expected);
    }

    void generateBlockAddressRule()
    {
        Rule r;
        r.setDirection(Rule::INCOMING);
        r.setSourceAddr("15.15.15.15");
        r.setAction(Rule::Action::DENY);

        IptablesRuleGeneratorWrapper generator;
        auto iptablesRule = generator.generateRule(r);
        auto expected = "-A INPUT -s 15.15.15.15 -j DROP";
        QCOMPARE(iptablesRule, expected);
    }

    void generateRulesToAllowSSHWithReplies()
    {
        Rule r;
        r.setDirection(Rule::INCOMING);
        r.setDestinationPorts({22});
        r.setProtocol("tcp");
        r.setAction(Rule::Action::ALLOW);

        IptablesRuleGeneratorWrapper generator;
        QStringList iptablesRule = generator.generateTwoWayCommunicationRules(r);
        QStringList expected = {"-A INPUT -p tcp --dport 22 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT",
                                "-A OUTPUT -p tcp --sport 22 -m conntrack --ctstate ESTABLISHED -j ACCEPT"};
        QCOMPARE(iptablesRule, expected);
    }

    void generateDefaultPolicies()
    {
        IptablesRuleGeneratorWrapper generator;
        QString iptablesRule = generator.generateDefaultPolicy("INPUT", Rule::DENY);
        QString expected = "--policy INPUT DROP";
        QCOMPARE(iptablesRule, expected);

        iptablesRule = generator.generateDefaultPolicy("OUTPUT", Rule::ALLOW);
        expected = "--policy OUTPUT ACCEPT";
        QCOMPARE(iptablesRule, expected);
    }
};

QTEST_MAIN(TestIptablesRuleGenerator)
#include "TestIptablesRuleGenerator.moc"