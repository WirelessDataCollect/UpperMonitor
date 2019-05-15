#ifndef CHARTSWIDGT_H
#define CHARTSWIDGT_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QLineSeries>
#include <QSplineSeries>
#include<QMouseEvent>
#include<QWheelEvent>
#include <QRubberBand>
#include"chartview.h"
#include<QFontMetrics>
#include<QLabel>
#include<QDialog>
#include<QDockWidget>
#include<QColor>

#include<QPointF>
#include<QTimer>

#include "devicesystem.h"
#include"devicesignal.h"
#include"doubleslider.h"
#include"signaldata.h"
QT_CHARTS_USE_NAMESPACE


class chartswidgt : public QWidget
{
    Q_OBJECT


public:
    explicit chartswidgt(DeviceSystem *system, QWidget *parent = nullptr);
    //QWidget *parent = 0
    QLabel *label_position;

    ChartView *m_chartView;
    void GetSeriesPoint(bool status);
    void showDataDialog();



public slots:

    void connectMarkers();
    void disconnectMarkers();

    void handleMarkerClicked();

    void clickpoint(const QPointF &point,bool status);
    void show_position(const QPoint &point);

    void UpdateChart();
    void setMaxRange();
    void setMinRange();
    void setMaxValue(float val);
    void setMinValue(float val);
    void on_updateslider();

private:
    bool isClicking;
    int xOld;
    int yOld;
    QChart *m_chart;
    //QSplineSeries

    QVector< QVector<QLineSeries *>> series_list;
    QVector< QVector<QVector<QLineSeries *> > > series_can;
    QVector<QVector<QVector<QList<QPointF>>>> point_vector;
    QVector< QVector <QVector<bool>>> status_vector;
    QVector< QVector<bool>> status_list;
    QList<QList<QColor>*> color_list;
    QList<QList<QString>*> name_list;
    QVector<QVector<QList<QPointF>>> point_list;
    QList<QSplineSeries *> s_series;

    quint16 pchannel;

    QVBoxLayout *m_vbox_layout;
    QHBoxLayout *m_hbox_layout;

    QList<QList<QPointF> > data;
    bool get_point_status;
    qreal plotXaxis;

    QRectF m_rect;
    QRectF m_textRect;
    QFont m_font;

    QTimer *timer= nullptr;
    DeviceSystem *device_system = nullptr;
    DoubleSlider *h_slider;
    DoubleSlider *v_slider;

    void InitSeries();
    int IndexofSeries(QLineSeries *series, int device, int signal,QString name, QColor color);
    float m_min;
    float m_max;
    QLineEdit *lineEditMaxRange;
    QLineEdit *lineEditMinRange;

signals:
    void AddPointData(QString time, QColor color, QString name, QString point);


protected:

    void wheelEvent(QWheelEvent *event);

};

#endif // CHARTSWIDGT_H
