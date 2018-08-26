#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    plottimer = new QTimer(this);


    findLocalIPs();

    if (myudp == nullptr)
    {
        myudp = new MyUDP;
    }
    if (syncudp == nullptr)
    {
        syncudp = new MyUDP;
    }
    if(dialog == nullptr)
    {
        dialog = new chartswidgt;
    }
    Adc_data.clear();
    Adc_data.resize(4);
    TotalByteNum = 0;
    TotalPackNum= 0;

    QGridLayout *baseLayout = new QGridLayout(ui->widchart); //便于显示，创建网格布局
    baseLayout->addWidget(dialog, 0, 0,-1,-1);
    baseLayout->setSpacing(0);
    baseLayout->setContentsMargins(0,0,0,0);
    dialog->show();

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

    udpListenPort = 5001;
    udpTargetPort = 5002;
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

    //获取主机名
    QString localHost = QHostInfo::localHostName();

    QHostInfo info = QHostInfo::fromName(localHost);

        info.addresses();//QHostInfo的address函数获取本机ip地址
        //如果存在多条ip地址ipv4和ipv6：
        foreach(QHostAddress address,info.addresses())
        {
            if(address.protocol()==QAbstractSocket::IPv4Protocol){//只取ipv4协议的地址
                qDebug()<<address.toString();
                localAddr= address;
                ui->label_LocalIP->setText(address.toString());
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

        // udp_txrx bindport
        bool isSuccess = myudp->bindPort(localAddr, udpListenPort);
        if(isSuccess)
        {
             ui->statusBar->showMessage(&"Listen to" [ udpListenPort],2);
            qDebug()<<"udp_txrx bindport ok.";
        }
        else{
            qDebug()<<"udp_txrx bindport error.";
            return;
        }

        // syncudp  bindport
        isSuccess = syncudp->bindPort(localAddr, syncListenPort);
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
        connect(myudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(AdcByteToData(QString,QByteArray)),Qt::QueuedConnection);

        connect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),syncudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)),Qt::DirectConnection);
        connect(this, SIGNAL(myudpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)),Qt::DirectConnection);
        //test the cninnection with client and count the number of count;

        connect(timer, SIGNAL(timeout()), this, SLOT(UiDataShow()));

        connect(this, SIGNAL(sendplotdata(QVector<double> &)),dialog, SLOT(rxplotdata(QVector<double> &)));
        connect(plottimer, SIGNAL(timeout()), this, SLOT(UiChartShow()));

        testconnect();
        sleep(500);
        ClientCount = checkreturn(GET_TEST);
        qDebug()<<"ClientCount"<<ClientCount;
        if(ClientCount ==0){
            QString  text("these is no client");
            onUdpAppendMessage("Me",text);
            initoff();
            return;
        }


         // set the target ip adress of clients
         if(SendIpAdress(localAddr,udpListenPort) == false) {
              qDebug()<< "SendIpAdress error";
              initoff();

             return;
         }

         // time sync
          if(synctime()==false) {
              qDebug()<< "synctime error";
              initoff();
             return;
          }
          else qDebug()<< "synctime OK";

         // set IVmodel
//         if(SendAdcModle() == false) {
//              qDebug()<< "SendIpAdress error";
//              initoff();
//             return;
//         }

        // Client start
         if(start()==false) {
             qDebug()<< "start() error";
             initoff();
           return;
          }
         // timer begin(updata the ui)
         timer->start(2000);
         plottimer->start(500);
         ui->lineEdit_UdpListenPort->setDisabled(true);
         ui->button_UdpStart->setText("Stop");
    }

    else initoff();
}

