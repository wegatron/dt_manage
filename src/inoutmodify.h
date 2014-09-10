#ifndef INOUTMODIFY_H
#define INOUTMODIFY_H

#include <QDialog>

#include "product.h"

namespace Ui {
class InoutModifyDialog;
}

class InoutModifyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InoutModifyDialog(QWidget *parent = 0);
    ~InoutModifyDialog();
    void init();
    int getInOutData(InOutData &inout_data);
    void setInOutData(const InOutData &inout_data);
private slots:
    void on_buttonBox_accepted();

private:
    void setOrderIds();
    void setProDuctInfo();
    int inout_id;
    double quality_change;
    double quality_remain;
    QString date;
    QString product_id;
    Ui::InoutModifyDialog *ui;
    std::vector<QString> order_date_v;
    std::vector<QString> product_name_v;
};

#endif // INOUTMODIFY_H
