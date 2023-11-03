#include "showcardsdialog.h"
#include "ui_showcardsdialog.h"

showCardsDialog::showCardsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showCardsDialog)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();
    if(!db.isOpen()){
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
        this->close();
    }

    init_cars();
}

showCardsDialog::~showCardsDialog()
{
    delete ui;
}

void showCardsDialog::init_cars()
{
    QSqlQuery query;
    QString command = "SELECT cars.id , users.full_name as user_full_name , cars.full_name , cars.gender , cars.year , cars.name , cars.color , cars.place , cars.national_code , cars.address , cars.passenger_count , cars.health , cars.created_at FROM users , cars WHERE users.id = cars.user_id ORDER BY created_at DESC";
    if(query.exec(command)){

        model.insertColumn(12);
        model.insertRow(query.size());

        QStringList headers;
        headers.append("شناسه ");
        headers.append("نام کاربر");
        headers.append("نام مالک");
        headers.append("کد ملی");
        headers.append("آدرس");
        headers.append("جنسیت");
        headers.append("مدل");
        headers.append("نام");
        headers.append("رنگ");
        headers.append("مکان");
        headers.append("سرنشین");
        headers.append("درصد سلامتی");
        headers.append("تاریخ ایجاد");


        model.setHorizontalHeaderLabels(headers);

        int i = 0;
        while(query.next()){


            QStandardItem *item_1 = new QStandardItem(query.value(0).toString());
            item_1->setTextAlignment(Qt::AlignCenter);
            model.setItem(i , 0 , item_1 );

            QStandardItem *item_2 = new QStandardItem(query.value(1).toString());
            model.setItem(i , 1 , item_2 );

            QStandardItem *item_3 = new QStandardItem(query.value(2).toString());
            model.setItem(i , 2 , item_3 );


            QStandardItem *item_4 = new QStandardItem(query.value(8).toString());
            model.setItem(i , 3 , item_4 );

            QStandardItem *item_5 = new QStandardItem(query.value(9).toString());
            model.setItem(i , 4 , item_5 );


            QString gender = "مرد";
            if(query.value(3).toString() == "female") gender = "زن";

            QStandardItem *item_6 = new QStandardItem(gender);
            model.setItem(i , 5 , item_6 );

            QStandardItem *item_7 = new QStandardItem(query.value(4).toString());
            model.setItem(i , 6 , item_7 );


            QStandardItem *item_8 = new QStandardItem(query.value(5).toString());
            model.setItem(i , 7 , item_8 );



            QStandardItem *item_9 = new QStandardItem(query.value(6).toString());
            model.setItem(i , 8 , item_9 );


            QStandardItem *item_10 = new QStandardItem(query.value(7).toString());
            model.setItem(i , 9 , item_10 );


            QStandardItem *item_11 = new QStandardItem(query.value(10).toString());
            model.setItem(i , 10 , item_11 );


            QStandardItem *item_12 = new QStandardItem(query.value(11).toString());
            model.setItem(i , 11 , item_12 );

            QString date_and_time = query.value(12).toString();
            QString date = date_and_time.split("T")[0];
            QString time = date_and_time.split("T")[1];
            long year = date.split("-")[0].toLong();
            long month = date.split("-")[1].toLong();
            long day = date.split("-")[2].toLong();

            QStandardItem *item_13 = new QStandardItem(gregorian_to_jalali(year , month , day) + " " + time.mid(0 , 8));
            model.setItem(i , 12 , item_13 );

            i++;
        }


        ui->tblCars->setModel(&model);


    }else{
        qInfo() << query.lastError();
        QMessageBox::critical(this , "خطا" , "خطای برقراری ارتباط با پایگاه داده");
    }
}

QString showCardsDialog::gregorian_to_jalali(long gy, long gm, long gd)
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
