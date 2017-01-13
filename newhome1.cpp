#include <QSqlQueryModel>
#include "newhome1.h"
#include "ui_newhome1.h"
#define deflabel "HOVER OVER THE BUTTONS \n FOR MORE INFORMATION "

newhome1::newhome1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newhome1)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->SearchBar_3->hide();
    ui->SearchBar_4->hide();
    ui->SearchLabel_1->hide();
    ui->tableView_2->hide();
    ui->SearchButton_1->hide();
    ui->InfoLabel_1->setMaximumHeight(16777215);
    ui->InfoLabel_1->setMaximumWidth(16777215);

    ui->InfoLabel_1->setText(deflabel);
    ui->ViewStaff->installEventFilter(this);
    ui->UpdateData->installEventFilter(this);
    ui->GTS_1->installEventFilter(this);
    ui->VS_1->installEventFilter(this);
}

bool newhome1::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->ViewStaff)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel_1->setText("View the detailed information of the staffs \n and add the staffs");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel_1->setText(deflabel);
        }
    }
    else if(obj==ui->UpdateData)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel_1->setText("Update data after sales");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel_1->setText(deflabel);
        }
    }

    else if(obj==ui->GTS_1)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel_1->setText("View the overall stock of medicines in the pharmacy");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel_1->setText(deflabel);
        }
    }
    else if(obj==ui->VS_1)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel_1->setText("Show the monthly sales and transactions \n and calculate profit ");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel_1->setText(deflabel);
        }

    }
    else
    {
        event->ignore();
    }
    return 0;

}

newhome1::~newhome1()
{
    delete ui;
}

void newhome1::on_GTS_1_clicked()
{
    ui->UpdateData->hide();
    ui->ViewStaff->hide();
    ui->VS_1->hide();
    update2();
}

void newhome1::update2()
{
    ui->SearchBar_3->setPlaceholderText("Item Name");
    ui->SearchBar_4->setPlaceholderText("Category");
    selector=3;
    ui->tableView_2->show();
    ui->InfoLabel_1->hide();
    ui->SearchBar_3->show();
    ui->SearchBar_4->show();
    ui->SearchLabel_1->show();
    ui->SearchButton_1->show();
    ui->tableView_2->setMaximumWidth(16777215);
    ui->tableView_2->setMaximumHeight(16777215);
    ui->tableView_2->setStyleSheet("background-color:rgb(231, 231, 231)");
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM [table]");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView_2->setModel(modal);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void newhome1::on_BackButton_1_clicked()
{
    newhome1 *super=new newhome1;
    super->showMaximized();
    this->close();
}

void newhome1::on_SearchButton_1_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
    if (selector==3)
    {
        QString Items_name= ui->SearchBar_3->text();
        QString Location_name= ui->SearchBar_4->text();


        if (Items_name!=NULL)
        {
            qry->prepare("SELECT* FROM [table] WHERE LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\')");
        }
        else if (Location_name!=NULL)
        {
            qry->prepare("SELECT* FROM [table] WHERE LOWER(LOCATION_NAME) LIKE LOWER(\'\%"+Location_name+"\%\') or LOWER(LOCATION_NAME)=\'miscellaneous\'");
        }
        else if (Items_name!=NULL and Location_name!=NULL)
        {
            qry->prepare("SELECT* FROM [table] WHERE LOWER(LOCATION_NAME) LIKE LOWER(\'\%"+Location_name+"\%\') and LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\') or LOWER(LOCATION_NAME)=\'miscellaneous\'");
        }

        qry->exec();
        qDebug()<<(qry->size());
         modal->setQuery(*qry);
    }
    else{}

    qDebug()<<(qry->size());
    if(modal->rowCount()==0)
    {
        QMessageBox::warning(this, "!!ALERT!! ","No such record found in the directory!!");
    }
    ui->tableView_2->setModel(modal);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}
