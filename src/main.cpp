#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("system"));
       QTextCodec::setCodecForCStrings(QTextCodec::codecForName("system"));
       QTextCodec::setCodecForLocale(QTextCodec::codecForName("system"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
