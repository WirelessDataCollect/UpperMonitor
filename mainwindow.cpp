#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    findLocalIPs();

    if (myudp == nullptr)
    {
        myudp = new MyUDP;
    }
    if (syncudp == nullptr)
    {
        syncudp = new MyUDP;
    }

    //start myudp thread
//    QThread *thread_txrx= new QThread(this);
//    myudp->moveToThread(thread_txrx);

    //start sync thread
//    QThread *thread_sync = new QThread(this);
//    syncudp->moveToThread(thread_sync);

    //

    syncTargetAddr = QHostAddress("255.255.255.255");
    qDebug()<<"syncTargetAddr"<< syncTargetAddr;
    syncListenPort = 8080;
    udpListenPort = 5051;


    syncTargetPort = 8080;
    udpTargetPort = 5051;
    connect(this, SIGNAL(bindPort(QHostAddress, qint16)), syncudp, SLOT(bindPort(QHostAddress, qint16)),Qt::DirectConnection);

    // synctime();
    // SendIpAdress(syncTargetAddr, udpListenPort);
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
     udpTargetPort = ui->lineEdit_UdpTargetPort->text().toInt();
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
        quint16 port = ui->lineEdit_UdpListenPort->text().toInt();
        if(port) udpListenPort = port;
        ui->lineEdit_UdpListenPort->setText(QString::number(udpListenPort,10));
        ui->lineEdit_UdpListenPort->setDisabled(true);
        ui->button_UdpStart->setText("Stop");
        // udp_txrx bindport
        connect(this, SIGNAL(bindPort(QHostAddress, qint16)), myudp, SLOT(bindPort(QHostAddress, qint16)),Qt::DirectConnection);
        emit bindPort(localAddr,udpListenPort);
        disconnect(this, SIGNAL(bindPort(QHostAddress, qint16)), myudp, SLOT(bindPort(QHostAddress, qint16)));
//        bool isSuccess = myudp->bindPort(localAddr, udpListenPort);
//        if(isSuccess)
//        {
//          ui->statusBar->showMessage("Listen to" + udpListenPort);
//           qDebug()<<"udp_txrx bindport ok.";
//        }
//        else{
//          qDebug()<<"udp_txrx bindport error.";
//        }

        connect(this, SIGNAL(bindPort(QHostAddress, qint16)), syncudp, SLOT(bindPort(QHostAddress, qint16)),Qt::DirectConnection);
        emit bindPort(localAddr,syncListenPort);
        disconnect(this, SIGNAL(bindPort(QHostAddress, qint16)), syncudp, SLOT(bindPort(QHostAddress, qint16)));

        // syncudp  bindport
//        isSuccess = syncudp->bindPort(localAddr, syncListenPort);
//        if(isSuccess)
//        {
//          ui->statusBar->showMessage("Listen to" + syncListenPort);
//          qDebug()<<"sync bindport ok.";

//        }
//        else{
//             qDebug()<<"syncudp bindport error.";
//        }

        // signal connect to slot
        connect(this, SIGNAL(udpsent(QString,quint16, QByteArray)),syncudp, SLOT(sendMessage(QString,quint16, QByteArray)),Qt::DirectConnection);
        connect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),syncudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)),Qt::DirectConnection);
       connect(syncudp, SIGNAL(newMessage(QString,QByteArray)),this,SLOT(onUdpAppendMessage(QString,QByteArray)), Qt::DirectConnection);
      // connect(myudp, SIGNAL(newMessage(QString,QString)),this,SLOT(onUdpAppendMessage(QString,QString)),Qt::DirectConnection);
        // time sync
        synctime();
        SendIpAdress(localAddr,udpListenPort);
        // Client start
        start();
    }
    else{
       // Client stop
        stop();

        ui->button_UdpStart->setText("Start");
        ui->lineEdit_UdpListenPort->setDisabled(false);

        disconnect(this, SIGNAL(udpsent(QHostAddress,quint16, QByteArray)),myudp, SLOT(sendMessage(QHostAddress,quint16, QByteArray)));
        disconnect(syncudp, SIGNAL(newMessage(QString,QString)),this,SLOT(onUdpAppendMessage(QString,QString)) );
    }
}


void MainWindow::start()
{
    QByteArray data;
    data.resize(1);
    data[0] = (uchar)GET_WIFI_SEND_EN;
    emit udpsent(syncTargetAddr.toString(),syncTargetPort,data);
    QString text = "start";
    onUdpAppendMessage("Me", text);

}
void MainWindow::stop()
{
    QByteArray data;
    data.resize(1);
    data[0] = (uchar)GET_WIFI_SEND_DISABLE;
    emit udpsent(syncTargetAddr,syncTargetPort,data);
    QString text = "stop";
    onUdpAppendMessage("Me",text );

}
void MainWindow::synctime()
{
    QByteArray databyte;
    databyte.append((uchar)GET_TIME_SYNC);
    QDateTime datetime = QDateTime::currentDateTime();
    databyte.append(DatetimeToByte(datetime));
    emit udpsent(syncTargetAddr,syncTargetPort,databyte);
    qDebug()<<databyte.size();
    qDebug()<<databyte.toHex();
    QString text = " synctime: "+databyte.toHex();
     onUdpAppendMessage("Me",text);
}

void MainWindow::SendIpAdress(QHostAddress ip, quint16 port)
{
   QByteArray databyte;
   databyte.append((uchar)GET_REMOTE_IP_PORT);

   QByteArray ipv4adressByte = IntToByte(ip.toIPv4Address());

   databyte.append(ipv4adressByte);
   QByteArray portByte = uint16ToByte(port);
   databyte.append(portByte);
   emit udpsent(syncTargetAddr,syncTargetPort,databyte);
   qDebug()<<"syncTargetAddr"<<ip;
   qDebug()<< "databyte.size()"<<databyte.size();
   qDebug()<<"databyte.toHex()"<< databyte.toHex();
   onUdpAppendMessage("Me"," SendIpAdress: "+databyte.toHex());
}

void MainWindow::onUdpAppendMessage(const QString &from, const QString &message)
{
   qDebug()<<"onUdpAppendMessage:  "<< message;
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

    datebyte.append((uchar)(date.year()&0x000000ff));
    datebyte.append((uchar)(date.year()&0x0000ff00));
    datebyte.append((uchar)(date.month()&0x000000ff));
    datebyte.append((uchar)(date.day()&0x000000ff));

    quint32 msec= (time.hour()*3600+time.minute()*60+time.second())*1000+time.msec();
    QByteArray timebyte = IntToByte(msec);
    datebyte.append(timebyte.data());

    return datebyte;

}

QByteArray MainWindow:: IntToByte(quint32 i)
{
    QByteArray abyte0;
    abyte0.resize(4);
    abyte0[0] = (uchar)  (0x000000ff & i);
    abyte0[1] = (uchar) ((0x0000ff00 & i) >> 8);
    abyte0[2] = (uchar) ((0x00ff0000 & i) >> 16);
    abyte0[3] = (uchar) ((0xff000000 & i) >> 24);
    return abyte0;
}
QByteArray MainWindow:: uint16ToByte(quint16 i)
{
    QByteArray abyte0;
    abyte0.resize(2);
    abyte0[0] = (uchar)  (0x00ff & i);
    abyte0[1] = (uchar) ((0xff00 & i) >> 8);
    return abyte0;
}
