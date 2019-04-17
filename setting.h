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
    bool ReadTable();
    bool WriteTable();
    DeviceSystem *device_system;
signals:
    void can_filter_update();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_tableWidget_cellChanged(int row, int column);

    void on_pushButton_3_clicked();


    void onHeaderClicked(int);
    void onHeaderDoubleClicked(int);


    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_add_1_clicked();

    void on_pushButton_remove_1_clicked();

    void on_pushButton_add_2_clicked();

    void on_pushButton_remove_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_update_1_clicked();
    void on_itemChanged(QStandardItem *item);

private:
    Ui::Setting *ui;
    void TabelInit();
    void TreeInit();

    QStandardItemModel  *theModel;//数据模型
    QItemSelectionModel *theSelection;//Item选择模型

    QStandardItemModel  *theModel_2;//数据模型
    QItemSelectionModel *theSelection_2;//Item选择模型
    void TabelViewInit();
    QWComboBoxDelegate combox_delegate_1;
    QWComboBoxDelegate combox_delegate_2;
    QWComboBoxDelegate combox_delegate_3;


};

#endif // SETTING_H
