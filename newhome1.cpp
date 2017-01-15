#include <QSqlQueryModel>
#include "newhome1.h"
#include "ui_newhome1.h"
#include "moddel.h"
#define deflabel "HOVER OVER THE BUTTONS \n FOR MORE INFORMATION "

newhome1::newhome1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newhome1)
{

    ui->setupUi(this);
    this->showMaximized();
    modifyFormHide();
    modifySelectionHide();
  //  ui->tableView_1->AdjustToContentsOnFirstShow();
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->l9->hide();
    ui->e9->hide();
    ui->AddDrug->hide();
    ui->DeleteDrug->hide();
    ui->ModifyDrug->hide();
    ui->ModifyDrugButton->hide();
    ui->DelButton->hide();
    ui->Permission_1->hide();
    ui->AddStaff->hide();
    ui->tableView_1->hide();
    ui->ExistStaff->hide();
    ui->NewStaff->hide();
    ui->ModifyStaff->hide();
    ui->BackButton_1->hide();
    ui->SearchBar_3->hide();
    ui->SearchBar_4->hide();
    ui->SearchLabel_1->hide();
    ui->SearchButton_1->hide();
    ui->InfoLabel_1->setMaximumHeight(16777215);
    ui->InfoLabel_1->setMaximumWidth(16777215);
    ui->InfoLabel_1->setText(deflabel);
    ui->ViewStaff->installEventFilter(this);
    ui->UpdateData->installEventFilter(this);
    ui->GTS_1->installEventFilter(this);
    ui->VS_1->installEventFilter(this);
}
void newhome1::modifyFormHide()
{

    ui->e1->hide();
    ui->e2->hide();
    ui->e3->hide();
    ui->e4->hide();
    ui->e5->hide();
    ui->e6->hide();
    ui->e7->hide();
    ui->e8->hide();
    ui->l1->hide();
    ui->l2->hide();
    ui->l3->hide();
    ui->l4->hide();
    ui->l5->hide();
    ui->l6->hide();
    ui->l7->hide();
    ui->l8->hide();


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
    modifySelectionHide();
    modifyFormHide();
    ui->l9->hide();
    ui->e9->hide();
    ui->BackButton_1->show();
    ui->UpdateData->hide();
    ui->ModifyDrugButton->hide();
    ui->ViewStaff->hide();
    ui->VS_1->hide();
    update2();
    ui->groupBox->hide();


}

void newhome1::update2()
{
    ui->SearchBar_3->setPlaceholderText("Item Name");
    ui->SearchBar_4->setPlaceholderText("Category");
    selector=3;
    ui->tableView_1->show();
    ui->InfoLabel_1->hide();
    ui->SearchBar_3->show();
    ui->SearchBar_4->show();
    ui->SearchLabel_1->show();
    ui->SearchButton_1->show();
    ui->tableView_1->setMaximumWidth(16777215);
    ui->tableView_1->setMaximumHeight(16777215);
    ui->tableView_1->setStyleSheet("background-color:rgb(231, 231, 231)");
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM [table] GROUP BY ID");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//     ui->tableView_1->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
    else if (selector==1)
    {
        QString Firstname= ui->SearchBar_3->text();
        QString Lastname= ui->SearchBar_4->text();

        if (Firstname!=NULL)
        {qry->prepare("SELECT* FROM staff WHERE LOWER(firstname) LIKE LOWER(\'\%"+Firstname+"\%\')");}
        else if (Lastname!=NULL)
        {qry->prepare("SELECT* FROM staff WHERE LOWER(lastname) LIKE LOWER(\'\%"+Lastname+"\%\') ");}
        else if (Firstname!=NULL and Lastname!=NULL)
              qry->prepare("SELECT* FROM staff WHERE LOWER(firstname) LIKE LOWER(\'\%"+Firstname+"\%\') and LOWER(lastname) LIKE LOWER(\'\%"+Lastname+"\%\')");
          qry->exec();
          modal->setQuery(*qry);
    }

    qDebug()<<(qry->size());
    if(modal->rowCount()==0)
    {
        QMessageBox::warning(this, "!!ALERT!! ","No such record found in the directory!!");
    }
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());
}

