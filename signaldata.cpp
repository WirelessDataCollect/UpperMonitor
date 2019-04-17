#include "signaldata.h"

SignalData::SignalData()
{
    for(int i=1;i<9;i++)
        vector_x.push_back(1);
    symbol_table.add_constants();
    symbol_table.add_vector("X",view);
    expression.register_symbol_table(symbol_table);
}

bool SignalData::isExpreesionValue(QString express_str)
{

   parser->compile(express_str.toStdString(), expression);
    view.rebase(vector_x.data());
    qDebug()<<"isExpreesionValue"<<expression.value();
    if(isnan(expression.value())) return false;
     else return true;
}
void SignalData::AddData(double time,QByteArray data)
{
    time_list.append(time);
    message_list.append(data);
    double val = EvaluateExpress(data);
    //qDebug()<<val;
    val_list.append(val);
    //emit signal
}

double SignalData::EvaluateExpress(QByteArray data)
{
    std::vector<double> new_vec;
    for(int i=0;i<data.size();i++)
    {
        new_vec.push_back(double(data.at(i)));
    }
     //update vector
    view.rebase(new_vec.data());
    return expression.value();
}
