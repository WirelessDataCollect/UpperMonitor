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
#include<QDateTime>
#include<QRegExp>
Setting::Setting(DeviceSystem *system,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    device_system = system;
    ui->setupUi(this);

    //TabelInit();
    QString current_path = QCoreApplication::applicationDirPath();
    ui->frame->setMaximumWidth(300);
    TabelViewInit();
    TreeInit();
    ReadTableView();
}

Setting::~Setting()
{
    WriteTableView();
    delete ui;

}

void Setting::TreeInit()
{
    QStringList headers;
    headers << QStringLiteral("终端使能");
    ui->treeWidget->setHeaderLabels(headers);

    QTreeWidgetItem *item = new QTreeWidgetItem(1000);
    item->setText(0,"采集终端");

    item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setCheckState(0,Qt::Unchecked);
    ui->treeWidget->addTopLevelItem(item);

    for(int i=0;i<5;i++)
    {
        QTreeWidgetItem *item_device = new QTreeWidgetItem(100*i);
        item_device->setText(0,"终端"+QString::number(i+1));
        item_device->setFlags(item_device->flags() | Qt::ItemIsUserCheckable);
        item_device->setCheckState(0,Qt::Unchecked);
        item->addChild(item_device);

        for(int j=0;j<2;j++)
        {
            QTreeWidgetItem *item_can = new QTreeWidgetItem(100*i+(j+1)*10);
            item_can->setText(0,"CAN通道"+QString::number(j+1));
            item_can->setFlags(item_can->flags() | Qt::ItemIsUserCheckable);
            item_can->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_can);

            QTreeWidgetItem *item_canbaud_1 = new QTreeWidgetItem(100*i+(j+1)*10+1);
            item_canbaud_1->setText(0,"500K");
            item_canbaud_1->setFlags(item_can->flags() | Qt::ItemIsUserCheckable);
            item_canbaud_1->setCheckState(0,Qt::Checked);
            item_can->addChild(item_canbaud_1);

            QTreeWidgetItem *item_canbaud_2 = new QTreeWidgetItem(100*i+(j+1)*10+2);
            item_canbaud_2->setText(0,"250K");
            item_canbaud_2->setFlags(item_canbaud_2->flags() | Qt::ItemIsUserCheckable);
            item_canbaud_2->setCheckState(0,Qt::Unchecked);
            item_can->addChild(item_canbaud_2);
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
   // ui->tableView->resizeColumnsToContents();
   ui->tableView->horizontalHeader()->setStretchLastSection(true);

    combox_delegate_1.combox_list.append("1");
    combox_delegate_1.combox_list.append("2");
    combox_delegate_1.combox_list.append("3");
    combox_delegate_1.combox_list.append("4");
    combox_delegate_1.combox_list.append("5");
    ui->tableView->setItemDelegateForColumn(1,&combox_delegate_1);  //测深，整数
    combox_delegate_2.combox_list.append("1");
    combox_delegate_2.combox_list.append("2");
    ui->tableView->setItemDelegateForColumn(2,&combox_delegate_2);

    theModel_2 = new QStandardItemModel(0,5,this);
    theSelection_2 = new QItemSelectionModel(theModel_2);//Item选择模型
    headers.clear();
    headers << QStringLiteral(" 时间 ")<<QStringLiteral(" 终端 ")<<QStringLiteral(" 通道 ")<<QStringLiteral("  标识符  ")<<QStringLiteral("    数据帧    ");
    theModel_2->setHorizontalHeaderLabels(headers);
    ui->tableView_2->setModel(theModel_2); //设置数据模型
    ui->tableView_2->setSelectionModel(theSelection_2);//设置选择模型
    ui->tableView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

    connect(this->theModel,SIGNAL(itemChanged(QStandardItem *)),this, SLOT(on_itemChanged(QStandardItem *)));

    theModel_3 = new QStandardItemModel(0,7,this);
    theSelection_3 = new QItemSelectionModel(theModel_3);//Item选择模型
    headers.clear();
    headers << QStringLiteral("终端")<<QStringLiteral("")<<QStringLiteral("使能")<<QStringLiteral("颜色")<<QStringLiteral("模式")<<QStringLiteral("名称")<<QStringLiteral("表达式")<<QStringLiteral("数量");
    theModel_3->setHorizontalHeaderLabels(headers);
    ui->tableView_3->setModel(theModel_3);              //设置数据模型
    ui->tableView_3->setSelectionModel(theSelection_3);//设置选择模型
    ui->tableView_3->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectItems);
    connect(this->theModel_3,SIGNAL(itemChanged(QStandardItem *)),this, SLOT(model3_itemChanged(QStandardItem *)));


    QHeaderView *headerGoods =  ui->tableView_3->horizontalHeader();
    //connect(headerGoods, SIGNAL(sectionClicked(int)), this, SLOT(on_section_3Clicked(int)));

    combox_delegate_3.combox_list.append("电压模式");
    combox_delegate_3.combox_list.append("电流模式");

    ui->tableView_3->setItemDelegateForColumn(4,&combox_delegate_3);

    QList<QStandardItem*>    aItemList;  //QStandardItem的列表类
    QStandardItem   *aItem;
    QStringList device = {"一","二","三","四","五","六"};

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<6;j++)
        {
            aItemList.clear();
            aItem=new QStandardItem("终端"+device.at(i)); //新建一个QStandardItem

            aItem->setEditable(false);
            aItemList<<aItem;
            if(j<4)
            {
                aItem=new QStandardItem("模拟通道"+device.at(j)); //新建一个QStandardItem
                aItem->setEditable(false);
                aItemList<<aItem;
            }
            else
            {
                aItem=new QStandardItem("数字通道"+device.at(j-4)); //新建一个QStandardItem
                aItem->setEditable(false);
                aItemList<<aItem;
            }
            aItem=new QStandardItem("使能"); //新建一个QStandardItem
            aItem->setCheckable(true);
            aItem->setEditable(false);
            aItem->setSelectable(false);
            aItemList<<aItem;

            aItem=new QStandardItem(); //color
            aItem->setData(QColor(Qt::white),Qt::BackgroundColorRole);
            aItem->setEditable(false);
            aItem->setSelectable(false);
            aItemList<<aItem;

            if(j<4)
            {
                aItem=new QStandardItem("电压模式"); //采集模式
                aItem->setSelectable(false);
                aItemList<<aItem;
            }
            else
            {
                aItem=new QStandardItem();
                aItem->setEditable(false);
                aItem->setSelectable(false);
                aItemList<<aItem;

            }


            aItem=new QStandardItem("通道"+device.at(j)+"名称"); //新建一个QStandardItem
            aItemList<<aItem;

            aItem=new QStandardItem("X"); //新建一个QStandardItem
            aItemList<<aItem;

            aItem=new QStandardItem("0"); //新建一个QStandardItem
            aItem->setEditable(false);
            aItemList<<aItem;
            theModel_3->appendRow(aItemList);
        }
        ui->tableView_3->setSpan(i*6,0,6,1);
    }
}


