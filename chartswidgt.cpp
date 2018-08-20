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
#include "mainwindow.h"

QT_CHARTS_USE_NAMESPACE

chartswidgt::chartswidgt(QWidget *parent) :
    QWidget(parent)
{
    // Create chart view with the chart
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);


    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(m_mainLayout);


    //connectMarkers();
     // setseries();

     // connectMarkers();
    //  m_chart->createDefaultAxes();

    // Set the title and show legend
    m_chart->setTitle("Legendmarker example (click on legend)");
    m_chart->legend()->setVisible(true);
   // m_chart->legend()->setAlignment(Qt::AlignBottom);
    m_chart->legend()->setAlignment(Qt::AlignLeft);


    m_chartView->setRenderHint(QPainter::Antialiasing);
}



void chartswidgt::setseries()
{
  while(s_series.count()<4){
     QSplineSeries *series = new  QSplineSeries();
     s_series.append(series);
     series->setName(QString("Channel " + QString::number(s_series.count())));
     QList<QPointF> data;
     for(int i=0;i<Alldatabuf-1;i++){
         qreal x=i;
         qreal y=-10;
         data.append(QPointF(x,y));
     }
     data.append(QPointF(Alldatabuf-1,10));
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


void chartswidgt::rxdata(QVector<QVector<uint16_t> > pdata,uint16_t pchannel,int Plotsize,int range){
     removeSeries();
      QList<QPointF> data;
      double GainAD8421;
      data.clear();
      double Yrange;
     QVector<QVector<uint16_t> >::iterator iter=pdata.begin();
     //qDebug()<<(*iter).size();
    // qDebug()<<(*iter).back();
   qDebug()<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
   if(range==0) {GainAD8421=1+9.9/0.205;Yrange=0.2;}
   else if(range==1) {GainAD8421=1; Yrange=10;}
       else if(range==2){ GainAD8421 =10;Yrange=1;}
        else if(range==3){ GainAD8421=1.99;Yrange=5;}
    for(int i=0;i<16;i++){
        QSplineSeries *series =new QSplineSeries();

        //s_series.append(series);
        //series->clear();
        series->setName(QString("Channel " + QString::number(i)));
        if(pchannel%2){
            for(int j=0;j<Plotsize;j++){
                    qreal x=j;
                    qreal y=((int16_t)((*iter).at(j)))/65536.0*2*4.09*2.5/GainAD8421;
                    qDebug()<<"LLLLLL:     "<<y;
                   data.append(QPointF(x,y));
                 }
          //  iter++;
        }
        else{
            for(int j=0;j<Plotsize;j++){
                    qreal x=j;
                    qreal y=0;
                   data.append(QPointF(x,y));
                 }
          //  iter++;
        }
        series->append(data);
        m_chart->addSeries(series);
        pchannel/=2;
       // m_chart->addSeries(series);
        data.clear();
    }
     connectMarkers();
     m_chart->createDefaultAxes();
     m_chart->axisX()->setRange(0,Plotsize);
     m_chart->axisY()->setRange(-Yrange,Yrange);
    }



