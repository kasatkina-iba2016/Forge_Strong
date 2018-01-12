#include "facade.h"
#include "namelist.h"
#include "mainwindow.h"
#include "authorizationUser.h"
#include <QDebug>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDate>
#include <QSqlQuery>
#include <QtWidgets>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("D:/DBSqlite/DB Browser for SQLite/Forge.db");

    if (!db.open())
    {
        qDebug()<<db.lastError().text();
        return 1;

    }
    else
    {
        qDebug()<<"DB Forge is open.";
    }

    QFile StyleFile;
    StyleFile.setFileName(":/Pict/Stylefile.css");
    StyleFile.open(QFile::ReadOnly);
    QString cssStr=StyleFile.readAll();
    qApp->setStyleSheet(cssStr);

    MainWindow mai;
    AuthorizationUser m_user;
    m_user.show();

    QString loginTxt;
    QString passwordTxt;
    QSqlQuery sqlq(db);

    while (m_user.exec()== QDialog::Accepted)
    {
        loginTxt=m_user.loginTextEdit->toPlainText();
        passwordTxt=m_user.passwordTextEdit->toPlainText();
        bool flag=false;
        sqlq.exec("SELECT UserName, PassWord FROM Authorization;");

        while (sqlq.next())
        {
            if (sqlq.value("UserName").toString()==loginTxt and sqlq.value("PassWord").toString()==passwordTxt)
             {
               m_user.close();
               mai.show();
               flag=true;
               return a.exec();
             }
        }

        if (flag==false)
        {
           m_user.loginTextEdit->clear();
           m_user.passwordTextEdit->clear();
           m_user.informLbl->setStyleSheet("QLabel { color : red; }");
           m_user.informLbl->setText("Вы ввели неверные данные");
           m_user.show();
        }
    }
    return 0;
}
