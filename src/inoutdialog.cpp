#include "inoutdialog.h"
#include "ui_inoutdialog.h"

#include <QMessageBox>

#include "database.h"

InoutDialog::InoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InoutDialog)
{
    ui->setupUi(this);
}

InoutDialog::~InoutDialog()
{
    delete ui;
}

void InoutDialog::setOrderIds()
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

void InoutDialog::setProDuctInfo()
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

void InoutDialog::on_p_id_currentIndexChanged(int index)
{
    ui->p_name_spec->setCurrentIndex(index);
}

void InoutDialog::on_p_name_spec_currentIndexChanged(int index)
{
    ui->p_id->setCurrentIndex(index);
}

void InoutDialog::on_buttonBox_accepted()
{
    InOutData inout_data;
    if(getInOutData(inout_data))
        return;
    QString err_msg;
    if(ValidateInOutData(inout_data, err_msg))
    {
        QMessageBox::information(this, "信息",err_msg);
        return;
    }

    double quality_remain_ori = GetRemainQuality(inout_data.date_s, inout_data.product_id_s);
    inout_data.quality_remain_d = quality_remain_ori + inout_data.quality_change_d;
    if (inout_data.quality_remain_d < 0)
    {
        QMessageBox::information(this, "信息", "出库数量不能大于"+inout_data.date_s+"库存数量"
                                 +QString::number(quality_remain_ori)+"!");
        return;
    }
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    {
        QSqlQuery query(db);
        query.prepare("insert into inout(product_id, product_name, order_number, date, quality_change, quality_remain, abstract) values(:product_id, :product_name, :order_number, :date, :quality_change, :quality_remain, :abstract)");
        query.bindValue(":product_id", inout_data.product_id_s);
        query.bindValue(":product_name",inout_data.product_name_s);
        query.bindValue(":order_number", inout_data.order_number_s);
        query.bindValue(":date", inout_data.date_s);
        query.bindValue(":quality_change", inout_data.quality_change_d);
        query.bindValue(":quality_remain", inout_data.quality_remain_d);
        query.bindValue(":abstract", inout_data.abstract_s);
        if(query.exec())
        {
            QMessageBox::information(this, "信息", "成功添加产品："+inout_data.product_name_s + "至订单:"+ inout_data.order_number_s);
        }
        else {
            QMessageBox::information(this, "错误","添加出入库信息失败!请重新核对信息并重试!");
        }
    }
    QString msg;
    if(UpdateStocks(inout_data.date_s, inout_data.product_id_s,inout_data.quality_change_d, msg))
    {
        QMessageBox::information(this, "信息", msg);
    }
    emit updateInoutQuery();
    return;
}

int InoutDialog::getInOutData(InOutData &inout_data)
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
