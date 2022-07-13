#include "reservation.h"
#include "ui_reservation.h"
#include <QMessageBox>
#include "reserv_add.h"
#include <QDebug>
#include "reserv_edit.h"

reservation::reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservation)
{
    ui->setupUi(this);
    list();
}

reservation::~reservation()
{
    delete ui;
}

void reservation::list()
{
    ui->reserv_list->clear();
    query = "SELECT * FROM reservation";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    int num = record.indexOf("num"); // DB 컬럼명
    int id = record.indexOf("id");
    int model = record.indexOf("car_model");
    int car_type = record.indexOf("car_type");
    int fuel = record.indexOf("fuel");
    int charge = record.indexOf("charge");
    int reserv_date = record.indexOf("reserv_date");
    int return_date = record.indexOf("return_date");
    ui->reserv_list->setRowCount(sql.size());
    ui->reserv_list->setColumnCount(record.count());
    ui->reserv_list->setHorizontalHeaderItem(0, new QTableWidgetItem("예약번호"));
    ui->reserv_list->setHorizontalHeaderItem(1, new QTableWidgetItem("아이디"));
    ui->reserv_list->setHorizontalHeaderItem(2, new QTableWidgetItem("자동차모델"));
    ui->reserv_list->setHorizontalHeaderItem(3, new QTableWidgetItem("차종"));
    ui->reserv_list->setHorizontalHeaderItem(4, new QTableWidgetItem("연료"));
    ui->reserv_list->setHorizontalHeaderItem(5, new QTableWidgetItem("일일요금"));
    ui->reserv_list->setHorizontalHeaderItem(6, new QTableWidgetItem("예약날짜"));
    ui->reserv_list->setHorizontalHeaderItem(7, new QTableWidgetItem("반납날짜"));
    ui->reserv_list->horizontalHeader()->setStretchLastSection(true);
    int i =0;
    while(sql.next())
    {
        ui->reserv_list->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->reserv_list->setItem(i, 1, new QTableWidgetItem(sql.value(id).toString()));
        ui->reserv_list->setItem(i, 2, new QTableWidgetItem(sql.value(model).toString()));
        ui->reserv_list->setItem(i, 3, new QTableWidgetItem(sql.value(car_type).toString()));
        ui->reserv_list->setItem(i, 4, new QTableWidgetItem(sql.value(fuel).toString()));
        ui->reserv_list->setItem(i, 5, new QTableWidgetItem(sql.value(charge).toString()));
        ui->reserv_list->setItem(i, 6, new QTableWidgetItem(sql.value(reserv_date).toString()));
        ui->reserv_list->setItem(i++, 7, new QTableWidgetItem(sql.value(return_date).toString()));
    }
}

void reservation::on_add_btn_clicked()
{
    reserv_add add;
    add.setModal(true);
    add.exec();
    list();
}

void reservation::on_edit_btn_clicked()
{
    if(ui->reserv_list->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row;
        std::vector<std::string>data;
        row = ui->reserv_list->currentRow();
        data.push_back(ui->reserv_list->takeItem(row, 0)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 1)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 2)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 3)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 4)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 5)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 6)->text().toStdString());
        data.push_back(ui->reserv_list->takeItem(row, 7)->text().toStdString());
        reserv_edit edit(data);
        edit.setModal(true);
        edit.exec();

        list();
    }

}

void reservation::on_delete_btn_clicked()
{
    if(ui->reserv_list->currentItem() == NULL)
    {
        QMessageBox::information(this, "", "선택하세요");
    }
    else
    {
        int row = ui->reserv_list->currentRow();
        query = "DELETE FROM reservation WHERE num = '" + ui->reserv_list->takeItem(row, 0)->text().toStdString() + "'";
        sql.exec(QString::fromStdString(query));
        query = "SELECT num, booking FROM rentacar WHERE carname = '" + ui->reserv_list->takeItem(row, 2)->text().toStdString() +"'";
        sql.exec(QString::fromStdString(query));
        record = sql.record();
        int booking = record.indexOf("booking");
        int carnum = record.indexOf("num");
        sql.next();
        int num = sql.value(booking).toInt();
        QString car = sql.value(carnum).toString();
        num--;
        QString number = QString::number(num);

        query = "UPDATE rentacar SET booking = '"
                + number.toStdString() + "' WHERE num = '" + car.toStdString() +"'";

        sql.exec(QString::fromStdString(query));

        QMessageBox::information(this, "", "삭제완료");

        list();
    }
}
