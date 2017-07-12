#include "information.h"
#include "dialog.h"
#include "namelist.h"

Information::Information(QWidget *parent) : QDialog(parent)
{
   tabWidget=new QTabWidget;
   tabWidget->addTab(gen=new GeneralTab(),tr("Информация о клиенте"));
   tabWidget->addTab(perm=new  PermissionsTab(), tr("Посещение занятий"));

   saveButton=new QPushButton("Сохранить");
   cancelButton=new QPushButton("Отмена");

   connect( saveButton,SIGNAL(clicked()), SLOT(accept()));
   connect( cancelButton,SIGNAL(clicked()), SLOT(reject()));

   buttonBox=new QDialogButtonBox(Qt::Horizontal);
   buttonBox->addButton(saveButton,QDialogButtonBox::ActionRole);
   buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(tabWidget);
   mainLayout->addWidget(buttonBox);
   setLayout(mainLayout);

   setWindowTitle("Редакирование информации о клиенте");
 }

Information::~Information()
{

}

GeneralTab::GeneralTab(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Информация о клиенте");
    QLabel *nameLbl=new QLabel("Фамилия Имя Отчество:");
    QLabel *numberLbl=new QLabel("Номер абонемента:");
    QLabel *serviceLbl=new QLabel("Вид абонемента");
    QLabel *dateLbl=new QLabel("Дата оплаты:");
    QLabel *balanseLbl=new QLabel("Срок действия по/Остаток занятий");
    tableNameButton=new QPushButton(tr("..."));
    tableNameButton->setFixedSize(27,27);
    tableCerviceButton=new QPushButton(tr("..."));
    tableCerviceButton->setFixedSize(27,27);

    connect(tableNameButton,SIGNAL(clicked()),SLOT(selectNameSlot()));
    connect(tableCerviceButton,SIGNAL(clicked()),SLOT(selectCerviceSlot()));

    serviceEdit=new QTextEdit;
    serviceEdit->setFixedHeight(25);
    serviceEdit->setReadOnly(true);
    dateEdit=new QTextEdit;
    dateEdit->setFixedHeight(25);
    dateEdit->setReadOnly(true);
    balanseEdit=new QTextEdit;
    balanseEdit->setFixedHeight(25);
    balanseEdit->setReadOnly(true);

    nameEdit=new QTextEdit;
    nameEdit->setFixedHeight(25);
    nameEdit->setReadOnly(true);
    numberEdit=new QTextEdit;
    numberEdit->setFixedHeight(25);

    mapper=new QDataWidgetMapper(this);

    QHBoxLayout *Layout1=new QHBoxLayout;
    QHBoxLayout *Layout2=new QHBoxLayout;
    Layout1->addWidget(nameEdit);
    Layout1->addWidget(tableNameButton);
    Layout1->setSpacing(0);
    Layout2->addWidget(serviceEdit);
    Layout2->addWidget(tableCerviceButton);
    Layout2->setSpacing(0);

    QGridLayout *newLineLayout=new QGridLayout(this);
    newLineLayout->addWidget(nameLbl,0,0);
    newLineLayout->addLayout(Layout1,0,1);
    newLineLayout->addWidget(numberLbl,1,0);
    newLineLayout->addWidget(numberEdit,1,1);
    newLineLayout->addWidget(serviceLbl,2,0);
    newLineLayout->addLayout(Layout2,2,1);
    newLineLayout->addWidget(dateLbl,3,0);
    newLineLayout->addWidget(dateEdit,3,1);
    newLineLayout->addWidget(balanseLbl,4,0);
    newLineLayout->addWidget(balanseEdit,4,1);
    setLayout(newLineLayout);
}

GeneralTab::~GeneralTab()
{

}

void GeneralTab::setMyModel(QSqlTableModel *model)
{

    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    model->select();
    mapper->setModel(model);
    mapper->addMapping(numberEdit,0,"plainText");
    mapper->addMapping(nameEdit,2,"plainText");
    mapper->addMapping(serviceEdit,3,"plainText");
    mapper->addMapping(dateEdit,1,"plainText");
    mapper->addMapping(balanseEdit,5,"plainText");
}

void GeneralTab::setIndex(int row)
{
    mapper->setCurrentIndex(row);
}

void GeneralTab::selectNameSlot()
{
    nameList nn("Список клиентов","Klients","Фамилия Имя Отчество","Телефон/Email",this);
     switch( nn.exec() )
     {
        case QDialog::Accepted:
        nameEdit->setText(nn.getInput());
        break;

        default:
        break;
      }
}

