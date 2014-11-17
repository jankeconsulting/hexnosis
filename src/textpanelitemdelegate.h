/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_TEXTPANELITEMDELEGATE_H_
#define SRC_TEXTPANELITEMDELEGATE_H_

#include <QStyledItemDelegate>
#include <QString>
#include <QVariant>
#include <QLineEdit>

/**
 * @brief The TextPanelItemDelegate class
 */
class TextPanelItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
 public:
    explicit TextPanelItemDelegate(QObject *parent = 0);
    QString displayText(const QVariant & value, const QLocale & locale ) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

 signals:

 public slots:
    QString toText(QVariant value) const;
};

#endif  // SRC_TEXTPANELITEMDELEGATE_H_
