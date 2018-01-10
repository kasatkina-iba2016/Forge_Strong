#-------------------------------------------------
#
# Project created by QtCreator 2017-04-10T22:50:59
#
#-------------------------------------------------

QT       += core gui sql
QT       += printsupport
QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Forge
TEMPLATE = app


SOURCES += main.cpp\
        facade.cpp \
    namelist.cpp \
    dialog.cpp \
    information.cpp \
    mainwindow.cpp \
    proxymodel.cpp \
    namedialog.cpp \
    audioplayer.cpp \
    calculator.cpp \
    authorizationUser.cpp

HEADERS  += facade.h \
    namelist.h \
    dialog.h \
    information.h \
    mainwindow.h \
    proxymodel.h \
    namedialog.h \
    audioplayer.h \
    calculator.h \
    authorizationUser.h

RESOURCES += \
    pict.qrc

DISTFILES +=

FORMS += \
    audioplayer.ui
