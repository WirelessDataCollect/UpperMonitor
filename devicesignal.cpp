#include<QDebug>
#include "devicesignal.h"

DeviceSignal::DeviceSignal()
{
    signal_data = new SignalData();
    update_status = false;
    vol_enable = true;
}


DeviceSignal::~DeviceSignal()
{

    delete signal_data;
}
void DeviceSignal::SetIVStatus(bool status)
{
    vol_enable = status;
}
void DeviceSignal::ClearReceiveData()
{
    signal_data->ClearAllData();
}
void DeviceSignal::SetMaxDataLen(int len)
{
    signal_data->SetMaxDataLen(len);
}

bool DeviceSignal::AddFilter(QColor color, QString name, QString express_str)
{
    if(signal_data->isExpreesionValue(express_str))
    {
        signal_data->SettingAttra( color,  name, express_str);
        return true;
    }
    else
    {
        return false;
    }
}
