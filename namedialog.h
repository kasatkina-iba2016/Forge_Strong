#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H

#include <QtWidgets>

class NameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NameDialog(const QString title, const QString headerName1, const QString headerName2,QWidget *parent = 0);
    ~NameDialog();
    QString getInputName() const;
    QString getInputTelephone() const;
    QDialogButtonBox *buttonBox;
    QTextEdit *nameTextEdit, *telephoneTextEdit;
    QPushButton *saveButton, *cancelButton;

};

#endif // NAMEDIALOG_H
