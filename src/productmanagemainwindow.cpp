#include "productmanagemainwindow.h"

#include <QtSql>

#include "ui_product_manage.h"

ProductManageMainWindow::ProductManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductManageMainWindow)
{
    ui->setupUi(this);
}

ProductManageMainWindow::~ProductManageMainWindow()
{
    delete ui;
}

void ProductManageMainWindow::reload_query()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database");
    db.open();
    QSqlQuery query;
    query.exec("select * from product");
    while (query.next()) {
        QStandardItemModel *inout_model = new QStandardItemModel();
        inout_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号")));
        inout_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称")));
        inout_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
        inout_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单价")));
        inout_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("规格")));
        inout_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("库存")));
        inout_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("备注")));
    }
}
