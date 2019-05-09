/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QGridLayout *gridLayout_7;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;
    QLabel *label;
    QSpinBox *spinBox;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QGridLayout *gridLayout;
    QTableView *tableView_3;
    QWidget *tab_4;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_4;
    QTableView *tableView;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_add_1;
    QPushButton *pushButton_remove_1;
    QPushButton *pushButton_clear_1;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QTableView *tableView_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_enable;
    QPushButton *pushButton_remove_2;
    QPushButton *pushButton_clear_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QStringLiteral("Setting"));
        Setting->resize(1105, 738);
        gridLayout_7 = new QGridLayout(Setting);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        frame = new QFrame(Setting);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        treeWidget = new QTreeWidget(frame);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout_2->addWidget(treeWidget, 2, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(frame);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout_2->addWidget(spinBox, 1, 0, 1, 1);


        gridLayout_7->addWidget(frame, 0, 0, 1, 1);

        tabWidget = new QTabWidget(Setting);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout = new QGridLayout(tab_3);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView_3 = new QTableView(tab_3);
        tableView_3->setObjectName(QStringLiteral("tableView_3"));

        gridLayout->addWidget(tableView_3, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        gridLayout_6 = new QGridLayout(tab_4);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_4 = new QGridLayout(groupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableView = new QTableView(groupBox);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout_4->addWidget(tableView, 0, 0, 1, 1);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setStyleSheet(QStringLiteral("background-color: rgb(240, 240, 240);"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_add_1 = new QPushButton(frame_2);
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

        horizontalLayout->addWidget(pushButton_add_1);

        pushButton_remove_1 = new QPushButton(frame_2);
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

        horizontalLayout->addWidget(pushButton_remove_1);

        pushButton_clear_1 = new QPushButton(frame_2);
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

        horizontalLayout->addWidget(pushButton_clear_1);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(175, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout_4->addWidget(frame_2, 1, 0, 1, 1);


        gridLayout_6->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(tab_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        tableView_2 = new QTableView(groupBox_2);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));

        gridLayout_5->addWidget(tableView_2, 0, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(3);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_enable = new QCheckBox(groupBox_2);
        checkBox_enable->setObjectName(QStringLiteral("checkBox_enable"));
        checkBox_enable->setMinimumSize(QSize(24, 20));

        horizontalLayout_2->addWidget(checkBox_enable);

        pushButton_remove_2 = new QPushButton(groupBox_2);
        pushButton_remove_2->setObjectName(QStringLiteral("pushButton_remove_2"));
        sizePolicy.setHeightForWidth(pushButton_remove_2->sizePolicy().hasHeightForWidth());
        pushButton_remove_2->setSizePolicy(sizePolicy);
        pushButton_remove_2->setMinimumSize(QSize(20, 20));
        pushButton_remove_2->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"border-image: url(:/ico/ico/icons/318.bmp);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"    \n"
"    border-image: url(:/ico/ico/icons/319.bmp)\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_remove_2);

        pushButton_clear_2 = new QPushButton(groupBox_2);
        pushButton_clear_2->setObjectName(QStringLiteral("pushButton_clear_2"));
        sizePolicy.setHeightForWidth(pushButton_clear_2->sizePolicy().hasHeightForWidth());
        pushButton_clear_2->setSizePolicy(sizePolicy);
        pushButton_clear_2->setMinimumSize(QSize(20, 20));
        pushButton_clear_2->setMaximumSize(QSize(20, 20));
        pushButton_clear_2->setStyleSheet(QLatin1String("\n"
"QPushButton{\n"
"border-image: url(:/ico/ico/icons/324.bmp);\n"
"\n"
"}\n"
"QPushButton:pressed{\n"
"    \n"
"    border-image: url(:/ico/ico/icons/325.bmp)\n"
"}"));

        horizontalLayout_2->addWidget(pushButton_clear_2);


        gridLayout_5->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_2, 1, 1, 1, 1);


        gridLayout_6->addWidget(groupBox_2, 1, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

        gridLayout_7->addWidget(tabWidget, 0, 1, 1, 1);


        retranslateUi(Setting);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "\351\207\207\351\233\206\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Setting", "\347\252\227\345\217\243\345\271\263\346\273\221\351\225\277\345\272\246", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Setting", "IO", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Setting", "\350\277\207\346\273\244\345\231\250\347\273\204", Q_NULLPTR));
        pushButton_add_1->setText(QString());
        pushButton_remove_1->setText(QString());
        pushButton_clear_1->setText(QString());
        groupBox_2->setTitle(QApplication::translate("Setting", "\346\225\260\346\215\256\346\230\276\347\244\272", Q_NULLPTR));
        checkBox_enable->setText(QString());
        pushButton_remove_2->setText(QString());
        pushButton_clear_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Setting", "CAN", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
