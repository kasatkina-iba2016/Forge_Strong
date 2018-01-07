#include "namedialog.h"

NameDialog::NameDialog(const QString title, const QString headerName1, const QString headerName2, QWidget *parent) : QDialog(parent)
{
     this->setWindowTitle(title);

     nameTextEdit=new QTextEdit;
     nameTextEdit->setFixedHeight(25);
     telephoneTextEdit=new QTextEdit;
     telephoneTextEdit->setFixedHeight(25);
     saveButton=new QPushButton(trUtf8("Сохранить"));
     cancelButton=new QPushButton(trUtf8("Отмена"));

     buttonBox=new QDialogButtonBox(Qt::Horizontal);
     buttonBox->addButton(saveButton,QDialogButtonBox::ActionRole);
     buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);

        QGridLayout *newLineLayout=new QGridLayout(this);
        QHBoxLayout *Layout1=new QHBoxLayout;
        QHBoxLayout *Layout2=new QHBoxLayout;
        QLabel *nameLbl=new QLabel(headerName1+":");
        QLabel *telephoneLbl=new QLabel( headerName2+":");

        Layout1->addWidget(nameTextEdit);
        Layout2->addWidget(telephoneTextEdit);

        newLineLayout->addWidget(nameLbl,2,0);
        newLineLayout->addLayout(Layout1,3,0);
        newLineLayout->addWidget(telephoneLbl,4,0);
        newLineLayout->addLayout(Layout2,5,0);
        newLineLayout->addWidget(buttonBox,6,0);

        setLayout(newLineLayout);

     connect( saveButton,SIGNAL(clicked()), SLOT(accept()));
     connect( cancelButton,SIGNAL(clicked()), SLOT(reject()));
}

NameDialog::~NameDialog()
{

}

QString NameDialog::getInputName() const
{
   QString str=nameTextEdit->toPlainText();
   return str;
}

QString NameDialog::getInputTelephone() const
{
   QString str=telephoneTextEdit->toPlainText();
   return str;
}
