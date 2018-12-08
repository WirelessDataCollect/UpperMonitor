#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    heatbeattimer = new QTimer(this);

    ClientStatusOnlineAll.resize(15);
    ClientStatusOnline.resize(5);
    findLocalIPs();

    if (myudp == nullptr)
    {
        myudp = new MyUDP;
    }
    if (syncudp == nullptr)
    {
        syncudp = new MyUDP;
    }
     mytcpclient = new MyTCPClient;
     tcpClientTargetAddr.setAddress("115.159.154.160");
     tcpClientTargetPort = 8080;




    Adc_data.clear();
    Adc_data.resize(4);
    Adc_data[0].resize(4);
    Adc_data[1].resize(4);
    Adc_data[2].resize(4);
    Adc_data[3].resize(4);
    ClientStatusEnable.clear();
    ClientStatusEnable.resize(4);

    TotalByteNum = 0;
    TotalPackNum= 0;
    datawidget.resize(4);

    datawidget[0] = new showwidget();
    //datawidget[0] = new showwidget(this);
    QGridLayout *baseLayout1 = new QGridLayout(ui->Client1); //便于显示，创建网格布局
    baseLayout1->addWidget(datawidget[0], 0, 0,-1,-1);
    baseLayout1->setSpacing(0);
    baseLayout1->setMargin(0);


    datawidget[1] = new showwidget(this);
    QGridLayout *baseLayout2 = new QGridLayout(ui->Client2); //便于显示，创建网格布局
    baseLayout2->addWidget(datawidget[1], 0, 0,-1,-1);
    baseLayout2->setSpacing(0);
    baseLayout2->setMargin(0);

    datawidget[2] = new showwidget(this);
    QGridLayout *baseLayout3 = new QGridLayout(ui->Client3); //便于显示，创建网格布局

    baseLayout3->addWidget(datawidget[2], 0, 0,-1,-1);
    baseLayout3->setSpacing(0);
    baseLayout3->setMargin(0);
    baseLayout3->setContentsMargins(0,0,0,0);


    datawidget[3] = new showwidget(this);
    QGridLayout *baseLayout4 = new QGridLayout(ui->Client4); //便于显示，创建网格布局
    baseLayout4->addWidget(datawidget[3], 0, 0,-1,-1);
    baseLayout4->setSpacing(0);
    baseLayout4->setContentsMargins(0,0,0,0);


    //start myudp thread
    QThread *thread_txrx= new QThread(this);
    myudp->moveToThread(thread_txrx);

//    //start sync thread
    QThread *thread_sync = new QThread(this);
    syncudp->moveToThread(thread_sync);


    //syncTargetAddr
    syncTargetAddr = QHostAddress("255.255.255.255");

//    qDebug()<<"syncTargetAddr"<< syncTargetAddr;
    syncListenPort = 5003;
    syncTargetPort = 5003;

    udpListenPort = 5004;
    udpTargetPort = 5002;


    for(int i = 0;i<4;i++)
    connect(datawidget[i],SIGNAL(uisendIVmodle(QByteArray)),this, SLOT(sendIVmodle(QByteArray)));



    //tcp client

}

MainWindow::~MainWindow()
{
    delete ui;


}


/***********************************
 *
 * Find IP of local WiFi connections
 *
 ***********************************/
void MainWindow::findLocalIPs()
{
   // ui->comboBox_Interface->clear();
   interfaceList.clear();
   interfaceList = QNetworkInterface::allInterfaces();


    if (interfaceList.isEmpty())
    {
        // TODO wifilist is empty
    }
    else
    {
        for (int j = 0; j < interfaceList.size(); ++j)
        {
            ui->comboBox_Interface->addItem(interfaceList.at(j).humanReadableName());
        }
    }
}


