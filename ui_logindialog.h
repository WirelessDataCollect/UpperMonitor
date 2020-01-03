/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

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

class Ui_LoginDialog
{
public:
    QGridLayout *gridLayout_4;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    QPushButton *more;
    QPushButton *minimum;
    QPushButton *exit;
    QSpacerItem *verticalSpacer;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QComboBox *comboBox_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QCheckBox *checkBox_2;
    QLineEdit *lineEdit;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(420, 320);
        LoginDialog->setMinimumSize(QSize(420, 320));
        LoginDialog->setMaximumSize(QSize(420, 320));
        LoginDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 240, 241);"));
        gridLayout_4 = new QGridLayout(LoginDialog);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        frame_3 = new QFrame(LoginDialog);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("#frame_3{border-image: url(:/ico/ico/ruililogin.png)}\n"
"#frame_3 *{border-image: url()}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(276, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        label->setFont(font);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        frame_4 = new QFrame(frame_3);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
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
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(21, 21));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QString::fromUtf8("\345\205\263\344\272\216"));
#endif // QT_NO_TOOLTIP
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/about.png)}\n"
""));

        horizontalLayout_3->addWidget(pushButton_3);

        more = new QPushButton(frame_4);
        more->setObjectName(QString::fromUtf8("more"));
        sizePolicy.setHeightForWidth(more->sizePolicy().hasHeightForWidth());
        more->setSizePolicy(sizePolicy);
        more->setMinimumSize(QSize(21, 21));
        more->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/more.png)}\n"
""));

        horizontalLayout_3->addWidget(more);

        minimum = new QPushButton(frame_4);
        minimum->setObjectName(QString::fromUtf8("minimum"));
        sizePolicy.setHeightForWidth(minimum->sizePolicy().hasHeightForWidth());
        minimum->setSizePolicy(sizePolicy);
        minimum->setMinimumSize(QSize(21, 21));
        minimum->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/mini.png)}\n"
""));
        minimum->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(minimum);

        exit = new QPushButton(frame_4);
        exit->setObjectName(QString::fromUtf8("exit"));
        sizePolicy.setHeightForWidth(exit->sizePolicy().hasHeightForWidth());
        exit->setSizePolicy(sizePolicy);
        exit->setMinimumSize(QSize(21, 21));
        exit->setStyleSheet(QString::fromUtf8("QPushButton{border-image: url(:/ico/ico/close.png)}\n"
""));

        horizontalLayout_3->addWidget(exit);

        exit->raise();
        more->raise();
        minimum->raise();
        pushButton_3->raise();

        gridLayout_2->addWidget(frame_4, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 118, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 1, 1);


        gridLayout_4->addWidget(frame_3, 0, 0, 1, 1);

        frame = new QFrame(LoginDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(120, 120));
        frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/ico/ico/user.png);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);

        horizontalLayout->addWidget(frame_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox_2 = new QComboBox(frame);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox_2, 0, 0, 1, 3);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 35));
        pushButton->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 35));
        pushButton_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgb(24, 56, 132);"));

        gridLayout->addWidget(pushButton_2, 4, 2, 1, 1);

        lineEdit_2 = new QLineEdit(frame);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy2);
        lineEdit_2->setMinimumSize(QSize(0, 25));
        QFont font1;
        font1.setPointSize(11);
        lineEdit_2->setFont(font1);

        gridLayout->addWidget(lineEdit_2, 2, 0, 1, 3);

        checkBox_2 = new QCheckBox(frame);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        gridLayout->addWidget(checkBox_2, 3, 2, 1, 1);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(50);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setBaseSize(QSize(0, 27));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        lineEdit->setFont(font2);
        lineEdit->setCursorPosition(3);

        gridLayout->addWidget(lineEdit, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 1);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 3, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer_3 = new QSpacerItem(89, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_4->addWidget(frame, 1, 0, 1, 1);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QWidget *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Form", nullptr));
        label->setText(QApplication::translate("LoginDialog", "\345\210\266\345\212\250\346\265\213\350\257\225\347\263\273\347\273\237\347\273\210\347\253\257", nullptr));
        pushButton_3->setText(QString());
#ifndef QT_NO_TOOLTIP
        more->setToolTip(QApplication::translate("LoginDialog", "\350\256\276\347\275\256\347\273\210\347\253\257\350\277\236\346\216\245WIFI\345\257\206\347\240\201", nullptr));
#endif // QT_NO_TOOLTIP
        more->setText(QString());
#ifndef QT_NO_TOOLTIP
        minimum->setToolTip(QApplication::translate("LoginDialog", "\346\234\200\345\260\217", nullptr));
#endif // QT_NO_TOOLTIP
        minimum->setText(QString());
#ifndef QT_NO_TOOLTIP
        exit->setToolTip(QApplication::translate("LoginDialog", "\345\205\263\351\227\255", nullptr));
#endif // QT_NO_TOOLTIP
        exit->setText(QString());
        comboBox_2->setItemText(0, QApplication::translate("LoginDialog", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("LoginDialog", "\346\226\260\345\273\272\351\241\271\347\233\256", nullptr));

        pushButton->setText(QApplication::translate("LoginDialog", "\345\256\211\345\205\250\347\231\273\351\231\206", nullptr));
        pushButton_2->setText(QApplication::translate("LoginDialog", "\346\234\254\345\234\260\346\265\213\350\257\225", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_2->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_2->setWhatsThis(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\257\206\347\240\201</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        lineEdit_2->setText(QApplication::translate("LoginDialog", "\347\231\273\351\231\206\345\257\206\347\240\201", nullptr));
        checkBox_2->setText(QApplication::translate("LoginDialog", "\350\207\252\345\212\250\347\231\273\351\231\206", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit->setWhatsThis(QApplication::translate("LoginDialog", "<html><head/><body><p>\347\224\250\346\210\267\345\220\215</p></body></html>", nullptr));
#endif // QT_NO_WHATSTHIS
        lineEdit->setText(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        checkBox->setText(QApplication::translate("LoginDialog", "\350\256\260\344\275\217\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
