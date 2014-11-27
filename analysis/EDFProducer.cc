#include "EDFProducer.hh"



EDFProducer::EDFProducer ( Settings* s ) : xValues ( nullptr ), yValues ( nullptr ), alreadySaved(false)
{
     this->settings = s;
     this->init();

     this->time = this->settings->get ( "maxT" );

}


EDFProducer::~EDFProducer()
{
  if(!alreadySaved) this->close();
  
  if(this->xValues!=nullptr) delete this->xValues;
  if(this->yValues!=nullptr) delete this->yValues;
}

void EDFProducer:: init()
{

     this->xValues = new vector<double>();
     this->yValues = new vector<double>();

}



void EDFProducer::fill ( double x, double y )
{
  
  if(!isNan(x)) this->xValues->push_back(x);
  if(!isNan(y)) this->yValues->push_back(y);
}

void EDFProducer::close()
{
 cout << "EDFProducer::saving CDFs, t=" << time<<endl;
 
 this->save();
 
 cout << "EDFProducer::all saved"<<endl;
}


void EDFProducer::save()
{
  if(alreadySaved) {
    cout << "EDFProducer:: already saved"<<endl;
    return;
  }
  
  
 
  //sort vectors
  
  
  

  
  
  double alpha = this->settings->getJumpsParameter();
  int potentialType = this->settings->get ( "POTENTIAL_TYPE" );
  int noiseType = this->settings->get ( "NOISE_TYPE" );
  
  char buf[200];
  char dataFileName[200];
  char fullSuffix[200];
  
  
  cout << "saving x"<<endl;
  sort( this->xValues->begin(), this->xValues->end() );
  size_t xsize = this->xValues->size();
  cout << " xvector size: "<< xsize <<endl;
   
 
  
  sprintf ( fullSuffix, "%s_t_%2.3f",  this->settings->getFullOutputFilesPrefix().c_str(), this->time );
  //sprintf ( buf, "%s/%s_plot.gnu", settings->getStoragePath(), fullSuffix );

  // save X
  
  sprintf ( dataFileName, "%s_edf_x.txt", fullSuffix );  // filename without filesystem path (relative to gnuplot script)
  sprintf ( buf, "%s/%s", settings->getStoragePath(), dataFileName );
  
  ofstream dataFile ( buf,ios_base::out );
  
  dataFile << "x\tF(x)\t1-F(x)\n";
  
  double lastValue = 0.0;
  for(size_t i = 0; i < xsize; i++) {
    volatile double val = (*this->xValues)[i];
    double EDFval = ( ( double ) i ) / ( ( double ) xsize );
    
    //detect nan 
    if( !isOk(val) || !isOk(EDFval) ) {
//      cout << "val = " << val << "\tedf=" << EDFval<<endl;
      continue;
    }
    
    // limit the resolution to make datafiles smaller
    
    if( abs( lastValue - val) < 0.001 ) { 
//      cout << "resolution skip"<<endl;
     continue;
    }
    
    
    dataFile << val << "\t" << EDFval <<"\t" << ( 1.0 - EDFval )<<"\n";
    
    lastValue = val;
  }
  dataFile.close();
  
  
  // save Y
  cout << "saving y"<<endl;
  sort( this->yValues->begin(), this->yValues->end() );
  size_t ysize = this->yValues->size();
  cout << " yvector size: "<< ysize <<endl;
  
  
  sprintf ( dataFileName, "%s_edf_y.txt", fullSuffix );  // filename without filesystem path (relative to gnuplot script)
  sprintf ( buf, "%s/%s", settings->getStoragePath(), dataFileName );
  dataFile.open( buf,ios_base::out );
  
  dataFile << "y\tF(y)\t1-F(y)\n";
  
  lastValue = 0.0;
  for(size_t i = 0; i < ysize; i++) {
    volatile double val = (*this->yValues)[i];
    double EDFval = ( ( double ) i ) / ( ( double ) ysize );
    
    
    if( !isOk(val) || !isOk(EDFval) ) {
//      cout << "val = " << val << "\tedf=" << EDFval<<endl;
      continue;
    }
    // limit the resolution to make datafiles smaller
    if( abs( lastValue - val) < 0.001 ) { 
//      cout << "resolution skip"<<endl;
     continue;
    }
    
    dataFile << val << "\t" << EDFval <<"\t" << ( 1.0 - EDFval )<<"\n";
    lastValue = val;
  }
  dataFile.close();
  
  
  
  this->alreadySaved = true;
}


//tool

bool EDFProducer::isNan (volatile double &x)
{
  return (!(x==x)); // detect NaN
}

bool EDFProducer::isOk ( volatile double &x)
{
  //limit do zakresu |x| < 100
   return ( ( abs(x) < 100.0 ) && ! isNan(x)) ;
}


