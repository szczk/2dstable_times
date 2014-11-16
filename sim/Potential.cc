#include "Potential.hh"


Potential:: Potential ( )
{
//       cout << "creating potential"<<endl;

     this->init();
}



Potential:: ~Potential()
{

     this->destroy();
}



void Potential::init()
{

}


void Potential::destroy()
{
     //if (this->randoms!=NULL) delete this->randoms;
}





vec Potential::operator() ( const vec X )
{

// V(x,y) = 1/4  (x^2 + y^2)^2

     //grad V(x,y) = [ x(x^2 + y^2) ,  y(x^2 + y^2)

     vec VX;

     // czwartego stopnia
     double x_squared = X.x*X.x;
     double y_squared = X.y*X.y;

     VX.x = X.x* ( x_squared + y_squared );
     VX.y = X.y* ( x_squared + y_squared );

//

     // paraboliczny
//   VX.x = X.x;
//   VX.y = X.y;



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

const char* Potential::toString()
{
     return "base class!";
}
