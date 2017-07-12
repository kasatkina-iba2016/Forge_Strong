#ifndef FACADE_H
#define FACADE_H
#include <QWidget>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSqlTableModel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QTableView>
#include <QSqlQuery>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include "proxymodel.h"
#include "edit.h"

class Facade : public QWidget
{
    Q_OBJECT

public:
    Facade(const QString &mainTableName ,QWidget *parent = 0);
    ~Facade();

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    QToolBar *ptb1,*ptb2;
    QAction *addAction, *delAction, *changeAction, *okAction, *sortAzAction, *sortZaAction,
    *searchAction;
    int count;
    QString ab4z, ab8z, ab12z, ab1m, ab3m, ab6m;
    Information *inform;
    QTableView *view;
    QSqlTableModel *model;
    ProxyModel *proxyMod;
    QCalendarWidget *calendar1;
    QCalendarWidget *calendar2;
    QTextEdit *data1,*data2,*find;
    QMenu *calendarMenu1;
    QMenu *calendarMenu2;
    QString podate;

signals:
    void signalMinDate(QDate datMin);
    void signalMaxDate(QDate datMax);
    void signalText (QString str);
public slots:
    void addNameSlot();
    void delNameSlot();
    void addInformSlot();
    void fileSaveAs();
    void getData();
    void getMinDate();
    void getMaxDate();
    void changeDateSlot1(QDate dat);
    void changeDateSlot2(QDate dat);
    void AzSlot();
    void ZaSlot();

 };

#endif // FACADE_H
