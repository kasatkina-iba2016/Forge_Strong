#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QtWidgets>
#include <QSortFilterProxyModel>
#include <QDate>
#include <QFile>

class ProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ProxyModel(QObject* parent = 0);
    ~ProxyModel();
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
public slots:
    void setFilterMinDate (const QDate &date);
    void setFilterMaxDate (const QDate &date);
private:
    QDate minDate;
    QDate maxDate;
};

#endif // PROXYMODEL_H
