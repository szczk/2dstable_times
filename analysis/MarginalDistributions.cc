#include "MarginalDistributions.hh"





MarginalDistributions::MarginalDistributions ( double t )
{
     this->t = t;
     this->marginalX = new EDF();
     this->marginalY = new EDF();
}


MarginalDistributions::~MarginalDistributions()
{
     if( marginalX!=nullptr) delete this->marginalX;
     if( marginalY!=nullptr) delete this->marginalY;
}


void MarginalDistributions::add ( double x, double y )
{

  this->marginalX->fill(x);
  this->marginalY->fill(y);
}
