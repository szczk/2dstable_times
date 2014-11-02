#include "KolmogorovTest.hh"





// 

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
      prob = TMath::KolmogorovProb(z);
   }
      // debug printout
   //if (opt.Contains("D")) {
//      cout << " Kolmogorov Probability = "<< prob " <<, Max Dist = " << rdmax << "\n";
   //}
   //if(opt.Contains("M")) return rdmax;
   return prob;
   
}

