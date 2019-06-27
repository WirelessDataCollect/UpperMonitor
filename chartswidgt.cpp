﻿#include "chartswidgt.h"
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
#include<QLineEdit>
#include<QDialog>
#include<QTableWidget>
#include"datadialog.h"
QT_CHARTS_USE_NAMESPACE

chartswidgt::chartswidgt(DeviceSystem *system,QWidget *parent) :
    QWidget(parent),
    isClicking(false),
    xOld(0), yOld(0)
{

    device_system = system;
    m_chart = new QChart();

    //  m_chartView = new ChartView(m_chart,this);
    //  m_chartView->setRubberBand(QChartView::NoRubberBand);

    m_chartView = new ChartView(m_chart);
    m_chartView->setRubberBand(QChartView::RectangleRubberBand);
    m_chartView->setInteractive(true);
    this->setMouseTracking(true);

    h_slider = new DoubleSlider();
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

    lineEditMinRange = new QLineEdit("0.000");
    lineEditMaxRange = new QLineEdit("99.000");
    m_min =0;
    m_max = 99;
    lineEditMaxRange->setMaximumWidth(50);
    lineEditMinRange->setMaximumWidth(50);

    QHBoxLayout * m_hbox_layout = new QHBoxLayout();
    m_hbox_layout->addWidget(lineEditMinRange);
    m_hbox_layout->addWidget(lineEditMaxRange);
    m_hbox_layout->insertStretch(1,10);
    m_vbox_layout->addLayout(m_hbox_layout);

    m_vbox_layout->setMargin(0);
    m_vbox_layout->setSpacing(1);

    setLayout(m_vbox_layout);
    m_chartView->setAutoFillBackground(true);

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
    InitSeries();

    timer = new QTimer();
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateChart()));
    m_chartView->setRenderHint(QPainter::Antialiasing);
    connect(h_slider,SIGNAL(minValueChanged(float)),this,SLOT(setMinValue(float)));
    connect(h_slider,SIGNAL(maxValueChanged(float)),this,SLOT(setMaxValue(float)));
    connect(lineEditMinRange,SIGNAL(editingFinished()),this,SLOT(setMinRange()));
    connect(lineEditMaxRange,SIGNAL(editingFinished()),this,SLOT(setMaxRange()));
    connect(m_chartView,SIGNAL(sendposition(QPoint)), this, SLOT(show_position(QPoint)));
    connect(m_chartView,SIGNAL(updateslider()), this, SLOT(on_updateslider()));
    connectMarkers();

    m_chart->createDefaultAxes();
}

