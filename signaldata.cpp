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
    filter_enable = false;
    max_data_len = 0;
    SetFilterLengthMax(1,1000);
}
SignalData::~SignalData()
{
    symbol_table.clear();
    expression.release();
}
/*
 *
 *
*/
bool SignalData::isExpreesionValue(QString express_str)
{
   parser.compile(express_str.toStdString(), expression);
   vector_x.clear();
   for(int i=1;i<9;i++) vector_x.push_back(i);
   qDebug()<< express_str;
   qDebug()<<"\n-----------------------------------------";
   qDebug()<<"expression.value()"<<expression.value();
   qDebug()<<"-----------------------------------------\n";
    if(isnan(expression.value())) return false;
     else return true;

}
// can date
void SignalData::AddData(double time,QByteArray data)
{
    if(!time_list.isEmpty() && time< time_list.last()) return;
    double val = EvaluateExpress(data);


    time_list.append(time);
    message_list.append(data);
    data_list.append(val);

    if(filter_enable) filter_enable = false;
    Filter(time,val);
    update_status = true;
}
//adc data fliter set true
void SignalData::AddData(double time,int data)
{
    if(!time_list.isEmpty() && time< time_list.last()) return;
    double voltage = data*(10.0/65536.0);
    double val = EvaluateExpress(voltage);

    time_list.append(time);
    val_list.append(data);
    data_list.append(val);
    if(filter_enable==false) filter_enable = true;
    Filter(time,val);
    update_status = true;
}
// io data fliter set false
void SignalData::AddIOData(double time,int data)
{
    if(!time_list.isEmpty() && time< time_list.last()) return;
    //if(!show_data.isEmpty() && time< show_data.last().rx()) return;
    double voltage = data;
    double val = EvaluateExpress(voltage);
    //qDebug()<<"AddIOData"<<data<<show_data.size()<< update_status;
//    if(show_data.isEmpty() )show_data.append(QPointF(time,val));
//    else if(time>= show_data.last().rx()) show_data.append(QPointF(time,val));

    time_list.append(time);
    val_list.append(data);
    data_list.append(val);
    if(filter_enable) filter_enable = false;
    Filter(time,val);
    update_status = true;
}

double SignalData::EvaluateExpress(QByteArray data)
{

    vector_x.clear();
    for(int i=0;i<data.size();i++)
    {
        vector_x.push_back((uchar(data.at(i))));
       // qDebug()<<"EvaluateExpress"<<i<<<<double(data.at(i));
    }
    return expression.value();
}

double SignalData::EvaluateExpress(double data)
{
    vector_x.clear();
    vector_x.push_back(double(data));
    return expression.value();
}
void SignalData::ClearPlotData()
{
    show_data.clear();
    show_data.resize(0);
    update_status = true;
}

void SignalData::ClearAllData()
{
    time_list.clear();
    data_list.clear();
    val_list.clear();
    message_list.clear();
    //ClearPlotData();
    UpdateAllData();
}
/*
 * 滑动平均滤波
*/
double SignalData::MoveAverageFilter(double value)
{
    if(filter_length>filter_list.size())
    {
        filter_list.append(value);
        filter_sum +=  value;
        return value;
    }
    filter_list.append(value);
    filter_sum += value;
    filter_sum -= filter_list.first();
    filter_list.removeFirst();
    return filter_sum/filter_list.length();
}

void SignalData::SetFilterLengthMax(int length, double max)
{

    max_change_data = max;
    if(length==0) length = 1;
    filter_length = length;
    int size = filter_list.size();
    if(size>filter_length)
    {
        for(int i=0;i<size-filter_length;i++) filter_list.removeFirst();
    }
    filter_sum = 0;
    for(int i=0;i<filter_list.length();i++)
    {
        filter_sum += filter_list.at(i);
    }
    UpdateAllData();
}

double SignalData::MaxFilter(double old_data, double new_data)
{
    if((old_data - new_data)>max_change_data ||((new_data - old_data)>max_change_data)) return old_data;
    return new_data;
}

void SignalData::Filter(double time, double new_data)
{

    if(filter_enable)
    {
        double old_data;
        if(show_data.isEmpty())  old_data = new_data;
        else old_data = show_data.last().y();
        double val = MaxFilter(old_data, new_data);
        double result = MoveAverageFilter(val);
        show_data.append(QPointF(time,result));
    }
    else show_data.append(QPointF(time,new_data));
    RemoveDataLen();
}

void SignalData::UpdateAllData()
{
    show_data.clear();
    show_data.resize(time_list.size());
    filter_sum=0;
    filter_list.clear();

    for(int i=0;i<time_list.size();i++)
    {
        Filter(time_list.at(i),data_list.at(i));
    }
   // if(!show_data.isEmpty()) update_status = true;
    update_status = true;
}

void SignalData::SettingAttra(QColor color, QString name, QString express_str)
{
    this->color = color;
    this->name = name;
    this->express_str = express_str;
    UpdateAllData();
    this->update_status = true;
    this->show_enable = true;
}

void SignalData::RemoveDataLen()
{
    if(max_data_len == 0) return;

    if(time_list.size()>max_data_len)time_list.remove(0,max_data_len/2);
    else return;
    if(data_list.size()>max_data_len)time_list.remove(0,max_data_len/2);
    if(val_list.size()>max_data_len)time_list.remove(0,max_data_len/2);
    if(message_list.size()>max_data_len)time_list.remove(0,max_data_len/2);
    show_data.remove(0,max_data_len/2);
}
void SignalData::SetMaxDataLen(int len)
{
    max_data_len = len;
}
