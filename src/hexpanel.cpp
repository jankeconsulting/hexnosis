/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hexpanel.h"
#include "./hexnosiswindow.h"
#include <QDebug>

/**
 * @brief constructs the object
 * @param parent
 */
HexPanel::HexPanel(QWidget *parent) :
    HexFileModelPanel(parent)
{
    HexPanelItemDelegate *delegate = new HexPanelItemDelegate();
    setItemDelegate(qobject_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
}

/**
 * @brief destroys the object
 */
HexPanel::~HexPanel()
{
}

/**
 * @brief sets format settings for the hexpanel
 */
void HexPanel::formatPanel()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    horizontalHeader()->setDefaultSectionSize(HEXPANEL_DEFAULT_COLUMN_WIDTH);
}
