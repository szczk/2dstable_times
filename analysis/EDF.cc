#include "EDF.hh"



EDF::EDF ( ) : values ( nullptr ), alreadySaved ( false )
{
     this->init();

     //this->time = this->settings->get ( "maxT" );

}


EDF::~EDF()
{
     if ( !alreadySaved ) this->close();

     if ( this->values!=nullptr ) delete this->values;
}

void EDF:: init()
{

     this->values = new vector<double>();

}



void EDF::fill ( double x )
{

     if ( !isNan ( x ) ) this->values->push_back ( x );
     else {
          cout << "NaN passed to EDF::fill() !"<<endl;
     }
}

void EDF::close()
{
     // cout << "EDF::close()" <<endl;

//this->save();

//cout << "EDF::all saved"<<endl;
}



void EDF::sort()
{
//      cout << "recalculating EDF"<<endl;

     ::sort ( this->values->begin(), this->values->end() );
//      size_t size = this->values->size();
     //cout << " vector size: "<< size <<endl;

};



//tool

bool EDF::isNan ( volatile double &x )
{
     return ( ! ( x==x ) ); // detect NaN
}

bool EDF::isOk ( volatile double &x )
{
     //limit do zakresu |x| < 100
     return ( ( abs ( x ) < 100.0 ) && ! isNan ( x ) ) ;
}



void EDF::save()
{
     this->sort();


     // ....
//      for ( size_t i = 0; i < xsize; i++ ) {
//           volatile double val = ( *this->xValues ) [i];
//           double EDFval = ( ( double ) i ) / ( ( double ) xsize );
// 
//           //detect nan
//           if ( !isOk ( val ) || !isOk ( EDFval ) ) {
// //      cout << "val = " << val << "\tedf=" << EDFval<<endl;
//                continue;
//           }
// 
//           // limit the resolution to make datafiles smaller
// 
//           if ( abs ( lastValue - val ) < 0.001 ) {
// //      cout << "resolution skip"<<endl;
//                continue;
//           }
// 
// 
//           dataFile << val << "\t" << EDFval <<"\t" << ( 1.0 - EDFval ) <<"\n";
// 
//           lastValue = val;
//      }

}


vector< double >* EDF::getValues()
{
  return this->values;
}

vector< double >* EDF::getValuesSorted()
{
  this->sort();
  return this->getValues();
}

