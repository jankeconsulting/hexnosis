/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "tabpanel.h"
#include <QDebug>

TabPanel::TabPanel(QWidget *parent, QFile *file) :
    QWidget(parent)
{
    setModel(new HexFileModel(this, file));
    hexpanel = new HexPanel(this);
    textpanel = new TextPanel(this);
    layout = new QHBoxLayout;
    layout->addWidget(hexpanel);
    layout->addWidget(textpanel);
    setLayout(layout);

    if(file) {
        model()->loadDatafromFile();
    }

    hexpanel->setModel(model());
    textpanel->setModel(model());

    textpanel->setSelectionModel(hexpanel->selectionModel());
    connect(textpanel->verticalScrollBar(), SIGNAL(valueChanged(int)), hexpanel->verticalScrollBar(), SLOT(setValue(int)));
    hexpanel->formatColumns();
    textpanel->formatColumns();
}

TabPanel::~TabPanel()
{
    delete model();
    delete hexpanel;
    delete textpanel;
    delete layout;
}

void TabPanel::createFile(int len, char fillchar)
{
    model()->createBuffer(len, fillchar);
}

bool TabPanel::saveFile(QString filename)
{
    return model()->saveDatatoFile(filename);
}

void TabPanel::setAlternatingRowColors(bool state)
{
    hexpanel->setAlternatingRowColors(state);
    textpanel->setAlternatingRowColors(state);
}
