/**
 * Copyright (c) 2014 Ralph Janke. All rights reserved.
 *
 * Author: Ralph Janke hexnosis@jankeconsulting.ca
 */

#ifndef SRC_LICENSEDIALOG_H_
#define SRC_LICENSEDIALOG_H_

#include <QDialog>

namespace Ui
{
class LicenseDialog;
}

/**
 * @brief The LicenseDialog class
 */
class LicenseDialog : public QDialog
{
    Q_OBJECT

 public:
    explicit LicenseDialog(QWidget *parent = 0);
    ~LicenseDialog();

 private:
    Ui::LicenseDialog *ui;
};

#endif  // SRC_LICENSEDIALOG_H_
