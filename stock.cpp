#include "stock.h"
#include "ui_stock.h"
#include <QSqlQueryModel>

Stock::Stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stock)
{
    ui->setupUi(this);
    this->showMaximized();
    Widget conn;
    conn.connOpen();

    QSqlQuery *qry= new QSqlQuery(conn.myDB);
    QSqlQueryModel *modal= new QSqlQueryModel;
    qry->prepare("SELECT ID,ITEMSNAME_1,LOCATION_NAME,QUANTITY FROM [table] WHERE QUANTITY<=\'10\'");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

Stock::~Stock()
{
    delete ui;
}

void Stock::on_pushButton_clicked()
{
    this->close();
}
