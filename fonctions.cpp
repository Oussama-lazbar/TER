#ifndef _FONCTIONS_CPP

#include "fonctions.h"
#include <algorithm>
#include <cmath>


double u(const double & x) 
{
    double f;
    //f = (exp(c*x/(nu - 1))/(c*(1 - exp(c/nu)))) + (x/c) ;
    f = ((2*(exp(50*x) -1)/(1 - exp(50.))) +2*x);
    return f;
}

double ddu(const double &x) 
{
    double f;
    //f = c*(nu -1)*(nu-1)*exp(c*x/(nu - 1))/((1 - exp(c/nu)));
    f = (2*50*50/(1- exp(50)))*exp(50*x);
    return f;
}

double metric(const double & x) 
{
    double a(abs(ddu(x)));
    return sqrt(std::max(a, param_min));
}

const Eigen::Matrix<double,2,2> Melem(const double &x1, const double &x2) 
{
    Eigen::Matrix<double,2,2> M;
    M<<  1, -1,
        -1, 1;
    double a;
    a = 0.5*(metric(x1) + metric(x2));
    M = a*M;
    return M;
}


#define _FONCTIONS_CPP
#endif
