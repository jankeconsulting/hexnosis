/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./hexnosiswindow.h"
#include "./ui_hexnosiswindow.h"
#include <QDebug>

QLabel *HexnosisWindow::cursorPosition = 0;
QLabel *HexnosisWindow::cursorValue = 0;
QDockWidget *HexnosisWindow::dataProcessor = 0;

/**
 * @brief constructs the main window
 * @param parent of the main window objectS
 */
HexnosisWindow::HexnosisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HexnosisWindow),
    m_settings()
{
    findWorkingTheme();
    ui->setupUi(this);
    about = new AboutDialog(this, HEXNOSIS_REVISION);
    dataProcessor = ui->dataProcessorDockWidget;
    dataProcessor->setVisible(ui->actionDataProcessor->isChecked());
    infoDisplay = ui->infoDisplayDockWidget;
    infoDisplay->setVisible(ui->actionDataProcessor->isChecked());
    clearInfoDisplay();
    setWindowTitle(QString(tr("Hexnosis - Hex Editor")));
    setIconFallbacks();
    enableActions(false);
    tab = new HexTabWidget(ui->centralWidget);
    tab->setTabsClosable(true);
    this->setCentralWidget(tab);
    connect(tab, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tab, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
    connect(tab, SIGNAL(cursorDataChanged(QByteArray)), this, SLOT(updateDataProcessor(QByteArray)));
    connect(ui->unsignedCheckBox, SIGNAL(toggled(bool)), tab, SLOT(currentCursorData()));
    connect(ui->bigEndianCheckBox, SIGNAL(toggled(bool)), tab, SLOT(currentCursorData()));
    on_editableCheckBox_toggled(ui->editableCheckBox->isChecked());
    createDataProcessorValidators();
    createStatusBar();
    readSettings();
}

/**
 * @brief destrioys the main window
 *
 * All objects created during the construction are deleted
 * before the object itself is destroyed.
 */
HexnosisWindow::~HexnosisWindow()
{
    delete about;
    delete tab;
    delete ui;
    delete cursorPosition;
    delete cursorValue;
    delete int8validator;
    delete int16validator;
    delete int32validator;
    delete int64validator;
    delete floatvalidator;
    delete doublevalidator;
}

/**
 * @brief closes a tab of the main window
 * @param index of the tab
 *
 * Each file opened is put into its own tab. When
 * a file is closed, the corresponding tab is closed.
 */
void HexnosisWindow::closeTab(int index)
{
    QWidget *p = tab->widget(index);
    tab->removeTab(index);
    delete p;
}

/**
 * @brief slot that is called when the current tan is changed
 * @param index of the tab that is the new current tab
 *
 * When the tab is changed, all the panels are changed to
 * represent the current tab.
 */
void HexnosisWindow::currentTabChanged(int index)
{
    Q_UNUSED(index);
    if (tab->count() > 0)
    {
        enableActions(true);
        TabPanel *tabpanel = qobject_cast<TabPanel *>(tab->currentWidget());
        if (!tabpanel->model()->hasFile())
        {
            ui->actionSave->setEnabled(false);
        }
        QModelIndex index = tabpanel->hexPanel()->selectionModel()->currentIndex();
        tabpanel->model()->updateCursorInfo(index, index);
        updateInfoDisplay(tabpanel->model()->fileInfo());
    }
    else
    {
        enableActions(false);
        clearCursorInfo();
        clearInfoDisplay();
    }
}

/**
 * @brief enables file actions when available
 * @param enable - true to enable, false to disable
 */
void HexnosisWindow::enableActions(bool enable)
{
    ui->actionClose->setEnabled(enable);
    ui->actionSave->setEnabled(enable);
    ui->actionSaveAs->setEnabled(enable);
}

/**
 * @brief sets theme icons
 */
void HexnosisWindow::findWorkingTheme()
{
//    TODO: Needs rework for DRY
    if(QIcon::hasThemeIcon("application-exit")
            && QIcon::hasThemeIcon("document-new")
            && QIcon::hasThemeIcon("document-open")
            && QIcon::hasThemeIcon("document-save")
            && QIcon::hasThemeIcon("document-save-as")
            && QIcon::hasThemeIcon("document-close")
            )
        return;

    QIcon::setThemeName("oxygen");
    if(QIcon::hasThemeIcon("application-exit")
            && QIcon::hasThemeIcon("document-new")
            && QIcon::hasThemeIcon("document-open")
            && QIcon::hasThemeIcon("document-save")
            && QIcon::hasThemeIcon("document-save-as")
            && QIcon::hasThemeIcon("document-close")
            )
        return;
}

/**
 * @brief sets fallback icons in case there is no theme found
 */
void HexnosisWindow::setIconFallbacks()
{
//    TODO: Needs rework for DRY
    if(!QIcon::hasThemeIcon("document-close"))
        ui->actionClose->setIcon(this->style()->standardIcon(QStyle::SP_DialogCloseButton));
    if(!QIcon::hasThemeIcon("document-open"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogOpenButton));
    if(!QIcon::hasThemeIcon("document-save"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    if(!QIcon::hasThemeIcon("document-save-as"))
        ui->actionOpen->setIcon(this->style()->standardIcon(QStyle::SP_DialogSaveButton));
    if(!QIcon::hasThemeIcon("document-new"))
        ui->actionNew->setIcon(this->style()->standardIcon(QStyle::SP_FileDialogStart));
}

/**
 * @brief creates the Validators for the input fields of the data processor panel
 */
void HexnosisWindow::createDataProcessorValidators()
{
    int8validator = new QIntValidator(-128, 255, this);
    int16validator = new QIntValidator(-32768, 65535, this);
    int32validator = new QxLongValidator(Q_INT64_C(-2147483648), Q_INT64_C(4294967295), this);
    int64validator = new QxLongValidator(this);
    floatvalidator = new QDoubleValidator;
    doublevalidator = new QDoubleValidator;

    setDataProcessorValidators();
}

/**
 * @brief sets the Validators for the input fields of the data processor panel
 */
void HexnosisWindow::setDataProcessorValidators()
{
    ui->int8Editor->setValidator(int8validator);
    ui->int16Editor->setValidator(int16validator);
    ui->int32Editor->setValidator(int32validator);
    ui->int64Editor->setValidator(int64validator);
    ui->floatEditor->setValidator(floatvalidator);
    ui->doubleEditor->setValidator(doublevalidator);
}

/**
 * @brief writes the settings to store between session
 */
void HexnosisWindow::writeSettings()
{
    m_settings.beginGroup("view");
    m_settings.setValue("alternatingRows", ui->actionRowShading->isChecked());
    m_settings.setValue("charDisplay", ui->actionCharDisplay->isChecked());
    m_settings.setValue("hexDisplay", ui->actionHexDisplay->isChecked());
    m_settings.setValue("dataProcessor", ui->actionDataProcessor->isChecked());
    m_settings.setValue("infoDisplay", ui->actionInfoDisplay->isChecked());
    m_settings.endGroup();
}

/**
 * @brief reads  the settings stored from previous session
 */
void HexnosisWindow::readSettings()
{
    m_settings.beginGroup("view");
    ui->actionRowShading->setChecked(qvariant_cast<bool>(m_settings.value("alternatingRows")));
    ui->actionCharDisplay->setChecked(qvariant_cast<bool>(m_settings.value("charDisplay")));
    ui->actionHexDisplay->setChecked(qvariant_cast<bool>(m_settings.value("hexDisplay")));
    ui->actionDataProcessor->setChecked(qvariant_cast<bool>(m_settings.value("dataProcessor")));
    ui->actionInfoDisplay->setChecked(qvariant_cast<bool>(m_settings.value("infoDisplay")));
    m_settings.endGroup();
}

/**
 * @brief sets the cursor information in the status bar
 * @param offset within the file
 * @param value of the byte the cursor is placed on
 */
void HexnosisWindow::updateCursorInfo(int offset, int value)
{
    cursorPosition->setText(tr("Cursor Offset : %1").arg(offset));
    cursorValue->setText(tr("Cursor Value : %1").arg(value));
}

/**
 * @brief clears the cursor information in the status bar
 */
void HexnosisWindow::clearCursorInfo()
{
    if(cursorPosition)
        cursorPosition->clear();
    if(cursorValue)
        cursorValue->clear();
}

/**
 * @brief updates the information in the data processor panel
 * @param data contains a QByteArray of data needed
 */
void HexnosisWindow::updateDataProcessor(QByteArray data)
{
//    TODO: refactor this
    char *bytes = data.data();
    if (ui->unsignedCheckBox->isChecked())
    {
        uchar charByte = data[0];
        ui->int8Editor->setText(QString().setNum(charByte, 10));
        ushort shortBytes;
        memcpy(&shortBytes, bytes, sizeof(ushort));
        ui->int16Editor->setText(QString().setNum(shortBytes));
        uint intBytes;
        memcpy(&intBytes, bytes, sizeof(uint));
        ui->int32Editor->setText(QString().setNum(intBytes));
        ulong longBytes;
        memcpy(&longBytes, bytes, sizeof(ulong));
        ui->int64Editor->setText(QString().setNum(longBytes));
    }
    else
    {
        ui->int8Editor->setText(QString().setNum(data[0], 10));
        short shortBytes;
        memcpy(&shortBytes, bytes, sizeof(short));
        ui->int16Editor->setText(QString().setNum(shortBytes));
        int intBytes;
        memcpy(&intBytes, bytes, sizeof(int));
        ui->int32Editor->setText(QString().setNum(intBytes));
        long longBytes;
        memcpy(&longBytes, bytes, sizeof(long));
        ui->int64Editor->setText(QString().setNum(longBytes));
    }
    QString bitBytes = QString("");
    for (int i = 7; i >= 0; i--)
    {
        if (1 << i & data[0]) {
            bitBytes.append("1");
        }
        else
        {
            bitBytes.append("0");
        }
    }
    ui->binaryEditor->setText(bitBytes);
    float floatBytes;
    memcpy(&floatBytes, bytes, sizeof(float));
    ui->floatEditor->setText(QString().setNum(floatBytes));
    double doubleBytes;
    memcpy(&doubleBytes, bytes, sizeof(double));
    ui->doubleEditor->setText(QString().setNum(doubleBytes));
}

/**
 * @brief clears the information in the data processor panel
 */
void HexnosisWindow::clearDataProcessor()
{
    ui->binaryEditor->clear();
    ui->int8Editor->clear();
    ui->int16Editor->clear();
    ui->int32Editor->clear();
    ui->int64Editor->clear();
    ui->floatEditor->clear();
    ui->doubleEditor->clear();
}

/**
 * @brief updates the information in the info display
 * @param info
 */
void HexnosisWindow::updateInfoDisplay(QString info)
{
    ui->infoDisplayTextBrowser->setText(info);
}

/**
 * @brief clears the information in the info display
 */
void HexnosisWindow::clearInfoDisplay()
{
    ui->infoDisplayTextBrowser->clear();

}

/**
 * @brief slot that is called when a new file is created
 *
 * Opens a tab with an empty file and resets the checkable
 * menu actions
 */
void HexnosisWindow::on_actionNew_triggered()
{
    tab->createFile();
    resetToggles();
}
/**
 * @brief slot that is called when file is opened
 *
 * Opens a tab with file and resets the checkable
 * menu actions. The file is open after it is selected
 * through a file selecting dialog.
 */
void HexnosisWindow::on_actionOpen_triggered()
{
    tab->openFile();
    resetToggles();
}

/**
 * @brief slot that is called when a file is closed.
 */
void HexnosisWindow::on_actionClose_triggered()
{
    closeTab(tab->currentIndex());
}

/**
 * @brief slot that is called when a file is saved
 */
void HexnosisWindow::on_actionSave_triggered()
{
    tab->saveFile();
}

/**
 * @brief slot that is called when a file is saved as
 */
void HexnosisWindow::on_actionSaveAs_triggered()
{
    tab->saveFileAs();
}

/**
 * @brief slot that is called when the about dialog is requested
 *
 * Shows the about dialog
 */
void HexnosisWindow::on_actionAbout_triggered()
{
    about->show();
}

/**
 * @brief slots that is called when the Qt-About dialog is requested
 *
 * Shows the Qt-About dialog
 */
void HexnosisWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

/**
 * @brief creates the status bar
 */
void HexnosisWindow::createStatusBar()
{
    cursorPosition = new QLabel();
    statusBar()->addPermanentWidget(cursorPosition);
    cursorValue = new QLabel();
    statusBar()->addPermanentWidget(cursorValue);
}

/**
 * @brief provides the state for row shading
 * @return true if row shading is enable, otherwise false
 */
bool HexnosisWindow::rowShadingState() {
    return ui->actionRowShading->isChecked();
}

/**
 * @brief provides the state for the hexpanel visibility
 * @return true if hexpanel is visible is enable, otherwise false
 */
bool HexnosisWindow::hexPanelVisibility()
{
    return ui->actionHexDisplay->isChecked();
}

/**
 * @brief provides the state for the textpanel visibility
 * @return true if textpanel is visible is enable, otherwise false
 */
bool HexnosisWindow::textPanelVisibility()
{
    return ui->actionCharDisplay->isChecked();
}

/**
 * @brief resets the checkable menu actions
 */
void HexnosisWindow::resetToggles()
{
    on_actionRowShading_toggled(rowShadingState());
    on_actionHexDisplay_toggled(hexPanelVisibility());
    on_actionCharDisplay_toggled(textPanelVisibility());
}

/**
 * @brief slot that is called when row shading flag is changed
 * @param state of the checkbox
 */
void HexnosisWindow::on_actionRowShading_toggled(bool state)
{
    tab->setAlternatingRowColors(state);
}

/**
 * @brief slot that is called when hexdisplay visibility is changed
 * @param state of the checkbox
 */
void HexnosisWindow::on_actionHexDisplay_toggled(bool state)
{
    tab->setHexPanelVisibility(state);
}

/**
 * @brief slot that is called when textdisplay visibility is changed
 * @param state of the checkbox
 */
void HexnosisWindow::on_actionCharDisplay_toggled(bool state)
{
    tab->setTextPanelVisibility(state);
}

/**
 * @brief slot that is called when editability of data processor fields is changed
 * @param checked - value of the checkbox
 */
void HexnosisWindow::on_editableCheckBox_toggled(bool checked)
{
    ui->binaryEditor->setReadOnly(!checked);
    ui->int8Editor->setReadOnly(!checked);
    ui->int16Editor->setReadOnly(!checked);
    ui->int32Editor->setReadOnly(!checked);
    ui->int64Editor->setReadOnly(!checked);
    ui->floatEditor->setReadOnly(!checked);
    ui->doubleEditor->setReadOnly(!checked);
}

/**
 * @brief slot that is called when the binary editor field value has changed
 * @param text contains the new value of the field
 */
void HexnosisWindow::on_binaryEditor_textEdited(const QString &text)
{
    char c = 0;
    for (int i = 0; i < 8; i++)
    {
        if (text[i] == QChar('1'))
        {
            c |= (1 << (7-i));
        }
    }
    tab->setTextInCurrentTab(QByteArray().append(&c, 1));
}

/**
 * @brief slot that is called  when the 8 bit editor field was edited
 */
void HexnosisWindow::on_int8Editor_editingFinished()
{
    int value = ui->int8Editor->text().toInt();
    char c[1];
    memcpy(&c, &value, 1);
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, 1));
}

/**
 * @brief slot that is called  when the 16 bit editor field was edited
 */
void HexnosisWindow::on_int16Editor_editingFinished()
{
    bool ok;
    short value = ui->int16Editor->text().toShort(&ok);
    // need to use void* in order to allow both short and ushort being possible
    void *p = &value;
    if (!ok)
    {
        ushort value = ui->int16Editor->text().toUShort(&ok);
        p = &value;
    }
    char c[sizeof(value)];
    memcpy(&c, p, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

/**
 * @brief slot that is called  when the 32 bit editor field was edited
 */
void HexnosisWindow::on_int32Editor_editingFinished()
{
    bool ok;
    int value = ui->int32Editor->text().toInt(&ok);
    // need to use void* in order to allow both int and uint being possible
    void *p = &value;
    if (!ok)
    {
        uint value = ui->int32Editor->text().toUInt(&ok);
        p = &value;
    }
    char c[sizeof(value)];
    memcpy(&c, p, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

/**
 * @brief slot that is called  when the 64 bit editor field was edited
 */
void HexnosisWindow::on_int64Editor_editingFinished()
{
    bool ok;
    // need to use void* in order to allow both long and ulong being possible
    void *p;
    QString text = ui->int64Editor->text();
    if (text[0] == '-')
    {
        qlonglong value = text.toLongLong(&ok);
        p = &value;
    }
    else
    {
        qulonglong value = text.toULongLong(&ok);
        p = &value;
    }
    char c[8];
    memcpy(&c, p, 8);
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, 8));
}

/**
 * @brief slot that is called  when the float editor field was edited
 */
void HexnosisWindow::on_floatEditor_editingFinished()
{
    float value = ui->floatEditor->text().toFloat();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

/**
 * @brief slot that is called  when the double editor field was edited
 */
void HexnosisWindow::on_doubleEditor_editingFinished()
{
    double value = ui->doubleEditor->text().toDouble();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

/**
 * @brief slot that is called when the window is closed
 *
 * Writes all the session settings to be store for the next session
 */
void HexnosisWindow::on_actionQuit_triggered()
{
    writeSettings();
}
