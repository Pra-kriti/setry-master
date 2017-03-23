#ifndef MODDEL_H
#define MODDEL_H

#include <QDialog>
#include <widget.h>
#include <QSqlQueryModel>
#include <newhome1.h>

namespace Ui {
class ModDel;
}

class ModDel : public QDialog
{
    Q_OBJECT

public:
    explicit ModDel(QWidget *parent = 0);
    ~ModDel();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ModDel *ui;
};

#endif // MODDEL_H
