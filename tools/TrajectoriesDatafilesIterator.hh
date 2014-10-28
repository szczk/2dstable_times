#ifndef __TRAJECTORIES_DATAFILES_ITERATOR_HH__
#define __TRAJECTORIES_DATAFILES_ITERATOR_HH__

#include "../core/Settings.hh"
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
    
    vector<Datafile *> * datafiles;
    
    int count;
    
    void init();
    
        
    void open();
    
public:
    TrajectoriesDatafilesIterator(Settings *);
    ~TrajectoriesDatafilesIterator();  
    
    
    int getNumTrajectories();
    
    
    void close();
    
    
    vector<Datafile*>* getDatafiles() { return this->datafiles; }

    
    /**
     * remember that trajectories are 2D, so actual count whould be count/2
     */
    int getCount() { return this->count; }
};



#endif