#include<QDebug>
#include "devicesignal.h"

DeviceSignal::DeviceSignal()
{
    signal_data = new SignalData();
    update_status = false;
    filter_length = 1;
    for(int i=0;i<filter_length;i++) filter_list.append(0);
    vol_enable = true;
}


DeviceSignal::~DeviceSignal()
{

    delete signal_data;
}

double DeviceSignal::Filter(double value)
{
    double sum=0;
    if (filter_length==0 || filter_length== 1) return value;
   // qDebug()<<"filter_length"<<filter_length;
    filter_list.append(value);
    filter_list.removeFirst();
    for(int i=0;i<filter_list.length();i++)
    {
        sum+=filter_list.at(i);
    }
    sum = sum/filter_list.length();
   //qDebug()<<"length"<<filter_list.length();
    return sum;
}

void DeviceSignal::SetIVStatus(bool status)
{
    vol_enable = status;
}
void DeviceSignal::SetFilterLength(int length)
{
    filter_length = length;
    filter_list.clear();
    for(int i=0;i<filter_length;i++) filter_list.append(0);
    qDebug()<<"SetFilterLength"<<length;

}
void DeviceSignal::ClearReceiveData()
{
    signal_data->ClearAllData();
}
