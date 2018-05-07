#include <QTest>
#include <QObject>

#include "../entities/Rule.h"
#include "../entities/Service.h"

class TestEntities : public QObject {
Q_OBJECT
private slots:
    void creation()
    {
        Rule r;
        RuleSet rs;
        Service s;
    }
};

QTEST_MAIN(TestEntities)
#include "TestEntities.moc"