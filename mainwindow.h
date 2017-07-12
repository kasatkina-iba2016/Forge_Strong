#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "facade.h"
#include <QMainWindow>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QSignalMapper>
#include <QtPrintSupport/QPrinter>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    Facade *fac;
    QMdiArea *mdiArea;
    QSignalMapper *signalMap;
    QMenu *mnuFile1,*mnuFile2,*mnuFile4,*mnuFile5;
    QToolBar *ptb1;//,*ptb2,*ptb3,*ptb4,*ptb5;
    QAction *saveAsAction,*exitAction,*printAction,*cascadeAction,
    *clientsAction,*serviceAction,*abonementAction;

signals:

public slots:
   void fileOpen();
   void fileSaveAs();
   void print();
   void abonementSlot();
   void clientSlot();
   void serviceSlot();
};

#endif // MAINWINDOW_H
