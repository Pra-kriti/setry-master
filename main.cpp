#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splash=new QSplashScreen;
    splash->setPixmap(QPixmap(":/new/prefix1/PicsArt_02-10-12.48.02.jpg"));
    splash->show();

    Widget w;
    QTimer:: singleShot(5000,splash,SLOT(close()));
    QTimer:: singleShot(5000,&w,SLOT(show()));

    return a.exec();
}
