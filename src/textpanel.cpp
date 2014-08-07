/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "textpanel.h"
#include <QDebug>

TextPanel::TextPanel(QWidget *parent) :
    HexFileModelPanel(parent)
{
    TextPanelItemDelegate *delegate = new TextPanelItemDelegate();
    setItemDelegate(qobject_cast<QAbstractItemDelegate *>(delegate));
    formatPanel();
}

TextPanel::~TextPanel()
{
}

void TextPanel::formatPanel()
{
    horizontalHeader()->setDefaultSectionSize(TEXTPANEL_DEFAULT_COLUMN_WIDTH);
}
