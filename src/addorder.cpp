#include "addorder.h"
#include "ui_addorder.h"

#include <QMessageBox>

#include "database.h"

AddOrderDialog::AddOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddOrderDialog)
{
    ui->setupUi(this);
}

AddOrderDialog::~AddOrderDialog()
{
    delete ui;
}

void AddOrderDialog::on_buttonBox_accepted()
{
    OrderData order_data;
    getOrderData(order_data);
    // validate data
    QString err_msg;
    if (ValidateOrderData(order_data,err_msg))
    {
        QMessageBox::information(this, "信息有误", err_msg);
        return;
    }

    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("insert into order_list(id, date, sign_people, operator, remarks) values(:id, :date, :sign_people, :operator, :remarks)");
    query.bindValue(":id", order_data.id_s);
    query.bindValue(":date",order_data.date_s);
    query.bindValue(":sign_people", order_data.sign_people_s);
    query.bindValue(":operator", order_data.operator_s);
    query.bindValue(":remarks", order_data.remarks_s);

    if(query.exec())
    {
        QMessageBox::information(this, "信息", "添加订单成功!");
    } else {
        QMessageBox::information(this, "信息", "添加订单失败!");
    }
    emit updateOrderQuery();
}

void AddOrderDialog::getOrderData(OrderData &order_data)
{
    order_data.id_s = ui->id->text();
    order_data.date_s = ui->date->text();
    order_data.operator_s = ui->operator_2->text();
    order_data.sign_people_s = ui->sign_people->text();
    order_data.remarks_s = ui->remark->text();
}
