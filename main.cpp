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
    QSqlQuery sql;

    switch(m_user.exec())
    {
       case QDialog::Accepted:
       loginTxt=m_user.loginTextEdit->toPlainText();
       passwordTxt=m_user.passwordTextEdit->toPlainText();
       if (sql.exec("Select * from Authorization where UserName='loginTxt' and PassWord='passwordTxt'"))
       {
         m_user.close();
         mai.show();
         return a.exec();
       }
       else
       {
           m_user.loginTextEdit->clear();
           m_user.passwordTextEdit->clear();
           return a.exec();
       }

       break;

       default:
       m_user.close();

       break;
    }

}
