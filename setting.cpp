#pragma execution_character_set("utf-8")
#include "setting.h"
#include "ui_setting.h"
#include<QFileDialog>
#include<QColor>
#include<QBrush>
#include<QDebug>
#include<QColorDialog>
#include<QMessageBox>
#include<QTableWidget>
#include<QString>
#include<QAbstractItemView>
#include"devicesystem.h"
#include"devicesignal.h"
#include<QDir>
Setting::Setting(DeviceSystem *system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    device_system = system;
    ui->setupUi(this);

    TabelInit();

    QString current_path = QCoreApplication::applicationDirPath();
    ui->lineEdit->setText(current_path);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableWidget->resizeColumnsToContents();
    ui->frame->setMaximumWidth(300);
    TreeInit();
    TabelViewInit();
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
   // curPath = QDir::currentPath();
    QString dlgTile = "选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTile,curPath,QFileDialog::ShowDirsOnly);
    if(!selectedDir.isEmpty())
    {
        ui->lineEdit->setText(selectedDir);
        device_system->data_path = selectedDir;
    }
}
void Setting::TreeInit()
{
    QStringList headers;
    headers << QStringLiteral("选择终端");
    ui->treeWidget->setHeaderLabels(headers);

    QTreeWidgetItem *item = new QTreeWidgetItem(1000);
    item->setText(0,"采集终端");

    item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(0,Qt::Unchecked);
    ui->treeWidget->addTopLevelItem(item);


    for(int i=0;i<5;i++)
    {
        QTreeWidgetItem *item_device = new QTreeWidgetItem(100+i);
        item_device->setText(0,"终端"+QString::number(i+1));
        item_device->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item_device->setCheckState(0,Qt::Unchecked);
        ui->treeWidget->topLevelItem(0)->addChild(item_device);

        for(int j=0;j<4;j++)
        {
            QTreeWidgetItem *item_signal = new QTreeWidgetItem(10*i+j);
            item_signal->setText(0,"模拟通道"+QString::number(j+1));
            item_signal->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_signal);

            QTreeWidgetItem *vol_curr_I = new QTreeWidgetItem(8);
            vol_curr_I->setText(0,"电流/电压模式");
            vol_curr_I->setFlags(vol_curr_I->flags() | Qt::ItemIsUserCheckable);
            vol_curr_I->setCheckState(0,Qt::Unchecked);
            item_signal->addChild(vol_curr_I);

        }
        for(int j=0;j<2;j++)
        {
            QTreeWidgetItem *item_signal = new QTreeWidgetItem(10*i+j+4);
            item_signal->setText(0,"数字通道"+QString::number(j+1));
            item_signal->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_signal);
        }
        for(int j=0;j<2;j++)
        {
            QTreeWidgetItem *item_signal = new QTreeWidgetItem(10*i+j+6);
            item_signal->setText(0,"CAN"+QString::number(j+1));
            item_signal->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_signal);

            QTreeWidgetItem *item_signal_H = new QTreeWidgetItem(9);
            item_signal_H->setText(0,"500K/250K");
            item_signal_H->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal_H->setCheckState(0,Qt::Unchecked);
            item_signal->addChild(item_signal_H);
        }

    }
}
void Setting::TabelViewInit()
{
    theModel = new QStandardItemModel(0,8,this);
     theSelection = new QItemSelectionModel(theModel);//Item选择模型
    QStringList headers;
    headers << QStringLiteral("使能")<<QStringLiteral("终端")<<QStringLiteral("通道")<<QStringLiteral("ID")<<QStringLiteral("颜色")<<QStringLiteral("名称")<<QStringLiteral("表达式")<<QStringLiteral("数量");
     theModel->setHorizontalHeaderLabels(headers);
      ui->tableView->setModel(theModel); //设置数据模型
      ui->tableView->setSelectionModel(theSelection);//设置选择模型
      ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
      ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

      combox_delegate_1.combox_list.append("1");
      combox_delegate_1.combox_list.append("2");
      combox_delegate_1.combox_list.append("3");
      combox_delegate_1.combox_list.append("4");
      combox_delegate_1.combox_list.append("5");
      ui->tableView->setItemDelegateForColumn(1,&combox_delegate_1);  //测深，整数
      combox_delegate_2.combox_list.append("1");
      combox_delegate_2.combox_list.append("2");
      ui->tableView->setItemDelegateForColumn(2,&combox_delegate_2);



      theModel_2 = new QStandardItemModel(0,4,this);
      theSelection_2 = new QItemSelectionModel(theModel_2);//Item选择模型
      headers.clear();
      headers << QStringLiteral("使能")<<QStringLiteral("颜色")<<QStringLiteral("名称")<<QStringLiteral("计算公式");
       theModel_2->setHorizontalHeaderLabels(headers);
       ui->tableView_2->setModel(theModel_2); //设置数据模型
       ui->tableView_2->setSelectionModel(theSelection_2);//设置选择模型
       ui->tableView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
       ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectItems);

       connect(this->theModel,SIGNAL(itemChanged(QStandardItem *)),this, SLOT(on_itemChanged(QStandardItem *)));
}