void newhome1::on_ViewStaff_clicked()
{
    selector=2;
    ui->groupBox_2->hide();
    ui->BackButton_1->show();
    ui->ExistStaff->show();
    ui->NewStaff->show();
    ui->ModifyStaff->show();
    ui->UpdateData->hide();
    ui->GTS_1->hide();
    ui->VS_1->hide();
    ui->InfoLabel_1->hide();

}

void newhome1::on_ExistStaff_clicked()
{
    modifyFormHide();
    modifySelectionHide();
    ui->AddStaff->hide();
    ui->DelButton->hide();
    ui->Permission_1->hide();
    ui->groupBox_2->hide();
    selector=1;
    ui->tableView_1->show();
    ui->SearchBar_3->setPlaceholderText("First Name");
    ui->SearchBar_4->setPlaceholderText("Last Name");
    ui->SearchLabel_1->setText("Enter the First Name or the Last Name of the staff to be searched in the database:");
    ui->SearchBar_3->show();
    ui->SearchBar_4->show();
    ui->SearchLabel_1->show();
    ui->SearchButton_1->show();
    ui->tableView_1->setMaximumWidth(16777215);
    ui->tableView_1->setMaximumHeight(16777215);
    ui->tableView_1->setStyleSheet("background-color:rgb(231, 231, 231)");
    Widget conn;
    QSqlQueryModel * modal=new QSqlQueryModel();
            conn.connOpen();
            QSqlQuery *qry=new QSqlQuery(conn.myDB);
    qry->prepare("SELECT* FROM staff");
    qry->exec();
    qDebug()<<(qry->size());
    modal->setQuery(*qry);
    ui->tableView_1->setModel(modal);
    ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
    qDebug()<<(modal->rowCount());

}

void newhome1::on_NewStaff_clicked()
{
    selector=2;
    modifySelectionHide();
    ui->Permission_1->show();
    modifyFormShow();
    ui->groupBox_2->show();
    ui->DelButton->hide();
    ui->BackButton_1->show();
    ui->tableView_1->hide();
    ui->SearchBar_3->hide();
    ui->SearchBar_4->hide();
    ui->SearchLabel_1->hide();
    ui->SearchButton_1->hide();
    ui->AddStaff->show();

}

void newhome1::on_AddStaff_clicked()
{
    ui->Permission_1->hide();
    ui->AddStaff->hide();
    if(selector==2 or selector==4)
    {
        ID= ui->e1->text();
        FName= ui->e2->text();
        LName=   ui->e3->text();
        Address= ui->e4->text();
        Age= ui->e5->text();
        Sex= ui->e6->text();
        Contact= ui->e7->text();
        Salespoint= ui->e8->text();
        NewUser=ui->newUsernameText->text();
        NewPass=ui->newPasswordText->text();

         Widget conn;
         conn.connOpen();
         if(!conn.connOpen()){qDebug()<<"bhaena";}
             QSqlQuery *qry=new QSqlQuery(conn.myDB);
            if(selector==2)
            {

                qry->prepare("INSERT INTO [staff] (ID, firstname, lastname, address, sex, age,contact,salespoint) VALUES (\'"+ID+"\',\'"+FName+"\',\'"+LName+"\',\'"+Address+"\',\'"+Sex+"\',\'"+Age+"\',\'"+Contact+"\',\'"+Salespoint+"\')");
                qry->exec();
                qry->prepare("INSERT INTO login (username,password,role) VALUES (\'"+NewUser+"\',\'"+NewPass+"\',\'staff\')");
                qry->exec();
            }
            else if(selector==4)
            {
                qDebug()<<"eta";
                qry->prepare("UPDATE [staff] SET ID=\'"+ID+"\', firstname=\'"+FName+"\', lastname=\'"+LName+"\', address=\'"+Address+"\', sex=\'"+Sex+"\', age=\'"+Age+"\',contact=\'"+Contact+"\',salespoint=\'"+Salespoint+"\' WHERE ID=\'"+modID+"\'");
                qry->exec();

            }

             conn.connClose();
        on_ExistStaff_clicked();
    }
 else if (selector==5)
    {
qDebug()<<"1111111111";
        ID_1= ui->e1->text();
        Itemsname= ui->e2->text();
        Quantity=   ui->e3->text();
        CPR= ui->e4->text();
        CPA= ui->e5->text();
        SPR= ui->e6->text();
        SPA= ui->e7->text();
        ExpDate= ui->e8->text();
        Location_Name=ui->e9->text();

        Widget conn;
        conn.connOpen();
        if(!conn.connOpen()){qDebug()<<"bhaena";}
            QSqlQuery *qry=new QSqlQuery(conn.myDB);

qry->prepare("INSERT INTO [table] (ID, QUANTITY, EXPDATE, CP_RATE, CP_AMOUNT, SP_RATE, SP_AMOUNT, ITEMSNAME_1, LOCATION_NAME) VALUES (\'"+ID_1+"\',\'"+Quantity+"\',\'"+ExpDate+"\',\'"+CPR+"\',\'"+CPA+"\',\'"+SPR+"\',\'"+SPA+"\',\'"+Itemsname+"\',\'"+Location_Name+"\')");            qry->exec();
            qDebug()<<"3333333333";
             conn.connClose();
     on_GTS_1_clicked();
    }

}
void newhome1::modifyFormShow()
{
    ui->e1->show();
    ui->e2->show();
    ui->e3->show();
    ui->e4->show();
    ui->e5->show();
    ui->e6->show();
    ui->e7->show();
    ui->e8->show();
    ui->l1->show();
    ui->l2->show();
    ui->l3->show();
    ui->l4->show();
    ui->l5->show();
    ui->l6->show();
    ui->l7->show();
    ui->l8->show();
}

