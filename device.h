#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include<QVector>
#include"devicesignal.h"
#include"devicecan.h"
class Device: public QObject
{
    Q_OBJECT

public:
    Device();
    //seting
    bool setting_status;
    //Actually
    bool online_status;
    bool actual_status;
    // devicename
    QString device_name;

    int signal_number;
    int device_id;
    QVector<DeviceSignal *> signal_vector;
    QVector<DeviceCan *> can_vector;



    void SetDeviceStatus(bool status);
    void UpdateActualStatus();
    void AddData(const QByteArray &message);
    int  ByteToInt32(QByteArray abyte0);
    void ClearReceiveData();
    void AddAdcData( QByteArray &adcbyte, int frame_time,int frame_length);
    void AddCanData( QByteArray &adcbyte, int frame_time,int frame_length);

    static int test_headtime;
};


#endif // DEVICE_H