void Setting::TabelInit()
{
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(30);
    ui->tableWidget->setSpan(0,0,6,1);
    ui->tableWidget->setSpan(6,0,6,1);
    ui->tableWidget->setSpan(12,0,6,1);
    ui->tableWidget->setSpan(18,0,6,1);
    ui->tableWidget->setSpan(24,0,6,1);

    QStringList headers;
    headers << QStringLiteral("终端") << QStringLiteral("通道") << QStringLiteral("颜色")<<QStringLiteral("名称")<<QStringLiteral("最小值")<<QStringLiteral("最大值")<<QStringLiteral("单位最小值")<<QStringLiteral("单位最大值");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    connect( ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)),
                    this, SLOT(onHeaderClicked(int)));
    connect( ui->tableWidget->horizontalHeader(), SIGNAL(sectionDoubleClicked(int)),
                    this, SLOT(onHeaderDoubleClicked(int)));
    //if(!ReadTable())//读取失败
    {
        QVector<QTableWidgetItem *> item_vector_0;
        QVector<QTableWidgetItem *> item_vector_1;
        item_vector_0.resize(5);
        item_vector_1.resize(30);
        for(int i= 0;i<30;i++)
        {
            //终端
            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setFlags(item_vector_1[i]->flags()& (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(i,0,item_vector_1[i]);
            //通道
            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setFlags(item_vector_1[i]->flags()& (~Qt::ItemIsEditable));
            if(i%6 < 4) item_vector_1[i]->setText("模拟"+QString::number(i%6+1));
            else item_vector_1[i]->setText("数字"+QString::number(i%6-3));
            ui->tableWidget->setItem(i,1,item_vector_1[i]);
            //颜色
            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setFlags(Qt::NoItemFlags);
            ui->tableWidget->setItem(i,2,item_vector_1[i]);
            //名称
            item_vector_1[i] = new QTableWidgetItem;
            if(i%6 < 4) item_vector_1[i]->setText("模拟"+QString::number(i%6+1));
            else item_vector_1[i]->setText("数字"+QString::number(i%6-3));
            ui->tableWidget->setItem(i,3,item_vector_1[i]);

            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setText("0.8");
            ui->tableWidget->setItem(i,4,item_vector_1[i]);

            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setText("4.5");
            ui->tableWidget->setItem(i,5,item_vector_1[i]);

            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setText("1");
            ui->tableWidget->setItem(i,6,item_vector_1[i]);

            item_vector_1[i] = new QTableWidgetItem;
            item_vector_1[i]->setText("10");
            ui->tableWidget->setItem(i,7,item_vector_1[i]);
        }
        for(int i=0;i<5;i++)
        {

            item_vector_0[i] =  new QTableWidgetItem;
            item_vector_0[i]->setText("终端"+QString::number(i+1));
            item_vector_0[i]->setFlags(item_vector_0[i]->flags()& (~Qt::ItemIsEditable));
            ui->tableWidget->setItem(6*i,0,item_vector_0[i]);
        }
    }

    }


bool Setting::ReadTable(){

        QFile file("settingconfig");
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug()<<"ReadTable Error: cannot open file";
            return false;
        }
        qDebug()<<"ReadTable";
        QDataStream in(&file);
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->read(in);
                if(j ==0 || j==1) item->setFlags(item->flags()& (~Qt::ItemIsEditable));;
                if(j==2) item->setFlags(Qt::NoItemFlags);
                ui->tableWidget->setItem(i,j,item);
                qDebug()<<"ReadTable"<<i<<j<<ui->tableWidget->item(i,j)->text();
            }
        }
        ui->tableWidget->update();
        file.close();
        return true;
}

