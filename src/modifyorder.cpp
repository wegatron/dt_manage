#include "modifyorder.h"
#include "ui_modifyorderdialog.h"

#include <QMessageBox>

#include "database.h"

ModifyOrderDialog::ModifyOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyOrderDialog)
{
    ui->setupUi(this);
}

ModifyOrderDialog::~ModifyOrderDialog()
{
    delete ui;
}

void ModifyOrderDialog::setOrderData(OrderData &order_data)
{
    ui->id->setText(order_data.id_s);
    QDate date = QDate::fromString ( order_data.date_s, "yyyy'-'MM'-'dd" );
    ui->date->setDate(date);
    ui->sign_people->setText(order_data.sign_people_s);;
    ui->operator_2->setText(order_data.operator_s);
    ui->remark->setText(order_data.remarks_s);
}

void ModifyOrderDialog::getOrderData(OrderData &order_data)
{
    order_data.id_s =  ui->id->text();
    order_data.date_s = ui->date->text();
    order_data.sign_people_s = ui->sign_people->text();
    order_data.operator_s = ui->operator_2->text();
    order_data.remarks_s = ui->remark->text();
}

void ModifyOrderDialog::on_buttonBox_accepted()
{
    OrderData order_data;
    getOrderData(order_data);
    QString err_msg;
    if(ValidateOrderData(order_data, err_msg))
    {
        QMessageBox::information(this,"错误信息",err_msg);
        return;
    }

    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);

    query.prepare("update order_list set id = :id, date = :date, sign_people = :sign_people, operator = :operator, remarks = :remarks  where id = :ori_id");
    query.bindValue(":id", order_data.id_s);
    query.bindValue(":date", order_data.date_s);
    query.bindValue(":sign_people", order_data.sign_people_s);
    query.bindValue(":operator", order_data.operator_s);
    query.bindValue(":remarks", order_data.remarks_s);
    query.bindValue(":ori_id", ori_id);

    if(query.exec())
    {
        QMessageBox::information(this, "信息", "修改订单成功!");
    } else {
        QMessageBox::information(this, "信息", "修改订单失败!");
    }
}
