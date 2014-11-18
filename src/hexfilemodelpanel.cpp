/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hexfilemodelpanel.h"
#include <QDebug>

/**
 * @brief constructs the object
 * @param parent of the object
 */
HexFileModelPanel::HexFileModelPanel(QWidget *parent) :
    QTableView(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    setShowGrid(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    verticalHeader()->setDefaultSectionSize(15);

    //    setMouseTracking(true);
    //    viewport()->setMouseTracking(true);
    //    connect(this, SIGNAL(entered(QModelIndex)), this, SLOT(setHighlight(QModelIndex)));
}

/**
 * @brief destroys the object
 */
HexFileModelPanel::~HexFileModelPanel()
{
    delete itemDelegate();
    delete model();
}

/**
 * @brief calculates the minimum width for the panel
 */
void HexFileModelPanel::calculateMinimumWidth()
{
    int total_width = 0;
    int column_width = 0;
    for(int i = 0; i< model()->columnCount(); i++) {
        column_width += columnWidth(i);
    }
    total_width += column_width;
    total_width += frameWidth()*2;
//    if(verticalHeader()->isVisible())
        total_width += verticalHeader()->width();
//    TODO: ideally there needs to be a change when scrollbar is hidden or shown
//    if(verticalScrollBar()->isVisible())
    if(verticalScrollBarPolicy() == Qt::ScrollBarAlwaysOn || verticalScrollBarPolicy() == Qt::ScrollBarAsNeeded)
        total_width += verticalScrollBar()->sizeHint().width();
    setMinimumWidth(total_width);
}
