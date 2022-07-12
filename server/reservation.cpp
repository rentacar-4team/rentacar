#include "reservation.h"
#include "ui_reservation.h"
#include <QMessageBox>

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
    int charge = record.indexOf("charge");
    int reserv_date = record.indexOf("reserv_date");
    int return_date = record.indexOf("return_date");
    ui->reserv_list->setRowCount(sql.size());
    ui->reserv_list->setColumnCount(record.count());
    ui->reserv_list->setHorizontalHeaderItem(0, new QTableWidgetItem("예약번호"));
    ui->reserv_list->setHorizontalHeaderItem(1, new QTableWidgetItem("아이디"));
    ui->reserv_list->setHorizontalHeaderItem(2, new QTableWidgetItem("자동차모델"));
    ui->reserv_list->setHorizontalHeaderItem(3, new QTableWidgetItem("차종"));
    ui->reserv_list->setHorizontalHeaderItem(4, new QTableWidgetItem("요금"));
    ui->reserv_list->setHorizontalHeaderItem(5, new QTableWidgetItem("예약날짜"));
    ui->reserv_list->setHorizontalHeaderItem(6, new QTableWidgetItem("반납날짜"));
    ui->reserv_list->horizontalHeader()->setStretchLastSection(true);
    int i =0;
    while(sql.next())
    {
        ui->reserv_list->setItem(i, 0, new QTableWidgetItem(sql.value(num).toString()));
        ui->reserv_list->setItem(i, 1, new QTableWidgetItem(sql.value(id).toString()));
        ui->reserv_list->setItem(i, 2, new QTableWidgetItem(sql.value(model).toString()));
        ui->reserv_list->setItem(i, 3, new QTableWidgetItem(sql.value(car_type).toString()));
        ui->reserv_list->setItem(i, 4, new QTableWidgetItem(sql.value(charge).toString()));
        ui->reserv_list->setItem(i, 5, new QTableWidgetItem(sql.value(reserv_date).toString()));
        ui->reserv_list->setItem(i++, 6, new QTableWidgetItem(sql.value(return_date).toString()));
    }
}

void reservation::on_add_btn_clicked()
{

}

void reservation::on_edit_btn_clicked()
{

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
        qDebug() << QString::fromStdString(query);
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "", "삭제완료");
        list();
    }
}
