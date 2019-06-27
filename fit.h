#ifndef FIT_H
#define FIT_H
#include <iostream>
#include <vector>
#include <cmath>
#include<QDebug>
using namespace std;
class Fit
{
public:
    Fit();
    double sum(vector<double> Vnum, int n);
    double MutilSum(vector<double> Vx, vector<double> Vy, int n);
    double RelatePow(vector<double> Vx, int n, int ex);
    double RelateMutiXY(vector<double> Vx, vector<double> Vy, int n, int ex);
    void EMatrix(vector<double> Vx, vector<double> Vy, int n, int ex, double coefficient[]);
    void CalEquation(int exp, double coefficient[]);
    double F(double c[],int l,int m);
    QVector<double> GetPara(QVector<double> vx, QVector<double> vy);
    double Em[6][4];


};

#endif // FIT_H
