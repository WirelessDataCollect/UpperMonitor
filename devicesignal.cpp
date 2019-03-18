#include<QDebug>
#include "devicesignal.h"

DeviceSignal::DeviceSignal()
{
    signal_name = "test";
    show_enable = false;
    vol_enable = false;
    update_status = false;
    updata_all_data = false;
    filter_length = 1;
    for(int i=0;i<filter_length;i++) filter_list.append(0);
}

void DeviceSignal::SetSignalStatus(bool status)
{
    show_enable = status;
    update_status = true;
}
void DeviceSignal::SetIVStatus(bool status)
{
    vol_enable = status;
}
void DeviceSignal::ClearFrameData()
{
    frame_raw_data.clear();
    frame_unit_data.clear();
}


void DeviceSignal::AddFrameData()
{
    if(updata_all_data) return;
    all_raw_data.append(frame_raw_data);


    all_unit_data.append(frame_unit_data);

    frame_unit_data.clear();
    frame_raw_data.clear();

    update_status = true;
}

void DeviceSignal::UpdataAllUnitData()
{
    updata_all_data = true;
    all_unit_data.clear();
   for(int i=0; i<all_raw_data.size();i++)
   {
       QPointF point_f;
       point_f.setX(all_raw_data.at(i).x()*0.001);
       double y = all_raw_data.at(i).y()*k;
       point_f.setY(Filter(y));
       all_unit_data.append(point_f);
   }

   updata_all_data = false;

   update_status = true;
}

void DeviceSignal::AddData(QPoint point)
{
    frame_raw_data.append(point);
    QPointF point_f;
    point_f.setX(point.x()*0.0001);
    double y = point.y()*k;
    point_f.setY(Filter(y));
    frame_unit_data.append(point_f);
    //qDebug()<<frame_unit_data.last().x()<<frame_unit_data.last().y();
}

void DeviceSignal::SetSignalName(QString name)
{
    signal_name = name;
    update_status = true;
}

void DeviceSignal::SetSignalColor(QColor color)
{
    line_collor = color;
    update_status = true;
}
bool DeviceSignal::SetUnitVol(int index,double value)
{
    switch (index) {
    case 1:
        if(abs(value-min_v)>0.000001)
        {
            min_v = value;
            if(abs(max_v-min_v)<0.000001) return false;

        }
        break;
    case 2:
        if(abs(value-max_v)>0.000001)
        {
           max_v = value;
           if(abs(max_v-min_v)<0.000001) return false;

        }
        break;
    case 3:
        if(abs(value-min_unit)>0.000001)
        {
            min_unit = value;
            if(abs(max_unit-min_unit)<0.000001) return false;

        }
        break;
    case 4:
        if(abs(value-max_unit)>0.000001)
        {
            max_unit = value;
            if(abs(max_unit-min_unit)<0.000001) return false;
        }
        break;
    }
    qDebug()<<"min_v"<<min_v;
    qDebug()<<"max_v"<<max_v;
    qDebug()<<"min_unit"<<min_unit;
    qDebug()<<"max_unit"<<max_unit;
     k=(max_unit-min_unit)/(max_v-min_v)* 152*0.000001;

    UpdataAllUnitData();
    return true;
}


void DeviceSignal::ClearReceiveData()
{
    all_raw_data.clear();
    all_unit_data.clear();
    frame_raw_data.clear();
    frame_unit_data.clear();
    update_status =true;
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
void DeviceSignal::SetFilterLength(int length)
{
    filter_length = length;
    filter_list.clear();
    for(int i=0;i<filter_length;i++) filter_list.append(0);
    qDebug()<<"SetFilterLength"<<length;
    UpdataAllUnitData();
}
