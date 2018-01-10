#include "calculator.h"
#include <QtMath>
#include <QPalette>
#include <QCommonStyle>
Calculator::Calculator(QWidget *parent):QWidget(parent)
{
    monit1=new QTextEdit;
    monit1->setFrameStyle(QFrame::NoFrame);
    monit1->setMinimumSize(190,23);
    monit1->setAlignment(Qt::AlignRight);

    monit2=new QTextEdit;
    monit2->isReadOnly();
    monit2->setFrameStyle(QFrame::NoFrame);
    monit2->fontFamily();
    monit2->setAlignment(Qt::AlignRight);
    monit2->setMinimumSize(170,21);

    QGridLayout *Lay=new QGridLayout;

    Lay->addWidget(monit1,0,0,1,4);
    Lay->setVerticalSpacing(0);
    Lay->addWidget(monit2,1,0,1,4);

    QGridLayout *Lay1=new QGridLayout;
    Lay1->addLayout(Lay,0,0,1,4);

    QString nameButton[5][4]={{"CE","√","1/x","/"},
                              {"7","8","9","*"},
                              {"4","5","6","-"},
                              {"1","2","3","+"},
                              {"<-","0",".","+/-"}};
    for (int i=0;i<5;i++)
      for (int j=0;j<4;j++)
        Lay1->addWidget(newBut(nameButton[i][j]),i+1,j,1,1);
        Lay1->addWidget(newBut("="),6,0,1,4);
        setLayout(Lay1);
}

QPushButton *Calculator::newBut(const QString &str)
{
    nB=new QPushButton(str);
    nB->setMinimumSize(40,40);
    nB->setStyleSheet("QPushButton:hover{ background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 yellow, stop: 0.4 orange, stop:1 yellow);"
                             "color: white; font-size: 15px; font-weight: bold; border-color:orange;  border-radius:5px;}"
                      "QPushButton{ margin: 1.2px; background: qlineargradient(x1:0, y1:0, x2:1, y2:1,stop:0 white, stop: 0.4 orange, stop:1 red);"
                                                   "color: white; border-color:orange; border-radius:5px;}");
    QObject::connect(nB,SIGNAL(clicked()),SLOT(displayPushBut()));
    return nB;
}

void Calculator::calcul()
{
    double rez;

  if (vec[1]=="√")
   {
      double dat1=vec[0].toDouble();
      rez=qSqrt(dat1);
   }

  if (vec[1]=="1/x")
   {
      double dat1=vec[0].toDouble();
      rez=1/dat1;
   }

  if ((vec[1]=="+")||(vec[1]=="-")||(vec[1]=="*")||(vec[1]=="/"))
   {
     double dat1=vec[0].toDouble();
     QString oper=vec[1];
     double dat2=vec[2].toDouble();

     if (oper=="+")
     rez=dat1+dat2;

     if (oper=="-")
     rez=dat1-dat2;

     if (oper=="*")
     rez=dat1*dat2;

     if (oper=="/")
      {
         if (dat2==0)
        {
         rez=0;
         monit2->setText("error");
         return;}
         else rez=dat1/dat2;
      }
  }
   monit1->clear();
   monit1->insertPlainText(QString::number(rez));
   vec.clear();
   vec.push_back(QString::number(rez));

}
void Calculator::displayPushBut()
{
  QString str1=((QPushButton*)sender())->text();

   if (str1=="CE")
   {
       monit1->clear();
       monit2->clear();
       vec.clear();
       str1="";
    }

   if ((str1=="."))
       monit2->insertPlainText(str1);

   if ((str1.contains(QRegExp("[0-9]")))&&(str1!="1/x")&&(str1!="+/-"))
       monit2->insertPlainText(str1);

   if ((str1=="√")||(str1=="1/x"))
        {
          QString str2;
          str2=monit2->toPlainText();
         if (vec.count()==0)
          {
             vec.push_back(str2);
             vec.push_back(str1);
             monit2->clear();
             calcul();
          }
         else
         {
            if (str2.size()!=0)
            {
              QString str1_data,str1_operat,str_rez;
              str1_data=vec[0];
              str1_operat=vec[1];
              vec.clear();
              vec<<str2<<str1;
              calcul();
              monit2->clear();
              monit1->clear();
              str_rez=vec[0];
              vec.clear();
              vec<<str1_data<<str1_operat<<str_rez;
              calcul();
             }
            else
            {
             vec.push_back(str1);
             monit1->clear();
             monit2->clear();
             calcul();
            }
        }
   }

   if ((str1=="+")||(str1=="-")||(str1=="*")||(str1=="/"))
        {
           if (vec.count()==1)
             {
              monit1->insertPlainText(str1);
              vec.push_back(str1);
              monit2->clear();
             }
            else
             {
                QString str_2;
                str_2=monit2->toPlainText();
                monit1->insertPlainText(str_2);
                monit1->insertPlainText(str1);
                vec.push_back(str_2);
                vec.push_back(str1);
                monit2->clear();

                 if (vec.count()>3)
                  {
                      calcul();
                      monit1->insertPlainText(str1);
                      vec.push_back(str1);
                  }
             }
        }

    if (str1=="=")
     {
       if ((monit2->toPlainText().size()==0)&&(vec.size()!=0))
        {
            vec.push_back(vec[0]);
            calcul();
         }
        if ((monit2->toPlainText().size()>0)&&(vec.size()==2))
        {
        vec.push_back(monit2->toPlainText());
        monit1->clear();
        monit2->clear();
        calcul();
        }
     }

    if (str1=="<-")
     {
        QString str_2;
        str_2=monit2->toPlainText();
        monit2->clear();
        monit2->insertPlainText(str_2.remove(str_2.length()-1,1));
    }

    if (str1=="+/-")
     {
        QString str_mon2; double str_3;
        str_mon2=monit2->toPlainText();

        if (str_mon2.size()>0)
        {
          str_3=str_mon2.toDouble();
          str_3=str_3*(-1);
          monit2->clear();
          monit2->insertPlainText(QString::number(str_3));
         }

        if ((str_mon2.size()==0)&&(vec.size()>0))
           {
              str_3=vec[0].toDouble();
                str_3=str_3*(-1);
                   monit1->clear();
                   monit1->insertPlainText(QString::number(str_3));
                   vec.clear();
                   vec.push_back( monit1->toPlainText());
            }
    }
      monit1->setAlignment(Qt::AlignRight);
      monit2->setAlignment(Qt::AlignRight);
}

