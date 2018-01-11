#ifndef NAMEFACADE_H
#define NAMEFACADE_H
#include <QTableView>
#include <QSqlTableModel>
#include <QObject>
#include <QWidget>

class nameFacade : public QWidget
{
    Q_OBJECT
public:
    nameFacade(const QString &titleName , const QString &nameTableName, const QString &headerName1, const QString &headerName2, QWidget *parent = 0);
    QTableView *view;
    QSqlTableModel *model;

signals:

public slots:
};

#endif // NAMEFACADE_H
