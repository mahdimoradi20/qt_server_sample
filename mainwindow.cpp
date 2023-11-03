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

    init_user_cars();
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
    qInfo() << data;

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
                }else{
                    ui->listOnlineUsers->addItem("کاربر " + full_name);
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
        map.insert("action" ,"login");
        server.send(map , socket);



    }
    else if(data["action"].toString() == "submit_form"){

        QVariantMap map;
        QString status = "";
        QString message = "";

        ui->statusbar->showMessage("ثبت خودرو جدید..." , 3000 ) ;

        int user_id = validate_access_token(data["access_token"].toString());

        if(user_id == 0){
            status = "error";
            message = "access denied";
        }else{
            QSqlQuery query;
            QString command = "INSERT INTO cars (user_id , year,full_name , gender , name , color , place , national_code , address , passenger_count , health) VALUES (:user_id , :year ,:full_name , :gender , :name , :color , :place , :national_code , :address , :passenger_count , :health) ";

            query.prepare(command);
            query.bindValue(":full_name" , data["full_name"].toString());
            query.bindValue(":gender" , data["gender"].toString());
            query.bindValue(":name" , data["name"].toString());
            query.bindValue(":color" , data["color"].toString());
            query.bindValue(":place" , data["place"].toString());
            query.bindValue(":national_code" , data["national_code"].toString());
            query.bindValue(":address" , data["address"].toString());
            query.bindValue(":passenger_count" , data["passenger_count"].toInt());
            query.bindValue(":health" , data["health"].toInt());
            query.bindValue(":year" , data["year"].toInt());
            query.bindValue(":user_id" , user_id);

            if(query.exec()){
                status = "ok";
                message = "form has been saved";

            }else{
                status = "error";
                message = "something went wrong";
            }
        }

        map.insert("status" , status);
        map.insert("message" ,message);
        map.insert("action" ,"submit_form");
        server.send(map , socket);

    }else if(data["action"].toString() == "logout"){


        QVariantMap map;
        QString status = "";
        QString message = "";

        QString access_token = data["access_token"].toString();

        QString result = release_access_token(access_token);

        if(result == "error"){
            status = "error";
            message = "somrthing went wrong";
        }else if(result == "none"){
            status = "error";
            message = "not a valid access token";
        }else{
            status = "ok";
            message = "log out safely";
        }


        QList<QListWidgetItem*> items = ui->listOnlineUsers->findItems(result , Qt::MatchContains);
        foreach (QListWidgetItem* item, items) {
            int row = ui->listOnlineUsers->row(item);
            ui->listOnlineUsers->takeItem(row);
        }
        map.insert("status" , status);
        map.insert("message" ,message);
        map.insert("action" ,"logout");


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

int MainWindow::validate_access_token(QString access_token)
{
    QSqlQuery query;
    QString command = "SELECT id , user_id FROM user_access_tokens WHERE token = :token";

    query.prepare(command);
    query.bindValue(":token" , access_token);

    if(query.exec()){
        if(query.size() > 0) {
            query.next() ;
            return query.value(1).toInt();
        }
        else return 0;
    }else{
        return 0;
    }

}

QString MainWindow::release_access_token(QString access_token)
{
    QSqlQuery query;
    QString command = "SELECT user_access_tokens.id , users.id as user_id , users.full_name FROM user_access_tokens , users WHERE user_access_tokens.user_id = users.id  AND  user_access_tokens.token = :token";

    query.prepare(command);
    query.bindValue(":token" , access_token);

    if(query.exec()){
        if(query.size() > 0) {
            query.next() ;
            int token_id = query.value(0).toInt();
            QString full_name = query.value(2).toString();
            command = "DELETE FROM user_access_tokens WHERE id = :token_id";
            query.prepare(command);
            query.bindValue(":token_id" , token_id);
            if(query.exec()){
                return full_name;
            }else{
                return "error";
            }
        }
        else return "none";
    }else{
        return "error";
    }

}

void MainWindow::init_user_cars()
{


    QStandardItem *root = model.invisibleRootItem();
    QStringList headers;
    headers << "";
    model.setHorizontalHeaderLabels(headers);

    QSqlQuery query;
    QString command = "SELECT id, full_name FROM users";


    if(!query.exec(command)) return;
    while(query.next()){

        QSqlQuery query_cars;
        QString command_cars = "SELECT id, name FROM cars WHERE user_id = :user_id";
        query_cars.prepare(command_cars);
        query_cars.bindValue(":user_id" , query.value(0).toInt());

        //parent item
        QStandardItem *parent = new QStandardItem(query.value(1).toString());

        if(!query_cars.exec()) break;
        if(query_cars.size() == 0) continue;

        while(query_cars.next()){
            //child item
            QStandardItem *child = new QStandardItem(query_cars.value(1).toString());
            parent->appendRow(child);
        }
        root->appendRow(parent);
    }
    ui->treeUserCars->setModel(&model);
}



void MainWindow::on_action_triggered()
{
    showCardsDialog *dialog = new showCardsDialog(this);
    dialog->show();
}

