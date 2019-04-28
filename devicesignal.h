#ifndef DEVICESIGNAL_H
#define DEVICESIGNAL_H
#include<QObject>
#include<QColor>
#include<QDateTime>
#include<QPointF>
#include<QTimer>
#include"signaldata.h"
class DeviceSignal: public QObject
{
    Q_OBJECT

public:
    DeviceSignal();
    ~DeviceSignal();
    SignalData *signal_data;
    bool update_status;

    int signal_id;
    int device_id;
    bool vol_enable;

    QList<double> filter_list;
    int filter_length;

    double Filter(double value);
    void SetFilterLength(int length);
    void SetIVStatus(bool status);
    void ClearReceiveData();
};

#endif // DEVICESIGNAL_H
