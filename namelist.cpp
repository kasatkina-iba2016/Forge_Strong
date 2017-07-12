#include "namelist.h"
#include <QHeaderView>
#include <QGridLayout>

nameList::nameList(const QString &titleName, const QString &nameTableName, const QString &headerName1, const QString &headerName2, QWidget *parent):
    QDialog( parent )
{
    this->setWindowTitle(titleName);
    model=new QSqlTableModel(this);
    model->setTable(nameTableName);
    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->select();
    model->setHeaderData(0,Qt::Horizontal,trUtf8("Номер"));
    model->setHeaderData(1,Qt::Horizontal,headerName1);
    model->setHeaderData(2,Qt::Horizontal,headerName2);

    view=new QTableView(this);
    view->setModel(model);
    view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    view->setAlternatingRowColors(true);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    view->setMinimumSize(700,300);
    view->setStyleSheet("QTableView::item:selected{background: #ece9d8;color: blue;}");

    ptb1=new QToolBar;
    newAddAction=new QAction(tr("Добавить"),this);
    newAddAction->setIcon(QPixmap(":/Pict/Add.png"));
    connect(newAddAction, SIGNAL(triggered()),SLOT(addNewStringSlot()));

    delAction=new QAction(tr("Удалить"),this);
    delAction->setIcon(QPixmap(":/Pict/Del.png"));
    connect(delAction, SIGNAL(triggered()),SLOT(delStringSlot()));

    acceptAction=new QAction(tr("Просмотреть/Изменить"),this);
    acceptAction->setIcon(QPixmap(":/Pict/Accept.png"));
    connect(acceptAction, SIGNAL(triggered()),SLOT(accept()));

    sortAzAction=new QAction(tr("Сортировать по возрастанию"),this);
    sortAzAction->setIcon(QPixmap(":/Pict/SortAZ.png"));
    sortAzAction->setCheckable(true);
    connect(sortAzAction, SIGNAL(triggered()),SLOT(AzSlot()));

    sortZaAction=new QAction(tr("Сортировать по убыванию"),this);
    sortZaAction->setIcon(QPixmap(":/Pict/SortZA.png"));
    sortZaAction->setCheckable(true);
    connect(sortZaAction, SIGNAL(triggered()),SLOT(ZaSlot()));

    count=0;
    find=new QTextEdit;
    find->setFixedSize(90,25);
    searchAction=new QAction(tr("Найти"),this);
    searchAction->setIcon(QPixmap(":/Pict/Search.png"));
    connect(searchAction, SIGNAL(triggered()),SLOT(getData()));

    ptb1->addAction(newAddAction);
    ptb1->addAction(delAction);
    ptb1->addAction(acceptAction);
    ptb1->addSeparator();
    ptb1->addAction(sortAzAction);
    ptb1->addAction(sortZaAction);
    ptb1->addSeparator();
    ptb1->addWidget(find);
    ptb1->addAction(searchAction);

    QVBoxLayout *newLineLayout1=new QVBoxLayout;

    newLineLayout1->addWidget(ptb1);
    newLineLayout1->addWidget(view);
    setLayout(newLineLayout1);
}

nameList::~nameList()
{

}

void nameList::addNewStringSlot()
{
    int row=model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row,0),row+1);
}

void nameList::delStringSlot()
{
   {
     model->removeRow(view->currentIndex().row());
    }
}

void nameList::getData()
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

void nameList::AzSlot()
{
    if (sortAzAction->isChecked())
    {
     sortZaAction->setChecked(false);
     view->model()->sort(1,Qt::AscendingOrder);
    }
    else view->model()->sort(0,Qt::AscendingOrder);

}

void nameList::ZaSlot()
{
    if (sortZaAction->isChecked())
    {
        sortAzAction->setChecked(false);
        view->model()->sort(1,Qt::DescendingOrder);
    }
    else view->model()->sort(0,Qt::AscendingOrder);

}

QString nameList::getInput() const
{
   QModelIndex idIndex=view->model()->index(view->currentIndex().row(),1);
   QString str=idIndex.data().toString();
   return str;
}

QString nameList::getInput2() const
{
    QModelIndex idIndex=view->model()->index(view->currentIndex().row(),2);
    QString str=idIndex.data().toString();
    return str;
}


