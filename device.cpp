#include "device.h"
#include "devicesignal.h"
#include<QDebug>
#include<math.h>


int Device::test_headtime=0;

Device::Device()
{
    signal_number = 6;
    for(int i =0;i<6;i++)
    {

        DeviceSignal *signal = new DeviceSignal();
        signal->signal_id = i;
        signal->device_id = device_id;

        signal_vector.append(signal);
    }

    for(int i=0;i<2;i++)
    {
        DeviceCan *can = new DeviceCan();
        can->signal_id = i;
        can->device_id = device_id;
        can_vector.append(can);
    }

    setting_status = false;
}

Device::~Device()
{
    for(int i =0;i<signal_vector.size();i++)
    {
        delete signal_vector[i];
    }
    signal_vector.clear();

    for(int i =0;i<can_vector.size();i++)
    {
        delete can_vector[i];
    }
}

void Device::SetDeviceStatus(bool status)
{
    setting_status = status;
}
void Device::UpdateActualStatus()
{
    actual_status = online_status && setting_status;
}

void Device::AddData(const QByteArray &message)
{
    int size = message.size();
    int frame_length = ByteToInt32(message.mid(8,4));

    int frame_time = ByteToInt32(message.mid(4,4))-test_headtime;//(100us)
   // qDebug()<<"frame_time*************"<<frame_time;
    // qDebug()<<"frame_length*************"<<frame_length;

    QByteArray meaasgebyte = message.mid(16+64,static_cast<int>(frame_length));
    qDebug()<<"MESSAGE TYPE CAN:1; ADC:2"<<int(message.at(14));
    if(message.at(14) ==2) AddAdcData(meaasgebyte,frame_time,frame_length);
    if(message.at(14) ==1)  AddCanData(meaasgebyte,frame_time,frame_length);
    if(frame_length+48<size)
    {
        QByteArray extern_message = message.right(size-frame_length-48);
        qDebug()<<"数据包有剩余数据";
    }
}

void Device::AddAdcData( QByteArray &adcbyte, int frame_time,int frame_length)
{
    static int count;
    count++;

    double time;
    int val;
   // qDebug()<<"AddAdcData============================";

    for(int i=0;i<frame_length;)
    {
        time= (frame_time+i/8*10)*0.0001;
        for(int j=0;j<4;j++)
        {
            val = uchar(adcbyte.at(i++))*256;
            val += uchar(adcbyte.at(i++));
            val = qint16(val);
            signal_vector.at(j)->signal_data->AddData(time,val);
        } 
    }
}

void Device::AddCanData(QByteArray &canbyte, int ,int frame_length)
{
    int frame_count = frame_length/25;
    int frame_time;
    double time;
    int channel;
    int can_id;
    qDebug()<<"AddCanData";
    for(int i=0;i<frame_count;i++)// 1+4+20
    {
        channel = canbyte.at(i*25);
        if(channel == 1 || channel == 2)
        {
            frame_time = ByteToInt32(canbyte.mid(i*25+1,4))-test_headtime;//(100us)
            time = frame_time * 0.0001;

            can_id = ByteToInt32(canbyte.mid(i*25+9,4));
//            qDebug()<<"can_id"<<canbyte.mid(i*25+9,4).toHex()<<can_id;
//            qDebug()<<"device_id"<<device_id;
//            qDebug()<<"channel"<<channel;
//            qDebug()<<"frame_time"<<frame_time;
//            qDebug()<<"canbyte.mid(i*25+16,8))"<<canbyte.mid(i*25+16,8).toHex();
            can_vector.at(channel-1)->AddFrameData(can_id,time,canbyte.mid(i*25+16,8));

            if(candata_status) emit addcanrow(time,device_id,channel,can_id,canbyte.mid(i*25+16,8));
        }
        else
        {
            qDebug()<<"FRAME ERROR";
        }
    }
}

int Device:: ByteToInt32(QByteArray abyte0)
{

    int data =0;

    for(int i=3;i>=0;i--)
    {
        data = data*256;
        data += uchar(abyte0.at(i));

    }
    return data;
}
void Device::ClearReceiveData()
{
    for(int i=0;i<6;i++) signal_vector.at(i)->ClearReceiveData();
    for(int i=0;i<2;i++) can_vector.at(i)->ClearReceiveData();
}
void Device::ShowCanData(bool status)
{
    candata_status = status;
}
