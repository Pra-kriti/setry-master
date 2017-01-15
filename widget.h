
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileInfo>

#include <QtSql/QSqlDriver>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include<QMessageBox>
#include <QSqlQuery>
#include <QString>

//#define Path_to_DB "C:/Users/shreetis13/Desktop/newse/untitled1/table(1).sqlite"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
      QSqlDatabase myDB;
    QString Role;
     QString Username, Password;

     void connClose()
     {
         myDB.close();
         myDB.removeDatabase(QSqlDatabase::defaultConnection);
     }

     bool connOpen()
     {     myDB= QSqlDatabase::addDatabase("QSQLITE");
           myDB.setDatabaseName("/home/prakriti/Desktop/new4/setry-master/table (1).sqlite");
          if(myDB.open())
                 {
                     qDebug()<<("connected! ");
                     return true;
                 }


             else
             {
                 qDebug()<<("Failure connection to db file");
                 return false;
             }
     }
    ~Widget();

private slots:
    void on_AdminButton_clicked();
    bool checkdb();

    void on_SuperButton_clicked();

    void on_StaffButton_clicked();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
