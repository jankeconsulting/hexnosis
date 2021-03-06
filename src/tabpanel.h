/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_TABPANEL_H_
#define SRC_TABPANEL_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollBar>
#include <./hexpanel.h>
#include <./textpanel.h>
#include <./hexfilemodel.h>

/**
 * @brief The TabPanel class
 */
class TabPanel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(HexFileModel *model READ model WRITE setModel)
    Q_PROPERTY(HexPanel *hexpanel READ hexPanel WRITE setHexPanel)
    Q_PROPERTY(TextPanel *textpanel READ textPanel WRITE setTextPanel)

 public:
    explicit TabPanel(QWidget *parent = 0, QFile *file = 0);
    ~TabPanel();

    void createFile(int len, char fillchar);
    bool saveFile(QString filename);
    void setAlternatingRowColors(bool state);
    void setHexPanelVisibility(bool state);
    void setTextPanelVisibility(bool state);

    // QProperty Getters and Setters
    void setModel(HexFileModel *model);
    HexFileModel *model();
    void setHexPanel(HexPanel *panel);
    HexPanel *hexPanel();
    void setTextPanel(TextPanel *panel);
    TextPanel *textPanel();

 signals:

 public slots:

 private:
    HexPanel *m_hexpanel;
    TextPanel *m_textpanel;
    HexFileModel *m_model;
};

#endif  // SRC_TABPANEL_H_
