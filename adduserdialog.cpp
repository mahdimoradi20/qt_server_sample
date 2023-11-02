#include "adduserdialog.h"
#include "ui_adduserdialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();
    if(!db.isOpen()){
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
        this->close();
    }

}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::on_btnReject_clicked()
{
    this->reject();
}

QString AddUserDialog::validate()
{
    if(ui->textFullName->text() == "") return "نام و نام خانوادگی نمیتواند خالی باشد";
    if(ui->textUsername->text() == "") return "نام کاربری نمیتواند خالی باشد";
    if(ui->textPassword->text() == "") return "کلمه عبور نمیتواند خالی باشد";
    if(ui->textRepeatedPassword->text() == "") return "تکرار کلمه عبور نمیتواند خالی باشد ";
    if(ui->textPassword->text() != ui->textRepeatedPassword->text()) return "کلمه عبور با تکرارش همخوانی ندارد";

    return "none";
}


void AddUserDialog::on_btnRegister_clicked()
{
    QString validation = validate();
    if(validation == "none"){

        QString command = "INSERT INTO users (full_name , username , password) VALUES (:full_name , :username , :password)";
        QSqlQuery query;
        query.prepare(command);
        query.bindValue(":full_name" , ui->textFullName->text());
        query.bindValue(":username" , ui->textUsername->text());
        query.bindValue(":password" , QString(QCryptographicHash::hash(ui->textPassword->text().toUtf8(),QCryptographicHash::Md5).toHex()));

        if(query.exec()){
            QMessageBox::warning(this , "موفق" , " اطلاعات کاربر با موفقیت ثبت شد");
            ui->textFullName->setText("");
            ui->textPassword->setText("");
            ui->textRepeatedPassword->setText("");
            ui->textUsername->setText("");
        }else{
            QMessageBox::warning(this , "خطا" , " در هنگام ثبت اطلاعات خطایی رخ داد");
            qInfo() << query.lastError().text();
        }


    }else{
        QMessageBox::warning(this , "خطا" , validation);
    }
}

