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

     cout << "Analysis::save()"<<endl;


     char fileName[200];
     const char * filePrefix = this->settings->getFullOutputFilesPrefix().c_str();
     const char * storagePath = this->settings->getStoragePath();



     // do save
     if ( this->meanR!=nullptr ) {
          cout << "saving meanR"<<endl;

          sprintf ( fileName,"%s/%s_mean_r_squared.txt",storagePath, filePrefix );

          ofstream output ( fileName );

          output << "# t\t<x^2 + y^2>\n";

          for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
               MeanRsquared * mr = ( it->second );

//                cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;

               output << it->first << "\t" << mr->getMeanValue() << endl;
          }
          output.close();
     }


     if ( this->marginalDistributions!=nullptr ) {

          cout << "saving marginalDistributions"<<endl;

          
          double deltaT = this->settings->get ( "KSTEST_DELTA_T" ); //time interval between two distibutions
          
	  
	  this->saveKolmogorovTestResults(0.02);
	  this->saveKolmogorovTestResults(0.04);
	  this->saveKolmogorovTestResults(0.06);
	  this->saveKolmogorovTestResults(0.08);
	  this->saveKolmogorovTestResults(0.1);
	  this->saveKolmogorovTestResults(0.15);
	  this->saveKolmogorovTestResults(0.2);
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

     cout << "Analysis::calculate(): time iteration start" <<endl;
     //vector< MeanRsquared* > * rsqrd = new vector<MeanRsquared *>();
     //vector< MarginalDistributions*>  * marginals = new vector<MarginalDistributions * > ();


     vector<Datafile*>* files = this->trajIterator->getDatafiles();

     // iterate over time moments
     // fill analysis classes with (x,t)(t) data
     for ( double t = starttime; t <= maxT;  t+=dt ) {

          //cout << " t = " << t << endl;



          MeanRsquared * mr = new MeanRsquared();
          MarginalDistributions * marginalDistr = new MarginalDistributions ( t );

//        // loop over datafiles and fill analysis classes
          for ( auto f = files->begin(); f!=files->end(); ++f ) {

               double x = ( *f )->read();
               double y = ( *f )->read();
//                cout << "(" << x << ","<<y<<")"<<endl;


               mr->add ( x,y );
               marginalDistr->add ( x,y );
          }

          this->meanR->insert ( std::make_pair ( t, mr ) );


          this->marginalDistributions->push_back ( marginalDistr );

     }
     cout << "Analysis::calculate(): time iteration end" <<endl;

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
     //this->checkDatafiles();
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
     this->marginalDistributions = new vector<MarginalDistributions*>();
}

void Analysis::deleteAnalysis()
{



     if ( this->meanR!=nullptr ) {
          cout << "deleting meanR"<<endl;

          for ( auto it = meanR->begin(); it!= meanR->end(); ++it ) {
               MeanRsquared * mr = ( it->second );

               //cout << "t = " << it->first  << "\t < r^2 >  = " << mr->getMeanValue() <<endl;
               delete mr;
          }

          delete this->meanR;
          this->meanR = nullptr;
     }

     //
//

     if ( this->marginalDistributions!=nullptr ) {
          cout << "deleting marginalDistributions"<<endl;
          for ( auto it = marginalDistributions->begin(); it!= marginalDistributions->end(); ++it ) {
               MarginalDistributions * distributions = ( *it );

               // cout << "t = " << meanR->getT() << "\t < r^2 >  = " << meanR->getMeanValue() <<endl;

               //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;

               delete distributions;
          }

          delete marginalDistributions;
     }



}



