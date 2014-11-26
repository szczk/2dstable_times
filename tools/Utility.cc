#include "Utility.hh" 



int Utility::linearRegression(const double * x, const double * y, const size_t n, double * c0, double * c1) 
{  
    double cov00, cov01, cov11, sumsq ;
    
    return gsl_fit_linear( x, 1,  y, 1, n, c0, c1,  &cov00, &cov01, &cov11, &sumsq);
}