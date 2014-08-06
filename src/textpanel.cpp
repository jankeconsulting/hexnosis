/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "textpanel.h"

TextPanel::TextPanel(QWidget *parent) :
    QTableView(parent)
{
    TextPanelItemDelegate *delegate = new TextPanelItemDelegate();
    setItemDelegate(static_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
}

TextPanel::~TextPanel()
{
    delete itemDelegate();
    delete model();
}

void TextPanel::formatColumns()
{
    setShowGrid(false);
    horizontalHeader()->setDefaultSectionSize(13);
    verticalHeader()->setDefaultSectionSize(15);
    setAlternatingRowColors(true);
}

void TextPanel::formatPanel()
{
    for(int i=0; i<16; i++) {
        setColumnWidth(i+16, 13);
    }
}
