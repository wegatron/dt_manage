#ifndef INOUTDIALOG_H
#define INOUTDIALOG_H

#include <QDialog>

namespace Ui {
class InoutDialog;
}

class InoutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InoutDialog(QWidget *parent = 0);
    ~InoutDialog();
    
private:
    Ui::InoutDialog *ui;
};

#endif // INOUTDIALOG_H
