#include "widget.h"
#include "ui_widget.h"
#include "newhome.h"
#include "newhome1.h"
#include "newhome2.h"
#include <QTimer>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
     QTimer:: singleShot(5000,this,SLOT(showMaximized()));
}

Widget::~Widget()
{
    delete ui;
    qDebug()<<"     Closing the connection";
    myDB.close();
}

void Widget::on_AdminButton_clicked()
{
    Username=ui->User->text();
    Password=ui->Pass->text();
    Role="admin";
    if(checkdb())
   {
    connClose();
    newhome *admin=new newhome;
    admin->show();
    this->close();}
}
bool Widget::checkdb()
{

    connOpen();
    QSqlQuery qry;
    if(qry.exec("SELECT username,password,role FROM login WHERE username=\'"+Username+"\' AND password=\'"+Password+"\' AND role=\'"+Role+"\' "))
    {
        if(qry.next())
        {
            ui->Status->setText("[+]VALID USERNAME AND PASSWORD");
            return true;
        }
        else
        {
            ui->Status->setText("   UNKNOWN USERNAME AND PASSWORD      ");
            return false;
        }

    }
}

void Widget::on_SuperButton_clicked()
{
    Username=ui->User->text();
    Password=ui->Pass->text();
    Role="supervisor";
  if(checkdb())
    {
      connClose();
      newhome1 *super=new newhome1;
      super->show();
      this->close();
    }
}

void Widget::on_StaffButton_clicked()
{
    Username=ui->User->text();
    Password=ui->Pass->text();
    Role="staff";
   if(checkdb())
    {
        connClose();
        newhome2 *staff=new newhome2;
        staff->show();
        this->close();
   }
}