void Setting::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    //向下同步
    int type= item->type();
    // int type_parent =  item->parent()->type();
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
        if(type%100 == 0)  device_system->device_vector.at(type/100)->SetDeviceStatus(status);
        else
        {
            if(type%10 == 0) device_system->device_vector.at(type/100)->can_vector.at(type/10%10-1)->SetSignalStatus(status);
            else
            {
                if(type%10 ==1)
                {
                    qDebug()<<"DEVICE"<<type/100<<"CAN"<<type/10%10-1;
                    device_system->device_vector.at(type/100)->can_vector.at(type/10%10-1)->SetBaudRate(status);

                    if(status) item->parent()->child(1)->setCheckState(0,Qt::Unchecked);
                    else item->parent()->child(1)->setCheckState(0,Qt::Checked);
                }
                if(type%10 ==2)
                {
                    if(status) item->parent()->child(0)->setCheckState(0,Qt::Unchecked);
                    else item->parent()->child(0)->setCheckState(0,Qt::Checked);
                }

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

void Setting::model3_itemChanged(QStandardItem *item)
{
    QModelIndex index = theModel_3->indexFromItem(item);
    if(index.column() == 2)
    {
        int row = index.row();
        QColor color = theModel_3->item(row,3)->background().color();
        QString model = theModel_3->item(row,4)->text();
        QString name = theModel_3->item(row,5)->text();
        QString express_str = theModel_3->item(row,6)->text().toUpper();
        int device = row/6;
        int channel = row%6;
        bool vol_enable;
        if(model == QString("电压模式")) vol_enable = true;
        else vol_enable = false;
        qDebug()<<"model"<<model<<vol_enable;
        if(item->checkState() == Qt::Checked)
        {
            if(device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->isExpreesionValue(express_str))
            {
                device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->color = color;
                device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->name = name;
                device_system->device_vector.at(device)->signal_vector.at(channel)->SetIVStatus(vol_enable);
                device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->show_enable = true;
                for(int j=4;j<7;j++) theModel_3->item(row,j)->setEditable(false);
            }
            else
            {
                item->setCheckState(Qt::Unchecked);
            }
        }
        else
        {
            for(int j=4;j<7;j++) theModel_3->item(row,j)->setEditable(true);
            device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->show_enable = false;
        }
    }
}


bool Setting::ReadTableView(QString file_name)
{
    if(file_name.isEmpty()) file_name= "configure.txt";

    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "ReadTabelView Error: cannot open file";
        return false;
    }
    qDebug() << "ReadTabelView from configure.txt begin----------------------------- ";
    QStringList fFileContent;
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd())
    {
        QString str = in.readLine();
        fFileContent.append(str);
    }
    file.close();
    QString linetext;
    QStringList linetextlist;
    Qt::CheckState status;

    for(int i=0;i<fFileContent.count();i++)
    {
        linetext = fFileContent.at(i);
        if(linetext.contains("Device configure start"))
        {
            i++;
            for(int j=0;j<5;j++)
            {
                i++;
                linetext = fFileContent.at(i);
                linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);

                status = Qt::Unchecked;
                if(linetextlist.at(1) =="1") status =Qt::Checked;
                ui->treeWidget->topLevelItem(0)->child(j)->setCheckState(0,status);

                status = Qt::Unchecked;
                if(linetextlist.at(2) == "1") status =Qt::Checked;
                ui->treeWidget->topLevelItem(0)->child(j)->child(0)->setCheckState(0,status);

                status = Qt::Unchecked;
                if(linetextlist.at(3) == "50") status =Qt::Checked;
                ui->treeWidget->topLevelItem(0)->child(j)->child(0)->child(0)->setCheckState(0,status);

                status = Qt::Unchecked;
                if(linetextlist.at(4) == "1") status =Qt::Checked;
                ui->treeWidget->topLevelItem(0)->child(j)->child(1)->setCheckState(0,status);

                status = Qt::Unchecked;
                if(linetextlist.at(5) == "50") status =Qt::Checked;
                ui->treeWidget->topLevelItem(0)->child(j)->child(1)->child(0)->setCheckState(0,status);
            }

        }
        if(linetext.contains("CAN configure start"))
        {
            on_pushButton_clear_1_clicked(); //clear the table

            i=i+2;
            linetext = fFileContent.at(i);
            linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
            int row = linetextlist.at(0).toInt();
            i++;
            for(int j=0;j<row;j++)
            {
                i++;
                linetext = fFileContent.at(i);
                linetextlist = linetext.split(QRegExp(",\\s+"),QString::KeepEmptyParts);
                on_pushButton_add_1_clicked();

                for(int k=1;k<theModel->columnCount();k++)
                {
                    if(k==4) theModel->item(j,k)->setData(QColor(linetextlist.at(k)),Qt::BackgroundColorRole);
                    else theModel->item(j,k)->setText(linetextlist.at(k));
                }
                status = Qt::Unchecked;
                if(linetextlist.at(0) == "true")  status = Qt::Checked;
                theModel->item(j,0)->setCheckState(status);
            }
        }

        if(linetext.contains("Signal configure start"))
        {
            i=i+2;
            linetext = fFileContent.at(i);
            linetextlist = linetext.split(QRegExp(",\\s+"),QString::SkipEmptyParts);
            int row = linetextlist.at(0).toInt();
            i++;
            for(int j =0;j<row;j++)
            {

                i++;

                linetext = fFileContent.at(i);
                linetextlist = linetext.split(QRegExp(",\\s+"),QString::KeepEmptyParts);

                for(int k = 4;k<theModel_3->columnCount();k++)
                {
                    qDebug()<<k;
                    theModel_3->item(j,k)->setText(linetextlist.at(k));
                }

                theModel_3->item(j,3)->setData(QColor(linetextlist.at(3)),Qt::BackgroundColorRole);

                status = Qt::Unchecked;
                if(linetextlist.at(2) == "true")  status = Qt::Checked;
                theModel_3->item(j,2)->setCheckState(status);
            }
        }
    }
     qDebug() << "ReadTabelView from configure.txt end----------------------------- ";
    return true;
}

