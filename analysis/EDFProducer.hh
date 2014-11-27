#ifndef __EDF_PRODUCER_HH__
#define __EDF_PRODUCER_HH__


#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include "../core/Settings.hh"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * for producing empirical cumulative distribution functions
 *
 * for 2d data, so it works on marginal distributions
 *
 *
 */



class EDFProducer {

private:
     Settings * settings;
     vector<double> * xValues;
     vector<double> * yValues;

     bool alreadySaved;

     double time;
     void init();
     void save();
     
     // check for NaN
     bool isNan(volatile double &);
     
     // check if value is ok (not, NaN, not ~1e-300, etc)
     bool isOk(volatile double &);
     
public:

     EDFProducer ( Settings* );
     ~EDFProducer();


     void fill ( double x, double y );
     void close();

     void setTime ( double t ) {
          if ( t>=0.0 ) this->time = t;
     }

};


#endif
