#ifndef QXVALIDATOR_H
#define QXVALIDATOR_H

#include <QIntValidator>
#include <QtCore/qlocale.h>
#include "qxutil.h"


class QxLongValidator : public QIntValidator, QxUtil
{
    Q_OBJECT
    Q_PROPERTY(QVariant bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(QVariant top READ top WRITE setTop NOTIFY topChanged)

public:
    explicit QxLongValidator(QObject *parent = 0);
    QxLongValidator(QVariant bottom, QVariant top, QObject *parent = 0);

    void setBottom(QVariant bottom);
    void setTop(QVariant top);
    virtual void setRange(QVariant bottom, QVariant top);

    QVariant bottom() const { return b; }
    QVariant top() const { return t; }

    QValidator::State validate(QString &input, int &) const;

signals:
    void bottomChanged(QVariant bottom);
    void topChanged(QVariant top);

public slots:

private:
    Q_DISABLE_COPY(QxLongValidator)
    bool checkType(QVariant value);

    QVariant b;
    QVariant t;
};

#endif // QXVALIDATOR_H