void Analysis::saveKolmogorovTestResults ( double deltaT )
{

     char datafileNameX[200];
     char datafileNameY[200];
     
     char dataFullPathX[200];
     char dataFullPathY[200];
     
     char datafileNameXplot[200];
     char datafileNameYplot[200];

     double dt = this->settings->getDt();
     
     if ( deltaT< dt ) {
          deltaT= 0.02;
          cout << "deltaT not set in settings, defaulting to " << deltaT <<endl;
     }

     double deltaN = deltaT/dt;
     cout << " DELTA_T = " << deltaT << "\t delta N = " << deltaN << endl;

//        cout << "storagepath="  << storagePath <<endl;
//        cout << "filePrefix="<< filePrefix <<endl;

     sprintf ( datafileNameX,"%s_KStest_X_deltaT_%2.3f.txt", this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
     sprintf ( dataFullPathX,"%s/%s",this->settings->getStoragePath(), datafileNameX );
     ofstream ksXout ( dataFullPathX );

     sprintf ( datafileNameXplot,"%s/%s_KStest_X_deltaT_%2.3f.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
     ofstream ksXplt ( datafileNameXplot );


     cout << "datafileNameX:" << datafileNameX<<"\n ksXout:" << dataFullPathX << "\nksXplt:"<< datafileNameXplot << endl;
     
     
     ksXplt << "reset\n";

     ksXplt << "set title ' marg. distr. X  {/Symbol a} = " << this->settings->getJumpsParameter();
     ksXplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
     ksXplt << " {/Symbol D}t = " << deltaT << "'\n";

     ksXplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     ksXplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_KStest_X_deltaT_"<< deltaT <<".eps\"\n";

     ksXplt << "set xlabel \"t\"\n";
     ksXplt << "set ylabel \"K-S D\"\n";

     ksXplt << "plot './"<< datafileNameX <<"' using 1:2 w lp notitle\n";


//          cout << "storagepath="  << storagePath <<endl;
//          cout << "filePrefix="<< filePrefix <<endl;
     sprintf ( datafileNameY,"%s_KStest_Y_deltaT_%2.3f.txt", this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
     sprintf ( dataFullPathY,"%s/%s",this->settings->getStoragePath(), datafileNameY );
     ofstream ksYout ( dataFullPathY );

     sprintf ( datafileNameYplot,"%s/%s_KStest_Y_deltaT_%2.3f.plt",this->settings->getStoragePath(), this->settings->getFullOutputFilesPrefix().c_str(), deltaT );
     ofstream ksYplt ( datafileNameYplot );
     
     cout << "datafileNameY:" << datafileNameY<<"\n ksYout:" << dataFullPathY << "\nksYplt:"<< datafileNameYplot << endl;
     
     
     ksYplt << "reset\n";

     ksYplt << "set title ' marg. distr. Y  {/Symbol a} = " << this->settings->getJumpsParameter();
     ksYplt << " {/Symbol b} = " << this->settings->getWaitingTimesParameter();
     ksYplt << " {/Symbol D}t = " << deltaT << "'\n";

     ksYplt << "set terminal post eps size 12,7 enhanced color font 'Helvetica,35' linewidth 2;\n";
     ksYplt << "set output \""<< this->settings->getFullOutputFilesPrefix() << "_KStest_Y_deltaT_"<< deltaT <<".eps\"\n";

     ksYplt << "set xlabel \"t\"\n";
     ksYplt << "set ylabel \"K-S D\"\n";

     ksYplt << "plot './"<< datafileNameY <<"' using 1:2 w lp notitle\n";
     
     
     
     
     
     
     
     
     ksXout <<"# t \t K-S test D (marginal X distr, delta T = " << deltaT<<")\n";
     ksYout <<"# t \t K-S test D (marginal Y distr, delta T = " << deltaT<<")\n";

     int size = this->marginalDistributions->size() - deltaN;

     for ( int c = 0; c < size ; c++ ) {

          MarginalDistributions * distributions = this->marginalDistributions->at ( c );

          double t = distributions->getT();
          //double secondT = t + deltaT;
          //bool secondTexists = ( this->marginalDistributions->count( secondT) == 1 );
          MarginalDistributions * secondDist = this->marginalDistributions->at ( c + deltaN );

          double secondT = secondDist->getT();

//                   cout << "t = " << t << "\t second t  = " << secondT ;

          //test << meanR->getT() << "\t" << meanR->getMeanValue() << endl;


          double KStestX = KolmogorovTest::calculate ( distributions->getXedf(), secondDist->getXedf() );
          double KStestY = KolmogorovTest::calculate ( distributions->getYedf(), secondDist->getYedf() );
//                   cout << " KS x = " << KStestX << " \t KS y = " << KStestY << endl;

          ksXout << t <<"\t" << KStestX <<"\n";
          ksYout << t <<"\t" << KStestY <<"\n";

     }


     ksXout.close();
     ksYout.close();

     ksXplt.close();
     ksYplt.close();
}


