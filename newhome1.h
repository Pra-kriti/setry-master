
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
    QString ID,FName,LName,Address,Age,Sex,Contact,Salespoint,modID,field;

    QString ID_1,Quantity,ExpDate1,CPR,CPA,SPR,SPA,Itemsname,Location_Name,NewUser,NewPass;
public:
    explicit newhome1(QWidget *parent = 0);
    int selector,selectorUpdate,UpdateSel;
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

    void on_selector_clicked();

    void on_ModifyDrugButton_clicked();

    void on_VS_1_clicked();

    void on_ClearSales_2_clicked();

    void on_expDatebutton_2_clicked();

    void on_StockButton_2_clicked();

private:
    Ui::newhome1 *ui;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // NEWHOME1_H
