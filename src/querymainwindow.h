#ifndef QUERYMAINWINDOW_H
#define QUERYMAINWINDOW_H

#include <vector>

#include <QMainWindow>
#include <QtGui>
#include <QStandardItemModel>

#include "inoutdialog.h"

#include "inoutmodify.h"

namespace Ui {
class QueryMainWindow;
}

class QueryMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QueryMainWindow(QWidget *parent = 0);
    void reload_query();
    ~QueryMainWindow();
    
private slots:

    void on_inout_add_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QStandardItemModel *inout_model;
    QSortFilterProxyModel *sort_filter;
    Ui::QueryMainWindow *ui;
    InoutDialog inout_dlg;
    InoutModifyDialog inout_modify_dlg;
};

#endif // QUERYMAINWINDOW_H
