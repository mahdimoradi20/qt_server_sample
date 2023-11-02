#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduserdialog.h"

#include<QMessageBox>

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include "showusersdialog.h"

#include<QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit_app_triggered();

    void on_add_new_user_triggered();

    void on_show_all_users_triggered();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
