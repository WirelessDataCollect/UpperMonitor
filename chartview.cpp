#include "chartview.h"
#include "chartswidgt.h"
ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    isClicking(false),
    xOld(0), yOld(0)
{
  setRubberBand(QChartView::NoRubberBand);

}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"ChartView"<<"mousePressEvent";
    if (event->button() & Qt::LeftButton) {
        isClicking = true;
    } else if (event->button() & Qt::RightButton) {
        chart()->zoomReset();
    }

    QChartView::mousePressEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<"ChartView"<<"mouseMoveEvent";

    emit sendposition(event->pos());
    int x, y;
    if (isClicking) {
        if (xOld == 0 && yOld == 0) {

        } else {
            x = event->x() - xOld;
            y = event->y() - yOld;
            chart()->scroll(-x, y);
        }

        xOld = event->x();
        yOld = event->y();
        return;
    }


    QChartView::mouseMoveEvent(event);
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"ChartView mouseReleaseEvent";
    if (isClicking) {
        xOld = yOld = 0;
        isClicking = false;
    }

    /* Disable original right click event */
    if (!(event->button() & Qt::RightButton)) {
        QChartView::mouseReleaseEvent(event);
    }



}


void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        keyPressEvent(event);
        break;
    }
}

