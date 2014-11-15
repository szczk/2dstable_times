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

     
     virtual bool inLimit( const vec X ) {
      // x^2+y^2>  pow(10.,3./(c-2.+0.01))) 
      //  10^(3/( 2.01 )) =~ 31.62
      return   ( ( X.x*X.x + X.y*X.y) < 31.62  );
     }
     
     virtual vec getExact(const vec X, double dt) {
         double sqt = 1.0/(sqrt( ( 1.0 + 4.0* dt * ( (X.x*X.x) + (X.y*X.y) ) )/ ( (X.x*X.x) )   ));
         
         
         double newX = sqt;
         double newY = (X.y/X.x)*sqt;
         
         vec NX;
         // odpowiednia cwiartka
         
         
         if( X.x < 0.0 ) {
             if( newX<0.0) NX.x = newX;
             else NX.x = - newX;             
         } else {
             if( newX<0.0) NX.x = -newX;
             else NX.x =  newX;   
         }
         
         
         if( X.y < 0.0 ) {
             if( newY<0.0) NX.y = newY;
             else NX.y = - newY;             
         } else {
             if( newY<0.0) NX.y = -newY;
             else NX.y =  newY;   
         }
         
         
         
         return NX;
     }

     
};


#endif

