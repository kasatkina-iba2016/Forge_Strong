#include "authorizationUser.h"

AuthorizationUser::AuthorizationUser(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Авторизаиция пользователя");

    loginTextEdit=new QTextEdit;
    loginTextEdit->setFixedHeight(25);
    passwordTextEdit=new QTextEdit;
    passwordTextEdit->setFixedHeight(25);

    OkButton=new QPushButton(trUtf8("Подтвердить"));
    cancelButton=new QPushButton(trUtf8("Отмена"));
}

AuthorizationUser::~AuthorizationUser()
{

}
