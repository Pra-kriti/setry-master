
#ifndef NEWHOME2_H
#define NEWHOME2_H

#include <QWidget>

namespace Ui {
class newhome2;
}

class newhome2 : public QWidget
{
    Q_OBJECT

public:
    explicit newhome2(QWidget *parent = 0);
    ~newhome2();

private slots:
    void on_SearchBar_staff_clicked();

private:
    Ui::newhome2 *ui;
};

#endif // NEWHOME2_H