void MainWindow::on_button_UdpSend_clicked()
{
     QString text = ui->lineEdit_UdpSend->text();

     QString senderIP = ui->lineEdit_UdpTargetIP->text();
     udpTargetPort = ui->lineEdit_UdpTargetPort->text().toUShort();
     qDebug()<<"udpTargetPort"<<udpTargetPort;
     if(text.isEmpty() || senderIP.isEmpty() || udpTargetPort==0 )
     {
         qDebug()<<"text.isEmpty() || senderIP.isEmpty()";
         return;
     }
     QByteArray data;
     data.append(text);
     QHostAddress IPadress(senderIP);
     emit udpsent(IPadress, udpTargetPort, data);
     onUdpAppendMessage("Me",text);
     ui->lineEdit_UdpSend->clear();
}

void MainWindow::on_button_UdpStart_clicked()
{
    qDebug()<<ui->button_UdpStart->text();
    if (ui->button_UdpStart->text()=="Start"){

        findLocalIPs();
        quint16 port = ui->lineEdit_UdpListenPort->text().toUShort();
        if(port) udpListenPort = port;

        ui->lineEdit_UdpListenPort->setText(QString::number(udpListenPort,10));


        // syncudp  bindport
        bool isSuccess = syncudp->bindPort(localAddr, syncListenPort);
        if(isSuccess)
        {
          ui->statusBar->showMessage(&"Listen to" [ syncListenPort],2);
          qDebug()<<"sync bindport ok.";
        }
        else{
             qDebug()<<"syncudp bindport error.";
             return;
        }

        // signal connect to slot
        connect(syncudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(syncrxmessage(QString,QByteArray)),Qt::QueuedConnection);


        connect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),syncudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)),Qt::DirectConnection);




        //IVseting button
        for(int i = 0;i<4;i++)
        connect(datawidget[i],SIGNAL(uisendIVmodle(QByteArray)),this, SLOT(sendIVmodle(QByteArray)));


         // set the target ip adress of clients
//         if(SendIpAdress(localAddr,udpListenPort) == false) {
//              qDebug()<< "SendIpAdress error";
//              initoff();

//             return;
//         }

         // time sync

        // Client start

         // timer begin(updata the ui)
         timer->start(1000);

         heatbeattimer->start(5000);
         heartbeat();
         connect(heatbeattimer, SIGNAL(timeout()), this, SLOT(heatbeatslot()));
         connect(timer, SIGNAL(timeout()), this, SLOT(UiDataShow()));

         ui->lineEdit_UdpListenPort->setDisabled(true);
         ui->button_UdpStart->setText("Stop");
         ui->label_clientnum->setText(QString::number(ClientCount));
    }
    else initoff();
}

void MainWindow::initoff(){
    timer->stop();
   // Client stop
   // stop();
    heatbeattimer->stop();
//    if(CH1SaveData.length()>10)
//    {
//
//        QString sFilePath="D:\\terx.txt";
//        QFile f(sFilePath);      //定义一个文件
//        f.open(QIODevice::WriteOnly);   //打开文件
//        QTextStream qs(&f);             //定义一个数据流
//        qs.setCodec("UTF-8");
//        for(int i=0;i<CH1SaveData.length();i++)
//        {
//           // qs <<CH1SaveData[i];      //把数组中的数据写到数据流，即写入文件中
//            qs<<QString::number(CH1SaveData.at(i),10)<<endl;
//        }

//        f.close();
//         qDebug()<<"CH1SaveData.at(0)"<<CH1SaveData.at(0);
//        CH1SaveData.clear();
//        CH1SaveData.resize(0);

//    }
  // myudp->unbindPort();
   syncudp->unbindPort();
   ui->button_UdpStart->setText("Start");
   ui->lineEdit_UdpListenPort->setDisabled(false);

   disconnect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),syncudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
  // disconnect(this, SIGNAL(myudpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
  // disconnect(myudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(AdcByteToData(QString,QByteArray)));
   disconnect(syncudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(syncrxmessage(QString,QByteArray)));
   for(int i=0; i<4;i++)
   disconnect(datawidget[i],SIGNAL(uisendIVmodle(QByteArray)),this, SLOT(sendIVmodle(QByteArray)));
   disconnect(timer, SIGNAL(timeout()), this, SLOT(UiDataShow()));
   disconnect(heatbeattimer, SIGNAL(timeout()), this, SLOT(heatbeatslot()));
   disconnect(timer, SIGNAL(timeout()), this, SLOT(UiDataShow()));
}

