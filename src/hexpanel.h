/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef HEXPANEL_H
#define HEXPANEL_H

#include <QTableView>
#include <QHeaderView>
#include "./hexpanelitemdelegate.h"

class HexPanel : public QTableView
{
    Q_OBJECT
public:
    explicit HexPanel(QWidget *parent = 0);
    ~HexPanel();
    void formatColumns();

signals:

public slots:
    void setHighlight(QModelIndex index);

private:
    void formatPanel();

};

#endif // HEXPANEL_H
