#include "aboutclass.h"

AboutClass::AboutClass(QWidget *parent) : QDialog(parent)
{

    this->setWindowTitle("О программе");
    this->setFixedSize(400,200);

    aboutLbl=new QLabel;

    Layout1=new QVBoxLayout;
    Layout2=new QVBoxLayout;

    butt=new QPushButton("Закрыть");
    butt->setFixedSize(110,40);

    connect(butt,SIGNAL(clicked()),this,SLOT(close()));

    aboutLbl->setText("Forge 1.0\n"
                       "\n"
                       "Собрано Jan 2018\n"
                       "\n"
                       "© 2016-2018. KasatkinaProject. Все права защищены\n");

    Layout1->addWidget(aboutLbl);
    Layout1->setAlignment(Qt::AlignCenter | Qt::AlignLeft);
    Layout2->addWidget(butt);
    Layout2->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    Layout1->addLayout(Layout2);

    setLayout(Layout1);

}

AboutClass::~AboutClass()
{


}
