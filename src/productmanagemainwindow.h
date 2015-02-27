#ifndef PRODUCT_MANAGE_H
#define PRODUCT_MANAGE_H

#include <QMainWindow>

#include <QtGui>
#include <QStandardItemModel>

#include "addproduct.h"
#include "modifyproduct.h"

namespace Ui {
class ProductManageMainWindow;
}

class ProductManageMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ProductManageMainWindow(QWidget *parent = 0);
    ~ProductManageMainWindow();
    void reload_query();
private slots:
    void on_add_clicked();

    void on_modify_clicked();

    void on_delete_2_clicked();

    void on_pushButton_clicked();
signals:
     void updateProductQuery(void);
private:
    Ui::ProductManageMainWindow *ui;
    QStandardItemModel *product_model;
    QSortFilterProxyModel *sort_filter;
    AddProductDialog add_product_dialog;
    ModifyProductDialog modify_product_dialog;
};

#endif // PRODUCT_MANAGE_H
