#ifndef __ANALYSIS__
#define __ANALYSIS__


#include "../core/Settings.hh"

using namespace std;


/**
 * analysis interface for a single time t
 * 
 */

class Analysis {

private:
     Settings * settings;

public:
     Analysis(Settings *);
     
     ~Analysis();
     

     /**
      * Add a set of (x,y) values for a given time t
      */
     void addValues ( double t, double x, double y );

     /**
      *
      */
     void save();
     
};

#endif
