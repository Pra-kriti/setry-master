#include "expdate.h"
#include "ui_expdate.h"
#include <QDate>
#include <QSqlQueryModel>

ExpDate::ExpDate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpDate)
{
    ui->setupUi(this);
    this->showMaximized();
    Widget conn;
    conn.connOpen();
    QDate date;
    date=date.currentDate();
   // int day=date.day();

    QSqlQuery *qry= new QSqlQuery(conn.myDB);
    QSqlQueryModel *modal= new QSqlQueryModel;
    qry->prepare("SELECT ID,ITEMSNAME_1,LOCATION_NAME,QUANTITY,EXPDATE FROM [table] WHERE EXPDATE<=(SELECT DATE('NOW','start of month','+4 months'))");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();



}

ExpDate::~ExpDate()
{
    delete ui;
}

void ExpDate::on_pushButton_clicked()
{
    this->close();
}
