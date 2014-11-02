#ifndef __MARGINAL_DISTRIBUTIONS__
#define __MARGINAL_DISTRIBUTIONS__

#include "EDF.hh"



using namespace std;

/**
 * marginal distributions (x's and y's)
 *
 * for a single time t
 */


class MarginalDistributions {

private:
     double t;

     EDF * marginalX;
     EDF * marginalY;


public:

     MarginalDistributions ( double t );
     ~MarginalDistributions();


     void add ( double x, double y );


     double getT() {
          return this->t;
     }

     EDF * getXedf() {
          return this->marginalX;
     }
     EDF * getYedf() {
          return this->marginalY;
     }
};

#endif
