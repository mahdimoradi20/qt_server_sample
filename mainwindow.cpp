#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();
    if(!db.isOpen()){
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
        this->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_app_triggered()
{
    this->close();
}


void MainWindow::on_add_new_user_triggered()
{
    AddUserDialog *dialog = new AddUserDialog(this);
    dialog->show();
}



void MainWindow::on_show_all_users_triggered()
{
    ShowUsersDialog *dialog = new ShowUsersDialog(this);
    dialog->show();
}

