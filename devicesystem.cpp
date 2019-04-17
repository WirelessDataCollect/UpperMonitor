﻿#pragma execution_character_set("utf-8")
#include<QCoreApplication>
#include<QMessageBox>
#include<QTimer>
#include<QTimeZone>
#include<QDebug>
#include "devicesystem.h"
#include<QThread>
#include"md5.h"
DeviceSystem::DeviceSystem()
{
    device_num = 5;

    for(int i=0;i<device_num;i++)
    {
        Device *device = new Device();
        device->device_id = i;
        for(int j=0;j<device->signal_number;j++) device->signal_vector.at(j)->device_id = i;
        device_vector.append(device);
    }
    udp_order = new MyUDP();
    udp_data  = new MyUDP();

    //tcp ip and port
    tcp_client = new MyTCPClient();

    tcp_target_addr.setAddress("115.159.154.160");
    tcp_target_port = 8089;

   //local udp

   data_local_port = 5014;
   data_target_port= 5002;

   order_target_addr = QHostAddress("255.255.255.255");
   order_local_port = 5003;
   order_target_port= 5003;
   device_all_status.fill(0,15);

   heart_beat_timer = new QTimer();
   LocalThread();
   tcp_message_flag = 0;


}
void DeviceSystem::LocalThread()
{
    QThread *udp_order_thread = new QThread();
    udp_order->moveToThread(udp_order_thread);
    udp_order_thread->start();

//    QThread *udp_data_thread = new QThread();
//    udp_data->moveToThread(udp_data_thread);
//    udp_data_thread->start();

//    QThread *tcp_client_thread = new QThread();
//    tcp_client->moveToThread(tcp_client_thread);
//    tcp_client_thread->start();
}

DeviceSystem::~DeviceSystem()
{

    QString order("Disconnect");
    QString value;
    bool status = TcpSendCheck(order,value);
    qDebug()<<"TcpSendCheck Disconnect Status"<<status;
    tcp_client->disconnectCurrentConnection();
    tcp_client->closeClient();

    heart_beat_timer->stop();
    delete  heart_beat_timer;

    udp_data->unbindPort();
    delete  udp_data;

    udp_order->unbindPort();
  //  delete  udp_order;


    if(is_local_status)
    {

    }
}

