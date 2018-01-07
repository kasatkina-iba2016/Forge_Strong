#include "facade.h"
#include "namelist.h"
#include "mainwindow.h"
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

    mai.show();
    return a.exec();
}
