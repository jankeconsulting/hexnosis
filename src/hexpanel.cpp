/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexpanel.h"
#include <QDebug>

HexPanel::HexPanel(QWidget *parent) :
    QTableView(parent)
{
    HexPanelItemDelegate *delegate = new HexPanelItemDelegate();
    setItemDelegate(static_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
//    setMouseTracking(true);
//    viewport()->setMouseTracking(true);
//    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(setHighlight(QModelIndex)));
}

HexPanel::~HexPanel()
{
    delete itemDelegate();
    delete model();
}

void HexPanel::formatPanel()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setShowGrid(false);
    horizontalHeader()->setDefaultSectionSize(25);
    verticalHeader()->setDefaultSectionSize(15);
}

void HexPanel::formatColumns()
{
    for(int i=0; i<16; i++) {
        setColumnWidth(i+16, 13);
    }
}

void HexPanel::setHighlight(QModelIndex index)
{
//    TODO: Implement code to follow mouse cursor in parallel window
//#ifdef DEBUG
//    qDebug() << "HexPanel::setHighlight entered" << index;
//#endif
//#ifdef DEBUG
//    qDebug() << "HexPanel::setHighlight : index->data() = " << index.data(Qt::DisplayRole).toString();
//#endif
    if(index.column() < 16) {

    } else {

    }

}