void MainWindow::initoff(){
    timer->stop();
    plottimer->stop();
   // Client stop
    stop();
   myudp->unbindPort();
   syncudp->unbindPort();
   ui->button_UdpStart->setText("Start");
   ui->lineEdit_UdpListenPort->setDisabled(false);

   disconnect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),syncudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
   disconnect(this, SIGNAL(myudpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
   disconnect(myudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(AdcByteToData(QString,QByteArray)));
   disconnect(syncudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(syncrxmessage(QString,QByteArray)));

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

  DigitalIO = message.mid(13,2);
  QByteArray adcbyte = message.mid(16,static_cast<int>(count));
  QVector<QVector<double> >::iterator iter=Adc_data.begin();

  for(int i=0;i<16;)
   {
       (*iter).append(ByteToAdcdata(adcbyte.mid(i,2)));
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
       iter=Adc_data.begin();
  }





//  iter=Adc_data.begin();
//  AdcDataShow((*iter).at(0), (*(iter+1)).at(0), (*(iter+2)).at(0), (*(iter+3)).at(0));
// DigitalDataShow(DigitalIO);
// Adc_data.clear();
// Adc_data.resize(4);

}


void MainWindow::UiDataShow()
{

     if(Adc_data[0].isEmpty()) return;
    QVector<QVector<double> >::iterator iter=Adc_data.begin();
    iter=Adc_data.begin();
    AdcDataShow((*iter).at(0), (*(iter+1)).at(0), (*(iter+2)).at(0), (*(iter+3)).at(0));
    DigitalDataShow(DigitalIO);
    qDebug()<< "(*iter).size()"<<(*iter).size();
    qDebug()<<"TotalByteNum"<< TotalByteNum;
    qDebug()<<"TotalPackNum"<< TotalPackNum;
    TotalByteNum = 0;
    TotalPackNum = 0;
    Adc_data.clear();
    Adc_data.resize(4);
}


void MainWindow::UiChartShow()
{
    /*
    //test
    static double i = 0;
     i++;
     if(i>5) i=0;
    qDebug()<<"rand number"<<i;
    Adc_data[0].append(i);
    Adc_data[1].append(i);
    Adc_data[2].append(i);
    Adc_data[3].append(i);
    //
    */
    if(Adc_data.at(0).isEmpty()) return;

    QVector<double> plotdata;
    plotdata.clear();
    for(int i = 0;i < 4;i++)
    {
      plotdata.append(Adc_data.at(i).back());
      qDebug()<<"Adc_data.at(i).back()"<<Adc_data.at(i).back();
    }

    emit sendplotdata(plotdata);
}


void MainWindow::AdcDataShow(double ch1, double ch2, double ch3, double ch4)
{
    ui->label_Channel1->setText(QString::number(ch1, 'g', 4));
    ui->label_Channel2->setText(QString::number(ch2, 'g', 4));
    ui->label_Channel3->setText(QString::number(ch3, 'g', 4));
    ui->label_Channel4->setText(QString::number(ch4, 'g', 4));
}

void MainWindow::DigitalDataShow(QByteArray bate0)
{
     qDebug()<< "DigitalDataShow"<<bate0.toHex();
    if(bate0.at(0) == 0)

    {
        ui->radioButton_1_0->setChecked(true);
        ui->radioButton_1_1->setChecked(false);
    }

    else
    {
        ui->radioButton_1_0->setChecked(false);
        ui->radioButton_1_1->setChecked(true);
    }
    if(bate0.at(1) == 0)

    {
        ui->radioButton_2_0->setChecked(true);
        ui->radioButton_2_1->setChecked(false);
    }

    else
    {
        ui->radioButton_2_0->setChecked(false);
        ui->radioButton_2_1->setChecked(true);
    }

}


int MainWindow::checkreturn(int order)
{

      return OrderReturn.count(static_cast<char>(order));
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
   }
   if(from == localAddr.toString()) localfrom = "SELF";

   onUdpAppendMessage(localfrom,message);
}

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
//order  (syncudp)
bool MainWindow::start()
{
    QByteArray data;
    data.resize(1);
    data[0] = static_cast<char>(GET_WIFI_SEND_EN);
    QString text = "start: "+ data.toHex();
    int i=0;
    while(checkreturn(GET_WIFI_SEND_EN) != ClientCount && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,data);
       onUdpAppendMessage("Me", text);
       sleep(200);
       i++;
    }
    return checkreturn(GET_WIFI_SEND_EN) == ClientCount;
}
bool MainWindow::stop()
{
    QByteArray data;
    data.resize(1);
    data[0] = static_cast<char>(GET_WIFI_SEND_DISABLE);
    QString text = "stop: "+ data.toHex();
    int i=0;
    while(checkreturn(GET_WIFI_SEND_DISABLE) != ClientCount && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,data);
       onUdpAppendMessage("Me", text);
       sleep(200);
       i++;
    }
    return checkreturn(GET_WIFI_SEND_DISABLE) == ClientCount;
}
bool MainWindow::synctime()
{
    QByteArray databyte;
    databyte.append(static_cast<char>(GET_TIME_SYNC));
    QDateTime datetime = QDateTime::currentDateTime();
    databyte.append(DatetimeToByte(datetime));
    int i=0;
    QString text = "synctime: "+ databyte.toHex();
    while(checkreturn(GET_TIME_SYNC) != ClientCount && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,databyte);
       onUdpAppendMessage("Me",text);
       sleep(200);
       i++;
    }

    return checkreturn(GET_TIME_SYNC) == ClientCount;

}
bool MainWindow::SendAdcModle()
{
    QByteArray databyte;
    char  hexzero = 0;
    databyte.append(static_cast<char>(GET_CHANNEL_MODEL));
    databyte.append(0x01);
    if(ui->checkBox->isChecked())   databyte.append(0x01);  //V
    else databyte.append(hexzero);                             //I
    if(ui->checkBox_2->isChecked())   databyte.append(0x01);  //V
    else databyte.append(hexzero);                             //I
    if(ui->checkBox_3->isChecked())   databyte.append(0x01);  //V
    else databyte.append(hexzero);                             //I
    if(ui->checkBox_4->isChecked())   databyte.append(0x01);  //V
    else databyte.append(hexzero);                             //I

    int i = 0;
    QString text = "SendAdcModle: "+ databyte.toHex();
    while(checkreturn(GET_CHANNEL_MODEL) != ClientCount && i<5)
    {
       OrderReturn.clear();
       emit udpsent(syncTargetAddr,syncTargetPort,databyte);
        onUdpAppendMessage("Me",text);
        sleep(200);
       i++;
    }
    return checkreturn(GET_CHANNEL_MODEL) == ClientCount;
}

