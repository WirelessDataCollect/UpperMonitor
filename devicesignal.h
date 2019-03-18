#ifndef DEVICESIGNAL_H
#define DEVICESIGNAL_H
#include<QObject>
#include<QColor>
#include<QDateTime>
#include<QPointF>
#include<QTimer>
class DeviceSignal: public QObject
{
    Q_OBJECT

public:
    DeviceSignal();

    QString signal_name;
    bool show_enable;
    bool vol_enable;
    QColor line_collor;
    double max_v;
    double min_v;
    double max_unit;
    double min_unit;
    int signal_id;
    int device_id;
    QList<QPoint> all_raw_data;
    QList<QPoint> frame_raw_data;
    QTimer *timer;

    QList<double> filter_list;
    int filter_length;

    QList<QPointF> all_unit_data;
    QList<QPointF> frame_unit_data;

    bool update_status;
    double k;



    void UpdataAllUnitData();

    void ClearReceiveData();
    void SetSignalStatus(bool status);
    void SetIVStatus(bool status);
    void SetSignalName(QString name);
    void SetSignalColor(QColor color);
    void ClearFrameData();
    void ClearAllData();
    void EmitFrameData();
    void EmitAllData();
    void EmitNoneData();
    void EmitCleanData();
    bool SetUnitVol(int index,double value);
    double Filter(double value);
    void SetFilterLength(int length);
    bool updata_all_data;
    void AddData(QPoint point);
    void AddFrameData();

signals:
    void sendframedata(int device_id,int signal_id,QString name,QColor signal_color, QList<QPointF> frame_uint_data,bool is_frame);
public slots:





};

#endif // DEVICESIGNAL_H