void chartswidgt::UpdateChart()
{
    m_chartView->setUpdatesEnabled(false);

    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
            QLineSeries * series = series_list.at(device).at(signal);
            SignalData *device_signal = device_system->device_vector.at(device)->signal_vector.at(signal)->signal_data;

            if(device_signal->show_enable)
            {
                if(!m_chart->series().contains(series))
                {
                    m_chart->addSeries(series);
                    m_chart->createDefaultAxes();
                    QPen pen = series->pen();
                    pen.setWidth(2);
                    series->setPen(pen);
                }
                bool update =  device_signal->update_status;
                if(series->color()!=device_signal->color) series->setColor(device_signal->color);
                if(series->name()!=device_signal->name) series->setName(device_signal->name);
                if(update)
                {

                   device_signal->update_status = false;
                  //if(device_signal->show_data.isEmpty())
                   series->replace(device_signal->show_data);

                   qDebug()<<device<<signal<<"Signal plot------------------------------------";
                   qDebug()<<device_signal->show_data.size();

                }
            }
            else
            {
                if(m_chart->series().contains(series))
                {
                    m_chart->removeSeries(series);
                }
            }
        }

        for(int channel=0;channel<2;channel++)
        {
            QVector<QLineSeries *> series_list = series_can[device][channel];
            bool status;
            SignalData *device_signal;
            QLineSeries * series;

            if(device_system->device_vector.at(device)->can_vector.at(channel)->update_status)
            {
                device_system->device_vector.at(device)->can_vector.at(channel)->update_status = false;

                for(int i=0;i<series_can[device][channel].size();i++)
                {
                    m_chart->removeSeries(series_can[device][channel][i]);
                   // delete series_can[device][channel][0];
                }
                series_can[device][channel].clear();
                for(int i=0;i<device_system->device_vector.at(device)->can_vector.at(channel)->filter_list.size();i++)
                {
                    series = new QLineSeries();
                    series->setUseOpenGL(true);
                    series_can[device][channel].append(series);
                    // m_chart->addSeries(series);
                }
                qDebug()<<"-------------------------------------------";
                qDebug()<<"series_can[device][channel].size()"<<series_can[device][channel].size();
            }

            series_list = series_can[device][channel];
            for(int i =0;i<series_list.size();i++)
            {
                device_signal = device_system->device_vector.at(device)->can_vector.at(channel)->filter_list.at(i);
                bool update =  device_signal->update_status;
                //qDebug()<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX CANNNNNNNNNNNNNNNNNN"<<device<<channel<<i<<update<<device_system->device_vector.at(device)->can_vector.at(channel)->filter_list.at(i)->show_data.size();

                if(update)
                {
                    series = series_list.at(i);
                    if(series->color()!=device_signal->color) series->setColor(device_signal->color);
                    if(series->name()!=device_signal->name) series->setName(device_signal->name);
                    device_signal->update_status = false;
                    series->replace(device_signal->show_data);
                    //  qDebug()<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXX  CAN replace";
                    if(!m_chart->series().contains(series))
                    {
                        m_chart->addSeries(series);
                        m_chart->createDefaultAxes();
                        QPen pen = series->pen();
                        pen.setWidth(2);
                        series->setPen(pen);
                    }
                }
            }
        }
    }
    connectMarkers();
    m_chartView->setUpdatesEnabled(true);
    m_chartView->update();
}

