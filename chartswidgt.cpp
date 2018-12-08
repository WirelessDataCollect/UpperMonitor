#include "chartswidgt.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QLineSeries>
#include <QtCharts/QXYLegendMarker>
#include <QtCore/QtMath>
#include <QValueAxis>
#include<QToolTip>
#include "mainwindow.h"

QT_CHARTS_USE_NAMESPACE


chartswidgt::chartswidgt(QWidget *parent) :
    QWidget(parent),
    isClicking(false),
    xOld(0), yOld(0)
{
     //dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    // Create chart view with the chart
    m_chart = new QChart();
    m_callout = new callout(this);
  //  m_callout = new callout();
//   if(ChartMouseStyle==1)
//   {
        m_chartView = new QChartView(m_chart, this);
//   }

    m_chartView = new ChartView(m_chart,this);
    m_chartView->installEventFilter(this);
    m_chart->installEventFilter(this);

    m_chartView->setRubberBand(QChartView::RectangleRubberBand);


    this->setMouseTracking(true);
    m_chartView->setInteractive(true);

   // m_chartView->setRenderHint(QPainter::Antialiasing);
    // Create layout for grid and detached legend
    m_mainLayout = new QVBoxLayout();

    m_mainLayout->setSpacing(0);
    m_mainLayout->setMargin(0);
    label_position= new QLabel("X:  Y:  ");
    label_position->setAlignment(Qt::AlignHCenter);

    m_mainLayout->addWidget(label_position);
    m_mainLayout->addWidget(m_chartView);
    m_mainLayout->setMargin(0);
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    setLayout(m_mainLayout);
    setseries();
    m_chartView->setAutoFillBackground(true);
     for(int i =0;i<4;i++)
     {
       connect(s_series.at(i),&QSplineSeries::hovered, this, &chartswidgt::clickpoint);

     }

     connect(m_chartView,SIGNAL(sendposition(QPoint)), this, SLOT(show_position(QPoint)));
     connectMarkers();
     m_chart->createDefaultAxes();
    // m_chart->axisY()->setRange(0,5);

    // Set the title and show legend
    m_chart->setTitle("Legendmarker example (click on legend)");
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);

    plotXaxis = 0;
    QList<QPointF> zerolist;
    for(plotXaxis = 0;plotXaxis<Alldatabuf;plotXaxis++)
    {
     zerolist.append(QPointF(plotXaxis,0));
    }
    for(int i = 0;i<4;i++)
    {
        data.append(zerolist);
    }

   // m_chartView->setRenderHint(QPainter::Antialiasing);
}



void chartswidgt::setseries()
{
  while(s_series.count()<4){
     QSplineSeries *series = new  QSplineSeries();
     s_series.append(series);
     series->setName(QString("Channel " + QString::number(s_series.count())));
     QList<QPointF> data;
     for(int i=0;i<Alldatabuf;i++){
         qreal x=i;
         qreal y=0;
         data.append(QPointF(x,y));
     }
     //data.append(QPointF(Alldatabuf-1,10));
     series->append(data);
     m_chart->addSeries(series);
  }

}

void chartswidgt::removeSeries()
{
    // Remove last series from chart
    while (s_series.count() > 0) {
        QLineSeries *series = s_series.last();
        m_chart->removeSeries(series);
        s_series.removeLast();
        delete series;
    }
    s_series.clear();
}

void chartswidgt::connectMarkers()
{
//![1]
    // Connect all markers to handler
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
        QObject::connect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
//![1]
}

void chartswidgt::disconnectMarkers()
{
//![2]
    foreach (QLegendMarker* marker, m_chart->legend()->markers()) {
        QObject::disconnect(marker, SIGNAL(clicked()), this, SLOT(handleMarkerClicked()));
    }
//![2]
}

void chartswidgt::handleMarkerClicked()
{
//![3]
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
//![3]

//![4]
    switch (marker->type())
//![4]
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
//![5]
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);
//![5]

//![6]
        // Dim the marker, if series is not visible
        qreal alpha = 1.0;

        if (!marker->series()->isVisible()) {
            alpha = 0.5;
        }

        QColor color;
        QBrush brush = marker->labelBrush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setLabelBrush(brush);

        brush = marker->brush();
        color = brush.color();
        color.setAlphaF(alpha);
        brush.setColor(color);
        marker->setBrush(brush);

        QPen pen = marker->pen();
        color = pen.color();
        color.setAlphaF(alpha);
        pen.setColor(color);
        marker->setPen(pen);

//![6]
        break;
        }
    default:
        {
        qDebug() << "Unknown marker type";
        break;
        }
    }
}

void chartswidgt::rxplotdata(QVector<QVector<double> >&plotdata)
{
    plotXaxis++;
    for(int i = 0; i < 4;i++){

         QSplineSeries *series =s_series.at(i);


         series->append(QPointF(plotXaxis,plotdata.at(i).at(0)));
         qDebug()<<"plotdata.at(i).length()"<<plotdata.at(i).length();
         series->removePoints(0,1);
    }

    m_chart->axisX()->setRange(plotXaxis-Alldatabuf,plotXaxis);
}


void chartswidgt::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0) {
        m_chart->zoom(1.5);
    } else {
        m_chart->zoom(0.5);
    }

    QWidget::wheelEvent(event);

}

void chartswidgt::mousePressEvent(QMouseEvent *event)
{

   qDebug()<<"chartswidgt"<<event->button();
 if (event->button() & Qt::RightButton) {
        m_chart->zoomReset();
    }

    QWidget::mousePressEvent(event);
}



void chartswidgt::mouseMoveEvent(QMouseEvent *event)
{
    /* Setting the mouse position label on the axis from value to position */

    qDebug()<<"chartswidgt"<<"mouseMoveEvent";
    qreal xVal = m_chart->mapToValue(event->pos()).x();
    qreal yVal = m_chart->mapToValue(event->pos()).y();
    qDebug()<<"xVal"<<xVal;
    qDebug()<<"xVal"<<yVal;

   QWidget::mouseMoveEvent(event);
}


void chartswidgt::clickpoint(const QPointF &point, bool state){
      if(state)
      {

       QString m_text = QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y());
       QFontMetrics metrics(m_font);
       m_textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, m_text);
       m_textRect.translate(5, 5);
       m_rect = m_textRect.adjusted(-5, -5, 5, 5);
       qDebug()<<"chartswidgt";
       qDebug()<<point.x();
       qDebug()<<point.y();


       QToolTip::showText(this->mapToGlobal(m_chart->mapToPosition(point).toPoint()), m_text, this);


//      m_callout->move(this->mapToGlobal(m_chart->mapToPosition(point).toPoint()));
//      m_callout->m_label->setText(m_text);
//      m_callout->show();

      }
//      QPoint a = this->mapToGlobal(m_chart->mapToPosition(point).toPoint());
      else
      {
         // m_callout->hide();
      }

}

void chartswidgt::show_position(const QPoint &point)
{

   label_position->setText(QString("X: %1  Y: %2 ").arg(m_chart->mapToValue(point).x()).arg(m_chart->mapToValue(point).y()));

}

bool chartswidgt::eventFilter(QObject *target , QEvent *event )
{

   // qDebug()<<"object"<<target<<"QEvent"<<event->type();
    if(target == m_chartView)
    {

        if(event->type() == QEvent::MouseButtonPress)
        {
            qDebug()<<"dddd";
            return true;

        }

    }
       return false;
}


