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
     
     
     
     if(settings.multipleOutputs()) {
       
       int maxNum = settings.getMultipleOutputFilenum(); 
       
       for(int filenum = 1; filenum <= maxNum ; filenum++ )
       {
        
          for ( int nt =0; nt < ntrajectories ; nt++ ) {
       
            if ( nt%tenPerc==0 ) {
                cout << nt<<"/"<<ntrajectories<<endl;
            }
          
            string outputFile = settings. getMultiDatafileName( settings.getDataPath(), filenum,  nt);
        
            cout << "opening " << outputFile << endl;
        
            Datafile * datafile = Datafile::open ( outputFile.c_str() );
            if(datafile->ok()) {
              datafiles->push_back(datafile);
            }
            else {
             delete datafile; 
            }
          }
       }
     }
     else 
     {
          for ( int nt =0; nt < ntrajectories ; nt++ ) {
       
            if ( nt%tenPerc==0 ) {
                cout << nt<<"/"<<ntrajectories<<endl;
            }
          
            string outputFile = settings.getDatafileName( settings.getDataPath(), nt);
        
            cout << "opening " << outputFile << endl;
        
            Datafile * datafile = Datafile::open ( outputFile.c_str() );
            
            if(datafile->ok()) {
              datafiles->push_back(datafile);
            }
            else {
             delete datafile; 
            }
          }
     }
     
     
     
     
     
         
     cout << endl << endl << " opened trajectories files: " << datafiles->size() << endl;

     
     
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
     
     
     
     
     
     

     

     // close all datafiles
     
     
     cout << endl << " closing datafiles "<< endl;
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