void chartswidgt::GetSeriesPoint(bool status)
{
    QLineSeries *series;
    get_point_status = status;
    qDebug()<<"get_point_status"<<get_point_status;

    for(int device=0;device<5;device++)
    {
        for(int signal =0;signal<6;signal++)
        {
            series = series_list[device][signal];
            series->setUseOpenGL(!status);
            if(status) connect(series,SIGNAL(hovered(QPointF,bool)),this,SLOT(clickpoint(QPointF,bool)));
            else disconnect(series,SIGNAL(hovered(QPointF,bool)),this,SLOT(clickpoint(QPointF,bool)));
        }
        for(int channel =0; channel<2;channel++)
        {
            for(int k =0;k<series_can.at(device).at(channel).size();k++)
            {
                series =  series_can.at(device).at(channel).at(k);
                series->setUseOpenGL(!status);
                if(status) connect(series,SIGNAL(hovered(QPointF,bool)),this,SLOT(clickpoint(QPointF,bool)));
                else disconnect(series,SIGNAL(hovered(QPointF,bool)),this,SLOT(clickpoint(QPointF,bool)));
            }
        }
    }
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
    series_can.resize(5);
    for(auto itor = series_can.begin();itor!=series_can.end();itor++)
    {
        itor->resize(2);
    }

    point_vector.resize(5);
    for(auto itor = point_vector.begin();itor!=point_vector.end();itor++)
    {
        itor->resize(8);
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
void chartswidgt::on_updateslider()
{
    QValueAxis *axisX = dynamic_cast<QValueAxis*>(m_chart->axisX());
    if(NULL != axisX)
    {
        h_slider->setMaxValue(axisX->max());
        h_slider->setMinValue(axisX->min());
    }
}

void chartswidgt::wheelEvent(QWheelEvent *event)
{
    QValueAxis *axisX = dynamic_cast<QValueAxis*>(m_chart->axisX());
    QValueAxis *axisY = dynamic_cast<QValueAxis*>(m_chart->axisY());
    double y_min = axisY->min();
    double y_max = axisY->max();

    if(NULL != axisX && NULL != axisY)
    {
        if (event->delta() < 0) {
            axisY->setMax((y_max+y_min)/2 + (y_max-y_min)*0.75);
            axisY->setMin((y_max+y_min)/2 - (y_max-y_min)*0.75);

        }
        else
        {
            axisY->setMax((y_max+y_min)/2 + (y_max-y_min)*0.25);
            axisY->setMin((y_max+y_min)/2 - (y_max-y_min)*0.25);
        }
        h_slider->setMaxValue(axisX->max());
        h_slider->setMinValue(axisX->min());

    }
    QWidget::wheelEvent(event);
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

void chartswidgt::setMaxRange()
{
    float range =lineEditMaxRange->text().toFloat();
    if(range-m_min>0.009f) m_max = range;
    lineEditMaxRange->setText(QString::number(m_max,'f',3));

    h_slider->setMaxRange(m_max);
}
void chartswidgt::setMinRange()
{

    float range =lineEditMinRange->text().toFloat();
    if(m_max-range>0.009f) m_min = range;
    lineEditMinRange->setText(QString::number(m_min,'f',3));
    h_slider->setMinRange(m_min);
}

void chartswidgt::setMinValue(float val)
{
    if(!m_chart->series().isEmpty())
        m_chart->axisX()->setMin(val);
}

void chartswidgt::setMaxValue(float val)
{
    if(!m_chart->series().isEmpty())
        m_chart->axisX()->setMax(val);
}

void chartswidgt::show_position(const QPoint &point)
{
    label_position->setText(QString("X: %1  Y: %2 ").arg(m_chart->mapToValue(point).x()).arg(m_chart->mapToValue(point).y()));
}

void chartswidgt::showDataDialog()
{
    QValueAxis *axisX = dynamic_cast<QValueAxis*>(m_chart->axisX());
    QValueAxis *axisY = dynamic_cast<QValueAxis*>(m_chart->axisY());

    QTableWidget *tablewidget = new QTableWidget();
    tablewidget->insertColumn(1);
    if(NULL != axisX && NULL != axisY)
    {
        DataDialog *dialog = new DataDialog(this);
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        double x_min = axisX->min();
        double x_max = axisX->max();
        double y_min = axisY->min();
        double y_max = axisY->max();
        qDebug()<<x_min<<x_max<<y_min<<y_max;

        for(int i=0;i<5;i++)
        {
            for(int j=0;j<6;j++)
            {
                SignalData *signaldata = device_system->device_vector.at(i)->signal_vector.at(j)->signal_data;
                if(signaldata->show_enable)
                {
                    QVector<QPointF> data;
                    for(auto itor= signaldata->show_data.begin();itor<signaldata->show_data.end();itor++)
                    {
                        if(itor->x()>x_min && itor->x()<x_max && itor->y()>y_min && itor->y()<y_max) data.append(*itor);
                    }
                    if(!data.isEmpty()) dialog->AddColumn(signaldata->name,data);
                }
            }
            for(int j=0;j<2;j++)
            {
                for(int k=0;k<series_can.at(i).at(j).size();k++)
                {
                    SignalData *signaldata = device_system->device_vector.at(i)->can_vector.at(j)->filter_list.at(k);
                    if(signaldata->show_enable)
                    {
                        QVector<QPointF> data;
                        for(auto itor= signaldata->show_data.begin();itor<signaldata->show_data.end();itor++)
                        {
                            if(itor->x()>x_min && itor->x()<x_max && itor->y()>y_min && itor->y()<y_max) data.append(*itor);
                        }
                        if(!data.isEmpty()) dialog->AddColumn(signaldata->name,data);
                    }
                }
            }
        }
         dialog->show();
    }
}


