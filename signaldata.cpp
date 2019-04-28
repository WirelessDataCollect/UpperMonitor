#include "signaldata.h"

SignalData::SignalData()
{
    vector_x.clear();
    for(int i=1;i<9;i++) vector_x.push_back(i*5);
    symbol_table.add_constants();
    symbol_table.add_vector("X",vector_x);
    expression.register_symbol_table(symbol_table);

     update_status = false;
     show_enable = false;

}
SignalData::~SignalData()
{

    symbol_table.clear();

    expression.release();

   // qDebug()<<"delete parese begin";
}
bool SignalData::isExpreesionValue(QString express_str)
{

   parser.compile(express_str.toStdString(), expression);
   vector_x.clear();
   for(int i=1;i<9;i++) vector_x.push_back(i*5);
  //  view.rebase(vector_x.data());

    qDebug()<<"isExpreesionValue"<<expression.value();
   // if(isnan(expression.value())) return false;
   //  else return true;
   return  true;
}

void SignalData::AddData(double time,QByteArray data)
{
    time_list.append(time);
    message_list.append(data);
    double val = EvaluateExpress(data);
//    qDebug()<<"CAN SignalData add";
//    qDebug()<<data.toHex();
   // val_list.append(val);
   //emit signal
    all_unit_data.append(QPointF(time,val));
    update_status = true;
}
void SignalData::AddData(double time,int data)
{
    time_list.append(time);
    val_list.append(data);
//    qDebug()<<"signal data add";
//    qDebug()<<data;
    double voltage = data*(10.0/65536.0);
    double val = EvaluateExpress(voltage);
    all_unit_data.append(QPointF(time,val));
    update_status = true;
}
double SignalData::EvaluateExpress(QByteArray data)
{
    std::vector<double> new_vec;
    vector_x.clear();
    for(int i=0;i<data.size();i++)
    {
        vector_x.push_back(double(data.at(i)));
    }
    return expression.value();
}

double SignalData::EvaluateExpress(double data)
{
    std::vector<double> new_vec;
    vector_x.clear();
    vector_x.push_back(double(data));
    return expression.value();
}
void SignalData::ClearPlotData()
{
    all_unit_data.clear();
     update_status = true;
}

void SignalData::ClearAllData()
{
    time_list.clear();
    val_list.clear();
    message_list.clear();
    ClearPlotData();
}
