#include "inoutdialog.h"
#include "ui_inoutdialog.h"

InoutDialog::InoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InoutDialog)
{
    ui->setupUi(this);
}

InoutDialog::~InoutDialog()
{
    delete ui;
}
