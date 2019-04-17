#ifndef SIGNALDATA_H
#define SIGNALDATA_H

#include <QObject>
#include"exprtk.hpp"
#include<QColor>
#include<QVector>
#include<QDebug>
class SignalData
{
public:
    SignalData();
    uint id;
    QString name;
    QColor color;
    QString express_str;
    QVector<QByteArray> message_list;
    QVector<double> val_list;
    QVector<double> time_list;
    exprtk::expression<double> expression;
    exprtk::parser<double> *parser = new exprtk::parser<double>;
    exprtk::symbol_table<double>   symbol_table;
    std::vector<double> vector_x;
    exprtk::vector_view<double> view = exprtk::make_vector_view(vector_x,8);
    bool isExpreesionValue(QString express_str);
    double EvaluateExpress(QByteArray data);
    void AddData(double time,QByteArray data);
};

#endif // SIGNALDATA_H
