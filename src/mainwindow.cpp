#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    query_window.reload_query();
    query_window.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    stock_window.reload_query();
    stock_window.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    product_manage_window.reload_query();
    product_manage_window.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    order_manage_window.reload_query();
    order_manage_window.show();
}
