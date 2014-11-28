/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./tabpanel.h"
#include <QDebug>

/**
 * @brief constructs th object
 * @param parent of the object
 * @param file associated with the panel
 *
 *
 */
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

    if (file)
    {
        model()->loadDatafromFile();
    }

    hexpanel->setModel(model());
    textpanel->setModel(model());

    textpanel->setSelectionModel(hexpanel->selectionModel());
    connect(textpanel->verticalScrollBar(), SIGNAL(valueChanged(int)),
            hexpanel->verticalScrollBar(), SLOT(setValue(int)));

    hexpanel->calculateMinimumWidth();
    textpanel->calculateMinimumWidth();
    connect(hexpanel->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            model(), SLOT(updateCursorInfo(QModelIndex, QModelIndex)));
}

/**
 * @brief destroys the object
 *
 * The associated model, hexpanel, textpael and layoout are freed
 * before the object is destroys.
 */
TabPanel::~TabPanel()
{
    delete model();
    delete hexPanel();
    delete textPanel();
    delete layout();
}

/**
 * @brief creates the buffer for the file in the model
 * @param len - length of the file
 * @param fillchar - character to fill the buffer with
 *
 * This method is called when a new file is created.
 */
void TabPanel::createFile(int len, char fillchar)
{
    model()->createBuffer(len, fillchar);
}

/**
 * @brief saves the file associated with this object
 * @param filename of the file to be saved
 * @return true if file was saved sucessfully, otherwise false
 */
bool TabPanel::saveFile(QString filename)
{
    return model()->saveDatatoFile(filename);
}

/**
 * @brief sets the flag for alternating row colors
 * @param state - true if alternatig row colors are displayed, otherwise false
 */
void TabPanel::setAlternatingRowColors(bool state)
{
    hexPanel()->setAlternatingRowColors(state);
    textPanel()->setAlternatingRowColors(state);
}

/**
 * @brief sets the flag for the visibility of the hexpanel
 * @param state - true if th hexpanel is visible, otherwise false
 */
void TabPanel::setHexPanelVisibility(bool state)
{
    hexPanel()->setVisible(state);
}

/**
* @brief sets the flag for the visibility of the textpanel
* @param state - true if th textpanel is visible, otherwise false
*/
void TabPanel::setTextPanelVisibility(bool state)
{
    textPanel()->setVisible(state);
    if (state)
    {
        hexPanel()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        hexPanel()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    hexPanel()->calculateMinimumWidth();
}

/**
 * @brief sets the model for this tab
 * @param model
 */
void TabPanel::setModel(HexFileModel *model)
{
    m_model = model;
}

/**
 * @brief provides the model for the tab
 * @return the model
 */
HexFileModel *TabPanel::model()
{
    return m_model;
}

/**
 * @brief sets the hexpanel for the tab
 * @param panel
 */
void TabPanel::setHexPanel(HexPanel *panel)
{
    m_hexpanel = panel;
}

/**
 * @brief returns the hexpanel of the tab
 * @return hexpanel
 */
HexPanel *TabPanel::hexPanel()
{
    return m_hexpanel;
}

/**
 * @brief sets the textpanel for the tab
 * @param panel
 */
void TabPanel::setTextPanel(TextPanel *panel)
{
    m_textpanel = panel;
}

/**
 * @brief returns the textpanel of the tab
 * @return textpanel
 */
TextPanel *TabPanel::textPanel()
{
    return m_textpanel;
}
