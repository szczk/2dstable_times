#ifndef __UTILITY_HH__
#define __UTILITY_HH__

#include <gsl/gsl_fit.h>


using namespace std;

/**
 * Additional utilities
 * 
 */

class Utility {
    
private:
    
    
    
public:  


    // do linear regression fit
    // for Y = c0 + c1 * x
    static int linearRegression( const double * x, const double * y, const size_t n, double * c0, double * c1);
    
    
    
};


#endif
