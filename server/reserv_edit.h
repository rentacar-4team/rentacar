#ifndef RESERV_EDIT_H
#define RESERV_EDIT_H

#include <QDialog>

namespace Ui {
class reserv_edit;
}

class reserv_edit : public QDialog
{
    Q_OBJECT

public:
    explicit reserv_edit(QWidget *parent = nullptr);
    ~reserv_edit();

private:
    Ui::reserv_edit *ui;
};

#endif // RESERV_EDIT_H
