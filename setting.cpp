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

  // ReadTable();
  // ColorSet(ui->tableWidget);
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

//        QTreeWidgetItem *item_analog = new QTreeWidgetItem(100);
//        item_analog->setText(0,"模拟通道");
//        item_analog->setFlags(item->flags()&(~Qt::ItemIsEnabled));

//        item_analog->setCheckState(0,Qt::Unchecked);
//        item_device->addChild(item_analog);
        for(int j=0;j<4;j++)
        {
            QTreeWidgetItem *item_signal = new QTreeWidgetItem(10*i+j);
            item_signal->setText(0,"模拟通道"+QString::number(j+1));
            item_signal->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_signal);

            QTreeWidgetItem *vol_curr_1 = new QTreeWidgetItem(10*i+j+6);
            vol_curr_1->setText(0,"电压模式");
            vol_curr_1->setFlags(vol_curr_1->flags() | Qt::ItemIsUserCheckable);
            vol_curr_1->setCheckState(0,Qt::Unchecked);
            item_signal->addChild(vol_curr_1);
        }
        for(int j=0;j<2;j++)
        {
            QTreeWidgetItem *item_signal = new QTreeWidgetItem(10*i+j+4);
            item_signal->setText(0,"数字通道"+QString::number(j+1));
            item_signal->setFlags(item_signal->flags() | Qt::ItemIsUserCheckable);
            item_signal->setCheckState(0,Qt::Unchecked);
            item_device->addChild(item_signal);
        }
    }


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

       // ReadTable();
    }

//void Setting::TableDeviceEnable()
//{


//}

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
            //QString msg = QString("r: %1, g: %2, b: %3").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue()));
            //QMessageBox::information(NULL, "Selected color", msg);

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
   // qDebug()<<"on_tableWidget_cellChanged"<<row<<column<<signal->line_collor<<device_system->device_vector.at(row/6)->signal_vector.at(row%6)->signal_name<<signal->min_v<<signal->max_v<<signal->min_uint<<signal->max_unit;
}


void Setting::on_pushButton_3_clicked()
{
    ReadTable();
}

void Setting::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    //向下同步
    int type= item->type();
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
            else device_system->device_vector.at(type/10)->signal_vector.at(type%10 - 6)->SetIVStatus(status);
        }
    }
}

void Setting::on_spinBox_valueChanged(int arg1)
{
    device_system->SetFilterLength(arg1);
    qDebug()<<"on_spinBox_valueChanged"<<arg1;
}
