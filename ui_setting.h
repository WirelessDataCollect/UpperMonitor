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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QTreeWidget *treeWidget;
    QLabel *label;
    QSpinBox *spinBox;
    QTableWidget *tableWidget;

    void setupUi(QWidget *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QStringLiteral("Setting"));
        Setting->resize(1105, 743);
        gridLayout = new QGridLayout(Setting);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        splitter = new QSplitter(Setting);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        frame = new QFrame(splitter);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_2->addWidget(lineEdit, 3, 0, 1, 1);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_2->addWidget(pushButton, 2, 0, 1, 1);

        pushButton_3 = new QPushButton(frame);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 6, 0, 1, 1);

        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 5, 0, 1, 1);

        treeWidget = new QTreeWidget(frame);
        treeWidget->headerItem()->setText(0, QString());
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        gridLayout_2->addWidget(treeWidget, 4, 0, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(frame);
        spinBox->setObjectName(QStringLiteral("spinBox"));

        gridLayout_2->addWidget(spinBox, 1, 0, 1, 1);

        splitter->addWidget(frame);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setStyleSheet(QLatin1String("\n"
"selection-background-color: rgb(0,120,215);\n"
""));
        splitter->addWidget(tableWidget);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QWidget *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "\351\207\207\351\233\206\350\256\276\347\275\256", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Setting", "\345\212\240\350\275\275\350\256\276\347\275\256", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Setting", "\344\277\235\345\255\230\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Setting", "\347\252\227\345\217\243\345\271\263\346\273\221\351\225\277\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
