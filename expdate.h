#ifndef EXPDATE_H
#define EXPDATE_H
#include <widget.h>
#include <QDialog>

namespace Ui {
class ExpDate;
}

class ExpDate : public QDialog
{
    Q_OBJECT

public:
    explicit ExpDate(QWidget *parent = 0);
    ~ExpDate();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ExpDate *ui;
};

#endif // EXPDATE_H
