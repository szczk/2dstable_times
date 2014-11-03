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


     double maxT = settings.get ( "maxT" );
     double dt = settings.get ( "dt" );
     double starttime = settings.get ( "starttime" );

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
     int shouldbe = ( ( maxT-starttime ) /dt );
     cout  << " trajectories count: " << count << endl;
     cout << "t0 = 0 , tmax = " << maxT <<" dt= " << dt << ", so in datafiles should be: 2*"<< shouldbe << " points"<<endl;
     if ( shouldbe*2 == count ) {
          cout << "it is! all ok" << endl;
     } else {
          cout << "it isnt! " << count << " != " << shouldbe << endl;
          delete trajIterator;
          return -1;
     }


     
     ///================================================================================
       
     vector<Datafile*>* files = trajIterator->getDatafiles();

     



     cout << "time iteration start" <<endl;
     vector< MeanRsquared* > * rsqrd = new vector<MeanRsquared *>();
     vector< MarginalDistributions*>  * marginals = new vector<MarginalDistributions * > ();  
     

     // iterate over time moments
     for( double tt = starttime; tt <= maxT;  tt+=dt ) {
       
       cout << " t = " << tt <<endl;
       
       
       
       MeanRsquared * meanR = new MeanRsquared(tt);
       MarginalDistributions * marginalDistribution = new MarginalDistributions(tt);
       
//        // loop over datafiles and fill analysis classes
       for( auto f = files->begin(); f!=files->end(); ++f) {
       
            double x = (*f)->read();
            double y = (*f)->read();
	 //cout << "(" << x << ","<<y<<")"<<endl;
	 
	 
            meanR->add(x,y);
            marginalDistribution->add(x,y);
       }
       
       rsqrd->push_back(meanR);
       marginals->push_back(marginalDistribution);
       
     }

     //=== end of loop over datafile
     
     
     
     
     cout << "deleting meanR"<<endl;
     
     ofstream test("out.txt");
     
     for( auto it = rsqrd->begin(); it!= rsqrd->end(); ++it) {
       MeanRsquared * meanR = (*it);
       
       cout << "t = " << meanR->getT() << "\t < r^2 >  = " << meanR->getMeanValue() <<endl;
       
       test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;
       
       delete meanR;
     }
     test.close();
     
     delete rsqrd;
     
     
     
     for( auto it = marginals->begin(); it!= marginals->end(); ++it) {
       MarginalDistributions * distributions = (*it);
       
      // cout << "t = " << meanR->getT() << "\t < r^2 >  = " << meanR->getMeanValue() <<endl;
       
       //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;
       
       delete distributions;
     }
     
     delete marginals;
     
     
     
     delete trajIterator;



     ///===================================================================================================


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


