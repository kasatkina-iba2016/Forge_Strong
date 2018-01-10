#include "dialog.h"
#include "namelist.h"

Dialog::Dialog(const QString title, QWidget *parent) : QDialog(parent)
{
     this->setWindowTitle(title);
     tableNameButton=new QPushButton(tr("..."));
     tableNameButton->setFixedSize(27,27);
     tableCerviceButton=new QPushButton(tr("..."));
     tableCerviceButton->setFixedSize(27,27);
     numberTextEdit=new QTextEdit;
     numberTextEdit->setFixedHeight(25);
     nameTextEdit=new QTextEdit;
     nameTextEdit->setFixedHeight(25);
     cerviceTextEdit=new QTextEdit;
     cerviceTextEdit->setFixedHeight(25);
     saveButton=new QPushButton(trUtf8("Сохранить"));
     cancelButton=new QPushButton(trUtf8("Отмена"));

     buttonBox=new QDialogButtonBox(Qt::Horizontal);
     buttonBox->addButton(saveButton,QDialogButtonBox::ActionRole);
     buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);

        QGridLayout *newLineLayout=new QGridLayout(this);
        QHBoxLayout *Layout1=new QHBoxLayout;
        QHBoxLayout *Layout2=new QHBoxLayout;
        QLabel *numberLbl=new QLabel("Номер абонемента:");
        QLabel *nameLbl=new QLabel("Фамилия Имя Отчество:");
        QLabel *serviceLbl=new QLabel("Вид услуги:");

        Layout1->addWidget(nameTextEdit);
        Layout1->addWidget(tableNameButton);
        Layout1->setSpacing(0);
        Layout2->addWidget(cerviceTextEdit);
        Layout2->addWidget(tableCerviceButton);
        Layout2->setSpacing(0);
        newLineLayout->addWidget(numberLbl,0,0);
        newLineLayout->addWidget(numberTextEdit,1,0);
        newLineLayout->addWidget(nameLbl,2,0);
        newLineLayout->addLayout(Layout1,3,0);
        newLineLayout->addWidget(serviceLbl,4,0);
        newLineLayout->addLayout(Layout2,5,0);
        newLineLayout->addWidget(buttonBox,6,0);

        setLayout(newLineLayout);

     connect(tableNameButton,SIGNAL(clicked()),SLOT(selectNameSlot()));
     connect(tableCerviceButton,SIGNAL(clicked()),SLOT(selectCerviceSlot()));
     connect( saveButton,SIGNAL(clicked()), SLOT(accept()));
     connect( cancelButton,SIGNAL(clicked()), SLOT(reject()));
}

Dialog::~Dialog()
{

}

QString Dialog::getInputName() const
{
   QString str=nameTextEdit->toPlainText();
   return str;
}

QString Dialog::getInputNumber() const
{
   QString str=numberTextEdit->toPlainText();
   return str;
}

QString Dialog::getInputService() const
{
   QString str=cerviceTextEdit->toPlainText();
   return str;
}

QString Dialog::getInputCena() const
{
    return cena;
}

void Dialog::selectNameSlot()
{
   nameList nn("Список клиентов","Clients","Фамилия Имя Отчество","Телефон/Email",this);
    switch( nn.exec() )
    {
       case QDialog::Accepted:
       nameTextEdit->setText(nn.getInput());
       break;

       default:
       break;
     }
}

void Dialog::selectCerviceSlot()
{
    nameList nn("Список услуг","Cervices","Наименование услуги","Стоимость",this);
    switch(nn.exec())
    {
       case QDialog::Accepted:
        cerviceTextEdit->setText(nn.getInput());
        cena=nn.getInput2();

        break;

       default:
        break;
     }
}
