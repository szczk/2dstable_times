#ifndef __ANALYSIS__
#define __ANALYSIS__

#include <map>
#include <vector>

#include "../core/Settings.hh"
#include "../tools/TrajectoriesDatafilesIterator.hh"
#include "../tools/Utility.hh"

#include "MeanRsquared.hh"
#include "MarginalDistributions.hh"

#include "KolmogorovTest.hh"


//delete when not needed
#include "HistogramsProducer.hh"
#include "EDFProducer.hh"


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

//      TrajectoriesDatafilesIterator * trajIterator;

     // analysis modules mapped by time
     map<double, MeanRsquared *> *meanR;
     map<double, MarginalDistributions *> *marginalDistributions;
     //vector<MarginalDistributions*> * marginalDistributions;


     
     
     map<double, HistogramsProducer *> *histogramProducers ;
     map<double, EDFProducer *>  *edfProducers ;


     

     void initAnalysis();
     void deleteAnalysis();


     bool calculated;

//      void checkDatafiles();


     void saveMeanRTestResults();
     
     
     void saveKolmogorovTestResults ( double deltaT );


public:
     Analysis ( Settings * );

     ~Analysis();



//      /**
//       * when deleting Analysis object, this datafile iterator will NOT be deleted!
//       */
//      void setDatafilesIterator ( TrajectoriesDatafilesIterator * iter ) {
//           if ( iter!=nullptr ) {
//                this->trajIterator = iter;
//                this->checkDatafiles();
//           }
//      }


     /*
      * Pass an open datafile to be iterated over t and filled from
      */
     void fillFromFile ( Datafile * );

     /**
      * add data for a given time point t
      */
     void fill ( double t, double x, double y );

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
