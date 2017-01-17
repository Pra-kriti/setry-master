#include <QSqlQueryModel>
#include <widget.h>
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
    ui->groupBox->hide();
      ui->CreateBill->hide();
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT ID,QUANTITY,EXPDATE,SP_RATE,ITEMSNAME_1,LOCATION_NAME FROM [table] GROUP BY ID");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    Widget conn;

    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);

    if(ui->radioButton->isChecked())
    {
        qry->prepare("UPDATE MED SET DIS=0.05");
        qry->exec();
    }
    else if(ui->radioButton_2->isChecked())
    {
        qry->prepare("UPDATE MED SET DIS=0.1");
        qry->exec();
    }
    else if(ui->radioButton_3->isChecked())
    {
        qry->prepare("UPDATE MED SET DIS=0.15");
        qry->exec();
    }
    else
    {
        qry->prepare("UPDATE MED SET DIS=0");
        qry->exec();
    }
    conn.connClose();
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
    qry->prepare("INSERT INTO MED (ID1,QUANTITY) VALUES (\'"+ID+"\',\'"+Quantity+"\')");
    qry->exec();
    qry->prepare("UPDATE [table] SET QUANTITY=QUANTITY-"+Quantity+" WHERE ID=\'"+ID+"\'");
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
 }
