#ifndef DIALOGCONF_H
#define DIALOGCONF_H

#include <QDialog>
#include <QAbstractButton>
#include "mytcpclient.h"
namespace Ui {
class DialogConf;
}

class DialogConf : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConf(QWidget *parent = nullptr);
    ~DialogConf();
    bool SetCmdValue(QString cmd, QString value);

private slots:

    void onTcpClientConnectFailed();
    void onTcpClientAppendMessage(const QString &from, const QByteArray &message);
    void onTcpClientConnected(const QString &from, const quint16 port);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


private:
    Ui::DialogConf *ui;
    MyTCPClient *mytcpclient =nullptr;
    QByteArray return_message;
    void sleep(int msec);


};

#endif // DIALOGCONF_H
