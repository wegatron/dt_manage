#ifndef ADDORDER_H
#define ADDORDER_H

#include <QDialog>
#include "product.h"

namespace Ui {
class AddOrderDialog;
}

class AddOrderDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddOrderDialog(QWidget *parent = 0);
    ~AddOrderDialog();
    void getOrderData(OrderData &order_data);
private slots:
    void on_buttonBox_accepted();

signals:
     void updateOrderQuery(void);

private:
    Ui::AddOrderDialog *ui;
};

#endif // ADDORDER_H
