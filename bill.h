#ifndef BILL_H
#define BILL_H
#include "widget.h"
#include "newhome2.h"
#include <QDialog>

namespace Ui {
class bill;
}

class bill : public QDialog
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = 0);
    ~bill();

private:
    Ui::bill *ui;
};

#endif // BILL_H
