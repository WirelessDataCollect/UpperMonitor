#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include<QLabel>
#include<QCheckBox>
#include<QMessageBox>
#include<QRadioButton>
#include<QFormLayout>
#include<QGroupBox>
#include<QButtonGroup>
#include<QVector>
#include<QDebug>
#include"chartswidgt.h"

class showwidget : public QWidget
{
    Q_OBJECT
public:
    explicit showwidget(QWidget *parent = nullptr);

signals:
    void uisendIVmodle(QByteArray databyte);
    void sendsignal(QByteArray &a, QString b);
public slots:
    void IVmodleset(void);
    void showdata(QVector<double> &data, QByteArray &databyte);
    void showplot(QVector<double> &data);

private:

public:
    QPushButton *modleset = nullptr;
    QLabel *unit = nullptr;
    QLabel *data1 = nullptr;
    QLabel *data2 = nullptr;
    QLabel *data3 = nullptr;
    QLabel *data4 = nullptr;
    QCheckBox *ch1 = nullptr;
    QCheckBox *ch2= nullptr;
    QCheckBox *ch3= nullptr;
    QCheckBox *ch4= nullptr;

    QRadioButton *ch1_status0 = nullptr;
    QRadioButton *ch1_status1 = nullptr;
    QRadioButton *ch2_status0 = nullptr;
    QRadioButton *ch2_status1 = nullptr;
    chartswidgt *plotwidget = nullptr;

    QGroupBox *messageanalog = nullptr;
    QGroupBox *messagedigital = nullptr;
    QGroupBox *message = nullptr;



};

#endif // SHOWWIDGET_H
