#include "authorizationUser.h"

AuthorizationUser::AuthorizationUser(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Авторизаиция пользователя");

    loginTextEdit=new QTextEdit;
    loginTextEdit->setFixedHeight(25);
    loginTextEdit->setFixedWidth(150);
    passwordTextEdit=new QTextEdit;
    passwordTextEdit->setFixedHeight(25);
    passwordTextEdit->setFixedWidth(150);

    loginLbl=new QLabel("Логин");
    passwordLbl=new QLabel("Пароль");

    OkButton=new QPushButton(trUtf8("Подтвердить"));
    cancelButton=new QPushButton(trUtf8("Отмена"));

    buttonBox=new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(OkButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(cancelButton,QDialogButtonBox::ActionRole);

    connect( OkButton,SIGNAL(clicked()), SLOT(accept()));
    connect( cancelButton,SIGNAL(clicked()), SLOT(reject()));

    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    Layout3=new QVBoxLayout;

    Layout1->addWidget(loginLbl);
    Layout1->addWidget(loginTextEdit);
    Layout2->addWidget(passwordLbl);
    Layout2->addWidget(passwordTextEdit);
    Layout3->addLayout(Layout1);
    Layout3->addLayout(Layout2);
    Layout3->addWidget(buttonBox);

    setLayout(Layout3);
}

AuthorizationUser::~AuthorizationUser()
{

}
