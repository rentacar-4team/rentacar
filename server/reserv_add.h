#ifndef RESERV_ADD_H
#define RESERV_ADD_H

#include <QDialog>

namespace Ui {
class reserv_add;
}

class reserv_add : public QDialog
{
    Q_OBJECT

public:
    explicit reserv_add(QWidget *parent = nullptr);
    ~reserv_add();

private:
    Ui::reserv_add *ui;
};

#endif // RESERV_ADD_H
