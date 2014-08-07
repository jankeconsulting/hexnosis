/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexpanelitemdelegate.h"
#include <QDebug>

HexPanelItemDelegate::HexPanelItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QString HexPanelItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    return toHex(value);
}

QWidget *HexPanelItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setMaxLength(2);
    editor->setInputMask("HH");

    return editor;
}

void HexPanelItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineeditor = qobject_cast<QLineEdit *>(editor);
    lineeditor->setText(toHex(index.model()->data(index, Qt::EditRole)));
}

void HexPanelItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineeditor = qobject_cast<QLineEdit *>(editor);
    model->setData(index, QByteArray::fromHex(lineeditor->text().toLatin1()), Qt::EditRole);
}

void HexPanelItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

QString HexPanelItemDelegate::toHex(QVariant value) const
{
    return QString("%1").arg(QByteArray(1, value.toInt()).toHex().toUpper().data());
}
