#ifndef QXVALIDATOR_H
#define QXVALIDATOR_H

#include <QIntValidator>
#include <QtCore/qlocale.h>

class QxLongValidator : public QIntValidator
{
    Q_OBJECT
    Q_PROPERTY(qint64 bottom READ bottom WRITE setBottom NOTIFY bottomChanged)
    Q_PROPERTY(quint64 top READ top WRITE setTop NOTIFY topChanged)

public:
    explicit QxLongValidator(QObject *parent = 0);
    QxLongValidator(qint64 bottom, quint64 top, QObject *parent = 0);

    void setBottom(qint64 bottom);
    void setTop(quint64 top);
    virtual void setRange(qint64 bottom, quint64 top);

    qint64 bottom() const { return b; }
    quint64 top() const { return t; }

    QValidator::State validate(QString &input, int &) const;

signals:
    void bottomChanged(qint64 bottom);
    void topChanged(quint64 top);

public slots:

private:
    Q_DISABLE_COPY(QxLongValidator)

    qint64 b;
    quint64 t;
};

#endif // QXVALIDATOR_H
