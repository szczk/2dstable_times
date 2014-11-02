#ifndef __EDF_HH__
#define __EDF_HH__

#include "../core/Settings.hh"

#include <vector>
#include <algorithm>
#include <iostream>




using namespace std;


/**
 * class producing EDF (CDF) from input data
 */


class EDF {

private:
     vector<double> * values;

     bool alreadySaved;

     //double time;
     void init();
     //void save();
     
     // check for NaN
     bool isNan(volatile double &);
     
     // check if value is ok (not, NaN, not ~1e-300, etc)
     bool isOk(volatile double &);
     
     
     void calculate();
     
public:

     EDF ( );
     virtual ~EDF();


     void fill ( double x );
     void close();


     
     void save();

};

#endif