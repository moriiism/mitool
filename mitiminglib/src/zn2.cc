#include "mit_zn2.h"

double MitZn2::GetZn2(const DataArray1d* const data_arr, double mjdref, string tunit,
                             const Ephemeris* const eph,
                             int nharmonics)
{
    // R. Buccheri et al. 1983, A&A, 128, 245
    // nharmonics : number of harmonics

    int ntime = data_arr->GetNdata();
    if(ntime <= 0){
        printf("error\n");
        abort();
    }
    double zn2 = 0.0;
    for(int iharmonics = 0; iharmonics < nharmonics; iharmonics ++){
        double xvector = 0.0;
        double yvector = 0.0;
        for(int itime = 0; itime < ntime; itime ++){
            double time = data_arr->GetValElm(itime);
            double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
            double phase = eph->GetPhaseAtTimeMjd(time_mjd);
            xvector += cos(2 * M_PI * (iharmonics + 1) * phase);
            yvector += sin(2 * M_PI * (iharmonics + 1) * phase);
        }
        zn2 += pow(xvector, 2) + pow(yvector, 2);
    }
    zn2 *= 2./ntime;
    return zn2;
}



double MitZn2::GetZn2(const GraphData2d* const g2d, double mjdref, string tunit,
                             const Ephemeris* const eph,
                             int nharmonics)
{
    // R. Buccheri et al. 1983, A&A, 128, 245
    // nharmonics : number of harmonics

    int ntime = g2d->GetNdata();
    double zn2 = 0.0;
    for(int iharmonics = 0; iharmonics < nharmonics; iharmonics ++){
        double xvector = 0.0;
        double yvector = 0.0;
        for(int itime = 0; itime < ntime; itime ++){
            double time = g2d->GetXvalElm(itime);
            double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
            double phase = eph->GetPhaseAtTimeMjd(time_mjd);
            double weight = g2d->GetOvalElm(itime);
            xvector += cos(2 * M_PI * (iharmonics + 1) * phase) * weight;
            yvector += sin(2 * M_PI * (iharmonics + 1) * phase) * weight;
        }
        zn2 += pow(xvector, 2) + pow(yvector, 2);
    }
    zn2 *= 2./ntime;
    return zn2;
}