void newhome1::modifySelectionHide(){
    ui->IDLabel->hide();
    ui->IDField->hide();
    ui->Select->hide();
}

void newhome1::on_ModifyStaff_clicked()
{

    ui->tableView_1->hide();
    ui->SearchBar_3->hide();
    ui->SearchBar_4->hide();
    ui->SearchButton_1->hide();
    ui->SearchLabel_1->hide();
    ui->AddStaff->hide();
    ui->Permission_1->hide();
    modifyFormHide();
    modifySelectionHide();
    ui->DelButton->show();
    ui->Select->show();
    ui->IDField->show();
    ui->IDLabel->show();
    ui->Select->setText("MODIFY");
    selectorUpdate=1;
}

void newhome1::on_Select_clicked()
{
    modifySelectionHide();
    ui->DelButton->hide();

    if (selectorUpdate==1)
    {
        selector=4;
        modifyFormShow();
        ui->Permission_1->show();
        ui->Permission_1->setText("Please enter the modified profile:");
        modID = ui->IDField->text();
        Widget conn;
        conn.connOpen();
        QSqlQueryModel *modal=new QSqlQueryModel;

        QSqlQuery *qry=new QSqlQuery(conn.myDB);
        qry->prepare("SELECT* FROM [staff] where ID=\'"+modID+"\'");
        qry->exec();
        modal->setQuery(*qry);
        ui->AddStaff->show();
        ui->AddStaff->setText("Modify staff");
        if(modal->rowCount()==0)
        {
            QMessageBox::warning(this,"ERROR!!","NO SUCH ID FOUND IN THE DIRECTORY!!");
            modifyFormHide();
            conn.connClose();
            on_ExistStaff_clicked();
        }
    }
    else if(selectorUpdate==2)
    {
        modID=ui->IDField->text();
        ui->SearchBar_3->hide();
        ui->SearchBar_4->hide();
        ui->SearchButton_1->hide();
        ui->SearchLabel_1->hide();
        ui->Permission_1->show();
        ui->Permission_1->setText("CHOOSE THE MODIFICATION TYPE::");
        ui->groupBox->show();
        Widget conn;
        conn.connOpen();
        QSqlQueryModel *modal=new QSqlQueryModel;

        QSqlQuery *qry=new QSqlQuery(conn.myDB);
        qry->prepare("SELECT* FROM [table] where ID=\'"+modID+"\'");
        qry->exec();
        modal->setQuery(*qry);
        if(modal->rowCount()==0)
        {
            QMessageBox::warning(this,"ERROR!!","NO SUCH ID FOUND IN THE DIRECTORY!!");
            modifyFormHide();
            conn.connClose();
            on_ExistStaff_clicked();
        }
        ui->tableView_1->setModel(modal);
        ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        conn.connClose();
    }
    else if (selectorUpdate==3)
    {
         modID=ui->IDField->text();
         Widget conn;
         conn.connOpen();
         QSqlQueryModel *modal=new QSqlQueryModel;

         QSqlQuery *qry=new QSqlQuery(conn.myDB);
         qry->prepare("SELECT* FROM [table] where ID=\'"+modID+"\'");
         qry->exec();
         modal->setQuery(*qry);
         ui->tableView_1->setModel(modal);
         ui->tableView_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

         if(modal->rowCount()==0)
         {
             QMessageBox::warning(this,"ERROR!!","NO SUCH ID FOUND IN THE DIRECTORY!!");
             modifyFormHide();
             conn.connClose();
             on_GTS_1_clicked();
         }
         else
         {
             qry->prepare("DELETE FROM [table] where ID=\'"+modID+"\'");
             qry->exec();

            ui->SearchBar_3->hide();
            ui->SearchBar_4->hide();
            ui->SearchLabel_1->hide();
            ui->SearchButton_1->hide();

         }
         conn.connClose();
         ui->tableView_1->hide();
         on_GTS_1_clicked();
    }

}

