#include "fit.h"
#include<QVector>
Fit::Fit()
{
}
double Fit::sum(vector<double> Vnum, int n)
{
    double dsum=0;
    for (int i=0; i<n; i++)
    {
        dsum+= Vnum[i];
    }
    return dsum;
}
//乘积和
double Fit::MutilSum(vector<double> Vx, vector<double> Vy, int n)
{
    double dMultiSum=0;
    for (int i=0; i<n; i++)
    {
        dMultiSum+=Vx[i]*Vy[i];
    }
    return dMultiSum;
}
//ex次方和
double Fit::RelatePow(vector<double> Vx, int n, int ex)
{
    double ReSum=0;
    for (int i=0; i<n; i++)
    {
        ReSum+=pow(Vx[i],ex);
    }
    return ReSum;
}
//x的ex次方与y的乘积的累加
double Fit::RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex)
{
    double dReMultiSum=0;
    for (int i=0; i<n; i++)
    {
        dReMultiSum+=pow(Vx[i],ex)*Vy[i];
    }
    return dReMultiSum;
}
//计算方程组的增广矩阵
void Fit::EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[])
{
    for (int i=1; i<=ex; i++)
    {
        for (int j=1; j<=ex; j++)
        {
            Em[i][j]=RelatePow(Vx,n,i+j-2);
        }
        Em[i][ex+1]=RelateMutiXY(Vx,Vy,n,i-1);
    }
    Em[1][1]=n;
    CalEquation(ex,coefficient);
}
//求解方程
void Fit::CalEquation(int exp, double coefficient[])
{
    for(int k=1;k<exp;k++) //消元过程
    {
        for(int i=k+1;i<exp+1;i++)
        {
            double p1=0;

            if(Em[k][k]!=0)
                p1=Em[i][k]/Em[k][k];

            for(int j=k;j<exp+2;j++)
                Em[i][j]=Em[i][j]-Em[k][j]*p1;
        }
    }
    coefficient[exp]=Em[exp][exp+1]/Em[exp][exp];
    for(int l=exp-1;l>=1;l--)   //回代求解
        coefficient[l]=(Em[l][exp+1]-F(coefficient,l+1,exp))/Em[l][l];
}
//供CalEquation函数调用
double Fit::F(double c[],int l,int m)
{
    double sum=0;
    for(int i=l;i<=m;i++)
        sum+=Em[l-1][i]*c[i];
    return sum;
}

QVector<double> Fit::GetPara(QVector<double> qvx, QVector<double> qvy)
{
     double coefficient[5];
     for(int i=0;i<5;i++) coefficient[i]=0;

     vector<double> vx,vy;
     QVector<double> qcof;

     int exp =2 ;
     int size = qvx.size();
     for (int i=0; i<size; i++)
     {
         vx.push_back(qvx[i]);
         vy.push_back(qvy[i]);
         qDebug()<< qvx[i]<<qvy[i];
     }
      EMatrix(vx,vy,size,exp+1,coefficient);
      for(int i=0;i<5;i++)
      {
          qcof.append(coefficient[i]);
      }
      return qcof;
}
