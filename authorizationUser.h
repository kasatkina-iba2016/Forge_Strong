#ifndef AUTHORIZATIONUSER_H
#define AUTHORIZATIONUSER_H

#include <QObject>
#include <QtWidgets>

class AuthorizationUser : public QDialog
{
    Q_OBJECT
public:
    explicit AuthorizationUser(QWidget *parent = 0);
    ~AuthorizationUser();

    QTextEdit *loginTextEdit, *passwordTextEdit;
    QPushButton *OkButton, *cancelButton;
    QLabel *loginLbl, *passwordLbl, *informLbl;
    QHBoxLayout *Layout1, *Layout2,*Layout4;
    QVBoxLayout *Layout3;

};

#endif // AUTHORIZATIONUSER_H
