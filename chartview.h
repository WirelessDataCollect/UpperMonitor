#ifndef __CHARTVIEW_H__
#define __CHARTVIEW_H__

#include <QChartView>
#include <QRubberBand>
#include <QDebug>
#include <QtCharts/QChart>


QT_CHARTS_USE_NAMESPACE


class ChartView : public QChartView
{
    Q_OBJECT
signals:
    void sendposition(const QPoint &point);
    void updateslider();
public:
    ChartView(QChart *chart, QWidget *parent = 0);


protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    bool isClicking;

    int xOld;
    int yOld;



};

#endif /* __CHARTVIEW_H__ */
