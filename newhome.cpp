#include <QSqlQueryModel>
#include "newhome.h"
#include "newsuper.h"
#include "ui_newhome.h"
#define deflabel "HOVER OVER THE BUTTONS \n FOR MORE INFORMATION "
newhome::newhome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newhome)
{

    ui->setupUi(this);
    this->showMaximized();
    ui->Permission->hide();
    ui->Yes->hide();
    ui->No->hide();
    ui->SuperImage->hide();
    ui->ExistSuper->hide();
    ui->ChangeSuper->hide();
    ui->SupervisorProfile->hide();
    ui->BackButton->hide();
    ui->SearchBar->hide();
    ui->SearchBar1->hide();
    ui->SearchLabel->hide();
    ui->tableView->hide();
    ui->SearchButton->hide();
    ui->InfoLabel->setMaximumHeight(16777215);
    ui->InfoLabel->setMaximumWidth(16777215);

    ui->InfoLabel->setText(deflabel);
    ui->ViewStaff->installEventFilter(this);
    ui->ViewSuper->installEventFilter(this);
    ui->GTS->installEventFilter(this);
    ui->VS->installEventFilter(this);
}

bool newhome::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->ViewStaff)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel->setText("View the detailed information of the staffs");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel->setText(deflabel);
        }
    }
    else if(obj==ui->ViewSuper)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel->setText("View the detailed information of the supervisor \n and add the supervisor");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel->setText(deflabel);
        }
    }

    else if(obj==ui->GTS)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel->setText("View the overall stock of medicines in the pharmacy");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel->setText(deflabel);
        }
    }
    else if(obj==ui->VS)
    {
        if(event->type()==QEvent::HoverEnter)
        {
            ui->InfoLabel->setText("Show the monthly sales and transactions \n and calculate profit ");
        }
        else if(event->type()==QEvent::HoverLeave)
        {
            ui->InfoLabel->setText(deflabel);
        }

    }
    else
    {
        event->ignore();
    }
    return 0;

}

newhome::~newhome()
{
    delete ui;
}

void newhome::on_ViewStaff_clicked()
{

   ui->BackButton->show();
   ui->ViewSuper->hide();
   ui->GTS->hide();
   ui->VS->hide();
   ui->InfoLabel->hide();
   update1();
}
void newhome::update1()
{
    selector=1;
    ui->SearchBar->setPlaceholderText("First Name");
    ui->SearchBar1->setPlaceholderText("Last Name");
    ui->SearchLabel->setText("Enter the First Name or the Last Name of the staff to be searched in the database:");
    ui->tableView->show();
    ui->SearchBar->show();
    ui->SearchBar1->show();
    ui->SearchLabel->show();
    ui->SearchButton->show();
    ui->tableView->setMaximumWidth(16777215);
    ui->tableView->setMaximumHeight(16777215);
    ui->tableView->setStyleSheet("background-color:rgb(231, 231, 231)");
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM staff");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());

}

void newhome::on_SearchButton_clicked()
{
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    if (selector==1)
    {
        QString Firstname= ui->SearchBar->text();
        QString Lastname= ui->SearchBar1->text();

        if (Firstname!=NULL)
        {qry->prepare("SELECT* FROM staff WHERE LOWER(firstname) LIKE LOWER(\'\%"+Firstname+"\%\')");}
        else if (Lastname!=NULL)
        {qry->prepare("SELECT* FROM staff WHERE LOWER(lastname) LIKE LOWER(\'\%"+Lastname+"\%\') ");}
        else if (Firstname!=NULL and Lastname!=NULL)
              qry->prepare("SELECT* FROM staff WHERE LOWER(firstname) LIKE LOWER(\'\%"+Firstname+"\%\') and LOWER(lastname) LIKE LOWER(\'\%"+Lastname+"\%\')");
          qry->exec();
          modal->setQuery(*qry);
    }
    else if (selector==3)
    {
        QString Items_name= ui->SearchBar->text();
        QString Location_name= ui->SearchBar1->text();

    if (Items_name!=NULL)
    {qry->prepare("SELECT* FROM [table] WHERE LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\')");}
    else if (Location_name!=NULL)
    {qry->prepare("SELECT* FROM [table] WHERE LOWER(LOCATION_NAME) LIKE LOWER(\'\%"+Location_name+"\%\') or LOWER(LOCATION_NAME)=\'miscellaneous\'");}
    else if (Items_name!=NULL and Location_name!=NULL)
          qry->prepare("SELECT* FROM [table] WHERE LOWER(LOCATION_NAME) LIKE LOWER(\'\%"+Location_name+"\%\') and LOWER(ITEMSNAME_1) LIKE LOWER(\'\%"+Items_name+"\%\') or LOWER(LOCATION_NAME)=\'miscellaneous\'");

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
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());


}

void newhome::on_BackButton_clicked()
{
    newhome *admin=new newhome;
    admin->showMaximized();
    this->close();
}

void newhome::on_GTS_clicked()
{
    ui->BackButton->show();
    ui->ViewSuper->hide();
    ui->ViewStaff->hide();
    ui->VS->hide();
    update3();
}
void newhome::update3()
{

    ui->SearchBar->setPlaceholderText("Item Name");
    ui->SearchBar1->setPlaceholderText("Category");
    ui->SearchLabel->setText("Enter the Item Name or the Category of the medicine to be searched in the database:");
    selector=3;
    ui->tableView->show();
    ui->InfoLabel->hide();
    ui->SearchBar->show();
    ui->SearchBar1->show();
    ui->SearchLabel->show();
    ui->SearchButton->show();
    ui->tableView->setMaximumWidth(16777215);
    ui->tableView->setMaximumHeight(16777215);
    ui->tableView->setStyleSheet("background-color:rgb(231, 231, 231)");
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM [table]");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void newhome::on_ViewSuper_clicked()
{

    ui->BackButton->show();
    ui->ViewStaff->hide();
    ui->GTS->hide();
    ui->VS->hide();
    ui->ChangeSuper->show();
    ui->ExistSuper->show();
     ui->InfoLabel->hide();
    selector=2;

}


void newhome::on_ExistSuper_clicked()
{
    ui->Yes->hide();
    ui->No->hide();
    ui->Permission->hide();
    ui->SupervisorProfile->hide();
    ui->SupervisorProfile->show();
    ui->SuperImage->show();
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM [super]");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->SupervisorProfile->setModel(modal);
    ui->SupervisorProfile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->SupervisorProfile->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());

}

void newhome::on_ChangeSuper_clicked()
{
    ui->SuperImage->hide();
    ui->SupervisorProfile->hide();
    ui->Permission->show();
    ui->Yes->show();
    ui->No->show();
}

void newhome::on_Yes_clicked()
{
 NewSuper *newsup=new NewSuper;
 newsup->setModal(true);
 newsup->exec();
 on_ExistSuper_clicked();
}


void newhome::on_No_clicked()
{
    on_ExistSuper_clicked();
}

void newhome::on_LogOut_1_clicked()
{
    Widget *wid=new Widget;
    this->close();
    wid->showMaximized();
}
