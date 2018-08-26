#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextTable>
#include <QScrollBar>
#include <QSettings>
#include <QNetworkInterface>
#include <QTimer>

#include <QHostAddress>
#include <QHostInfo>

#include <QProcess>
#include<QTime>
#include<QTimeZone>
#include<QThread>

#include<QDateTime>
#include "myudp.h"
#include <numeric>
#include"chartswidgt.h"
#include"showwidget.h"
#define  GET_TIME_SYNC          0xa1
#define  TIME_SYNC_BOARD        0xa4

#define  GET_RETURN_ORDER       0xa2
#define  GET_TEST               0xa3

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
    void myudpsent(QHostAddress IP, quint16 senderPort, QByteArray Data);
    bool bindPort(QHostAddress addr, quint16 port);
    void sendplotdata(QVector<double> &plotdata);
private slots:

//    void onTcpServerSendMessage();
//    void onTcpServerAppendMessage(const QString &from, const QString &message);

    void on_button_UdpSend_clicked();

    void on_button_UdpStart_clicked();

    void onUdpAppendMessage(const QString &from, const QString &message);
    void onUdpAppendMessage(const QString &from, const QByteArray &message);

    void syncrxmessage(const QString &from, const QByteArray &message);
     bool sendIVmodle(QByteArray &databyte);
    void AdcByteToData(const QString &from, const QByteArray &message);
    void UiDataShow();
    void UiChartShow();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyUDP *myudp = nullptr;
    MyUDP *syncudp = nullptr;
    QTimer *timer = nullptr;
    QTimer *plottimer = nullptr;
    chartswidgt *dialog = nullptr;

    QVector<showwidget *> datawidget;
    quint16 udpListenPort;
    quint16 syncListenPort;

    QHostAddress localAddr;
    QHostAddress syncTargetAddr;

    quint64 TotalByteNum;
    quint64  TotalPackNum;

    quint16 udpTargetPort;
    quint16 syncTargetPort;

    QByteArray DigitalIO;


    QVector<QVector< QVector<double> > > Adc_data;
    QVector<int> ClientStatus;
    QVector<char> OrderReturn;
    int ClientCount;
    QByteArray IVset;
    QByteArray IntToByte(quint32 i);
    QByteArray IntToHighByte(quint32 i);
    QByteArray uint16ToByte(quint16 i);
    QByteArray DatetimeToByte(QDateTime datetime);
    QDateTime DatetimeToByte(QByteArray datebyte);
    quint32  ByteTouint32(QByteArray abyte0);
    quint16 ByteTouint16(QByteArray abyte0);
    QDateTime ByteToDatetime(QByteArray datebyte);
    double ByteToAdcdata(QByteArray abyte0);
    void sleep(int msec);

private:
    Ui::MainWindow *ui;

    QTextTableFormat tableFormat;

    void findLocalIPs();
    void testconnect();
    bool start();
    bool stop();
    bool synctime();
    bool SendIpAdress(QHostAddress addr, quint16 port);
    bool SendAdcModle();
    int checkreturn(int order);
    void DataShow(int channel, QByteArray bate0);
    void initoff();

};

#endif // MAINWINDOW_H
