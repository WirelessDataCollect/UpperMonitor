#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QVector>
#include<QStandardItemModel>
#include<QTableWidget>
#include <QXmlStreamWriter>
#include<QTreeWidget>

#include<QTreeWidgetItem>
#include "qwcomboboxdelegate.h"
class DeviceSystem;
namespace Ui {
class Setting;
}
class Device;

class Setting : public QWidget
{
    Q_OBJECT

public:
    Setting(DeviceSystem *system, QWidget *parent = nullptr);
    ~Setting();

    DeviceSystem *device_system;
signals:
    void can_filter_update();
public slots:
    void on_addcanrow(double time, int device, int channel,int id, QByteArray data);
    bool WriteTableView(QString file = "");
    bool ReadTableView(QString file = "");

private slots:



    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_add_1_clicked();

    void on_pushButton_remove_1_clicked();

    void on_pushButton_remove_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_3_clicked(const QModelIndex &index);


    void on_itemChanged(QStandardItem *item);
    void model3_itemChanged(QStandardItem *item);
   // void on_sectionClicked(int);

    void on_pushButton_clear_1_clicked();

    void on_checkBox_enable_clicked(bool checked);

    void on_pushButton_clear_2_clicked();



private:
    Ui::Setting *ui;
    void TreeInit();

    QStandardItemModel  *theModel;//数据模型
    QItemSelectionModel *theSelection;//Item选择模型

    QStandardItemModel  *theModel_2;//数据模型
    QItemSelectionModel *theSelection_2;//Item选择模型

    QStandardItemModel  *theModel_3;//数据模型
    QItemSelectionModel *theSelection_3;//Item选择模型

    void TabelViewInit();
    QWComboBoxDelegate combox_delegate_1;
    QWComboBoxDelegate combox_delegate_2;
    QWComboBoxDelegate combox_delegate_3;




};

#endif // SETTING_H
