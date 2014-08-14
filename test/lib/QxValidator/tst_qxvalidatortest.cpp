#include "../../../src/lib/qxvalidator.h"
#include <QtTest>

class QxValidatorTest : public QObject
{
    Q_OBJECT

public:
    QxValidatorTest();

private Q_SLOTS:
    void testCompare();
    void testCompare_data();
};

QxValidatorTest::QxValidatorTest()
{
}

void QxValidatorTest::testCompare()
{
    QFETCH(QVariant, a);
    QFETCH(QVariant, b);
    QFETCH(int, result);
    qDebug() << a << b << result;
    QCOMPARE(QxUtil::compare(a,b), result);
}

void QxValidatorTest::testCompare_data()
{
    QTest::addColumn<QVariant>("a");
    QTest::addColumn<QVariant>("b");
    QTest::addColumn<int>("result");

    qlonglong a;
    qulonglong u_a;
    qlonglong b;
    qulonglong u_b;

    a = 1; b = 2; QTest::newRow("signed 1, signed 2") << QVariant(a) << QVariant(b) << -1;
    a = 1; u_b = 2; QTest::newRow("signed 1, unsigned 2") << QVariant(a) << QVariant(u_b) << -1;
    u_a = 2; b = 1; QTest::newRow("unsigned 2, signed 1") << QVariant(u_a) << QVariant(b) << 1;
    u_a = 2; u_b = 1; QTest::newRow("unsigned 2, unsigned 1") << QVariant(u_a) << QVariant(u_b) << 1;
    a = 2; b = 2; QTest::newRow("signed 2, signed 2") << QVariant(a) << QVariant(b) << 0;
    a = 2; u_b = 2; QTest::newRow("signed 2, unsigned 2") << QVariant(a) << QVariant(u_b) << 0;
    u_a = 2; b = 2; QTest::newRow("unsigned 2, signed 2") << QVariant(u_a) << QVariant(b) << 0;
    u_a = 2; u_b = 2; QTest::newRow("unsigned 2, unsigned 2") << QVariant(u_a) << QVariant(u_b) << 0;
    a = 2; u_b = Q_UINT64_C(18446744073709551615); QTest::newRow("signed 2, unsigned 18446744073709551615") << QVariant(a) << QVariant(u_b) << -1;
    u_a = Q_UINT64_C(18446744073709551615); b = 2; QTest::newRow("unsigned 18446744073709551615, signed 2") << QVariant(u_a) << QVariant(b) << 1;
    a = -2; u_b = Q_UINT64_C(18446744073709551615); QTest::newRow("signed -2, unsigned 18446744073709551615") << QVariant(a) << QVariant(u_b) << -1;
    u_a = Q_UINT64_C(18446744073709551615); b = -2; QTest::newRow("unsigned 18446744073709551615, signed -2") << QVariant(u_a) << QVariant(b) << 1;
    a = Q_INT64_C(-9223372036854775808); b = -1; QTest::newRow("signed -9223372036854775808, signed -1") << QVariant(a) << QVariant(b) << -1;
    a = Q_INT64_C(-9223372036854775808); u_b = 1; QTest::newRow("signed -9223372036854775808, unsigned 1") << QVariant(a) << QVariant(u_b) << -1;
    a = -1; b = Q_INT64_C(-9223372036854775808); QTest::newRow("signed -1, signed -9223372036854775808") << QVariant(a) << QVariant(b) << 1;
    u_a = -1; b = Q_INT64_C(-9223372036854775808); QTest::newRow("unsigned 1, signed -9223372036854775808") << QVariant(u_a) << QVariant(b) << 1;
    a = Q_INT64_C(-9223372036854775808); u_b = Q_UINT64_C(18446744073709551615); QTest::newRow("signed -9223372036854775808, unsigned 18446744073709551615") << QVariant(a) << QVariant(u_b) << -1;
    u_a = Q_UINT64_C(18446744073709551615); b = Q_INT64_C(-9223372036854775808); QTest::newRow("unsigned 18446744073709551615, signed -9223372036854775808") << QVariant(u_a) << QVariant(b) << 1;
    u_a = Q_UINT64_C(18446744073709551615); u_b = Q_UINT64_C(18446744073709551615); QTest::newRow("unsigned 18446744073709551615, unsigned 18446744073709551615") << QVariant(u_a) << QVariant(u_b) << 0;
    u_a = Q_UINT64_C(18446744073709551614); u_b = Q_UINT64_C(18446744073709551615); QTest::newRow("unsigned 18446744073709551614, unsigned 18446744073709551615") << QVariant(u_a) << QVariant(u_b) << -1;
    u_a = Q_UINT64_C(18446744073709551615); u_b = Q_UINT64_C(18446744073709551614); QTest::newRow("unsigned 18446744073709551615, unsigned 18446744073709551614") << QVariant(u_a) << QVariant(u_b) << 1;

}

QTEST_APPLESS_MAIN(QxValidatorTest)

#include "tst_qxvalidatortest.moc"
