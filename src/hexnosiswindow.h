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
#include <QTextBrowser>
#include "aboutdialog.h"
#include "hextabwidget.h"
#include "lib/qxvalidator.h"

#ifndef HEXNOSIS_REVISION
#define HEXNOSIS_REVISION "1.0.0"
#endif


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

    void on_binaryEditor_textEdited(const QString &text);
    void on_int8Editor_editingFinished();
    void on_int16Editor_editingFinished();
    void on_int32Editor_editingFinished();
    void on_int64Editor_editingFinished();
    void on_floatEditor_editingFinished();
    void on_doubleEditor_editingFinished();

    void on_editableCheckBox_toggled(bool checked);

private:
    Ui::HexnosisWindow *ui;
    AboutDialog *about;
    HexTabWidget *tab;
    static QDockWidget *dataProcessor;
    static QLabel *cursorPosition;
    static QLabel *cursorValue;

    QValidator *int8validator;
    QValidator *int16validator;
    QValidator *int32validator;
    QValidator *int64validator;
    QValidator *floatvalidator;
    QValidator *doublevalidator;

    void createStatusBar();
    void enableActions(bool enable = false);
    void findWorkingTheme();
    void setIconFallbacks();

    void createDataProcessorValidators();
    void setDataProcessorValidators();

public slots:
    static void updateCursorInfo(int offset, int value);
    static void clearCursorInfo();
    void updateDataProcessor(QByteArray data);
    void clearDataProcessor();
    void updateInfoDisplay(QString info);
    void clearInfoDisplay();
};

#endif // HEXNOSISWINDOW_H

