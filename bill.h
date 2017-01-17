#ifndef BILL_H
#define BILL_H
#include "widget.h"
#include "newhome2.h"
#include <QDialog>
#include <widget.h>
#include <QSqlQueryModel>

namespace Ui {
class bill;
}

class bill : public QDialog
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = 0);
    ~bill();

private slots:
    void on_CONFIRM_clicked();

private:
    Ui::bill *ui;
};

#endif // BILL_H