bool Setting::WriteTableView(QString file_name)
{
    if(file_name.isEmpty()) file_name = "configure.txt";
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        qDebug() << "WriteTable Error: cannot open file";
        return false;
    }

    QString str;
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out<<"Configure File \n";
    out<<"Save Time: "<<QDateTime::currentDateTime().toString(Qt::ISODate)<<"\n";
    out<<"Test Time: "<<device_system->test_time.toString(Qt::ISODate)<<"\n";
    out<<"\n";
    qDebug()<<"WriteTable--------------------------------";

    out<<"Device configure start---------------------------------------\n";
    str =  "终端"; out<<str; out<<",    ";
    str = "使能"; out<<str; out<<",    ";
    str = "CAN1使能";out<<str; out<<",    ";
    str = "CAN1波特率"; out<<str; out<<",    ";
    str = "CAN2使能";out<<str; out<<",    ";
    str = "CAN2波特率"; out<<str<<"\n";


    for(int i=0;i<5;i++)
    {
        out<<i+1<<",    "<<device_system->device_vector.at(i)->setting_status<<",    ";
        out<<device_system->device_vector.at(i)->can_vector.at(0)->show_enable<<",    "<<int(device_system->device_vector.at(i)->can_vector.at(0)->baud_rate)<<",    ";
        out<<device_system->device_vector.at(i)->can_vector.at(1)->show_enable<<",    "<<int(device_system->device_vector.at(i)->can_vector.at(1)->baud_rate);
        out<<"\n";
    }
    out<<"Device configure end---------------------------------------\n";
    out<<"\n";

    // tableview
    out<<"CAN configure start---------------------------------------"<<"\n";
    out<<"Table Size:\n"<<theModel->rowCount()<<",    "<<theModel->columnCount()<<"\n";

    str =  "状态"; out<<str; out<<",    ";
    str =  "终端"; out<<str; out<<",    ";
    str =  "通道"; out<<str; out<<",    ";
    str =  "ID(hex)";  out<<str; out<<",    ";
    str =  "颜色"; out<<str; out<<",    ";

    str =  "名称"; out<<str; out<<",    ";
    str =  "表达式"; out<<str; out<<",    ";
    str =  "数量"; out<<str;
    out<<"\n";
    QString status;


    for(int i=0;i<theModel->rowCount();i++)
    {
        if(theModel->item(i,0)->checkState() == Qt::Checked) status = "true";
        else status = "false";
        out<<status;
        for(int j=1;j<theModel->columnCount();j++)
        {
            out<<",    ";
            if(j== 4)  out<< theModel->item(i,j)->data(Qt::BackgroundColorRole).toString();
            else  out<< theModel->item(i,j)->text();
        }
        out<<"\n";
    }
    out<<"CAN configure end---------------------------------------\n";
    out<<"\n";

    out<<"Signal configure start---------------------------------------"<<"\n";
    out<<"Table Size:\n"<<theModel_3->rowCount()<<",    "<<theModel_3->columnCount()<<"\n";
    str =  "终端"; out<<str; out<<",    ";
    str =  "通道"; out<<str; out<<",    ";
    str =  "状态"; out<<str; out<<",    ";

    str =  "颜色"; out<<str; out<<",    ";
    str =  "模式"; out<<str; out<<",    ";
    str =  "名称"; out<<str; out<<",    ";
    str =  "表达式"; out<<str; out<<",    ";
    str =  "数量"; out<<str;
    out<<"\n";

    for(int i=0;i<theModel_3->rowCount();i++)
    {
        if(theModel_3->item(i,2)->checkState() == Qt::Checked) status = "true";
        else status = "false";
        for(int j=0;j<theModel_3->columnCount();j++)
        {

            if(j==2)   out<<status;
            else if(j== 3)  out<< theModel_3->item(i,j)->data(Qt::BackgroundColorRole).toString();
            else  out<< theModel_3->item(i,j)->text();
            out<<",    ";
        }
        out<<"\n";
    }
    out<<"Signal configure end---------------------------------------";
    out<<"\n";
    out.flush();
    file.close();
    return true;
}
void Setting::on_pushButton_add_1_clicked()
{
    //插入行

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
        if(j==4) aItem->setData(QColor(Qt::white),Qt::BackgroundColorRole);
    }
    theModel->insertRow(theModel->rowCount(),aItemList); //插入一行，需要每个Cell的Item
    QModelIndex curIndex=theModel->index(theModel->rowCount()-1,0);//创建最后一行的ModelIndex
    theSelection->clearSelection();//清空选择项
    theSelection->setCurrentIndex(curIndex,QItemSelectionModel::Select);//设置刚插入的行为当前选择行
}


