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
    productmanagemainwindow.cpp \
    addproduct.cpp \
    product.cpp \
    modifyproduct.cpp \
    database.cpp \
    ordermanagemainwindow.cpp \
    addorder.cpp \
    modifyorder.cpp

HEADERS  += mainwindow.h \
    querymainwindow.h \
    inoutdialog.h \
    stockmainwindow.h \
    productmanagemainwindow.h \
    addproduct.h \
    product.h \
    dbcon.h \
    modifyproduct.h \
    database.h \
    ordermanagemainwindow.h \
    addorder.h \
    modifyorder.h

FORMS    += mainwindow.ui \
    querymainwindow.ui \
    inoutdialog.ui \
    stockmainwindow.ui \
    product_manage.ui \
    addproduct.ui \
    modifyproduct.ui \
    ordermanagemainwindow.ui \
    addorder.ui \
    modifyorderdialog.ui
