#include "productmanagemainwindow.h"

#include <QtGui>
#include <QStandardItemModel>

#include "ui_product_manage.h"
#include "product.h"
#include "database.h"

ProductManageMainWindow::ProductManageMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProductManageMainWindow)
{
    product_model = new QStandardItemModel();
    sort_filter = new QSortFilterProxyModel(this);
    ui->setupUi(this);
}

ProductManageMainWindow::~ProductManageMainWindow()
{
  delete sort_filter;
  delete product_model;
    delete ui;
}

void ProductManageMainWindow::reload_query()
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select * from product");
    product_model->clear();
    product_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号")));
    product_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称")));
    product_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
    product_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单价(元)")));
    product_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("规格")));
    product_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("库存")));
    product_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("备注")));
    int i = 0;
    while (query.next()) {
        product_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        product_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        product_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        product_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        product_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        product_model->setItem(i, 5, new QStandardItem(query.value(5).toString()));
        product_model->setItem(i, 6, new QStandardItem(query.value(6).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(product_model);
    sort_filter->sort (0);
    ui->table_product->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_product->setModel (sort_filter);
    ui->table_product->setSortingEnabled(true);
    ui->table_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ProductManageMainWindow::on_add_clicked()
{
    QObject::connect(&add_product_dialog, SIGNAL(updateProductQuery()),
                           this, SLOT(on_pushButton_clicked()));
    add_product_dialog.show();
}


void ProductManageMainWindow::on_modify_clicked()
{
    QItemSelectionModel *select = ui->table_product->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if (selected_index.size() == 0)
    {
        QMessageBox::information(NULL, "信息", "请先选中一条数据!");
        return;
    }
    int row_index = selected_index.at(0).row();
    ProductData pro_data = {
         .p_id_s =ui->table_product->model()->data(ui->table_product->model()->index(row_index,0)).toString(),
         .p_name_s = ui->table_product->model()->data(ui->table_product->model()->index(row_index,1)).toString(),
         .p_unit_s = ui->table_product->model()->data(ui->table_product->model()->index(row_index,2)).toString(),
         .p_price_s = ui->table_product->model()->data(ui->table_product->model()->index(row_index,3)).toString(),
         .p_specification_s = ui->table_product->model()->data(ui->table_product->model()->index(row_index,4)).toString(),
         .p_remain_s = ui->table_product->model()->data(ui->table_product->model()->index(row_index,5)).toString(),
         .p_remark_s =ui->table_product->model()->data(ui->table_product->model()->index(row_index,6)).toString()
    };

    modify_product_dialog.setProductData(pro_data);
    modify_product_dialog.show();
    modify_product_dialog.setOriId(pro_data.p_id_s);
    QObject::connect(&modify_product_dialog, SIGNAL(updateProductQuery()),
                           this, SLOT(on_pushButton_clicked()));
}

void ProductManageMainWindow::on_delete_2_clicked()
{
    QItemSelectionModel *select = ui->table_product->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if (selected_index.size() == 0)
    {
        QMessageBox::information(this, "信息", "请先选中一条数据!");
        return;
    }
    int row_index = selected_index.at(0).row();
    QString selected_id = ui->table_product->model()->data(ui->table_product->model()->index(row_index,0)).toString();
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("delete from product where id = :id");
    query.bindValue(":id", selected_id);

    if (QMessageBox::No == QMessageBox::question(this, "信息","删除该产品，将会删除所有该产品的相关信息，是否继续？",QMessageBox::Yes,QMessageBox::No))
    {
        return;
    }

    if(query.exec())
    {
        QMessageBox::information(this, "信息", "删除产品" + selected_id + "成功!");
    } else {
        QMessageBox::information(this, "信息", "删除产品" + selected_id + "失败!");
    }
    on_pushButton_clicked();
}

void ProductManageMainWindow::on_pushButton_clicked()
{
    int s_index = ui->comboBox->currentIndex();
    QString value = "%"+ui->lineEdit->text()+"%";
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    switch (s_index)
    {
    case 0:
        query.prepare("select * from product where id like :id");
        query.bindValue(":id", value);
        break;
    case 1:
        query.prepare("select * from product where name like :name");
        query.bindValue(":name", value);
        break;
    case 2:
        query.prepare("select * from product where id like :id or name like :name");
        query.bindValue(":id", value);
        query.bindValue(":name", value);
        break;
    default:
        query.prepare("select * from product");
    }
    query.exec();
    product_model->clear();
    product_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("产品编号")));
    product_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品名称")));
    product_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("单位")));
    product_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单价(元)")));
    product_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("规格")));
    product_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("库存")));
    product_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("备注")));
    int i = 0;
    while (query.next()) {
        product_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        product_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        product_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        product_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        product_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        product_model->setItem(i, 5, new QStandardItem(query.value(5).toString()));
        product_model->setItem(i, 6, new QStandardItem(query.value(6).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(product_model);
    sort_filter->sort (0);
    ui->table_product->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_product->setModel (sort_filter);
    ui->table_product->setSortingEnabled(true);
    ui->table_product->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