bool MainWindow::SendIpAdress(QHostAddress ip, quint16 port)
{
   QByteArray databyte;
   databyte.append(static_cast<char>(GET_REMOTE_IP_PORT));

   quint32    ipv4sdress = ip.toIPv4Address();
   QByteArray ipv4adressByte =IntToHighByte(ipv4sdress);
   databyte.append(ipv4adressByte);
   QByteArray portByte = uint16ToByte(port);
   databyte.append(portByte);
//   qDebug()<<"syncTargetAddr"<<ip;
//   qDebug()<< "databyte.size()"<<databyte.size();
//   qDebug()<<"databyte.toHex()"<< databyte.toHex();

   int i = 0;
   QString text = "SendIpAdress: "+ databyte.toHex();
   while(checkreturn(GET_REMOTE_IP_PORT) != ClientCount && i<5)
   {
      OrderReturn.clear();
      emit udpsent(syncTargetAddr,syncTargetPort,databyte);
      onUdpAppendMessage("Me",text);
      sleep(2000);
      i++;
   }
   qDebug()<<"checkreturn(GET_TIME_SYNC)"<<checkreturn(GET_TIME_SYNC);
   return checkreturn(GET_REMOTE_IP_PORT) == ClientCount;
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
   qDebug()<<"onUdpAppendMessage:  "<< message;
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

void MainWindow::on_button_IVSetting_clicked()
{
    SendAdcModle();

}

void MainWindow::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

