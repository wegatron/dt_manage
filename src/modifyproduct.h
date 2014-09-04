#ifndef MODIFYPRODUCT_H
#define MODIFYPRODUCT_H

#include <QDialog>
#include "product.h"

namespace Ui {
class ModifyProductDialog;
}

class ModifyProductDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModifyProductDialog(QWidget *parent = 0);
    ~ModifyProductDialog();
    void setProductData(const ProductData &pro_data);
    void getProductData(ProductData &pro_data);
    void setOriId(const QString &p_id_s) { ori_id = p_id_s; }
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ModifyProductDialog *ui;
    QString ori_id; // origional id of the modifying infomation
};

#endif // MODIFYPRODUCT_H
