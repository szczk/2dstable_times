#include "Randoms.hh"



Randoms:: Randoms()
{
    cout << "creating Randoms " <<endl;
    //srand(time(0));
    this->init();
}

Randoms:: ~Randoms()
{
    cout << "destroying Randoms...";
    this->destroy();
    cout << "ok" <<endl;
}

void Randoms:: init()
{
    this->generator = gsl_rng_alloc ( gsl_rng_mt19937  );//gsl_rng_ranlux
    //this->reset();
// gsl_rng_set (generator, time(0) );

}

void Randoms::reset(long unsigned int newseed)
{
  cout << "Seeding random number generator with '" << newseed << "'"<<endl;
  gsl_rng_set (generator, newseed );
}


void Randoms:: reset()
{
    cout << "reset(),";
    srand(time(0));
    reset( rand() );
    
    //gsl_rng_set (generator, r );
}

void Randoms:: destroy()
{
    gsl_rng_free(this->generator);
}


// Randoms* Randoms::getInstance()
//   {
//   //Inicjalizacja statycznego obiektu.
//   //Obiekt zostanie utworzony przy pierwszym wywołaniu tej metody
//   //i tylko wtedy nastąpi inicjalizacja przy pomocy konstruktora.
//   //Każde następne wywołanie jedynie zwróci referencję tego obiektu.
//   static Randoms instance;
//   return &instance;
//   }


double Randoms:: getUniform(double a, double b)
{
    return gsl_ran_flat(this->generator, a, b);
}


double Randoms:: getGauss(double sigma)
{
    double xi = gsl_ran_gaussian(this->generator, sigma);
    return xi ;
}

// 0 < alpha <= 2
// -1 <= beta <= 1

// beta = 1 => "totaly skewed levy distr'
// alpha = 2 => gauss with sigma = sqrt(2) * sigma_parameter
double Randoms:: getLevyStable(double alpha,double beta, double sigma, double mu)
{
    double xi = mu + gsl_ran_levy_skew(this->generator, sigma, alpha, beta);

    return xi;
}


// get skew levy
// checked for infinite value
double Randoms:: getSkewLevy(double alpha)
{
    int maxTries = 10;
    double ret = 0.0;
    int cnt=1;
    do
    {
        ret = this->m_drawSkewLevy(alpha);
        cnt++;

        if (ret == numeric_limits<double>::infinity())
        {
            cerr << "Randoms:: WARNING: getSkewLevy() returned infinity, drawing again..."<<endl;
        }

    }
    while ( ret == numeric_limits<double>::infinity() && cnt < maxTries);

    if (cnt==maxTries)
    {
        cerr << "Randoms:: WARNING: getSkewLevy() returned infinity after " << cnt << " tries. returning 0 instead. "<<endl;
        ret = 0.0;
    }

    return ret;
}


double Randoms::  m_drawSkewLevy(double alpha)
{
    double v = this->getUniform(-M_PI_2,M_PI_2);
    double w = gsl_ran_exponential(this->generator, 1.0);

    double c_1 = pow( cos( M_PI_2 * alpha), -1.0/alpha );
    double c_2 = M_PI_2;

    double f1 = sin( alpha*(v + c_2) )/pow(cos(v),1.0/alpha);
    double f2 = pow((cos( v - alpha*(v+c_2) )/w), (1-alpha)/alpha );

    double xi = c_1 * f1 * f2;
//   this->gslSkewLevyHist->Fill(xi);
    return xi;
}



double Randoms:: getLevy2(double mu)
{
// magdziarz/weron
    double v = this->getUniform(-M_PI_2,M_PI_2);
    double w = gsl_ran_exponential(this->generator, 1.0);

    double f1 = sin(mu * v)/pow( cos(v), 1.0/mu);
    double f2 = pow( (cos(v - mu*v)/w), (1.0-mu)/mu );

    double xi = f1 * f2;
    return xi;
}

double Randoms:: getMittagLeffler(double beta)
{
    double u = this->getUniform(0,1.0);
    double v = this->getUniform(0,1.0);
    double m1 = sin(beta * M_PI)/tan(beta*M_PI*v);
    double m2 = cos(beta * M_PI);

    double m = pow( (m1 - m2), (1.0/beta) );
    double tau = - log(u) * m;

//   cout << tau<<endl;
//   this->gslSkewLevyHist->Fill(tau);

    return tau;
}
