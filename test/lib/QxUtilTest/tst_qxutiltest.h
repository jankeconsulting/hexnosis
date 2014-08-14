/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef QXUTILTEST_H
#define QXUTILTEST_H

#include "../../../src/lib/qxutil.h"

class QxUtilTest : public QObject
{
    Q_OBJECT

public:
    QxUtilTest();

private Q_SLOTS:
    void testCompare();
    void testCompare_data();
    void testIsUnsignedType();
};

#endif // QXUTILTEST_H
