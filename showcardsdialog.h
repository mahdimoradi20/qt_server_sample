#ifndef SHOWCARDSDIALOG_H
#define SHOWCARDSDIALOG_H

#include <QDialog>

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>

#include<QStandardItem>
#include<QStandardItemModel>

namespace Ui {
class showCardsDialog;
}

class showCardsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showCardsDialog(QWidget *parent = nullptr);
    ~showCardsDialog();

private:
    Ui::showCardsDialog *ui;

    QSqlDatabase db;
    QStandardItemModel model;
    void init_cars();
    QString gregorian_to_jalali(long gy, long gm, long gd);
};

#endif // SHOWCARDSDIALOG_H
