#ifndef MODIFYORDER_H
#define MODIFYORDER_H

#include <QDialog>
#include "product.h"

namespace Ui {
class ModifyOrderDialog;
}

class ModifyOrderDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModifyOrderDialog(QWidget *parent = 0);
    ~ModifyOrderDialog();
    void setOrderData(const OrderData &order_data);
    void getOrderData(OrderData &order_data);
    void setOriId(const QString &id) { ori_id = id; }
private slots:
    void on_buttonBox_accepted();
signals:
     void updateOrderQuery(void);
private:
    Ui::ModifyOrderDialog *ui;
    QString ori_id;
};

#endif // MODIFYORDER_H
