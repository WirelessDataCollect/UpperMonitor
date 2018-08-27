#include "showwidget.h"

showwidget::showwidget(QWidget *parent) : QWidget(parent)
{

 QHBoxLayout * m_mainLayout = new QHBoxLayout();

 messageanalog = new QGroupBox();
 messagedigital = new QGroupBox();
 message = new QGroupBox();
 messageanalog->setTitle("Analog Data");
 messagedigital->setTitle("Digital Data");

 QGridLayout *mesageanalogLayout = new QGridLayout();
 QGridLayout *mesagedigitalLayout = new QGridLayout();
 modleset = new QPushButton("I/V");
 unit =  new QLabel(tr("单位"));

 data1 = new QLabel("0");
 data2 = new QLabel("0");
 data3 = new QLabel("0");
 data4 = new QLabel("0");

 ch1 = new QCheckBox("CH1");
 ch2 = new QCheckBox("CH2");
 ch3 = new QCheckBox("CH3");
 ch4 = new QCheckBox("CH4");

 messageanalog->setLayout(mesageanalogLayout);
 mesageanalogLayout->addWidget(modleset,0,0,1,1);
 mesageanalogLayout->addWidget(unit,0,1,1,1);

 mesageanalogLayout->addWidget(ch1,1,0,1,1);
 mesageanalogLayout->addWidget(ch2,2,0,1,1);
 mesageanalogLayout->addWidget(ch3,3,0,1,1);
 mesageanalogLayout->addWidget(ch4,4,0,1,1);

 mesageanalogLayout->addWidget(data1,1,1,1,1);
 mesageanalogLayout->addWidget(data2,2,1,1,1);
 mesageanalogLayout->addWidget(data3,3,1,1,1);
 mesageanalogLayout->addWidget(data4,4,1,1,1);


messagedigital->setLayout(mesagedigitalLayout);

QLabel *label_ch = new QLabel(tr("通道"));
QLabel *label_statusL = new QLabel("L");
QLabel *label_statusH = new QLabel("H");
QLabel *label_ch1 = new QLabel("CH1");
QLabel *label_ch2 = new QLabel("CH2");


ch1_status0 = new QRadioButton();
ch1_status1 = new QRadioButton();
ch2_status0 = new QRadioButton();
ch2_status1 = new QRadioButton();
QButtonGroup *ch1_Group = new QButtonGroup(this);
QButtonGroup *ch2_Group = new QButtonGroup(this);

ch1_Group->addButton(ch1_status0);
ch1_Group->addButton(ch1_status1);

ch2_Group->addButton(ch2_status0);
ch2_Group->addButton(ch2_status1);

mesagedigitalLayout->addWidget(label_ch,0,0,1,1);
mesagedigitalLayout->addWidget(label_statusL,0,1,1,1);
mesagedigitalLayout->addWidget(label_statusH,0,2,1,1);
mesagedigitalLayout->addWidget(label_ch1,1,0,1,1);
mesagedigitalLayout->addWidget(label_ch2,2,0,1,1);

mesagedigitalLayout->addWidget(ch1_status0,1,1,1,1);
mesagedigitalLayout->addWidget(ch1_status1,1,2,1,1);
mesagedigitalLayout->addWidget(ch2_status0,2,1,1,1);
mesagedigitalLayout->addWidget(ch2_status1,2,2,1,1);


//QWidget *datawidget = new QWidget(this);

//QWidget *plotwidget = new QWidget(this);

//datawidget->layout()->addWidget(messageanalog);
//datawidget->layout()->addWidget(messagedigital);


 QVBoxLayout *dataLayout = new QVBoxLayout;

 messageanalog->setFixedWidth(180);
  messageanalog->setFixedHeight(250);

 messagedigital->setFixedWidth(180);
 messagedigital->setFixedHeight(120);

 dataLayout->addWidget(messageanalog);
 dataLayout->addWidget(messagedigital);
 dataLayout->addWidget(message);
 plotwidget = new chartswidgt();

 m_mainLayout->addLayout(dataLayout);
 m_mainLayout->addWidget(plotwidget);
 m_mainLayout->setMargin(5);
 m_mainLayout->setSpacing(0);
 setLayout(m_mainLayout);

 connect(this->modleset,SIGNAL(clicked()),this, SLOT(IVmodleset()));

}

void showwidget::IVmodleset()
{
    QByteArray databyte;
    char hexzero = 0;
    if(ch1->isCheckable()) databyte.append(0x01);  //V
    else databyte.append(hexzero);

    if(ch2->isCheckable()) databyte.append(0x01);  //V
    else databyte.append(hexzero);

    if(ch3->isCheckable()) databyte.append(0x01);  //V
    else databyte.append(hexzero);

    if(ch4->isCheckable()) databyte.append(0x01);  //V
    else databyte.append(hexzero);
    emit uisendIVmodle(databyte);
    qDebug()<<"clicked";

}

void showwidget::showdata(QVector<double> &data, QByteArray &databyte)
{

  data1->setText(QString::number(data.at(0), 'g', 4));
  data2->setText(QString::number(data.at(1), 'g', 4));
  data3->setText(QString::number(data.at(2), 'g', 4));
  data4->setText(QString::number(data.at(3), 'g', 4));

  if(databyte.at(0)==1) ch1_status0->setChecked(true);
  else ch1_status1->setChecked(true);
  if(databyte.at(1)==1) ch2_status0->setChecked(true);
  else ch2_status1->setChecked(true);
}


void showwidget::showplot(QVector<double> &data)
{
    plotwidget->rxplotdata(data);
}
