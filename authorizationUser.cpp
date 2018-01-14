#include "authorizationUser.h"

AuthorizationUser::AuthorizationUser(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Авторизаиция пользователя");
    this->setFixedSize(280,160);

    loginTextEdit=new QTextEdit;
    loginTextEdit->setFontWeight(QFont::Bold);
    loginTextEdit->setFixedHeight(25);
    loginTextEdit->setFixedWidth(150);

    passwordTextEdit=new QTextEdit;
    passwordTextEdit->setFontWeight(QFont::Bold);
    passwordTextEdit->setFixedHeight(25);
    passwordTextEdit->setFixedWidth(150);

    loginLbl=new QLabel("Логин");
    passwordLbl=new QLabel("Пароль");
    informLbl=new QLabel("Введите логин и пароль");
    informLbl->setFixedSize(200,25);

    OkButton=new QPushButton(trUtf8("ОК"));
    cancelButton=new QPushButton(trUtf8("Отмена"));

    OkButton->setFixedSize(110,36);
    cancelButton->setFixedSize(110,36);

    connect( OkButton,SIGNAL(clicked()), SLOT(accept()));
    connect( cancelButton,SIGNAL(clicked()), SLOT(reject()));

    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    Layout3=new QVBoxLayout;
    Layout4=new QHBoxLayout;
    Layout4->setAlignment(Qt::AlignCenter | Qt::AlignCenter);

    Layout1->addWidget(loginLbl);
    Layout1->addWidget(loginTextEdit);
    Layout2->addWidget(passwordLbl);
    Layout2->addWidget(passwordTextEdit);
    Layout3->addLayout(Layout1);
    Layout3->addLayout(Layout2);
    Layout4->addWidget(OkButton);
    Layout4->addWidget(cancelButton);
    Layout3->addWidget(informLbl);
    Layout3->addLayout(Layout4);

    setLayout(Layout3);
}

AuthorizationUser::~AuthorizationUser()
{

}
