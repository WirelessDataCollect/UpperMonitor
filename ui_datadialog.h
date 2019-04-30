/********************************************************************************
** Form generated from reading UI file 'datadialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATADIALOG_H
#define UI_DATADIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DataDialog
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;

    void setupUi(QDialog *DataDialog)
    {
        if (DataDialog->objectName().isEmpty())
            DataDialog->setObjectName(QStringLiteral("DataDialog"));
        DataDialog->resize(558, 561);
        gridLayout = new QGridLayout(DataDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView = new QTableView(DataDialog);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 0, 0, 1, 1);


        retranslateUi(DataDialog);

        QMetaObject::connectSlotsByName(DataDialog);
    } // setupUi

    void retranslateUi(QDialog *DataDialog)
    {
        DataDialog->setWindowTitle(QApplication::translate("DataDialog", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DataDialog: public Ui_DataDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATADIALOG_H
