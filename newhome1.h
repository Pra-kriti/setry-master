
#ifndef NEWHOME1_H
#define NEWHOME1_H
#include <widget.h>

#include <QWidget>

namespace Ui {
class newhome1;
}

class newhome1 : public QWidget
{
    Q_OBJECT

public:
    explicit newhome1(QWidget *parent = 0);
    int selector;
    ~newhome1();

private slots:
    void on_BackButton_1_clicked();
    void update2();
    void on_GTS_1_clicked();

    void on_SearchButton_1_clicked();

private:
    Ui::newhome1 *ui;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // NEWHOME1_H
