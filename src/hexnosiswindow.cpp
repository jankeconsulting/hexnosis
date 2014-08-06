/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexnosiswindow.h"
#include "ui_hexnosiswindow.h"
#include <QDebug>

HexnosisWindow::HexnosisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HexnosisWindow)
{
    findWorkingTheme();
    ui->setupUi(this);
    setWindowTitle(QString(tr("Hexnosis - Hex Editor")));
    setIconFallbacks();
    updateHexPanelActionStates(false);
    tab = new HexTabWidget(ui->centralWidget);
    tab->setTabsClosable(true);
    this->setCentralWidget(tab);
    connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
}

HexnosisWindow::~HexnosisWindow()
{
    delete tab;
    delete ui;
}

void HexnosisWindow::on_actionRow_Shading_toggled(bool state)
{
    tab->setAlternatingRowColors(state);
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
        updateHexPanelActionStates(true);
    } else {
        updateHexPanelActionStates(false);
    }
}

void HexnosisWindow::updateHexPanelActionStates(bool enable)
{
//    TODO: save needs to be disabled when tab has no filename
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

void HexnosisWindow::on_actionNew_triggered()
{
    tab->createFile();
    on_actionRow_Shading_toggled(rowShadingState());
}

void HexnosisWindow::on_actionOpen_triggered()
{
    tab->openFile();
    on_actionRow_Shading_toggled(rowShadingState());
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

bool HexnosisWindow::rowShadingState() {
    return ui->actionRow_Shading->isChecked();
}
