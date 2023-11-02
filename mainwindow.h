#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "adduserdialog.h"

#include<QMessageBox>

#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include "showusersdialog.h"
#include "server.h"
#include<QTcpServer>
#include<QTcpSocket>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonDocument>

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

    void data_recived(QJsonDocument data , QTcpSocket *socket);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    Server server;
    QString register_new_access_token(int user_id);
};
#endif // MAINWINDOW_H
