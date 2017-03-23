#ifndef NEWSUPER_H
#define NEWSUPER_H
#include "widget.h"
#include "newhome.h"
#include <QDialog>

namespace Ui {
class NewSuper;
}

class NewSuper : public QDialog
{
    Q_OBJECT

public:
    explicit NewSuper(QWidget *parent = 0);
    ~NewSuper();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewSuper *ui;
     QString ID,FName,LName,Add,Contact,Age,Sex,Email,OInfo;
};

#endif // NEWSUPER_H
