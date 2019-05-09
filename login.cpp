#pragma execution_character_set("utf-8")
#include<QNetworkInterface>
#include<QMessageBox>
#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    setWindowFlags(Qt::FramelessWindowHint); //去边框

    //q=new MainWindow(this);
    main_window = new MainWin();
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    m_IniFile = new QSettings("loginconfig.ini",QSettings::IniFormat);
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    loadcfg();
    find_ipadress();
    connect(main_window->device_system,SIGNAL(TcpConnectStatus(bool,QString)),this,SLOT(on_TcpConnectStatus(bool, QString)));
}

Login::~Login()
{
    delete ui;
    delete main_window;
}
void Login:: on_TcpConnectStatus(bool status, QString str)
{
    if(status)
    {
        savecfg();
        this->close();
        main_window->showMaximized();
    }
    else QMessageBox::warning(main_window,QStringLiteral("连接错误"),str);
}

void Login::on_pushButton_clicked()
{
    //远程登陆
    username = ui->lineEdit->text();
    passwd = ui->lineEdit_2->text();
    main_window->device_system->RemoteTcpStart(username,passwd);
    main_window->device_system->SetLocalTest(false);
}

void Login::on_pushButton_2_clicked()
{
    //本地
    main_window->showMaximized();
    main_window->device_system->LocalOrderUdpStart();
    main_window->device_system->SetLocalTest(true);

    username = ui->lineEdit->text();
    passwd = ui->lineEdit_2->text();
    main_window->device_system->RemoteTcpStart(username,passwd);
    this->close();
}

void Login::on_checkBox_clicked(bool checked)
{
    if(checked){
        remeberPasswd = true;
    }
    else{
        ui->lineEdit_2->clear();
        remeberPasswd = false;
    }
}

void Login::on_checkBox_2_clicked(bool checked)
{

    if(checked){
        autologin = true;
    }
    else{
        autologin = false;
    }
}

void Login::savecfg()
{
    m_IniFile->setValue("autologin",autologin);
    m_IniFile->setValue("remeberPasswd",remeberPasswd);
    if(remeberPasswd){
        m_IniFile->setValue("username",username);
        m_IniFile->setValue("passwd",passwd);
    }
    else{
        m_IniFile->setValue("username","用户名");
        m_IniFile->setValue("passwd","密码");
    }
}

void Login::loadcfg()
{
    autologin = m_IniFile->value("autologin").toBool();
    remeberPasswd = m_IniFile->value("remeberPasswd").toBool();
    username =m_IniFile->value("username").toString();
    passwd = m_IniFile->value("passwd").toString();
    if(username.isEmpty()==false)
    {
        ui->lineEdit->setText(username);
        ui->lineEdit_2->setText(passwd);

    }
    qDebug()<<"autologin"<<autologin<<remeberPasswd<<username<<passwd;
    if(remeberPasswd){
        ui->checkBox->setChecked(true);
    }
    else{
        ui->checkBox->setChecked(false);
    }
    if(autologin){
        ui->checkBox_2->setChecked(true);
    }
    else{
        ui->checkBox_2->setChecked(false);
    }
}

void Login::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragVector = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
void Login::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() && Qt::LeftButton)
    {
        move(event->globalPos() - dragVector);
        event->accept();
    }
}

void Login::on_more_clicked()
{
    DialogConf *dlg_conf = new DialogConf(main_window->device_system);
    dlg_conf->exec();
    delete dlg_conf;
}

void Login::on_minimum_clicked()
{
    showMinimized();
}

void Login::on_exit_clicked()
{
    this->close();
}
void Login::find_ipadress()
{
    // ui->comboBox->clear();
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

            ui->comboBox->addItem(interfaceList.at(j).humanReadableName());
        }
    }

}

void Login::on_comboBox_highlighted(int index)
{
    qDebug()<<index;
    if (ui->comboBox->count() >= index)
    {
        ui->comboBox->setCurrentIndex(index);

        for (int i = 0; i < interfaceList.at(index).addressEntries().size(); ++i)
        {
            if (interfaceList.at(index).addressEntries().at(i).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ui->label_LocalIP->setText("IP: "+interfaceList.at(index).addressEntries().at(i).ip().toString());
                localAddr = interfaceList.at(index).addressEntries().at(i).ip();
                main_window->device_system->local_addr  = localAddr;
            }
        }
    }
    else if (ui->comboBox->count() > 0 && ui->comboBox->count() < index)
    {
        ui->comboBox->setCurrentIndex(0);
        for (int i = 0; i < interfaceList.at(0).addressEntries().size(); ++i)
        {
            if (interfaceList.at(0).addressEntries().at(i).ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                ui->label_LocalIP->setText("IP: "+ interfaceList.at(0).addressEntries().at(i).ip().toString());
                localAddr = interfaceList.at(index).addressEntries().at(i).ip();
                main_window->device_system->local_addr  = localAddr;
            }
        }
    }

}



void Login::on_pushButton_3_clicked()
{
    QString dlgTitle="about消息框";
    QString strInfo="无线数据采集系统";

    QMessageBox::about(this, dlgTitle, strInfo);
}
