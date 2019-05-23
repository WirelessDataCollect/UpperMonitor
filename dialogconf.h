#ifndef DIALOGCONF_H
#define DIALOGCONF_H

#include <QDialog>
#include <QAbstractButton>
#include "mytcpclient.h"
#include "devicesystem.h"
namespace Ui {
class DialogConf;
}

class DialogConf : public QDialog
{
    Q_OBJECT

public:
    DialogConf(DeviceSystem *system,QWidget *parent = nullptr);
    ~DialogConf();
    bool SetCmdValue(QString cmd, QString value);

private slots:

    void onTcpClientConnectFailed();
    void onTcpClientAppendMessage(const QString &from, const QByteArray &message);
    void onTcpClientConnected(const QString &from, const quint16 port);


    void on_pushButton_3_clicked();


    void on_buttonBox_2_accepted();

    void on_buttonBox_accepted();

    void on_pushButton_2_clicked();

private:
    Ui::DialogConf *ui;
    MyTCPClient *mytcpclient =nullptr;
    QByteArray return_message;
    void sleep(int msec);
    DeviceSystem *device_system = nullptr;


};

#endif // DIALOGCONF_H
