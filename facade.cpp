#include "facade.h"
#include "dialog.h"
#include "information.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlError>
#include <QModelIndex>
#include <QHeaderView>
#include <QDebug>
#include <QSortFilterProxyModel>

Facade::Facade(const QString &mainTableName, QWidget *parent):QWidget(parent)

{
    count=0;
    setWindowTitle("Список абонементов");
    model=new QSqlTableModel(this);
    model->setTable(mainTableName);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();
    model->setHeaderData(0,Qt::Horizontal,trUtf8("Номер"));
    model->setHeaderData(1,Qt::Horizontal,trUtf8("Дата оплаты"));
    model->setHeaderData(2,Qt::Horizontal,trUtf8("ФИО"));
    model->setHeaderData(3,Qt::Horizontal,trUtf8("Вид абонемента"));
    model->setHeaderData(4,Qt::Horizontal,trUtf8("Сумма оплаты"));
    model->setHeaderData(5,Qt::Horizontal,trUtf8("Срок действия по/Остаток занятий"));

    proxyMod=new ProxyModel(this);
    proxyMod->setSourceModel(model);
    view=new QTableView(this);
    view->setModel(proxyMod);

      inform=new Information(this);
      inform->gen->setMyModel(model);
      inform->perm->setMyModel2(model);

    //скрываем столбцы посещений

    for (int i=6;i<18;i++)
    view->setColumnHidden(i,true);

    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    view->setAlternatingRowColors(true);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->setMinimumSize(700,300);
    view->setStyleSheet("QTableView::item:selected{background: #ece9d8;color: blue;}");

    find=new QTextEdit;
    find->setFixedSize(90,25);
    calendar1=new QCalendarWidget;
    calendar2=new QCalendarWidget;
    QLabel *lbl1=new QLabel("С:");
    QLabel *lbl2=new QLabel("  По:");
    data1=new QTextEdit;
    data1->setText("01/01/2017");
    data1->setReadOnly(true);
    data2=new QTextEdit;
    data2->setText(QDate::currentDate().toString("dd/MM/yyyy"));
    data2->setReadOnly(true);
    QToolButton *btn1=new QToolButton;
    QToolButton *btn2=new QToolButton;
    calendarMenu1=new QMenu;
    calendarMenu2=new QMenu;

    connect (calendar1,SIGNAL(clicked(QDate)),SLOT(changeDateSlot1(QDate)));
    connect (calendar2,SIGNAL(clicked(QDate)),SLOT(changeDateSlot2(QDate)));

    QWidgetAction *act1=new QWidgetAction(0);

    act1->setDefaultWidget(calendar1);
    calendarMenu1->addAction(act1);
    btn1->setPopupMode(QToolButton::InstantPopup);
    btn1->setIcon(QIcon(":/Pict/Calendar.png"));
    btn1->setFixedSize(27,27);
    btn1->setMenu(calendarMenu1);
    data1->setFixedSize(70,25);

    connect (btn1,SIGNAL(clicked()),calendarMenu1,SLOT(show()));

    QWidgetAction *act2=new QWidgetAction(0);

    act2->setDefaultWidget(calendar2);
    calendarMenu2->addAction(act2);
    btn2->setPopupMode(QToolButton::InstantPopup);
    btn2->setIcon(QIcon(":/Pict/Calendar.png"));
    btn2->setFixedSize(27,27);
    btn2->setMenu(calendarMenu2);
    data2->setFixedSize(70,25);

    connect (btn2,SIGNAL(clicked()),calendarMenu2,SLOT(show()));

    addAction=new QAction(tr("Добавить"),this);
    addAction->setIcon(QPixmap(":/Pict/Add.png"));
    connect(addAction, SIGNAL(triggered()),SLOT(addNameSlot()));

    delAction=new QAction(tr("Удалить"),this);
    delAction->setIcon(QPixmap(":/Pict/Del.png"));
    connect(delAction, SIGNAL(triggered()),SLOT(delNameSlot()));

    changeAction=new QAction(tr("Просмотреть/Изменить"),this);
    changeAction->setIcon(QPixmap(":/Pict/Change.png"));
    connect(changeAction, SIGNAL(triggered()),SLOT(addInformSlot()));

    okAction=new QAction(tr("Сформировать"),this);
    okAction->setIcon(QPixmap(":/Pict/Ok.png"));
    connect(okAction, SIGNAL(triggered()),SLOT(getMinDate()));
    connect(okAction, SIGNAL(triggered()),SLOT(getMaxDate()));
    connect(this, SIGNAL(signalMinDate(QDate)),proxyMod,SLOT(setFilterMinDate(QDate)));
    connect(this, SIGNAL(signalMaxDate(QDate)),proxyMod,SLOT(setFilterMaxDate(QDate)));

    searchAction=new QAction(tr("Найти"),this);
    searchAction->setIcon(QPixmap(":/Pict/Search.png"));
    connect(searchAction, SIGNAL(triggered()),SLOT(getData()));

    sortAzAction=new QAction(tr("Сортировать по возрастанию"),this);
    sortAzAction->setIcon(QPixmap(":/Pict/SortAZ.png"));
    sortAzAction->setCheckable(true);
    connect(sortAzAction, SIGNAL(triggered()),SLOT(AzSlot()));

    sortZaAction=new QAction(tr("Сортировать по убыванию"),this);
    sortZaAction->setIcon(QPixmap(":/Pict/SortZA.png"));
    sortZaAction->setCheckable(true);
    connect(sortZaAction, SIGNAL(triggered()),SLOT(ZaSlot()));

    ptb1=new QToolBar;
    ptb2=new QToolBar;
    ptb1->addAction(addAction);
    ptb1->addAction(delAction);
    ptb1->addAction(changeAction);
    ptb1->addSeparator();
    ptb1->addAction(sortAzAction);
    ptb1->addAction(sortZaAction);
    ptb1->addSeparator();
    ptb1->addWidget(find);
    ptb1->addAction(searchAction);

    ptb2->addWidget(lbl1);
    ptb2->addWidget(btn1);
    ptb2->addWidget(data1);
    ptb2->addWidget(lbl2);
    ptb2->addWidget(btn2);
    ptb2->addWidget(data2);
    ptb2->addAction(okAction);

    ab4z="Абонемент на 4 занятия"; ab8z="Абонемент на 8 занятий"; ab12z="Абонемент на 12 занятий";
    ab1m="Абонемент на месяц"; ab3m="Абонемент на 3 месяца"; ab6m="Абонемент на 6 месяцев";

    QVBoxLayout *mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(ptb1);
    mainLayout->addWidget(ptb2);
    mainLayout->addWidget(view);
    setLayout(mainLayout);
}

