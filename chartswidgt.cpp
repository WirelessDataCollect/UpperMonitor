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
#include<QThread>


QT_CHARTS_USE_NAMESPACE

chartswidgt::chartswidgt(DeviceSystem *system,QWidget *parent) :
    QWidget(parent),
    isClicking(false),
    xOld(0), yOld(0)
{


    device_system = system;
    m_chart = new QChart();

    m_chartView = new ChartView(m_chart,this);


    m_chartView->setRubberBand(QChartView::NoRubberBand);

    this->setMouseTracking(true);
    m_chartView->setInteractive(true);
    h_slider = new DoubleSlider();
    v_slider = new DoubleSlider();

   // m_chartView->setRenderHint(QPainter::Antialiasing);
    // Create layout for grid and detached legend
    m_vbox_layout = new QVBoxLayout();



    m_chart->layout()->setContentsMargins(0,0,0,0);
    m_chart->setMargins(QMargins(0,0,0,0));


    label_position= new QLabel("X:  Y:  ");
    label_position->setStyleSheet("background-color:white");

    label_position->setAlignment(Qt::AlignHCenter);

    m_vbox_layout->addWidget(label_position);
    m_vbox_layout->addWidget(m_chartView);


    m_vbox_layout->addWidget(h_slider);
    m_vbox_layout->setMargin(0);
    m_vbox_layout->setSpacing(1);

    //m_vbox_layout->setContentsMargins(0,0,0,0);

    setLayout(m_vbox_layout);
    m_chartView->setAutoFillBackground(true);

     connect(m_chartView,SIGNAL(sendposition(QPoint)), this, SLOT(show_position(QPoint)));
     connectMarkers();

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    InitSeries();
    m_chart->createDefaultAxes();

     timer = new QTimer();
     timer->start(300);
     connect(timer, SIGNAL(timeout()), this, SLOT(UpdateChart()));
    m_chartView->setRenderHint(QPainter::Antialiasing);

}

void chartswidgt::ReveiveFrameData(int device, int signal, QString name, QColor color, QList<QPointF> frame_uint_data, bool is_frame)
{

  //  m_chartView->setUpdatesEnabled(false);

     QLineSeries * series = series_list.at(device).at(signal);
     point_list[device][signal].append(frame_uint_data);
     status_list[device][signal] = true;

    // if(series->color()!=color) series->setColor(color);
   //  if(series->name()!=name) series->setName(name);

//    qDebug()<<"frame_uint_data size"<<frame_uint_data.size();
//   qDebug()<<"frame_uint_data (x,y)"<<frame_uint_data.at(0).x()<<frame_uint_data.at(0).y();

//      qDebug()<<"series_list.size();"<<series_list.size();
//      qDebug()<<"series_list.size();"<<series_list.size();

   //  series->setName("dddd");
//     series->replace(point_list[device][signal]);
//    // m_chart->addSeries(series);
//     if(!m_chart->series().contains(series)) m_chart->addSeries(series);
//     m_chart->createDefaultAxes();
//     m_chartView->setUpdatesEnabled(true);
}

void chartswidgt::UpdateChart()
{
    m_chartView->setUpdatesEnabled(false);

    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
            QLineSeries * series = series_list.at(device).at(signal);
            DeviceSignal *device_signal = device_system->device_vector.at(device)->signal_vector.at(signal);
            bool status = device_signal->show_enable;

            if(status && !device_signal->all_unit_data.isEmpty())
            {
                bool update =  device_signal->update_status;
                if(update)
                {
                    if(series->color()!=device_signal->line_collor) series->setColor(device_signal->line_collor);
                    if(series->name()!=device_signal->signal_name) series->setName(device_signal->signal_name);
                        device_signal->update_status = false;
                       qDebug()<<"ddddddddddd"<<device<<signal;
                        series->replace(device_signal->all_unit_data);
                       qDebug()<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

                        if(!m_chart->series().contains(series)) m_chart->addSeries(series);
                   }
                }

            else if(m_chart->series().contains(series)) m_chart->removeSeries(series);
        }
    }
    connectMarkers();
    m_chartView->setUpdatesEnabled(true);
   // m_chartView->update();
    m_chart->createDefaultAxes();
}
void chartswidgt::UpdateChartView()
{
    bool status = false;
    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
         status |= status_list[device][signal];
         if(status) break;
        }
        if(status) break;
    }
    if(status==false)
    {

        return;
    }

   // m_chart->setEnabled(false);
    m_chartView->setUpdatesEnabled(false);

  for(int device=0;device<5;device++)
  {
      for(int signal =0;signal<6;signal++)
      {
          if(status_list[device][signal] &&device_system->device_vector.at(device)->signal_vector.at(signal)->update_status)
          {
              device_system->device_vector.at(device)->signal_vector.at(signal)->update_status =false;

              status_list[device][signal] = false;
               QLineSeries * series = series_list.at(device).at(signal);
               //if(m_chart->series().contains(series)) m_chart->removeSeries(series);
               series->replace(point_list.at(device).at(signal));

               qDebug()<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
               qDebug()<<"point_list.at(device).at(signal).size"<<point_list.at(device).at(signal).size();
               if(!m_chart->series().contains(series)) m_chart->addSeries(series);
          }


      }
  }

 // m_chart->setEnabled(true);
  connectMarkers();
  m_chartView->setUpdatesEnabled(true);
  m_chart->createDefaultAxes();
}


void chartswidgt::GetSeriesPoint(bool status)
{
    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
            series_list[device][signal]->setUseOpenGL(!status);

        }

}
    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
            connect(series_list[device][signal],SIGNAL(hovered(QPointF,bool)),this,SLOT(clickpoint(QPointF,bool)));

        }
}
    get_point_status = status;
    qDebug()<<"get_point_status"<<get_point_status;
}

void chartswidgt::InitSeries()
{
    m_chart->series().clear();
    series_list.clear();
    series_list.resize(5);
    for(auto itor = series_list.begin();itor!=series_list.end();itor++)
    {
        for(int i=0;i<6;i++)
        {
            QLineSeries *series = new QLineSeries();


            series->setUseOpenGL(true);

            itor->append(series);
        }
    }

    point_list.resize(5);
    for(auto itor = point_list.begin();itor!=point_list.end();itor++)
    {
        itor->resize(6);
    }
    status_list.resize(5);
    for(auto itor = status_list.begin();itor!=status_list.end();itor++)
    {
        itor->resize(6);
    }

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



void chartswidgt::clickpoint(const QPointF &point,bool status){
    if(status)
    {
       QLineSeries *series = (QLineSeries *)sender();
       QString name = series->name();
       QColor color = series->color();

       QString m_text = QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y());
       QFontMetrics metrics(m_font);
       m_textRect = metrics.boundingRect(QRect(0, 0, 150, 150), Qt::AlignLeft, m_text);
       m_textRect.translate(5, 5);
       m_rect = m_textRect.adjusted(-5, -5, 5, 5);
       QToolTip::showText(this->mapToGlobal(m_chart->mapToPosition(point).toPoint()), m_text, this);
       QString time = QString::number(point.x(), 10, 3);
       QString value= QString::number(point.y(), 10, 3);
       emit AddPointData(time,color,name,value);
       qDebug()<<"AddPointData send";
}


}

void chartswidgt::show_position(const QPoint &point)
{

   label_position->setText(QString("X: %1  Y: %2 ").arg(m_chart->mapToValue(point).x()).arg(m_chart->mapToValue(point).y()));
}
