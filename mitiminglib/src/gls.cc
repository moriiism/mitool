#include "mit_gls.h"

//
// data_arr must be in the unit of sec.
//
double MitGls::GetTau(const GraphDataSerr2d* const gd2d,
                             double nu)
{
    double omega = 2 * M_PI * nu;

    double W = 0.0;
    for(int idata = 0; idata < gd2d->GetNdata(); idata++){
        W += 1./ pow(gd2d->GetOvalSerrElm(idata), 2);
    }
    double sum_sin  = 0.0;
    double sum_cos  = 0.0;
    double sum_sin2 = 0.0;
    double sum_cos2 = 0.0;
    for(int idata = 0; idata < gd2d->GetNdata(); idata++){
        double time = gd2d->GetXvalElm(idata);
        double weight = 1./ pow(gd2d->GetOvalSerrElm(idata), 2) / W;
        sum_sin  += weight * sin(omega * time);
        sum_cos  += weight * cos(omega * time);        
        sum_sin2 += weight * sin(2 * omega * time);
        sum_cos2 += weight * cos(2 * omega * time);
    }
    double tau = atan(
        sum_sin2 - 2 * sum_sin * sum_cos /
        (sum_cos2 - ( pow(sum_cos, 2) + pow(sum_sin, 2) ) ) )
        / (2 * omega);
    return tau;
}


double MitGls::GetGls(const GraphDataSerr2d* const gd2d,
                             double nu, double tau)
{
    double omega = 2 * M_PI * nu;
    double W = 0.0;
    for(int idata = 0; idata < gd2d->GetNdata(); idata++){
        W += 1./ pow(gd2d->GetOvalSerrElm(idata), 2);
    }
    double Y = 0.0;
    double C = 0.0;
    double S = 0.0;
    double hat_YY = 0.0;
    double hat_YC = 0.0;
    double hat_YS = 0.0;
    double hat_CC = 0.0;
    double hat_SS = 0.0;
    for(int idata = 0; idata < gd2d->GetNdata(); idata++){
        double weight = 1./ pow(gd2d->GetOvalSerrElm(idata), 2) / W;
        double time = gd2d->GetXvalElm(idata);
        double yval = gd2d->GetOvalElm(idata);
        Y += weight * yval;
        C += weight * cos(omega * (time - tau));
        S += weight * sin(omega * (time - tau));
        hat_YY += weight * yval * yval;
        hat_YC += weight * yval * cos(omega * (time - tau));
        hat_YS += weight * yval * sin(omega * (time - tau));
        hat_CC += weight * pow(cos(omega * (time - tau)), 2);
        hat_SS += weight * pow(sin(omega * (time - tau)), 2);
    }
    double YY = hat_YY - Y * Y;
    double YC = hat_YC - Y * C;
    double YS = hat_YS - Y * S;
    double CC = hat_CC - C * C;
    double SS = hat_SS - S * S;
    double gls = (pow(YC, 2)/ CC + pow(YS, 2) / SS) / YY;
    return gls;
}

