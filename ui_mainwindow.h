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
#include <QtWidgets/QCheckBox>
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
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_LocalIP;
    QSpacerItem *horizontalSpacer;
    QLabel *Listen;
    QLineEdit *lineEdit_UdpListenPort;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_UdpStart;
    QTabWidget *tabWidget;
    QWidget *Client1;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *button_IVSetting;
    QLabel *label_unit;
    QCheckBox *checkBox;
    QLabel *label_Channel1;
    QCheckBox *checkBox_2;
    QLabel *label_Channel2;
    QCheckBox *checkBox_3;
    QLabel *label_Channel3;
    QCheckBox *checkBox_4;
    QLabel *label_Channel4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_2;
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(526, 604);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget#centerWidget {\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"QFrame{\n"
"        border: 1px solid rgb(50, 50, 50);\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"\n"
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
"        background: rgb(85, 85, 85);\n"
"}\n"
"QPushButton:enabled:pressed{\n"
"        background: rgb(80, 80, 80);\n"
"}\n"
"\n"
"\n"
"\n"
""
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
"        width: 20px;\n"
"        height:20px;\n"
"}\n"
"QRadioButton::indicator::checked {\n"
"    color: rgb(0, 0, 0);\n"
"    image: url(:/ico/ico/checked.png)\n"
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
"           background: rgb(50, 50, 50);\n"
"          \n"
"}\n"
"\n"
"QCheckBox{\n"
"         spacing: 10px;\n"
"         \n"
"}\n"
"QCheckBox:enabled{\n"
"      "
                        "  color: rgb(175, 175, 175);\n"
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
"QComboBox:enabled {\n"
"        color: rgb(175, 175, 175);\n"
"}\n"
"QComboBox:!enabled {\n"
"        color: rgb(155, 155, 155);\n"
"}\n"
"QComboBox:enabled:hover, QCom"
                        "boBox:enabled:focus {\n"
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
"/*\n"
"QComboBox::down-arrow {\n"
"        image: url(:/Black/arrowBottom);\n"
"}*/\n"
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
"}\n"
"QLineEdit {\n"
"        border-radius: 4px;\n"
"        height: 25px;\n"
"        width:30px;\n"
"        border: 1px solid rgb(100, 100, 1"
                        "00);\n"
