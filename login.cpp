#pragma execution_character_set("utf-8")
#include<QNetworkInterface>
#include<QMessageBox>
#include "login.h"
#include "ui_login.h"
#include"mainwin.h"
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    main_window = new MainWin();
    //main_window = (MainWin*) parentWidget();

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    setWindowModality(Qt::WindowModal);
    m_IniFile = new QSettings("loginconfig.ini",QSettings::IniFormat);
    ui->setupUi(this);
    ui->comboBox->setEditable(false);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    loadcfg();
    find_ipadress();

    connect(main_window->device_system,SIGNAL(TcpConnectStatus(bool,QString)),this,SLOT(on_TcpConnectStatus(bool, QString)));
}

Login::~Login()
{
    delete ui;
    delete main_window;
    qDebug()<<"~Login-----------------";
}

void Login:: on_TcpConnectStatus(bool status, QString str)
{
    if(status)
    {
        if(!main_window->isMaximized())
        {
            main_window->showMaximized();
        }
        savecfg();
        this->close();
    }
    else
    {
        this->show();
        if( !main_window->device_system->is_local_test) main_window->close();
        QMessageBox::warning(this, QStringLiteral("警告"),str);
    }
}

void Login::on_pushButton_clicked()
{
    //远程登陆
    username = ui->lineEdit->text();
    passwd = ui->lineEdit_2->text();
     main_window->device_system->SetLocalTest(false);
    main_window->device_system->RemoteTcpStart(username,passwd);
}

void Login::on_pushButton_2_clicked()
{
    //本地
    username = ui->lineEdit->text();
    passwd = ui->lineEdit_2->text();
    main_window->showMaximized();
    main_window->device_system->SetLocalTest(true);
    main_window->device_system->LocalOrderUdpStart();
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
    if(event->button() == Qt::RightButton)
    {
        dragVector = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    QWidget::mousePressEvent(event);
}
void Login::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        move(event->globalPos() - dragVector);
        event->accept();
    }
    QWidget::mouseMoveEvent(event);
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

    interfaceList.clear();
    interfaceList = QNetworkInterface::allInterfaces();
    int size = interfaceList.size();
    if (interfaceList.isEmpty())
    {
        // TODO wifilist is empty
        return;
    }
    while(ui->comboBox->count()>size)
    {
        ui->comboBox->removeItem(ui->comboBox->count()-1);
    }
    while(ui->comboBox->count()<size)
    {
        ui->comboBox->addItem("");
    }

    for (int j = 0; j < size; ++j)
    {
        if( ui->comboBox->itemText(j)!=interfaceList.at(j).humanReadableName()){
            ui->comboBox->setItemText(j,interfaceList.at(j).humanReadableName());
        }
    }
}


void Login::on_comboBox_highlighted(int index)
{
    find_ipadress();
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
    QString dlgTitle="关于";
    QString strInfo="无线数据采集系统";
    QMessageBox::about(this, dlgTitle, strInfo);
}
