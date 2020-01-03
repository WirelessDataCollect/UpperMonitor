#pragma execution_character_set("utf-8")
#include "mainwin.h"
#include "ui_mainwin.h"
#include<QDebug>
#include<QGridLayout>
#include<QInputDialog>
#include<QMessageBox>
#include<QFileDialog>
#include<QDialogButtonBox>
#include<QFormLayout>
#include"md5.h"
#include<QThread>
//#include"login.h"
MainWin::MainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);
    device_system = new DeviceSystem();
//    login_widget = new Login(this);

    settingui = new Setting(device_system,this);
    settingui->setWindowFlags(settingui->windowFlags() | Qt::Window);
    calibration_dialog = new Calibration(device_system);
    //chart_widgt
    chart_widget = new chartswidgt(device_system);
    QGridLayout *layout= new QGridLayout();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(chart_widget);
    ui->widget_chart->setLayout(layout);

    //tabelview
    standard_model = new QStandardItemModel;
    standard_selection = new QItemSelectionModel(standard_model);//Item选择模型
    ui->tableView->setModel(standard_model);
    ui->tableView->setSelectionModel(standard_selection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    standard_model->setRowCount(0);
    QStringList headerList;
    headerList<<QString("时间")<<QString("颜色")<<QString("名称")<<QString("测量值");
    standard_model->setHorizontalHeaderLabels(headerList);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    // ui->tableView->resizeColumnsToContents();
    ui->tableView->setMaximumWidth(280);
    ui->tableView->setVisible(false);


    //widget_chart
connect(device_system,SIGNAL(UpdataTestName(QString)),this,SLOT(UpdataTestName(QString)));
connect(device_system,SIGNAL(UpdataTestTime(QString)),this,SLOT(UpdataTestTime(QString)));
connect(device_system,SIGNAL(UpdataTestDeep(QString)),this,SLOT(UpdataTestDeep(QString)));
connect(device_system, SIGNAL(UpdataDocsnames(QList<QString>,QList<QString>)),this,SLOT(on_UpdataDocsnames(QList<QString>,QList<QString>)));

    //历史测试数据初始化
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setCalendarPopup(true);
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->frame_2->setMaximumWidth(600);
    ui->frame_2->setMinimumWidth(400);

    //历史记录
    standard_model_2 = new QStandardItemModel;
    standard_selection_2 = new QItemSelectionModel(standard_model_2);//Item选择模型
    ui->tableView_2->setModel(standard_model_2);
    ui->tableView_2->setSelectionModel(standard_selection_2);
    ui->tableView_2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    standard_model_2->setRowCount(0);
    standard_model_2->setColumnCount(2);
    QStringList headerList_2;
    headerList_2<<QString("测试名称")<<QString("时间");
    standard_model_2->setHorizontalHeaderLabels(headerList_2);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

    //widget_device
    ui->widget_device->setMaximumHeight(180);
    online_group = new QButtonGroup();

    online_group->addButton(ui->radioButton,0);
    online_group->addButton(ui->radioButton_2,1);
    online_group->addButton(ui->radioButton_3,2);
    online_group->addButton(ui->radioButton_4,3);
    online_group->addButton(ui->radioButton_5,4);
    online_group->addButton(ui->radioButton_11,5);

    online_group->setExclusive(false);

    enable_group =new QButtonGroup();
    enable_group->addButton(ui->radioButton_6,0);
    enable_group->addButton(ui->radioButton_7,1);
    enable_group->addButton(ui->radioButton_8,2);
    enable_group->addButton(ui->radioButton_9,3);
    enable_group->addButton(ui->radioButton_10,4);
    enable_group->setExclusive(false);

    //定时器
    timer =new QTimer();
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_DeviceStatus()));

    //action
    ui->action->setEnabled(true);
    ui->action_3->setDisabled(true);
    connect(chart_widget,SIGNAL(AddPointData(QString,QColor,QString,QString)),this,SLOT(on_AddPointData(QString,QColor,QString,QString)));

    connect(standard_selection_2,SIGNAL(selectionChanged(const QItemSelection, const QItemSelection )),this,SLOT(on_SelectionChanged(const QItemSelection, const QItemSelection)));

     for(int i=0;i<device_system->device_num;i++)
     {
         connect(device_system->device_vector.at(i),SIGNAL(addcanrow(double, int , int,int, QByteArray)),settingui,SLOT(on_addcanrow(double, int , int,int, QByteArray)));
     }
     connect(device_system, SIGNAL(SaveConfigureFile(QString)),settingui, SLOT(WriteTableView(QString)));
     connect(device_system, SIGNAL(LoadConfigureFile(QString)),settingui, SLOT(ReadTableView(QString)));

     connect(device_system, SIGNAL(testconfigureshow(QString)),this, SLOT(on_testconfigureshow(QString)));
}

