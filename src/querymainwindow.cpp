#include "querymainwindow.h"
#include "ui_querymainwindow.h"

#include <QtGui>
#include <QStandardItemModel>

QueryMainWindow::QueryMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryMainWindow)
{
    ui->setupUi(this);
}

QueryMainWindow::~QueryMainWindow()
{
    delete ui;
}

void QueryMainWindow::reload_query()
{
    QStandardItemModel *inout_model = new QStandardItemModel();
    inout_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品")));
    inout_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("日期")));
    inout_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("内容摘要")));
    inout_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单号")));
    inout_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("入库数")));
    inout_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("发货数")));
    inout_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("领料")));
    inout_model->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("结存")));

    inout_model->setItem(0, 0, new QStandardItem("PPR热水管　25*4.2"));
    inout_model->setItem(0, 1, new QStandardItem("01/01/2011"));
    inout_model->setItem(0, 2, new QStandardItem("黄可振"));
    inout_model->setItem(0, 3, new QStandardItem("7560"));
    inout_model->setItem(0, 4, new QStandardItem(""));
    inout_model->setItem(0, 5, new QStandardItem("708"));
    inout_model->setItem(0, 6, new QStandardItem(""));
    inout_model->setItem(0, 7, new QStandardItem("5396"));

    inout_model->setItem(1, 0, new QStandardItem("PPR热水管　25*4.21"));
    inout_model->setItem(1, 1, new QStandardItem("01/01/2011"));
    inout_model->setItem(1, 2, new QStandardItem("黄可振"));
    inout_model->setItem(1, 3, new QStandardItem("7565"));
    inout_model->setItem(1, 4, new QStandardItem(""));
    inout_model->setItem(1, 5, new QStandardItem("708"));
    inout_model->setItem(1, 6, new QStandardItem(""));
    inout_model->setItem(1, 7, new QStandardItem("5396"));

    QSortFilterProxyModel *sort_filter = new QSortFilterProxyModel(this);
    sort_filter->setSourceModel(inout_model);
    sort_filter->sort (0);
    ui->table_inout->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_inout->setModel (sort_filter);
    ui->table_inout->setSortingEnabled(true);
}

void QueryMainWindow::on_inout_add_clicked()
{
    inout_dlg.show();
}
