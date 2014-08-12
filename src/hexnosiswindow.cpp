/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "hexnosiswindow.h"
#include "ui_hexnosiswindow.h"
#include <QDebug>

QLabel *HexnosisWindow::cursorPosition = 0;
QLabel *HexnosisWindow::cursorValue = 0;
QDockWidget *HexnosisWindow::dataProcessor = 0;

HexnosisWindow::HexnosisWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HexnosisWindow)
{
    findWorkingTheme();
    ui->setupUi(this);
    dataProcessor = ui->dataProcessorDockWidget;
    dataProcessor->setVisible(ui->actionDataProcessor->isChecked());
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
}

HexnosisWindow::~HexnosisWindow()
{
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

void HexnosisWindow::closeTab(int index)
{
    QWidget *p = tab->widget(index);
    tab->removeTab(index);
    delete p;
}

void HexnosisWindow::currentTabChanged(int index)
{
    Q_UNUSED(index);
    if(tab->count() > 0) {
        enableActions(true);
        if(!qobject_cast<TabPanel *>(tab->currentWidget())->model()->hasFile()) {
            ui->actionSave->setEnabled(false);
        }
        QModelIndex index = qobject_cast<TabPanel *>(tab->currentWidget())->hexPanel()->selectionModel()->currentIndex();
        qobject_cast<TabPanel *>(tab->currentWidget())->model()->updateCursorInfo(index, index);
    } else {
        enableActions(false);
        clearCursorInfo();
    }
}

void HexnosisWindow::enableActions(bool enable)
{
    ui->actionClose->setEnabled(enable);
    ui->actionSave->setEnabled(enable);
    ui->actionSaveAs->setEnabled(enable);
}

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

void HexnosisWindow::createDataProcessorValidators()
{
    int8validator = new QIntValidator(-128, 255, this);
    int16validator = new QIntValidator(-32768, 65535, this);
//    int32validator = new QIntValidator(-2147483648, 4294967295, this);
    int32validator = new QIntValidator(this);
//    int64validator = new QIntValidator(-9223372036854775808, 18446744073709551615, this);
    int64validator = new QIntValidator(this);
    floatvalidator = new QDoubleValidator;
    doublevalidator = new QDoubleValidator;

    setDataProcessorValidators();
}

void HexnosisWindow::setDataProcessorValidators()
{
    ui->int8Editor->setValidator(int8validator);
    ui->int16Editor->setValidator(int16validator);
    ui->int32Editor->setValidator(int32validator);
    ui->int64Editor->setValidator(int64validator);
    ui->floatEditor->setValidator(floatvalidator);
    ui->doubleEditor->setValidator(doublevalidator);
}

void HexnosisWindow::updateCursorInfo(int offset, int value)
{
    cursorPosition->setText(tr("Cursor Offset : %1").arg(offset));
    cursorValue->setText(tr("Cursor Value : %1").arg(value));
}

void HexnosisWindow::clearCursorInfo()
{
    if(cursorPosition)
        cursorPosition->clear();
    if(cursorValue)
        cursorValue->clear();
}

void HexnosisWindow::updateDataProcessor(QByteArray data)
{
//    TODO: refactor this
    char *bytes = data.data();
    if(ui->unsignedCheckBox->isChecked()) {
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
    } else {
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
    for(int i = 7; i >= 0; i--)
    {
        if(1 << i & data[0]) {
            bitBytes.append("1");
        } else {
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

void HexnosisWindow::on_actionNew_triggered()
{
    tab->createFile();
    resetToggles();
}

void HexnosisWindow::on_actionOpen_triggered()
{
    tab->openFile();
    resetToggles();
}

void HexnosisWindow::on_actionClose_triggered()
{
    closeTab(tab->currentIndex());
}

void HexnosisWindow::on_actionSave_triggered()
{
    tab->saveFile();
}

void HexnosisWindow::on_actionSaveAs_triggered()
{
    tab->saveFileAs();
}

void HexnosisWindow::on_actionAbout_triggered()
{
//    TODO: Add about widget
}

void HexnosisWindow::on_actionAboutQt_triggered()
{
    qApp->aboutQt();
}

void HexnosisWindow::createStatusBar()
{
    cursorPosition = new QLabel();
    statusBar()->addPermanentWidget(cursorPosition);
    cursorValue = new QLabel();
    statusBar()->addPermanentWidget(cursorValue);
}

bool HexnosisWindow::rowShadingState() {
    return ui->actionRowShading->isChecked();
}

bool HexnosisWindow::hexPanelVisibility()
{
    return ui->actionHexDisplay->isChecked();
}

bool HexnosisWindow::textPanelVisibility()
{
    return ui->actionCharDisplay->isChecked();
}

void HexnosisWindow::resetToggles()
{
    on_actionRowShading_toggled(rowShadingState());
    on_actionHexDisplay_toggled(hexPanelVisibility());
    on_actionCharDisplay_toggled(textPanelVisibility());
}

void HexnosisWindow::on_actionRowShading_toggled(bool state)
{
    tab->setAlternatingRowColors(state);
}

void HexnosisWindow::on_actionHexDisplay_toggled(bool state)
{
    tab->setHexPanelVisibility(state);
}

void HexnosisWindow::on_actionCharDisplay_toggled(bool state)
{
    tab->setTextPanelVisibility(state);
}

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

void HexnosisWindow::on_binaryEditor_textEdited(const QString &text)
{
    char c = 0;
    for(int i = 0; i < 8; i++) {
        if(text[i] == QChar('1')) {
            c |= (1 << (7-i));
        }
    }
    tab->setTextInCurrentTab(QByteArray().append(&c, 1));
}

void HexnosisWindow::on_int8Editor_editingFinished()
{
    qDebug() << "HexnosisWindow::on_int8Editor_editingFinished";
    int value = ui->int8Editor->text().toInt();
    char c[1];
    memcpy(&c, &value, 1);
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, 1));
}

void HexnosisWindow::on_int16Editor_editingFinished()
{
    short value = ui->int16Editor->text().toShort();
    char c[sizeof(value)];
    memcpy(&c, &value, 2);
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

void HexnosisWindow::on_int32Editor_editingFinished()
{
    int value = ui->int32Editor->text().toInt();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

void HexnosisWindow::on_int64Editor_editingFinished()
{
    long value = ui->int64Editor->text().toLongLong();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

void HexnosisWindow::on_floatEditor_editingFinished()
{
    float value = ui->floatEditor->text().toFloat();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}

void HexnosisWindow::on_doubleEditor_editingFinished()
{
    double value = ui->doubleEditor->text().toDouble();
    char c[sizeof(value)];
    memcpy(&c, &value, sizeof(value));
    char *cp;
    cp = (&c[0]);
    tab->setTextInCurrentTab(QByteArray().append(cp, sizeof(value)));
}


