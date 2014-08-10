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
#include <QLabel>
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
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();

    void closeTab(int index);
    void currentTabChanged(int index);
    bool rowShadingState();
    bool hexPanelVisibility();
    bool textPanelVisibility();

    void resetToggles();
    void on_actionRowShading_toggled(bool state);
    void on_actionHexDisplay_toggled(bool state);
    void on_actionCharDisplay_toggled(bool state);

private:
    Ui::HexnosisWindow *ui;
    HexTabWidget *tab;
    static QDockWidget *dataProcessor;
    static QLabel *cursorPosition;
    static QLabel *cursorValue;

    void createStatusBar();
    void enableActions(bool enable = false);
    void findWorkingTheme();
    void setIconFallbacks();

public slots:
    static void updateCursorInfo(int offset, int value);
    static void clearCursorInfo();
    void updateDataProcessor(QByteArray data);
    void clearDataProcessor();
};

#endif // HEXNOSISWINDOW_H

