#include "reserv_edit.h"
#include "ui_reserv_edit.h"

reserv_edit::reserv_edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserv_edit)
{
    ui->setupUi(this);
}

reserv_edit::~reserv_edit()
{
    delete ui;
}
