#ifndef MORIIISM_MITOOL_MITIMINGLIB_ESTIMATE_H_
#define MORIIISM_MITOOL_MITIMINGLIB_ESTIMATE_H_

#include "mi_iolib.h"

namespace MitEstimate{

    double GetDeltaNu(double time_span);
    // delta_nu = 1./T
    // It equals Fourier resolution.
    // See Numerical Recipes, Section "Descrete Fourier Transform"
    
    double GetDeltaNudot(double time_span);
    double GetDeltaNudot2(double time_span);
    double GetDeltaNudotNuRatio(double time_span, double nu);
    double GetNyquistFreq(double delta_time);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_ESTIMATE_H_
