#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include "licensedialog.h"

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = 0, QString version = "");
    ~AboutDialog();

private slots:
    void on_licenseButton_clicked();

private:
    Ui::AboutDialog *ui;
    LicenseDialog *license;
};

#endif // ABOUTDIALOG_H
