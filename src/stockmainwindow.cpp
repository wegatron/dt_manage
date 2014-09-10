#include "stockmainwindow.h"

#include <QtGui>
#include <QStandardItemModel>

#include "ui_stockmainwindow.h"

#include "database.h"
#include "product.h"
#include "excel.h"

StockMainWindow::StockMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StockMainWindow)
{
    stock_model = new QStandardItemModel();
    sort_filter = new QSortFilterProxyModel(this);
    ui->setupUi(this);
}

StockMainWindow::~StockMainWindow()
{
    if(stock_model != NULL) {
        delete stock_model;
    }
    if(sort_filter != NULL) {
        delete sort_filter;
    }
    delete ui;
}

void StockMainWindow::reload_query()
{
    stock_model->clear();
    stock_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号")));
    stock_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称/规格")));
    stock_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
    stock_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("上期结存")));
    stock_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库数")));
    stock_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出库数")));
    stock_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结存")));

    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select id, name, specification, unit from product");

    QString date_from = ui->sqd_begin->text();
    QString date_to = ui->sqd_end->text();
    int i=0;
    while(query.next())
    {
        QString product_id = query.value(0).toString();
        double quality_r0 = GetRemainQuality(date_from, product_id);
        double quality_r1 = GetRemainQuality(date_to, product_id);
        double quality_in = GetInBetween(date_from,date_to,product_id);
        double quality_out = GetOutBetween(date_from, date_to, product_id);
        stock_model->setItem(i, 0, new QStandardItem(product_id));
        stock_model->setItem(i, 1, new QStandardItem(query.value(1).toString()+"/"+query.value(2).toString()));
        stock_model->setItem(i, 2, new QStandardItem(query.value(3).toString()));
        stock_model->setItem(i, 3, new QStandardItem(QString::number(quality_r0)));
        stock_model->setItem(i, 4, new QStandardItem(QString::number(quality_in)));
        stock_model->setItem(i, 5, new QStandardItem(QString::number(quality_out)));
        stock_model->setItem(i, 6, new QStandardItem(QString::number(quality_r1)));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(stock_model);
    sort_filter->sort (0);
    ui->table_stock->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_stock->setModel (sort_filter);
    ui->table_stock->setSortingEnabled(true);
    ui->table_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StockMainWindow::on_stock_query_clicked()
{
    stock_model->clear();
    stock_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号")));
    stock_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称/规格")));
    stock_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
    stock_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("上期结存")));
    stock_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库数")));
    stock_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出库数")));
    stock_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结存")));


    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        query.prepare("select id, name, specification, unit from product where id like :product_id");
        query.bindValue(":product_id", ui->sq_connent->text());
        break;
    case 1:
        query.prepare("select id, name, specification, unit from product where name like :product_name");
        query.bindValue(":product_name", ui->sq_connent->text());
        break;
    default:
        query.prepare("select id, name, specification, unit from product");
    }

    query.exec();

    QString date_from = ui->sqd_begin->text();
    QString date_to = ui->sqd_end->text();
    int i=0;
    while(query.next())
    {
        QString product_id = query.value(0).toString();
        double quality_r0 = GetRemainQuality(date_from, product_id);
        double quality_r1 = GetRemainQuality(date_to, product_id);
        double quality_in = GetInBetween(date_from,date_to,product_id);
        double quality_out = GetOutBetween(date_from, date_to, product_id);
        stock_model->setItem(i, 0, new QStandardItem(product_id));
        stock_model->setItem(i, 1, new QStandardItem(query.value(1).toString()+"/"+query.value(2).toString()));
        stock_model->setItem(i, 2, new QStandardItem(query.value(3).toString()));
        stock_model->setItem(i, 3, new QStandardItem(QString::number(quality_r0)));
        stock_model->setItem(i, 4, new QStandardItem(QString::number(quality_in)));
        stock_model->setItem(i, 5, new QStandardItem(QString::number(quality_out)));
        stock_model->setItem(i, 6, new QStandardItem(QString::number(quality_r1)));
        ++i;
    }
    sort_filter->clear();
    sort_filter->setSourceModel(stock_model);
    sort_filter->sort (0);
    ui->table_stock->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_stock->setModel (sort_filter);
    ui->table_stock->setSortingEnabled(true);
    ui->table_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void StockMainWindow::on_stock_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("保存Exel文件为"), "",
            tr("Excel文件 (*.xls);;所有文件 (*)"));
    if(fileName.length() != 0) {
        ExportExcel(fileName, sort_filter);
    }
}
