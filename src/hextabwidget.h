/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_HEXTABWIDGET_H_
#define SRC_HEXTABWIDGET_H_

#include <QTabWidget>
#include <QInputDialog>
#include <./tabpanel.h>

/**
 * @brief The HexTabWidget class
 */
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
    void setTextInCurrentTab(QByteArray data);

 signals:
    void cursorDataChanged(QByteArray data);

 public slots:
    void currentCursorData();
};

#endif  // SRC_HEXTABWIDGET_H_
