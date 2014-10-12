#include "Simulation.hh"


Simulation::Simulation ( Settings * s )  : rand ( nullptr ) , potential ( nullptr )
{
     this->settings = s;
     this->init();
}


Simulation::~Simulation()
{


     this->cleanUp();
}


void Simulation::init()
{
     cout << "initializing simulation"<<endl;
     this->rand = new Randoms();
     this->reset();
}



void Simulation::cleanUp()
{
     cout << "destroying simulation"<<endl;

     if ( rand!=nullptr ) delete rand;
     if ( potential!=nullptr ) delete potential;

}

void Simulation::reset()
{
     this->rand->reset();
     if ( potential!=nullptr ) delete potential;

     int potentialType = this->settings->get ( "POTENTIAL_TYPE" );
     if ( potentialType==2 ) {
          cout << "creating square potential"<<endl;
          this->potential = new SquarePotential( );
     } else {
          cout << "creating quadratic potential"<<endl;
          this->potential = new QuadraticPotential();
     }

     cout << this->potential->toString() <<endl;
}


void Simulation::run ( Datafile* datafile )
{
     vec X;
     X.x = this->settings->getX0();
     X.y = this->settings->getY0();

//      cout << "starting sim " <<endl;

     
     double alpha = this->settings->getJumpsParameter();
     double sigma = this->settings->getNoiseIntensity();

     
     double t = this->settings->getStartTime();
     double endTime = this->settings->get("maxT");
     double dt = this->settings->getDt();

     
     double dL = exp ( log ( dt ) /alpha ); //pow(dt, 1.0/alpha);

     
     int noiseType = settings->get ( "NOISE_TYPE" );


     do {
	  //save x and y as pair
	  datafile->write(X.x);
	  datafile->write(X.y); 
	  
	  
	  
          double * v ;
// cout << "t= " <<t << endl;

          switch ( noiseType ) {
          case 1:
               v = rand->getAlphaStableVector ( alpha, sigma );
               break;
          case 2:
          default:
               v = rand->getDicreteAlphaStableVector ( alpha, sigma );
               break;
          }


          // grad V(x,y)
          vec potential = ( * ( this->potential ) ) ( X );

	  // calkowanie numeryczne  

          X.x += -potential.x*dt  + v[0]*dL;
          X.y += -potential.y*dt  + v[1]*dL;


	  // dla odpowiednio duzych r 
	  // przechodzimy na obliczenie dokladne czesci deterministrycznej + dodanie czesci stochastycznej
	  //  x^2+y^2>  pow(10.,3./(c-2.+0.01)))
	  


          delete[] v;
          t+= dt;
	  
     } while ( t <= endTime );

}
