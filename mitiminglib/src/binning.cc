#include "mit_folding.h"

// GraphDataSerr2d ---> HistDataSerr1d

HistDataSerr1d* const MitFolding::GenFoldingBinCenter(const GraphDataSerr2d* const g2d,
                                                       double mjdref, string tunit,
                                                       const Ephemeris* const eph,
                                                       int nphase)
{
    double* rate_num = new double [nphase];
    double* rate_den = new double [nphase];
    double* rate     = new double [nphase];
    double* rate_serr = new double [nphase];
    for(int iphase = 0; iphase < nphase; iphase ++){
        rate_num[iphase] = 0.0;
        rate_den[iphase] = 0.0;
        rate[iphase]     = 0.0;
        rate_serr[iphase] = 0.0;
    }
    
    int ntime_bad = 0;
    for (int idata = 0; idata < g2d->GetNdata(); idata++){
        double time = g2d->GetXvalElm(idata);
        double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
        double phase = eph->GetPhaseAtTimeMjd(time_mjd);

        double delta_phase = 1./nphase;
        int iphase = (int) floor( phase / delta_phase);

        if( fabs( g2d->GetOvalSerrElm(idata) ) > DBL_EPSILON ){
            rate_num[iphase] += g2d->GetOvalElm(idata) / pow(g2d->GetOvalSerrElm(idata), 2);
            rate_den[iphase] += 1./pow(g2d->GetOvalSerrElm(idata), 2);
        } else {
            ntime_bad ++;
        }
    }
    printf("ntime_bad = %d\n", ntime_bad);

    for(int iphase = 0; iphase < nphase; iphase++){
        if(fabs(rate_den[iphase]) > DBL_EPSILON) {
            rate[iphase] = rate_num[iphase] / rate_den[iphase];
            rate_serr[iphase] = sqrt(1./rate_den[iphase]);
        } else {
            rate[iphase] = 0.0;
            rate_serr[iphase] = 0.0;
        }
    }

    HistDataSerr1d* h1d_pulse = new HistDataSerr1d;
    h1d_pulse->Init(nphase, 0.0, 1.0);
    h1d_pulse->Set(nphase, 0.0, 1.0,
                   rate, rate_serr);
    delete [] rate_num;
    delete [] rate_den;
    delete [] rate;
    delete [] rate_serr;

    return h1d_pulse;
}


// HistDataSerr1d ---> HistDataSerr1d

HistDataSerr1d* const MitFolding::GenFoldingBinCenter(const HistDataSerr1d* const h1d,
                                                       double mjdref, string tunit,
                                                       const Ephemeris* const eph,
                                                       int nphase)
{
    double* rate_num = new double [nphase];
    double* rate_den = new double [nphase];
    double* rate     = new double [nphase];
    double* rate_serr = new double [nphase];
    for(int iphase = 0; iphase < nphase; iphase ++){
        rate_num[iphase] = 0.0;
        rate_den[iphase] = 0.0;
        rate[iphase]     = 0.0;
        rate_serr[iphase] = 0.0;
    }
    
    int ntime_bad = 0;
    for (int ibin = 0; ibin < h1d->GetNbinX(); ibin++){
        double time = h1d->GetBinCenterX(ibin);
        double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
        double phase = eph->GetPhaseAtTimeMjd(time_mjd);

        double delta_phase = 1./nphase;
        int iphase = (int) floor( phase / delta_phase);

        if( fabs( h1d->GetOvalSerrElm(ibin) ) > DBL_EPSILON ){
            rate_num[iphase] += h1d->GetOvalElm(ibin) / pow(h1d->GetOvalSerrElm(ibin), 2);
            rate_den[iphase] += 1./pow(h1d->GetOvalSerrElm(ibin), 2);
        } else {
            ntime_bad ++;
        }
    }
    printf("ntime_bad = %d\n", ntime_bad);

    for(int iphase = 0; iphase < nphase; iphase++){
        if(fabs(rate_den[iphase]) > DBL_EPSILON) {
            rate[iphase] = rate_num[iphase] / rate_den[iphase];
            rate_serr[iphase] = sqrt(1./rate_den[iphase]);
            //qflag[iphase] = 1;
        } else {
            rate[iphase] = 0.0;
            rate_serr[iphase] = 0.0;
            //qflag[iphase] = -1;
        }
    }

    HistDataSerr1d* h1d_pulse = new HistDataSerr1d;
    h1d_pulse->Init(nphase, 0.0, 1.0);
    h1d_pulse->Set(nphase, 0.0, 1.0,
                   rate, rate_serr);
    delete [] rate_num;
    delete [] rate_den;
    delete [] rate;
    delete [] rate_serr;

    return h1d_pulse;
}



// DataArray1d ---> HistDataSerr1d

HistDataSerr1d* const MitFolding::GenFolding(const DataArray1d* const data_arr,
                                              double mjdref, string tunit,
                                              const Ephemeris* const eph,
                                              int nphase)
{
    double* rate     = new double [nphase];
    double* rate_serr = new double [nphase];
    for(int iphase = 0; iphase < nphase; iphase ++){
        rate[iphase]     = 0.0;
        rate_serr[iphase] = 0.0;
    }
    
    double delta_phase = 1./nphase;
    for (int idata = 0; idata < data_arr->GetNdata(); idata++){
        double time = data_arr->GetValElm(idata);
        double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
        double phase = eph->GetPhaseAtTimeMjd(time_mjd);
        int iphase = (int) floor( phase / delta_phase);
        rate[iphase] ++;
    }

    for(int iphase = 0; iphase < nphase; iphase++){
        rate_serr[iphase] = sqrt( rate[iphase] );
    }
    
    HistDataSerr1d* h1d_pulse = new HistDataSerr1d;
    h1d_pulse->Init(nphase, 0.0, 1.0);
    h1d_pulse->Set(nphase, 0.0, 1.0,
                   rate, rate_serr);
    delete [] rate;
    delete [] rate_serr;

    return h1d_pulse;
}
