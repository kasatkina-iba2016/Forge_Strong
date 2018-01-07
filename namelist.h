#ifndef NAMELIST_H
#define NAMELIST_H

#include <QtWidgets>
#include <QDialog>
#include <QTableView>
#include <QSqlTableModel>
#include <QTextEdit>
#include <QDialogButtonBox>

class nameList : public QDialog
{
    Q_OBJECT
public:
    nameList(const QString &titleName, const QString &nameTableName, const QString &headerName1,const QString &headerName2,
                      QWidget *parent = 0);
    ~nameList();

public:

    int count;
    QTextEdit *find;
    QToolBar *ptb1;
    QAction *newAddAction, *delAction, *acceptAction, *searchAction,
            *sortAzAction, *sortZaAction;
    QString name1, name2;
    QString getInput() const;
    QString getInput2() const;

private:
    QTableView *view;
    QSqlTableModel *model;

private slots:
      void addNewStringSlot();
      void delStringSlot();
      void getData();
      void AzSlot();
      void ZaSlot();
};

#endif // NAMELIST_H
