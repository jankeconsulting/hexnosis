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
    HexPanel *hexpanel = new HexPanel(this);
    setHexPanel(hexpanel);
    TextPanel *textpanel = new TextPanel(this);
    setTextPanel(textpanel);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(hexpanel);
    layout->addWidget(textpanel);
    layout->addStretch();
    setLayout(layout);

    if(file) {
        model()->loadDatafromFile();
    }

    hexpanel->setModel(model());
    textpanel->setModel(model());

    hexpanel->calculateMinimumWidth();
    textpanel->calculateMinimumWidth();

    textpanel->setSelectionModel(hexpanel->selectionModel());
    connect(textpanel->verticalScrollBar(), SIGNAL(valueChanged(int)), hexpanel->verticalScrollBar(), SLOT(setValue(int)));
}

TabPanel::~TabPanel()
{
    delete model();
    delete hexPanel();
    delete textPanel();
    delete layout();
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
    hexPanel()->setAlternatingRowColors(state);
    textPanel()->setAlternatingRowColors(state);
}

void TabPanel::setModel(HexFileModel *model) {
    m_model = model;
}

HexFileModel *TabPanel::model() {
    return m_model;
}

void TabPanel::setHexPanel(HexPanel *panel) {
    m_hexpanel = panel;
}

HexPanel *TabPanel::hexPanel() {
    return m_hexpanel;
}

void TabPanel::setTextPanel(TextPanel *panel) {
    m_textpanel = panel;
}

TextPanel *TabPanel::textPanel() {
    return m_textpanel;
}
