#include "mit_eph_calc.h"

double EphemerisCalc::GetPeriod(double nu)
{
    double period = 1./nu;
    return period;
}

double EphemerisCalc::GetPeriodDot(double nu,
                                   double nu_dot)
{
    double period_dot = -1. * nu_dot / (nu * nu);
    return period_dot;
}
    
double EphemerisCalc::GetPeriodDot2(double nu,
                                    double nu_dot,
                                    double nu_dot2)
{
    double period_dot2 = (2 * nu_dot * nu_dot - nu * nu_dot2) / pow(nu, 3);
    return period_dot2;
}

double EphemerisCalc::GetPeriodDot3(double nu,
                                    double nu_dot,
                                    double nu_dot2,
                                    double nu_dot3)
{
    double period_dot3 = ( -6 * pow(nu_dot, 3)
                           + 6 * nu * nu_dot * nu_dot2
                           - nu * nu * nu_dot3) / pow(nu, 4);
    return period_dot3;
}


double EphemerisCalc::GetPeriodErr(double nu, double nu_err)
{
    double period_err = nu_err / (nu * nu);
    return period_err;
}
    
double EphemerisCalc::GetPeriodDotErr(double nu, double nu_err,
                                      double nu_dot, double nu_dot_err)
{
    double period_dot_err = sqrt(pow(2 * nu_dot * nu_err, 2)
                                 + pow(nu * nu_dot_err, 2) ) / fabs(pow(nu, 3));
    return period_dot_err;
}

double EphemerisCalc::GetPeriodDot2Err(double nu, double nu_err,
                                       double nu_dot, double nu_dot_err,
                                       double nu_dot2, double nu_dot2_err)
{
    double period_dot2_err = sqrt( pow( (6 * nu_dot * nu_dot
                                         - 2 * nu * nu_dot2) * nu_err, 2)
                                   + pow( 4 * nu * nu_dot * nu_dot_err, 2)
                                   + pow( nu * nu * nu_dot2_err, 2) ) / pow(nu, 4);
    return period_dot2_err;
}

double EphemerisCalc::GetPeriodDot3Err(double nu, double nu_err,
                                       double nu_dot, double nu_dot_err,
                                       double nu_dot2, double nu_dot2_err,
                                       double nu_dot3, double nu_dot3_err)
{
    double perid_dot3_err = sqrt( pow( (2 * nu_dot3 * nu * nu
                                        - 18 * nu_dot2 * nu_dot * nu
                                        + 24 * pow(nu_dot, 3) ) * nu_err, 2)
                                  + pow( (6 * nu_dot2 * nu - 18 * nu_dot * nu_dot) * nu * nu_dot_err, 2)
                                  + pow(6 * nu_dot * nu * nu * nu_dot2_err, 2)
                                  + pow( pow(nu, 3) * nu_dot3_err, 2) ) / fabs(pow(nu, 5));
    return perid_dot3_err;
}

double EphemerisCalc::GetNu(double period)
{
    double nu = GetPeriod(period);
    return nu;
}
    
double EphemerisCalc::GetNuDot(double period,
                               double period_dot)
{
    double nu_dot = GetPeriodDot(period,
                                 period_dot);
    return nu_dot;
}

double EphemerisCalc::GetNuDot2(double period,
                                double period_dot,
                                double period_dot2)
{
    double nu_dot2 = GetPeriodDot2(period,
                                   period_dot,
                                   period_dot2);
    return nu_dot2;
}

double EphemerisCalc::GetNuDot3(double period,
                                double period_dot,
                                double period_dot2,
                                double period_dot3)
{
    double nu_dot3 = GetPeriodDot3(period,
                                   period_dot,
                                   period_dot2,
                                   period_dot3);
    return nu_dot3;
}


double EphemerisCalc::GetNuErr(double period, double period_err)
{
    double nu_err = GetPeriodErr(period, period_err);
    return nu_err;
}

double EphemerisCalc::GetNuDotErr(double period, double period_err,
                                  double period_dot, double period_dot_err)
{
    double nu_dot_err = GetPeriodDotErr(period, period_err,
                                        period_dot, period_dot_err);
    return nu_dot_err;
}

double EphemerisCalc::GetNuDot2Err(double period, double period_err,
                                   double period_dot, double period_dot_err,
                                   double period_dot2, double period_dot2_err)
{
    double nu_dot2_err = GetPeriodDot2Err(period, period_err,
                                          period_dot, period_dot_err,
                                          period_dot2, period_dot2_err);
    return nu_dot2_err;
}

double EphemerisCalc::GetNuDot3Err(double period, double period_err,
                                   double period_dot, double period_dot_err,
                                   double period_dot2, double period_dot2_err,
                                   double period_dot3, double period_dot3_err)
{
    double nu_dot3_err = GetPeriodDot3Err(period, period_err,
                                          period_dot, period_dot_err,
                                          period_dot2, period_dot2_err,
                                          period_dot3, period_dot3_err);
    return nu_dot3_err;
}
