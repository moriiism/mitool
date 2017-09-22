#include "mit_lomb.h"

//
// data_arr must be in the unit of sec.
//
double MitLomb::GetTau(const DataArray1d* const data_arr,
                              double nu)
{
    double omega = 2 * M_PI * nu;
    double sum_sin = 0.0;
    double sum_cos = 0.0;
    for(int idata = 0; idata < data_arr->GetNdata(); idata++){
        double time = data_arr->GetValElm(idata);
        sum_sin += sin(2 * omega * time);
        sum_sin += cos(2 * omega * time);
    }
    double tau = atan(sum_sin/sum_cos)/(2 * omega);
    return tau;
}


double MitLomb::GetLomb(const GraphData2d* const gd2d,
                               double nu, double tau)
{
    double amean = MirMath::GetAMean(gd2d->GetNdata(),
                                     gd2d->GetOvalArr()->GetVal());
    double un_biased_variance =
        MirMath::GetUnbiasedVariance(gd2d->GetNdata(),
                                     gd2d->GetOvalArr()->GetVal());
    double omega = 2 * M_PI * nu;
    double sum_oval_cos = 0.0;
    double sum_oval_sin = 0.0;
    double sum_cos2 = 0.0;
    double sum_sin2 = 0.0;    
    for(int idata = 0; idata < gd2d->GetNdata(); idata++){
        sum_oval_cos += (gd2d->GetOvalElm(idata) - amean) *
            cos(omega * (gd2d->GetXvalElm(idata) - tau));
        sum_oval_sin += (gd2d->GetOvalElm(idata) - amean) *
            sin(omega * (gd2d->GetXvalElm(idata) - tau));
        sum_cos2 += pow(cos(omega * (gd2d->GetXvalElm(idata) - tau)), 2);
        sum_sin2 += pow(sin(omega * (gd2d->GetXvalElm(idata) - tau)), 2);
    }
    double sum_oval_cos2 = pow(sum_oval_cos, 2);
    double sum_oval_sin2 = pow(sum_oval_sin, 2);

    double lomb = (sum_oval_cos2/ sum_cos2 + sum_oval_sin2/ sum_sin2) /
        (2. * un_biased_variance);
    return lomb;
}

double MitLomb::GetLomb(const DataArray1d* const da1d,
                               double nu, double tau)
{
    double omega = 2 * M_PI * nu;
    double sum_oval_cos = 0.0;
    double sum_oval_sin = 0.0;
    double sum_cos2 = 0.0;
    double sum_sin2 = 0.0;    
    for(int idata = 0; idata < da1d->GetNdata(); idata++){
        sum_oval_cos += cos(omega * (da1d->GetValElm(idata) - tau));
        sum_oval_sin += sin(omega * (da1d->GetValElm(idata) - tau));
        sum_cos2 += pow(cos(omega * (da1d->GetValElm(idata) - tau)), 2);
        sum_sin2 += pow(sin(omega * (da1d->GetValElm(idata) - tau)), 2);
    }
    double sum_oval_cos2 = pow(sum_oval_cos, 2);
    double sum_oval_sin2 = pow(sum_oval_sin, 2);

    double lomb = (sum_oval_cos2/ sum_cos2 + sum_oval_sin2/ sum_sin2)/2.;
    return lomb;
}