// local
void MainWindow::on_pushButton_local_clicked()
{
    //disable the tcp client
    mytcpclient->closeClient();


    bool isSuccess = myudp->bindPort(localAddr, udpListenPort);
    if(isSuccess)
    {
         ui->statusBar->showMessage(&"Listen to" [udpListenPort],2);
         qDebug()<<"udp_txrx bindport ok.";

         connect(myudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(AdcByteToData(QString,QByteArray)),Qt::QueuedConnection);
         connect(this, SIGNAL(myudpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)),Qt::DirectConnection);
         ui->pushButton_local->setDisabled(true);
         ui->pushButton_remote->setDisabled(false);
          QMessageBox::information(this,QStringLiteral("UDP连接成功"),QStringLiteral("局域网UDP连接成功"));
    }
    else{
        qDebug()<<"udp_txrx bindport error.";
          QMessageBox::warning(this,QStringLiteral("本地UDP连接失败"),QStringLiteral("失败"));
        return;
    }



}

void MainWindow::on_pushButton_remote_clicked()
{
    //disable the udp

    myudp->unbindPort();
    disconnect(myudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(AdcByteToData(QString,QByteArray)));
    disconnect(this, SIGNAL(myudpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
    ui->pushButton_local->setDisabled(false);


    //enable the tcp client
    connect(mytcpclient, SIGNAL(connectionFailed()), this, SLOT(onTcpClientTimeOut()));
    connect(mytcpclient, SIGNAL(myClientConnected(QString, quint16)), this, SLOT(onTcpClientNewConnection(QString, quint16)));
    mytcpclient->connectTo(tcpClientTargetAddr, tcpClientTargetPort);

}


//data receive (myudp)
void MainWindow::AdcByteToData(const QString &from, const QByteArray &message)
{

  qDebug()<<"message.size()"<<message.size();

  if(message.size()<16 || (message.size()%8!=0))
  {
      qDebug()<<"message.size()"<<message.size();
      return;
  }

  TotalPackNum ++;
  TotalByteNum += static_cast<quint64>(message.size()) ;
  QDateTime datatime = ByteToDatetime(message.left(8));
  quint32 count =  ByteTouint32(message.mid(8,4));


  char ChannelID = message.at(12);
 // qDebug()<<"count:"<<count;
 //  qDebug()<<"ChannelID:v "<<ChannelID;
  if(count%8 >0) return;
  if(ChannelID>4 || ChannelID<1) return;
  DigitalIO = message.mid(13,2);

  QByteArray adcbyte = message.mid(16,static_cast<int>(count));

  QVector<QVector<double> >::iterator iter = Adc_data[ChannelID-1].begin();

  for(int i=0;i<static_cast<int>(count);)
   {
       (*iter).append(ByteToAdcdata(adcbyte.mid(i,2)));
       CH1SaveData.append((quint16)(adcbyte.at(i)*16+adcbyte.at(i+1)/16));
       i+=2;
       iter++;
       (*iter).append(ByteToAdcdata(adcbyte.mid(i,2)));
       i+=2;
       iter++;
       (*iter).append(ByteToAdcdata(adcbyte.mid(i,2)));
       i+=2;
       iter++;
       (*iter).append(ByteToAdcdata(adcbyte.mid(i,2)));
       i+=2;
       iter-=3;
  }



}


void MainWindow::UiDataShow()
{
    QVector<double> data;
    for(int i =0; i<4; i++)
    {
       if(Adc_data[i][0].isEmpty());// ClientStatusEnable[i] = 0;
       else
       {
          // ClientStatusEnable[i] = 1;
           data.clear();
           for(int j= 0;j<4;j++)
            data.append(Adc_data[i][j].first());
            datawidget[i]->showdata(data,DigitalIO);
            datawidget[i]->showplot(Adc_data[i]);
       }

       Adc_data[i].clear();
       Adc_data[i].resize(4);
    }
}

void MainWindow::ClientStatusShow()
{
   if(ClientStatusOnline[0]==1)
   {
       ui->radioButton->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/checked-red.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-green.png);}"
                );
       ui->radioButton->setCheckable(true);
      if(ClientStatusEnable[0]) ui->radioButton->setChecked(true);
      else ui->radioButton->setChecked(false);

   }
   else{
        ui->radioButton->setChecked(false);
        ui->radioButton->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/unchecked.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-red.png);}"
                );
       ui->radioButton->setCheckable(false);
   }

   if(ClientStatusOnline[1]==1)
   {
       ui->radioButton_2->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/checked-red.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-green.png);}"
                );
        ui->radioButton_2->setCheckable(true);

   }
   else{
        ui->radioButton_2->setChecked(false);
       ui->radioButton_2->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/unchecked.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-red.png);}"
                );
       ui->radioButton_2->setCheckable(false);
   }
   if(ClientStatusOnline[2]==1)
   {
       ui->radioButton_3->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/checked-red.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-green.png);}"
                );
       ui->radioButton_3->setCheckable(true);
       if(ClientStatusEnable[2]) ui->radioButton->setChecked(true);
       else ui->radioButton->setChecked(false);

   }
   else{
        ui->radioButton_3->setChecked(false);
       ui->radioButton_3->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/unchecked.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-red.png);}"
                );
       ui->radioButton_3->setCheckable(false);

   }

   if(ClientStatusOnline[3]==1)
   {
       ui->radioButton_4->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/checked-red.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-green.png);}"
                );
        ui->radioButton_4->setCheckable(true);

   }
   else{
        ui->radioButton_4->setChecked(false);
       ui->radioButton_4->setStyleSheet(
                "QRadioButton::indicator::unchecked {image: url(:/ico/ico/unchecked.png);}"
                "QRadioButton::indicator::checked {image: url(:/ico/ico/checked-red.png);}"
                );
       ui->radioButton_4->setCheckable(false);
   }
}

