#include "TrajectoriesDatafilesIterator.hh" 






TrajectoriesDatafilesIterator::TrajectoriesDatafilesIterator(Settings * s ) : datafiles(nullptr)
{
    this->init();
    
}


TrajectoriesDatafilesIterator:: ~TrajectoriesDatafilesIterator() {
 
    this->delete();
    
}


void TrajectoriesDatafilesIterator:: init() {

    this->datafiles = new vector<Datafile*>();
    
    
}

void TrajectoriesDatafilesIterator:: close() {
    
    if( this->datafiles != nullptr) {
     
        //close all files and delete 
     
        cout << endl << " closing datafiles "<< endl;
        for( int j = 0 ; j < this->datafiles->size() ; j++) {
      
        Datafile * f = this->datafiles->at(j);
        f->close();
        delete f;
       
     }
     
     
     delete this->datafiles;
    }
    
}
