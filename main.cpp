#include "login.h"
#include <QApplication>
#include<QPointF>
#include"mainwin.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<QList<QPointF> >("QList<QPointF>");
    qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
    qRegisterMetaType<QList<QString> >("QList<QString>");



    QApplication a(argc, argv);
//    MainWin w;
    Login w;
    w.show();
    return a.exec();
}
