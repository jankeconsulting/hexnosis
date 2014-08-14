#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent, QString version) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->version->setText(tr("Version ").append(version));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_licenseButton_clicked()
{

}
