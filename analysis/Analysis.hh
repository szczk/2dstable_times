#ifndef __ANALYSIS__
#define __ANALYSIS__

#include <map>
#include <vector>

#include "../core/Settings.hh"
#include "../tools/TrajectoriesDatafilesIterator.hh"

#include "MeanRsquared.hh"
#include "MarginalDistributions.hh"

#include "KolmogorovTest.hh"

using namespace std;


/**
 * over-all analysis interface
 *
 * uses trajectories datafiles iterator to iterate over
 * trajectories and over t
 * and fills all the analysis classes working on a single t
 * and so on
 */

class Analysis {

private:
     Settings * settings;

     TrajectoriesDatafilesIterator * trajIterator;

     // analysis modules mapped by time
     map<double, MeanRsquared *> *meanR;
     vector<MarginalDistributions*> * marginalDistributions;
     
     
    
     void initAnalysis();
     void deleteAnalysis();
     
     
     bool calculated;
     bool inputOk;
     void checkDatafiles();
     
     
     
     void saveKolmogorovTestResults(double deltaT);
     

public:
     Analysis ( Settings * );

     ~Analysis();



     /**
      * when deleting Analysis object, this datafile iterator will NOT be deleted!
      */
     void setDatafilesIterator ( TrajectoriesDatafilesIterator * iter ) {
          if ( iter!=nullptr ) {
               this->trajIterator = iter;
               this->checkDatafiles();
          }
     }

     /**
      * 
      */
     bool inputOK();
     
     
     /**
      * Calculate everything that needs to be calculated
      */
     void calculate();


     /**
      * Save everything that needs to be saved.
      * calculate() should be manuall called first
      * as it is not called automatically
      *
      */
     void save();

     /**
      * close everything and delete objects
      */
     void close();
};

#endif
