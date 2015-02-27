#include "ordermanagemainwindow.h"
#include "ui_ordermanagemainwindow.h"

#include <QtGui>
#include <QStandardItemModel>
#include "database.h"

OrderManageMainWindow::OrderManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderManageMainWindow)
{
    order_list_model = new QStandardItemModel();
    sort_filter = new QSortFilterProxyModel(this);
    ui->setupUi(this);
}

OrderManageMainWindow::~OrderManageMainWindow()
{
    delete sort_filter;
    delete order_list_model;
    delete ui;
}

void OrderManageMainWindow::reload_query()
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select * from order_list");

    order_list_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("订单号")));
    order_list_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("日期")));
    order_list_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("签收人")));
    order_list_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("经办人")));
    order_list_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("备注")));
    int i = 0;
    while (query.next()) {
        order_list_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        order_list_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        order_list_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        order_list_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        order_list_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(order_list_model);
    sort_filter->sort (0);

    ui->table_order_list->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_order_list->setModel (sort_filter);
    ui->table_order_list->setSortingEnabled(true);
    ui->table_order_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void OrderManageMainWindow::on_pushButton_clicked()
{
    QObject::connect(&addorder_dialog, SIGNAL(updateOrderQuery()),
                       this, SLOT(on_pushButton_4_clicked()));
    addorder_dialog.show();
}

void OrderManageMainWindow::on_pushButton_2_clicked()
{
    QItemSelectionModel *select = ui->table_order_list->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if (selected_index.size() == 0)
    {
        QMessageBox::information(this, "信息", "请先选中一条数据!");
        return;
    }
    int row_index = selected_index.at(0).row();

    OrderData order_data = {
         .id_s =ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,0)).toString(),
         .date_s = ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,1)).toString(),
         .sign_people_s = ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,2)).toString(),
         .operator_s = ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,3)).toString(),
         .remarks_s =ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,4)).toString()
    };

    modifyorder_dialog.setOrderData(order_data);
    modifyorder_dialog.show();
    modifyorder_dialog.setOriId(order_data.id_s);
    QObject::connect(&modifyorder_dialog, SIGNAL(updateOrderQuery()),
                       this, SLOT(on_pushButton_4_clicked()));
}

void OrderManageMainWindow::on_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->table_order_list->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if (selected_index.size() == 0)
    {
        QMessageBox::information(this, "信息", "请先选中一条数据!");
        return;
    }
    int row_index = selected_index.at(0).row();
    QString selected_id = ui->table_order_list->model()->data(ui->table_order_list->model()->index(row_index,0)).toString();
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("delete from order_list where id = :id");
    query.bindValue(":id", selected_id);
    if (QMessageBox::No == QMessageBox::question(this, "信息","删除该订单，将会删除所有该订单的相关信息，是否继续？",QMessageBox::Yes,QMessageBox::No))
    {
        return;
    }

    if(query.exec())
    {
        QMessageBox::information(this, "信息", "删除订单" + selected_id + "成功!");
    } else {
        QMessageBox::information(this, "信息", "删除订单" + selected_id + "失败!");
    }
    on_pushButton_4_clicked();
}

void OrderManageMainWindow::on_pushButton_4_clicked()
{
    int s_index = ui->comboBox->currentIndex();
    QString value = "%"+ui->lineEdit->text()+"%";
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    switch (s_index)
    {
    case 0:
        query.prepare("select * from order_list where id like :id");
        query.bindValue(":id", value);
        break;
    case 1:
        query.prepare("select * from order_list where date = :date");
        query.bindValue(":date", ui->lineEdit->text());
        break;
    case 2:
        query.prepare("select * from order_list where sign_people like :sign_people");
        query.bindValue(":sign_people", value);
        break;
    case 3:
        query.prepare("select * from order_list where operator like :operator");
        query.bindValue(":operator", value);
        break;
    case 4:
        query.prepare("select * from order_list where remarks like :remarks");
        query.bindValue(":remarks", value);
        break;
    default:
        query.prepare("select * from order_list");
    }
    query.exec();
    order_list_model->clear();
    order_list_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("订单编号")));
    order_list_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("日期")));
    order_list_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("签收人")));
    order_list_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("经办人")));
    order_list_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("备注")));
    int i = 0;
    while (query.next()) {
        order_list_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        order_list_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        order_list_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        order_list_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        order_list_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(order_list_model);
    sort_filter->sort (0);
    ui->table_order_list->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_order_list->setModel (sort_filter);
    ui->table_order_list->setSortingEnabled(true);
    ui->table_order_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
