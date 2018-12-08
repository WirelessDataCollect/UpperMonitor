#include "mainwindow.h"
#include <QApplication>
#include "myeventfilter.h"
int main(int argc, char *argv[])
{
    qRegisterMetaType<QHostAddress>("QHostAddress");

    QApplication a(argc, argv);
    a.installEventFilter(new myEventFilter());
    MainWindow w;
    w.show();

    return a.exec();
}
