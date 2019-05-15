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
