#ifndef MORIIISM_MITOOL_MILIB_RAND_H_
#define MORIIISM_MITOOL_MILIB_RAND_H_

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "mt64.h"

namespace MiRand
{
    void Init(long seed);
    double Uniform(void);
    double Normal(double mu, double sigma);
    
}  //  namespace MiRand

#endif // MORIIISM_MITOOL_MILIB_RAND_H_
