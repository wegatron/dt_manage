#ifndef STOCKMAINWINDOW_H
#define STOCKMAINWINDOW_H

#include <QMainWindow>

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
private:
    Ui::StockMainWindow *ui;
};

#endif // STOCKMAINWINDOW_H
