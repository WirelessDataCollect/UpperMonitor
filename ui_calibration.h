/********************************************************************************
** Form generated from reading UI file 'calibration.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATION_H
#define UI_CALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Calibration
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QFrame *frame;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_add_1;
    QPushButton *pushButton_remove_1;
    QPushButton *pushButton_clear_1;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Calibration)
    {
        if (Calibration->objectName().isEmpty())
            Calibration->setObjectName(QStringLiteral("Calibration"));
        Calibration->resize(417, 504);
        gridLayout_2 = new QGridLayout(Calibration);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Calibration);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        spinBox = new QSpinBox(Calibration);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setMinimum(1);
        spinBox->setMaximum(5);

        horizontalLayout_2->addWidget(spinBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(Calibration);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox_2 = new QSpinBox(Calibration);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(1);
        spinBox_2->setMaximum(4);

        horizontalLayout_2->addWidget(spinBox_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        label_4 = new QLabel(Calibration);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        spinBox_3 = new QSpinBox(Calibration);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMinimum(0);
        spinBox_3->setMaximum(10000);
        spinBox_3->setSingleStep(100);

        horizontalLayout_2->addWidget(spinBox_3);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        frame = new QFrame(Calibration);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(frame);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_add_1 = new QPushButton(frame);
        pushButton_add_1->setObjectName(QStringLiteral("pushButton_add_1"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_add_1->sizePolicy().hasHeightForWidth());
        pushButton_add_1->setSizePolicy(sizePolicy);
        pushButton_add_1->setMinimumSize(QSize(20, 20));
        pushButton_add_1->setMaximumSize(QSize(30, 16777215));
        pushButton_add_1->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"border-image: url(:/ico/ico/icons/316.bmp);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"    \n"
"    border-image: url(:/ico/ico/icons/317.bmp)\n"
"}"));

        horizontalLayout_3->addWidget(pushButton_add_1);

        pushButton_remove_1 = new QPushButton(frame);
        pushButton_remove_1->setObjectName(QStringLiteral("pushButton_remove_1"));
        sizePolicy.setHeightForWidth(pushButton_remove_1->sizePolicy().hasHeightForWidth());
        pushButton_remove_1->setSizePolicy(sizePolicy);
        pushButton_remove_1->setMinimumSize(QSize(20, 20));
        pushButton_remove_1->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"border-image: url(:/ico/ico/icons/318.bmp);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"    \n"
"    border-image: url(:/ico/ico/icons/319.bmp)\n"
"}"));

        horizontalLayout_3->addWidget(pushButton_remove_1);

        pushButton_clear_1 = new QPushButton(frame);
        pushButton_clear_1->setObjectName(QStringLiteral("pushButton_clear_1"));
        sizePolicy.setHeightForWidth(pushButton_clear_1->sizePolicy().hasHeightForWidth());
        pushButton_clear_1->setSizePolicy(sizePolicy);
        pushButton_clear_1->setMinimumSize(QSize(20, 20));
        pushButton_clear_1->setMaximumSize(QSize(20, 20));
        pushButton_clear_1->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"border-image: url(:/ico/ico/icons/324.bmp);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"    \n"
"    border-image: url(:/ico/ico/icons/325.bmp)\n"
"}"));

        horizontalLayout_3->addWidget(pushButton_clear_1);

        horizontalSpacer_3 = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(Calibration);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(Calibration);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        lineEdit = new QLineEdit(Calibration);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(Calibration);

        QMetaObject::connectSlotsByName(Calibration);
    } // setupUi

    void retranslateUi(QWidget *Calibration)
    {
        Calibration->setWindowTitle(QApplication::translate("Calibration", "\346\240\241\345\207\206", Q_NULLPTR));
        label->setText(QApplication::translate("Calibration", "\347\273\210\347\253\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("Calibration", "\351\200\232\351\201\223", Q_NULLPTR));
        label_4->setText(QApplication::translate("Calibration", "\346\267\261\345\272\246", Q_NULLPTR));
        pushButton_add_1->setText(QString());
        pushButton_remove_1->setText(QString());
        pushButton_clear_1->setText(QString());
        pushButton->setText(QApplication::translate("Calibration", "\346\240\241\345\207\206", Q_NULLPTR));
        label_3->setText(QApplication::translate("Calibration", "\346\213\237\345\220\210\345\244\232\351\241\271\345\274\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Calibration: public Ui_Calibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATION_H
