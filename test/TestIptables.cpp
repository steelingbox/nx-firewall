#include <QTest>
#include <QObject>

#include "../gateways/Iptables.h"

class TestIptables : public QObject {
Q_OBJECT
    class IptablesWrapper : public Iptables {
        friend class TestIptables;
    };
private slots:
    void testGetBinaryPath()
    {
        IptablesWrapper wrapper;
        QString path = wrapper.getBinaryPath();
        QCOMPARE(path, "/sbin/iptables");
    };

    void testGenerateIptablesInstructions()
    {
        RuleSet ruleSet = getDenyAllButHttpAndHttpsRuleSet();

        IptablesWrapper wrapper;
        auto rules = wrapper.generateIptablesInstructions(ruleSet);
        QStringList expected = {"--flush",
                                "--policy INPUT DROP",
                                "--policy OUTPUT DROP",
                                "-A OUTPUT -p tcp -m multiport --dports 80,443 -m conntrack --ctstate NEW,ESTABLISHED -j ACCEPT",
                                "-A INPUT -p tcp -m multiport --sports 80,443 -m conntrack --ctstate ESTABLISHED -j ACCEPT"};
        QCOMPARE(rules, expected);
    }

    void setRules()
    {
        RuleSet ruleSet = getDenyAllButHttpAndHttpsRuleSet();
        IptablesWrapper wrapper;
        wrapper.apply(ruleSet);
    }

private:
    RuleSet getDenyAllButHttpAndHttpsRuleSet() const
    {
        RuleSet ruleSet;
        ruleSet.setDefaultIncomingPolicy(Rule::DENY);
        ruleSet.setDefaultOutgoingPolicy(Rule::DENY);

        Rule allowHttp = getAllowHttpAndHttpsRule();

        ruleSet.setRules({allowHttp});
        return ruleSet;
    }

    Rule getAllowHttpAndHttpsRule() const
    {
        Rule allowHttp;
        allowHttp.setDirection(Rule::OUTGOING);
        allowHttp.setProtocol("tcp");
        allowHttp.setDestinationPorts({80, 443});
        allowHttp.setAction(Rule::ALLOW);

        return allowHttp;
    }

};

QTEST_MAIN(TestIptables)
#include "TestIptables.moc"