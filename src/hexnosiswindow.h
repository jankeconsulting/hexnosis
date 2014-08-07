/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef HEXNOSISWINDOW_H
#define HEXNOSISWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QtGui>
#include "./hextabwidget.h"

namespace Ui {
class HexnosisWindow;
}

class HexnosisWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit HexnosisWindow(QWidget *parent = 0);
    ~HexnosisWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClose_triggered();
    void on_actionRow_Shading_toggled(bool state);
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void closeTab(int index);
    void currentTabChanged(int index);
    bool rowShadingState();

private:
    Ui::HexnosisWindow *ui;
    HexTabWidget *tab;

    void enableActions(bool enable = false);
    void findWorkingTheme();
    void setIconFallbacks();
};

#endif // HEXNOSISWINDOW_H
