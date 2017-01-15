#include <QSqlQueryModel>
#include <widget.h>
#include "newhome2.h"
#include "bill.h"
#include "ui_newhome2.h"

newhome2::newhome2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newhome2)
{
    ui->setupUi(this);
    this->showMaximized();

    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT ID,QUANTITY,EXPDATE,SP_RATE,ITEMSNAME_1,LOCATION_NAME FROM [table]");
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

    qry->prepare("SELECT ID,QUANTITY,EXPDATE,SP_RATE,ITEMSNAME_1,LOCATION_NAME FROM [table] WHERE LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\') ");
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

void newhome2::on_pushButton_clicked()
{
    bill* bdail=new bill;
    bdail->setModal(true);
    bdail->exec();
}
