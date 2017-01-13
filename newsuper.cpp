#include "newsuper.h"
#include "ui_newsuper.h"
#include "newhome.h"


NewSuper::NewSuper(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSuper)
{
    ui->setupUi(this);

}

NewSuper::~NewSuper()
{
    delete ui;
}

void NewSuper::on_buttonBox_accepted()
{
    ID=ui->l1->text();
    FName=ui->l2->text();
    LName=ui->l3->text();
    Add=ui->l4->text();
    Contact=ui->l5->text();
    Age=ui->l6->text();
    Sex=ui->l7->text();
    Email=ui->l8->text();
    OInfo=ui->l9->text();
    Widget conn;
    conn.connOpen();
qDebug()<<"HEEEEEEEEEE";
if(!conn.connOpen()){qDebug()<<"bhaena";}
    QSqlQuery *qry=new QSqlQuery(conn.myDB);
   qry->prepare("UPDATE super SET FieldValue=\'"+OInfo+"\' WHERE FieldName=\'OTHER INFO\'");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+Email+"\' WHERE FieldName=\'EMAIL\'");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+ID+"\' WHERE FieldName=\'ID\'");
   qry->exec();
   qry->prepare("UPDATE super SET  FieldValue=\'"+FName+"\' WHERE FieldName=\'FIRST NAME\' ");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+Add+"\' WHERE FieldName=\'ADDRESS\'");
   qry->exec();
   qry->prepare("UPDATE super SET  FieldValue=\'"+Contact+"\' WHERE FieldName=\'CONTACT NO\'");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+Age+"\' WHERE FieldName=\'AGE\'");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+Sex+"\' WHERE FieldName=\'SEX\' ");
   qry->exec();
   qry->prepare("UPDATE super SET FieldValue=\'"+LName+"\' WHERE FieldName=\'LAST NAME\'");
   qry->exec();
   conn.connClose();

}