bool Setting::WriteTable(){

        QFile file("settingconfig");
        if (!file.open(QFile::WriteOnly | QFile::Text)){
            qDebug() << "WriteTable Error: cannot open file";
            return false;
        }
        qDebug()<<"WriteTable";
        QDataStream out(&file);
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {

                qDebug()<<i<<j<<ui->tableWidget->item(i,j);
                ui->tableWidget->item(i,j)->write(out);
            }
        }

        file.close();
        return true;
}

void Setting::onHeaderClicked(int index)
{
    if(2 ==index)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            QColor qc=QColor::fromHsl(rand()%360,rand()%256,rand()%200);

            ui->tableWidget->item(i,index)->setBackgroundColor(qc);
        }
    }
}
void Setting::onHeaderDoubleClicked(int index)
{
    if(2 ==index)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            QColor qc=QColor(255,255,255);

            ui->tableWidget->item(i,index)->setBackgroundColor(qc);
        }
    }
}
void Setting::on_pushButton_2_clicked()
{
    WriteTable();
}


void Setting::on_tableWidget_cellClicked(int row, int column)
{
    if(column == 2)
    {
        QColor color = QColorDialog::getColor(Qt::red, this);
        ui->tableWidget->item(row,2)->setBackgroundColor(color);
    }
}

void Setting::on_tableWidget_cellChanged(int row, int column)
{
        bool valid;
        QString string = ui->tableWidget->item(row,column)->text();
        DeviceSignal *signal = device_system->device_vector.at(row/6)->signal_vector.at(row%6);
        if(2 == column) signal->SetSignalColor(ui->tableWidget->item(row,column)->backgroundColor());
        if(3 == column) signal->SetSignalName(string.trimmed());
        if(column>3)
        {
            double number = string.toDouble(&valid);

            if(valid &&signal->SetUnitVol(column-3,number));

            else ui->tableWidget->item(row,column)->setText("0");
    }
}

void Setting::on_pushButton_3_clicked()
{
    ReadTable();
}

void Setting::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    //向下同步
    int type= item->type();
    int type_parent =  item->parent()->type();
    if(type== 1000)
    {
        for(int i=0;i<item->childCount();i++)
        {
            item->child(i)->setCheckState(0,item->checkState(0));
        }

    }
    //写入状态
    else
    {
        bool status = item->checkState(0)==Qt::Checked? true:false;
        if(type/100>0)
        {
            //设备使能
            device_system->device_vector.at(type%100)->SetDeviceStatus(status);
            if(status)
            {
                for(int i =0; i< item->childCount();i++)
                {
                    item->child(i)->setFlags(item->child(i)->flags()| Qt::ItemIsEnabled);
                }
            }
            else
            {

                for(int i =0; i< item->childCount();i++)
                {
                    item->child(i)->setFlags(item->child(i)->flags()& (~Qt::ItemIsEnabled) );
                }
            }
        }
        //信号使能
        else
        {
            if(type%10<6)
            {
                device_system->device_vector.at(type/10)->signal_vector.at(type%10)->SetSignalStatus(status);
                qDebug()<<"信号使能"<<type/10<<type%10;
            }
            if(type%10==6 ||type%10==7)
            {
                device_system->device_vector.at(type/10)->can_vector.at(type%10-6)->SetSignalStatus(status);
            }
            if(type%10==8)
            {
                device_system->device_vector.at(type_parent/10)->signal_vector.at(type_parent%10)->SetIVStatus(status);
            }
            if(type%10==9)
            {
                device_system->device_vector.at(type_parent/10)->can_vector.at(type_parent%10-6)->SetBaudRate(status);
                qDebug()<<"CAN STATUS"<<type_parent/10<<type_parent%10-6<<status;
            }
        }
    }
}

void Setting::on_spinBox_valueChanged(int arg1)
{
    device_system->SetFilterLength(arg1);
    qDebug()<<"on_spinBox_valueChanged"<<arg1;
}

