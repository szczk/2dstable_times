#ifndef __SIMULATION__HH__
#define __SIMULATION__HH__

#include "../core/Settings.hh"
#include "../core/Randoms.hh"
#include "../tools/Datafile.hh"

#include "QuadraticPotential.hh"
#include "SquarePotential.hh"


using namespace std;



class Simulation {

private:
     Settings * settings;
     Randoms * rand;
     Potential * potential;
  
     void init();
     void cleanUp();
     
     
     void reset();

public:

     Simulation ( Settings* s );
     ~Simulation();
     
     
     
     
     void run ( Datafile* datafile );


};



#endif
