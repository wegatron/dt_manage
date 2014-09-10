#ifndef INOUTDIALOG_H
#define INOUTDIALOG_H

#include <QDialog>
#include <vector>

#include "product.h"

namespace Ui {
class InoutDialog;
}

class InoutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InoutDialog(QWidget *parent = 0);
    ~InoutDialog();
    void setOrderIds();
    void setProDuctInfo();
    int getInOutData(InOutData &inout_data);

private slots:
    void on_p_id_currentIndexChanged(int index);

    void on_p_name_spec_currentIndexChanged(int index);

    void on_buttonBox_accepted();

private:
    Ui::InoutDialog *ui;
    std::vector<QString> order_date_v;
    std::vector<QString> product_name_v;
};

#endif // INOUTDIALOG_H
