#ifndef EDIT_H
#define EDIT_H

#include <QObject>
#include <QtWidgets>
#include <QDataWidgetMapper>
#include <information.h>
#include <QSqlTableModel>

class Edit : public QWidget
{
    Q_OBJECT
public:
    explicit Edit(QWidget *parent = 0);
    void setModel(QSqlTableModel *model);
    GeneralTab *inform;
    QDataWidgetMapper *mapper;
private:

signals:

public slots:
};

#endif // EDIT_H
