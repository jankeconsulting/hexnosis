/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hextabwidget.h"
#include <QDebug>

HexTabWidget::HexTabWidget(QWidget *parent) :
    QTabWidget(parent)
{    
}

HexTabWidget::~HexTabWidget()
{
    for (int i = 0; i < count(); i++) {
        delete widget(i);
    }
}

void HexTabWidget::addTabPage(TabPanel *page, QString tabname, QString tabhint)
{
    addTab(page, tabname);
    setTabToolTip(indexOf(page), tabhint);
    setCurrentWidget(page);

}

void HexTabWidget::createFile()
{
    bool ok;
    int len = QInputDialog::getInt(this, QString(tr("Enter File Size")), QString(tr("Please enter file length")), 1, 1, 2147483647, 1, &ok);
    if(ok) {
        TabPanel *page = new TabPanel(this, 0);
        page->createFile(len, 0);
        addTabPage(page);
    }
}

void HexTabWidget::openFile()
{
    if(chooseFile()) {
        TabPanel *page = new TabPanel(this, file);
        addTabPage(page, fileName(), filename);
    }
}

void HexTabWidget::saveFile()
{
    qobject_cast<TabPanel *>(currentWidget())->saveFile(fileName(true));
}

void HexTabWidget::saveFileAs()
{
    if(chooseFile())
        qobject_cast<TabPanel *>(currentWidget())->saveFile(fileName(true));
}

void HexTabWidget::setAlternatingRowColors(bool state)
{
    for (int i = 0; i < count(); i++) {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setAlternatingRowColors(state);
    }
}

void HexTabWidget::setHexPanelVisibility(bool state)
{
    for (int i = 0; i < count(); i++) {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setHexPanelVisibility(state);
    }
}

void HexTabWidget::setTextPanelVisibility(bool state)
{
    for (int i = 0; i < count(); i++) {
        QWidget* w = widget(i);
        qobject_cast<TabPanel *>(w)->setTextPanelVisibility(state);
    }
}

bool HexTabWidget::chooseFile()
{
//    TODO: possibly refactor file parts to model (or own file class) - keep UI part in this class
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), QString());
    if(filename.isNull())
        return false;
    if (!filename.isEmpty()) {
        file = new QFile(filename);
        if (!file->open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return false;
        }
    }
    return true;
}

QString HexTabWidget::fileName(bool with_path)
{
    if(with_path) {
        return filename;
    } else {
        return QFileInfo(filename).fileName();
    }
}
