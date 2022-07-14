#include "chatting.h"
#include "ui_chatting.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>


chatting::chatting(QTcpSocket * socket,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatting)
{
    ui->setupUi(this);
    clntsocket = socket;
    thread = new Thread(clntsocket, this);
    connect(thread, SIGNAL(setValue(QString)), this, SLOT(show(QString)));
    connect(thread, SIGNAL(alarmSetting(QString)), this, SLOT(alarm(QString)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

chatting::~chatting()
{
    delete ui;
}

void chatting::show(QString msg)
{
    ui->textBrowser->append(msg);
}

void chatting::alarm(QString message)
{
    ui->textBrowser->append(message);
    QMessageBox::information(this, "", "채팅이 종료되었습니다");
    ui->send_btn->setEnabled(false);
    this->close();
}


void chatting::on_send_btn_clicked()
{
    if(ui->line->text() != "")
    {
        std::string msg = "[고객센터]" + ui->line->text().toStdString();
        ui->line->clear();
        clntsocket->write(msg.c_str());
        clntsocket->flush();
        clntsocket->bytesWritten(3000);
        ui->textBrowser->append(QString::fromStdString(msg));
    }

}