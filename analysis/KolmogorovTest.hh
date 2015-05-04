#ifndef __KOLMOGOROV_TEST__
#define __KOLMOGOROV_TEST__

#include "EDF.hh"


using namespace std;





// https://asaip.psu.edu/Articles/beware-the-kolmogorov-smirnov-test



class KolmogorovTest {



     // http://root.cern.ch/root/html/TMath.html#TMath:KolmogorovProb
     static double KolmogorovProb ( double z );


     static int Nint ( double x );

public:


     /**
      * calculate kolmogorov-smirnov test value
      *
      *
      * see
      * http://root.cern.ch/root/html/src/TMath.cxx.html#SX5s7D
      *
      *
      *  The returned value prob is a calculated confidence level which gives a
      *  statistical test for compatibility of a and b.
      *  Values of prob close to zero are taken as indicating a small probability
      *  of compatibility. For two point sets drawn randomly from the same parent
      *  distribution, the value of prob should be uniformly distributed between
      *  zero and one.
      *  in case of error the function return -1
      *  if the 2 sets have a different number of points, the minimum of
      *  the two sets is used.

      */
     static double calculate ( EDF* , EDF* );

};
#endif
