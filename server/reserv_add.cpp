#include "reserv_add.h"
#include "ui_reserv_add.h"

reserv_add::reserv_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv_add)
{
    ui->setupUi(this);
}

reserv_add::~reserv_add()
{
    delete ui;
}
