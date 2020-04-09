/*
 *   myudp.cpp: UDP socket
 * 
 *   Copyright (C) 2017  Zhengyu Peng, https://zpeng.me
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "myudp.h"
#include<QEventLoop>
#include<QTimer>

MyUDP::MyUDP(QObject *parent) : QUdpSocket(parent)
{
    socket = new QUdpSocket();
}

bool MyUDP::bindPort(QHostAddress addr, quint16 port)
{
    socket->abort();

    bool isBinded = socket->bind(addr, port);
    qDebug()<< "bindPort :" <<  addr<<port<<isBinded ;
     qDebug()<<socket->errorString();//此处为错误打印
    if (isBinded)
    {
        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()),Qt::DirectConnection);
    }
    return isBinded;

}


void MyUDP::sendMessage(QHostAddress sender, quint16 senderPort, QByteArray Data)
{
    //qDebug()<<"me -->senderPort"<<senderPort;
    // Sends the datagram datagram
    // to the host address and at port.
    socket->writeDatagram(Data, sender, senderPort);
}


void MyUDP::readyRead()
{
    // when data comes in
    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    // Receives a datagram no larger than maxSize bytes and stores it in data.
    // The sender's host address and port is stored in *address and *port
    // (unless the pointers are 0).

    socket->readDatagram(buffer.data(), buffer.size(),
                         &sender, &senderPort);
   // qDebug()<<"   senderPort --> me"<<sender.toString()<<":"<< senderPort<<"-->"<<socket->localPort();
    emit newMessage(sender.toString(), buffer);

}

void MyUDP::unbindPort()
{
    disconnect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->disconnectFromHost();
    socket->close();
}
bool MyUDP::waitForReadyRead(int milliseconds)
{
        QEventLoop eventLoop;
        QTimer timer;
        connect(this->socket, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
        connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
        timer.setSingleShot(true);
        timer.start(milliseconds);
        eventLoop.exec();
        return timer.isActive();

}

