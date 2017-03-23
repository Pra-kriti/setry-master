#include "newhome2.h"
#include "bill.h"
#include "ui_bill.h"

#include <QString>

bill::bill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bill)
{
    ui->setupUi(this);
    Widget conn,conn2;
    conn.connOpen();
    QSqlQuery *qry= new QSqlQuery(conn.myDB);
    QSqlQueryModel *modal=new QSqlQueryModel;
    qry->prepare("SELECT* FROM BILL");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    conn.connClose();
    conn2.connOpen();
    QSqlQuery *qry1= new QSqlQuery(conn.myDB);
    QSqlQueryModel *modal1=new QSqlQueryModel;
    QSqlQuery *qry2= new QSqlQuery(conn.myDB);
    QSqlQueryModel *modal2=new QSqlQueryModel;
   // qry1->prepare("UPDATE MED SET AMOUNT=[table].SP_RATE*MED.QUANTITY ");
    qry1->prepare("SELECT ID, ITEMSNAME_1, SP_RATE , MED.QUANTITY ,  ([table].SP_RATE*MED.QUANTITY) AS TOTALPRICE,([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY)  AS GRAND, (([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY))* 1.13 AS TOTAL  FROM [table] INNER JOIN MED ON MED.QUANTITY<= [table].QUANTITY and  [table].ID = MED.ID1   ");

    qry1->exec();
  //  qry1->prepare("UPDATE [table] SET [table].ACTUAL_SPAMT=([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY)*0.13+([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY) AS TOTAL")
    modal1->setQuery(*qry1);
    if(modal1->rowCount()==0)
    {
       QMessageBox::warning(this,"RECORD NOT FOUND","NO RECORD FOUND!");
    }

    qDebug()<<(qry1->size());
    modal1->setQuery(*qry1);
    ui->tableView_2->setModel(modal1);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   // qDebug()<<(Billno);
    qry2->prepare("SELECT sum([table].SP_RATE*MED.QUANTITY) AS TOTALAMT,sum([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY) AS GRAND_AMT, SUM((([table].SP_RATE*MED.QUANTITY)-MED.DIS*([table].SP_RATE*MED.QUANTITY))*1.13) AS GRAND_TOTAL FROM [table] INNER JOIN MED ON [table].ID = MED.ID1 ");
    qry2->exec();
     modal2->setQuery(*qry2);
     ui->tableView_3->setModel(modal2);
     ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->tableView_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn2.connClose();
}

bill::~bill()
{
    delete ui;
}

void bill::on_CONFIRM_clicked()
{
    Widget conn;
    conn.connOpen();
    QSqlQuery *qry= new QSqlQuery(conn.myDB);
    //QSqlQueryModel *modal=new QSqlQueryModel;
    qry->prepare("DELETE FROM MED");
    qry->exec();
    qry->prepare("INSERT INTO MED (ID1,QUANTITY,DIS) VALUES (\'0\',\'0\',\'0\')");
    qry->exec();
    qry->prepare("UPDATE BILL SET FIELDVALUE=\'0\'");
    qry->exec();
    conn.connClose();
     newhome2 *staff=new newhome2;
     staff->show();
     this->close();

}