void newhome1::on_DelButton_clicked()
{
     modifySelectionHide();
     modifyFormHide();
      ui->groupBox->hide();
     modID = ui->IDField->text();
     Widget conn;
     conn.connOpen();
     QSqlQueryModel *modal=new QSqlQueryModel;

     QSqlQuery *qry=new QSqlQuery(conn.myDB);
     qry->prepare("SELECT* FROM [staff] where ID=\'"+modID+"\'");
     qry->exec();
     modal->setQuery(*qry);
     qry->prepare("DELETE FROM [staff] WHERE ID=\'"+modID+"\'");
     qry->exec();

     if(modal->rowCount()==0)
     {
         QMessageBox::warning(this,"ERROR!!","NO SUCH ID FOUND IN THE DIRECTORY!!");
         modifyFormHide();
         conn.connClose();
         on_ExistStaff_clicked();
     }
    on_ExistStaff_clicked();
}


void newhome1::on_LogOut_clicked()
{
    Widget *wid=new Widget;
    this->close();
    wid->showMaximized();

}

void newhome1::on_UpdateData_clicked()
{

    ui->ViewStaff->hide();
    ui->GTS_1->hide();
     ui->groupBox->hide();
    ui->VS_1->hide();
    ui->ModifyDrugButton->hide();
    ui->BackButton_1->show();
    ui->InfoLabel_1->hide();
    ui->AddDrug->show();
    ui->DeleteDrug->show();
    ui->ModifyDrug->show();

}

void newhome1::on_ModifyDrug_clicked()
{
    selectorUpdate=2;
    ui->Permission_1->hide();
    ui->AddStaff->hide();
    on_GTS_1_clicked();
    ui->UpdateData->show();
    ui->IDLabel->show();
    ui->IDLabel->setText("ENTER THE ID OF THE MEDICINE TO BE MODIFIED:: ");
    ui->IDField->show();
    ui->ModifyDrugButton->hide();
    ui->Select->show();
}

void newhome1::on_DeleteDrug_clicked()
{
    selectorUpdate=3;
    on_GTS_1_clicked();
    ui->Permission_1->hide();
    ui->ModifyDrugButton->hide();
    ui->AddStaff->hide();
    ui->UpdateData->show();
    ui->IDLabel->show();
    ui->IDLabel->setText("ENTER THE ID OF THE MEDICINE TO BE DELETED:: ");
    ui->IDField->show();
    ui->Select->show();
}

