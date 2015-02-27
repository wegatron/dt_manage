#include "querymainwindow.h"
#include "ui_querymainwindow.h"

#include <QtGui>
#include <QStandardItemModel>
#include <iostream>

#include "database.h"

#include "excel.h"

QueryMainWindow::QueryMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryMainWindow)
{
    inout_model = new QStandardItemModel();
    sort_filter = new QSortFilterProxyModel(this);
    ui->setupUi(this);
}

QueryMainWindow::~QueryMainWindow()
{
  delete sort_filter;
  delete inout_model;
  delete ui;
}

void QueryMainWindow::reload_query()
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select * from inout");

    inout_model->clear();
    inout_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("信息编号")));
    inout_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品编号")));
    inout_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("产品名称")));
    inout_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单号")));
    inout_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("日期")));
    inout_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("库存变化")));
    inout_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结存")));
    inout_model->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("内容摘要")));

    int i = 0;
    while (query.next()) {
        inout_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        inout_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        inout_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        inout_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        inout_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        inout_model->setItem(i, 5, new QStandardItem(query.value(5).toString()));
        inout_model->setItem(i, 6, new QStandardItem(query.value(6).toString()));
        inout_model->setItem(i, 7, new QStandardItem(query.value(7).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(inout_model);
    sort_filter->sort (0);

    ui->table_inout->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_inout->setModel (sort_filter);
    ui->table_inout->setSortingEnabled(true);
    ui->table_inout->setEditTriggers(QAbstractItemView::NoEditTriggers);
    query_remarks = "所有出入库信息";
}

void QueryMainWindow::on_inout_add_clicked()
{
    inout_dlg.setOrderIds();
    inout_dlg.setProDuctInfo();
    inout_dlg.show();
    QObject::connect(&inout_dlg, SIGNAL(updateInoutQuery()),
                           this, SLOT(on_pushButton_2_clicked()));
}

void QueryMainWindow::on_pushButton_3_clicked()
{
    QItemSelectionModel *select = ui->table_inout->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if(selected_index.size()==0)
    {
      QMessageBox::information(this, "信息", "请选中一条信息!");
      return;
    }
    int row_index = selected_index.at(0).row();
    InOutData inout_data = {
        .inout_id = ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 0)).toInt(),
        .product_id_s=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 1)).toString(),
        .product_name_s=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index,2)).toString(),
        .order_number_s=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 3)).toString(),
        .date_s=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index,4)).toString(),
        .quality_change_d=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index,5)).toDouble(),
        .quality_remain_d=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index,6)).toDouble(),
        .abstract_s=ui->table_inout->model()->data(ui->table_inout->model()->index(row_index,7)).toString()
    };

    inout_modify_dlg.init();
    inout_modify_dlg.setInOutData(inout_data);
    inout_modify_dlg.show();
    QObject::connect(&inout_modify_dlg, SIGNAL(updateInoutQuery()),
                           this, SLOT(on_pushButton_2_clicked()));
}

void QueryMainWindow::on_pushButton_clicked()
{
    QItemSelectionModel *select = ui->table_inout->selectionModel();
    QModelIndexList selected_index = select->selectedRows();
    if(selected_index.size() == 0)
    {
        QMessageBox::information(this, "信息","请选中一条信息!");
        return;
    }
    int row_index = selected_index.at(0).row();
    int inout_id = ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 0)).toInt();
    QString product_id = ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 1)).toString();
    QString date = ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 4)).toString();
    double quality_change = ui->table_inout->model()->data(ui->table_inout->model()->index(row_index, 5)).toDouble();
    QString err_msg;
    if(UpdateStocks(date, product_id, -quality_change, err_msg))
    {
        QMessageBox::information(this, "错误信息", err_msg);
        return;
    }

    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("delete from inout where id = :id");
    query.bindValue(":id", inout_id);

    if (QMessageBox::No == QMessageBox::question(this, "信息","删除该出入库信息是否继续？",QMessageBox::Yes,QMessageBox::No))
    {
        return;
    }
    if(query.exec())
    {
        QMessageBox::information(this, "信息","删除出入库信息成功!");
    } else {
        QMessageBox::information(this, "信息", "删除出入库信息失败!");
    }
    on_pushButton_2_clicked();
}

void QueryMainWindow::on_pushButton_2_clicked()
{
    QString value = "%" + ui->lineEdit->text() + "%";
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    QString prepare_str = "select * from inout where date between date('"
            +ui->dateEdit->text()+"') and date('"
            +ui->dateEdit_2->text()+"')";
    switch(ui->comboBox->currentIndex())
    {
    case 1:
        query.prepare(prepare_str+"and product_id like :product_id");
        query.bindValue(":product_id",value);
        query_remarks = "从"+ui->dateEdit->text().toStdString()+
                "到"+ui->dateEdit_2->text().toStdString()+"产品编号包含"+ui->lineEdit->text().toStdString()+"的出入库信息";
        break;
    case 2:
        query.prepare(prepare_str+"and product_name like :product_name");
        query.bindValue(":product_name",value);
        query_remarks = "从"+ui->dateEdit->text().toStdString()+"到"+
                ui->dateEdit_2->text().toStdString()+"产品名称包含"+ui->lineEdit->text().toStdString()+"的出入库信息";
        break;
    case 3:
        query.prepare(prepare_str+"and order_number like :order_number");
        query.bindValue(":order_number",value);
        query_remarks = "从"+ui->dateEdit->text().toStdString()+
                "到"+ui->dateEdit_2->text().toStdString()+"产品编号单号"+ui->lineEdit->text().toStdString()+"的出入库信息";
        break;
    default: // 0
        query.prepare(prepare_str);
        query_remarks = "从"+ui->dateEdit->text().toStdString()+
                "到"+ui->dateEdit_2->text().toStdString()+"的出入库信息";
        break;
    }
    query.exec();
    inout_model->clear();
    inout_model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("信息编号")));
    inout_model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("产品编号")));
    inout_model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("产品名称/规格")));
    inout_model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("单号")));
    inout_model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("日期")));
    inout_model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("库存变化")));
    inout_model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("结存")));
    inout_model->setHorizontalHeaderItem(7, new QStandardItem(QObject::tr("内容摘要")));

    int i = 0;
    while (query.next()) {
        inout_model->setItem(i, 0, new QStandardItem(query.value(0).toString()));
        inout_model->setItem(i, 1, new QStandardItem(query.value(1).toString()));
        inout_model->setItem(i, 2, new QStandardItem(query.value(2).toString()));
        inout_model->setItem(i, 3, new QStandardItem(query.value(3).toString()));
        inout_model->setItem(i, 4, new QStandardItem(query.value(4).toString()));
        inout_model->setItem(i, 5, new QStandardItem(query.value(5).toString()));
        inout_model->setItem(i, 6, new QStandardItem(query.value(6).toString()));
        inout_model->setItem(i, 7, new QStandardItem(query.value(7).toString()));
        ++i;
    }

    sort_filter->clear();
    sort_filter->setSourceModel(inout_model);
    sort_filter->sort (0);

    ui->table_inout->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->table_inout->setModel (sort_filter);
    ui->table_inout->setSortingEnabled(true);
    ui->table_inout->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void QueryMainWindow::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("保存Exel文件为"), "",
            tr("Excel文件 (*.csv);;所有文件 (*)"));
    std::string header = "信息编号,产品编号,产品名称/规格,单号,日期,库存变化,结存,内容摘要";
    if(fileName.length() != 0) {
        ExportExcel(fileName, sort_filter, header, query_remarks);
    }
}
