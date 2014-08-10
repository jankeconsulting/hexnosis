/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef HEXTABWIDGET_H
#define HEXTABWIDGET_H

#include <QTabWidget>
#include <QInputDialog>
#include <tabpanel.h>

class HexTabWidget : public QTabWidget
{
    Q_OBJECT

private:
    QString filename;
    QFile *file;

    bool chooseFile();
    QString fileName(bool with_path = false);

public:
    explicit HexTabWidget(QWidget *parent = 0);
    ~HexTabWidget();

    void addTabPage(TabPanel *page, QString tabname = "New", QString tabhint = "New File");
    void createFile();
    void openFile();
    void saveFile();
    void saveFileAs();

    void setAlternatingRowColors(bool state);
    void setHexPanelVisibility(bool state);
    void setTextPanelVisibility(bool state);

signals:
    void cursorDataChanged(QByteArray data);

public slots:
    void currentCursorData();
};

#endif // HEXTABWIDGET_H