bool MainWindow::checkreturn(char order,char channelnum)
{
      if(OrderReturn.isEmpty()) return false;
      for(int i=0;i<OrderReturn.count()-1;i++)
      {
          if(OrderReturn.at(i)==order && OrderReturn.at(i+1)==channelnum)
          {
              OrderReturn.remove(i,2);

              return true;
          }
      }
      return false;
}


QVector<int> MainWindow::checkreturn(char order)
{
     QVector<int> channel;
     channel.fill(0,5);
      for(int i=0;i<OrderReturn.count()-1;i++)
      {
          if(OrderReturn.at(i)==order &&OrderReturn.at(i+1)<5 &&OrderReturn.at(i+1)>=0)
          {
              channel[OrderReturn.at(i+1)-1]=1;
              OrderReturn.remove(i,2);
              i--;
          }
      }
      return channel;
}


void MainWindow::syncrxmessage(const QString &from, const QByteArray &message)
{
    QString localfrom = from;
    QString localmessage = message;

   if(static_cast<quint8>(message.at(0))== TIME_SYNC_BOARD)  //终端之间的时间同步
   {
     localmessage = "Time sync between boards";
   }


   else if(static_cast<quint8>(message.at(0)) == GET_RETURN_ORDER && (from != localAddr.toString()) )
   {

          OrderReturn.append(message.at(1));
          OrderReturn.append(message.at(2));

   }
   if(from == localAddr.toString()) localfrom = "SELF";
   onUdpAppendMessage(localfrom,message);
}



/***********************************
 *
 * UDP 测试连接
 *
 ***********************************/

