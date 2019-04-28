#ifndef DEVICECAN_H
#define DEVICECAN_H
#include<QObject>
#include<QMap>
#include<QVector>
#include<QRegExp>
#include<QColor>
#include<QDebug>
#include<QDateTime>

#include"signaldata.h"
class DeviceCan
{
public:
    DeviceCan();
    int device_id;
    int signal_id;
    char baud_rate;
    bool show_enable;
    QVector<SignalData *> filter_list;
    void SetSignalStatus(bool status);
    void SetBaudRate(bool status);
    bool AddFilter(uint id, QColor color, QString name, QString express_str);
    void RemoveFilter(QColor color, QString name, QString express_str);
    void AddFrameData(int id,double time, QByteArray data);
    void ClearReceiveData();
    bool update_status;


private:

};

#endif // DEVICECAN_H
