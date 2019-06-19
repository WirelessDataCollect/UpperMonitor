#include "devicecan.h"

DeviceCan::DeviceCan()
{
    baud_rate = 50;
    show_enable = false;
    update_status = false;
}
void DeviceCan::SetSignalStatus(bool status)
{
    show_enable = status;
}
void DeviceCan::SetBaudRate(bool status)
{

    if(status) baud_rate = 50;
    else baud_rate = 25;
    qDebug()<<"baud_rate"<<device_id<<signal_id<<int(baud_rate);
}
bool DeviceCan::AddFilter(uint id, QColor color, QString name, QString express_str)
{

    SignalData *message = new SignalData();
    if(message->isExpreesionValue(express_str))
    {
        message->id = id;
        message->SettingAttra( color,  name, express_str);
        filter_list.append(message);
        qDebug()<<color<<name<<express_str;
        update_status = true;
        return true;
    }
    else
    {
        delete message;
        return false;
    }

}

void DeviceCan::RemoveFilter(QColor color, QString name, QString express_str)
{
    for(int i=0;i<filter_list.size();i++)
    {
       // SignalData *message = filter_list.at(i);
        qDebug()<<"/===================================";
        qDebug()<<color<<name<<express_str;
        qDebug()<<filter_list.at(i)->color<<filter_list.at(i)->name<<filter_list.at(i)->express_str;
        if(filter_list.at(i)->color == color && filter_list.at(i)->name == name && filter_list.at(i)->express_str == express_str)
        {

            //delete  filter_list.at(i);
            filter_list.at(i)->message_list.clear();
            filter_list.at(i)->time_list.clear();
            filter_list.at(i)->val_list.clear();
            filter_list.removeAt(i);
            update_status =true;
        }
    }
    return;
}
void DeviceCan::AddFrameData(int id,double time, QByteArray data)
{


    for(int i=0;i<filter_list.size();i++)
    {
        if(filter_list.at(i)->id == id)
           filter_list.at(i)->AddData(time,data);
    }

}
void DeviceCan::ClearReceiveData()
{
     for(int i=0;i<filter_list.size();i++)
     {
         filter_list.at(i)->ClearAllData();

     }
      update_status =true;
}
