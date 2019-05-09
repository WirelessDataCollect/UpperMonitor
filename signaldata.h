#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QObject>
#include"exprtk.hpp"
#include<QColor>
#include<QVector>
#include<QDebug>
#include<QPointF>
class SignalData
{
public:
    SignalData();
    ~SignalData();
    int id;
    QString name;
    QColor color;
    QString express_str;
    QVector<QByteArray> message_list;
    QVector<int> val_list;
    QVector<double> time_list;
    QVector<QPointF> all_unit_data;
    exprtk::expression<double> expression;
    exprtk::parser<double> parser;
    exprtk::symbol_table<double>   symbol_table;
    std::vector<double> vector_x;

   // exprtk::vector_view<double> view = exprtk::make_vector_view(vector_x,8);
    bool isExpreesionValue(QString express_str);
    double EvaluateExpress(QByteArray data);
    double EvaluateExpress(double data);
    void AddData(double time,QByteArray data);
    void AddData(double time,int data);
    void ClearPlotData();
    void ClearAllData();
    bool update_status;
    bool show_enable;
};

#endif // SIGNALDATA_H
