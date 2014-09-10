#ifndef ORDERMANAGEMAINWINDOW_H
#define ORDERMANAGEMAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QStandardItemModel>

#include "addorder.h"
#include "modifyorder.h"

namespace Ui {
class OrderManageMainWindow;
}

class OrderManageMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OrderManageMainWindow(QWidget *parent = 0);
    ~OrderManageMainWindow();
    void reload_query();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::OrderManageMainWindow *ui;
    QStandardItemModel *order_list_model;
    QSortFilterProxyModel *sort_filter;
    AddOrderDialog addorder_dialog;
    ModifyOrderDialog modifyorder_dialog;
};

#endif // ORDERMANAGEMAINWINDOW_H
