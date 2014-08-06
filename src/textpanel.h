/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef TEXTPANEL_H
#define TEXTPANEL_H

#include <QTableView>
#include <QHeaderView>
#include "./textpanelitemdelegate.h"

class TextPanel : public QTableView
{
    Q_OBJECT
public:
    explicit TextPanel(QWidget *parent = 0);
    ~TextPanel();
    void formatColumns();

signals:

public slots:

private:
    void formatPanel();

};

#endif // TEXTPANEL_H
