#ifndef DEVICESYSTEM_H
#define DEVICESYSTEM_H

#include <QObject>
#include<QDateTime>
#include<QVector>
#include<QByteArray>
#include<QTimer>
#include<QDate>
#include "device.h"
#include"myudp.h"
#include"mytcpclient.h"

#define  GET_TIME_SYNC          (static_cast<char>(0xa1))


#define  GET_RETURN_ORDER       (static_cast<char>(0xa2))
#define  GET_TEST_NAME          (static_cast<char>(0xa3))
#define  TIME_SYNC_BOARD        (static_cast<char>(0xa4))
#define  GET_WIFI_SEND_EN      (static_cast<char>(0xa5))
#define  GET_WIFI_SEND_DISABLE (static_cast<char>(0xa6))
#define  GET_CHANNEL_MODEL     (static_cast<char>(0xa7))
#define  GET_CAN_SEND_EN       (static_cast<char>(0xa8))
#define  GET_REMOTE_IP_PORT    (static_cast<char>(0xa9))
#define  GET_HEARTBEAT         (static_cast<char>(0xaa))

#define MongoFindDocsNames  "MongoFindDocsNames"
#define MongoFindDocs "MongoFindDocs"
#define SendConfigure "StartTest"
#define ReceiveConfigure "GetTestConfig"
#define ReceiveRtdata "GetRtdata"

#define StopReceiveRtdata "StopGetRtdata"
#define PACKAGE_HEAD_FRAME_LENGTH 48
class DeviceSystem: public QObject
{
      Q_OBJECT

public:
    DeviceSystem();
    ~DeviceSystem();

    QString data_path;
    QString test_data_path;
    QString test_name;

    QDateTime test_time;

    QString test_name_time;

    int device_num;
    QVector<Device*> device_vector;

    QHostAddress tcp_target_addr;
    quint16 tcp_target_port;

    QHostAddress local_addr;

    QHostAddress data_target_addr;
    quint16 data_local_port;
    quint16 data_target_port;

    QHostAddress order_target_addr;
    quint16 order_local_port;
    quint16 order_target_port;

    QVector<bool> device_all_status;
    bool clock_device_status;




    MyUDP *udp_data  = nullptr;
    MyUDP *udp_order = nullptr;
    MyTCPClient *tcp_client = nullptr;


    bool TcpSendCheck(QString order, QString value = "");
    bool UdpSendCheck(QByteArray order, QByteArray value);
    bool UdpSendCheck();
    void SetDevStatus(bool status, int i= -1);
    void ClearData();
    void SetTestNameTime(QString name, QDateTime time);
    void SetTestDeep(double time);
    void NewLocalTest(QString name);
    void EndLocalTest();
    void RemoteTcpStart(QString username,QString passwd);
    bool FindDocsNames(QDate begin, QDate end);
    bool FindDocs(int index);

    bool LocalOrderUdpStart();
    bool LocalDataUdpStart();

    QVector<bool> checkreturn(char order);
    bool checkreturn(char order,char channelnum);

    bool LocalTestStart();

    bool LocalTestIVModel();
    bool SendRemoteAdress(QHostAddress ip, quint16 port);
    bool LocalTestSyncTime();
    bool LocalTestName();
    bool SendCanFilter();
    void ReceiveDocsName(const QByteArray &message);
    void RemoteTcpLogin(QByteArray salt);
    void ReciveDeviceData();
    void  SetFilterLengthMax(int length,double max);
    void ClearCanFilter();
    bool SendConfigureFile(QString test_name);
    bool FindConfigureFile(QString test_name);
    bool ReceiveConfigureFile(QByteArray configure_data);
    bool GetRTdata();
    bool StopGetRTdata();
    bool SaveDataFile(QString file_name);
    bool LoadDataFile(QString file_name);
    void AutoStop(int time);
    void ShowCanData(bool status);
    void SetLocalTest(bool status);
    QByteArray device_data;
    class DocName
    {
    public:
        QList<QString> name_list;
        QList<QString> time_list;
        QList<QByteArray> name_time_list;
        QList<QDateTime> datetime_list;
        void cleardata();
    }doc_name;

    bool is_local_test;
    bool is_receive_data;
    void RemoteTcpReset();
    void StopSendDocs();

signals:
    void UpdataTestName(QString str);
    void UpdataTestTime(QString str);
    void UpdataTestDeep(QString str);
    //void TcpClientTimeOut();
    void ReceiveRadstr(QByteArray str);
    void TcpConnectStatus(bool status, QString str = "");
    void UpdataDocsnames(QList<QString> name,QList<QString> time);
    void SaveConfigureFile(QString file = "");
    void LoadConfigureFile(QString file = "");
    void testconfigureshow(QString str);


public slots:

    void onTcpClientAppendMessage(const QString &from, const QByteArray &message);
    void onTcpClientConnected(const QString &from, const quint16 port);
    void onTcpConnectFailed();
    void onUdpOrderMessage(const QString &from, const QByteArray &message);
    void onUdpDataMessage(const QString &from, const QByteArray &message);
    void UdpHeartBeat();
    void LocalThread();
    bool LocalTestStop();
    void ShowSpeed();

private:
    double test_deep_time;
    QByteArray Tcp_Data;
    QByteArray Tcp_Data_list;
    QByteArray udp_order_return;
    int tcp_message_flag;
    int tcp_data_number;
    int tcp_package_number;
    double tcp_time;
    QString username;
    QString passwd;

    QByteArray IntToHighByte(quint32 i);
    QByteArray uint16ToByte(quint16 i);
    QByteArray DatetimeToByte(QDateTime datetime);
    QDateTime ByteToDatetime(QByteArray datebyte);
    QByteArray Uint32ToByte(quint32 i);

    int  ByteToInt32(QByteArray abyte0);
    void sleep(int msec);
    void TestConfigureShow();

    QTimer *heart_beat_timer =nullptr;
    QTimer *show_speed_timer = nullptr;

    QTimer *auto_stop = nullptr;
    int time_count;
};

#endif // DEVICESYSTEM_H
