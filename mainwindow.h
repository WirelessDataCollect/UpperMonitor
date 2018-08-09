#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextTable>
#include <QScrollBar>
#include <QSettings>
#include <QNetworkInterface>


#include <QHostAddress>
#include <QHostInfo>

#include <QProcess>
#include<QTime>

#include<QThread>

#include<QDateTime>
#include "myudp.h"

#define  GET_TIME_SYNC          0xa1
#define  GET_WIFI_SEND_EN       0xa5
#define  GET_WIFI_SEND_DISABLE  0xa6
#define  GET_CHANNEL_MODEL      0xa7
#define  GET_CAN_SEND_EN        0xa8
#define  GET_REMOTE_IP_PORT     0xa9


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void udpsent(QHostAddress IP, quint16 senderPort, QByteArray Data);
    void udpsent(QString IP, quint16 senderPort, QByteArray Data);
    bool bindPort(QHostAddress addr, qint16 port);
private slots:

//    void onTcpServerSendMessage();
//    void onTcpServerAppendMessage(const QString &from, const QString &message);

    void on_button_UdpSend_clicked();

    void on_button_UdpStart_clicked();

    void onUdpAppendMessage(const QString &from, const QString &message);
    void onUdpAppendMessage(const QString &from, const QByteArray &message);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyUDP *myudp = nullptr;
    MyUDP *syncudp = nullptr;
    quint16 udpListenPort;
    quint16 syncListenPort;

    QHostAddress localAddr;
    QHostAddress syncTargetAddr;


    quint16 udpTargetPort;
    quint16 syncTargetPort;

    QByteArray IntToByte(quint32 i);
    QByteArray MainWindow:: uint16ToByte(quint16 i);
    QByteArray DatetimeToByte(QDateTime datetime);
private:
    Ui::MainWindow *ui;

    QTextTableFormat tableFormat;
    void MainWindow::findLocalIPs();
    void start();
    void stop();
    void synctime();
    void SendIpAdress(QHostAddress addr, quint16 port);
};

#endif // MAINWINDOW_H
