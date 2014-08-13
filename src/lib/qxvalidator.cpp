#include "qxvalidator.h"

QxLongValidator::QxLongValidator(QObject *parent) :
    QIntValidator(parent)
{
    b = 0x00000080;
    t = 0xFFFFFFFF;
}

QxLongValidator::QxLongValidator(qint64 bottom, quint64 top, QObject *parent)
{
    b = bottom;
    t = top;
}

void QxLongValidator::setBottom(qint64 bottom)
{
    setRange(bottom, top());
}

void QxLongValidator::setTop(quint64 top)
{
    setRange(bottom(), top);
}

void QxLongValidator::setRange(qint64 bottom, quint64 top)
{
    bool rangeChanged = false;
    if (b != bottom) {
        b = bottom;
        rangeChanged = true;
        emit bottomChanged(b);
    }

    if (t != top) {
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

//    if (t < 0 && buff.startsWith('+'))
//        return Invalid;

    if (buff.size() == 1 && (buff.at(0) == '+' || buff.at(0) == '-'))
        return Intermediate;

      bool ok, overflow;
//    qlonglong entered = QLocalePrivate::bytearrayToLongLong(buff.constData(), 10, &ok, &overflow);
//    if (overflow || !ok)
//        return Invalid;

    qlonglong entered = buff.toLongLong(&ok);
    qulonglong uentered;
    if(!ok) {
        if(buff.startsWith('-')) {
            return Invalid;
        } else {
            uentered = buff.toULongLong(&ok);
            if(!ok)
                return Invalid;
        }

    }

    if (entered >= b && uentered <= t) {
        locale().toInt(input, &ok);
        return ok ? Acceptable : Intermediate;
    }

    if (entered >= 0) {
        // the -entered < b condition is necessary to allow people to type
        // the minus last (e.g. for right-to-left languages)
        return (uentered > t && -entered < b) ? Invalid : Intermediate;
    } else {
        return (entered < b) ? Invalid : Intermediate;
    }
}