"        background: rgb(72, 72, 73);\n"
"}\n"
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
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(9, 9, 502, 69));
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        line = new QFrame(groupBox_3);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_2);

        label_LocalIP = new QLabel(groupBox_3);
        label_LocalIP->setObjectName(QStringLiteral("label_LocalIP"));

        horizontalLayout->addWidget(label_LocalIP);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Listen = new QLabel(groupBox_3);
        Listen->setObjectName(QStringLiteral("Listen"));

        horizontalLayout->addWidget(Listen);

        lineEdit_UdpListenPort = new QLineEdit(groupBox_3);
        lineEdit_UdpListenPort->setObjectName(QStringLiteral("lineEdit_UdpListenPort"));

        horizontalLayout->addWidget(lineEdit_UdpListenPort);

        horizontalSpacer_2 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        button_UdpStart = new QPushButton(groupBox_3);
        button_UdpStart->setObjectName(QStringLiteral("button_UdpStart"));

        horizontalLayout->addWidget(button_UdpStart);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 80, 501, 421));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        Client1 = new QWidget();
        Client1->setObjectName(QStringLiteral("Client1"));
        groupBox = new QGroupBox(Client1);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 171, 191));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        button_IVSetting = new QPushButton(groupBox);
        button_IVSetting->setObjectName(QStringLiteral("button_IVSetting"));

        gridLayout->addWidget(button_IVSetting, 0, 0, 1, 1);

        label_unit = new QLabel(groupBox);
        label_unit->setObjectName(QStringLiteral("label_unit"));
        label_unit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_unit, 0, 1, 1, 1);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout->addWidget(checkBox, 1, 0, 1, 1);

        label_Channel1 = new QLabel(groupBox);
        label_Channel1->setObjectName(QStringLiteral("label_Channel1"));

        gridLayout->addWidget(label_Channel1, 1, 1, 1, 1);

        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 2, 0, 1, 1);

        label_Channel2 = new QLabel(groupBox);
        label_Channel2->setObjectName(QStringLiteral("label_Channel2"));

        gridLayout->addWidget(label_Channel2, 2, 1, 1, 1);

        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 3, 0, 1, 1);

        label_Channel3 = new QLabel(groupBox);
        label_Channel3->setObjectName(QStringLiteral("label_Channel3"));

        gridLayout->addWidget(label_Channel3, 3, 1, 1, 1);

        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QStringLiteral("checkBox_4"));

        gridLayout->addWidget(checkBox_4, 4, 0, 1, 1);

        label_Channel4 = new QLabel(groupBox);
        label_Channel4->setObjectName(QStringLiteral("label_Channel4"));

        gridLayout->addWidget(label_Channel4, 4, 1, 1, 1);

        button_IVSetting->raise();
        checkBox->raise();
        checkBox_2->raise();
        checkBox_3->raise();
        checkBox_4->raise();
        label_unit->raise();
        label_Channel1->raise();
        label_Channel2->raise();
        label_Channel3->raise();
        label_Channel4->raise();
        groupBox_2 = new QGroupBox(Client1);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 194, 171, 141));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_4->addWidget(label_7);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_8);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        radioButton_3 = new QRadioButton(groupBox_2);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        sizePolicy.setHeightForWidth(radioButton_3->sizePolicy().hasHeightForWidth());
        radioButton_3->setSizePolicy(sizePolicy);
        radioButton_3->setLayoutDirection(Qt::LeftToRight);
        radioButton_3->setAutoFillBackground(false);

        horizontalLayout_2->addWidget(radioButton_3);

        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        sizePolicy.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy);
        radioButton->setLayoutDirection(Qt::LeftToRight);
        radioButton->setAutoFillBackground(false);
        radioButton->setInputMethodHints(Qt::ImhNone);

        horizontalLayout_2->addWidget(radioButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_3->addWidget(label_9);

        radioButton_5 = new QRadioButton(groupBox_2);
        radioButton_5->setObjectName(QStringLiteral("radioButton_5"));
        sizePolicy.setHeightForWidth(radioButton_5->sizePolicy().hasHeightForWidth());
        radioButton_5->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(radioButton_5);

        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        sizePolicy.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy);
        radioButton_2->setLayoutDirection(Qt::LeftToRight);
        radioButton_2->setAutoFillBackground(false);
        radioButton_2->setInputMethodHints(Qt::ImhNone);

        horizontalLayout_3->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout_3);

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
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_UdpTargetIP->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetIP->setSizePolicy(sizePolicy2);
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
        sizePolicy2.setHeightForWidth(lineEdit_UdpTargetPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetPort->setSizePolicy(sizePolicy2);
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
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 526, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Network Interface:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "IP: ", Q_NULLPTR));
        label_LocalIP->setText(QApplication::translate("MainWindow", "255.255.255.255", Q_NULLPTR));
        Listen->setText(QApplication::translate("MainWindow", "Listen Port:", Q_NULLPTR));
        button_UdpStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Anolog Input", Q_NULLPTR));
        button_IVSetting->setText(QApplication::translate("MainWindow", "I/V Setting", Q_NULLPTR));
        label_unit->setText(QApplication::translate("MainWindow", "\345\215\225\344\275\215(mA)", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "CH1", Q_NULLPTR));
        label_Channel1->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("MainWindow", "CH2", Q_NULLPTR));
        label_Channel2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("MainWindow", "CH3", Q_NULLPTR));
        label_Channel3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        checkBox_4->setText(QApplication::translate("MainWindow", "CH4", Q_NULLPTR));
        label_Channel4->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Digital Input", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Status", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", " 0", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", " 1", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "CH1", Q_NULLPTR));
        radioButton_3->setText(QString());
        radioButton->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "CH2", Q_NULLPTR));
        radioButton_5->setText(QString());
        radioButton_2->setText(QString());
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
