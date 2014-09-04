#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>
#include "product.h"

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddProductDialog(QWidget *parent = 0);
    ~AddProductDialog();
    void setProductData(const ProductData &pro_data);
    void getProductData(ProductData &pro_data);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddProductDialog *ui;
};

#endif // ADDPRODUCT_H
