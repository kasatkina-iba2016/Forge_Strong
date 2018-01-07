#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "facade.h"
#include "calculator.h"
#include <QMainWindow>
#include <QActionGroup>
#include <QMenu>
#include <QMenuBar>
#include <QMdiArea>
#include <QSignalMapper>
#include <QtPrintSupport/QPrinter>
#include "audioplayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Facade *fac;
    QMdiArea *mdiArea;
    QSignalMapper *signalMap;
    QMenu *mnuFile1,*mnuFile2,*mnuFile4,*mnuFile5;
    QToolBar *ptb1;
    QAction *saveAsAction,*exitAction,*printAction,*cascadeAction,*titleAction,
    *clientsAction,*serviceAction,*abonementAction,*audioAction,*calculatorAction;
    audioPlayer *mySuperPlayer;
    Calculator *calculator;

public slots:
   void fileOpen();
   void fileSaveAs();
   void print();
   void abonementSlot();
   void clientSlot();
   void serviceSlot();
   void audioSlot();
   void calculatorSlot();

};

#endif // MAINWINDOW_H
