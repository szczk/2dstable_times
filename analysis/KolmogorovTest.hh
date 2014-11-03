#ifndef __KOLMOGOROV_TEST__
#define __KOLMOGOROV_TEST__

#include "EDF.hh"


using namespace std;





// https://asaip.psu.edu/Articles/beware-the-kolmogorov-smirnov-test



class KolmogorovTest {
  
  
  
  
public:
  
  
  /**
   * calculate kolmogorov-smirnov test value
   * 
   * 
   * see
   * http://root.cern.ch/root/html/src/TMath.cxx.html#SX5s7D
   * 
   */
  static double calculate(EDF* , EDF*);
  
};
#endif