void DeviceSystem::RemoteTcpStart(QString username,QString passwd)
{
    is_local_status = false;
    qDebug()<<"RemoteTcpStart start";
    this->username = username;
    this->passwd = passwd;

   disconnect(tcp_client, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    disconnect(tcp_client,SIGNAL(myClientConnected(QString,quint16)), this,SLOT(onTcpClientConnected(QString,quint16)));
    disconnect(tcp_client,SIGNAL(connectionFailed()), this,SLOT(onTcpConnectFailed()));

    tcp_client->disconnectCurrentConnection();

    connect(tcp_client, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
   connect(tcp_client,SIGNAL(myClientConnected(QString,quint16)), this,SLOT(onTcpClientConnected(QString,quint16)));
    Tcp_Data.clear();

    qDebug()<<"STATUS"<<tcp_client->connectTo(tcp_target_addr, tcp_target_port);
}

void DeviceSystem::onTcpClientConnected(const QString &from, const quint16 port)
{
    connect(tcp_client,SIGNAL(connectionFailed()), this,SLOT(onTcpConnectFailed()));
    qDebug()<< tcp_client->waitForReadyRead(3000);
    sleep(300);
    qDebug()<< "onTcpClientConnected"<<Tcp_Data;

    if(!Tcp_Data.isEmpty())
    {
        QByteArray radom_array =  Tcp_Data.remove(0,8);
        radom_array.remove(radom_array.size()-1,1);
        RemoteTcpLogin(radom_array);
       // qDebug()<<"str"<<radom_array;
    }
    else
    {
        emit TcpConnectStatus(false, "无法接收随机数验证消息");
    }
}



void DeviceSystem::RemoteTcpLogin(QByteArray salt)
{
    QByteArray PASSWD = passwd.toUtf8();
    qDebug()<<"passwd"<<passwd;
    qDebug()<<"username"<<username;

    QByteArray MessageDigest = MD5Process(salt,PASSWD);
    QString order("Login");

    QString value = username+";"+MessageDigest;
    qDebug()<<"value"<<value;
    if(TcpSendCheck(order, value))
    {
        emit TcpConnectStatus(true);
    }
    else
    {
         emit TcpConnectStatus(false, "密码错误");
         qDebug()<<"密码错误";
    }

}
void DeviceSystem::onTcpConnectFailed()
{

    disconnect(tcp_client, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    disconnect(tcp_client,SIGNAL(myClientConnected(QString,quint16)), this,SLOT(onTcpClientConnected(QString,quint16)));
    disconnect(tcp_client,SIGNAL(connectionFailed()), this,SLOT(onTcpConnectFailed()));

    emit TcpConnectStatus(false, "远程连接断开");
}

void DeviceSystem::onTcpClientAppendMessage(const QString &from, const QByteArray &message)
{
    Tcp_Data= message;

  //  qDebug()<<"tcp_message_flag"<<tcp_message_flag;
   // qDebug()<<"message.contains(MongoFindDocsNames:)"<<message.contains("MongoFindDocsNames:");

    if(tcp_message_flag !=1 && message.startsWith("MongoFindDocsNames:"))
    {
        tcp_message_flag = 1;

    }
    if(tcp_message_flag !=2 && message.startsWith("MongoFindDocs:"))
    {
        tcp_message_flag =2;
    }

    if(tcp_message_flag == 1)
    {
       // qDebug()<<"Tcp_Data_list"<<Tcp_Data_list;
        Tcp_Data_list.append(Tcp_Data);

        if(Tcp_Data_list.contains("OVER"))
        {
            qDebug()<<"XXXXXXXXXXXXXXXXXX"<<"OVER";
            ReceiveDocsName(Tcp_Data_list);
            tcp_message_flag =0;
            //Tcp_Data_list.clear();
        }
    }
    if(tcp_message_flag == 2)
    {
          device_data.append(Tcp_Data);
          ReciveDeviceData();
          qDebug()<<" ReciveDeviceD================";
    }
}

bool DeviceSystem::LocalOrderUdpStart()
{
    is_local_status = true;
    bool is_success = udp_order->bindPort(local_addr,order_local_port);
    if(is_success)
    {
        connect(udp_order,SIGNAL(newMessage(QString,QByteArray)),this, SLOT(onUdpOrderMessage(QString,QByteArray)));

        heart_beat_timer->start(10000);
        connect(heart_beat_timer, SIGNAL(timeout()), this, SLOT(UdpHeartBeat()));


       for(int i =0;i<3;i++)
       {
           UdpHeartBeat();
           sleep(50);
       }
       return true;
    }
    else return false;
}

bool DeviceSystem::LocalDataUdpStart()
{
    bool is_success = udp_data->bindPort(local_addr,data_local_port);
    if(is_success)
    {
        connect(udp_data,SIGNAL(newMessage(QString,QByteArray)),this, SLOT(onUdpDataMessage(QString,QByteArray)));
        return true;
    }
    else
    {
        udp_data->unbindPort();
       return false;

    }
}

void DeviceSystem::onUdpOrderMessage(const QString &from, const QByteArray &message)
{
   // qDebug()<<"onUdpOrderMessage"<<message.toHex();
    if(from != local_addr.toString() && message.at(0) == GET_RETURN_ORDER ){
        udp_order_return.append(message.at(1));
        udp_order_return.append(message.at(2));
        qDebug()<<"udp_order_return SLOT"<<udp_order_return;
    }

}
void DeviceSystem::onUdpDataMessage(const QString &from, const QByteArray &message)
{

    time_count++;
    qDebug()<<"________________________________________________________";
   // qDebug()<<"from"<<from<<"onUdpDataMessage SIZe"<<message.size();
    int size =  message.size();

  //  qDebug()<<"id"<<message.at(11);
    if(size<48) return;

    QDateTime datatime = ByteToDatetime(message.left(8));
   // qDebug()<<"datatime"<<datatime.toString(Qt::ISODate)<<message.left(8).toHex();

    // qDebug()<<"datatime YYYY_MM_DD"<<ByteTouint32(message.left(4));

    int count =  ByteToInt32(message.mid(8,4));
    int node_id = int(message.at(12));
    QByteArray test_name = message.mid(16,32);
    QList<QByteArray> name_list = test_name.split('/');

  //   qDebug()<<"test_name"<<QString::fromUtf8(test_name);

     if(name_list.size()>1)
     {
         qDebug()<<"name_list"<<name_list.at(1);
         QDateTime datatime_2 = QDateTime::fromString(QString(name_list.at(1)),Qt::ISODate);
         qDebug()<<"datatime"<<datatime_2.toString(Qt::ISODate);

     }

     qDebug()<<"node_id"<<node_id;
     qDebug()<<"message type"<<int(message.at(13));
     if(node_id>0 &&node_id<5) device_vector.at(node_id-1)->AddData(message);

 //    qDebug()<<"ALL date size"<<device_vector.at(1)->signal_vector.at(1)->all_raw_data.size();
 //    qDebug()<<"frame date size"<<device_vector.at(1)->signal_vector.at(1)->frame_raw_data.size();


     //qDebug()<<"________________________________________________________";
}

void DeviceSystem::ReciveDeviceData()
{

    if(device_data.startsWith(MongoFindDocs))
    {

        if(device_data.size()>static_cast<int>(sizeof(MongoFindDocs))+16+64)
        {
             qDebug()<<"okokokokokoko"<<device_data.left(sizeof(MongoFindDocs)+16).toHex();
            int count = ByteToInt32(device_data.mid(static_cast<int>(sizeof(MongoFindDocs))+8,4));
            qDebug()<<"COUNT"<<count;
            if(device_data.size()>static_cast<int>(sizeof(MongoFindDocs))+16+64+count)
            {
                 int node_id = int(device_data.at(static_cast<int>(sizeof(MongoFindDocs)+12)));
                 qDebug()<<"node_id"<<node_id;
                QByteArray fram_array =  device_data.mid(static_cast<int>(sizeof(MongoFindDocs)),count+64+16);
                  if(node_id>0 &&node_id<5) device_vector.at(node_id-1)->AddData(fram_array);
                device_data.remove(0,static_cast<int>(sizeof(MongoFindDocs))+16+64+count);

            }
            else return;
        }
        else return;
    }
    else
    {
        device_data.remove(0,1);
        qDebug()<<"ERROR remove(0,1)";
    }
    if(device_data.isEmpty()) return;
     ReciveDeviceData();



}

bool DeviceSystem::TcpSendCheck(QString order, QString value)
{
    Tcp_Data.clear();
    if(value.isEmpty()) tcp_client->sendMessage(order);
    else tcp_client->sendMessage(order+"+"+value);
    tcp_client->waitForReadyRead(3000);
    sleep(100);
    qDebug()<<"TcpSendCheck"<<order+"+"+value;
    qDebug()<<"TcpSendCheck"<<Tcp_Data;

    if(Tcp_Data==order +":OK\n"){
        return true;
    }
    else return false;
}

bool DeviceSystem::checkreturn(char order,char channelnum)
{
      if(udp_order_return.isEmpty()) return false;
      for(int i=0;i<udp_order_return.count()-1;i=i+2)
      {
          if(udp_order_return.at(i)==order && udp_order_return.at(i+1)==channelnum)
          {
              udp_order_return.remove(i,2);
              return true;
          }
      }
      return false;
}

QVector<bool> DeviceSystem::checkreturn(char order)
{
     QVector<bool> channel;
     channel.fill(0,5);
      if(udp_order_return.isEmpty()) return channel;
      for(int i=0;i<udp_order_return.count()-1;i=i+2)
      {
          if(udp_order_return.at(i)==order &&udp_order_return.at(i+1)<5 &&udp_order_return.at(i+1)>0)
          {
              channel[udp_order_return.at(i+1)-1]=1;
              udp_order_return.remove(i,2);
              i=i-2;
          }
      }
      return channel;
}


bool DeviceSystem::UdpSendCheck(QByteArray order, QByteArray value)
{
    QByteArray send_data;
    send_data.append(order);
    send_data.append(value);
    udp_order->sendMessage(order_target_addr,order_target_port,send_data);
    for(int i = 0;i<2;i++)
    {
        qDebug()<<i<<"______"<<send_data.toHex();
        udp_order->waitForReadyRead(300);
        sleep(100);
        if(value.isEmpty()) //广播
        {
            if(checkreturn(order.at(0)) == device_all_status.mid(0,5))
                return true;
        }
        else
        {
            if(checkreturn(order.at(0),value.at(0)))
                return true;
        }
    }
    return false;
}

void DeviceSystem::UdpHeartBeat()
{
    //check  GET_HEARTBEAT
    QVector<bool> channel =checkreturn(GET_HEARTBEAT);
    //三次状态取或
    device_all_status+=channel;
    device_all_status.erase(device_all_status.begin(),device_all_status.begin()+5);
    for(int i=0;i<device_num;i++)
    {
        device_all_status[i]=(device_all_status.at(i) | device_all_status.at(i+5) | device_all_status.at(i+10));

        device_vector.at(i)->online_status =  device_all_status[i];
        device_vector.at(i)->UpdateActualStatus();
        qDebug()<<"终端状态"<<i+1<<"------>"<<device_vector.at(i)->online_status;
    }
     qDebug()<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    //send
     QByteArray send_data;
     send_data.append(GET_HEARTBEAT);
     QString text = "heartbeat: "+ send_data.toHex();
     udp_order->sendMessage(order_target_addr,order_target_port,send_data);
     udp_data->sendMessage(order_target_addr,5000,send_data);
}

bool DeviceSystem::LocalTestStart()
{
    QByteArray order;
    QByteArray value;
    order.append(GET_WIFI_SEND_EN);
    bool is_success = false;
    for(char i=0;i<device_num;i++)
    {
        if(device_vector.at(i)->actual_status)
        {
            value.clear();
            value.append(i+1);
            for(int j=0;j<3;j++)
            {
                is_success=UdpSendCheck(order,value);
                if(is_success) break;
            }
            if(!is_success) return false;
        }
    }
    return true;
}

bool DeviceSystem::LocalTestStop()
{
    QByteArray order;
    QByteArray value;
    order.append(GET_WIFI_SEND_DISABLE);
    bool is_success = false;
    for(char i=0;i<device_num;i++)
    {
       // if(device_vector.at(i)->actual_status)
       // {
            value.clear();
            value.append(i+1);
            for(int j=0;j<3;j++)
            {
                is_success=UdpSendCheck(order,value);
                if(is_success) break;

            }
            //if(!is_success) return false;

      //  }

    }
    return true;
}

bool  DeviceSystem::LocalTestIVModel()
{
    QByteArray order;
    QByteArray value;
    order.append(GET_CHANNEL_MODEL);
    bool is_success = false;
    QByteArray iv_model;
    for(char i=0;i<device_num;i++)
    {
        if(device_vector.at(i)->actual_status)
        {

            value.clear();
            value.append(i+1);
            iv_model.clear();
            for(int k=0;k<4;k++)
            {
                iv_model.append(device_vector.at(i)->signal_vector.at(k)->vol_enable);
            }
            value.append(iv_model);
            for(int j=0;j<3;j++)
            {
                is_success=UdpSendCheck(order,value);
                if(is_success) break;
            }
            if(!is_success) return false;
        }
    }
    return true;
}
bool DeviceSystem::SendCanFilter()
{
    QByteArray order;
    QByteArray value;
    value.clear();
    order.append(GET_CAN_SEND_EN);

     char filter_size;
     DeviceCan *device_can;
     bool is_success;
     quint32 id;
    for(char i=0;i<device_num;i++)
    {
        for(char j=0;j<2;j++)
        {
            device_can = device_vector.at(i)->can_vector.at(j);
            if(device_can->show_enable &&! device_can->filter_list.isEmpty())
            {
                value.clear();
                value.append(i+1); //device
                value.append(j+1); //channel
                value.append(device_can->baud_rate);//baud_rate
                filter_size =char(device_can->filter_list.size());
                value.append(filter_size); //size
                for(char k=0;k<filter_size;k++)
                {
                     id = device_can->filter_list.at(k)->id;

                    value.append(Uint32ToByte(id));
                    qDebug()<<"decive:"<<int(i)<<"Channel"<<int(j)<<"id"<<id<<filter_size<<value.toHex();
                }


            for(int k=0;k<3;k++)
            {
              is_success=UdpSendCheck(order,value);
              if(is_success) break;
            }
            }
            }
        }
    return true;
}

bool DeviceSystem::LocalTestSyncTime()
{
    QByteArray order;
    QByteArray value;
    order.append(GET_TIME_SYNC);
    QDateTime datetime = QDateTime::currentDateTime();
    order.append(DatetimeToByte(datetime));
    for(int i=0;i<3;i++)
    {
       if(UdpSendCheck(order,value))
           return true;
    }
    return false;
}

bool DeviceSystem::LocalTestName()
{

    QByteArray order;
    QByteArray value;
    value.clear();
    order.append(GET_TEST_NAME);
    order.append(test_name.toUtf8());
    order.append('/');
   // order.append(QString::number(test_time.toMSecsSinceEpoch()));
   // order.append(DatetimeToByte(test_time));
    order.append(test_time.toString(Qt::ISODate));
    order.append('\0');

    qDebug()<<"test_name_set"<<order<<order.size();
    for(int i=0;i<3;i++)
    {
       if(UdpSendCheck(order,value))
           return true;
    }
    return false;
}

bool DeviceSystem::SendRemoteAdress(QHostAddress ip, quint16 port)
{
    QByteArray order;
    QByteArray value;
    value.clear();
    order.append(GET_REMOTE_IP_PORT);

    quint32    ipv4sdress = ip.toIPv4Address();
    QByteArray ipv4adressByte =IntToHighByte(ipv4sdress);
    QByteArray portByte = uint16ToByte(port);
    order.append(ipv4adressByte);
    order.append(portByte);
    for(int i=0;i<3;i++)
    {
       if(UdpSendCheck(order,value))
           return true;
    }
    return false;
}

void DeviceSystem::SetDevStatus(bool status, int index)
{
    if(index ==-1)
    {
        for(int i=0;i<device_num;i++)
            device_vector.at(i)->setting_status=status;
    }
    else
         device_vector.at(index)->setting_status=status;
}

void DeviceSystem::SetTestName(QString str)
{
    test_name = str;
    emit UpdataTestName(str);
}
void DeviceSystem::SetTestTime(QDateTime datetime)
{
    test_time = datetime;
    Device::test_headtime = datetime.time().msecsSinceStartOfDay()*10;
    emit UpdataTestTime(datetime.toString(Qt::ISODate));
}
void DeviceSystem::SetTestDeep(QString str)
{
     emit UpdataTestDeep(str);
}

void DeviceSystem::ClearData()
{
    SetTestName("");
    SetTestTime(QDateTime::currentDateTime());
    for(int i =0;i<device_num;i++)
    {
        device_vector.at(i)->ClearReceiveData();
    }
}

void DeviceSystem::NewLocalTest(QString name)
{
    //LocalTestStop();
    ClearData();
    QDateTime time =QDateTime::currentDateTime();
    SetTestTime(time);
    SetTestName(name);
    for(int i=0;i<device_num;i++)
    {
        device_vector.at(i)->UpdateActualStatus();
         qDebug()<<"终端使能状态"<<i+1<<":"<<device_vector.at(i)->actual_status;

    }

  if(LocalTestSyncTime())
       qDebug()<<"LocalTestSyncTime OK";
  else qDebug()<<"LocalTestSyncTime wrongxxxxxxxxxxxx";
   if(LocalTestIVModel())
       qDebug()<<"LocalTestIVModel OK";
   else qDebug()<<"LocalTestSyncTime wrongxxxxxxxxxxxx";
   if(LocalTestName())
        qDebug()<<"LocalTestName OK";
   else qDebug()<<"LocalTestName wrongxxxxxxxxxxxx";
   if(LocalTestStart())
       qDebug()<<"LocalTestStart OK";
   else qDebug()<<"LocalTestStart wrongxxxxxxxxxxxx";
   if(LocalDataUdpStart())
       qDebug()<<"LocalDataUdpStart OK";
   SendCanFilter();
}

void DeviceSystem::EndLocalTest()
{
    if(LocalTestStop())
        qDebug()<<"LocalTestStop OK";
    udp_data->unbindPort();
}

bool DeviceSystem::FindDocsNames(QDate begin, QDate end)
{
    Tcp_Data.clear();
    QString order = MongoFindDocsNames;
    Tcp_Data_list.clear();
    doc_name.cleardata();

    //order.append()
    tcp_client->sendMessage(order);
    tcp_client->waitForReadyRead(3000);
    if(Tcp_Data.isEmpty()) return false;
    else return true;
}
void DeviceSystem::ReceiveDocsName(const QByteArray &message)
{
    QList<QByteArray> list = message.split('\n');
    qDebug()<<"message ReceiveDocsName"<<QString::fromUtf8(message,message.size());
    for(auto itor = list.begin();itor<list.end();itor++)
    {
        if(itor->endsWith("OVER"))
        {
            emit UpdataDocsnames(doc_name.name_list, doc_name.time_list);
            qDebug()<<"emit UpdataDocsnames";
            return;
        }

            if(itor->startsWith(MongoFindDocsNames))
            {
                itor->remove(0,sizeof(MongoFindDocsNames));
                QList<QByteArray> itor_list = itor->split('/');
                QByteArray name=itor_list.first();
                doc_name.name_time_list.append(*itor);
                doc_name.name_list.append(QString::fromUtf8(name,name.size()));
                QDateTime datetime;
                if(itor_list.size()>1)
                {
                    datetime = QDateTime::fromString(itor_list.at(1),Qt::ISODate);
                }
                if(datetime.isValid())
                {
                    doc_name.time_list.append(itor_list.at(1));

                }
                else doc_name.time_list.append("时间错误");

                doc_name.datetime_list.append(datetime);

//                qDebug()<<" doc_name"<< doc_name.name_list.last();
//                qDebug()<<" doc_time"<< doc_name.time_list.last();
//                qDebug()<<" doc_name_time"<< doc_name.name_time_list.last();
            }

     }
}

bool DeviceSystem::FindDocs(int index)
{
    for(int i=0;i<device_num;i++)
    {
        device_vector.at(i)->ClearReceiveData();
    }
    if(doc_name.name_list.size()<index)
    {
        return false;
    }
    else
    {
        device_data.clear();
        SetTestName(doc_name.name_list.at(index));
        SetTestTime(doc_name.datetime_list.at(index));
        QString order;
        order.append("MongoFindDocs+test:");
        order.append(doc_name.name_time_list.at(index));
        qDebug()<<"FindDocs"<<order;
        Tcp_Data_list.clear();
        tcp_client->sendMessage(order);
        tcp_client->waitForReadyRead(3000);
        if(Tcp_Data.isEmpty()) return false;
        else return true;
    }
}

void DeviceSystem::sleep(int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//非阻塞
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}


void DeviceSystem::DocName::cleardata()
{
    this->name_list.clear();
    this->time_list.clear();
    this->name_time_list.clear();

}
/*datetime to 8byte
 * hight 4byte MMMM*256+256+MM*256+DD
 * low   4byte
 *
 */
QByteArray DeviceSystem::DatetimeToByte(QDateTime datetime)
{
    QTime time = datetime.time();
    QDate date = datetime.date();
    int yyyy_mm_dd = date.year()*256*256+date.month()*256+date.day();

    QByteArray datebyte = Uint32ToByte(static_cast<quint32>(yyyy_mm_dd));

    int msec=time.msecsSinceStartOfDay()*10;
    qDebug()<<"MESC________________________"<<msec;
    QByteArray timebyte = Uint32ToByte(static_cast<quint32> (msec));
    datebyte.append(timebyte);
    qDebug()<<"datetime"<<date.year()<<date.month()<<date.day()<<time.hour()<<time.minute()<<time.second();
    qDebug()<<"datebyte.toHex()"<<datebyte.toHex();
    return datebyte;
}

QDateTime DeviceSystem:: ByteToDatetime(QByteArray datebyte)
{
    qDebug()<<"ByteToDatetime"<<datebyte.toHex();
    QDate date(static_cast<quint8>(datebyte[2])+((static_cast<quint16>(datebyte[3]))*256),datebyte[1],datebyte[0]);
    QTime time_0(0,0,0);
    QByteArray timebyte = datebyte.mid(4,4);
    int a= ByteToInt32(timebyte);

    QTime time =time_0.addMSecs(a/10);
    qDebug()<<"ByteToDatetime"<<time.msecsSinceStartOfDay()<<time.toString(Qt::ISODate);

    QDateTime datetime(date,time,QTimeZone::systemTimeZone());

    return datetime;
}
QByteArray DeviceSystem:: IntToHighByte(quint32 i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[3] =  static_cast<char>  (0x000000ff & i);
    abyte0[2] =  static_cast<char> ((0x0000ff00 & i) >> 8);
    abyte0[1] =  static_cast<char> ((0x00ff0000 & i) >> 16);
    abyte0[0] =  static_cast<char> ((0xff000000 & i) >> 24);
    return abyte0;
}
QByteArray DeviceSystem:: Uint32ToByte(quint32 i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = static_cast<char> (0x000000ff & i);
    abyte0[1] = static_cast<char>((0x0000ff00 & i) >> 8);
    abyte0[2] = static_cast<char>((0x00ff0000 & i) >> 16);
    abyte0[3] = static_cast<char>((0xff000000 & i) >> 24);
    return abyte0;
}
QByteArray DeviceSystem:: uint16ToByte(quint16 i)
{
    QByteArray abyte0;
    abyte0.resize(2);
    abyte0[0] =  static_cast<char> (0x00ff & i);
    abyte0[1] =  static_cast<char> ((0xff00 & i) >> 8);
    return abyte0;
}

int DeviceSystem:: ByteToInt32(QByteArray abyte0)
{
    int data =0;

    for(int i=3;i>=0;i--)
   {
        data *=256;
        data += uchar(abyte0.at(i));
    }
    return data;
}
void  DeviceSystem:: SetFilterLength(int length)
{
    for(int i=0;i<device_num;i++)
    {
        for(int j=0;j<device_vector.at(i)->signal_number;j++)
        {
            device_vector.at(i)->signal_vector.at(j)->SetFilterLength(length);
        }
    }
}
void DeviceSystem::ClearCanFilter()
{
    for(int i=0;i<device_num;i++)
    {
        for(int j=0;j<2;j++)
        {
            device_vector.at(i)->can_vector.at(j)->filter_list.clear();
        }
    }
}