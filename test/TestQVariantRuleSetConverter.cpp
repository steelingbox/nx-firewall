#include <QTest>
#include <QObject>

#include "../entities/RuleSet.h"
#include "../entities/QVariantRuleSetConverter.h"
#include <QDebug>
class TestQVariantRuleSetConverter : public QObject {
Q_OBJECT
private slots:
    void ruleToVariant()
    {
        Rule r;
        QVariantMap expected;
        QVariantMap result;

        r = getAllowOutgoingSshRule();
        expected = getAllowSshRuleVariant();
        result = QVariantRuleSetConverter::toVariant(r);

        QCOMPARE(result, expected);

        r = getAllowIncomingHttpRule();
        expected = getAllowIncomingHttpVariant();
        result = QVariantRuleSetConverter::toVariant(r);

        QCOMPARE(result, expected);
    }

    void variantToRule()
    {
        Rule expected;
        QVariantMap source;
        Rule result;
        try {
            source = getAllowSshRuleVariant();
            result = QVariantRuleSetConverter::toRule(source);
            expected = getAllowOutgoingSshRule();
            QCOMPARE(result, expected);

            source = getAllowIncomingHttpVariant();
            result = QVariantRuleSetConverter::toRule(source);
            expected = getAllowIncomingHttpRule();
            QCOMPARE(result, expected);
        }
        catch (QVariantRuleSetConverter::ConversionException e) {
            QFAIL("Unexpected exception");
        }
    }

    void ruleSetToVariant()
    {
        auto ruleSet = getRuleSet();
        auto expected = getRuleSetVariant();
        auto result = QVariantRuleSetConverter::toVariant(ruleSet);
        QCOMPARE(expected, result);
    }

    void variantToRuleSet()
    {

        auto source = getRuleSetVariant();
        auto expected = getRuleSet();
        auto result = QVariantRuleSetConverter::toRuleSet(source);
        QCOMPARE(expected, result);
    }

protected:
    QVariantMap getRuleSetVariant() const
    {
        QVariantMap map;
        map["DEFAULT_INCOMING_POLICY"] = "DENY";
        map["DEFAULT_OUTGOING_POLICY"] = "DENY";
        QVariantList list = {getAllowIncomingHttpVariant(), getAllowSshRuleVariant()};
        map["RULES"] = list;
        return map;
    }
    RuleSet getRuleSet() const
    {
        RuleSet ruleSet;
        ruleSet.setDefaultOutgoingPolicy(Rule::DENY);
        ruleSet.setDefaultIncomingPolicy(Rule::DENY);

        Rule http = getAllowIncomingHttpRule();
        Rule ssh = getAllowOutgoingSshRule();

        ruleSet.setRules({http, ssh});
        return ruleSet;
    }
    Rule getAllowOutgoingSshRule() const
    {
        Rule r;
        r.setDirection(Rule::OUTGOING);
        r.setProtocol("tcp");
        r.setAction(Rule::ALLOW);
        r.setDestinationAddr("10.0.0.1");
        r.setDestinationPorts({22});
        return r;
    }

    Rule getAllowIncomingHttpRule() const
    {
        Rule r;
        r.setDirection(Rule::INCOMING);
        r.setProtocol("tcp");
        r.setAction(Rule::ALLOW);
        r.setSourceAddr("10.0.0.0/24");
        r.setSourcePorts({80});
        return r;
    }

    QVariantMap getAllowSshRuleVariant() const
    {
        QVariantMap expected;
        expected[QVariantRuleSetConverter::KEY_DIRECTION] = "OUTGOING";
        expected[QVariantRuleSetConverter::KEY_PROTOCOL] = "tcp";
        expected[QVariantRuleSetConverter::KEY_ACTION] = "ALLOW";
        expected[QVariantRuleSetConverter::KEY_DESTINATION_ADDR] = "10.0.0.1";
        expected[QVariantRuleSetConverter::KEY_DESTINATION_PORTS] = QVariantList({22});
        return expected;
    }

    QVariantMap getAllowIncomingHttpVariant() const
    {
        QVariantMap expected;
        expected[QVariantRuleSetConverter::KEY_DIRECTION] = "INCOMING";
        expected[QVariantRuleSetConverter::KEY_PROTOCOL] = "tcp";
        expected[QVariantRuleSetConverter::KEY_ACTION] = "ALLOW";
        expected[QVariantRuleSetConverter::KEY_SOURCE_ADDR] = "10.0.0.0/24";
        expected[QVariantRuleSetConverter::KEY_SOURCE_PORTS] = QVariantList({80});
        return expected;
    }
};

QTEST_MAIN(TestQVariantRuleSetConverter)
#include "TestQVariantRuleSetConverter.moc"