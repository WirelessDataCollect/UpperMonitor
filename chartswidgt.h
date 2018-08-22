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
QT_CHARTS_USE_NAMESPACE


#define Alldatabuf 100
class chartswidgt : public QWidget
{
    Q_OBJECT
public:
    explicit chartswidgt(QWidget *parent = 0);

public slots:
    //void addSeries();
    void removeSeries();
    void connectMarkers();
    void disconnectMarkers();

    void handleMarkerClicked();
    void rxplotdata(QVector<double> &plotdata);
private:

    QChart *m_chart;
    QList<QSplineSeries *> s_series;
    QVector<QVector<quint16> > pdata;
    quint16 pchannel;
    QChartView *m_chartView;
    QGridLayout *m_mainLayout;
    QGridLayout *m_fontLayout;
    QList<QList<QPointF> > data;
    qreal plotXaxis;
    void setseries();
};

#endif // CHARTSWIDGT_H
