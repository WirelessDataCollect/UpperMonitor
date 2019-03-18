#include "device.h"
#include "devicesignal.h"
#include<QDebug>

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
      qDebug()<<"数据包数据不足";

    int size = message.size();
    int frame_length = ByteToInt32(message.mid(8,4));

    if(frame_length+48>size)  //包残缺
    {
        frame_length = (size-48)/8*8;
        qDebug()<<"数据包数据不足";
    }

    int frame_time = ByteToInt32(message.mid(4,4))-test_headtime;
    qDebug()<<"frame_time*************"<<frame_time;
     qDebug()<<"frame_length*************"<<frame_length;
    QByteArray adcbyte = message.mid(16+64,static_cast<int>(frame_length));
    int y=0;
    for(int i=0;i<frame_length;)
    {
        for(int j=0;j<4;j++)
        {
             QPoint point;
            point.setX(frame_time+10*(i/8));
            int x = point.x();

             y = uchar(adcbyte.at(i++))*256;
             y += uchar(adcbyte.at(i++));
            point.setY(y);
            y = point.y();
           if(j==0) qDebug()<<x<<y;
            signal_vector.at(j)->AddData(point);
        }
    }
    for(int j=0;j<4;j++)
    {
        signal_vector.at(j)->AddFrameData();
    }

    if(frame_length+48<size)
    {
        QByteArray extern_message = message.right(size-frame_length-48);
        qDebug()<<"数据包有剩余数据";
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
    for(int i=0;i<signal_number;i++)
    {
        signal_vector.at(i)->ClearReceiveData();
    }
}
