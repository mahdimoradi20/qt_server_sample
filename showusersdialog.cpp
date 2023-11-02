#include "showusersdialog.h"
#include "ui_showusersdialog.h"

ShowUsersDialog::ShowUsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowUsersDialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();
    if(!db.isOpen()){
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
        this->close();
    }

    init_users();

}



ShowUsersDialog::~ShowUsersDialog()
{
    delete ui;
}

void ShowUsersDialog::init_users()
{
    QSqlQuery query;
    QString command = "SELECT * FROM users ORDER BY created_at DESC";
    if(query.exec(command)){

        model.insertColumn(3);
        model.insertRow(query.size());

        QStringList headers;
        headers.append("شناسه کاربری");
        headers.append("نام و نام خانوادگی");
        headers.append("نام کاربری");

        model.setHorizontalHeaderLabels(headers);

        int i = 0;
        while(query.next()){


            QStandardItem *item_id = new QStandardItem(query.value(0).toString());
            model.setItem(i , 0 , item_id );

            QStandardItem *item_full_name = new QStandardItem(query.value(1).toString());
            model.setItem(i , 1 , item_full_name );

            QStandardItem *item_username = new QStandardItem(query.value(2).toString());
            model.setItem(i , 2 , item_username );

            i++;
        }


        ui->tblUsers->setModel(&model);


    }else{
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
    }
}



