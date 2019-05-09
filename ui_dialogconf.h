/********************************************************************************
** Form generated from reading UI file 'dialogconf.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONF_H
#define UI_DIALOGCONF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;
    QLabel *label_9;
    QPushButton *pushButton_3;
    QComboBox *comboBox;
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
            DialogConf->setObjectName(QStringLiteral("DialogConf"));
        DialogConf->resize(366, 330);
        gridLayout_4 = new QGridLayout(DialogConf);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tabWidget = new QTabWidget(DialogConf);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Tab1 = new QWidget();
        Tab1->setObjectName(QStringLiteral("Tab1"));
        gridLayout = new QGridLayout(Tab1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Tab1);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(Tab1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lineEdit = new QLineEdit(Tab1);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 2);

        label_3 = new QLabel(Tab1);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_2 = new QLineEdit(Tab1);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_2, 3, 1, 1, 2);

        buttonBox = new QDialogButtonBox(Tab1);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 2, 1, 1);

        label_9 = new QLabel(Tab1);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(Tab1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(pushButton_3, 0, 2, 1, 1);

        comboBox = new QComboBox(Tab1);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(comboBox, 1, 2, 1, 1);

        tabWidget->addTab(Tab1, QString());
        Tab2 = new QWidget();
        Tab2->setObjectName(QStringLiteral("Tab2"));
        verticalLayout_2 = new QVBoxLayout(Tab2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(Tab2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(90, 0));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_2->addWidget(lineEdit_4, 0, 3, 1, 1);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 1, 3, 1, 1);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 2, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(Tab2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);
        label_7->setMinimumSize(QSize(90, 0));

        gridLayout_3->addWidget(label_7, 0, 0, 1, 1);

        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout_3->addWidget(lineEdit_7, 0, 1, 1, 1);

        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(label_8, 1, 0, 1, 1);

        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));

        gridLayout_3->addWidget(lineEdit_8, 1, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        buttonBox_2 = new QDialogButtonBox(Tab2);
        buttonBox_2->setObjectName(QStringLiteral("buttonBox_2"));
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_2->addWidget(buttonBox_2);

        tabWidget->addTab(Tab2, QString());

        gridLayout_4->addWidget(tabWidget, 0, 0, 1, 1);


        retranslateUi(DialogConf);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DialogConf);
    } // setupUi

    void retranslateUi(QDialog *DialogConf)
    {
        DialogConf->setWindowTitle(QApplication::translate("DialogConf", "\347\273\210\347\253\257\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("DialogConf", "\350\256\276\345\244\207ID", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\220\215\347\247\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\257\206\347\240\201", Q_NULLPTR));
        label_9->setText(QApplication::translate("DialogConf", "\350\256\276\345\244\207\350\277\236\346\216\245", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("DialogConf", "\350\277\236\346\216\245\351\207\207\351\233\206\347\273\210\347\253\257", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogConf", "1", Q_NULLPTR)
         << QApplication::translate("DialogConf", "2", Q_NULLPTR)
         << QApplication::translate("DialogConf", "3", Q_NULLPTR)
         << QApplication::translate("DialogConf", "4", Q_NULLPTR)
         << QApplication::translate("DialogConf", "5", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(Tab1), QApplication::translate("DialogConf", "\351\207\207\351\233\206\347\273\210\347\253\257", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("DialogConf", "\346\234\254\345\234\260\344\277\241\346\201\257", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogConf", "\346\234\254\346\234\272IP", Q_NULLPTR));
        label_6->setText(QApplication::translate("DialogConf", "\346\234\254\345\234\260\346\225\260\346\215\256\347\253\257\345\217\243", Q_NULLPTR));
        label_5->setText(QApplication::translate("DialogConf", "\346\234\254\345\234\260\345\221\275\344\273\244\347\253\257\345\217\243", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250\344\277\241\346\201\257", Q_NULLPTR));
        label_7->setText(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250IP", Q_NULLPTR));
        label_8->setText(QApplication::translate("DialogConf", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Tab2), QApplication::translate("DialogConf", "\347\263\273\347\273\237\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogConf: public Ui_DialogConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONF_H
