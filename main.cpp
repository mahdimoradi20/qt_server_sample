#include "mainwindow.h"

#include <QApplication>
#include<QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("qt_test_db");
    db.setUserName("root");
    db.setPassword("");


    MainWindow w;
    w.show();
    return a.exec();
}
