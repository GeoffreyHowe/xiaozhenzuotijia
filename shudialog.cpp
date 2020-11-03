#include "shudialog.h"
#include "ui_shudialog.h"

SHUDialog::SHUDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SHUDialog)
{
    ui->setupUi(this);
}

SHUDialog::~SHUDialog()
{
    delete ui;
}
