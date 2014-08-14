#include "qxvalidator.h"
#include <QDebug>

QxLongValidator::QxLongValidator(QObject *parent) :
    QIntValidator(parent)
{
    b = Q_INT64_C(-9223372036854775808);
    t = Q_UINT64_C(18446744073709551615);
}

QxLongValidator::QxLongValidator(QVariant bottom, QVariant top, QObject *parent) :
    QIntValidator(parent)

{
//    TODO: Assert needed?
    if(checkType(bottom))
        b = bottom;
    if(checkType(top))
        t = top;
}

void QxLongValidator::setBottom(QVariant bottom)
{
    setRange(bottom, top());
}

void QxLongValidator::setTop(QVariant top)
{
    setRange(bottom(), top);
}

void QxLongValidator::setRange(QVariant bottom, QVariant top)
{
    bool rangeChanged = false;
    if (checkType(bottom) && (b != bottom)) {
        b = bottom;
        rangeChanged = true;
        emit bottomChanged(b);
    }

    if (checkType(bottom) && (t != top)) {
        t = top;
        rangeChanged = true;
        emit topChanged(t);
    }

    if (rangeChanged)
        emit changed();
}

QValidator::State QxLongValidator::validate(QString & input, int&) const
{
//    QByteArray buff;
//    if (!locale().d->validateChars(input, QLocalePrivate::IntegerMode, &buff)) {
//        return Invalid;
//    }

    QByteArray buff = QByteArray().insert(0, input);

    if (buff.isEmpty())
        return Intermediate;

    if (b >= 0 && buff.startsWith('-'))
        return Invalid;

    if (t < 0 && buff.startsWith('+'))
        return Invalid;

    if (buff.size() == 1 && (buff.at(0) == '+' || buff.at(0) == '-'))
        return Intermediate;

//    TODO: is locale necessary for this?
//    bool ok, overflow;
//    qlonglong entered = QLocalePrivate::bytearrayToLongLong(buff.constData(), 10, &ok, &overflow);
//    if (overflow || !ok)
//        return Invalid;

    bool ok;
    QVariant entered = QVariant(buff.toLongLong(&ok));
    if(!ok) {
        if(buff.startsWith('-')) {
            return Invalid;
        } else {
//            TODO: may be superflous... toLongLong seem to convert all???
            entered = QVariant(buff.toULongLong(&ok));
            if(!ok)
                return Invalid;
        }
    }

    if ((compare(entered, b) != -1) && (compare(entered, t) != 1)) {
//        locale().toInt(input, &ok);
//        return ok ? Acceptable : Intermediate;
        return Acceptable ;
    }

    if (compare(entered, b) == -1) {
        return Invalid;
    }

    if (compare(entered, t) == 1) {
        return Invalid;
    }
/*
    TODO: Only needed if '-' entered last is allowed (in place of above)
    if (entered >= 0) {
        // the -entered < b condition is necessary to allow people to type
        // the minus last (e.g. for right-to-left languages)
        return (entered > t && -entered < b) ? Invalid : Intermediate;
    } else {
        return (entered < b) ? Invalid : Intermediate;
    }
*/
    qDebug() << "QxLongValidator::validate: should never get here";
}

bool QxLongValidator::checkType(QVariant value)
{
//    TODO: Why not allow shorter ints converted into longs?
    switch(value.type()) {
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        return true;
    default:
        return false;
    }
}

