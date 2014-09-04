#include "addproduct.h"

#include <QMessageBox>
#include <QtSql>
#include "ui_addproduct.h"

#include "product.h"
#include "database.h"

AddProductDialog::AddProductDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddProductDialog)
{
    ui->setupUi(this);
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}

void AddProductDialog::on_buttonBox_accepted()
{
    ProductData pro_data;
    getProductData(pro_data);
    // validate data
    QString err_msg;
    if (ValidateProductData(pro_data,err_msg))
    {
        QMessageBox::information(this, "信息有误", err_msg);
        return;
    }

    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("insert into product(id, name, unit, price, specification, quality_remain, remarks) values(:id, :name, :unit, :price, :specification, :quality_remain, :remarks)");
    query.bindValue(":id", pro_data.p_id_s);
    query.bindValue(":name", pro_data.p_name_s);
    query.bindValue(":unit", pro_data.p_unit_s);
    query.bindValue(":price", pro_data.p_price_s);
    query.bindValue(":specification", pro_data.p_specification_s);
    query.bindValue(":quality_remain", pro_data.p_remain_s);
    query.bindValue(":remarks", pro_data.p_remark_s);

    if(query.exec())
    {
        QMessageBox::information(this, "信息", "添加产品成功!");
    } else {
        QMessageBox::information(this, "信息", "添加产品失败!");
    }
}

void AddProductDialog::setProductData(const ProductData &pro_data)
{
    ui->p_id->setText(pro_data.p_id_s);
    ui->p_name->setText(pro_data.p_name_s);
    ui->p_unit->setText(pro_data.p_unit_s);
    ui->p_price->setText(pro_data.p_price_s);
    ui->p_specification->setText(pro_data.p_specification_s);
    ui->p_remain->setText(pro_data.p_remain_s);
    ui->p_remarks->setText(pro_data.p_remark_s);
}

void AddProductDialog::getProductData(ProductData &pro_data)
{
    pro_data.p_id_s = ui->p_id->text();
    pro_data.p_name_s = ui->p_name->text();
    pro_data.p_unit_s = ui->p_unit->text();
    pro_data.p_price_s = ui->p_price->text();
    pro_data.p_specification_s = ui->p_specification->text();
    pro_data.p_remain_s = ui->p_remain->text();
    pro_data.p_remark_s = ui->p_remarks->text();
}
