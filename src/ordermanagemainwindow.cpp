#include "ordermanagemainwindow.h"
#include "ui_ordermanagemainwindow.h"

OrderManageMainWindow::OrderManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderManageMainWindow)
{
    ui->setupUi(this);
}

OrderManageMainWindow::~OrderManageMainWindow()
{
    delete ui;
}
