﻿#pragma execution_character_set("utf-8")
#include<QCoreApplication>
#include<QMessageBox>
#include<QTimer>
#include<QTimeZone>
#include<QDebug>
#include "devicesystem.h"
#include<QThread>
#include<QFile>
#include"md5.h"
#include"signaldata.h"

DeviceSystem::DeviceSystem()
{
    device_num = 5;

    for(int i=0;i<device_num;i++)
    {
        Device *device = new Device();
        device->device_id = i;
        for(int j=0;j<device->signal_number;j++) device->signal_vector.at(j)->device_id = i;
        for(int j=0;j<2;j++) device->can_vector.at(j)->device_id = i;
        device_vector.append(device);
    }
    udp_order = new MyUDP();
    udp_data  = new MyUDP();


    //tcp ip and port
    tcp_client = new MyTCPClient();

    tcp_target_addr.setAddress("114.55.104.50");
    //  tcp_target_addr.setAddress("192.168.3.2");
    tcp_target_port = 8089;

    //local udp
    data_local_port = 5014;
    data_target_port= 5002;

    order_target_addr = QHostAddress("255.255.255.255");
    order_local_port = 5003;
    order_target_port= 5003;
    device_all_status.fill(0,18);
    clock_device_status = false;

    heart_beat_timer = new QTimer();
    LocalThread();
    tcp_message_flag = 0;
    test_name = "no_test";
    //show_speed_timer = new QTimer();
    //connect(show_speed_timer,SIGNAL(timeout()),this,SLOT(ShowSpeed()));
    //->start(1000);
    auto_stop = new QTimer();
    connect(auto_stop,SIGNAL(timeout()),this,SLOT(LocalTestStop()));
    is_receive_data = false;
}

void DeviceSystem::LocalThread()
{
    QThread *udp_order_thread = new QThread();
    udp_order->moveToThread(udp_order_thread);
    udp_order_thread->start();

    //    QThread *udp_data_thread = new QThread();
    //    udp_data->moveToThread(udp_data_thread);
    //    udp_data_thread->start();
//     QThread *tcp_client_thread = new QThread();
//     tcp_client->moveToThread(tcp_client_thread);
//     tcp_client_thread->start();
}

DeviceSystem::~DeviceSystem()
{
    QString order("Disconnect");
    QString value;
    bool status = TcpSendCheck(order,value);
    qDebug()<<"TcpSendCheck Disconnect Status"<<status;
    tcp_client->disconnectCurrentConnection();
    tcp_client->closeClient();
    //  delete  udp_order;
    if(is_local_test)
    {
        LocalTestStop();
    }
    heart_beat_timer->stop();
    delete  heart_beat_timer;
    udp_data->unbindPort();
    delete  udp_data;
    udp_order->unbindPort();
    device_vector.clear();
    for(int i=0;i<device_vector.size();i++)
    {
        delete device_vector[i];
    }
}

