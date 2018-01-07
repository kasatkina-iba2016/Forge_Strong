#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <QtWidgets>
#include <QTextEdit>
#include <QLayout>
#include <QVector>
#include <QString>

class Calculator:public QWidget
{
    Q_OBJECT
private:


    QVector <QString> vec;

public:
       QPushButton *nB;
       QTextEdit *monit1,*monit2;
       Calculator(QWidget *parent=0);
       QPushButton *newBut(const QString &str);
       void calcul();
       public slots:
       void displayPushBut();

};

#endif // CALCULATOR_H
