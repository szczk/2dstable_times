#include "HistogramsProducer.hh"



HistogramsProducer::HistogramsProducer ( Settings * s ) : alreadySaved ( false ), histogram ( nullptr ), osX_histo ( nullptr ), osY_histo ( nullptr )
{
     this->settings = s;
     this->init();
     

     this->time = this->settings->get ( "maxT" );

}



HistogramsProducer::~HistogramsProducer()
{
     if ( ! this->alreadySaved ) this->close();
     if ( histogram!=nullptr ) ( this->histogram );
     if ( osX_histo!=nullptr ) gsl_histogram_free ( this->osX_histo );
     if ( osY_histo!=nullptr ) gsl_histogram_free ( this->osY_histo );
}


void HistogramsProducer::init()
{
     this->initHistograms();
}


void HistogramsProducer::close()
{
  cout << "HistogramsProducer:: saving histograms " <<endl;
     if ( ! this->alreadySaved ) this->save();
  cout << "HistogramsProducer:: all saved"<<endl;
}

void HistogramsProducer::initHistograms()
{
     this->range = 5;
     this->xbins = 200;
     this->ybins = 200;


     this->xmin =-range;
     this->xmax = range;

     this->ymin =-range;
     this->ymax = range;

     this->dx = ( xmax-xmin ) /xbins;
     this->dy = ( ymax-ymin ) /ybins;

     this->histogram = gsl_histogram2d_alloc ( xbins, ybins );

     gsl_histogram2d_set_ranges_uniform ( this->histogram, xmin, xmax, ymin, ymax );

     this->osX_histo = gsl_histogram_alloc ( xbins );
     this->osY_histo = gsl_histogram_alloc ( ybins );

     gsl_histogram_set_ranges_uniform ( this->osX_histo, xmin, xmax );
     gsl_histogram_set_ranges_uniform ( this->osY_histo, ymin, ymax );
}


void HistogramsProducer::fill ( double x, double y )
{

     gsl_histogram2d_increment ( this->histogram, x, y );

     if ( abs ( x ) < dx ) {
          gsl_histogram_increment ( this->osY_histo, y );
     }
     if ( abs ( y ) < dy ) {
          gsl_histogram_increment ( this->osX_histo, x );
     }


}




void HistogramsProducer::save()
{
     if ( alreadySaved ) return;
     


     double alpha = this->settings->getJumpsParameter();
     int potentialType = this->settings->get ( "POTENTIAL_TYPE" );
     int noiseType = this->settings->get ( "NOISE_TYPE" );

     char buf[200];
     char fullSuffix[200];
     char histogram_file[200];



     
     sprintf ( fullSuffix, "%s_t_%2.3f", this->settings->getFullOutputFilesPrefix().c_str() , this->time );

     sprintf ( buf, "%s/%s_plot.plt", settings->getStoragePath(), fullSuffix );



     ofstream plotScript ( buf,ios_base::out );

     plotScript << "reset\n";
     plotScript << "set term png enhanced \n";

     sprintf ( buf, "%s_dist.png", fullSuffix );  //plot filename, without filesystem path (relative to gnuplot script)
     plotScript << "set output \""<<buf<<"\"\n";

     plotScript << "set title '{/Symbol a} = "<< alpha <<", t="<< this->time << "'\n";

     plotScript << "set xrange ["<< this->xmin <<":"<< this->xmax << "]\n";
     plotScript << "set yrange ["<< this->ymin <<":"<< this->ymax << "]\n";
     plotScript << "set zrange [0:1]\n";

     plotScript << "set xlabel 'x'\n";
     plotScript << "set ylabel 'y'\n";
     plotScript << "set zlabel 'p(x,y)' offset 1\n";

     plotScript << "set contour base\n";
     plotScript << "set hidden3d\n";
     plotScript << "set view 55, 49\n";

//     set pm3d map
// set isosample 400
// set palette defined (-1 "white", 0 "blue", 1 "red")




     //normalize
     double scale = 1.0/ ( dx*dy*gsl_histogram2d_sum ( this->histogram ) );
     gsl_histogram2d_scale ( this->histogram,  scale );


     sprintf ( histogram_file, "%s_stable_dist.txt", fullSuffix );  // filename without filesystem path (relative to gnuplot script)
     sprintf ( buf, "%s/%s", settings->getStoragePath(), histogram_file );
     FILE * pFile = fopen ( buf,"w" );
     gsl_histogram2d_fprintf ( pFile, this->histogram, "%g", "%g" );

     fclose ( pFile );


//
     plotScript<< "splot '"<< histogram_file <<"' using ($1+ ($2-$1)/2):($3 + ($4-$3)/2): ($5>0 ? $5 : 1/0 ) with lines title 't="<< this->time <<"'\n";
     plotScript.close();


     // axes histograms

     sprintf ( buf, "%s/%s_plot_axes.plt", settings->getStoragePath() ,fullSuffix );

     plotScript.open ( buf,ios_base::out );

     plotScript << "reset\n";
     plotScript << "set term png enhanced \n";
     sprintf ( buf, "%s_dist_xy.png", fullSuffix );
     plotScript << "set output \""<<buf<<"\"\n";

     plotScript << "set title '{/Symbol a} = "<< settings->getJumpsParameter() <<" t = "<< this->time <<"'\n";

//      plotScript << "set xrange [-5:5]\n";
//      plotScript << "set yrange [-5:5]\n";

     plotScript << "set xlabel 'x | y'\n";
     plotScript << "set ylabel 'P(x,y)'\n";


     double scaleOX = 1.0/ ( dx*gsl_histogram_sum ( this->osX_histo ) );
     gsl_histogram_scale ( this->osX_histo,  scaleOX );

     sprintf ( histogram_file, "%s_dist_oX.txt", fullSuffix ); //nazwa pliku bez sciezki
     sprintf ( buf, "%s/%s", settings->getStoragePath(), histogram_file );

     pFile = fopen ( buf,"w" );

     gsl_histogram_fprintf ( pFile,  this->osX_histo, "%g", "%g" );

     fclose ( pFile );




     plotScript<< "plot '"<<histogram_file <<"' using ($1+ ($2-$1)/2):3 with linespoints title 'osX, |y| < "<<dy<<"' lc rgbcolor 'red' lw 2,\\\n";





     double scaleOY = 1.0/ ( dy*gsl_histogram_sum ( this->osY_histo ) );
     gsl_histogram_scale ( this->osY_histo,  scaleOY );

     sprintf ( histogram_file, "%s_dist_oY.txt", fullSuffix ); //nazwa pliku bez sciezki
     sprintf ( buf, "%s/%s", settings->getStoragePath(), histogram_file );

     pFile = fopen ( buf,"w" );
     gsl_histogram_fprintf ( pFile, this->osY_histo, "%g", "%g" );

     fclose ( pFile );



     plotScript<< "'"<<histogram_file <<"' using ($1+ ($2-$1)/2):3 with linespoints title 'osY, |x| < "<<dx<<"'  lc rgbcolor 'blue' lw 1 \n";




     plotScript.close();



     

     alreadySaved = true;
}