void MainWindow::testconnect()
{
   //sync test
   QByteArray databyte;
   databyte.append(static_cast<char>(GET_TEST));
   emit udpsent(syncTargetAddr, syncTargetPort,databyte);
   emit myudpsent(syncTargetAddr,udpTargetPort,databyte);//某些客户端需要先发送数据才能接收
   QString text("testconnect");
   onUdpAppendMessage("Me",text);
}

/***********************************
 *
 * TCP client has a new connection
 *
 ***********************************/

void MainWindow::onTcpClientNewConnection(const QString &from, quint16 port)
{
    disconnect(mytcpclient, SIGNAL(myClientConnected(QString, quint16)), this, SLOT(onTcpClientNewConnection(QString, quint16)));
    disconnect(mytcpclient, SIGNAL(connectionFailed()), this, SLOT(onTcpClientTimeOut()));

    connect(mytcpclient, SIGNAL(myClientDisconnected()), this, SLOT(onTcpClientDisconnected()));
    ui->statusBar->showMessage("TCP Connected to " + from + ": " + QString::number(port), 2000);
    qDebug()<< "TCP Connected to " + from + ": " + QString::number(port);

    connect(mytcpclient, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    ui->pushButton_remote->setDisabled(true);
    QMessageBox::information(this,QStringLiteral("TCP连接成功"),"Remote Serve Ip Adress is "+from+ ":"+QString::number(port));
}



/***********************************
 *
 * TCP client connection time out
 *
 ***********************************/
void MainWindow::onTcpClientTimeOut()
{
    ui->statusBar->showMessage("TCP Connection time out", 2000);
    qDebug()<< "TCP Connection time out";
    disconnect(mytcpclient, SIGNAL(myClientConnected(QString, quint16)), this, SLOT(onTcpClientNewConnection(QString, quint16)));
    disconnect(mytcpclient, SIGNAL(connectionFailed()), this, SLOT(onTcpClientTimeOut()));
    mytcpclient->closeClient();
    ui->pushButton_remote->setDisabled(false);
    QMessageBox::warning(this,QStringLiteral("TCP连接超时"),"Remote Serve Ip Adress is "+tcpClientTargetAddr.toString()+ ":"+QString::number(tcpClientTargetPort));

}

/***********************************
 *
 * TCP client disconnected
 *
 ***********************************/
void MainWindow::onTcpClientDisconnected()
{
    ui->statusBar->showMessage("TCP Disconnected from server", 2000);
    disconnect(mytcpclient, SIGNAL(myClientDisconnected()), this, SLOT(onTcpClientDisconnected()));
    disconnect(mytcpclient, SIGNAL(newMessage(QString, QString)), this, SLOT(onTcpClientAppendMessage(QString, QString)));
    ui->pushButton_remote->setDisabled(false);
    QMessageBox::warning(this,QStringLiteral("断开tcp"),"Remote Serve Ip Adress is "+tcpClientTargetAddr.toString()+ ":"+QString::number(tcpClientTargetPort));

}

/***********************************
 *
 * TCP client newmessage
 *
 ***********************************/

void MainWindow::onTcpClientAppendMessage(const QString &from, const QByteArray &message)
{
    AdcByteToData(from, message);

}

void MainWindow::heatbeatslot()
{
    emit myudpsent(syncTargetAddr,udpTargetPort,"test");
    checkheartbeat();
    heartbeat();
    ClientStatusShow();
}

void MainWindow::heartbeat()
{
    QByteArray data;
    data[0] = static_cast<char>(GET_HEARTBEAT);
    QString text = "heartbeat: "+ data.toHex();
    onUdpAppendMessage("Me", text);
    emit udpsent(syncTargetAddr,syncTargetPort,data);

}
void MainWindow::checkheartbeat()
{
    QVector<int> channel = checkreturn(static_cast<char>(GET_HEARTBEAT));
    ClientStatusOnlineAll+=channel;
    ClientStatusOnlineAll.erase(ClientStatusOnlineAll.begin(),ClientStatusOnlineAll.begin()+5);
    for(int i=0;i<5;i++)
    {
        ClientStatusOnline[i]=(ClientStatusOnlineAll.at(i) | ClientStatusOnlineAll.at(i+5) | ClientStatusOnlineAll.at(i+10));

    }

}

//order  (syncudp)

bool MainWindow::start(char channelnum)
{
    QByteArray data;
    bool status=false;
    data.resize(2);
    data[0] = static_cast<char>(GET_WIFI_SEND_EN);
    data[1] = channelnum;
    QString text = "start: "+ data.toHex();
    int i=0;
    while(status==false &&i<5)
    {
       emit udpsent(syncTargetAddr,syncTargetPort,data);
       onUdpAppendMessage("Me", text);
       sleep(200);
       i++;
       status = checkreturn(static_cast<char>(GET_WIFI_SEND_EN), channelnum);
    }
    if(status)   onUdpAppendMessage("Me", QString("start is ok"));
    return status;

}
bool MainWindow::stop(char channelnum)
{

    QByteArray data;
     bool status=false;
    data.resize(1);
    data[0] = static_cast<char>(GET_WIFI_SEND_DISABLE);
    data[1] = channelnum;
    QString text = "stop: "+ data.toHex();
    int i=0;
    OrderReturn.clear();
    while(status==false && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,data);
       onUdpAppendMessage("Me", text);
       sleep(200);
       i++;
       status = checkreturn(static_cast<char>(GET_WIFI_SEND_DISABLE), channelnum);
    }
    if(status)   onUdpAppendMessage("Me", QString("stop is ok"));
    return status;
}

