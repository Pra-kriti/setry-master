#ifndef NEWHOME_H
#define NEWHOME_H
#include <widget.h>

#include <QWidget>

namespace Ui {
class newhome;
}

class newhome : public QWidget
{
    Q_OBJECT

public:
    explicit newhome(QWidget *parent = 0);
    int selector;// selects choise of sreen for search
    ~newhome();

private slots:
    void on_ViewStaff_clicked();
    void update1();
    void on_SearchButton_clicked();
    void update3();
    void on_BackButton_clicked();
   // void update2();
    void on_GTS_clicked();

    void on_ViewSuper_clicked();


    void on_ChangeSuper_clicked();

    void on_Yes_clicked();

    void on_No_clicked();

    void on_LogOut_1_clicked();

public slots:
    void on_ExistSuper_clicked();

private:
    Ui::newhome *ui;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // NEWHOME_H
