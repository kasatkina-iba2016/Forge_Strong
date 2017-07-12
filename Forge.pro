#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T22:50:59
#
#-------------------------------------------------

QT       += core gui sql
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Forge
TEMPLATE = app


SOURCES += main.cpp\
        facade.cpp \
    namelist.cpp \
    dialog.cpp \
    information.cpp \
    mainwindow.cpp \
    proxymodel.cpp

HEADERS  += facade.h \
    namelist.h \
    dialog.h \
    information.h \
    mainwindow.h \
    proxymodel.h

RESOURCES += \
    pict.qrc

DISTFILES +=
