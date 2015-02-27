#ifndef STOCKMAINWINDOW_H
#define STOCKMAINWINDOW_H

#include <string>

#include <QMainWindow>

#include <QtGui>
#include <QStandardItemModel>

namespace Ui {
class StockMainWindow;
}

class StockMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit StockMainWindow(QWidget *parent = 0);
    ~StockMainWindow();
    void reload_query();
private slots:
    void on_stock_query_clicked();

    void on_stock_export_clicked();

private:
    std::string query_remarks; // for exported excel
    QStandardItemModel *stock_model;
    QSortFilterProxyModel *sort_filter;
    Ui::StockMainWindow *ui;
};

#endif // STOCKMAINWINDOW_H
