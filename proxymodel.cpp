#include "proxymodel.h"
#include <QDebug>

ProxyModel::ProxyModel(QObject *parent): QSortFilterProxyModel(parent)

{
    minDate.setDate(2017,01,01);
    maxDate=QDate::currentDate();
}

ProxyModel::~ProxyModel()
{

}

bool ProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex from_date=sourceModel()->index(source_row,1,source_parent);
    QModelIndex to_date=sourceModel()->index(source_row,1,source_parent);

    if (QDate::fromString(sourceModel()->data(from_date).toString(),"dd.MM.yyyy")>= minDate &&
    QDate::fromString(sourceModel()->data(to_date).toString(),"dd.MM.yyyy") <=maxDate)
{
        return true;
}
        return false;
}

void ProxyModel::setFilterMinDate(const QDate &date)
{
    minDate=date;
    invalidateFilter();
}

void ProxyModel::setFilterMaxDate(const QDate &date)
{
    maxDate=date;
    invalidateFilter();
}


