#include "main.hh"
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include <fstream>
#include <vector>




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


     double maxT = settings.get ( "maxT" );
     double dt = settings.get ( "dt" );
     double starttime = settings.get("starttime");

     //open datafiles with trajectories

     TrajectoriesDatafilesIterator * trajIterator = new TrajectoriesDatafilesIterator ( &settings );






     // analysis



     /**
      * all trajectories loaded at the same time
      *
      * so we have all (x,y) in a given time t
      *
      * create CDF (EDF)  for x and y in given t
      *
      * from EDF for  two different t calculate K-S test
      *
      */

     int count = trajIterator->getCount();
     int shouldbe = ((maxT-starttime)/dt);
     cout  << " trajectories count: " << count << endl;
     cout << "t0 = 0 , tmax = " << maxT <<" dt= " << dt << ", so in datafiles should be: 2*"<< shouldbe << " points"<<endl;
     if( shouldbe*2 == count) {
      cout << "it is! all ok"; 
     }
     else {
      cout << "it isnt! " << count << " != " << shouldbe << endl;
      delete trajIterator;
      return -1;
     }







     delete trajIterator;



     ///===================================================================================================


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


