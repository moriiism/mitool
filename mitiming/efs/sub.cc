#include "sub.h"

//
// for DataArray1d
//

void GenEfsNu(const DataArray1d* const data_arr, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nbin,
              HistData1d** h1d_chi2_ptr,
              Ephemeris** eph_best_ptr,
              HistDataSerr1d** h1d_pls_best_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    printf("EfsNu(): delta_nu    = %e\n", delta_nu);

    Ephemeris* eph_best = new Ephemeris;
    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;
    Ephemeris* eph = new Ephemeris;
    HistData1d* h1d_chi2 = new HistDataNerr1d;
    h1d_chi2->Init(nbin_nu, nu_lo, nu_up);

    double time_mjd_st = TimeConv::TimeToMjd(data_arr->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(data_arr->GetValMax(), mjdref, tunit);

    double sigval_max = 0.0;
    for(int inu = 0; inu < nbin_nu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        eph->Set(nu, 0.0, nu_dot, 0.0,
                 0.0, 0.0, 0.0, 0.0,
                 0.0, 0.0,
                 epoch_mjd, time_mjd_st, time_mjd_ed);
        HistDataSerr1d* h1d_pls = MitFolding::GenFolding(data_arr,
                                                          mjdref, tunit,
                                                          eph, nbin);
        double sigval = PulseProfStat::GetChi2(h1d_pls);
        //printf("%.10e  %.10e\n", nu, sigval);
        h1d_chi2->SetOvalElm(inu, sigval);

        if(sigval > sigval_max){
            eph_best->Copy(eph);
            h1d_pls_best->Copy(h1d_pls);
            sigval_max = sigval;
        }
        delete h1d_pls;
    }
    *h1d_chi2_ptr = h1d_chi2;
    *eph_best_ptr = eph_best;
    *h1d_pls_best_ptr = h1d_pls_best;
    delete eph;
}

void GenEfsNuNuDot(const DataArray1d* const data_arr, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nbin,
                   HistData2d**  h2d_chi2_ptr,
                   HistData1d*** h1d_chi2_arr_ptr,
                   Ephemeris** eph_best_ptr,
                   HistDataSerr1d** h1d_pls_best_ptr)
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
    printf("EfsNuNuDot(): delta_nu    = %e\n", delta_nu);
    printf("EfsNuNuDot(): delta_nudot = %e\n", delta_nudot);

    Ephemeris* eph_best = new Ephemeris;
    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;    
    Ephemeris* eph = new Ephemeris;
    HistData2d* h2d_chi2 = new HistDataNerr2d;
    h2d_chi2->Init(nbin_nu, nu_lo, nu_up,
                   nbin_nudot, nudot_lo, nudot_up);
    HistData1d** h1d_chi2_arr = new HistData1d* [nbin_nudot];
    for(int ibin = 0; ibin < nbin_nudot; ibin ++){
        h1d_chi2_arr[ibin] = new HistDataNerr1d;
        h1d_chi2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
    }

    double time_mjd_st = TimeConv::TimeToMjd(data_arr->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(data_arr->GetValMax(), mjdref, tunit);

    double sigval_max = 0.0;
    printf("EfsNuNuDot: inudot#: ");
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

            HistDataSerr1d* h1d_pls = MitFolding::GenFolding(data_arr,
                                                              mjdref, tunit,
                                                              eph, nbin);
            double sigval = PulseProfStat::GetChi2(h1d_pls);
            // printf("%.10e  %.10e  %.10e\n", nu, nudot, sigval);
            h1d_chi2_arr[inudot]->SetOvalElm(inu, sigval);
            h2d_chi2->SetOvalElm(inu, inudot, sigval);

            if(sigval > sigval_max){
                eph_best->Copy(eph);
                h1d_pls_best->Copy(h1d_pls);
                sigval_max = sigval;
            }
            delete h1d_pls;
        }
    }
    printf("\n");
    
    *h2d_chi2_ptr = h2d_chi2;
    *h1d_chi2_arr_ptr = h1d_chi2_arr;
    *eph_best_ptr = eph_best;
    *h1d_pls_best_ptr = h1d_pls_best;
    delete eph;
}


//
// for GraphDataSerr2d
//

