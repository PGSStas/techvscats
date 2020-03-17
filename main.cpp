#include "mainwindow.h"
#include <QApplication>
#include<Controller/controller.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   // Controller* controller = new Controller();
    return a.exec();
}
