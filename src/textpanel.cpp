/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "textpanel.h"
#include <QDebug>

TextPanel::TextPanel(QWidget *parent) :
    QTableView(parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    TextPanelItemDelegate *delegate = new TextPanelItemDelegate();
    setItemDelegate(qobject_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
}

TextPanel::~TextPanel()
{
    delete itemDelegate();
    delete model();
}

void TextPanel::formatPanel()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setShowGrid(false);
    horizontalHeader()->setDefaultSectionSize(13);
    verticalHeader()->setDefaultSectionSize(15);
}

void TextPanel::formatColumns()
{
    for(int i=0; i<16; i++) {
        setColumnWidth(i+16, 13);
    }
}

void TextPanel::calculateMinimumWidth()
{
    int column_width = 0;
    for(int i = 0; i< model()->columnCount(); i++) {
        column_width += columnWidth(i);
    }
    setMinimumWidth(verticalHeader()->width() + column_width + frameWidth()*2 + verticalScrollBar()->sizeHint().width());
}