void Setting::on_itemChanged(QStandardItem *item)
{
    QModelIndex index = theModel->indexFromItem(item);
    if(index.column() == 0)
    {
       int row = index.row();
       bool status;
       int device = theModel->item(row,1)->text().toInt(&status,10);
       int channel = theModel->item(row,2)->text().toInt(&status,10);
       uint filter_id = theModel->item(row,3)->text().toUInt(&status,16);

       QColor color = theModel->item(row,4)->background().color();
       QString name = theModel->item(row,5)->text();
       QString express_str = theModel->item(row,6)->text().toUpper();
       qDebug()<<"filter_id"<<filter_id<<theModel->item(row,3)->text();
        if(item->checkState() == Qt::Checked)
        {
            if( device!=0 && channel!=0 && filter_id!=0)
            {
                if(device_system->device_vector.at(device-1)->can_vector.at(channel-1)->AddFilter(filter_id, color,name,express_str))
                for(int j=1;j<7;j++) theModel->item(row,j)->setEditable(false);
                else  theModel->item(row,0)->setCheckState(Qt::Unchecked);
                qDebug()<<device<<channel<<device_system->device_vector.at(device-1)->can_vector.at(channel-1)->filter_list.size();
            }
            else
            {
                for(int j=1;j<7;j++) theModel->item(row,j)->setEditable(true);
                theSelection->selectedRows(row);
                theModel->item(row,0)->setCheckState(Qt::Unchecked);
            }
        }
        else
        {
             if( device!=0 && channel!=0 && filter_id!=0)
             {
                 for(int j=1;j<7;j++) theModel->item(row,j)->setEditable(true);
                  device_system->device_vector.at(device-1)->can_vector.at(channel-1)->RemoveFilter(color,name,express_str);
                 qDebug()<<device<<channel<<device_system->device_vector.at(device-1)->can_vector.at(channel-1)->filter_list.size();
             }
        }
    }
}
void Setting::on_pushButton_add_1_clicked()
{//插入行

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

void Setting::on_pushButton_add_2_clicked()
{
    QList<QStandardItem*>    aItemList;  //QStandardItem的列表类
    QStandardItem   *aItem;
    aItem=new QStandardItem("使能"); //新建一个QStandardItem
    aItem->setCheckable(true);
    aItem->setEditable(false);
    aItemList<<aItem;//添加到列表类
    for(int j=1;j<theModel_2->columnCount();j++)
    {
        aItem=new QStandardItem(); //新建一个QStandardItem
        aItem->setSelectable(false);
        aItemList<<aItem;//添加到列表类
    }
    theModel_2->insertRow(theModel_2->rowCount(),aItemList); //插入一行，需要每个Cell的Item
    QModelIndex curIndex=theModel_2->index(theModel_2->rowCount()-1,0);//创建最后一行的ModelIndex
    theSelection_2->clearSelection();//清空选择项
    theSelection_2->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择行
}

void Setting::on_pushButton_remove_1_clicked()
{
    QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引

    if (curIndex.row()==theModel->rowCount()-1)//最后一行
        theModel->removeRow(curIndex.row()); //删除最后一行
    else
    {
        theModel->removeRow(curIndex.row());//删除一行，并重新设置当前选择行
        theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}
void Setting::on_pushButton_remove_2_clicked()
{
    QModelIndex curIndex=theSelection_2->currentIndex();//获取当前选择单元格的模型索引

    if (curIndex.row()==theModel_2->rowCount()-1)//最后一行
        theModel_2->removeRow(curIndex.row()); //删除最后一行
    else
    {
        theModel_2->removeRow(curIndex.row());//删除一行，并重新设置当前选择行
        theSelection_2->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}


void Setting::on_tableView_clicked(const QModelIndex &index)
{

    if(index.column()==4  &&theModel->item(index.row(),0)->checkState()==Qt::Unchecked)
    {
        QColor color = QColorDialog::getColor(Qt::red, this);
        QBrush brush(color);
        theModel->setData(index,color,Qt::BackgroundColorRole);
    }
}

void Setting::on_pushButton_update_1_clicked()
{

    emit can_filter_update();
}
