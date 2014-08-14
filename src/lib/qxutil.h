#ifndef QXUTIL_H
#define QXUTIL_H

#include <QVariant>

class QxUtil
{
public:
    QxUtil();

    static int compare(QVariant a, QVariant b);
    static bool isUnsignedType(QVariant value);

};

#endif // QXUTIL_H
