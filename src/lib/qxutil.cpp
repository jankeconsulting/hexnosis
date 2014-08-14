#include "qxutil.h"
#include <QDebug>

QxUtil::QxUtil()
{
}

bool QxUtil::isUnsignedType(QVariant value)
{
    if(value.type() == QVariant::ULongLong)
        return true;
    return false;
}

/*
 * compares two value even if they are signed and unsigned
 * returns -1 if a < b
 * returns 0 if a == b
 * returns 1 if a > b
 */
int QxUtil::compare(QVariant a, QVariant b)
{
    if(isUnsignedType(a) == isUnsignedType(b)){
        if (a < b) return -1;
        if (a == b) return 0;
        return 1;
    } else {
        if(isUnsignedType(a)) {
            if(b < 0) return 1;
            if(a.toULongLong() & 0x80000000) return 1;
            if(a < b) return -1;
            if(a == b) return 0;
            return 1;
        } else {
            if(a < 0) return -1;
            if(b.toULongLong() & 0x80000000) return -1;
            if(a < b) return -1;
            if(a == b) return 0;
            qDebug() << "ttt" << a << " " << b;
            return 1;
        }
    }
}

