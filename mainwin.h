#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QButtonGroup>
#include<QTimer>
#include<QGroupBox>
#include<QDate>
#include<QStringListModel>
#include "setting.h"
#include"devicesystem.h"
#include"chartswidgt.h"
#include<QProcess>
#include"calibration.h"
namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWin(QWidget *parent = nullptr);
    ~MainWin();
    Setting *settingui =nullptr;
    DeviceSystem *device_system = nullptr;
    chartswidgt *chart_widget = nullptr;
    QStandardItemModel *standard_model = nullptr;
    QItemSelectionModel *standard_selection = nullptr;

    QStandardItemModel *standard_model_2 = nullptr;
    QItemSelectionModel *standard_selection_2 = nullptr;


    bool deltablerow = false;
    void on_MovePointdata();
    QButtonGroup *online_group;
    QButtonGroup *enable_group;

private slots:
    void UpdataTestName(QString);
    void UpdataTestTime(QString);
    void UpdataTestDeep(QString);

    void on_action_4_triggered();

    void on_action_5_triggered(bool checked);

    void on_action_triggered();
    void on_action_3_triggered();

    void on_action_6_toggled(bool checked);


    void on_action_8_triggered();

    void on_action_7_triggered(bool checked);

    void on_pushButton_clicked();
    void on_AddPointData(QString time, QColor color, QString name, QString point);
    void on_DeviceStatus();

    void on_UpdataDocsnames(QList<QString> name,QList<QString> time);

    void on_SelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    void on_action_9_triggered();

    void on_action_10_triggered();

    void on_action_2_triggered();

    void on_action_13_triggered();

    void on_action_15_triggered();

private:
    Ui::MainWin *ui;
     QTimer *timer = nullptr;
     QProcess *help_process = nullptr;
     Calibration *calibration_dialog = nullptr;

signals:
    void DeviceSystemThread();
    void FindDocsNames(QDate,QDate);
    void FindDocs(int index);
};

#endif // MAINWIN_H
