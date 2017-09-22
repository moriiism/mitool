#include "sub.h"

//
// for DataArray1d
//

void GenZn2Nu(const DataArray1d* const data_arr, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nharmonics,
              HistData1d** h1d_zn2_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    printf("Zn2Nu(): delta_nu    = %e\n", delta_nu);
  
    Ephemeris* eph = new Ephemeris;
    HistData1d* h1d_zn2 = new HistData1d;
    h1d_zn2->Init(nbin_nu, nu_lo, nu_up);

    double time_mjd_st = TimeConv::TimeToMjd(data_arr->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(data_arr->GetValMax(), mjdref, tunit);

    for(int inu = 0; inu < nbin_nu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        eph->Set(nu, 0.0, nu_dot, 0.0,
                 0.0, 0.0, 0.0, 0.0,
                 0.0, 0.0,
                 epoch_mjd, time_mjd_st, time_mjd_ed);
        double sigval = MxkwTimingZn2::GetZn2(data_arr, mjdref, tunit,
                                              eph, nharmonics);
        //printf("%.10e  %.10e\n", nu, sigval);
        h1d_zn2->SetOvalElm(inu, sigval);
    }
    *h1d_zn2_ptr = h1d_zn2;
    delete eph;
}

void GenZn2NuNuDot(const DataArray1d* const data_arr, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nharmonics,
                   HistData2d**  h2d_zn2_ptr,
                   HistData1d*** h1d_zn2_arr_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    double delta_nudot = (nudot_up - nudot_lo) / nbin_nudot;
    if (nudot_up - nudot_lo < 0){
        printf("bad nudot_lo, nudot_up: %e %e\n", nudot_lo, nudot_up);
        abort();
    }
    printf("Zn2NuNuDot(): delta_nu    = %e\n", delta_nu);
    printf("Zn2NuNuDot(): delta_nudot = %e\n", delta_nudot);
  
    Ephemeris* eph = new Ephemeris;
    HistData2d* h2d_zn2 = new HistData2d;
    h2d_zn2->Init(nbin_nu, nu_lo, nu_up,
                  nbin_nudot, nudot_lo, nudot_up);
    HistData1d** h1d_zn2_arr = new HistData1d* [nbin_nudot];
    for(int ibin = 0; ibin < nbin_nudot; ibin ++){
        h1d_zn2_arr[ibin] = new HistData1d;
        h1d_zn2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
    }

    double time_mjd_st = TimeConv::TimeToMjd(data_arr->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(data_arr->GetValMax(), mjdref, tunit);

    printf("Zn2NuNuDot: inudot#: ");
    for(long inudot = 0; inudot < nbin_nudot; inudot ++){
        double nudot = nudot_lo + (inudot + 0.5) * delta_nudot;
        printf(" %ld", inudot);
        fflush(stdout);
        for(long inu = 0; inu < nbin_nu; inu ++){
            double nu = nu_lo + (inu + 0.5) * delta_nu;
            eph->Set(nu, 0.0, nudot, 0.0,
                     nu_dot2, 0.0, 0.0, 0.0,
                     0.0, 0.0,
                     epoch_mjd, time_mjd_st, time_mjd_ed);
            double sigval = MxkwTimingZn2::GetZn2(data_arr, mjdref, tunit,
                                                  eph, nharmonics);
            // printf("%.10e  %.10e  %.10e\n", nu, nudot, sigval);
            h1d_zn2_arr[inudot]->SetOvalElm(inu, sigval);
            h2d_zn2->SetOvalElm(inu, inudot, sigval);
        }
    }
    printf("\n");
    
    *h2d_zn2_ptr = h2d_zn2;
    *h1d_zn2_arr_ptr = h1d_zn2_arr;
    delete eph;
}


//
// for GraphData2d
//

void GenZn2Nu(const GraphData2d* const g2d, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nharmonics,
              HistData1d** h1d_zn2_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    printf("Zn2Nu(): delta_nu    = %e\n", delta_nu);
  
    Ephemeris* eph = new Ephemeris;
    HistData1d* h1d_zn2 = new HistData1d;
    h1d_zn2->Init(nbin_nu, nu_lo, nu_up);

    double time_mjd_st = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMax(), mjdref, tunit);

    for(int inu = 0; inu < nbin_nu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        eph->Set(nu, 0.0, nu_dot, 0.0,
                 0.0, 0.0, 0.0, 0.0,
                 0.0, 0.0,
                 epoch_mjd, time_mjd_st, time_mjd_ed);
        double sigval = MxkwTimingZn2::GetZn2(g2d, mjdref, tunit,
                                              eph, nharmonics);
        //printf("%.10e  %.10e\n", nu, sigval);
        h1d_zn2->SetOvalElm(inu, sigval);
    }
    *h1d_zn2_ptr = h1d_zn2;
    delete eph;
}

void GenZn2NuNuDot(const GraphData2d* const g2d, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nharmonics,
                   HistData2d**  h2d_zn2_ptr,
                   HistData1d*** h1d_zn2_arr_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    double delta_nudot = (nudot_up - nudot_lo) / nbin_nudot;
    if (nudot_up - nudot_lo < 0){
        printf("bad nudot_lo, nudot_up: %e %e\n", nudot_lo, nudot_up);
        abort();
    }
    printf("Zn2NuNuDot(): delta_nu    = %e\n", delta_nu);
    printf("Zn2NuNuDot(): delta_nudot = %e\n", delta_nudot);
  
    Ephemeris* eph = new Ephemeris;
    HistData2d* h2d_zn2 = new HistData2d;
    h2d_zn2->Init(nbin_nu, nu_lo, nu_up,
                  nbin_nudot, nudot_lo, nudot_up);
    HistData1d** h1d_zn2_arr = new HistData1d* [nbin_nudot];
    for(int ibin = 0; ibin < nbin_nudot; ibin ++){
        h1d_zn2_arr[ibin] = new HistData1d;
        h1d_zn2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
    }

    double time_mjd_st = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMax(), mjdref, tunit);

    printf("Zn2NuNuDot: inudot#: ");
    for(long inudot = 0; inudot < nbin_nudot; inudot ++){
        double nudot = nudot_lo + (inudot + 0.5) * delta_nudot;
        printf(" %ld", inudot);
        fflush(stdout);
        for(long inu = 0; inu < nbin_nu; inu ++){
            double nu = nu_lo + (inu + 0.5) * delta_nu;
            eph->Set(nu, 0.0, nudot, 0.0,
                     nu_dot2, 0.0, 0.0, 0.0,
                     0.0, 0.0,
                     epoch_mjd, time_mjd_st, time_mjd_ed);
            double sigval = MxkwTimingZn2::GetZn2(g2d, mjdref, tunit,
                                                  eph, nharmonics);
            // printf("%.10e  %.10e  %.10e\n", nu, nudot, sigval);
            h1d_zn2_arr[inudot]->SetOvalElm(inu, sigval);
            h2d_zn2->SetOvalElm(inu, inudot, sigval);
        }
    }
    printf("\n");

    *h2d_zn2_ptr = h2d_zn2;
    *h1d_zn2_arr_ptr = h1d_zn2_arr;
    delete eph;
}
