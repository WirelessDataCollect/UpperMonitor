#pragma execution_character_set("utf-8")
#include "dialogconf.h"
#include "ui_dialogconf.h"
#include<QPushButton>
#include<QMessageBox>
#include<QTime>
#include<QTimer>
#include<QHostAddress>
DialogConf::DialogConf(DeviceSystem *system,QWidget *parent) :
    QDialog(parent),

    ui(new Ui::DialogConf)
{
    this->device_system = system;
    ui->setupUi(this);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);

    ui->comboBox->setEnabled(false);

    mytcpclient = new MyTCPClient();
    connect(mytcpclient, SIGNAL(connectionFailed()), this, SLOT(onTcpClientConnectFailed()));
    //
    connect(mytcpclient, SIGNAL(newMessage(QString, QByteArray)), this, SLOT(onTcpClientAppendMessage(QString, QByteArray)));
    connect(mytcpclient, SIGNAL(myClientConnected(QString, quint16)), this, SLOT(onTcpClientConnected(QString, quint16)));
    ui->lineEdit_4->setText(device_system->local_addr.toString());
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setText(QString::number(device_system->order_local_port));
    ui->lineEdit_6->setText(QString::number(device_system->data_local_port));

    ui->lineEdit_7->setText(device_system->tcp_target_addr.toString());
    ui->lineEdit_8->setText(QString::number(device_system->tcp_target_port));
}

DialogConf::~DialogConf()
{
    delete ui;
    delete mytcpclient;
}
void DialogConf::onTcpClientConnectFailed()
{
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->pushButton_3->setEnabled(true);

    QMessageBox::warning(this, QStringLiteral("警告"), "连接失败，请将本机WiFi连接至热点SORL_WIRELESS_NODE_X");
}

void DialogConf::onTcpClientAppendMessage(const QString &from, const QByteArray &message)
{

    return_message = message;
}


bool  DialogConf::SetCmdValue(QString cmd, QString value)
{
    QString text;
    if(value.isEmpty()) text = cmd;
    else text = cmd + " "+ value;
    QByteArray  data = text.toUtf8();
    data.append("\r\n");
    return_message.clear();
    mytcpclient->sendMessage(data);
    qDebug()<<"data"<<data.data();
    qDebug()<<"start------------------"<<QTime::currentTime();
    mytcpclient->waitForReadyRead(2000);
    sleep(2500);
    if(return_message == data) return  true;

    else return false;
}

void DialogConf::sleep(int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//非阻塞
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}

void DialogConf::on_pushButton_3_clicked()
{
    //连接采集终端
    QHostAddress tcpClientTargetAddr("192.168.100.1");
    quint16 tcpClientTargetPort = 5001;
    mytcpclient->connectTo(tcpClientTargetAddr, tcpClientTargetPort);
}

void DialogConf::onTcpClientConnected(const QString &from, const quint16 port)
{
    ui->lineEdit->setEnabled(true);
    ui->lineEdit_2->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->pushButton_3->setEnabled(false);

    qDebug()<<"onTcpClientConnected";
}


void DialogConf::on_buttonBox_2_accepted()
{


    int port;
    bool ok;
    port = ui->lineEdit_5->text().toInt(&ok,10);
    if(ok) device_system->order_local_port = quint16(port);
    else {
        ui->lineEdit_5->setText(QString::number(device_system->order_local_port));
        QMessageBox::warning(this,"警告","port错误");
        return;
    }
    port = ui->lineEdit_6->text().toInt(&ok,10);
    if(ok) device_system->data_local_port = quint16(port);
    else
    {
        ui->lineEdit_6->setText(QString::number(device_system->data_local_port));
        QMessageBox::warning(this,"警告","port错误");
        return;
    }
    QHostAddress tcp_target_addr;
    ok = tcp_target_addr.setAddress(ui->lineEdit_7->text());
    if(ok) device_system->tcp_target_addr = tcp_target_addr;
    else
    {
        ui->lineEdit_7->setText(device_system->tcp_target_addr.toString());
        QMessageBox::warning(this,"警告","地址错误");
        return;
    }
    port = ui->lineEdit_8->text().toInt(&ok,10);
    if(ok) device_system->tcp_target_port = quint16(port);
    else
    {
        ui->lineEdit_8->setText(QString::number(device_system->tcp_target_port));
        QMessageBox::warning(this,"警告","port错误");
        return;
    }
    accept();
}

void DialogConf::on_buttonBox_accepted()
{
    QString ssid_name = ui->lineEdit->text();
    QString ssid_pwd = ui->lineEdit_2->text();


    QString device_id = ui->comboBox->currentText();
    if(ssid_name.isEmpty() || ssid_pwd.isEmpty() || device_id.isEmpty()){
        QMessageBox::warning(this,"警告","输入密码和名称");
        return;
    }
    if(SetCmdValue("SET_NODE_ID",device_id)==true && SetCmdValue("SET_RSI_JOIN_SSID",ssid_name)==true && SetCmdValue("SET_RSI_PSK",ssid_pwd)==true)
    {
        if(SetCmdValue("SAVE_ALL_PARA",""))
        {
            sleep(100);
            if(SetCmdValue("RESET_SYSTEM",""))
            {
                QMessageBox::warning(this,"设置成功","系统即将重启");
                accept();
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"失败","重新保存");
        mytcpclient->closeClient();
        ui->pushButton_3->setEnabled(true);

        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->comboBox->setEnabled(false);
    }
    //SetCmdValue("SET_PWD")
    qDebug()<<"ssid_name"<<ssid_name<<"ssid_pwd"<<ssid_pwd<<"device_id"<<device_id;
}


void DialogConf::on_pushButton_2_clicked()
{
    //主机
}