void DeviceSystem::RemoteTcpStart(QString username,QString passwd)
{
    bool status;
    qDebug()<<"RemoteTcpStart start";
    this->username = username;
    this->passwd = passwd;
    tcp_client->disconnectCurrentConnection();
    tcp_client->closeClient();

    disconnect(tcp_client, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    disconnect(tcp_client,SIGNAL(myClientConnected(QString,quint16)), this,SLOT(onTcpClientConnected(QString,quint16)));
    disconnect(tcp_client,SIGNAL(connectionFailed()), this,SLOT(onTcpConnectFailed()));
    connect(tcp_client, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    connect(tcp_client,SIGNAL(myClientConnected(QString,quint16)), this,SLOT(onTcpClientConnected(QString,quint16)));
    Tcp_Data.clear();
    tcp_message_flag =0;
    status = tcp_client->connectTo(tcp_target_addr, tcp_target_port);
    qDebug()<<"tcp_client STATUS"<<status;

    if(!status) emit TcpConnectStatus(false, "无法连接远程服务器,请检查网络或服务器状态");
    else{
         FindDocsNames(QDate::currentDate(),QDate::currentDate());
    }
}

void DeviceSystem::onTcpClientConnected(const QString &from, const quint16 port)
{
    connect(tcp_client,SIGNAL(connectionFailed()), this,SLOT(onTcpConnectFailed()));
    qDebug()<< tcp_client->waitForReadyRead(1000);
    sleep(100);
    qDebug()<< "onTcpClientConnected"<<Tcp_Data;

    if(!Tcp_Data.isEmpty())
    {
        QByteArray radom_array =  Tcp_Data.remove(0,8);
        radom_array.remove(radom_array.size()-1,1);
        qDebug()<< "onTcpClientConnected radom_array"<<radom_array;
        RemoteTcpLogin(radom_array);
    }

    else
    {
        emit TcpConnectStatus(false, "链接正常，无法接收随机数验证消息,请检查服务器服务");
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
        emit TcpConnectStatus(false, "密码错误，请重新输入密码");
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
    if(message.isEmpty()) return;
    Tcp_Data= message;
    //qDebug()<<"tcp_message_flag"<<tcp_message_flag;
   // qDebug()<<"\n"<<"onTcpClientAppendMessage"<<message<<"\n";
    if(tcp_message_flag ==0 && message.startsWith("MongoFindDocsNames:"))
    {
        Tcp_Data_list.clear();
        tcp_message_flag = 1;
    }
    if(tcp_message_flag ==0 && message.startsWith("MongoFindDocs:"))
    {
        Tcp_Data_list.clear();
        device_data.clear();
        tcp_message_flag =2;
        tcp_data_number = 0;
        tcp_package_number = 0;
        tcp_time =0;
    }

    if(tcp_message_flag ==0 && message.startsWith(ReceiveConfigure))
    {
        Tcp_Data_list.clear();
        tcp_message_flag = 3;

    }
    if(tcp_message_flag == 1)
    {
        Tcp_Data_list.append(message);
        if(Tcp_Data_list.endsWith("OVER\n"))
        {
            ReceiveDocsName(Tcp_Data_list);
            tcp_message_flag =0;
        }
    }
    if(tcp_message_flag == 2)
    {
        device_data.append(message);
        tcp_data_number += message.size();
        tcp_package_number++;
        is_receive_data = true;
        if(device_data.endsWith("OVER\n"))
        {
            tcp_message_flag=0;
            is_receive_data = false;
            qDebug()<<"TCP DATA OVERxxxxxxxxxxxxxx\n";

        }
        ReciveDeviceData();
        qDebug()<<"/n/n";

    }
    if(tcp_message_flag == 3)
    {
        Tcp_Data_list.append(message);

        if(Tcp_Data_list.endsWith("OVER\n"))
        {
            qDebug()<<"\n\ntcp_message_flag = = 3--------------------------";
            qDebug()<<Tcp_Data_list.data();
            ReceiveConfigureFile(Tcp_Data_list);
            tcp_message_flag=0;

        }
    }
}

void DeviceSystem::ShowSpeed()
{
    if(tcp_message_flag!=2) return;
    static int data_number = 0;
    static int package_number = 0;
    tcp_time++;
    qDebug()<<"tcp_speed----------------------------";
    qDebug()<<"tcp_data_number/second"<<tcp_data_number-data_number;
    qDebug()<<"tcp_package_number/second"<<tcp_package_number-package_number;
    qDebug()<<"All Time"<< tcp_time;
    qDebug()<<"tcp_data average speed(KB)"<<tcp_data_number/tcp_time/1024;
    data_number = tcp_data_number;
    package_number = tcp_package_number;
}
bool DeviceSystem::LocalOrderUdpStart()
{
    bool is_success = udp_order->bindPort(local_addr,order_local_port);
    if(is_success)
    {
        connect(udp_order,SIGNAL(newMessage(QString,QByteArray)),this, SLOT(onUdpOrderMessage(QString,QByteArray)));
        for(int i =0;i<3;i++)
        {
            UdpHeartBeat();
            sleep(50);
        }
        LocalTestStop();
        heart_beat_timer->start(1000);
        connect(heart_beat_timer, SIGNAL(timeout()), this, SLOT(UdpHeartBeat()));
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
    int size =  message.size();
    if(size<48) return;
    int frame_time = ByteToInt32(message.mid(4,4))- Device::test_headtime;
    test_deep_time = frame_time/10000;
    SetTestDeep(test_deep_time);
    int node_id = int(message.at(12));
    if(node_id>0 &&node_id<=5) device_vector.at(node_id-1)->AddData(message);
}

void DeviceSystem::ReciveDeviceData()
{

    if(device_data.size()<static_cast<int>(sizeof(MongoFindDocs))+16+64) return;
    qDebug()<<device_data.left(sizeof(MongoFindDocs)+16);
    if(device_data.startsWith(MongoFindDocs) && device_data.at(sizeof(MongoFindDocs)+4) == device_data.at(sizeof(MongoFindDocs)+15))
    {
        int count = ByteToInt32(device_data.mid(static_cast<int>(sizeof(MongoFindDocs))+8,4));
        //qDebug()<<"COUNT"<<count<<device_data.mid(static_cast<int>(sizeof(MongoFindDocs)),4)<<device_data.mid(static_cast<int>(sizeof(MongoFindDocs))+4,4)<<device_data.mid(static_cast<int>(sizeof(MongoFindDocs))+8,4)<< device_data.left(40);
        if(device_data.size()>=static_cast<int>(sizeof(MongoFindDocs))+16+64+count)
        {
            int node_id = int(device_data.at(static_cast<int>(sizeof(MongoFindDocs)+12)));

            QByteArray fram_array =  device_data.mid(static_cast<int>(sizeof(MongoFindDocs)),count+64+16);
            int frame_time = ByteToInt32(fram_array.mid(4,4))- Device::test_headtime;
            if(frame_time/10000>test_deep_time){
                test_deep_time = frame_time/10000;
                SetTestDeep(test_deep_time);
            }
            if(node_id>0 &&node_id<=5) device_vector.at(node_id-1)->AddData(fram_array);
            qDebug()<<device_data.left(sizeof(MongoFindDocs));
            device_data.remove(0,static_cast<int>(sizeof(MongoFindDocs))+16+64+count);
        }
        else return;
    }
    else
    {

        device_data.remove(0,1);
        qDebug()<<"ERROR remove(0,1)";
    }

    ReciveDeviceData();
}

bool DeviceSystem::TcpSendCheck(QString order, QString value)
{
    Tcp_Data.clear();

    if(value.isEmpty()) tcp_client->sendMessage(order+'\t');
    else tcp_client->sendMessage(order+"+"+value+'\t');
    tcp_client->waitForReadyRead(1000);
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
    bool status = false;
    if(udp_order_return.isEmpty()) return false;
    for(int i=0;i<udp_order_return.count()-1;)
    {
        if(udp_order_return.at(i)==order && udp_order_return.at(i+1)==channelnum)
        {
            udp_order_return.remove(i,2);
            status = true;
        }
        else i=i+2;
    }
    return status;
}

QVector<bool> DeviceSystem::checkreturn(char order)
{
    QVector<bool> channel;
    channel.fill(0,6);
    if(udp_order_return.isEmpty()) return channel;
    for(int i=0;i<udp_order_return.count()-1;i=i+2)
    {
        if(udp_order_return.at(i)==order &&udp_order_return.at(i+1)<=5 &&udp_order_return.at(i+1)>=0)
        {
            channel[udp_order_return.at(i+1)]=1;
            udp_order_return.remove(i,2);
            i=i-2;
        }
    }
    return channel;
}

bool DeviceSystem::UdpSendCheck(QByteArray order, QByteArray value)
{

    QVector<bool> channel;
    channel.fill(0,6);
    QVector<bool> channel_tmp;
    channel_tmp.fill(0,6);

    QByteArray send_data;
    send_data.append(order);
    send_data.append(value);
    udp_order->sendMessage(order_target_addr,order_target_port,send_data);
    udp_order->waitForReadyRead(100);

    for(int i = 0;i<10;i++)
    {
        sleep(50);
        if(value.isEmpty()) //广播
        {
            channel_tmp = checkreturn(order.at(0));
            for(int i=0;i<6;i++)
            {
                channel[i] =  channel[i] || channel_tmp[i];
            }
            if(channel.mid(1,5) == device_all_status.mid(1,5))
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
    device_all_status.erase(device_all_status.begin(),device_all_status.begin()+6);
    for(int i=0;i<device_num+1;i++)
    {
        device_all_status[i]=(device_all_status.at(i) | device_all_status.at(i+6) | device_all_status.at(i+12));

    }
    clock_device_status = device_all_status.at(0);
    for(int i=0;i<device_num;i++)
    {
        device_vector.at(i)->online_status =  device_all_status[i+1];
        device_vector.at(i)->UpdateActualStatus();
        qDebug()<<"终端状态"<<i+1<<"------>"<<device_vector.at(i)->online_status;
    }

    QByteArray send_data;
    send_data.append(GET_HEARTBEAT);
    QString text = "heartbeat: "+ send_data.toHex();
    udp_order->sendMessage(order_target_addr,order_target_port,send_data);
    udp_data->sendMessage(order_target_addr,5000,send_data);
}

bool DeviceSystem::LocalTestStart()
{
    is_receive_data = true;
    QByteArray order;
    QByteArray value;
    order.append(GET_WIFI_SEND_EN);
    bool is_success = false;
    char adc_status = 0;
    char can_status = 0;
    for(char i=0;i<device_num;i++)
    {
        if(device_vector.at(i)->actual_status)
        {
            value.clear();
            value.append(i+1);
            if(device_vector.at(i)->can_vector.at(0)->show_enable) can_status+=1;
            if(device_vector.at(i)->can_vector.at(1)->show_enable) can_status+=2;
            value.append(can_status);
            for(int j=0;j<6;j++)
            {
                if(device_vector.at(i)->signal_vector.at(j)->signal_data->show_enable)
                {
                    adc_status = 1;
                    break;
                }
            }
            value.append(adc_status);
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
    is_receive_data = false;
    udp_order_return.clear();
    auto_stop->stop();
    QByteArray order;
    QByteArray value;
    order.append(GET_WIFI_SEND_DISABLE);
    bool is_success = false;
    for(char i=0;i<device_num;i++)
    {
        if(!device_vector.at(i)->online_status) continue;
        value.clear();
        value.append(i+1);
        int j=0;
        for(j=0;j<3;j++)
        {
            is_success=UdpSendCheck(order,value);
            if(is_success) break;
        }
        qDebug()<<"twice"<<j<<"LocalTestStop"<<"device"<<i+1<<is_success;
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
                sleep(100);
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
    int id;
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
                    qDebug()<<"SendCanFilter";
                }

                for(int k=0;k<3;k++)
                {

                    is_success=UdpSendCheck(order,value);
                    if(is_success) break;
                    sleep(100);
                }
                //qDebug()<<"decive:"<<int(i+1)<<"Channel"<<int(j+1)<<"id"<<id<<filter_size<<value.toHex()<< is_success;
                if(!is_success)
                {

                    return false;
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

void DeviceSystem::SetTestNameTime(QString name,QDateTime test_time)
{
    emit UpdataTestName(name);
    test_name = name;
    test_name.append('/');
    test_name.append(test_time.toString(Qt::ISODate));
    this->test_time = test_time;
    Device::test_headtime = test_time.time().msecsSinceStartOfDay()*10;
    emit UpdataTestTime(test_time.toString(Qt::ISODate));
}

void DeviceSystem::SetTestDeep(double time)
{
    emit UpdataTestDeep(QString::number(time,'f',3));
}

void DeviceSystem::ClearData()
{
    for(int i =0;i<device_num;i++)
    {
        device_vector.at(i)->ClearReceiveData();
    }
    test_deep_time = 0;
    SetTestDeep(test_deep_time);
}
void DeviceSystem::SetMaxDataLen(int len)
{
    for(int i =0;i<device_num;i++)
    {
        device_vector.at(i)->SetMaxDataLen(len);
    }
    test_deep_time = 0;
    SetTestDeep(test_deep_time);
}

void DeviceSystem::NewLocalTest(QString name)
{
    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxx";
    //LocalTestStop();
    ClearData();
    emit SaveConfigureFile();
    QDateTime time =QDateTime::currentDateTime();
    SetTestNameTime(name,time);

    qDebug()<<"cccccccccccccccccccccccccccccccccccccccc";
    for(int i=0;i<device_num;i++)
    {
        device_vector.at(i)->UpdateActualStatus();
    }
    TestConfigureShow();

    qDebug()<<"send meaasge---------------";
    if(LocalDataUdpStart())
        qDebug()<<"LocalDataUdpStart OK";

    if(SendCanFilter())
        qDebug()<<"SendCanFilter OK";
    else qDebug()<<"SendCanFilter wrongxxxxxxxxxxxx";

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

    if(SendConfigureFile(test_name))
        qDebug()<<"SendConfigureFile OK";
    else qDebug()<<"SendConfigureFile wrongxxxxxxxxxxxx";


}

void DeviceSystem::EndLocalTest()
{
    if(LocalTestStop())
        qDebug()<<"LocalTestStop OK";
    udp_data->unbindPort();
    disconnect(udp_data,SIGNAL(newMessage(QString,QByteArray)),this, SLOT(onUdpDataMessage(QString,QByteArray)));
}

bool DeviceSystem::FindDocsNames(QDate begin, QDate end)
{
    qDebug()<<"FindDocsNames";

    end = end.addDays(1);
    Tcp_Data.clear();
    QString order = MongoFindDocsNames;
    order.append("+isodate:");
    order.append(begin.toString(Qt::ISODate));
    order.append(',');
    order.append(end.toString(Qt::ISODate));

    order.append('\t');
    Tcp_Data_list.clear();
    doc_name.cleardata();

    tcp_client->sendMessage(order);
    tcp_client->waitForReadyRead(100);
    if(Tcp_Data.isEmpty()) return false;
    else return true;
}

bool DeviceSystem::GetRtData(bool status)
{
    QString order;
    QString value;
    if(status)
    {
        //start realtime data
       order = ReceiveRtdata;
       //get configure file
       if(doc_name.name_time_list.size()==0) return false;
       FindConfigureFile(doc_name.name_time_list.last());
       value.append(doc_name.name_time_list.last());
       //qDebug()<<"XXXXXXXXXXXXXXXXXXXXXX"<<value;
    }
    else
    {
        //stop realtime data
        order = StopReceiveRtdata;
    }
     //get rt data
    bool rt_status = TcpSendCheck(order,value);
    return rt_status;
}

bool DeviceSystem::SendConfigureFile(QString test_name)
{
    QString order = SendConfigure;
    QString value(test_name);
    value.append(";");
    qDebug()<<"sendconfigurefile name"<<test_name;

    QFile file("configure.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "WriteTable Error: cannot open file";
        return false;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString filetext = in.readAll();
    qDebug()<<"send configure begin   size:"<<filetext.size();
    value +=QString::number(filetext.size());
    value +=";";
    value+=filetext;

    for(int i=0;i<2;i++)
    {
        if( TcpSendCheck(order,value))
            return true;
    }
    return false;
}
bool DeviceSystem::FindConfigureFile(QString test_name)
{

    Tcp_Data.clear();
    QString order = ReceiveConfigure;
    order.append("+");
    order.append(test_name);
    order.append('\t');
    qDebug()<<"FindConfigureFile order"<<order;
    tcp_client->sendMessage(order);
    tcp_client->waitForReadyRead(1000);
    if(Tcp_Data.isEmpty())
    {
        qDebug()<<"FindConfigureFile no return ";
        return false;
    }
    else return true;
}

bool DeviceSystem::ReceiveConfigureFile(QByteArray Tcp_Data_list)
{
    qDebug()<<"file BEGIN____________________";
    QFile file("configure.txt");
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "WriteTable Error: cannot open file";
        return false;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<Tcp_Data_list;
    out.flush();
    file.close();
    emit LoadConfigureFile();
    return true;
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
        }
    }
}

bool DeviceSystem::FindDocs(int index)
{
    qDebug()<<"finddocs begin"<<"tcp_message_flag"<<tcp_message_flag<<doc_name.name_list.size();

    if(tcp_message_flag !=0) RemoteTcpReset();
    ClearData();
    if(doc_name.name_list.size()<index)
    {
        return false;
    }
    qDebug()<<"finddocs begin name"<<doc_name.name_list.at(index);

    device_data.clear();
    SetTestNameTime(doc_name.name_list.at(index),doc_name.datetime_list.at(index));
    FindConfigureFile(doc_name.name_time_list.at(index));
    QString order;
    order.append("MongoFindDocs+test:");
    order.append(doc_name.name_time_list.at(index));
    order.append('\t');
    qDebug()<<"FindDocs------------------"<<order;

    tcp_client->sendMessage(order);
    tcp_client->waitForReadyRead(100);
    TestConfigureShow();
    if(Tcp_Data.isEmpty()) return false;
    else return true;
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
    this->datetime_list.clear();
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
    //qDebug()<<"MESC________________________"<<msec;
    QByteArray timebyte = Uint32ToByte(static_cast<quint32> (msec));
    datebyte.append(timebyte);
    // qDebug()<<"datetime"<<date.year()<<date.month()<<date.day()<<time.hour()<<time.minute()<<time.second();
    //  qDebug()<<"datebyte.toHex()"<<datebyte.toHex();
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
    //  qDebug()<<"ByteToDatetime"<<time.msecsSinceStartOfDay()<<time.toString(Qt::ISODate);

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
void DeviceSystem:: SetFilterLengthMax(int length,double max)
{
    for(int i=0;i<device_num;i++)
    {
        for(int j=0;j<device_vector.at(i)->signal_number;j++)
        {
            device_vector.at(i)->signal_vector.at(j)->signal_data->SetFilterLengthMax(length, max);
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

bool DeviceSystem::SaveDataFile(QString file_name)
{
    if(file_name.isEmpty()) file_name.append(test_name).append("_data.txt");

    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "WriteTable Error: cannot open file";
        return false;
    }
    qDebug()<<"SaveDataFile";
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<"Test Data File \n";
    out<<"Save Time: "<<QDateTime::currentDateTime().toString(Qt::ISODate)<<"\n";
    out<<"Test Time: "<<test_time.toString(Qt::ISODate)<<"\n";
    out<<"Frenquence: 1ms \n";
    out<<"\n";

    QString str;

    QVector<int> length_vector;
    SignalData *signaldata;

    for(int i=0;i<device_num;i++)
    {
        out<<"Device"<< i+1<<" data start ---------------------------------------\n";
        for(int k=0;k<6;k++)
        {
            signaldata = device_vector.at(i)->signal_vector.at(k)->signal_data;
            out<<"Signal data start-----------------------------------------------\n";
            out<<"Device, Channel, Length:\n";
            out<<i+1<<",    "<<k+1<<",    "<<signaldata->val_list.size()<<"\n";
            out<<"Time(s),    Value\n";
            for(int j=0;j<signaldata->val_list.size();j++)
            {
                out<<  signaldata->time_list.at(j)<<",    "<<signaldata->val_list.at(j)<<"\n";
                //  qDebug()<<signaldata->time_list.at(j)<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxx";

            }
            out<<"Signal data end-----------------------------------------------\n";
            out<<"\n";
        }
        for(int k =0;k<2;k++)
        {
            for(int j = 0;j<device_vector.at(i)->can_vector.at(k)->filter_list.size();j++)
            {
                signaldata = device_vector.at(i)->can_vector.at(k)->filter_list.at(j);
                out<<"CAN data start-----------------------------------------------\n";
                out<<"Device,    Channel,    ID(hex),    Length\n";
                out<<i+1<<",    "<<k+1<<",    "<<QString::number(signaldata->id,16)<<",     "<<signaldata->message_list.size()<<"\n";

                for(int m =0;m<signaldata->message_list.size();m++)
                {
                    out<<signaldata->time_list.at(m)<<",    ";
                    out<<signaldata->message_list.at(m).toHex();                     out<<"\n";
                }
                out<<"Can data end-----------------------------------------------\n";
                out<<"\n";
            }
        }
        out<<"Device"<< i+1<<" data end ---------------------------------------\n";
        out<<"\n";
    }
    return true;
}
bool DeviceSystem::LoadDataFile(QString file_name)
{
    if(file_name.isEmpty()) file_name= "configure.txt";

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "LoadDataFile Error: cannot open file";
        return false;
    }

    qDebug() << "LoadDataFile";
    QStringList fFileContent;
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        QString str = in.readLine();
        fFileContent.append(str);
    }
    QString linetext;
    QStringList linetextlist;
    int device, channel,length;
    double time;
    int val;
    int id;
    bool ok;
    QByteArray data;
    for(int i=0;i<fFileContent.count();i++)
    {
        linetext = fFileContent.at(i);
        if(linetext.contains("Signal data start"))
        {
            i+=2;
            linetext = fFileContent.at(i);
            linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
            device = linetextlist.at(0).toInt();
            channel = linetextlist.at(1).toInt();
            length =  linetextlist.at(2).toInt();

            qDebug()<<"Signal data start";
            qDebug()<<"device:"<<device<<"channel"<<channel<<"length"<<length;

            for(int j = 0;j< length; j++)
            {
                i++;
                linetext = fFileContent.at(i);
                linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
                time= linetextlist.at(0).toDouble();
                val = linetextlist.at(1).toInt();
                device_vector.at(device-1)->signal_vector.at(channel-1)->signal_data->AddData(time,val);
            }
        }
        if(linetext.contains("CAN data start"))
        {

            i+=2;
            linetext = fFileContent.at(i);
            linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
            device = linetextlist.at(0).toInt();
            channel = linetextlist.at(1).toInt();
            id = linetextlist.at(2).toInt(&ok,16);
            qDebug()<<"Can data read start";
            length =  linetextlist.at(3).toInt();
            qDebug()<<"device:"<<device<<"channel:"<<channel<<"id:"<<id<<"length:"<<length;
            for(int j = 0; j<length;j++)
            {
                i++;
                linetext = fFileContent.at(i);
                linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
                time= linetextlist.at(0).toDouble();
                data.clear();
                for(int k=0;k<8;k++)
                {
                    char c = char(linetextlist.at(1).mid(k*2,2).toInt(&ok,16));
                    if(ok) data.append(c);
                }
                device_vector.at(device-1)->can_vector.at(channel-1)->AddFrameData(id,time,data);
            }
        }
    }
    return true;
}

void DeviceSystem::AutoStop(int time)
{
    if(time>0) auto_stop->start(time);
}
void DeviceSystem::ShowCanData(bool status)
{
    for(int i=0;i<device_num;i++)
    {
        device_vector.at(i)->ShowCanData(status);
    }
}
void DeviceSystem::SetLocalTest(bool status)
{
    is_local_test = status;
}
void DeviceSystem::RemoteTcpReset()
{
    QString order("Disconnect");
    QString value;
    bool status = TcpSendCheck(order,value);
    qDebug()<<"Disconnect--------------------";

    RemoteTcpStart(username,passwd);
}
void DeviceSystem::StopSendDocs()
{
    QString order;
    order.append("StopSendDocs");

    order.append('\t');
    qDebug()<<"FindDocs"<<order;

    tcp_client->sendMessage(order);

    qDebug()<<"StopSendDocs------------------------";
}
void DeviceSystem::TestConfigureShow()
{
    QString str;
    QStringList name_list = test_name.split('/');
    str.append(QString("实验名称:   "));
    str.append(name_list.at(0));
    str.append("\n");

    str.append(QString("实验时间:   "));
    str.append(name_list.at(1));
    str.append("\n");
    str.append(QString("实验内容(Siganl):\n"));
    for(int device=0;device<device_num;device++)
    {
        for(int signal=0;signal<device_vector.at(device)->signal_number;signal++)
            if(device_vector.at(device)->signal_vector.at(signal)->signal_data->show_enable)
            {
                str.append(device_vector.at(device)->signal_vector.at(signal)->signal_data->name);
                str.append("\n");
            }
    }
    str.append("\n");
    str.append(QString("实验内容(CAN):\n"));
    for(int device=0;device<device_num;device++)
    {
        for(int channel=0;channel<2;channel++)
        {
            for(int i=0;i< device_vector.at(device)->can_vector.at(channel)->filter_list.size();i++)
            {
                if(device_vector.at(device)->can_vector.at(channel)->filter_list.at(i)->show_enable)
                     str.append(device_vector.at(device)->can_vector.at(channel)->filter_list.at(i)->name);
                str.append("\n");
            }
        }
    }
    emit testconfigureshow(str);
}
