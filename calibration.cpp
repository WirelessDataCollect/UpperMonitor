#pragma execution_character_set("utf-8")
#include "calibration.h"
#include "ui_calibration.h"
#include"fit.h"
Calibration::Calibration(DeviceSystem *system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calibration),
    device_system(system)

{

    ui->setupUi(this);
    ui->spinBox_3->setValue(1000);
    TableInit();
    connect(this->theModel,SIGNAL(itemChanged(QStandardItem *)),this, SLOT(on_itemChanged(QStandardItem *)));
}

Calibration::~Calibration()
{
    delete ui;
    delete theModel;
    delete theSelection;
    qDebug()<<"Calibration OVER";

}
void Calibration::TableInit()
{
    theModel = new QStandardItemModel(0,3,this);
    theSelection = new QItemSelectionModel(theModel);//Item选择模型
    QStringList headers;
    headers << QString("使能")<<QString("实际值")<<QString("测量均值");
    theModel->setHorizontalHeaderLabels(headers);
    ui->tableView->setModel(theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection);//设置选择模型
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
   // ui->tableView->resizeColumnsToContents();
   ui->tableView->horizontalHeader()->setStretchLastSection(true);
   on_pushButton_add_1_clicked();
}

void Calibration::on_pushButton_add_1_clicked()
{
    QList<QStandardItem*>    aItemList;  //QStandardItem的列表类
    QStandardItem   *aItem;
    aItem=new QStandardItem("使能"); //新建一个QStandardItem
    aItem->setCheckable(true);
    aItem->setEditable(false);
    aItemList<<aItem;//添加到列表类
    for(int j=1;j<theModel->columnCount();j++)
    {
        aItem=new QStandardItem(); //新建一个QStandardItem
        aItem->setSelectable(false);
        aItemList<<aItem;//添加到列表类
    }
    theModel->insertRow(theModel->rowCount(),aItemList); //插入一行，需要每个Cell的Item
    QModelIndex curIndex=theModel->index(theModel->rowCount()-1,0);//创建最后一行的ModelIndex
    theSelection->clearSelection();//清空选择项
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择行
}

void Calibration::on_pushButton_remove_1_clicked()
{
    if(theModel->rowCount()==0) return;
    QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引

    if(theModel->item(curIndex.row(),0)->checkState() == Qt::Checked) return;

    if (curIndex.row()==theModel->rowCount()-1)//最后一行
        theModel->removeRow(curIndex.row()); //删除最后一行
    else
    {
        theModel->removeRow(curIndex.row());//删除一行，并重新设置当前选择行
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}

void Calibration::on_pushButton_clear_1_clicked()
{
    for(int i=0;i<theModel->rowCount();i++)
    {
        theModel->item(i,0)->setCheckState(Qt::Unchecked);
    }
    theModel->removeRows(0,theModel->rowCount());
}
void Calibration::on_itemChanged(QStandardItem *item)
{
    QModelIndex index = theModel->indexFromItem(item);
    bool ok;
    if(index.column() == 0)
    {
        if(item->checkState() == Qt::Checked)
        {
            double y = theModel->item(index.row(),1)->text().toDouble(&ok);
            if(ok)
            {
                 double actual_value = GetActualValue();
                 if(actual_value>0)
                 {
                     theModel->item(index.row(),2)->setText(QString::number(actual_value,'f',5));
//                     vx.append(actual_value);
//                     vy.append(y);
                     QVector<double> data = GetAllActualValue();
                     vx.append(data);
                     vy.append(QVector<double>(data.size(),y));
                 }
                 else item->setCheckState(Qt::Unchecked);
             }
            else{
                theModel->item(index.row(),1)->setText("");
                item->setCheckState(Qt::Unchecked);
            }
        }

        else theModel->item(index.row(),2)->setText("");
    }
}
double Calibration::GetActualValue()
{
    int device = ui->spinBox->value() -1;
    int channel = ui->spinBox_2->value()-1;
    int count = ui->spinBox_3->value();
    SignalData *signal_data = device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data;
   int signal_data_size = signal_data->data_list.size();
   double sum = 0;
   if(signal_data_size>count)
   {
        for(int i= signal_data_size-count;i<signal_data_size;i++)
        {
           sum += signal_data->data_list.at(i);
        }
        return sum/count;
    }
   else return -1;
}
QVector<double> Calibration::GetAllActualValue()
{
    int device = ui->spinBox->value() -1;
    int channel = ui->spinBox_2->value()-1;
    int count = ui->spinBox_3->value();
    SignalData *signal_data = device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data;
   int signal_data_size = signal_data->data_list.size();
   QVector<double> data;
   if(signal_data_size>count) data = signal_data->data_list.mid( signal_data_size -count,count);
   return data;
}

void Calibration::on_pushButton_clicked()
{
    qDebug()<<"VX"<<"VY";
    for(int i=0;i<vx.size();i++)
    qDebug()<< vx.at(i)<<vy.at(i);
//    vx.clear();
//    vy.clear();

//    vx.append(1);
//    vx.append(2);
//    vx.append(3);
//    vx.append(4);
//    vx.append(5);

//    vy.append(2.1);
//    vy.append(4.1);
//    vy.append(6.1);
//    vy.append(8.1);
//    vy.append(10.1);
    Fit fit;
    coeff = fit.GetPara(vx,vy);
     qDebug()<<"coeff";
    for(int i=0;i<coeff.size();i++)
    qDebug()<< coeff.at(i);
    QString str;
    for(int i=1; i<coeff.size();i++)
    {

        double c = coeff[i];
       if(abs(c)>0.000001)
       {
           str += QString::number(c,'f',5);
           str += "X^";
           str += QString::number(i-1,10);
           str +="+";
       }
    }
    str.remove(str.size()-1,1);
    ui->lineEdit->setText(str);

}


