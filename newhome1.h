
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
    QString ID,FName,LName,Address,Age,Sex,Contact,Salespoint,modID;
    QString ID_1,Quantity,ExpDate,CPR,CPA,SPR,SPA,Itemsname,Location_Name;
public:
    explicit newhome1(QWidget *parent = 0);
    int selector,selectorUpdate;
    ~newhome1();

private slots:
    void on_BackButton_1_clicked();
    void update2();
    void on_GTS_1_clicked();

    void on_SearchButton_1_clicked();

    void on_ViewStaff_clicked();

    void on_ExistStaff_clicked();

    void on_NewStaff_clicked();
    void modifyFormHide();
    void modifyFormShow();
    void on_AddStaff_clicked();
    void modifySelectionHide();
    void on_ModifyStaff_clicked();

    void on_Select_clicked();

private slots:
    void on_DelButton_clicked();

    void on_LogOut_clicked();

    void on_UpdateData_clicked();



    void on_ModifyDrug_clicked();

    void on_DeleteDrug_clicked();

    void on_AddDrug_clicked();

private:
    Ui::newhome1 *ui;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // NEWHOME1_H
