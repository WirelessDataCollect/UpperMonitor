/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout_3;
    QFrame *frame_3;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *more;
    QPushButton *minimum;
    QPushButton *exit;
    QLabel *label;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_LocalIP;
    QComboBox *comboBox;
    QCheckBox *checkBox_2;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QFrame *frame_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(420, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Login->sizePolicy().hasHeightForWidth());
        Login->setSizePolicy(sizePolicy);
        Login->setMinimumSize(QSize(420, 320));
        Login->setMaximumSize(QSize(420, 320));
        Login->setWindowTitle(QString::fromUtf8("Login"));
        Login->setStyleSheet(QString::fromUtf8("background-color: rgb(205, 209, 213);"));
        gridLayout_3 = new QGridLayout(Login);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(Login);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("#frame_3{border-image: url(:/ico/ico/ruililogin.png)}\n"
"#frame_3 *{border-image: url()}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(318, 0, 102, 21));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 230, 231);\n"
"border-image: url(:/ico/ico/toolground.png);"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_4);
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(frame_4);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(21, 21));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QString::fromUtf8("\345\205\263\344\272\216"));
#endif // QT_NO_TOOLTIP
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/about.png)}\n"
""));

        horizontalLayout_3->addWidget(pushButton_3);

        more = new QPushButton(frame_4);
        more->setObjectName(QString::fromUtf8("more"));
        sizePolicy1.setHeightForWidth(more->sizePolicy().hasHeightForWidth());
        more->setSizePolicy(sizePolicy1);
        more->setMinimumSize(QSize(21, 21));
        more->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/more.png)}\n"
""));

        horizontalLayout_3->addWidget(more);

        minimum = new QPushButton(frame_4);
        minimum->setObjectName(QString::fromUtf8("minimum"));
        sizePolicy1.setHeightForWidth(minimum->sizePolicy().hasHeightForWidth());
        minimum->setSizePolicy(sizePolicy1);
        minimum->setMinimumSize(QSize(21, 21));
        minimum->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/mini.png)}\n"
""));
        minimum->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(minimum);

        exit = new QPushButton(frame_4);
        exit->setObjectName(QString::fromUtf8("exit"));
        sizePolicy1.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy1);
        exit->setMinimumSize(QSize(21, 21));
        exit->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/close.png)}\n"
""));

        horizontalLayout_3->addWidget(exit);

        exit->raise();
        more->raise();
        minimum->raise();
        pushButton_3->raise();
        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 112, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 240, 241);\n"
"color: rgb(23, 55, 131);"));

        gridLayout_3->addWidget(frame_3, 0, 0, 1, 1);

        frame = new QFrame(Login);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_LocalIP = new QLabel(frame);
        label_LocalIP->setObjectName(QString::fromUtf8("label_LocalIP"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_LocalIP->sizePolicy().hasHeightForWidth());
        label_LocalIP->setSizePolicy(sizePolicy2);
        label_LocalIP->setMinimumSize(QSize(100, 0));

        gridLayout_2->addWidget(label_LocalIP, 4, 3, 1, 1);

        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy3);
        comboBox->setMinimumSize(QSize(25, 0));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 2);

        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout_2->addWidget(checkBox_2, 3, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout_2->addWidget(checkBox, 3, 1, 1, 1);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 35));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        gridLayout_2->addWidget(pushButton, 4, 1, 1, 1);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(120, 120));
        frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/ico/ico/user.png);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(frame_2, 1, 0, 4, 1);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(true);
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(50);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy4);
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setBaseSize(QSize(0, 27));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        lineEdit->setFont(font1);
        lineEdit->setCursorPosition(3);

        gridLayout_2->addWidget(lineEdit, 1, 1, 1, 2);

        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy5);
        lineEdit_2->setMinimumSize(QSize(0, 25));
        QFont font2;
        font2.setPointSize(11);
        lineEdit_2->setFont(font2);

        gridLayout_2->addWidget(lineEdit_2, 2, 1, 1, 2);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        gridLayout_2->addWidget(pushButton_2, 4, 2, 1, 1);


        gridLayout_3->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        pushButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        more->setToolTip(QApplication::translate("Login", "\350\256\276\347\275\256\347\273\210\347\253\257\350\277\236\346\216\245WIFI\345\257\206\347\240\201", nullptr));
#endif // QT_NO_TOOLTIP
        more->setText(QString());
#ifndef QT_NO_TOOLTIP
        minimum->setToolTip(QApplication::translate("Login", "\346\234\200\345\260\217", nullptr));
#endif // QT_NO_TOOLTIP
        minimum->setText(QString());
#ifndef QT_NO_TOOLTIP
        exit->setToolTip(QApplication::translate("Login", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        exit->setText(QString());
        label->setText(QApplication::translate("Login", "\345\210\266\345\212\250\346\265\213\350\257\225\347\263\273\347\273\237\347\273\210\347\253\257", nullptr));
        label_LocalIP->setText(QApplication::translate("Login", "IP: ", nullptr));
        comboBox->setItemText(0, QApplication::translate("Login", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBox->setItemText(1, QApplication::translate("Login", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBox->setItemText(2, QApplication::translate("Login", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));

        checkBox_2->setText(QApplication::translate("Login", "\350\207\252\345\212\250\347\231\273\351\231\206", nullptr));
        checkBox->setText(QApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
        pushButton->setText(QApplication::translate("Login", "\345\256\211\345\205\250\347\231\273\351\231\206", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("Login", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit->setWhatsThis(QApplication::translate("Login", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        lineEdit->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_2->setToolTip(QApplication::translate("Login", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_2->setWhatsThis(QApplication::translate("Login", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        lineEdit_2->setText(QApplication::translate("Login", "\347\231\273\351\231\206\345\257\206\347\240\201", nullptr));
        pushButton_2->setText(QApplication::translate("Login", "\346\234\254\345\234\260\346\265\213\350\257\225", nullptr));
        Q_UNUSED(Login);
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
