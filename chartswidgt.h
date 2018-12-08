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
#include"callout.h"
QT_CHARTS_USE_NAMESPACE

#define ChartMouseStyle   1

#define Alldatabuf 100
class chartswidgt : public QWidget
{
    Q_OBJECT


public:
    explicit chartswidgt(QWidget *parent = 0);
    QLabel *label_position;
    bool eventFilter(QObject *target , QEvent *event );
    QChartView *m_chartView;
public slots:
    //void addSeries();
    void removeSeries();
    void connectMarkers();
    void disconnectMarkers();

    void handleMarkerClicked();
    void rxplotdata(QVector<QVector<double> >&plotdata);
    void clickpoint(const QPointF &point, bool state);
    void show_position(const QPoint &point);





private:
    bool isClicking;
    int xOld;
    int yOld;
    QChart *m_chart;
    QList<QSplineSeries *> s_series;
    QVector<QVector<quint16> > pdata;
    quint16 pchannel;

    QVBoxLayout *m_mainLayout;

    QList<QList<QPointF> > data;
    qreal plotXaxis;
    void setseries();
    QRectF m_rect;
    QRectF m_textRect;
    QFont m_font;
    callout *m_callout = nullptr;

protected:

    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent * event);

};

#endif // CHARTSWIDGT_H
