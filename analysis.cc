#include "main.hh"
#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include <fstream>
#include <vector>
#include <sys/resource.h>
#include "stdio.h"

int main ( int argc, char **argv )
{
     cout << "\n\n" << flush;
     System& sys = System::getInstance();
     sys.start();
     sys.printInfo();

     Settings& settings = Settings:: getInstance ( "settings.dat" );
     settings.readCommandLineParameters ( argc,argv );
     settings.printParameters();
     ///==================================================================================
     // analysis
     Analysis * analysis = new Analysis ( &settings );
     // when deleting analysis, iterator will not be deleted!

     // < r^2>    x, y ,t
     // KS      (x),(y),t
     // KS 2d  (x,y),t

     double ntrajectories = settings.getNtrajectories();
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.1 ) : 1;
     cout << "opening trajectories files"<<endl;

     if ( settings.multipleOutputs() ) {
          int maxNum = settings.getMultipleOutputFilenum();
//           bool first = true;
          for ( int filenum = 1; filenum <= maxNum ; filenum++ ) {
               for ( int nt =0; nt < ntrajectories ; nt++ ) {
                    if ( nt%tenPerc==0 ) {
                         cout << nt<<"/"<<ntrajectories<<endl;
                    }

                    string outputFile = settings.getMultiDatafileName ( settings.getDataPath(), filenum,  nt );
                    cout << "opening " << outputFile << "...";

                    Datafile * datafile = Datafile::open ( outputFile.c_str() );
                    if ( datafile->ok() ) {
                         cout << "ok"<<endl;
                         analysis->fillFromFile ( datafile );
                         delete datafile;
                    }
               }
          }
     } else {
          for ( int nt =0; nt < ntrajectories ; nt++ ) {

               if ( nt%tenPerc==0 ) {
                    cout << nt<<"/"<<ntrajectories<<endl;
               }
               string outputFile = settings.getDatafileName ( settings.getDataPath(), nt );
               cout << "opening " << outputFile << "...";
               Datafile * datafile = Datafile::open ( outputFile.c_str() );
               if ( datafile->ok() ) {
                    cout << "ok"<<endl;
                    analysis->fillFromFile ( datafile );
               }
               delete datafile;
          }
     }

     analysis->calculate()->save()->close();
     delete analysis;

     ///===================================================================================================

     struct rlimit rp;
     int code = getrlimit ( RLIMIT_NOFILE, &rp );
     cout <<"return code:" << code << endl;
     cout << "RLIMIT_NOFILE: soft:" << rp.rlim_cur << "\t hard:" << rp.rlim_max << endl;


     sys.finish();
     sys.printTimeSummary();

     return 0;
}


