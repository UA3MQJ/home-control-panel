#-------------------------------------------------
#
# Project created by QtCreator 2015-01-08T23:17:26
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = lesson1
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    qcustomplot.cpp \
    qcustomplot2.cpp

HEADERS  += mywidget.h \
    qcustomplot.h \
    qcustomplot2.h

FORMS    += mywidget.ui
