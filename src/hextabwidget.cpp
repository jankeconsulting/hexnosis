/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hextabwidget.h"
#include <QDebug>

/**
 * @brief constructs the object
 * @param parent of the object
 */
HexTabWidget::HexTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(currentCursorData()));
}

/**
 * @brief destroys the object
 *
 * All the tab widgets inside this panel are deleted before the object
 * is destroyed
 */
HexTabWidget::~HexTabWidget()
{
    for (int i = 0; i < count(); i++)
    {
        delete widget(i);
    }
}

/**
 * @brief adds another tab for a file to the panel
 * @param page - the tab widget
 * @param tabname - name inside the tab
 * @param tabhint - the tooltip for the tab
 */
void HexTabWidget::addTabPage(TabPanel *page, QString tabname, QString tabhint)
{
    addTab(page, tabname);
    setTabToolTip(indexOf(page), tabhint);
    setCurrentWidget(page);
    connect(page->hexPanel()->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(currentCursorData()));
    connect(page->model(), SIGNAL(dataChanged(QModelIndex, QModelIndex)),
            this, SLOT(currentCursorData()));
}

/**
 * @brief creates a new file for the hexeditor
 *
 * A dialog is opened asking for the size of the file. The
 * file is created and added to the tabs.
 */
void HexTabWidget::createFile()
{
    bool ok;
    int len = QInputDialog::getInt(this, QString(tr("Enter File Size")),
                                   QString(tr("Please enter file length")),
                                   1, 1, 2147483647, 1, &ok);
    if (ok)
    {
        TabPanel *page = new TabPanel(this, 0);
        page->createFile(len, 0);
        addTabPage(page);
    }
}

/**
 * @brief opens a file for the hexeditor
 *
 * The new widget is ceated after the file is selected
 * from a file selector dialog and is added to the tabs.
 */
void HexTabWidget::openFile()
{
    if (chooseFile())
    {
        TabPanel *page = new TabPanel(this, file);
        addTabPage(page, fileName(), filename);
    }
}

/**
 * @brief saves the currently used file
 */
void HexTabWidget::saveFile()
{
    qobject_cast<TabPanel *>(currentWidget())->saveFile(fileName(true));
}

/**
 * @brief saves the currently used file as a particular name and path
 */
void HexTabWidget::saveFileAs()
{
    if (chooseFile())
    {
        qobject_cast<TabPanel *>(currentWidget())->saveFile(fileName(true));
    }
}

/**
 * @brief sets the flag for alternating row colors for all models in the tabs
 * @param state - true if alternating row colors are used, otherwise false
 */
void HexTabWidget::setAlternatingRowColors(bool state)
{
    for (int i = 0; i < count(); i++)
    {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setAlternatingRowColors(state);
    }
}

/**
 * @brief sets the visibility of the hexpanels in all the tabs
 * @param state - true if hexpanels are visible, otherwise false
 */
void HexTabWidget::setHexPanelVisibility(bool state)
{
    for (int i = 0; i < count(); i++)
    {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setHexPanelVisibility(state);
    }
}

/**
 * @brief sets the visibility of the textpanels in all the tabs
 * @param state - true if textpanels are visible, otherwise false
 */
void HexTabWidget::setTextPanelVisibility(bool state)
{
    for (int i = 0; i < count(); i++)
    {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setTextPanelVisibility(state);
    }
}

/**
 * @brief sets provided data in the model of the current tab
 * @param data
 */
void HexTabWidget::setTextInCurrentTab(QByteArray data)
{
    if (count() > 0)
    {
        TabPanel *tabwidget = qobject_cast<TabPanel *>(currentWidget());
        tabwidget->model()->setData(tabwidget->hexPanel()->currentIndex(), data, Qt::EditRole);
    }
}

/**
 * @brief slot that is called when data under the cursor is changed
 */
void HexTabWidget::currentCursorData()
{
    if (count() > 0)
    {
        TabPanel *tabwidget = qobject_cast<TabPanel *>(currentWidget());
        QByteArray bytes = tabwidget->model()->data(8, tabwidget->hexPanel()->currentIndex(),
                                                    Qt::DisplayRole);
        emit cursorDataChanged(bytes);
    }
}

/**
 * @brief opens file dialog for selecting a file and opens it
 * @return true if successful, otherwise false
 */
bool HexTabWidget::chooseFile()
{
//    TODO: possibly refactor file parts to model (or own file class) - keep UI part in this class
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString());
    if (filename.isNull())
    {
        return false;
    }
    if (not(filename.isEmpty()))
    {
        file = new QFile(filename);
        if (not(file->open(QIODevice::ReadOnly)))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return false;
        }
    }
    return true;
}

/**
 * @brief returns filename
 * @param with_path - indicated if only filename or full path is requested
 * @return
 */
QString HexTabWidget::fileName(bool with_path)
{
    if (with_path)
    {
        return filename;
    } else
    {
        return QFileInfo(filename).fileName();
    }
}
