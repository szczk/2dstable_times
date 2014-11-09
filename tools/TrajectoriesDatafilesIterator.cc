#include "TrajectoriesDatafilesIterator.hh"






TrajectoriesDatafilesIterator::TrajectoriesDatafilesIterator ( Settings * s ) : settings ( s ), datafiles ( nullptr ) , count(0)
{
     this->init();


}


TrajectoriesDatafilesIterator:: ~TrajectoriesDatafilesIterator()
{

     this->close();

}


void TrajectoriesDatafilesIterator:: init()
{

     this->datafiles = new vector<Datafile*>();


     this->open();

}

void TrajectoriesDatafilesIterator:: close()
{

     if ( this->datafiles != nullptr ) {

          //close all files and delete

          cout << endl << " closing datafiles "<< endl;
          for ( size_t j = 0 ; j < this->datafiles->size() ; j++ ) {

               Datafile * f = this->datafiles->at ( j );
               f->close();
               delete f;

          }


          delete this->datafiles;
     }

}


void TrajectoriesDatafilesIterator::open()
{
     double ntrajectories = this->settings->getNtrajectories();
     int tenPerc = ( ntrajectories>10 ) ? ( int ) ( ntrajectories*0.1 ) : 1;

     cout << "opening trajectories files"<<endl;

     if ( this->settings->multipleOutputs() ) {

          int maxNum = this->settings->getMultipleOutputFilenum();

          
          bool first = true;

          for ( int filenum = 1; filenum <= maxNum ; filenum++ ) {

               for ( int nt =0; nt < ntrajectories ; nt++ ) {

                    if ( nt%tenPerc==0 ) {
                         cout << nt<<"/"<<ntrajectories<<endl;
                    }

                    string outputFile = this->settings->getMultiDatafileName ( settings->getDataPath(), filenum,  nt );

                    cout << "opening " << outputFile << endl;

                    Datafile * datafile = Datafile::open ( outputFile.c_str() );
                    if ( datafile->ok() ) {

                         int count = datafile->getCount();

                         if ( first ) {
                              this->count = count;
                         }

                         if ( count != this->count ) {
                              cout << " non equal trajectory count! " << cout << " vs " << this->count << "!!!" << endl;
                              throw -1;
                         }

                         datafiles->push_back ( datafile );

                         this->count = count;
                    } else {
                         delete datafile;
                    }
               }
          }
     } else {
          for ( int nt =0; nt < ntrajectories ; nt++ ) {

               if ( nt%tenPerc==0 ) {
                    cout << nt<<"/"<<ntrajectories<<endl;
               }

               string outputFile = settings->getDatafileName ( settings->getDataPath(), nt );

               cout << "opening " << outputFile << endl;

               Datafile * datafile = Datafile::open ( outputFile.c_str() );

               if ( datafile->ok() ) {
                    datafiles->push_back ( datafile );
               } else {
                    delete datafile;
               }
          }
     }

     cout << endl << endl << " opened trajectories files: " << getNumTrajectories() << endl;
     
     
}


int TrajectoriesDatafilesIterator::getNumTrajectories()
{
  if(this->datafiles!=nullptr) {
   return this->datafiles->size(); 
  }
  else return 0;
}
