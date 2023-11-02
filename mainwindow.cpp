#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&server , &Server::data_recived , this , &MainWindow::data_recived);


    if(!server.start(8080)){
        QMessageBox::critical(this , "خطا" , "امکان برقراری ارتباط با شبکه وجود ندارد");
        this->close();
    }

    ui->statusbar->showMessage("سرور آماده به کار است...");

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

void MainWindow::data_recived(QJsonDocument data , QTcpSocket *socket)
{
    qInfo() << data["action"].toString();
    if(data["action"].toString() == "login"){

        ui->statusbar->showMessage("اعتبار سنجی کاربر جدید..." , 3000 ) ;

        QString username = data["username"].toString();
        QString password = data["password"].toString();


        //Chekc database for user credentials

        QSqlQuery query;
        QString command = "SELECT id , full_name FROM users WHERE username = :username AND password = :password";
        query.prepare(command);
        query.bindValue(":username" , username);
        query.bindValue(":password" , QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Md5).toHex()));

        QVariantMap map;
        QString status = "";
        QString message = "";
        QString full_name = "";
        QString token = "none";


        if(query.exec()){
            qInfo() <<query.executedQuery();
            if(query.size() > 0){
                status = "ok";
                message = "welcome!";
                query.next();
                token = register_new_access_token(query.value(0).toInt());
                full_name = query.value(1).toString();
                if(token == "error"){
                    status = "error";
                    message = "cannot specify token try again later";
                }
            }else{
                status = "error";
                message = "username or password is wrong";
            }
        }else{
            status = "error";
            message = "something went wrong";
        }

        map.insert("status" , status);
        map.insert("message" ,message);
        map.insert("access_token" ,token);
        map.insert("full_name" ,full_name);
        server.send(map , socket);



    }
}

QString MainWindow::register_new_access_token(int user_id)
{
    QSqlQuery query;

    QString phrase = QString::number(user_id) + QString::number(QDateTime::currentSecsSinceEpoch());
    QString token = QString(QCryptographicHash::hash(phrase.toUtf8(),QCryptographicHash::Md5).toHex());

    QString command = "INSERT INTO user_access_tokens (user_id , token) VALUES (:user_id , :token)";
    query.prepare(command);
    query.bindValue(":user_id" , user_id);
    query.bindValue(":token" , token);

    if(query.exec())return token;
    else return "error";

}

