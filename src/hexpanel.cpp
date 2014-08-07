/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexpanel.h"
#include <QDebug>

HexPanel::HexPanel(QWidget *parent) :
    HexFileModelPanel(parent)
{
    HexPanelItemDelegate *delegate = new HexPanelItemDelegate();
    setItemDelegate(qobject_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
}

HexPanel::~HexPanel()
{
}

void HexPanel::formatPanel()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalHeader()->setDefaultSectionSize(HEXPANEL_DEFAULT_COLUMN_WIDTH);
}
