#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "facade.h"
#include "calculator.h"
#include "audioplayer.h"
#include "aboutclass.h"
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
    ~MainWindow();
    Facade *fac;
    QMdiArea *mdiArea;
    QSignalMapper *signalMap;
    QMenu *mnuFile1,*mnuFile2,*mnuFile3,*mnuFile4;
    QToolBar *ptb1;
    QAction *saveAsAction,*exitAction,*printAction,*cascadeAction,*titleAction,
    *clientsAction,*serviceAction,*abonementAction,*audioAction,*calculatorAction,*aboutAction;
    audioPlayer *mySuperPlayer;
    Calculator *calculator;
    AboutClass *aboutMyprogramm;

public slots:

   void fileSaveAs();
   void print();
   void abonementSlot();
   void clientSlot();
   void serviceSlot();
   void audioSlot();
   void calculatorSlot();
   void aboutSlot();

};

#endif // MAINWINDOW_H
