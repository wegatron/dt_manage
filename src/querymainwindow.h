#ifndef QUERYMAINWINDOW_H
#define QUERYMAINWINDOW_H

#include <QMainWindow>

#include "inoutdialog.h"

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

private:
    Ui::QueryMainWindow *ui;
    InoutDialog inout_dlg;
};

#endif // QUERYMAINWINDOW_H