void GenEfsNu(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nbin,
              HistData1d** h1d_chi2_ptr,
              Ephemeris** eph_best_ptr,
              HistDataSerr1d** h1d_pls_best_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    printf("EfsNu(): delta_nu    = %e\n", delta_nu);
  
    Ephemeris* eph_best = new Ephemeris;
    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;
    Ephemeris* eph = new Ephemeris;
    HistData1d* h1d_chi2 = new HistDataNerr1d;
    h1d_chi2->Init(nbin_nu, nu_lo, nu_up);

    double time_mjd_st = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMax(), mjdref, tunit);

    double sigval_max = 0.0;
    for(int inu = 0; inu < nbin_nu; inu ++){
        double nu = nu_lo + (inu + 0.5) * delta_nu;
        eph->Set(nu, 0.0, nu_dot, 0.0,
                 0.0, 0.0, 0.0, 0.0,
                 0.0, 0.0,
                 epoch_mjd, time_mjd_st, time_mjd_ed);

        HistDataSerr1d* h1d_pls = MitFolding::GenFoldingBinCenter(g2d,
                                                                   mjdref, tunit,
                                                                   eph, nbin);
        double sigval = PulseProfStat::GetChi2(h1d_pls);
        h1d_chi2->SetOvalElm(inu, sigval);
        if(sigval > sigval_max){
            eph_best->Copy(eph);
            h1d_pls_best->Copy(h1d_pls);
            sigval_max = sigval;
        }
        delete h1d_pls;
    }
    *h1d_chi2_ptr = h1d_chi2;
    *eph_best_ptr = eph_best;
    *h1d_pls_best_ptr = h1d_pls_best;
    delete eph;
}


void GenEfsNuNuDot(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nbin,
                   HistData2d**  h2d_chi2_ptr,
                   HistData1d*** h1d_chi2_arr_ptr,
                   Ephemeris** eph_best_ptr,
                   HistDataSerr1d** h1d_pls_best_ptr)
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
    printf("EfsNuNuDot(): delta_nu    = %e\n", delta_nu);
    printf("EfsNuNuDot(): delta_nudot = %e\n", delta_nudot);
  
    Ephemeris* eph_best = new Ephemeris;
    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;
    Ephemeris* eph = new Ephemeris;
    HistData2d* h2d_chi2 = new HistDataNerr2d;
    h2d_chi2->Init(nbin_nu, nu_lo, nu_up,
                  nbin_nudot, nudot_lo, nudot_up);
    HistData1d** h1d_chi2_arr = new HistData1d* [nbin_nudot];
    for(int ibin = 0; ibin < nbin_nudot; ibin ++){
        h1d_chi2_arr[ibin] = new HistDataNerr1d;
        h1d_chi2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
    }

    double time_mjd_st = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMax(), mjdref, tunit);

    double sigval_max = 0.0;
    printf("EfsNuNuDot: inudot#: ");
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
            HistDataSerr1d* h1d_pls = MitFolding::GenFoldingBinCenter(g2d,
                                                                       mjdref, tunit,
                                                                       eph, nbin);
            double sigval = PulseProfStat::GetChi2(h1d_pls);
            // printf("%.10e  %.10e  %.10e\n", nu, nudot, sigval);
            h1d_chi2_arr[inudot]->SetOvalElm(inu, sigval);
            h2d_chi2->SetOvalElm(inu, inudot, sigval);

            if(sigval > sigval_max){
                eph_best->Copy(eph);
                h1d_pls_best->Copy(h1d_pls);
                sigval_max = sigval;
            }
            delete h1d_pls;
        }
    }
    printf("\n");

    *h2d_chi2_ptr = h2d_chi2;
    *h1d_chi2_arr_ptr = h1d_chi2_arr;
    *eph_best_ptr = eph_best;
    *h1d_pls_best_ptr = h1d_pls_best;
    delete eph;
}


//
// orbmod
//



