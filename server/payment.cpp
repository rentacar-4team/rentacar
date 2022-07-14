#include "payment.h"
#include "ui_payment.h"
#include <QMessageBox>

payment::payment(std::vector <std::string> data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
    text_setting(data);

}

payment::~payment()
{
    delete ui;
}

void payment::text_setting(std::vector <std::string> data)
{
    reserv_num = data[0];
    ID = data[1];
    total = data[2];
    ui->total_txt->setText(QString::fromStdString(data[2]));
    query = "SELECT point FROM member WHERE id = '" + ID +"'";
    sql.exec(QString::fromStdString(query));
    record = sql.record();
    sql.next();
    int pointnum = record.indexOf("point");
    QString point = sql.value(pointnum).toString();
    ui->point_txt->setText(point);
}

void payment::on_point_btn_clicked()
{
    int point = ui->point_txt->text().toInt();
    ui->point_txt->setText("0");
    int totalcharge = ui->total_txt->text().toInt();
    totalcharge = totalcharge - point;
    qDebug() << totalcharge;
    QString charge = QString::number(totalcharge);
    ui->total_txt->setText(charge);
}


void payment::on_pay_btn_clicked()
{
    if(ui->card_txt->text() == NULL)
        QMessageBox::warning(this, "", "카드회사를 입력하세요");
    else if( ui->cardnum_txt->text() == NULL)
        QMessageBox::warning(this, "", "카드번호를 입력하세요");
    else
    {
        query = "UPDATE member SET point = '" + ui->point_txt->text().toStdString() + "' WHERE id = '" + ID + "'";
        sql.exec(QString::fromStdString(query));
        query = "UPDATE reservation SET pay = 'O' WHERE num = '" + reserv_num + "'";
        sql.exec(QString::fromStdString(query));
        QMessageBox::information(this, "", "결제완료");
        this->close();
    }

}
