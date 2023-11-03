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

        model.insertColumn(4);
        model.insertRow(query.size());

        QStringList headers;
        headers.append("شناسه کاربری");
        headers.append("نام و نام خانوادگی");
        headers.append("نام کاربری");
        headers.append("تاریخ ثبت");

        model.setHorizontalHeaderLabels(headers);

        int i = 0;
        while(query.next()){


            QStandardItem *item_id = new QStandardItem(query.value(0).toString());
            model.setItem(i , 0 , item_id );

            QStandardItem *item_full_name = new QStandardItem(query.value(1).toString());
            model.setItem(i , 1 , item_full_name );

            QStandardItem *item_username = new QStandardItem(query.value(2).toString());
            model.setItem(i , 2 , item_username );

            QString date_and_time = query.value(4).toString();
            QString date = date_and_time.split("T")[0];
            QString time = date_and_time.split("T")[1];
            long year = date.split("-")[0].toLong();
            long month = date.split("-")[1].toLong();
            long day = date.split("-")[2].toLong();


            QStandardItem *item_created_at = new QStandardItem(gregorian_to_jalali(year , month , day) + " " + time.mid(0 , 8));
            model.setItem(i , 3 , item_created_at );

            i++;
        }


        ui->tblUsers->setModel(&model);


    }else{
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
    }
}

QString ShowUsersDialog::gregorian_to_jalali(long gy, long gm, long gd)
{
    int out[3];
    long days;
    {
        long gy2 = (gm > 2) ? (gy + 1) : gy;
        long g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        days = 355666 + (365 * gy) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + gd + g_d_m[gm - 1];
    }
    long jy = -1595 + (33 * ((int)(days / 12053)));
    days %= 12053;
    jy += 4 * ((int)(days / 1461));
    days %= 1461;
    if (days > 365) {
        jy += (int)((days - 1) / 365);
        days = (days - 1) % 365;
    }
    out[0] = jy;
    if (days < 186) {
        out[1]/*jm*/ = 1 + (int)(days / 31);
        out[2]/*jd*/ = 1 + (days % 31);
    } else {
        out[1]/*jm*/ = 7 + (int)((days - 186) / 30);
        out[2]/*jd*/ = 1 + ((days - 186) % 30);
    }

    QString response = QString::number(out[0]) + "/" +  QString::number(out[1]) + "/" + QString::number(out[2]);

    return response;
}



