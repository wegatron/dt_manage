#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include "querymainwindow.h"
#include "stockmainwindow.h"
#include "productmanagemainwindow.h"
#include "ordermanagemainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QueryMainWindow query_window;
    StockMainWindow stock_window;
    ProductManageMainWindow product_manage_window;
    OrderManageMainWindow order_manage_window;
};

#endif // MAINWINDOW_H
