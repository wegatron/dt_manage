#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

struct ProductData {
    QString p_id_s;
    QString p_name_s;
    QString p_unit_s;
    QString p_price_s;
    QString p_specification_s;
    QString p_remain_s;
    QString p_remark_s;
};

/*
 * return 0 if data is ok, else return i means i'th data is bad
 **/
int ValidateProductData(const ProductData &pro_data,
                        QString &msg);

struct OrderData {
   QString id_s;
   QString date_s;
   QString sign_people_s;
   QString operator_s;
   QString remarks_s;
};

/*
 * return 0 if data is ok, else return i means i'th data is bad
 **/
int ValidateOrderData(const OrderData &order_data, QString &msg);

struct InOutData {
    int inout_id;
    QString product_id_s;
    QString product_name_s;
    QString order_number_s;
    QString date_s;
    double quality_change_d;
    double quality_remain_d;
    QString abstract_s;
};

/*
 * return 0 if data is ok, else return i means i'th data is bad
 **/
int ValidateInOutData(const InOutData &inout_data, QString &msg);

double GetRemainQuality(const QString &date, const QString &product_id);

int UpdateStocks(const QString &date, const QString &product_id, const double value, QString &err_msg);

double GetInBetween(const QString &date_from, const QString &date_to, const QString &product_id);

double GetOutBetween(const QString &date_from, const QString &date_to, const QString &product_id);

#endif // PRODUCT_H
