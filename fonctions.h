#ifndef _FONCTIONS_H

#include "Dense"


// test function parameters
static double c(0.5), nu(0.01);

//adaptation parameters 
static double param_min(1.);

// adaptation test function
double u(const double & x);

//second derivative 
double ddu(const double & x);

//metric function
double metric(const double & x);

//elementary matrix
const Eigen::Matrix<double,2,2> Melem(const double &x1, const double &x2)  ;


#define _FONCTIONS_H
#endif