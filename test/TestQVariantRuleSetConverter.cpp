#include <QTest>
#include <QObject>

#include "../entities/RuleSet.h"
#include "../gateways/QVariantRuleSetConverter.h"
#include <QDebug>
class TestQVariantRuleSetConverter : public QObject {
Q_OBJECT
private slots:
    void RuleToVariant()
    {
        Rule r = getAllowSshRule();
        QVariantMap expected = getAllowSshRuleVariant();

        QVariantMap result;
        result = QVariantRuleSetConverter::toVariant(r);

        QCOMPARE(result, expected);
    }

protected:
    Rule getAllowSshRule() const
    {
        Rule r;
        r.setDirection(Rule::OUTGOING);
        r.setProtocol("tcp");
        r.setAction(Rule::ALLOW);
        r.setDestinationAddr("10.0.0.1");
        r.setDestinationPorts({80});
        return r;
    }
    QVariantMap getAllowSshRuleVariant() const
    {
        QVariantMap expected;
        expected[QVariantRuleSetConverter::KEY_DIRECTION] = "OUTGOING";
        expected[QVariantRuleSetConverter::KEY_PROTOCOL] = "tcp";
        expected[QVariantRuleSetConverter::KEY_ACTION] = "ALLOW";
        expected[QVariantRuleSetConverter::KEY_DESTINATION_ADDR] = "10.0.0.1";
        expected[QVariantRuleSetConverter::KEY_DESTINATION_PORTS] = QVariantList({80});
        return expected;
    }
};

QTEST_MAIN(TestQVariantRuleSetConverter)
#include "TestQVariantRuleSetConverter.moc"