MainWin::~MainWin()
{

    delete  device_system;
    if(help_process != nullptr)help_process->kill();
    delete settingui;
    delete ui;
    delete chart_widget;
    delete help_process;
}

void MainWin::UpdataTestName(QString str)
{
    ui->lineEdit->setText(str);
}
void MainWin::UpdataTestTime(QString str)
{
    ui->lineEdit_2->setText(str);
}
void MainWin::UpdataTestDeep(QString str)
{
    ui->lineEdit_3->setText(str);
}
void MainWin::on_action_4_triggered()
{
    settingui->show();
}

void MainWin::on_action_5_triggered(bool checked)
{
    //绘图窗口放大
    qDebug()<<checked;
    if(checked)
    {
        ui->frame_2->hide();
        ui->widget_device->hide();
    }
    else
    {
        ui->frame_2->show();
        ui->widget_device->show();
    }
}

void MainWin::on_action_triggered()
{
    QDialog dialog(this);

  //  dialog.setAttribute(Qt::WA_DeleteOnClose);

    QFormLayout form(&dialog);
    dialog.setWindowTitle("新建实验");

    QString value1 = QString("实验名称: ");
    QString test_name("实验1");
    QLineEdit *line_edit = new QLineEdit("实验1");
    form.addRow(value1, line_edit);

    QString value2 = QString("测试时长(s): ");
    QSpinBox *spinbox = new QSpinBox(&dialog);
    spinbox->setMaximum(1000000);
    form.addRow(value2, spinbox);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    form.setSizeConstraint(QLayout::SetFixedSize);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    if (dialog.exec() == QDialog::Accepted) {
        test_name = line_edit->text();
        int time = spinbox->value()*1000;
        ui->action->setDisabled(true);
        ui->action_3->setEnabled(true);
        //新建实验
        device_system->NewLocalTest(test_name);
        device_system->AutoStop(time);
    } 
}

void MainWin::on_action_3_triggered()
{
    //结束实验
    ui->action->setEnabled(true);
    ui->action_3->setDisabled(true);
    device_system->EndLocalTest();
}

void MainWin::on_action_6_toggled(bool checked)

{
    //取点
    chart_widget->GetSeriesPoint(checked);
}

void MainWin::on_action_7_triggered(bool checked)
{
    //删点
    deltablerow =checked;
    on_MovePointdata();
}
void MainWin::on_action_8_triggered()
{
    //导出数据
    QString curPath = QCoreApplication::applicationDirPath();
   // curPath = QDir::currentPath();
    QString dlgTile = "数据保存路径";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTile,curPath,QFileDialog::ShowDirsOnly);

    if(!selectedDir.isEmpty())
    {
        selectedDir+="/";
        selectedDir+=device_system-> test_name.split('/').at(0);
        QDir dir;
        if(!dir.exists(selectedDir)) dir.mkpath(selectedDir);
        QString data_file = selectedDir+"/"+"data.txt";
        QString configure_file = selectedDir+"/"+"configure.txt";
        device_system->SaveDataFile(data_file);
        settingui->WriteTableView(configure_file);
    }
}

void MainWin::on_pushButton_clicked()
{
    //查询历史
    QDate begin_date = ui->dateEdit->date();
    QDate end_date = ui->dateEdit_2->date();
    device_system->FindDocsNames(begin_date,end_date);
    emit FindDocsNames(begin_date,end_date);
    //device_system->FindDocs();
}

void MainWin::on_AddPointData(QString time,QColor color, QString name, QString value)
{
   ui->action_6->setChecked(false);
   if(standard_model->rowCount() ==0) ui->tableView->setVisible(true);
    qDebug()<<"AddPointData receive";
    QList<QStandardItem*> row;
    QStandardItem *item_time= new QStandardItem(time);
    QStandardItem *item_color= new QStandardItem();
    QBrush brush(color);
    item_color->setBackground(brush);
    QStandardItem *item_name= new QStandardItem(name);
    QStandardItem *item_value= new QStandardItem(value);
    row.append(item_time);
    row.append(item_color);
    row.append(item_name);
    row.append(item_value);
    standard_model->appendRow(row);
    ui->tableView->resizeColumnsToContents();
}

void MainWin::on_MovePointdata()
{
    QModelIndex cur_index = standard_selection->currentIndex();
    if(cur_index.row() == standard_model->rowCount()-1)
    {
        standard_model->removeRow(cur_index.row());
    }
    else
    {
        standard_model->removeRow(cur_index.row());
        standard_selection->setCurrentIndex(cur_index,QItemSelectionModel::Select);
    }
    if(standard_model->rowCount() ==0) ui->tableView->setVisible(false);
}

