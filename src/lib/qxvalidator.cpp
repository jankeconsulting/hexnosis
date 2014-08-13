#include "qxvalidator.h"
#include <QDebug>

QxLongValidator::QxLongValidator(QObject *parent) :
    QIntValidator(parent)
{
//    TODO: set correct type (unsigned or signed)
    b = Q_INT64_C(-9223372036854775808);
    t = Q_UINT64_C(18446744073309551616);
//    b = Q_INT64_C(-2147483648);
//    t = Q_INT64_C(4294967295);
}

QxLongValidator::QxLongValidator(QVariant bottom, QVariant top, QObject *parent) :
    QIntValidator(parent)

{
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

    qDebug() << "QxLongValidator::validate: input" << input;
    if (buff.isEmpty())
        return Intermediate;

    qDebug() << "QxLongValidator::validate: buffer is not empty";

    if (b >= 0 && buff.startsWith('-'))
        return Invalid;

    qDebug() << "QxLongValidator::validate: not b >= 0 && buff.startsWith('-')";

    if (t < 0 && buff.startsWith('+'))
        return Invalid;

    qDebug() << "QxLongValidator::validate: not t < 0 && buff.startsWith('+')";

    if (buff.size() == 1 && (buff.at(0) == '+' || buff.at(0) == '-'))
        return Intermediate;

    qDebug() << "QxLongValidator::validate: not buff.size() == 1 && (buff.at(0) == '+' || buff.at(0) == '-')";

//    TODO: is locale necessary for this?
//    bool ok, overflow;
//    qlonglong entered = QLocalePrivate::bytearrayToLongLong(buff.constData(), 10, &ok, &overflow);
//    if (overflow || !ok)
//        return Invalid;

    bool ok;
    QVariant entered = QVariant(buff.toLongLong(&ok));
    if(!ok) {
        if(buff.startsWith('-')) {
            qDebug() << "QxLongValidator::validate: toLongLong not ok and starts with '-'";
            return Invalid;
        } else {
            entered = QVariant(buff.toULongLong(&ok));
            qDebug() << "QxLongValidator::validate: toLongLong not ok and entered = " << entered;
            if(!ok)
                return Invalid;
        }
    }

    qDebug() << "QxLongValidator::validate: entered is valid so far : " << entered;
    qDebug() << "QxLongValidator::validate: b = " << b;
    qDebug() << "QxLongValidator::validate: t = " << t;
    qDebug() << "QxLongValidator::validate: entered >= b : " << (entered >=b);
    qDebug() << "QxLongValidator::validate: entered <= t : " << (entered <=t);

    if (entered >= b && entered <= t) {
//        locale().toInt(input, &ok);
//        return ok ? Acceptable : Intermediate;
        return Acceptable ;
    }

    qDebug() << "QxLongValidator::validate: not within boundaries";

    if (entered < b) {
        return Invalid;
    }

    if (entered > t) {
        return Invalid;
    }

    qDebug() << "QxLongValidator::validate: too big or too small";

    if (entered >= 0) {
        // the -entered < b condition is necessary to allow people to type
        // the minus last (e.g. for right-to-left languages)
        // return (entered > t && -entered < b) ? Invalid : Intermediate;
        return (entered > t && entered < b) ? Invalid : Intermediate;
    } else {
        return (entered < b) ? Invalid : Intermediate;
    }
}

bool QxLongValidator::checkType(QVariant value)
{
    return true;
    //    TODO: Assert needed? Why not allow shorter ints converted into longs?
    switch(value.type()) {
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        return true;
    default:
        return false;
    }
}

