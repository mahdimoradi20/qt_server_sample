#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

#include<QSqlDatabase>
#include<QtSql>
#include<QSqlQuery>
#include<QMessageBox>


namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

private slots:
    void on_btnReject_clicked();

    void on_btnRegister_clicked();

private:
    Ui::AddUserDialog *ui;
    QSqlDatabase db;
    QString validate();
};

#endif // ADDUSERDIALOG_H
