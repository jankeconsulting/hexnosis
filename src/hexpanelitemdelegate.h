/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_HEXPANELITEMDELEGATE_H_
#define SRC_HEXPANELITEMDELEGATE_H_

#include <QStyledItemDelegate>
#include <QString>
#include <QVariant>
#include <QLineEdit>

/**
 * @brief The HexPanelItemDelegate class
 */
class HexPanelItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
 public:
    HexPanelItemDelegate(QObject* parent = 0);
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

 private:
    QString toHex(QVariant value) const;
};

#endif  // SRC_HEXPANELITEMDELEGATE_H_
