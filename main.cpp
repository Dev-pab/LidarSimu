#include "mainwindow.h"

#include <QApplication>

MainWindow* ptW;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    ptW = &w;
    w.show();



    return a.exec();
}

