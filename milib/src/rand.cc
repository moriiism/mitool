#include "mi_rand.h"

void MiRand::Init(long seed)
{
    if(0 == seed){
        srand((unsigned)time(NULL));
        init_genrand64(rand());
    } else {
        init_genrand64(seed);
    }
}

double MiRand::Uniform( void )
{
    double val = genrand64_real1();
    return val;
}

double MiRand::Normal(double mu, double sigma)
{
    double z=sqrt( -2.0*log(Uniform()) ) * sin( 2.0*M_PI*Uniform() );
    double val = mu + sigma*z;
    return val;
}

