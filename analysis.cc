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
     

     //double maxT = settings.get ( "maxT" );
     double dt = settings.get("dt");

     double ntrajectories = settings.getNtrajectories();
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.1 ) : 1;

  
    
     vector<Datafile *> * datafiles = new vector<Datafile*>();
     
     //open datafiles with trajectories
     
     
     
     
     
     int maxNum = settings.getMultipleOutputFilenum();     
     
     for ( int nt =0; nt < ntrajectories ; nt++ ) {
       
          if ( nt%tenPerc==0 ) {
               cout << nt<<"/"<<ntrajectories<<endl;
          }
         
          string outputFile = settings.getDatafileName( settings.getDataPath(), nt);
	  
	  cout << "opening " << outputFile << endl;
	  
          Datafile * datafile = Datafile::open ( outputFile.c_str() );
	  
	  datafiles->push_back(datafile);
     }
     
     
     
     // analyse
     
     
//      for ( int nt =0; nt < ntrajectories ; nt++ ) {
//        
//           if ( nt%tenPerc==0 ) {
//                cout << nt<<"/"<<ntrajectories<<endl;
//           }
//          
//           string outputFile = settings.getDatafileName( settings.getDataPath(), nt);
// 	  
// 	  cout << "opening " << outputFile << endl;
// 	  
//           Datafile * datafile = Datafile::open ( outputFile.c_str() );
// 
// 	  datafile->close();
//      }

     

     // close all datafiles
     
     for( int j = 0 ; j < datafiles->size() ; j++) {
      
       Datafile * f = datafiles->at(j);
       f->close();
       delete f;
       
     }
     
     
     delete datafiles;



     ///===================================================================================================
     
     
     sys.finish();
     sys.printTimeSummary();

     return 0;
}


