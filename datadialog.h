#ifndef DATADIALOG_H
#define DATADIALOG_H

#include <QDialog>
#include<QTableView>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QVector>
#include<QPointF>
#include<QDebug>
namespace Ui {
class DataDialog;
}

class DataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataDialog(QWidget *parent = nullptr);
    ~DataDialog();
     QStandardItemModel  *aItemModel;//数据模型
     void AddColumn(QString name,QVector<QPointF> data);
private:
    Ui::DataDialog *ui;
};

#endif // DATADIALOG_H
