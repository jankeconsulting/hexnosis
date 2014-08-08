/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexnosiswindow.h"
#include "ui_hexnosiswindow.h"
#include <QDebug>

QLabel *HexnosisWindow::cursorPosition = 0;
QLabel *HexnosisWindow::cursorValue = 0;

HexnosisWindow::HexnosisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HexnosisWindow)
{
    findWorkingTheme();
    ui->setupUi(this);
    setWindowTitle(QString(tr("Hexnosis - Hex Editor")));
    setIconFallbacks();
    enableActions(false);
    tab = new HexTabWidget(ui->centralWidget);
    tab->setTabsClosable(true);
    this->setCentralWidget(tab);
    connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
    createStatusBar();
}

HexnosisWindow::~HexnosisWindow()
{
    delete tab;
    delete ui;
    delete cursorPosition;
    delete cursorValue;
}

void HexnosisWindow::closeTab(int index)
{
    delete tab->widget(index);
//    TODO: Investigate
//    oddly, the tab disappears by itself when widget is deleted so
//    following line would remove another tab.
//    tab->removeTab(index);
}

void HexnosisWindow::currentTabChanged(int index)
{
    Q_UNUSED(index);
    if(tab->count() > 0) {
        enableActions(true);
        if(!qobject_cast<TabPanel *>(tab->currentWidget())->model()->hasFile()) {
            ui->actionSave->setEnabled(false);
        }
        QModelIndex index = qobject_cast<TabPanel *>(tab->currentWidget())->hexPanel()->selectionModel()->currentIndex();
        qobject_cast<TabPanel *>(tab->currentWidget())->model()->updateCursorInfo(index, index);
    } else {
        enableActions(false);
        clearCursorInfo();
    }
}

void HexnosisWindow::enableActions(bool enable)
{
    ui->actionClose->setEnabled(enable);
    ui->actionSave->setEnabled(enable);
    ui->actionSaveAs->setEnabled(enable);
}

void HexnosisWindow::findWorkingTheme()
{
//    TODO: Needs rework for DRY
    if(QIcon::hasThemeIcon("application-exit")
            && QIcon::hasThemeIcon("document-new")
            && QIcon::hasThemeIcon("document-open")
            && QIcon::hasThemeIcon("document-save")
            && QIcon::hasThemeIcon("document-save-as")
            && QIcon::hasThemeIcon("document-close")
            )
        return;

    QIcon::setThemeName("oxygen");
    if(QIcon::hasThemeIcon("application-exit")
            && QIcon::hasThemeIcon("document-new")
            && QIcon::hasThemeIcon("document-open")
            && QIcon::hasThemeIcon("document-save")
            && QIcon::hasThemeIcon("document-save-as")
            && QIcon::hasThemeIcon("document-close")
            )
        return;
}

void HexnosisWindow::setIconFallbacks()
{
//    TODO: Needs rework for DRY
    if(!QIcon::hasThemeIcon("document-close"))
        ui->actionClose->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
    if(!QIcon::hasThemeIcon("document-open"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    if(!QIcon::hasThemeIcon("document-save"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    if(!QIcon::hasThemeIcon("document-save-as"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    if(!QIcon::hasThemeIcon("document-new"))
        ui->actionNew->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogStart));
}

void HexnosisWindow::updateCursorInfo(int offset, int value)
{
    cursorPosition->setText(tr("Cursor Offset : %1").arg(offset));
    cursorValue->setText(tr("Cursor Value : %1").arg(value));
}

void HexnosisWindow::clearCursorInfo()
{
    if(cursorPosition)
        cursorPosition->clear();
    if(cursorValue)
        cursorValue->clear();
}

void HexnosisWindow::on_actionNew_triggered()
{
    tab->createFile();
    resetToggles();
}

void HexnosisWindow::on_actionOpen_triggered()
{
    tab->openFile();
    resetToggles();
}

void HexnosisWindow::on_actionClose_triggered()
{
    closeTab(tab->currentIndex());
}

void HexnosisWindow::on_actionSave_triggered()
{
    tab->saveFile();
}

void HexnosisWindow::on_actionSaveAs_triggered()
{
    tab->saveFileAs();
}

void HexnosisWindow::on_actionAbout_triggered()
{
//    TODO: Add about widget
}

void HexnosisWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void HexnosisWindow::createStatusBar()
{
    cursorPosition = new QLabel();
    statusBar()->addPermanentWidget(cursorPosition);
    cursorValue = new QLabel();
    statusBar()->addPermanentWidget(cursorValue);
}

bool HexnosisWindow::rowShadingState() {
    return ui->actionRowShading->isChecked();
}

bool HexnosisWindow::hexPanelVisibility()
{
    return ui->actionHexDisplay->isChecked();
}

bool HexnosisWindow::textPanelVisibility()
{
    return ui->actionCharDisplay->isChecked();
}

void HexnosisWindow::resetToggles()
{
    on_actionRowShading_toggled(rowShadingState());
    on_actionHexDisplay_toggled(hexPanelVisibility());
    on_actionCharDisplay_toggled(textPanelVisibility());
}

void HexnosisWindow::on_actionRowShading_toggled(bool state)
{
    tab->setAlternatingRowColors(state);
}

void HexnosisWindow::on_actionHexDisplay_toggled(bool state)
{
    tab->setHexPanelVisibility(state);
}

void HexnosisWindow::on_actionCharDisplay_toggled(bool state)
{
    tab->setTextPanelVisibility(state);
}
