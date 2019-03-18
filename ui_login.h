/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QFrame *frame_2;
    QFrame *frame_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *more;
    QPushButton *minimum;
    QPushButton *exit;
    QLabel *label_LocalIP;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(420, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        Login->setMinimumSize(QSize(420, 320));
        Login->setMaximumSize(QSize(420, 320));
        Login->setWindowTitle(QStringLiteral("Login"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/ico/ico/osc.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Login->setWindowIcon(icon);
        Login->setStyleSheet(QStringLiteral("background-color: rgb(205, 209, 213);"));
        frame_2 = new QFrame(Login);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 160, 120, 120));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(120, 120));
        frame_2->setStyleSheet(QStringLiteral("border-image: url(:/ico/ico/user.png);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(Login);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(0, 0, 421, 141));
        frame_3->setStyleSheet(QStringLiteral("border-image: url(:/ico/ico/ruililogin.png);"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(320, 0, 91, 21));
        frame_4->setStyleSheet(QLatin1String("background-color: rgb(225, 230, 231);\n"
"border-image: url(:/ico/ico/toolground.png);"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(frame_4);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(21, 21));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QString::fromUtf8("\345\205\263\344\272\216"));
#endif // QT_NO_TOOLTIP
        pushButton_3->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/ico/ico/about.png)}\n"
""));

        horizontalLayout_3->addWidget(pushButton_3);

        more = new QPushButton(frame_4);
        more->setObjectName(QStringLiteral("more"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(more->sizePolicy().hasHeightForWidth());
        more->setSizePolicy(sizePolicy1);
        more->setMinimumSize(QSize(21, 21));
        more->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/ico/ico/more.png)}\n"
""));

        horizontalLayout_3->addWidget(more);

        minimum = new QPushButton(frame_4);
        minimum->setObjectName(QStringLiteral("minimum"));
        sizePolicy1.setHeightForWidth(minimum->sizePolicy().hasHeightForWidth());
        minimum->setSizePolicy(sizePolicy1);
        minimum->setMinimumSize(QSize(21, 21));
        minimum->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/ico/ico/mini.png)}\n"
""));
        minimum->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(minimum);

        exit = new QPushButton(frame_4);
        exit->setObjectName(QStringLiteral("exit"));
        sizePolicy1.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy1);
        exit->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/ico/ico/close.png)}\n"
""));

        horizontalLayout_3->addWidget(exit);

        exit->raise();
        more->raise();
        minimum->raise();
        pushButton_3->raise();
        label_LocalIP = new QLabel(Login);
        label_LocalIP->setObjectName(QStringLiteral("label_LocalIP"));
        label_LocalIP->setGeometry(QRect(310, 300, 111, 20));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 150, 175, 162));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 25));

        verticalLayout->addWidget(comboBox);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(50);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setBaseSize(QSize(0, 27));
        QFont font;
        font.setPointSize(11);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        lineEdit->setFont(font);
        lineEdit->setCursorPosition(3);

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy3);
        lineEdit_2->setMinimumSize(QSize(0, 25));
        QFont font1;
        font1.setPointSize(11);
        lineEdit_2->setFont(font1);

        verticalLayout->addWidget(lineEdit_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 35));
        pushButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 35));
        pushButton_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        pushButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        more->setToolTip(QApplication::translate("Login", "\350\256\276\347\275\256\347\273\210\347\253\257\350\277\236\346\216\245WIFI\345\257\206\347\240\201", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        more->setText(QString());
#ifndef QT_NO_TOOLTIP
        minimum->setToolTip(QApplication::translate("Login", "\346\234\200\345\260\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        minimum->setText(QString());
#ifndef QT_NO_TOOLTIP
        exit->setToolTip(QApplication::translate("Login", "\345\205\263\351\227\255", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        exit->setText(QString());
        label_LocalIP->setText(QApplication::translate("Login", "IP: ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("Login", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit->setWhatsThis(QApplication::translate("Login", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lineEdit->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEdit_2->setToolTip(QApplication::translate("Login", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_2->setWhatsThis(QApplication::translate("Login", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        lineEdit_2->setText(QApplication::translate("Login", "\347\231\273\351\231\206\345\257\206\347\240\201", Q_NULLPTR));
        checkBox->setText(QApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("Login", "\350\207\252\345\212\250\347\231\273\351\231\206", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Login", "\345\256\211\345\205\250\347\231\273\351\231\206", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Login", "\346\234\254\345\234\260\346\265\213\350\257\225", Q_NULLPTR));
        Q_UNUSED(Login);
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
