#ifndef ORDERMANAGEMAINWINDOW_H
#define ORDERMANAGEMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class OrderManageMainWindow;
}

class OrderManageMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit OrderManageMainWindow(QWidget *parent = 0);
    ~OrderManageMainWindow();
    
private:
    Ui::OrderManageMainWindow *ui;
};

#endif // ORDERMANAGEMAINWINDOW_H
