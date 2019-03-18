#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QVector>
#include<QTableWidget>
#include <QXmlStreamWriter>
#include<QTreeWidget>

#include<QTreeWidgetItem>

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

private:
    Ui::Setting *ui;
    void TabelInit();
    void TreeInit();

};

#endif // SETTING_H
