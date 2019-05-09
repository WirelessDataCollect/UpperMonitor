/*
 *   mytcpclient.cpp: TCP client
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

#include "mytcpclient.h"
#include<QEventLoop>
#include<QTimer>
MyTCPClient::MyTCPClient(QObject *parent) : QTcpSocket(parent)
{
    tcpSocket = new QTcpSocket();
}

bool MyTCPClient::connectTo(QHostAddress addr, quint16 port)
{

    tcpSocket->connectToHost(addr, port);

    // tcpSocket->waitForConnected(1000);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    return tcpSocket->waitForConnected(1000);//等待连接时间
}

void MyTCPClient::onConnected()
{
    disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));

    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(messageReady()));
    emit myClientConnected(tcpSocket->peerAddress().toString(), tcpSocket->peerPort());

    qDebug()<<"tcpSocket->peerAddress().toString()"<<tcpSocket->peerAddress().toString();
    //qDebug()<<"tcpSocket->peerPort().toString()"<<tcpSocket->peerPort();

}

void MyTCPClient::onStateChanged(QAbstractSocket::SocketState state)
{
    disconnect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onStateChanged(QAbstractSocket::SocketState)));
    //qDebug()<<state;
    switch (state)
    {

    case QAbstractSocket::UnconnectedState:
        emit connectionFailed();
      //  qDebug()<<"connecting timeout";
        break;
    case QAbstractSocket::HostLookupState:
        //qDebug()<<"HostLookupState";
        break;
    case QAbstractSocket::ConnectingState:
        //qDebug()<<"ConnectingState";
        break;
    case QAbstractSocket::ConnectedState:
        //qDebug()<<"ConnectedState";
        break;
    case QAbstractSocket::BoundState:
        //qDebug()<<"BoundState";
        break;
    case QAbstractSocket::ListeningState:
        //qDebug()<<"ListeningState";
        break;
    case QAbstractSocket::ClosingState:
        //qDebug()<<"ClosingState";
        break;
    }
}

void MyTCPClient::onDisconnected()
{
    disconnect(tcpSocket, SIGNAL(disconnected()));
    disconnect(tcpSocket, SIGNAL(readyRead()));
    tcpSocket->close();
    emit myClientDisconnected();
}

void MyTCPClient::closeClient()
{
    tcpSocket->close();
}

void MyTCPClient::abortConnection()
{
    tcpSocket->abort();
}

void MyTCPClient::messageReady()
{
      receive_message = tcpSocket->readAll();
    // qDebug()<<"messageReady"<<receive_message.data();
    emit newMessage(tcpSocket->peerAddress().toString(), receive_message);
}

void MyTCPClient::sendMessage(QByteArray Data)
{
    if (tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        tcpSocket->write(Data);

        tcpSocket->flush();
    }
}

void MyTCPClient::sendMessage(QString str)
{
    QByteArray Data = str.toUtf8();
    if (tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        qint64 number = tcpSocket->write(Data);
        qDebug()<<"sendMessage sendsize"<<number;
        tcpSocket->flush();
    }
}

void MyTCPClient::disconnectCurrentConnection()
{
    tcpSocket->disconnectFromHost();
}
bool MyTCPClient::waitForReadyRead(int milliseconds)
{
        QEventLoop eventLoop;
        QTimer timer;
        connect(this->tcpSocket, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));
        connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
        timer.setSingleShot(true);
        timer.start(milliseconds);
        eventLoop.exec();
        return timer.isActive();

}
