#ifndef __TRAJECTORIES_DATAFILES_ITERATOR_HH__
#define __TRAJECTORIES_DATAFILES_ITERATOR_HH__

#include "Settings.hh"
#include "Datafile.hh"

using namespace std;


/**
 * 
 * 
 * tool class to load datafiles with trajectories 
 * and easily iterate over them
 * 
 * 
 */

class TrajectoriesDatafilesIterator {
private:
    
    Settings * settings;
    
    vector<Datafile *> * datafiles
    
    
    void init();
    void close();
        
    
public:
    TrajectoriesDatafilesIterator(Settings *);
    ~TrajectoriesDatafilesIterator();  
    
    
    
    
    
    
    
};



#endif