#include "main.hh"
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include <fstream>
#include <vector>


#include "analysis/MeanRsquared.hh"
#include "analysis/MarginalDistributions.hh"

int main ( int argc, char **argv )
{
     cout << endl << endl;

     System& sys = System::getInstance();
     sys.start();

     sys.printInfo();

     Settings& settings = Settings:: getInstance ( "settings.dat" );
     settings.readCommandLineParameters ( argc,argv );
     settings.printParameters();


     ///==================================================================================

     //open datafiles with trajectories
     TrajectoriesDatafilesIterator * trajIterator = new TrajectoriesDatafilesIterator ( &settings );



     // analysis
     Analysis * analysis = new Analysis ( &settings );
     // when deleting analysis, iterator will not be deleted!
     analysis->setDatafilesIterator ( trajIterator );


     //  < r^2>    x, y ,t
     //  KS      (x),(y),t
     // KS 2d  (x,y),t




     if ( analysis->inputOK() )  {

          analysis->calculate();

          analysis->save();

          analysis->close();
     } else {
          cout << "Analysis input not ok!"<<endl;

          analysis->close();

          return -1;
     }









     delete analysis;

     delete trajIterator;



     ///===================================================================================================


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


