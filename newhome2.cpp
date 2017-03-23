#include <QSqlQueryModel>
#include <widget.h>
#include "stock.h"
#include "expdate.h"
#include "newhome2.h"
#include "bill.h"
#include "ui_newhome2.h"
#include <QDate>

newhome2::newhome2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newhome2)
{
    ui->setupUi(this);
    this->showMaximized();
     ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
    ui->groupBox->hide();
    ui->CreateBill->hide();
    ui->radioButton->show();
    ui->radioButton_2->show();
    ui->radioButton_3->show();
    ui->l8->show();

    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    QSqlQueryModel * modal1=new QSqlQueryModel();
     QSqlQueryModel * modal2=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT ID,QUANTITY,EXPDATE,SP_RATE,ITEMSNAME_1,LOCATION_NAME FROM [table] GROUP BY ID");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    qry->prepare("SELECT* FROM [table] WHERE EXPDATE<=(SELECT DATE(\'NOW\','+1 MONTH'))");
    qry->exec();

    modal2->setQuery(*qry);
    if(modal2->rowCount()>0)
    {
       ui->ExpAlertButton->setText("EXPIRY ALERT");
    }
    qry->prepare("SELECT* FROM [table] WHERE QUANTITY<=\'10\'");
    qry->exec();
    modal1->setQuery(*qry);
    if(modal1->rowCount()>0)
    {
        ui->StockButton->setText("OUT OF STOCK ALERT!");
    }
    conn.connClose();
    qDebug()<<(modal->rowCount());

    ui->ITEMS_NAME->setPlaceholderText("ITEMS_NAME");
}

newhome2::~newhome2()
{
    delete ui;
}

void newhome2::on_SearchBar_staff_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);

     QString Items_name= ui->ITEMS_NAME->text();
    ui->e2->setDate(QDate::currentDate())  ;
    qry->prepare("SELECT ID,QUANTITY,EXPDATE,SP_RATE,ITEMSNAME_1,LOCATION_NAME FROM [table] WHERE LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\') GROUP BY ID");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);

    if(modal->rowCount()==0)
    {
        QMessageBox::warning(this, "!!ALERT!! ","No such record found in the directory!!");
    }
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void newhome2::on_LogOut2_clicked()
{
    Widget *wid=new Widget;
    this->close();
    wid->showMaximized();
}

void newhome2::on_CreateBill_clicked()
{

    bill *bdail=new bill;
    bdail->showMaximized();
    this->close();
}

void newhome2::on_pushButton_clicked()
{
    Widget conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
    ID=ui->e7->text();
    Quantity=ui->e6->text();
    qry->prepare("INSERT INTO MED (ID1,QUANTITY,DIS) VALUES (\'"+ID+"\',\'"+Quantity+"\',\'"+Discount+"\')");
    qry->exec();

    qry->prepare("UPDATE [table] SET QUANTITY=QUANTITY-"+Quantity+",QUANTITIES_SOLD=QUANTITIES_SOLD+"+Quantity+",EXPECTED_CPAMT=EXPECTED_CPAMT+("+Quantity+"*CP_RATE),EXPECTED_SPAMT=EXPECTED_SPAMT+("+Quantity+"*SP_RATE) WHERE ID=\'"+ID+"\'");
    qry->exec();

    qry->prepare("UPDATE [table] SET ACT_SPAMT=ACT_SPAMT+(1.13 *(("+Quantity+"*SP_RATE) - (\'"+Discount+"\' * "+Quantity+" *SP_RATE))) WHERE ID=\'"+ID+"\'");
    qry->exec();
    qry->prepare("UPDATE [table] SET PROFIT=(ACT_SPAMT-EXPECTED_SPAMT) WHERE ID=\'"+ID+"\'");
    qry->exec();
    qry->prepare("UPDATE staff SET SALESPOINT=SALESPOINT+1 WHERE firstname=\'"+Staff+"\'");
    qry->exec();
    conn.connClose();

}

void newhome2::on_addProfile_clicked()
{

    Billno=ui->e1->text();
    Date=ui->e2->text();
    Panno=ui->e3->text();
    Staff=ui->e4->text();
    PatientsName=ui->e5->text();

    Widget conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);

    qry->prepare("UPDATE BILL SET FIELDVALUE=\'"+Billno+"\' WHERE FIELDNAME=\'BILLNO\'");
    qry->exec();
    qry->prepare("UPDATE BILL SET FIELDVALUE=\'"+Date+"\' WHERE FIELDNAME=\'DATE\'");
    qry->exec();
    qry->prepare("UPDATE BILL SET FIELDVALUE=\'"+Panno+"\' WHERE FIELDNAME=\'PANNO\'");
    qry->exec();
    qry->prepare("UPDATE BILL SET FIELDVALUE=\'"+Staff+"\' WHERE FIELDNAME=\'STAFF\'");
    qry->exec();
    qry->prepare("UPDATE BILL SET FIELDVALUE=\'"+PatientsName+"\' WHERE FIELDNAME=\'PATIENTSNAME\'");
    qry->exec();
    if(ui->radioButton->isChecked())
    {
        Discount="0.05";
        qDebug()<<"ya xu1";

    }
    else if(ui->radioButton_2->isChecked())
    {
        Discount="0.1";
        qDebug()<<"ya xu2";

    }
    else if(ui->radioButton_3->isChecked())
    {
         Discount="0.15";

         qDebug()<<"ya xu3";
    }
    else
    {
        Discount="0.0";
         qDebug()<<"ya xuhai";
    }
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->radioButton_3->hide();
    ui->l8->hide();
    ui->e1->hide();
    ui->e2->hide();
    ui->e3->hide();
    ui->e4->hide();
    ui->e5->hide();
    ui->l1->hide();
    ui->l2->hide();
    ui->l3->hide();
    ui->l4->hide();
    ui->l5->hide();
    ui->l8->hide();
    ui->addProfile->hide();
   ui->CreateBill->show();
    ui->groupBox->show();
    conn.connClose();
 }

void newhome2::on_StockButton_clicked()
{
    Stock *stock=new Stock;
     stock->setModal(true);
     stock->exec();
}

void newhome2::on_ExpAlertButton_clicked()
{
    ExpDate *exp=new ExpDate;
    exp->setModal(true);
    exp->exec();
}
