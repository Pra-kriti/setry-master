#include "newhome2.h"
#include "bill.h"
#include "ui_bill.h"

bill::bill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bill)
{
    ui->setupUi(this);
}

bill::~bill()
{
    delete ui;
}