void Setting::on_pushButton_remove_1_clicked()
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


void Setting::on_pushButton_remove_2_clicked()
{
    if(theModel_2->rowCount() == 0) return;
    QModelIndex curIndex=theSelection_2->currentIndex();//获取当前选择单元格的模型索引

    if (curIndex.row()==theModel_2->rowCount()-1)//最后一行
        theModel_2->removeRow(curIndex.row()); //删除最后一行
    else
    {
        theModel_2->removeRow(curIndex.row());//删除一行，并重新设置当前选择行
        theSelection_2->setCurrentIndex(curIndex,QItemSelectionModel::Select);
    }
}



void Setting::on_tableView_clicked(const QModelIndex &index)//CAN颜色点击
{


    if(index.column()==4  &&theModel->item(index.row(),0)->checkState()==Qt::Unchecked)
    {
        QColor color = QColorDialog::getColor(Qt::red, this);
        QBrush brush(color);
        theModel->setData(index,color,Qt::BackgroundColorRole);
    }
}


void Setting::on_tableView_3_clicked(const QModelIndex &index) //信号颜色点击
{

    if(index.column()==3)
    {
        QColor color = QColorDialog::getColor(Qt::red, this);
        QBrush brush(color);
        theModel_3->setData(index,color,Qt::BackgroundColorRole);
        int row = index.row();
        int device = row/6;
        int channel = row%6;
        device_system->device_vector.at(device)->signal_vector.at(channel)->signal_data->color = color;
    }
}

void Setting::on_pushButton_clear_1_clicked()
{
    for(int i=0;i<theModel->rowCount();i++)
    {
        theModel->item(i,0)->setCheckState(Qt::Unchecked);
    }
    theModel->removeRows(0,theModel->rowCount());
}

void Setting::on_checkBox_enable_clicked(bool checked)
{
    device_system->ShowCanData(checked);
}

void Setting::on_pushButton_clear_2_clicked()
{
    theModel_2->removeRows(0,theModel_2->rowCount());
}

void Setting::on_addcanrow(double time, int device, int channel,int id, QByteArray data)
{
    QList<QStandardItem*>    aItemList;  //QStandardItem的列表类
    QStandardItem   *aItem;

    aItem = new QStandardItem(QString::number(time,'f',3));
    aItemList.append(aItem);

    aItem = new QStandardItem(QString::number(device));
    aItemList.append(aItem);

    aItem = new QStandardItem(QString::number(channel));
    aItemList.append(aItem);


    aItem = new QStandardItem(QString::number(id,16));
    aItemList.append(aItem);

    aItem = new QStandardItem(QString(data.toHex()));
    aItemList.append(aItem);
    theModel_2->appendRow(aItemList);
    ui->tableView_2->resizeColumnsToContents();
}
