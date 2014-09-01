#ifndef PRODUCT_MANAGE_H
#define PRODUCT_MANAGE_H

#include <QMainWindow>

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
private:
    Ui::ProductManageMainWindow *ui;
};

#endif // PRODUCT_MANAGE_H
