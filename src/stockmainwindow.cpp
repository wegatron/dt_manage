#include "stockmainwindow.h"

#include <QtGui>
#include <QStandardItemModel>

#include "ui_stockmainwindow.h"

StockMainWindow::StockMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StockMainWindow)
{
    ui->setupUi(this);
}

StockMainWindow::~StockMainWindow()
{
    delete ui;
}

void StockMainWindow::reload_query()
{
    QStandardItemModel *stock_model = new QStandardItemModel();
    stock_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品代号")));
    stock_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称")));
    stock_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
    stock_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("上期结存")));
    stock_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库数")));
    stock_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("出库数")));
    stock_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结存")));
    stock_model->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("备注")));

    stock_model->setItem(0, 0, new QStandardItem("20*2.3"));
    stock_model->setItem(0, 1, new QStandardItem("PPR-冷水管"));
    stock_model->setItem(0, 2, new QStandardItem("米"));
    stock_model->setItem(0, 3, new QStandardItem("20660"));
    stock_model->setItem(0, 4, new QStandardItem("2692"));
    stock_model->setItem(0, 5, new QStandardItem("3600"));
    stock_model->setItem(0, 6, new QStandardItem("19752"));
    stock_model->setItem(0, 7, new QStandardItem("8000"));

    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setSourceModel(stock_model);
    sort_filter->sort (0);
    ui->table_stock->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_stock->setModel (sort_filter);
    ui->table_stock->setSortingEnabled(true);
}
