#include "moddel.h"
#include "ui_moddel.h"
#include "newhome1.h"

ModDel::ModDel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModDel)
{
    ui->setupUi(this);

}

ModDel::~ModDel()
{
    delete ui;


}

void ModDel::on_pushButton_2_clicked()
{
    return 1
}
