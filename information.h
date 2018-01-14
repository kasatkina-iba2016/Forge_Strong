#ifndef INFORMATION_H
#define INFORMATION_H

#include <QtWidgets>
#include <QSqlTableModel>

    class GeneralTab : public QWidget
     {
         Q_OBJECT

     public:

         GeneralTab(QWidget *parent = 0);
         ~GeneralTab();
         QDataWidgetMapper *mapper;
         QTextEdit *numberEdit,*nameEdit,*dateEdit,*serviceEdit,*balanseEdit;
         QPushButton *tableNameButton;
         void setMyModel (QSqlTableModel *model);
         void setIndex (int row);

     private slots:
         void selectNameSlot();
       };

     class PermissionsTab : public QWidget
     {
         Q_OBJECT

     public:
         PermissionsTab(QWidget *parent = 0);
         ~PermissionsTab();

         QDataWidgetMapper *mapper2;
         QLabel *newlbl(const QString &str);
         QLabel *visitLbl;
         QList<QToolButton*> btn;
         QList<QTextEdit*> visit;
         QList<QCalendarWidget*> calendar;
         int kol=0,count=1,counti=0,countj=1, i=0, j=0, balans;
         QTextEdit *visit1,*visit2,*visit3,*visit4,*visit5,*visit6,
                   *visit7, *visit8, *visit9, *visit10, *visit11, *visit12;
         QToolButton *btn1,*btn2,*btn3,*btn4,*btn5,*btn6,*btn7,*btn8,*btn9,
                     *btn10,*btn11,*btn12;
         QMenu *calendarMenu1,*calendarMenu2,*calendarMenu3,*calendarMenu4,*calendarMenu5,*calendarMenu6,
                *calendarMenu7,*calendarMenu8,*calendarMenu9,*calendarMenu10,*calendarMenu11,*calendarMenu12;
         QCalendarWidget *calendar1,*calendar2,*calendar3,*calendar4,*calendar5,*calendar6,*calendar7,*calendar8,
                         *calendar9,*calendar10,*calendar11,*calendar12;
         QString podate="";

         void setMyModel2 (QSqlTableModel *model);
         void setIndex (int row);

     public  slots:
         void changeDateSlot0(QDate dat);
         void changeDateSlot1(QDate dat);
         void changeDateSlot2(QDate dat);
         void changeDateSlot3(QDate dat);
         void changeDateSlot4(QDate dat);
         void changeDateSlot5(QDate dat);
         void changeDateSlot6(QDate dat);
         void changeDateSlot7(QDate dat);
         void changeDateSlot8(QDate dat);
         void changeDateSlot9(QDate dat);
         void changeDateSlot10(QDate dat);
         void changeDateSlot11(QDate dat);
       };

     class Information : public QDialog
     {
         Q_OBJECT
     public:

     Information(QWidget *parent = 0);
     ~Information();

     PermissionsTab *perm;
     GeneralTab *gen;

     QTabWidget *tabWidget;
     QPushButton *saveButton, *cancelButton;

     };

#endif // INFORMATION_H
