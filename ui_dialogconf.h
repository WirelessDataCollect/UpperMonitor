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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogConf
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *DialogConf)
    {
        if (DialogConf->objectName().isEmpty())
            DialogConf->setObjectName(QStringLiteral("DialogConf"));
        DialogConf->resize(400, 300);
        layoutWidget = new QWidget(DialogConf);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 50, 211, 151));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 2, 1, 1, 1);

        layoutWidget1 = new QWidget(DialogConf);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(190, 250, 181, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget1);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(DialogConf);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(70, 10, 211, 31));

        retranslateUi(DialogConf);

        QMetaObject::connectSlotsByName(DialogConf);
    } // setupUi

    void retranslateUi(QDialog *DialogConf)
    {
        DialogConf->setWindowTitle(QApplication::translate("DialogConf", "\347\273\210\347\253\257\350\256\276\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("DialogConf", "\350\256\276\345\244\207ID", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("DialogConf", "1", Q_NULLPTR)
         << QApplication::translate("DialogConf", "2", Q_NULLPTR)
         << QApplication::translate("DialogConf", "3", Q_NULLPTR)
         << QApplication::translate("DialogConf", "4", Q_NULLPTR)
         << QApplication::translate("DialogConf", "5", Q_NULLPTR)
        );
        label_2->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\220\215\347\247\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogConf", "\347\203\255\347\202\271\345\257\206\347\240\201", Q_NULLPTR));
        pushButton->setText(QApplication::translate("DialogConf", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("DialogConf", "\345\217\226\346\266\210", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("DialogConf", "\350\277\236\346\216\245\351\207\207\351\233\206\347\273\210\347\253\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogConf: public Ui_DialogConf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONF_H
