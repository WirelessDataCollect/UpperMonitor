#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QWidget>
#include<QStandardItemModel>
#include<QItemSelectionModel>
#include<QtDebug>
#include<QString>
#include "devicesystem.h"
#include"signaldata.h"
namespace Ui {

class Calibration;
}

class Calibration : public QWidget
{
    Q_OBJECT

public:
    explicit Calibration(DeviceSystem *system,QWidget *parent = nullptr);
    ~Calibration();

private slots:
    void on_pushButton_add_1_clicked();

    void on_pushButton_remove_1_clicked();

    void on_pushButton_clear_1_clicked();
    void on_itemChanged(QStandardItem *item);

    void on_pushButton_clicked();

private:
    Ui::Calibration *ui;
    QStandardItemModel *theModel = nullptr;
    QItemSelectionModel *theSelection = nullptr;
    DeviceSystem *device_system = nullptr;

    void TableInit();
    double GetActualValue();
    QVector<double> GetAllActualValue();
    QVector<double> vx;
    QVector<double> vy;
    QVector<double> coeff;
};

#endif // CALIBRATION_H