Facade::~Facade()
{

}

void Facade::addNameSlot()
{
    Dialog nameDialog("Добавление клиента",this);
    int row=proxyMod->rowCount();
    int max=proxyMod->data(proxyMod->index(0,0)).toInt();

    for (int i=0;i<row;i++)
    {
        if (proxyMod->data(proxyMod->index(i,0)).toInt()>max)
            max=proxyMod->data(proxyMod->index(i,0)).toInt();
    }

    nameDialog.numberTextEdit->setText(QString::number(max+1));
    switch( nameDialog.exec() )
    {
       case QDialog::Accepted:

       model->insertRows(row,1);
       model->setData(model->index(row,0),nameDialog.getInputNumber());
       model->setData(model->index(row,1),QDateTime::currentDateTime().toString("dd/MM/yyyy"));
       model->setData(model->index(row,2),nameDialog.getInputName());
       model->setData(model->index(row,3),nameDialog.getInputService());
       model->setData(model->index(row,4),nameDialog.getInputCena()+" руб.");

         if (nameDialog.getInputService()==ab12z)
            model->setData(model->index(row,5),"12 занятий");
         else if (nameDialog.getInputService()==ab8z)
            model->setData(model->index(row,5),"8 занятий");
         else if (nameDialog.getInputService()==ab4z)
            model->setData(model->index(row,5),"4 занятия");
         else if (nameDialog.getInputService()==ab1m)
            model->setData(model->index(row,5),QDateTime::currentDateTime().addMonths(1).toString("dd/MM/yyyy"));
        else if (nameDialog.getInputService()==ab3m)
            model->setData(model->index(row,5),QDateTime::currentDateTime().addMonths(3).toString("dd/MM/yyyy"));
        else if (nameDialog.getInputService()==ab6m)
            model->setData(model->index(row,5),QDateTime::currentDateTime().addMonths(6).toString("dd/MM/yyyy"));

         model->submitAll();

         break;

       default:
       qDebug() << "Unexpected";
     }
}

void Facade::delNameSlot()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Удаление");
    msgBox.setText("Удалить выбранный элемент?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int res = msgBox.exec();
    if (res == QMessageBox::Ok)
     {
        model->removeRow(view->currentIndex().row());
        model->submitAll();
        model->select();
     }
    else  msgBox.close();
}

