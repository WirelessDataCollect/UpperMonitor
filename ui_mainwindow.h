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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
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
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *label_LocalIP;
    QSpacerItem *horizontalSpacer;
    QLabel *Listen;
    QLineEdit *lineEdit_UdpListenPort;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *button_UdpStart;
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
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(892, 619);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget#centerWidget {\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"\n"
"QWidget#widchart {\n"
"        background: rgb(50, 50, 50);\n"
"}\n"
"\n"
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
"        height:20px;\n"
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
"QPush"
                        "Button:enabled:pressed{\n"
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
"QC"
                        "heckBox{\n"
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
"QComboBox:enabled {\n"
"        color: rgb(175, 175, 175);\n"
"}\n"
"QComboBox"
                        ":!enabled {\n"
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
" "
                        "       height: 25px;\n"
"        width:30px;\n"
"        border: 1px solid rgb(100, 100, 100);\n"
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
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(groupBox_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_2);

        label_LocalIP = new QLabel(groupBox_3);
        label_LocalIP->setObjectName(QStringLiteral("label_LocalIP"));
        label_LocalIP->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(label_LocalIP);

        horizontalSpacer = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Listen = new QLabel(groupBox_3);
        Listen->setObjectName(QStringLiteral("Listen"));

        horizontalLayout->addWidget(Listen);

        lineEdit_UdpListenPort = new QLineEdit(groupBox_3);
        lineEdit_UdpListenPort->setObjectName(QStringLiteral("lineEdit_UdpListenPort"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_UdpListenPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpListenPort->setSizePolicy(sizePolicy2);
        lineEdit_UdpListenPort->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(lineEdit_UdpListenPort);

        horizontalSpacer_2 = new QSpacerItem(48, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        button_UdpStart = new QPushButton(groupBox_3);
        button_UdpStart->setObjectName(QStringLiteral("button_UdpStart"));
        sizePolicy1.setHeightForWidth(button_UdpStart->sizePolicy().hasHeightForWidth());
        button_UdpStart->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(button_UdpStart);


        verticalLayout->addWidget(groupBox_3);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
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
        sizePolicy.setHeightForWidth(lineEdit_UdpTargetIP->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetIP->setSizePolicy(sizePolicy);
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
        sizePolicy.setHeightForWidth(lineEdit_UdpTargetPort->sizePolicy().hasHeightForWidth());
        lineEdit_UdpTargetPort->setSizePolicy(sizePolicy);
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

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 892, 23));
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
        label_2->setText(QApplication::translate("MainWindow", "IP:", Q_NULLPTR));
        label_LocalIP->setText(QApplication::translate("MainWindow", "255.255.255.255", Q_NULLPTR));
        Listen->setText(QApplication::translate("MainWindow", "Listen Port:", Q_NULLPTR));
        button_UdpStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
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
