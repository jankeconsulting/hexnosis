/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "textpanelitemdelegate.h"
#include <QDebug>

TextPanelItemDelegate::TextPanelItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QString TextPanelItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    return toText(value);
}

QWidget *TextPanelItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setMaxLength(1);

    return editor;
}

void TextPanelItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineeditor = static_cast<QLineEdit *>(editor);
    lineeditor->setText(toText(index.model()->data(index, Qt::EditRole)));
}

void TextPanelItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineeditor = static_cast<QLineEdit *>(editor);
    model->setData(index, lineeditor->text().toLatin1(), Qt::EditRole);
}

void TextPanelItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

QString TextPanelItemDelegate::toText(QVariant value) const
{
    return qPrintable(value.toChar());
}
