/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#include "./licensedialog.h"
#include "./ui_licensedialog.h"

/**
 * @brief contructs the object
 * @param parent of the object
 */
LicenseDialog::LicenseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LicenseDialog)
{
    ui->setupUi(this);
}

/**
 * @brief destroys the objects
 */
LicenseDialog::~LicenseDialog()
{
    delete ui;
}