bool MainWindow::synctime()
{
    QByteArray databyte;
    QVector<int> channel;
    bool status = false;
    databyte.append(static_cast<char>(GET_TIME_SYNC));
    QDateTime datetime = QDateTime::currentDateTime();
    databyte.append(DatetimeToByte(datetime));
    int i=0;
    QString text = "synctime: "+ databyte.toHex();
    OrderReturn.clear();

      while(status==false && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,databyte);
       onUdpAppendMessage("Me",text);
       sleep(200);
       i++;
       status = (ClientStatusOnline==checkreturn(static_cast<char>(GET_TIME_SYNC)));

    }
    return status;

}


bool MainWindow::sendIVmodle(QByteArray databyte)
{
    QByteArray byte;
    bool status = false;
    byte.append(static_cast<char>(GET_CHANNEL_MODEL));

    showwidget *btn = qobject_cast<showwidget *>(sender());
   if(btn == datawidget[0]) byte.append(0x01);
   if(btn == datawidget[1]) byte.append(0x02);
   if(btn == datawidget[2]) byte.append(0x03);
   if(btn == datawidget[3]) byte.append(0x04);
   qDebug()<< byte.toHex();
    byte.append(databyte);
    int i = 0;
    QString text = "SendAdcModle: "+ byte.toHex();

    while(status==false && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,byte);
        onUdpAppendMessage("Me",text);
        sleep(200);
       i++;
       status = checkreturn(static_cast<char>(GET_CHANNEL_MODEL), byte.at(1));
    }
    return status;
}

bool MainWindow::SendIpAdress(QHostAddress ip, quint16 port)
{
    QByteArray databyte;
    bool status = false;
    databyte.append(static_cast<char>(GET_REMOTE_IP_PORT));

    quint32    ipv4sdress = ip.toIPv4Address();
    QByteArray ipv4adressByte =IntToHighByte(ipv4sdress);
    databyte.append(ipv4adressByte);
    QByteArray portByte = uint16ToByte(port);
    databyte.append(portByte);
    //   qDebug()<<"syncTargetAddr"<<ip;
    //   qDebug()<< "databyte.size()"<<databyte.size();
    //   qDebug()<<"databyte.toHex()"<< databyte.toHex();
    QString text = "SendIpAdress: "+ databyte.toHex();
    int i=0;
    while(status==false && i<5)
    {
        OrderReturn.clear();
        emit udpsent(syncTargetAddr,syncTargetPort,databyte);
        onUdpAppendMessage("Me",text);
        sleep(200);
        i++;
        status = (ClientStatusOnline==checkreturn(static_cast<char>(GET_TIME_SYNC)));
    }
    return status;
}

