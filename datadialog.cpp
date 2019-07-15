#pragma execution_character_set("utf-8")
#include "datadialog.h"
#include "ui_datadialog.h"

DataDialog::DataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DataDialog)
{
    this->setWindowTitle("数据点");
    ui->setupUi(this);
    aItemModel = new QStandardItemModel();
    ui->tableView->setModel(aItemModel);
}

DataDialog::~DataDialog()
{
    delete ui;
    delete aItemModel;
}
void DataDialog::AddColumn(QString name,QVector<QPointF> data)
{

    qDebug()<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<data.size();
    QList<QStandardItem*> aItemList;

    QList<QStandardItem*> aItemList_2;

     QStandardItem   *aItem;
     aItem = new QStandardItem();
     aItem->setData(name,Qt::DisplayRole);
     aItemList.append(aItem);

     name ="差值";
     aItem = new QStandardItem();
     aItem->setData(name,Qt::DisplayRole);
     aItemList_2.append(aItem);
     qDebug()<<"AddColumn"<<data.size();
      QString str;
     for(auto itor = data.begin();itor<data.end();itor++)
     {
         aItem = new QStandardItem();
        str ="(";
        str.append(QString::number(itor->rx(),'f',3));
        str.append(",");
        str.append(QString::number(itor->ry(),'f',3));
        str.append(")");


         aItem->setData(str,Qt::DisplayRole);
         aItemList.append(aItem);

         aItem = new QStandardItem();
         if(itor!=data.begin())
         {
             str = QString::number((*itor-*(itor-1)).y(),'f',3);
             aItem->setData(str,Qt::DisplayRole);
         }
         aItemList_2.append(aItem);
     }
     aItemModel->insertColumn(aItemModel->columnCount(),aItemList);
     aItemModel->insertColumn(aItemModel->columnCount(),aItemList_2);
}
