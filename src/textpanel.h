/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef TEXTPANEL_H
#define TEXTPANEL_H

#include "hexfilemodelpanel.h"
#include "textpanelitemdelegate.h"

// TODO: Make width more flexible due to font etc
#define TEXTPANEL_DEFAULT_COLUMN_WIDTH 13

class TextPanel : public HexFileModelPanel
{
    Q_OBJECT
public:
    explicit TextPanel(QWidget *parent = 0);
    ~TextPanel();

signals:

public slots:

private:
    void formatPanel();

};

#endif // TEXTPANEL_H
