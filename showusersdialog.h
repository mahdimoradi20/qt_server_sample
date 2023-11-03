#ifndef SHOWUSERSDIALOG_H
#define SHOWUSERSDIALOG_H

#include <QDialog>

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>

#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class ShowUsersDialog;
}

class ShowUsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowUsersDialog(QWidget *parent = nullptr);
    ~ShowUsersDialog();

private slots:


    void on_btnDelete_clicked();

private:
    Ui::ShowUsersDialog *ui;
    QSqlDatabase db;
    QStandardItemModel model;
    void init_users();
    QString gregorian_to_jalali(long gy, long gm, long gd);


};

#endif // SHOWUSERSDIALOG_H
