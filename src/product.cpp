#include "product.h"

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
