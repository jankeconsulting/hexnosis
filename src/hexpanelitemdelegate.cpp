/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hexpanelitemdelegate.h"
#include <QDebug>

// TODO(txwikinger): Investigate merging of some functionality
//                   with TextpanelItemDelegate for DRY principle

/**
 * @brief constructs the object
 * @param parent of the object
 */
HexPanelItemDelegate::HexPanelItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

/**
 * @brief provides the representation for the text to be displayed
 * @param value of the item
 * @param locale -- not used
 * @return the text in the respresentation to be displayed
 *
 * This method is re-implemented
 */
QString HexPanelItemDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    return toHex(value);
}

/**
 * @brief creates the editor to bee used for the item
 * @param parent
 * @param option -- not used
 * @param index -- not used
 * @return the editor object created
 *
 * This method is re-implemented
 */
QWidget *HexPanelItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
    editor->setMaxLength(2);
    editor->setInputMask("HH");

    return editor;
}

/**
 * @brief sets the data from the model into the editor field
 * @param editor that is used
 * @param index of the item
 *
 * This method is re-implemented
 */
void HexPanelItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineeditor = qobject_cast<QLineEdit *>(editor);
    lineeditor->setText(toHex(index.model()->data(index, Qt::EditRole)));
}

/**
 * @brief sets the data from the editor into the model
 * @param editor that is used
 * @param model that is used
 * @param index of the item
 *
 * This method is re-implemented
 */
void HexPanelItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                        const QModelIndex &index) const
{
    QLineEdit *lineeditor = qobject_cast<QLineEdit *>(editor);
    model->setData(index, QByteArray::fromHex(lineeditor->text().toLatin1()), Qt::EditRole);
}

/**
 * @brief updates the size and location of the editor
 * @param editor that is used
 * @param option to determine the size and location
 * @param index -- not used
 *
 * This method is re-implemented
 */
void HexPanelItemDelegate::updateEditorGeometry(QWidget *editor,
                                                const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}

/**
 * @brief is a help function that returns the hex representation of a value
 * @param value that is given
 * @return hex representation of the value given
 */
QString HexPanelItemDelegate::toHex(QVariant value) const
{
    return QString("%1").arg(QByteArray(1, value.toInt()).toHex().toUpper().data());
}
