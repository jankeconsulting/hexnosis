/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./aboutdialog.h"
#include "./ui_aboutdialog.h"

/**
 * @brief constructs the AboutDialog
 * @param parent of the object
 * @param version of the application as shown in AboutDialog
 */
AboutDialog::AboutDialog(QWidget *parent, QString version) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->version->setText(tr("Version ").append(version));
    license = new LicenseDialog(this);
}

/**
 * @brief destroys the AboutDialog
 */
AboutDialog::~AboutDialog()
{
    delete license;
    delete ui;
}

/**
 * @brief slot called when license Button is selected
 *
 * Shows the LicenseDialog.
 */
void AboutDialog::on_licenseButton_clicked()
{
    license->show();
}
