/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *Client1;
    QWidget *Client2;
    QWidget *Client3;
    QWidget *Client4;
    QWidget *tab;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_12;
    QTextBrowser *textBrowser_UdpMessage;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *lineEdit_UdpTargetIP;
    QFrame *line_2;
    QLabel *label_4;
    QLineEdit *lineEdit_UdpTargetPort;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lineEdit_UdpSend;
    QFrame *line_8;
    QPushButton *button_UdpSend;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *Listen;
    QLineEdit *lineEdit_UdpListenPort;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_local;
    QPushButton *pushButton_remote;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_Interface;
    QLabel *label_LocalIP;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLabel *label_clientnum;
    QPushButton *button_UdpStart;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 757);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget#centerWidget {\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"\n"
"QWidget#widchart {\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"QMessageBox{\n"
" background: rgb(50, 50, 50);\n"
"}\n"
"/*\n"
"QFrame{\n"
"        border: 1px solid rgb(50, 50, 50);\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"*/\n"
"QLabel {\n"
"        border-radius: 4px;\n"
"        border: none;\n"
"        width: 35px;\n"
"        height:25px;\n"
"        color: white;\n"
"        \n"
"       background: rgb(60, 60, 60);\n"
"}\n"
"\n"
"Line{\n"
"\n"
"background: white;\n"
"}\n"
"\n"
"\n"
"\n"
"/**********\346\214\211\351\222\256**********/\n"
"QPushButton{\n"
"        border-radius: 4px;\n"
"        border: none;\n"
"        width: 50px;\n"
"        height: 25px;\n"
"}\n"
"QPushButton:enabled {\n"
"        background: rgb(68, 69, 73);\n"
"        color: white;\n"
"}\n"
"QPushButton:!enabled {\n"
"        background: rgb(100, 100, 100);\n"
"        color: rgb(200, 200, 200);\n"
"}\n"
"QPushButton:enabled:hover{\n"
""
                        "        background: rgb(85, 85, 85);\n"
"}\n"
"QPushButton:enabled:pressed{\n"
"        background: rgb(80, 80, 80);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"/**********\345\215\225\351\200\211\346\241\206**********/\n"
"QRadioButton{\n"
"        spacing: 0px;\n"
"       /* font-size:12px*/\n"
"}\n"
"QRadioButton:enabled{\n"
"        color: rgb(175, 175, 175);\n"
"    /* color: rgb(0, 0, 0)*/\n"
"}\n"
"QRadioButton:enabled:hover{\n"
"        color: rgb(200, 200, 200);\n"
"       \n"
"}\n"
"QRadioButton:!enabled{\n"
"        color: rgb(155, 155, 155);\n"
"}\n"
"QRadioButton::indicator {\n"
"\n"
"        width: 58px;\n"
"        height: 20px;\n"
"\n"
"}\n"
"QRadioButton::indicator::checked {\n"
"    color: rgb(0, 0, 0);\n"
"    image: url(:/ico/ico/checked-red.png)\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    \n"
"    image: url(:/ico/ico/unchecked.png)\n"
"}\n"
"\n"
"\n"
"QGroupBox{\n"
"           color: rgb(200, 200, 200); \n"
"            /*background: rgb(68, 69, 73);*/\n"
"     "
                        "      background: rgb(50, 50, 50);\n"
"          \n"
"}\n"
"\n"
"QCheckBox{\n"
"         spacing: 10px;\n"
"         \n"
"}\n"
"QCheckBox:enabled{\n"
"        color: rgb(175, 175, 175);\n"
"    /* color: rgb(0, 0, 0)*/\n"
"}\n"
"QCheckBox:enabled:hover{\n"
"        color: rgb(200, 200, 200);\n"
"       \n"
"}\n"
"QCheckBox:!enabled{\n"
"        color: rgb(155, 155, 155);\n"
"}\n"
"\n"
"QCheckBox::indicator::checked{\n"
"       image: url(:/ico/ico/box-checked.png)\n"
"}\n"
"QCheckBox::indicator {\n"
"        width: 30px;\n"
"        height:25px;\n"
"}\n"
"QCheckBox::indicator::unchecked{\n"
"        image: url(:/ico/ico/box-checked-left.png)\n"
"}\n"
"\n"
"QTextBrowser{\n"
"     background: rgb(50, 50, 50);\n"
"     color: rgb(200, 200, 200);\n"
"\n"
"}\n"
"/**********\344\270\213\346\213\211\345\210\227\350\241\250**********/\n"
"QComboBox {\n"
"        height: 25px;\n"
"        border-radius: 4px;\n"
"        border: 1px solid rgb(100, 100, 100);\n"
"        background: rgb(72, 72, 73);\n"
"}\n"
"QComboBox:e"
                        "nabled {\n"
"        color: rgb(175, 175, 175);\n"
"}\n"
"QComboBox:!enabled {\n"
"        color: rgb(155, 155, 155);\n"
"}\n"
"QComboBox:enabled:hover, QComboBox:enabled:focus {\n"
"        color: rgb(230, 230, 230);\n"
"        background: rgb(68, 69, 73);\n"
"}\n"
"QComboBox::drop-down {\n"
"        width: 20px;\n"
"        border: none;\n"
"        background: transparent;\n"
"}\n"
"QComboBox::drop-down:hover {\n"
"        background: rgba(255, 255, 255, 30);\n"
"}\n"
"QComboBox::down-arrow {\n"
"        image: url(:/Black/arrowBottom);\n"
"}\n"
"QComboBox::down-arrow:on {\n"
"        /**top: 1px;**/\n"
"}\n"
"QComboBox QAbstractItemView {\n"
"        border: 1px solid rgb(100, 100, 100);\n"
"        background: rgb(68, 69, 73);\n"
"        outline: none;\n"
"}\n"
"QComboBox QAbstractItemView::item {\n"
"        height: 25px;\n"
"        color: rgb(175, 175, 175);\n"
"}\n"
"QComboBox QAbstractItemView::item:selected {\n"
"        background: rgba(255, 255, 255, 40);\n"
"        color: rgb(230, 230, 230);\n"
""
                        "}\n"
"QLineEdit {\n"
"        border-radius: 4px;\n"
"        height: 25px;\n"
"        width:30px;\n"
"        border: 1px solid rgb(100, 100, 100);\n"
"        background: rgb(72, 72, 73);\n"
"}\n"
"\n"
"QLineEdit:enabled {\n"
"        color: rgb(175, 175, 175);\n"
"}\n"
"QLineEdit:enabled:hover, QLineEdit:enabled:focus {\n"
"        color: rgb(230, 230, 230);\n"
"}\n"
"QLineEdit:!enabled {\n"
"        color: rgb(155, 155, 155);\n"
"}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        Client1 = new QWidget();
        Client1->setObjectName(QStringLiteral("Client1"));
        tabWidget->addTab(Client1, QString());
        Client2 = new QWidget();
        Client2->setObjectName(QStringLiteral("Client2"));
        tabWidget->addTab(Client2, QString());
        Client3 = new QWidget();
        Client3->setObjectName(QStringLiteral("Client3"));
        tabWidget->addTab(Client3, QString());
        Client4 = new QWidget();
        Client4->setObjectName(QStringLiteral("Client4"));
        tabWidget->addTab(Client4, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_8 = new QGroupBox(tab);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 10, 443, 325));
        verticalLayout_11 = new QVBoxLayout(groupBox_8);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        groupBox_7 = new QGroupBox(groupBox_8);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout_12 = new QVBoxLayout(groupBox_7);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        textBrowser_UdpMessage = new QTextBrowser(groupBox_7);
        textBrowser_UdpMessage->setObjectName(QStringLiteral("textBrowser_UdpMessage"));

        verticalLayout_12->addWidget(textBrowser_UdpMessage);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(groupBox_7);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_8->addWidget(label);

        lineEdit_UdpTargetIP = new QLineEdit(groupBox_7);
        lineEdit_UdpTargetIP->setObjectName(QStringLiteral("lineEdit_UdpTargetIP"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_UdpTargetIP->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetIP->setSizePolicy(sizePolicy1);
        lineEdit_UdpTargetIP->setMinimumSize(QSize(200, 0));
        lineEdit_UdpTargetIP->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_8->addWidget(lineEdit_UdpTargetIP);

        line_2 = new QFrame(groupBox_7);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line_2);

        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        lineEdit_UdpTargetPort = new QLineEdit(groupBox_7);
        lineEdit_UdpTargetPort->setObjectName(QStringLiteral("lineEdit_UdpTargetPort"));
        lineEdit_UdpTargetPort->setEnabled(true);
        sizePolicy1.setHeightForWidth(lineEdit_UdpTargetPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetPort->setSizePolicy(sizePolicy1);
        lineEdit_UdpTargetPort->setMinimumSize(QSize(80, 0));
        lineEdit_UdpTargetPort->setMaximumSize(QSize(80, 16777215));
        lineEdit_UdpTargetPort->setBaseSize(QSize(0, 0));

        horizontalLayout_8->addWidget(lineEdit_UdpTargetPort);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);


        verticalLayout_12->addLayout(horizontalLayout_8);

        line_3 = new QFrame(groupBox_7);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_12->addWidget(line_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lineEdit_UdpSend = new QLineEdit(groupBox_7);
        lineEdit_UdpSend->setObjectName(QStringLiteral("lineEdit_UdpSend"));

        horizontalLayout_6->addWidget(lineEdit_UdpSend);

        line_8 = new QFrame(groupBox_7);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_6->addWidget(line_8);

        button_UdpSend = new QPushButton(groupBox_7);
        button_UdpSend->setObjectName(QStringLiteral("button_UdpSend"));

        horizontalLayout_6->addWidget(button_UdpSend);


        verticalLayout_12->addLayout(horizontalLayout_6);


        verticalLayout_11->addWidget(groupBox_7);

        tabWidget->addTab(tab, QString());

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_6 = new QSpacerItem(187, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Listen = new QLabel(groupBox_3);
        Listen->setObjectName(QStringLiteral("Listen"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Listen->sizePolicy().hasHeightForWidth());
        Listen->setSizePolicy(sizePolicy2);
        Listen->setMinimumSize(QSize(80, 25));

        horizontalLayout_3->addWidget(Listen);

        lineEdit_UdpListenPort = new QLineEdit(groupBox_3);
        lineEdit_UdpListenPort->setObjectName(QStringLiteral("lineEdit_UdpListenPort"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_UdpListenPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpListenPort->setSizePolicy(sizePolicy3);
        lineEdit_UdpListenPort->setMinimumSize(QSize(60, 0));
        lineEdit_UdpListenPort->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_3->addWidget(lineEdit_UdpListenPort);


        gridLayout->addLayout(horizontalLayout_3, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(93, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_local = new QPushButton(groupBox_3);
        pushButton_local->setObjectName(QStringLiteral("pushButton_local"));
        sizePolicy2.setHeightForWidth(pushButton_local->sizePolicy().hasHeightForWidth());
        pushButton_local->setSizePolicy(sizePolicy2);
        pushButton_local->setMinimumSize(QSize(60, 0));
        pushButton_local->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_5->addWidget(pushButton_local);

        pushButton_remote = new QPushButton(groupBox_3);
        pushButton_remote->setObjectName(QStringLiteral("pushButton_remote"));
        pushButton_remote->setMinimumSize(QSize(60, 0));
        pushButton_remote->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_5->addWidget(pushButton_remote);


        gridLayout->addLayout(horizontalLayout_5, 0, 4, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
        radioButton = new QRadioButton(groupBox_3);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy4);
        radioButton->setAutoExclusive(false);

        horizontalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_3);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        sizePolicy2.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy2);
        radioButton_2->setAutoExclusive(false);

        horizontalLayout_2->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(groupBox_3);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        sizePolicy2.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBox_3);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setAutoExclusive(false);

        horizontalLayout_2->addWidget(radioButton_4);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox_Interface = new QComboBox(groupBox_3);
        comboBox_Interface->setObjectName(QStringLiteral("comboBox_Interface"));
        sizePolicy2.setHeightForWidth(comboBox_Interface->sizePolicy().hasHeightForWidth());
        comboBox_Interface->setSizePolicy(sizePolicy2);
        comboBox_Interface->setMaximumSize(QSize(130, 16777215));

        horizontalLayout->addWidget(comboBox_Interface);

        label_LocalIP = new QLabel(groupBox_3);
        label_LocalIP->setObjectName(QStringLiteral("label_LocalIP"));
        sizePolicy3.setHeightForWidth(label_LocalIP->sizePolicy().hasHeightForWidth());
        label_LocalIP->setSizePolicy(sizePolicy3);
        label_LocalIP->setMinimumSize(QSize(100, 25));
        label_LocalIP->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(label_LocalIP);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(187, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setMinimumSize(QSize(80, 0));

        horizontalLayout_4->addWidget(label_3);

        label_clientnum = new QLabel(groupBox_3);
        label_clientnum->setObjectName(QStringLiteral("label_clientnum"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_clientnum->sizePolicy().hasHeightForWidth());
        label_clientnum->setSizePolicy(sizePolicy5);
        label_clientnum->setMinimumSize(QSize(60, 0));

        horizontalLayout_4->addWidget(label_clientnum);


        gridLayout->addLayout(horizontalLayout_4, 1, 2, 1, 1);

        button_UdpStart = new QPushButton(groupBox_3);
        button_UdpStart->setObjectName(QStringLiteral("button_UdpStart"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(button_UdpStart->sizePolicy().hasHeightForWidth());
        button_UdpStart->setSizePolicy(sizePolicy6);
        button_UdpStart->setMinimumSize(QSize(140, 0));
        button_UdpStart->setMaximumSize(QSize(140, 16777215));

        gridLayout->addWidget(button_UdpStart, 1, 4, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(93, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 3, 1, 1);


        gridLayout_2->addWidget(groupBox_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 892, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Client1), QApplication::translate("MainWindow", "Client1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Client2), QApplication::translate("MainWindow", "Client2", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Client3), QApplication::translate("MainWindow", "Client3", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Client4), QApplication::translate("MainWindow", "Client4", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Message:", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Send to:", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "IP:", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Port:", Q_NULLPTR));
        button_UdpSend->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Debug", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Network Interface:", Q_NULLPTR));
        Listen->setText(QApplication::translate("MainWindow", "Listen Port:", Q_NULLPTR));
        pushButton_local->setText(QApplication::translate("MainWindow", "Local", Q_NULLPTR));
        pushButton_remote->setText(QApplication::translate("MainWindow", "Remote", Q_NULLPTR));
        radioButton->setText(QString());
        radioButton_2->setText(QString());
        radioButton_3->setText(QString());
        radioButton_4->setText(QString());
        label_LocalIP->setText(QApplication::translate("MainWindow", "255.255.255.255", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Client Num: ", Q_NULLPTR));
        label_clientnum->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        button_UdpStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
