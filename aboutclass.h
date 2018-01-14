#ifndef ABOUTCLASS_H
#define ABOUTCLASS_H

#include <QtWidgets>

class AboutClass : public QDialog
{
    Q_OBJECT
public:
    explicit AboutClass(QWidget *parent = 0);
    ~AboutClass();

    QLabel *aboutLbl;
    QVBoxLayout *Layout1,*Layout2;
    QPushButton *butt;

};

#endif // ABOUTCLASS_H
