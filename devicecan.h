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
    char can_id;
    char baud_rate;
    bool show_enable;
    QVector<SignalData *> filter_list;
    void SetSignalStatus(bool status);
    void SetBaudRate(bool status);
    bool AddFilter(uint id, QColor color, QString name, QString express_str);
    void RemoveFilter(QColor color, QString name, QString express_str);
    void AddFrameData(quint32 id,double time, QByteArray data);
    bool update_size;

private:

};

#endif // DEVICECAN_H