void GenEfsNuOrbAmp(const DataArray1d* const data_arr, double mjdref, string tunit,
                    int nbin_nu, double nu_lo, double nu_up,
                    int nbin_orbamp, double orbamp_lo, double orbamp_up,
                    double epoch_mjd, int nbin,
                    HistData2d**  h2d_chi2_ptr,
                    HistData1d*** h1d_chi2_arr_ptr,
                    Ephemeris** eph_best_ptr,
                    HistDataSerr1d** h1d_pls_best_ptr)
{
    double delta_nu = (nu_up - nu_lo) / nbin_nu;
    if (nu_up - nu_lo < 0){
        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
        abort();
    }
    double delta_orbamp = (orbamp_up - orbamp_lo) / nbin_orbamp;
    if (orbamp_up - orbamp_lo < 0){
        printf("bad orbamp_lo, orbamp_up: %e %e\n", orbamp_lo, orbamp_up);
        abort();
    }
    printf("EfsNuOrbAmp(): delta_nu    = %e\n", delta_nu);
    printf("EfsNuOrbAMp(): delta_orbamp = %e\n", delta_orbamp);

    Ephemeris* eph_best = new Ephemeris;
    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;    
    Ephemeris* eph = new Ephemeris;
    HistData2d* h2d_chi2 = new HistDataNerr2d;
    h2d_chi2->Init(nbin_nu, nu_lo, nu_up,
                   nbin_orbamp, orbamp_lo, orbamp_up);
    HistData1d** h1d_chi2_arr = new HistData1d* [nbin_orbamp];
    for(int ibin = 0; ibin < nbin_orbamp; ibin ++){
        h1d_chi2_arr[ibin] = new HistDataNerr1d;
        h1d_chi2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
    }

    double time_mjd_st = TimeConv::TimeToMjd(data_arr->GetValMin(), mjdref, tunit);
    double time_mjd_ed = TimeConv::TimeToMjd(data_arr->GetValMax(), mjdref, tunit);


    FILE* fp = fopen("temp.qdp", "w");
    fprintf(fp, "skip sing\n");
    fprintf(fp, "\n");
    
    //double sigval_max = 0.0;
    printf("EfsNuOrbAmp: iorbamp#: ");
    for(long iorbamp = 0; iorbamp < nbin_orbamp; iorbamp ++){
        double orbamp = orbamp_lo + (iorbamp + 0.5) * delta_orbamp;
        printf(" %ld", iorbamp);
        fflush(stdout);

        // time shift
        double orb_period = 1./8.21826e-06 / kDayToSec; // day
        double time_eclipse_mjd = 55000.0 + 0.55 * orb_period;
        double time_peri = time_eclipse_mjd + orb_period/4.;
        BinaryOrb1* binorb = new BinaryOrb1;
        double ax_sini = orbamp;
        double ecc = 0.0;
        double angle_peri = 0.0;
        binorb->Set(orb_period, ax_sini,
                    ecc, time_peri,
                    angle_peri);

        DataArray1d* data_arr_shift = new DataArrayNerr1d;
        vector<double> time_obj_vec;
        for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
            double time = data_arr->GetValElm(idata);
            double time_mjd = TimeConv::TimeToMjd(time, mjdref, tunit);
            //double time_obj_mjd = binorb->GetTimeObj(time_mjd);

            double delay_time = -1 * ax_sini
                * sin( 2 * kPi * (time_mjd - time_peri) / orb_period );
            
            // double time_obj = TimeConv::MjdToTime(time_obj_mjd, mjdref, tunit);

            
            double time_obj = time - delay_time;
            
            time_obj_vec.push_back(time_obj);

            fprintf(fp, "%e  %e\n", time_mjd, time - time_obj);
        }
        data_arr_shift->Init(time_obj_vec.size());
        data_arr_shift->SetVal(time_obj_vec);
        delete binorb;

        int nterm = 50;
        Interval* gti_one = new Interval;
        gti_one->InitSet(data_arr->GetValMin(), data_arr->GetValMax());
        Interval* gti_split = new Interval;
        gti_split->Split(gti_one, nterm);
        DataArray1d** data_arr_shift_arr = NULL;
        DataArray1dOpe::GenSelectDa1dArrByIntervalNerr(data_arr_shift, gti_split,
                                                       &data_arr_shift_arr);

        HistData1d* h1d_chi2_sum = new HistDataNerr1d;
        h1d_chi2_sum->Init(nbin_nu, nu_lo, nu_up);
        
        for(int iterm = 0; iterm < nterm; iterm++){
            for(long inu = 0; inu < nbin_nu; inu ++){
                double nu = nu_lo + (inu + 0.5) * delta_nu;
                double nudot = 0.0;
                double nu_dot2 = 0.0;
                eph->Set(nu, 0.0, nudot, 0.0,
                         nu_dot2, 0.0, 0.0, 0.0,
                         0.0, 0.0,
                         epoch_mjd, time_mjd_st, time_mjd_ed);

                HistDataSerr1d* h1d_pls = MitFolding::GenFolding(data_arr_shift_arr[iterm],
                                                                  mjdref, tunit,
                                                                  eph, nbin);
                double sigval = PulseProfStat::GetChi2(h1d_pls);

               
                //h1d_chi2_arr[iorbamp]->SetOvalElm(inu, sigval);
                //h2d_chi2->SetOvalElm(h2d_chi2->GetIbin(inu, iorbamp), sigval);

                // printf("inu sigval = %ld, %e\n", inu, sigval);
                h1d_chi2_sum->Fill(nu, sigval);
                
                //if(sigval > sigval_max){
                //    eph_best->Copy(eph);
                //    h1d_pls_best->Copy(h1d_pls);
                //    sigval_max = sigval;
                // }
                delete h1d_pls;
            }

            //printf("iterm = %ld, sigvaladd = %e\n",
            //       iterm,
            //       h1d_chi2_sum->GetOvalElm(0));
        }

        for(long inu = 0; inu < nbin_nu; inu ++){
            double sigval_sum = h1d_chi2_sum->GetOvalElm(inu);

            // printf("sigval_sum = %e\n", sigval_sum);
            
            h1d_chi2_arr[iorbamp]->SetOvalElm(inu, sigval_sum);
            h2d_chi2->SetOvalElm(inu, iorbamp, sigval_sum);
        }

        delete data_arr_shift;

        delete gti_one;
        delete gti_split;
        for(int iterm = 0; iterm < 10; iterm++){
            delete data_arr_shift_arr[iterm];
        }
        delete [] data_arr_shift_arr;
        delete h1d_chi2_sum;
        

        fprintf(fp, "\n");
        fprintf(fp, "no\n");
        fprintf(fp, "\n");
        
    }
    printf("\n");

    fclose(fp);
    
    *h2d_chi2_ptr = h2d_chi2;
    *h1d_chi2_arr_ptr = h1d_chi2_arr;
    *eph_best_ptr = eph_best;
    *h1d_pls_best_ptr = h1d_pls_best;
    delete eph;
}


