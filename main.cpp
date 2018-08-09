#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QHostAddress >("QHostAddress");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
