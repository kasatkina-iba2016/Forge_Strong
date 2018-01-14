#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets>
#include <QFile>

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(const QString title,QWidget *parent = 0);
    ~Dialog();
    QString getInputName() const;
    QString getInputNumber() const;
    QString getInputService() const;
    QString getInputCena() const;
    QString cena;
    QTextEdit *numberTextEdit, *nameTextEdit, *cerviceTextEdit;
    QPushButton *tableNameButton, *tableCerviceButton, *saveButton, *cancelButton;

public slots:
    void selectNameSlot();
    void selectCerviceSlot();
};

#endif // DIALOG_H