void GeneralTab::selectCerviceSlot()
{
    nameList nn("Список услуг","Cervices","Наименование услуги","Стоимость",this);
    switch(nn.exec())
    {
       case QDialog::Accepted:
        serviceEdit->setText(nn.getInput());
        if (serviceEdit->toPlainText()=="Абонемент на 12 занятий")
            balanseEdit->setText("12 занятий");
        else if (serviceEdit->toPlainText()=="Абонемент на 8 занятий")
            balanseEdit->setText("8 занятий");
        else if (serviceEdit->toPlainText()=="Абонемент на 4 занятия")
            balanseEdit->setText("4 занятия");
        else if (serviceEdit->toPlainText()=="Абонемент на 1 месяц")
           balanseEdit->setText(QDateTime::currentDateTime().addMonths(1).toString("dd/MM/yyyy"));
       else if (serviceEdit->toPlainText()=="Абонемент на 3 месяца")
           balanseEdit->setText(QDateTime::currentDateTime().addMonths(3).toString("dd/MM/yyyy"));
       else if (serviceEdit->toPlainText()=="Абонемент на 6 месяцев")
           balanseEdit->setText(QDateTime::currentDateTime().addMonths(6).toString("dd/MM/yyyy"));
        break;

       default:
        break;
    }
}

PermissionsTab::PermissionsTab(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Информация о посещениях");
    mapper2=new QDataWidgetMapper(this);

    QGridLayout *newLineLayout=new QGridLayout(this);

    visit1=new QTextEdit;  btn1=new QToolButton;
    visit2=new QTextEdit;  btn2=new QToolButton;
    visit3=new QTextEdit;  btn3=new QToolButton;
    visit4=new QTextEdit;  btn4=new QToolButton;
    visit5=new QTextEdit;  btn5=new QToolButton;
    visit6=new QTextEdit;  btn6=new QToolButton;
    visit7=new QTextEdit;  btn7=new QToolButton;
    visit8=new QTextEdit;  btn8=new QToolButton;
    visit9=new QTextEdit;  btn9=new QToolButton;
    visit10=new QTextEdit;  btn10=new QToolButton;
    visit11=new QTextEdit;  btn11=new QToolButton;
    visit12=new QTextEdit;  btn12=new QToolButton;

    calendarMenu1=new QMenu;  QHBoxLayout *lay1=new QHBoxLayout;
    calendarMenu2=new QMenu;  QHBoxLayout *lay2=new QHBoxLayout;
    calendarMenu3=new QMenu;  QHBoxLayout *lay3=new QHBoxLayout;
    calendarMenu4=new QMenu;  QHBoxLayout *lay4=new QHBoxLayout;
    calendarMenu5=new QMenu;  QHBoxLayout *lay5=new QHBoxLayout;
    calendarMenu6=new QMenu;  QHBoxLayout *lay6=new QHBoxLayout;
    calendarMenu7=new QMenu;  QHBoxLayout *lay7=new QHBoxLayout;
    calendarMenu8=new QMenu;  QHBoxLayout *lay8=new QHBoxLayout;
    calendarMenu9=new QMenu;  QHBoxLayout *lay9=new QHBoxLayout;
    calendarMenu10=new QMenu; QHBoxLayout *lay10=new QHBoxLayout;
    calendarMenu11=new QMenu; QHBoxLayout *lay11=new QHBoxLayout;
    calendarMenu12=new QMenu; QHBoxLayout *lay12=new QHBoxLayout;

    calendar1=new QCalendarWidget;  calendar7=new QCalendarWidget;
    calendar2=new QCalendarWidget;  calendar8=new QCalendarWidget;
    calendar3=new QCalendarWidget;  calendar9=new QCalendarWidget;
    calendar4=new QCalendarWidget;  calendar10=new QCalendarWidget;
    calendar5=new QCalendarWidget;  calendar11=new QCalendarWidget;
    calendar6=new QCalendarWidget;  calendar12=new QCalendarWidget;
    calendar<<calendar1<<calendar2<<calendar3<<calendar4<<calendar5<<calendar6
           <<calendar7<<calendar8<<calendar9<<calendar10<<calendar11<<calendar12;

   btn<<btn1<<btn2<<btn3<<btn4<<btn5<<btn6<<btn7<<btn8<<btn9<<btn10<<btn11<<btn12;


    visit<<visit1<<visit2<<visit3<<visit4<<visit5<<visit6<<visit7<<visit8<<visit9<<visit10<<visit11<<visit12;

    for (int i=0;i<12;i++)
    {
        visit[i]->setReadOnly(true);
    }

    QList<QHBoxLayout*> lay;
    lay<<lay1<<lay2<<lay3<<lay4<<lay5<<lay6<<lay7<<lay8<<lay9<<lay10<<lay11<<lay12;

    QList<QMenu*> calendarMenu;
    calendarMenu<< calendarMenu1<< calendarMenu2<< calendarMenu3<<calendarMenu4<<calendarMenu5
                 << calendarMenu6<< calendarMenu7<< calendarMenu8<< calendarMenu9<< calendarMenu10
                 << calendarMenu11<< calendarMenu12;

    connect (calendar[0],SIGNAL(clicked(QDate)),SLOT(changeDateSlot0(QDate)));
    connect (calendar[1],SIGNAL(clicked(QDate)),SLOT(changeDateSlot1(QDate)));
    connect (calendar[2],SIGNAL(clicked(QDate)),SLOT(changeDateSlot2(QDate)));
    connect (calendar[3],SIGNAL(clicked(QDate)),SLOT(changeDateSlot3(QDate)));
    connect (calendar[4],SIGNAL(clicked(QDate)),SLOT(changeDateSlot4(QDate)));
    connect (calendar[5],SIGNAL(clicked(QDate)),SLOT(changeDateSlot5(QDate)));
    connect (calendar[6],SIGNAL(clicked(QDate)),SLOT(changeDateSlot6(QDate)));
    connect (calendar[7],SIGNAL(clicked(QDate)),SLOT(changeDateSlot7(QDate)));
    connect (calendar[8],SIGNAL(clicked(QDate)),SLOT(changeDateSlot8(QDate)));
    connect (calendar[9],SIGNAL(clicked(QDate)),SLOT(changeDateSlot9(QDate)));
    connect (calendar[10],SIGNAL(clicked(QDate)),SLOT(changeDateSlot10(QDate)));
    connect (calendar[11],SIGNAL(clicked(QDate)),SLOT(changeDateSlot11(QDate)));

     for (i=0;i<3;i++)
      {
        for (j=0;j<4;j++)
        {
          QWidgetAction *act=new QWidgetAction(0);

          act->setDefaultWidget(calendar[count-1]);
          calendarMenu[count-1]->addAction(act);
          btn[count-1]->setPopupMode(QToolButton::InstantPopup);
          btn[count-1]->setIcon(QIcon(":/Pict/Calendar.png"));
          btn[count-1]->setFixedSize(27,27);
          btn[count-1]->setMenu(calendarMenu[count-1]);
          lay[count-1]->addWidget(btn[count-1]);
          lay[count-1]->addWidget(visit[count-1]);
          lay[count-1]->setSpacing(0);
          visit[count-1]->setFixedSize(70,25);
          connect (btn[count-1],SIGNAL(clicked()),calendarMenu[count-1],SLOT(show()));
          newLineLayout->addWidget(newlbl(QString::number(count)+"-е занятие"),counti,j);
          newLineLayout->addLayout(lay[count-1],countj,j);
          count++;
        }
        counti+=2;
        countj+=2;
       }
     setLayout(newLineLayout);
}

