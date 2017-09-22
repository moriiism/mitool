#ifndef MORIIISM_MITOOL_MITIMINGLIB_EPH_CALC_H_
#define MORIIISM_MITOOL_MITIMINGLIB_EPH_CALC_H_

#include "mi_iolib.h"

namespace EphemerisCalc{
    double GetPeriod(double nu);
    double GetPeriodDot(double nu,
                        double nu_dot);
    double GetPeriodDot2(double nu,
                         double nu_dot,
                         double nu_dot2);
    double GetPeriodDot3(double nu,
                         double nu_dot,
                         double nu_dot2,
                         double nu_dot3);
    double GetPeriodErr(double nu, double nu_err);
    double GetPeriodDotErr(double nu, double nu_err,
                           double nu_dot, double nu_dot_err);
    double GetPeriodDot2Err(double nu, double nu_err,
                            double nu_dot, double nu_dot_err,
                            double nu_dot2, double nu_dot2_err);
    double GetPeriodDot3Err(double nu, double nu_err,
                            double nu_dot, double nu_dot_err,
                            double nu_dot2, double nu_dot2_err,
                            double nu_dot3, double nu_dot3_err);

    // the followings are the same functions as those above.
    double GetNu(double period);
    double GetNuDot(double period,
                    double period_dot);
    double GetNuDot2(double period,
                     double period_dot,
                     double period_dot2);
    double GetNuDot3(double period,
                     double period_dot,
                     double period_dot2,
                     double period_dot3);
    double GetNuErr(double period, double period_err);
    double GetNuDotErr(double period, double period_err,
                       double period_dot, double period_dot_err);
    double GetNuDot2Err(double period, double period_err,
                        double period_dot, double period_dot_err,
                        double period_dot2, double period_dot2_err);
    double GetNuDot3Err(double period, double period_err,
                        double period_dot, double period_dot_err,
                        double period_dot2, double period_dot2_err,
                        double period_dot3, double period_dot3_err);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_EPH_CALC_H_
