#-------------------------------------------------
#
# Project created by QtCreator 2014-07-14T23:05:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dt_manage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    querymainwindow.cpp \
    inoutdialog.cpp \
    stockmainwindow.cpp \
    productmanagemainwindow.cpp

HEADERS  += mainwindow.h \
    querymainwindow.h \
    inoutdialog.h \
    stockmainwindow.h \
    productmanagemainwindow.h

FORMS    += mainwindow.ui \
    querymainwindow.ui \
    inoutdialog.ui \
    stockmainwindow.ui \
    product_manage.ui
