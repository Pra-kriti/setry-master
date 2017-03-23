#ifndef STOCK_H
#define STOCK_H
#include <widget.h>
#include <QDialog>

namespace Ui {
class Stock;
}

class Stock : public QDialog
{
    Q_OBJECT

public:
    explicit Stock(QWidget *parent = 0);
    ~Stock();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Stock *ui;
};

#endif // STOCK_H
