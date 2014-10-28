#include "EDF.hh" 



EDF::EDF ( Settings* s ) : values ( nullptr ), alreadySaved(false)
{
     this->init();

     //this->time = this->settings->get ( "maxT" );

}


EDF::~EDF()
{
  if(!alreadySaved) this->close();
  
  if(this->values!=nullptr) delete this->values;
}

void EDF:: init()
{

     this->values = new vector<double>();

}



void EDF::fill ( double x )
{
  
  if(!isNan(x)) this->values->push_back(x);
  else {
   cout << "NaN passed to EDF::fill() !"<<endl; 
  }
}

void EDF::close()
{
 cout << "EDF::close()" <<endl;
 
 //this->save();
 
 //cout << "EDF::all saved"<<endl;
}



void EDF::calculate() {
  cout << "recalculating EDF"<<endl;
  
  sort( this->values->begin(), this->values->end() );
  size_t size = this->values->size();
  cout << " vector size: "<< size <<endl;
  
};



//tool

bool EDF::isNan (volatile double &x)
{
  return (!(x==x)); // detect NaN
}

bool EDF::isOk ( volatile double &x)
{
  //limit do zakresu |x| < 100
   return ( ( abs(x) < 100.0 ) && ! isNan(x)) ;
}



void EDF::save() {
    this->calculate();
 
 
  
}



