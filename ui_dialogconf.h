/********************************************************************************
** Form generated from reading UI file 'dialogconf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONF_H
#define UI_DIALOGCONF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogConf
{
public:
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *Tab1;
    QGridLayout *gridLayout;
    QLabel *label_10;
    QComboBox *comboBox_2;
    QLabel *label_9;
    QPushButton *pushButton_3;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_11;
    QLineEdit *lineEdit_3;
    QDialogButtonBox *buttonBox;
    QWidget *Tab2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLabel *label_6;
    QLabel *label_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QLabel *label_8;
    QLineEdit *lineEdit_8;
    QDialogButtonBox *buttonBox_2;

    void setupUi(QDialog *DialogConf)
    {
        if (DialogConf->objectName().isEmpty())
            DialogConf->setObjectName(QString::fromUtf8("DialogConf"));
        DialogConf->resize(380, 353);
        gridLayout_4 = new QGridLayout(DialogConf);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        tabWidget = new QTabWidget(DialogConf);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Tab1 = new QWidget();
        Tab1->setObjectName(QString::fromUtf8("Tab1"));
        gridLayout = new QGridLayout(Tab1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_10 = new QLabel(Tab1);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout->addWidget(label_10, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(Tab1);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        gridLayout->addWidget(comboBox_2, 0, 1, 1, 1);

        label_9 = new QLabel(Tab1);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(Tab1);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(pushButton_3, 1, 1, 1, 1);

        label = new QLabel(Tab1);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        comboBox = new QComboBox(Tab1);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox, 2, 1, 1, 1);

        label_2 = new QLabel(Tab1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        lineEdit = new QLineEdit(Tab1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit, 3, 1, 1, 1);

        label_3 = new QLabel(Tab1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        lineEdit_2 = new QLineEdit(Tab1);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_2, 4, 1, 1, 1);

        label_11 = new QLabel(Tab1);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout->addWidget(label_11, 5, 0, 1, 1);

        lineEdit_3 = new QLineEdit(Tab1);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_3, 5, 1, 1, 1);

        buttonBox = new QDialogButtonBox(Tab1);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 1, 1, 1);

        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName(QString::fromUtf8("Tab2"));
        verticalLayout_2 = new QVBoxLayout(Tab2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(Tab2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(90, 0));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 0, 3, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 1, 3, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 2, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Tab2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMinimumSize(QSize(90, 0));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout_3->addWidget(lineEdit_7, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        gridLayout_3->addWidget(lineEdit_8, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        buttonBox_2 = new QDialogButtonBox(Tab2);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox_2);

        tabWidget->addTab(Tab2, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(DialogConf);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DialogConf);
    } // setupUi

    void retranslateUi(QDialog *DialogConf)
    {
        DialogConf->setWindowTitle(QApplication::translate("DialogConf", "\347\273\210\347\253\257\350\256\276\347\275\256", nullptr));
        label_10->setText(QApplication::translate("DialogConf", "\346\250\241\345\274\217\350\256\276\347\275\256", nullptr));
        comboBox_2->setItemText(0, QApplication::translate("DialogConf", "\351\207\207\351\233\206\347\273\210\347\253\257", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("DialogConf", "\345\220\214\346\255\245\346\227\266\351\222\237", nullptr));

        label_9->setText(QApplication::translate("DialogConf", "\350\256\276\345\244\207\350\277\236\346\216\245", nullptr));
        pushButton_3->setText(QApplication::translate("DialogConf", "\350\277\236\346\216\245\351\207\207\351\233\206\347\273\210\347\253\257", nullptr));
        label->setText(QApplication::translate("DialogConf", "\350\256\276\345\244\207ID", nullptr));
        comboBox->setItemText(0, QApplication::translate("DialogConf", "1", nullptr));
        comboBox->setItemText(1, QApplication::translate("DialogConf", "2", nullptr));
        comboBox->setItemText(2, QApplication::translate("DialogConf", "3", nullptr));
        comboBox->setItemText(3, QApplication::translate("DialogConf", "4", nullptr));
        comboBox->setItemText(4, QApplication::translate("DialogConf", "5", nullptr));

        label_2->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\220\215\347\247\260", nullptr));
        label_3->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\257\206\347\240\201", nullptr));
        label_11->setText(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QApplication::translate("DialogConf", "\351\207\207\351\233\206\347\273\210\347\253\257", nullptr));
        groupBox->setTitle(QApplication::translate("DialogConf", "\346\234\254\345\234\260\344\277\241\346\201\257", nullptr));
        label_4->setText(QApplication::translate("DialogConf", "\346\234\254\346\234\272IP", nullptr));
        label_6->setText(QApplication::translate("DialogConf", "\346\234\254\345\234\260\346\225\260\346\215\256\347\253\257\345\217\243", nullptr));
        label_5->setText(QApplication::translate("DialogConf", "\346\234\254\345\234\260\345\221\275\344\273\244\347\253\257\345\217\243", nullptr));
        groupBox_2->setTitle(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250\344\277\241\346\201\257", nullptr));
        label_7->setText(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250IP", nullptr));
        label_8->setText(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QApplication::translate("DialogConf", "\347\263\273\347\273\237\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogConf: public Ui_DialogConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONF_H