void MainWin::on_DeviceStatus()
{
    for(int i=0;i<device_system->device_num;i++)
    {
        bool status = device_system->device_vector.at(i)->online_status;
        online_group->buttons().at(i)->setChecked(status);
        status = device_system->device_vector.at(i)->actual_status;
        enable_group->button(i)->setChecked(status);
    }
    bool status = device_system->clock_device_status;
    online_group->buttons().at(5)->setChecked(status);


}

void MainWin::on_UpdataDocsnames(QList<QString> name,QList<QString> time)
{
    qDebug()<<"on_UpdataDocsnames"<<name.size();

    QList<QStandardItem*> item_column_name = standard_model_2->takeColumn(0);
    item_column_name.clear();
    QList<QStandardItem*> item_column_time = standard_model_2->takeColumn(0);
    item_column_time.clear();

    for(int i=0;i<name.size();i++)
    {
        QStandardItem *item_name = new QStandardItem();
        item_name->setText(name.at(i));
        item_column_name.append(item_name);

        QStandardItem *item_time = new QStandardItem();
        item_time->setText(time.at(i));
        item_column_time.append(item_time);
    }
    standard_model_2->appendColumn(item_column_name);
    standard_model_2->appendColumn(item_column_time);
}

void MainWin::on_SelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if(selected.indexes().isEmpty())return;
    int index = selected.indexes().at(0).row();
    device_system->FindDocs(index);
    standard_selection_2->clearSelection();
    qDebug()<<"current select"<< index;
}

void MainWin::on_action_9_triggered()
{
    //帮助文档
   // device_system->FindConfigureFile();
    qDebug()<<"HELP";
    if(help_process == nullptr) help_process = new QProcess();
   // QString exe("./assistant/assistant.exe");
    QString exe("./assistant.exe");
    QStringList params;
   // params << "-collectionFile" << "./assistant/assistant.qhc";
    params << "-collectionFile" << "./assistant.qhc";
    help_process->start(exe, params);
    if (!help_process->waitForStarted()) {
        QMessageBox::critical(0, QObject::tr("Tips"),
            QObject::tr("Unable to launch Qt Assistant (%1)").arg(exe));
         //qDebug()<<"HELPxxxxxxxxxxx";
    }
}

void MainWin::on_action_10_triggered()
{
    //导入数据
    QString curPath = QCoreApplication::applicationDirPath();
   // curPath = QDir::currentPath();
    QString dlgTile = "选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTile,curPath,QFileDialog::ShowDirsOnly);
    QString data_file = selectedDir+"/"+"data.txt";
    QString configure_file = selectedDir+"/"+"configure.txt";
    settingui->ReadTableView(configure_file);
    device_system->LoadDataFile(data_file);
}

void MainWin::on_action_2_triggered()
{
    //清屏清除数据
    device_system->ClearData();
}

void MainWin::on_action_13_triggered()
{
    //弹窗取点
   chart_widget->showDataDialog();
}

void MainWin::on_action_15_triggered()
{
    //dialog->setAttribute(Qt::WA_DeleteOnClose);
    //校准
    calibration_dialog->show();

     //device_system->RemoteTcpReset();
   //device_system->StopSendDocs();
}

void MainWin::on_action_11_triggered()
{
    //导入配置文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTile = "选择配置文件";
    QString configure_file =  QFileDialog::getOpenFileName(this,dlgTile,curPath,tr("txt (*.txt)"));

    if(!configure_file.isEmpty())settingui->ReadTableView(configure_file);
}

void MainWin::on_action_12_triggered()
{
    //导出配置文件
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTile = "配置文件保存路径";
    QString selectedDir = QFileDialog::getExistingDirectory(this,dlgTile,curPath,QFileDialog::ShowDirsOnly);
    if(!selectedDir.isEmpty())
    {
        QString configure_file = selectedDir+"/"+"configure.txt";
        settingui->WriteTableView(configure_file);
    }
}

void MainWin::on_action_16_triggered()
{
    //适应窗口
   chart_widget->XAxisAdapt();
}

void MainWin::on_testconfigureshow(QString str)
{
    qDebug()<<str;
    ui->plainTextEdit->setPlainText(str);
}

void MainWin::on_action_14_triggered(bool checked)
{
    //远程实时
   device_system->GetRtData(checked);
   if(checked) device_system->SetMaxDataLen(chart_widget->plot_size*2000);
   else device_system->SetMaxDataLen(0);
}
