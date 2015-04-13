#include "KolmogorovTest.hh"





/*
The returned value prob is a calculated confidence level which gives a
 statistical test for compatibility of a and b.
 Values of prob close to zero are taken as indicating a small probability
 of compatibility. For two point sets drawn randomly from the same parent
 distribution, the value of prob should be uniformly distributed between
 zero and one.
   in case of error the function return -1
   If the 2 sets have a different number of points, the minimum of
   the two sets is used.
  */

double KolmogorovTest::calculate ( EDF* edf1 , EDF* edf2)
{


     double prob = -1;

     vector<double> * vals1 = edf1->getValuesSorted();
     vector<double> * vals2 = edf2->getValuesSorted();

// code is mostle copy from root TMath::KolmogorovTest

     int na = vals1->size();
     int nb = vals2->size();
//     Constants needed
     double rna = na;
     double rnb = nb;
     double sa  = 1./rna;
     double sb  = 1./rnb;
     double rdiff = 0;
     double rdmax = 0;
     int ia = 0;
     int ib = 0;
   
   
   bool ok = false;
   for (int i=0;i<na+nb;i++) {
      if ((*vals1)[ia] < (*vals2)[ib]) {
         rdiff -= sa;
         ia++;
         if (ia >= na) {ok = true; break;}
      } else if ((*vals1)[ia] > (*vals2)[ib]) {
         rdiff += sb;
         ib++;
         if (ib >= nb) {ok = true; break;}
      } else {
         // special cases for the ties 
         double x = (*vals1)[ia];
         while((*vals1)[ia] == x && ia < na) {
            rdiff -= sa;
            ia++;
         }
         while((*vals2)[ib] == x && ib < nb) {
            rdiff += sb;
            ib++;
         }
         if (ia >= na) {ok = true; break;}
         if (ib >= nb) {ok = true; break;}
      }
      rdmax =  max(rdmax, abs(rdiff) );
   }
   
   if (ok) {
      rdmax = max(rdmax,abs(rdiff));
      double z = rdmax * sqrt(rna*rnb/(rna+rnb));
      prob = KolmogorovProb(z);
   }
      // debug printout
   //if (opt.Contains("D")) {
//      cout << " Kolmogorov Probability = "<< prob " <<, Max Dist = " << rdmax << "\n";
   //}
   //if(opt.Contains("M")) return rdmax;
   return prob;
   
}


double KolmogorovTest::KolmogorovProb(double z) {
    
   // Calculates the Kolmogorov distribution function,
   //Begin_Html
   /*
   <img src="gif/kolmogorov.gif">
   */
   //End_Html
   // which gives the probability that Kolmogorov's test statistic will exceed
   // the value z assuming the null hypothesis. This gives a very powerful
   // test for comparing two one-dimensional distributions.
   // see, for example, Eadie et al, "statistocal Methods in Experimental
   // Physics', pp 269-270).
   //
   // This function returns the confidence level for the null hypothesis, where:
   //   z = dn*sqrt(n), and
   //   dn  is the maximum deviation between a hypothetical distribution
   //       function and an experimental distribution with
   //   n    events
   //
   // NOTE: To compare two experimental distributions with m and n events,
   //       use z = sqrt(m*n/(m+n))*dn
   //
   // Accuracy: The function is far too accurate for any imaginable application.
   //           Probabilities less than 10^-15 are returned as zero.
   //           However, remember that the formula is only valid for "large" n.
   // Theta function inversion formula is used for z <= 1
   //
   // This function was translated by Rene Brun from PROBKL in CERNLIB.

   double fj[4] = {-2,-8,-18,-32}, r[4];
   const double w = 2.50662827;
   // c1 - -pi**2/8, c2 = 9*c1, c3 = 25*c1
   const double c1 = -1.2337005501361697;
   const double c2 = -11.103304951225528;
   const double c3 = -30.842513753404244;

   double u = abs(z);
   double p;
   if (u < 0.2) {
      p = 1;
   } else if (u < 0.755) {
      double v = 1./(u*u);
      p = 1 - w*( exp(c1*v) + exp(c2*v) + exp(c3*v))/u;
   } else if (u < 6.8116) {
      r[1] = 0;
      r[2] = 0;
      r[3] = 0;
      double v = u*u;
      int maxj = max(1, Nint(3./u) );
      for (int j=0; j<maxj;j++) {
         r[j] = exp(fj[j]*v);
      }
      p = 2*(r[0] - r[1] +r[2] - r[3]);
   } else {
      p = 0;
   }
   return p;

}


int KolmogorovTest::Nint( double x) 
{
   // Round to nearest integer. Rounds half integers to the nearest
   // even integer.
   int i;
   if (x >= 0) {
      i = int(x + 0.5);
      if ( i & 1 && x + 0.5 == double(i) ) i--;
   } else {
      i = int(x - 0.5);
      if ( i & 1 && x - 0.5 == double(i) ) i++;
   }
   return i;

}