void MainWindow::onUdpAppendMessage(const QString &from, const QString &message)
{
    QTextCursor cursor(ui->textBrowser_UdpMessage->textCursor());
    cursor.movePosition(QTextCursor::End);
    if(from != "Me")
    {
        QTextTable *table = cursor.insertTable(1, 2, tableFormat);
        table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
        table->cellAt(0, 1).firstCursorPosition().insertText(message);
        }
    else
        {
        QTextTable *table = cursor.insertTable(1, 2, tableFormat);
        table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
        table->cellAt(0, 1).firstCursorPosition().insertText(message);
    }
    QScrollBar *bar = ui->textBrowser_UdpMessage->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void MainWindow::onUdpAppendMessage(const QString &from, const QByteArray &message)
{
 //  qDebug()<<"onUdpAppendMessage:  "<< message;
    QTextCursor cursor(ui->textBrowser_UdpMessage->textCursor());
    cursor.movePosition(QTextCursor::End);
    if(from != "Me")
    {

        QTextTable *table = cursor.insertTable(1, 2, tableFormat);
        table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
        table->cellAt(0, 1).firstCursorPosition().insertText(message.toHex());
        }
    else
        {
        QTextTable *table = cursor.insertTable(1, 2, tableFormat);
        table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
        table->cellAt(0, 1).firstCursorPosition().insertText(message.toHex());
    }
    QScrollBar *bar = ui->textBrowser_UdpMessage->verticalScrollBar();
    bar->setValue(bar->maximum());
}



QByteArray MainWindow::DatetimeToByte(QDateTime datetime)
{
    QTime time = datetime.time();
    QDate date = datetime.date();
    QByteArray datebyte;

    datebyte.append(static_cast<char>(date.year()&0x000000ff));
    datebyte.append(static_cast<char>((date.year()&0x0000ff00)>>8));
    datebyte.append(static_cast<char>(date.month()&0x000000ff));
    datebyte.append(static_cast<char>(date.day()&0x000000ff));

    int msec= (time.hour()*3600+time.minute()*60+time.second())*1000+time.msec();
    QByteArray timebyte = IntToByte(msec);
    datebyte.append(timebyte.data());
    qDebug()<<"datetime"<<date.year()<<date.month()<<date.day();
    qDebug()<<"datebyte.toHex()"<<datebyte.toHex();
    return datebyte;

}

QDateTime MainWindow:: ByteToDatetime(QByteArray datebyte)
{
    QDate date(datebyte[0] |(((quint16)datebyte[1])<<8),datebyte[2],datebyte[3]);
    QTime time(0,0,0);
    QByteArray timebyte = datebyte.right(4);
    time.addMSecs(ByteTouint32(timebyte));
    QDateTime datetime(date,time,QTimeZone::systemTimeZone());
    return datetime;
}

QByteArray MainWindow:: IntToByte(quint32 i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = static_cast<char> (0x000000ff & i);
    abyte0[1] = static_cast<char>((0x0000ff00 & i) >> 8);
    abyte0[2] = static_cast<char>((0x00ff0000 & i) >> 16);
    abyte0[3] = static_cast<char>((0xff000000 & i) >> 24);
    return abyte0;
}

QByteArray MainWindow:: IntToHighByte(quint32 i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[3] =  static_cast<char>  (0x000000ff & i);
    abyte0[2] =  static_cast<char> ((0x0000ff00 & i) >> 8);
    abyte0[1] =  static_cast<char> ((0x00ff0000 & i) >> 16);
    abyte0[0] =  static_cast<char> ((0xff000000 & i) >> 24);
    return abyte0;
}

QByteArray MainWindow:: uint16ToByte(quint16 i)
{
    QByteArray abyte0;
    abyte0.resize(2);
    abyte0[0] =  static_cast<char> (0x00ff & i);
    abyte0[1] =  static_cast<char> ((0xff00 & i) >> 8);
    return abyte0;
}


quint32 MainWindow:: ByteTouint32(QByteArray abyte0)
{
    quint32 data =0;
    for(int i=3;i>=0;i--)
    {
        data <<=8;
        data |= static_cast<quint32>(abyte0.at(i)) ;

    }
    return data;

}
quint16 MainWindow:: ByteTouint16(QByteArray abyte0)
{
    quint16 data =0;
    for(int i=1;i>=0;i--)
    {
        data <<=8;
        data |= abyte0.at(i);

    }
    return data;
}
double MainWindow:: ByteToAdcdata(QByteArray abyte0)
{

   return (((uchar)abyte0.at(0))*16 + ((uchar)abyte0.at(1))/16) *5.0/4096.0;
}



void MainWindow::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_comboBox_Interface_highlighted(int index)
{
    if (ui->comboBox_Interface->count() >= index)
    {
        ui->comboBox_Interface->setCurrentIndex(index);

        for (int i = 0; i < interfaceList.at(index).addressEntries().size(); ++i)
        {
            if (interfaceList.at(index).addressEntries().at(i).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ui->label_LocalIP->setText(interfaceList.at(index).addressEntries().at(i).ip().toString());
                localAddr = interfaceList.at(index).addressEntries().at(i).ip();

            }
        }
    }
    else if (ui->comboBox_Interface->count() > 0 && ui->comboBox_Interface->count() < index)
    {
        ui->comboBox_Interface->setCurrentIndex(0);
        for (int i = 0; i < interfaceList.at(0).addressEntries().size(); ++i)
        {
            if (interfaceList.at(0).addressEntries().at(i).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ui->label_LocalIP->setText(interfaceList.at(0).addressEntries().at(i).ip().toString());
                localAddr = interfaceList.at(index).addressEntries().at(i).ip();
            }
        }
    }

}




void MainWindow::on_radioButton_clicked(bool checked)
{
    qDebug()<<"on_radioButton_0_clicked"<<checked;
    if(checked)
    {

        if(start(1)) ClientStatusEnable[0]= 1;
        else  ClientStatusEnable[0]= 0;
        {

        }


    }
    else{
        if(stop(1)) ClientStatusEnable[0]= 0;
        else ClientStatusEnable[0]= 1;
    }


}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    qDebug()<<"on_radioButton_2_clicked"<<checked;
    if(checked)
    {

        if(start(2)) ClientStatusEnable[1]= 1;
        else  ClientStatusEnable[1]= 0;
        {

        }

    }
    else{
        if(stop(2)) ClientStatusEnable[1]= 0;
        else ClientStatusEnable[1]= 1;
    }
}



void MainWindow::on_radioButton_3_clicked(bool checked)
{
    qDebug()<<"on_radioButton_3_clicked"<<checked;
    if(checked)
    {

        if(start(3)) ClientStatusEnable[2]= 1;
        else  ClientStatusEnable[2]= 0;
        {

        }

    }
    else{
        if(stop(3)) ClientStatusEnable[2]= 0;
        else ClientStatusEnable[2]= 1;
    }
}



void MainWindow::on_radioButton_4_clicked(bool checked)
{
    qDebug()<<"on_radioButton_4_clicked"<<checked;
    if(checked)
    {

        if(start(4)) ClientStatusEnable[3]= 1;
        else  ClientStatusEnable[3]= 0;
        {

        }

    }
    else{
        if(stop(4)) ClientStatusEnable[3]= 0;
        else ClientStatusEnable[3]= 1;
    }

}
