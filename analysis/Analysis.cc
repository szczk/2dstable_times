#include "Analysis.hh"



Analysis::Analysis ( Settings*s ) : settings ( s ), meanR ( nullptr ) ,  calculated ( nullptr ),inputOk ( false )
{


     this->initAnalysis();
}

Analysis:: ~Analysis()
{
}



void Analysis::save()
{
     if ( !calculated ) {
          cout << "Analysis::calculate() not called!"<<endl;
          return;
     }

     char fileName[200];
     const char * filePrefix = this->settings->getFullOutputFilesPrefix().c_str();
     const char * storagePath = this->settings->getStoragePath();

     sprintf ( fileName,"%s/%s_mean_r_squared.txt",storagePath, filePrefix );


     // do save
     if ( this->meanR!=nullptr ) {
          cout << "saving meanR"<<endl;

          ofstream output ( fileName);
	  output << "# t\t<x^2 + y^2>\n";
	  
          for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
               MeanRsquared * mr = ( it->second );

//                cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;

               output << it->first << "\t" << mr->getMeanValue() << endl;

               delete mr;
          }
          output.close();

          delete this->meanR;
          this->meanR = nullptr;
     }


}


void Analysis::calculate()
{
     if ( calculated ) {
          return;
     }

     // iterate over time
     double maxT = settings->get ( "maxT" );
     double dt = settings->get ( "dt" );
     double starttime = settings->get ( "starttime" );

     cout << "time iteration start" <<endl;
     //vector< MeanRsquared* > * rsqrd = new vector<MeanRsquared *>();
     //vector< MarginalDistributions*>  * marginals = new vector<MarginalDistributions * > ();


     vector<Datafile*>* files = this->trajIterator->getDatafiles();

     // iterate over time moments
     // fill analysis classes with (x,t)(t) data
     for ( double t = starttime; t <= maxT;  t+=dt ) {

          cout << " t = " << t << endl;



          MeanRsquared * mr = new MeanRsquared();
          //MarginalDistributions * marginalDistribution = new MarginalDistributions ( tt );

//        // loop over datafiles and fill analysis classes
          for ( auto f = files->begin(); f!=files->end(); ++f ) {

               double x = ( *f )->read();
               double y = ( *f )->read();
//                cout << "(" << x << ","<<y<<")"<<endl;


               mr->add ( x,y );
               //marginalDistribution->add ( x,y );
          }

          this->meanR->insert ( std::make_pair ( t, mr ) );
          //marginals->push_back ( marginalDistribution );

     }


     calculated = true;
}


void Analysis::checkDatafiles()
{
     double maxT = settings->get ( "maxT" );
     double dt = settings->get ( "dt" );
     double starttime = settings->get ( "starttime" );

     int count = trajIterator->getCount();
     int shouldbe = ( ( maxT-starttime ) /dt );
     cout  << " trajectories count: " << count << endl;
     cout << "t0 = 0 , tmax = " << maxT <<" dt= " << dt << ", so in datafiles should be: 2*"<< shouldbe << " points"<<endl;
     if ( shouldbe*2 == count ) {
          cout << "it is! all ok" << endl;
          this->inputOk = true;
     } else {
          cout << "it isnt! " << count << " != " << shouldbe << endl;
          this->inputOk = false;
     }
}


bool Analysis::inputOK()
{
     this->checkDatafiles();
     return this->inputOk;
}

void Analysis::close()
{
     cout << "Analysis::close()"<<endl;
     this->deleteAnalysis();
}


void Analysis::initAnalysis()
{
     this->meanR = new map<double, MeanRsquared*>();
}

void Analysis::deleteAnalysis()
{



     if ( this->meanR!=nullptr ) {
          cout << "deleting meanR"<<endl;

          //ofstream test ( "out.txt" );
          for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
               MeanRsquared * mr = ( it->second );

               cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;

               //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;

               delete mr;
          }
          // test.close();

          delete this->meanR;
          this->meanR = nullptr;
     }



}



