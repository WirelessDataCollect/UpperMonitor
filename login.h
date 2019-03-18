#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QSettings>
#include"md5.h"
#include"mainwin.h"
#include"dialogconf.h"


namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
signals:
    void closeall();

private slots:
    void on_pushButton_clicked();


    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_more_clicked();

    void on_minimum_clicked();

    void on_exit_clicked();
    void on_comboBox_highlighted(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_TcpConnectStatus(bool status, QString str);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragVector;
    Ui::Login *ui;
    //MainWindow *q = nullptr;
    MainWin *qq= nullptr;
    QSettings *m_IniFile = nullptr;
    QString		username;
    QString		passwd;
    QString		AutoLogin;
    QByteArray MessageDigest;
    bool		remeberPasswd;
    bool		autologin;
    QList<QNetworkInterface> interfaceList;
    QHostAddress localAddr;

    void		savecfg();
    void		loadcfg();
    void find_ipadress();

};

#endif // LOGIN_H
