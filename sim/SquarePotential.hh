#ifndef __SQ_POTENTIAL_HH__
#define __SQ_POTENTIAL_HH__

#include "Potential.hh"
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
class SquarePotential : public Potential {

public:
     virtual ~SquarePotential() {};

     vec operator() ( const vec X ) {

          // paraboliczny
// V(x,y) = 1/2  (x^2 + y^2)

          //grad V(x,y) = [ x , y ]

          vec VX;

          VX.x = X.x;
          VX.y = X.y;



          // to powoduje bledy!
//   double limit = 20.0;
//   if(VX.x > limit) VX.x = limit;
//   else if(VX.x < -limit) VX.x = -limit;
//
//   if(VX.y > limit) VX.y = limit;
//   else if(VX.y < -limit) VX.y = -limit;
//

          return VX;
     }


      const char* toString() {
          return "V(x,y) = 1/2  (x^2 + y^2)";
     }

     bool inLimit( vec X) {
         return true;
     }
     
     vec getExact(const vec X, double dt) {
       
         vec NX;
         
         NX.x = exp(-dt) * X.x;
         NX.y = exp(-dt) * X.y;
         
         
         return NX;
     }
};


#endif

