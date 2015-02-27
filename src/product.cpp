#include "product.h"

#include "database.h"

int ValidateProductData(const ProductData &pro_data, QString &msg)
{
    if(pro_data.p_id_s.length()==0)
    {
        msg = QString("产品编号不能为空！");
        return 1;
    }

    if(pro_data.p_name_s.length()==0)
    {
        msg = QString("产品名称不能为空!");
        return 2;
    }

    if(pro_data.p_unit_s.length()==0)
    {
        msg = QString("产品单位不能为空!");
        return 3;
    }
    bool ok = false;
    pro_data.p_price_s.toDouble(&ok);
    if (!ok)
    {
        msg = QString("产品单价必须是数值！");
        return 4;
    }

    if(pro_data.p_specification_s.length()==0)
    {
        msg = QString("规格不能为空!");
        return 5;
    }

    ok = false;
    pro_data.p_remain_s.toDouble(&ok);
    if(!ok)
    {
        msg = QString("现有库存必须是一个数值！");
        return 6;
    }
    return 0;
}

int ValidateOrderData(const OrderData &order_data, QString &msg)
{
    if(order_data.id_s.length()==0)
    {
        msg = QString("订单编号不能为空！");
        return 1;
    }

    if(order_data.sign_people_s.length()==0)
    {
        msg = QString("签收人不能为空！");
        return 3;
    }

    if(order_data.operator_s.length()==0)
    {
        msg = QString("经办人不能为空！");
        return 4;
    }
    return 0;
}

int ValidateInOutData(const InOutData &inout_data, QString &msg)
{
    if(inout_data.product_id_s.length() == 0)
    {
        msg = "产品编号不能为空!";
        return 1;
    }

    if(inout_data.product_name_s.length() == 0)
    {
        msg = "产品名称不能为空!";
        return 2;
    }

    if(inout_data.order_number_s.length() == 0)
    {
        msg = "订单编号不能为空!";
        return 3;
    }

    if(inout_data.date_s.length() == 0)
    {
        msg = "日期不能为空!";
        return 4;
    }

    if(inout_data.quality_change_d < 1e-2 && inout_data.quality_change_d > -1e-2)
    {
        msg = "出入库不能为0!";
        return 5;
    }

    if(inout_data.quality_remain_d < 0)
    {
        msg ="结存不能为负!" ;
        return 6;
    }
    return 0;
}

int UpdateStocks(const QString &date, const QString &product_id, const double value, QString &err_msg)
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    {
        QSqlQuery query(db);
        query.prepare("update product set quality_remain = quality_remain+:value where id = :id");
        query.bindValue(":value", value);
        query.bindValue(":id", product_id);
        if(!query.exec())
        {
            err_msg = "更新产品:"+ product_id + "现有库存出错!";
            return 1;
        }
    }
    {
        QSqlQuery query(db);
        query.prepare("update inout set quality_remain = quality_remain+:value where product_id = :product_id and date > date('"
                      + date +"')");
        query.bindValue(":value", value);
        query.bindValue(":product_id",product_id);
        if (!query.exec())
        {
            err_msg = "更新产品:"+product_id +"定期结存出错!";
            return 2;
        }
    }
    return 0;
}

double GetRemainQuality(const QString &date, const QString &product_id)
{
    double quality_remain = 0;
    bool flag = false;
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    {
        QSqlQuery query(db);
        query.prepare("select quality_remain, quality_change, min(date) from inout where date > date('"
                      +date
                      +"') and product_id=:product_id");
        query.bindValue(":product_id", product_id);
        query.exec(); query.next();
        if(!query.isNull(0) )
        {
            quality_remain = query.value(0).toDouble() - query.value(1).toDouble();
            flag = true;
        }
    }
    if(!flag)
    {
        QSqlQuery query(db);
        query.prepare("select quality_remain from product where id = :product_id");
        query.bindValue(":product_id", product_id);
        query.exec(); query.next();
        quality_remain = query.value(0).toDouble();
    }
    return quality_remain;
}

double GetInBetween(const QString &date_from, const QString &date_to, const QString &product_id)
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("select sum(quality_change) from inout where quality_change>0 and product_id = :product_id and date between date('"
                  +date_from+"') and date('"+ date_to+"')");
    query.bindValue(":product_id", product_id);
    query.exec(); query.next();
    if(query.isNull(0)) {
        return 0.0;
    } else {
        return query.value(0).toDouble();
    }
}

double GetOutBetween(const QString &date_from, const QString &date_to, const QString &product_id)
{
    QSqlDatabase &db = DtDataBase::getDtDataBase();
    QSqlQuery query(db);
    query.prepare("select sum(quality_change) from inout where quality_change<0 and product_id = :product_id and date between date('"
                  +date_from+"') and date('"+ date_to+"')");
    query.bindValue(":product_id", product_id);
    query.exec(); query.next();
    if(query.isNull(0)) {
        return 0.0;
    } else {
        return -query.value(0).toDouble();
    }
}