PermissionsTab::~PermissionsTab()
{

}

QLabel *PermissionsTab::newlbl(const QString &str)
{
    visitLbl=new QLabel(str);
    return visitLbl;
}

void PermissionsTab::changeDateSlot0(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu1->close();
    visit[0]->setText(podate);
}

void PermissionsTab::changeDateSlot1(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu2->close();
    visit[1]->setText(podate);
}

void PermissionsTab::changeDateSlot2(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu3->close();
    visit[2]->setText(podate);
}

void PermissionsTab::changeDateSlot3(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu4->close();
    visit[3]->setText(podate);
}

void PermissionsTab::changeDateSlot4(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu5->close();
    visit[4]->setText(podate);
}

void PermissionsTab::changeDateSlot5(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu6->close();
    visit[5]->setText(podate);
}

void PermissionsTab::changeDateSlot6(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu7->close();
    visit[6]->setText(podate);
}

void PermissionsTab::changeDateSlot7(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu8->close();
    visit[7]->setText(podate);
}

void PermissionsTab::changeDateSlot8(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu9->close();
    visit[8]->setText(podate);
}

void PermissionsTab::changeDateSlot9(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu10->close();
    visit[9]->setText(podate);
}

void PermissionsTab::changeDateSlot10(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu11->close();
    visit[10]->setText(podate);
}

void PermissionsTab::changeDateSlot11(QDate dat)
{
    podate=dat.toString("dd/MM/yyyy");
    calendarMenu12->close();
    visit[11]->setText(podate);
}

 void PermissionsTab::setMyModel2(QSqlTableModel *model)
 {
     mapper2->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
     model->select();
     mapper2->setModel(model);
     mapper2->addMapping(visit1,6,"plainText");
     mapper2->addMapping(visit2,7,"plainText");
     mapper2->addMapping(visit3,8,"plainText");
     mapper2->addMapping(visit4,9,"plainText");
     mapper2->addMapping(visit5,10,"plainText");
     mapper2->addMapping(visit6,11,"plainText");
     mapper2->addMapping(visit7,12,"plainText");
     mapper2->addMapping(visit8,13,"plainText");
     mapper2->addMapping(visit9,14,"plainText");
     mapper2->addMapping(visit10,15,"plainText");
     mapper2->addMapping(visit11,16,"plainText");
     mapper2->addMapping(visit12,17,"plainText");
 }

 void PermissionsTab::setIndex(int row)
 {
     mapper2->setCurrentIndex(row);
 }

