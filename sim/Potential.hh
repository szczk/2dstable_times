#ifndef __POTENTIAL_HH__
#define __POTENTIAL_HH__

#include "../core/Randoms.hh"
#include "../core/Settings.hh"
// #include "../main.hh"

using namespace std;

/**
 * 2D potential
 * 
 * 
 *  V(x,y) = 1/4  (x^2 + y^2)^2
 *    
 *  grad V(x,y) = [ x(x^2 + y^2) ,  y(x^2 + y^2)
 * 
 * 
 * !! tak naprawde zwraca gradient V(x,y) !!
 */
class Potential {
  
private:
  
  
  /**
  * Initialize random number generator & stuff
  */
  void init();

  /**
  *  destroy everything and close
  */
  void destroy();
  
     
     
public:
  Potential();
  virtual ~Potential() =0 ;
  
  virtual const char * toString();
  
  virtual vec operator()(const vec);
  
  
  
};


#endif