//
//void GenEfsNuNuDot(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
//                   int nbin_nu, double nu_lo, double nu_up,
//                   int nbin_nudot, double nudot_lo, double nudot_up,
//                   double nu_dot2,
//                   double epoch_mjd, int nbin,
//                   HistData2d**  h2d_chi2_ptr,
//                   HistData1d*** h1d_chi2_arr_ptr,
//                   Ephemeris** eph_best_ptr,
//                   HistDataSerr1d** h1d_pls_best_ptr)
//{
//    double delta_nu = (nu_up - nu_lo) / nbin_nu;
//    if (nu_up - nu_lo < 0){
//        printf("bad nu_lo, nu_up: %e %e\n", nu_lo, nu_up);
//        abort();
//    }
//    double delta_nudot = (nudot_up - nudot_lo) / nbin_nudot;
//    if (nudot_up - nudot_lo < 0){
//        printf("bad nudot_lo, nudot_up: %e %e\n", nudot_lo, nudot_up);
//        abort();
//    }
//    printf("EfsNuNuDot(): delta_nu    = %e\n", delta_nu);
//    printf("EfsNuNuDot(): delta_nudot = %e\n", delta_nudot);
//  
//    Ephemeris* eph_best = new Ephemeris;
//    HistDataSerr1d* h1d_pls_best = new HistDataSerr1d;
//    Ephemeris* eph = new Ephemeris;
//    HistData2d* h2d_chi2 = new HistData2d;
//    h2d_chi2->Init(nbin_nu, nu_lo, nu_up,
//                  nbin_nudot, nudot_lo, nudot_up);
//    HistData1d** h1d_chi2_arr = new HistData1d* [nbin_nudot];
//    for(int ibin = 0; ibin < nbin_nudot; ibin ++){
//        h1d_chi2_arr[ibin] = new HistData1d;
//        h1d_chi2_arr[ibin]->Init(nbin_nu, nu_lo, nu_up);
//    }
//
//    double time_mjd_st = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMin(), mjdref, tunit);
//    double time_mjd_ed = TimeConv::TimeToMjd(g2d->GetXvalArr()->GetValMax(), mjdref, tunit);
//
//    double sigval_max = 0.0;
//    printf("EfsNuNuDot: inudot#: ");
//    for(long inudot = 0; inudot < nbin_nudot; inudot ++){
//        double nudot = nudot_lo + (inudot + 0.5) * delta_nudot;
//        printf(" %ld", inudot);
//        fflush(stdout);
//        for(long inu = 0; inu < nbin_nu; inu ++){
//            double nu = nu_lo + (inu + 0.5) * delta_nu;
//            eph->Set(nu, 0.0, nudot, 0.0,
//                     nu_dot2, 0.0, 0.0, 0.0,
//                     0.0, 0.0,
//                     epoch_mjd, time_mjd_st, time_mjd_ed);
//            HistDataSerr1d* h1d_pls = MitFolding::GenFoldingBinCenter(g2d,
//                                                                       mjdref, tunit,
//                                                                       eph, nbin);
//            double sigval = PulseProfStat::GetChi2(h1d_pls);
//            // printf("%.10e  %.10e  %.10e\n", nu, nudot, sigval);
//            h1d_chi2_arr[inudot]->SetOvalElm(inu, sigval);
//            h2d_chi2->SetOvalElm(h2d_chi2->GetIbin(inu, inudot), sigval);
//
//            if(sigval > sigval_max){
//                eph_best->Copy(eph);
//                h1d_pls_best->Copy(h1d_pls);
//                sigval_max = sigval;
//            }
//            delete h1d_pls;
//        }
//    }
//    printf("\n");
//
//    *h2d_chi2_ptr = h2d_chi2;
//    *h1d_chi2_arr_ptr = h1d_chi2_arr;
//    *eph_best_ptr = eph_best;
//    *h1d_pls_best_ptr = h1d_pls_best;
//    delete eph;
//}
//