void Facade::addInformSlot()
{
  int vis=0, count=0;
  QModelIndex proxyIndex;
  proxyIndex=proxyMod->mapToSource(view->currentIndex());

  if (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab4z)
   {
       vis=4;
       for (int i=4;i<12;i++)
         {
           inform->perm->btn[i]->setDisabled(true);
           inform->perm->visit[i]->setDisabled(true);
         }
    }

  if (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab8z)
   {
        vis=8;
        for (int i=8;i<12;i++)
         {
           inform->perm->btn[i]->setDisabled(true);
           inform->perm->visit[i]->setDisabled(true);
         }
    }

  if (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab12z) vis=12;

  if ((proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab1m)||
      (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab3m)||
      (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()==ab6m))
   {
     inform->perm->setDisabled(true);
   }

  inform->gen->setIndex(proxyIndex.row());
  inform->perm->setIndex(proxyIndex.row());

  switch( inform->exec() )
  {
      case QDialog::Accepted:
      inform->gen->mapper->submit();
      inform->perm->mapper2->submit();
      inform->perm->setEnabled(true);
      for (int i=0;i<12;i++)
       {
         inform->perm->btn[i]->setEnabled(true);
         inform->perm->visit[i]->setEnabled(true);
       }
      if ((proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()!=ab1m)&&
          (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()!=ab3m)&&
          (proxyMod->data(proxyMod->index(view->currentIndex().row(),3)).toString()!=ab6m))
         {
          for (int i=0;i<vis;i++)
           {
             if (inform->perm->visit[i]->toPlainText()!="")
             count++;
           }
          QString zan;
          if ((vis-count==0)||(vis-count>4 && vis-count<13)) zan=" занятий";
          if (vis-count==1) zan=" занятие";
          if (vis-count>1 && vis-count<5) zan=" занятия";
          model->setData(model->index(view->currentIndex().row(),5),QString::number(vis-count)+zan);
        }
      model->submitAll();
      break;

     default:
      for (int i=0;i<12;i++)
       {
         inform->perm->btn[i]->setEnabled(true);
         inform->perm->visit[i]->setEnabled(true);
       }
      inform->perm->setEnabled(true);
      break;
   }
}

void Facade::fileSaveAs()
{
   QString fileName=QFileDialog::getSaveFileName
      (this,"Сохранить как...",QDir::homePath(),"Microsoft Excel( *.xls )");
   QFile f(fileName);

   if( f.open( QIODevice::WriteOnly ) )
      {
          QTextStream ts( &f );
          QStringList strList;
   strList << "\" \"";
           for( int c = 0; c < view->horizontalHeader()->count(); c++ )
              { strList << "\""+view->model()->headerData(c, Qt::Horizontal).toString()+"\"";
           }
            ts << strList.join( ";" )+"\n";

            for( int r = 0; r < view->verticalHeader()->count(); ++r )
            {
                strList.clear();
                strList << "\""+view->model()->headerData(r, Qt::Vertical).toString()+"\"";
                for( int c = 0; c < view->horizontalHeader()->count(); ++c )
                {
                    strList << "\""+view->model()->data(view->model()->index(r, c), Qt::DisplayRole).toString()+"\"";
                }
                ts << strList.join( ";" )+"\n";
            }
            f.close();
    }
}

void Facade::getMinDate()
{
   emit signalMinDate(QDate::fromString(data1->toPlainText(),"dd/MM/yyyy"));
}

void Facade::getMaxDate()
{
   emit signalMaxDate(QDate::fromString(data2->toPlainText(),"dd/MM/yyyy"));
}

void Facade::changeDateSlot1(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu1->close();
    data1->setText(podate);
}

void Facade::changeDateSlot2(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu2->close();
    data2->setText(podate);
}

void Facade::getData()
{
    QModelIndexList list1;
    for (int i=0; i<model->rowCount(); i++)
        for (int j=0; j<6; j++)
        {
          if  (view->model()->data(view->model()->index(i,j), Qt::DisplayRole).toString().contains(find->toPlainText()))
             {
              list1<<view->model()->index(i,j);
             }
        }
    if (list1.count()==1)
    {
        view->setCurrentIndex(list1[0]);
    }

    else if (list1.count()>1 && count<list1.count()-1)
    {
        view->setCurrentIndex(list1[count]);
        count++;
    }
    else if (list1.count()>1 && count==list1.count()-1)
    {
        view->setCurrentIndex(list1[count]);
        count=0;
    }
}

void Facade::AzSlot()
{
    if (sortAzAction->isChecked())
    {
       sortZaAction->setChecked(false);
       view->model()->sort(2,Qt::AscendingOrder);
       model->sort(2,Qt::AscendingOrder);
    }
    else
    {
        view->model()->sort(1,Qt::AscendingOrder);
        model->sort(1,Qt::AscendingOrder);
    }

}

void Facade::ZaSlot()
{
    if (sortZaAction->isChecked())
    {
      sortAzAction->setChecked(false);
      view->model()->sort(2,Qt::DescendingOrder);
      model->sort(2,Qt::DescendingOrder);
    }
    else
    {
        view->model()->sort(1,Qt::AscendingOrder);
        model->sort(1,Qt::AscendingOrder);
    }
}



