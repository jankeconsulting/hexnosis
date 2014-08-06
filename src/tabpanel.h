/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef TABPANEL_H
#define TABPANEL_H

#include <QWidget>
#include <QHBoxLayout>
#include <QScrollBar>
#include <./hexpanel.h>
#include <./textpanel.h>
#include <./hexfilemodel.h>

class TabPanel : public QWidget
{
    Q_OBJECT
//    TODO: Investigate advantages of using Q_PROPERTY macro
    Q_PROPERTY(HexFileModel *model READ model WRITE setModel)
    Q_PROPERTY(HexPanel *hexpanel READ getHexPanel WRITE setHexPanel)

public:
    explicit TabPanel(QWidget *parent = 0, QFile *file = 0);
    ~TabPanel();

    void createFile(int len, char fillchar);
    bool saveFile(QString filename);
    void setAlternatingRowColors(bool state);

    void setModel(HexFileModel *model) {
        m_model = model;
    }

    HexFileModel *model() {
        return m_model;
    }

    void setHexPanel(HexPanel *panel) {
        hexpanel = panel;
    }

    HexPanel *getHexPanel() {
        return hexpanel;
    }

signals:

public slots:

private:
    HexPanel *hexpanel;
    TextPanel *textpanel;
    QHBoxLayout *layout;
    HexFileModel *m_model;
};

#endif // TABPANEL_H
