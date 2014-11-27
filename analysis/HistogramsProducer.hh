#ifndef __HISTOGRAMSPRODUCER_HH__
#define __HISTOGRAMSPRODUCER_HH__


#include <gsl/gsl_histogram2d.h>
#include <gsl/gsl_histogram.h>
#include "../core/Settings.hh"

using namespace std;

/**
 * Tool for producing histograms, plots etc
 *
 * histograms are made for specific time (t) in simulation
 * if not set, maxT (end of simulation) will be used!
 *
 */

class HistogramsProducer {



private:
     Settings * settings;
     bool alreadySaved;
     
     double range;
     double xmin,xmax;
     double ymin,ymax;

     double xbins;
     double ybins;

     double dx;
     double dy;
     
     
     // 
     double time; 
     
     //histogram 2d
     gsl_histogram2d * histogram;

     //histogramy
     gsl_histogram * osX_histo;
     gsl_histogram * osY_histo;


     void initHistograms();
     
     void init();
     void save();

public:
     HistogramsProducer ( Settings * s );
     ~HistogramsProducer();



     void close();

     
     void fill(double x, double y);


     void setTime(double t) {
      if(t>=0.0) this->time = t; 
     }
};

#endif
