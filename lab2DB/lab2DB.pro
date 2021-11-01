#-------------------------------------------------
#
# Project created by QtCreator 2020-10-19T13:54:50
#insert into base_beverages values
#(1, 'beer', 35, 57)
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab2DB
TEMPLATE = app

QTPLUGIN += QPSQL

SOURCES += main.cpp\
        mainwindow.cpp \
    initialization.cpp

HEADERS  += mainwindow.h \
    initialization.h

FORMS    += mainwindow.ui \
    initialization.ui
