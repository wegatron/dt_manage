#include "inoutmodify.h"
#include "ui_inoutmodify.h"

#include <QMessageBox>
#include <assert.h>
#include "database.h"

InoutModifyDialog::InoutModifyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InoutModifyDialog)
{
    ui->setupUi(this);
}

InoutModifyDialog::~InoutModifyDialog()
{
    delete ui;
}

void InoutModifyDialog::setOrderIds()
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select id, date from order_list");
    ui->order_id->clear();
    order_date_v.clear();
    while(query.next())
    {
        ui->order_id->addItem(query.value(0).toString());
        order_date_v.push_back(query.value(1).toString());
    }
}

void InoutModifyDialog::setProDuctInfo()
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.exec("select id, name, specification from product");
    ui->p_id->clear();
    ui->p_name_spec->clear();
    product_name_v.clear();
    while(query.next())
    {
        ui->p_id->addItem(query.value(0).toString());
        ui->p_name_spec->addItem(query.value(1).toString()+"/"+query.value(2).toString());
        product_name_v.push_back(query.value(1).toString()+"/"+query.value(2).toString());
    }
}

int InoutModifyDialog::getInOutData(InOutData &inout_data)
{
    if(ui->p_id->currentText() != ui->p_id->itemText(ui->p_id->currentIndex()))
    {
        QMessageBox::information(this, "信息", "没有编号为"+ui->p_id->currentText()+"的产品!");
        return -1;
    }

    inout_data.product_id_s = ui->p_id->currentText();
    inout_data.product_name_s = product_name_v.at(ui->p_id->currentIndex());
    inout_data.order_number_s = ui->order_id->currentText();
    inout_data.date_s = order_date_v.at(ui->order_id->currentIndex());
    bool ok = false;
    inout_data.quality_change_d = ui->quality_change->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::information(this, "信息", "出入库数量:"+ui->quality_change->text()+"不是一个有效数值!");
        return -1;
    }
    inout_data.quality_remain_d = 0;
    inout_data.abstract_s = ui->abstract_2->text();
    return 0;
}

void InoutModifyDialog::setInOutData(const InOutData &inout_data)
{
    int n_pid = ui->p_id->count();
    int pid_index = 0;
    for(; pid_index<n_pid; ++pid_index)
    {
        if(inout_data.product_id_s.compare(ui->p_id->itemText(pid_index)) == 0)
        {
            break;
        }
    }
    assert(pid_index<n_pid);
    ui->p_id->setCurrentIndex(pid_index);
    ui->p_name_spec->setCurrentIndex(pid_index);

    int n_order_id = ui->order_id->count();
    int order_index=0;

    for(;order_index<n_order_id; ++order_index)
    {
        if(inout_data.order_number_s.compare(ui->order_id->itemText(order_index)) == 0)
        {
            break;
        }
    }
    assert(order_index<n_order_id);
    ui->order_id->setCurrentIndex(order_index);
    ui->quality_change->setText(QString::number(inout_data.quality_change_d));
    ui->abstract_2->setText(inout_data.abstract_s);
    inout_id = inout_data.inout_id;
    quality_change = inout_data.quality_change_d;
    date = inout_data.date_s;
    product_id = inout_data.product_id_s;
    quality_remain = inout_data.quality_remain_d;
}

void InoutModifyDialog::init()
{
    setProDuctInfo();
    setOrderIds();
}

void InoutModifyDialog::on_buttonBox_accepted()
{
    InOutData inout_data;
    getInOutData(inout_data);
    QString err_msg;
    if(ValidateInOutData(inout_data, err_msg))
    {
        QMessageBox::information(this,"错误信息",err_msg);
        return;
    }

    if (UpdateStocks(date, product_id, -quality_change, err_msg))
    {
        QMessageBox::information(this, "信息",err_msg);
        return;
    }

    double quality_remain = GetRemainQuality(inout_data.date_s, inout_data.product_id_s);
    inout_data.quality_remain_d = quality_remain + inout_data.quality_change_d;
    if(inout_data.quality_remain_d < 0)
    {
        QMessageBox::information(this, "警告","出库导致产品"+inout_data.product_id_s
                                 +"在"+inout_data.date_s+"库存为负！");
    }
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    {
        QSqlQuery query(db);

        query.prepare("update inout set product_id = :product_id, product_name = :product_name, order_number = :order_number, date = :date, quality_change = :quality_change, quality_remain = :quality_remain, abstract = :abstract  where id = :ori_id");
        query.bindValue(":product_id", inout_data.product_id_s);
        query.bindValue(":product_name", inout_data.product_name_s);
        query.bindValue(":order_number", inout_data.order_number_s);
        query.bindValue(":date", inout_data.date_s);
        query.bindValue(":quality_change", inout_data.quality_change_d);
        query.bindValue(":quality_remain", inout_data.quality_remain_d);
        query.bindValue(":abstract",inout_data.abstract_s);
        query.bindValue(":id", inout_id);

        if(query.exec())
        {
            QMessageBox::information(this, "信息", "修改出入库信息成功!");
        } else {
            QMessageBox::information(this, "信息", "修改出入库信息失败!");
        }
    }

    if(UpdateStocks(inout_data.date_s, inout_data.product_id_s, inout_data.quality_change_d, err_msg))
    {
        QMessageBox::information(this, "信息", err_msg);
        return;
    }
    emit updateInoutQuery();
}
