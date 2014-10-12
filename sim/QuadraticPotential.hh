#ifndef __QUAD_POTENTIAL_HH__
#define __QUAD_POTENTIAL_HH__

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
class QuadraticPotential : public Potential {



public:
     virtual ~QuadraticPotential() { };


     vec operator() ( const vec X ) {

// V(x,y) = 1/4  (x^2 + y^2)^2

          //grad V(x,y) = [ x(x^2 + y^2) ,  y(x^2 + y^2)

          vec VX;
          // czwartego stopnia
          double x_squared = X.x*X.x;
          double y_squared = X.y*X.y;

          VX.x = X.x* ( x_squared + y_squared );
          VX.y = X.y* ( x_squared + y_squared );



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

     virtual const char* toString() {
          return "V(x,y) = 1/4  (x^2 + y^2)^2";
     }

};


#endif

