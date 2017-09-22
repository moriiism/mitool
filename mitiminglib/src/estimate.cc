#include "mit_estimate.h"

double MitEstimate::GetDeltaNu(double time_span)
{
    double delta_nu = 1./time_span;
    return delta_nu;
}

double MitEstimate::GetDeltaNudot(double time_span)
{
    double delta_nudot = 2./pow(time_span, 2);
    return delta_nudot;
}

double MitEstimate::GetDeltaNudot2(double time_span)
{
    double delta_nudot2 = 6./pow(time_span, 3);
    return delta_nudot2;
}

double MitEstimate::GetDeltaNudotNuRatio(double time_span, double nu)
{
    double delta_nudot_nu_ratio
        = 2./ nu / pow(time_span, 2);
    return delta_nudot_nu_ratio;
}

double MitEstimate::GetNyquistFreq(double delta_time)
{
    double nyquist_freq
        = 1./ (2. * delta_time);
    return nyquist_freq;
}
