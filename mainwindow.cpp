#include "mainwindow.h"
#include "namelist.h"
#include <QLayout>
#include <QFile>
#include <QTextStream>
#include <facade.h>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   this->setWindowTitle("Кузня");
   this->setWindowIcon(QPixmap(":/Pict/dumbbell_PNG16366.png"));
   fac= new Facade("MainWindowTable", this);
   //fac->setWindowTitle("Список абонементов");
   fac->setAttribute(Qt::WA_DeleteOnClose);
   fac->setWindowIcon(QPixmap(":/Pict/dumbbell_PNG16366.png"));
   mdiArea=new QMdiArea;
   mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
   mdiArea->addSubWindow(fac);

   signalMap=new QSignalMapper(this);
   //connect(signalMap,SIGNAL(mapped(QWidget*)),this,SLOT()

   mnuFile1=new QMenu("&Файл");
   mnuFile2=new QMenu("&Справочниики");
   mnuFile4=new QMenu("&Окна");
   mnuFile5=new QMenu("&Помощь");

   saveAsAction=new QAction(tr("&Сохранить как..."),this);
   saveAsAction->setIcon(QPixmap(":/Pict/SaveAs.png"));
   mnuFile1->addAction(QPixmap(":/Pict/SaveAs.png"),"&Сохранить как...",this,SLOT(fileSaveAs()),Qt::CTRL+Qt::SHIFT+Qt::Key_S);
   saveAsAction->setIconVisibleInMenu(true);
   connect(saveAsAction, SIGNAL(triggered()),SLOT(fileSaveAs()));
   mnuFile1->addSeparator();

   printAction=new QAction(tr("&Печать"),this);
   printAction->setIcon(QPixmap(":/Pict/printer.png"));
   mnuFile1->addAction(QPixmap(":/Pict/printer.png"),"&Печать",this,SLOT(print()),Qt::CTRL+Qt::Key_P);
   printAction->setIconVisibleInMenu(true);
   connect(printAction, SIGNAL(triggered()),SLOT(print()));
   mnuFile1->addSeparator();

   exitAction=new QAction(tr("&Выход"),0);
   exitAction->setIcon(QPixmap(":/Pict/Exit.png"));
   mnuFile1->addAction(QPixmap(":/Pict/Exit.png"),"&Выход",this,SLOT(close()),Qt::ALT+Qt::Key_F4);
   exitAction->setIconVisibleInMenu(true);
   connect(exitAction, SIGNAL(triggered()),SLOT(close()));
   mnuFile1->addSeparator();

   abonementAction=new QAction("&Абонементы",0);
   abonementAction->setIcon(QPixmap(":/Pict/Ablist.png"));
   mnuFile2->addAction(QPixmap(":/Pict/Ablist.png"),"&Абонементы",this,SLOT(abonementSlot()),Qt::ALT+Qt::Key_F);
   abonementAction->setIconVisibleInMenu(true);
   connect(abonementAction, SIGNAL(triggered()),SLOT(abonementSlot()));

   clientsAction=new QAction("Клиенты",0);
   clientsAction->setIcon(QPixmap(":/Pict/People.png"));
   mnuFile2->addAction(QPixmap(":/Pict/People.png"),"&Клиенты",this,SLOT(clientSlot()),Qt::ALT+Qt::Key_R);
   clientsAction->setIconVisibleInMenu(true);
   connect(clientsAction, SIGNAL(triggered()),SLOT(clientSlot()));

   serviceAction=new QAction("Услуги",0);
   serviceAction->setIcon(QPixmap(":/Pict/Service.png"));
   mnuFile2->addAction(QPixmap(":/Pict/Service.png"),"&Услуги",this,SLOT(serviceSlot()),Qt::ALT+Qt::Key_C);
   serviceAction->setIconVisibleInMenu(true);
   connect(serviceAction, SIGNAL(triggered()),SLOT(serviceSlot()));

   cascadeAction=new QAction("Каскад",0);

   mnuFile4->addAction(cascadeAction);

   menuBar()->addMenu(mnuFile1);
   menuBar()->addMenu(mnuFile2);
   menuBar()->addMenu(mnuFile4);
   menuBar()->addMenu(mnuFile5);

   ptb1=new QToolBar;
   addToolBar(Qt::TopToolBarArea,ptb1);
   ptb1->addAction(saveAsAction);
   ptb1->addAction(printAction);
   ptb1->addAction(exitAction);
   ptb1->addSeparator();
   ptb1->addAction(abonementAction);
   ptb1->addAction(clientsAction);
   ptb1->addAction(serviceAction);
   setCentralWidget(mdiArea);
}

void MainWindow::fileOpen()
{

}

void MainWindow::fileSaveAs()
{
    fac->fileSaveAs();
}

void MainWindow::print()
{

    QPrinter printer(QPrinter::HighResolution);
       QPrintDialog printdialog(&printer,this);

          if (printdialog.exec() == QDialog::Accepted) {

           QString html = "";
           QTextDocument *doc = new QTextDocument();

           html += "<html><body><table border=1 bordercolor=red cellpadding=5>";

           html += "<tr>";
           for (int i = 0; i < fac->proxyMod->columnCount(); i++) {
               if (!fac->view->isColumnHidden(i)) {
                   html += "<td><b>";
                   html += fac->proxyMod->headerData(i,Qt::Horizontal).toString();
                   html += "</b></td>";
               }
           }
           html += "</tr>";

           for (int j = 0; j < fac->proxyMod->rowCount(); j++) {
               if (!fac->view->isRowHidden(j)) {
                   html += "<tr>";
                   for (int i = 0; i < fac->proxyMod->columnCount(); i++) {
                       if (!fac->view->isColumnHidden(i)) {
                           html += "<td>";
                           html += fac->proxyMod->data(fac->proxyMod->index(j,i)).toString();
                           html += "</td>";
                       }
                   }
               }
               html += "</tr>";
           }
           html += "</table></body></html>";
           doc->setHtml(html);
           doc->print(&printer);
           delete doc;
       }
}

void MainWindow::clientSlot()
{
    nameList *nn= new nameList("Список клиентов","Klients","Фамилия Имя Отчество","Телефон/Email");
    mdiArea->addSubWindow(nn);
    nn->acceptAction->setEnabled(false);
    nn->show();
}

void MainWindow::serviceSlot()
{
    nameList *nn= new nameList("Список услуг","Cervices","Наименование услуги","Стоимость");
    mdiArea->addSubWindow(nn);
    nn->acceptAction->setEnabled(false);
    nn->show();
}

void MainWindow::abonementSlot()
{
    Facade *facad=new Facade("MainWindowTable");
    mdiArea->addSubWindow(facad);
    facad->show();
}