void newhome1::on_AddDrug_clicked()
{
    selector=5;
    modifySelectionHide();
    ui->Permission_1->show();
    ui->ModifyDrugButton->hide();
    ui->Permission_1->setText("Enter the new drug profile:");
    modifyFormShow();
    ui->l9->show();
    ui->e9->show();
    ui->BackButton_1->show();
    ui->AddStaff->show();
    ui->AddStaff->setText("ADD DRUG");

    ui->l1->setText("ID");
    ui->l2->setText("ITEMS NAME");
    ui->l3->setText("QUANTITY");
    ui->l4->setText("CP RATE");
    ui->l5->setText("CP AMOUNT");
    ui->l6->setText("SP RATE");
    ui->l7->setText("SP AMOUNT");
    ui->l8->setText("EXP DATE");
    ui->l9->setText("LOCATION NAME");

     ui->tableView_1->hide();
     ui->SearchBar_3->hide();
     ui->SearchBar_4->hide();
     ui->SearchLabel_1->hide();
     ui->SearchButton_1->hide();
     ui->AddStaff->show();
}

void newhome1::on_selector_clicked()
{
    ui->groupBox->hide();
    ui->ModifyDrugButton->show();
    ui->Permission_1->hide();
    if(ui->checkBox->isChecked())
    {
        field.append("a");
    }
    if(ui->checkBox2->isChecked())
    {
        field.append("b");
    }
    if(ui->checkBox3->isChecked())
    {
        field.append("c");
    }
    if(ui->checkBox4->isChecked())
    {
        field.append("d");
    }
    if(ui->checkBox5->isChecked())
    {
        field.append("e");
    }
    if(ui->checkBox6->isChecked())
    {
        field.append("f");
    }
    for (int i=0;i<field.length();i++)
    {
        if(field.at(i)=='a')
        {
            ui->l1->show();
            ui->l1->setText("QUANTITY");
            ui->e1->show();
        }
        else if(field.at(i)=='b')
        {
            ui->l2->show();
            ui->l2->setText("LOCATION NAME");
            ui->e2->show();
        }
        else if(field.at(i)=='c')
        {
            ui->l3->show();
            ui->l3->setText("CPR");
            ui->e3->show();
        }
        else if(field.at(i)=='d')
        {
            ui->l4->show();
            ui->l4->setText("SPR");
            ui->e4->show();
        }
        else if(field.at(i)=='e')
        {
            ui->l5->show();
            ui->l5->setText("EXPIRY DATE");
            ui->e5->show();
        }
        else if(field.at(i)=='f')
        {
            ui->l6->show();
            ui->l6->setText("ITEMS NAME");
            ui->e6->show();
        }
        else{}
    }

}

void newhome1::on_ModifyDrugButton_clicked()
{
    Widget conn;
    conn.connOpen();
    QSqlQuery *qry=new QSqlQuery(conn.myDB);


    if (ui->l1->isVisible())
    {
        Quantity=ui->e1->text();
        qry->prepare("UPDATE [table] SET QUANTITY=\'"+Quantity+"\' WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    if (ui->l2->isVisible())
    {
        Location_Name=ui->e2->text();
        qry->prepare("UPDATE [table] SET LOCATION_NAME=\'"+Location_Name+"\' WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    if (ui->l3->isVisible())
    {
        CPR=ui->e3->text();
        qry->prepare("UPDATE [table] SET CP_RATE=\'"+CPR+"\' WHERE ID=\'"+modID+"\'");
        qry->exec();
        qry->prepare("UPDATE [table] SET CP_AMOUNT=CP_RATE*QUANTITY WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    if (ui->l4->isVisible())
    {
        SPR=ui->e4->text();
        qry->prepare("UPDATE [table] SET SP_RATE=\'"+SPR+"\' WHERE ID=\'"+modID+"\'");

        qry->exec();
        qry->prepare("UPDATE [table] SET SP_AMOUNT=SP_RATE*QUANTITY WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    if (ui->l5->isVisible())
    {
        ExpDate=ui->e5->text();
        qry->prepare("UPDATE [table] SET EXPDATE=\'"+ExpDate+"\' WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    if (ui->l6->isVisible())
    {
        Itemsname=ui->e6->text();
        qry->prepare("UPDATE [table] SET ITEMSNAME_1=\'"+Itemsname+"\' WHERE ID=\'"+modID+"\'");
        qry->exec();
    }
    conn.connClose();

    on_GTS_1_clicked();
}
