#include "sub.h"

void GenPow(const DataArray1d* const data_arr,
            double mjdref, string tunit,
            double tbinfwidth, 
            int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
            double epoch_mjd, string powspec_type,
            HistData1d** h1d_pow_max_ptr,
            HistData1d** h1d_pow_amean_ptr,
            HistData1d** h1d_pow_num_ptr)
{
    // powspec_type = "Press",  "Leahy"
    
    double lc_time_lo = data_arr->GetValMin() - 0.5 * tbinfwidth;
    double lc_time_up = data_arr->GetValMax() + 0.5 * tbinfwidth;
    long nbin_lc = MxkwMath::GetNbinEven(lc_time_lo, lc_time_up, tbinfwidth);
    printf("nbin_lc = %ld\n", nbin_lc);
    
    HistData1d* h1d_lcbin = new HistData1d;
    h1d_lcbin->Init(nbin_lc, lc_time_lo, lc_time_up);

    HistData1d* h1d_pow_max   = new HistData1d;
    HistData1d* h1d_pow_amean = new HistData1d;
    HistData1d* h1d_pow_num   = new HistData1d;
    HistData1d* h1d_pow_sum   = new HistData1d;
    h1d_pow_max->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_amean->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_num->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_sum->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);    

    double time_epoch = TimeConv::MjdToTime(epoch_mjd, mjdref, tunit);
    printf("%s: epoch_mjd = %e, time_epoch = %e\n",
           __func__, epoch_mjd, time_epoch);

    for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
        double time = data_arr->GetValElm(idata);
        h1d_lcbin->Fill(time);
    }
    // powspec
    HistData1d* h1d_powspec = new HistData1d;
    if("Press" == powspec_type){
        HistData1dOpe::GetPowSpec(h1d_lcbin, h1d_powspec);
    } else if("Leahy" == powspec_type){
        HistData1dOpe::GetPowSpecLeahyNorm(h1d_lcbin, h1d_powspec);
    } else {
        MPrintErr("bad powspec_type");
        abort();
    }

    // select
    long nbin_freq = h1d_powspec->GetNbinX();
    double freq_lo = h1d_powspec->GetXvalLo();
    double freq_up = h1d_powspec->GetXvalUp();
    double delta_freq = (freq_up - freq_lo) / nbin_freq;
    long ibin_st = MxkwMath::GetNbin(freq_lo, nu_plot_lo, delta_freq, "floor") -1;
    long ibin_ed = MxkwMath::GetNbin(freq_lo, nu_plot_up, delta_freq, "ceil") +1;
    for(long ibin = ibin_st; ibin < ibin_ed; ibin ++){
        if(nu_plot_lo < h1d_powspec->GetBinCenterX(ibin) &&
           h1d_powspec->GetBinCenterX(ibin) < nu_plot_up){
            h1d_pow_sum->Fill(h1d_powspec->GetBinCenterX(ibin),
                              h1d_powspec->GetOvalElm(ibin));
            h1d_pow_num->Fill(h1d_powspec->GetBinCenterX(ibin));
            h1d_pow_max->FillByMax(h1d_powspec->GetBinCenterX(ibin),
                                   h1d_powspec->GetOvalElm(ibin));
        }
    }
    vector<long> index_bad_vec;
    h1d_pow_amean->Div(h1d_pow_sum, h1d_pow_num, &index_bad_vec);
    delete h1d_lcbin;
    delete h1d_powspec;
    delete h1d_pow_sum;

    *h1d_pow_max_ptr = h1d_pow_max;
    *h1d_pow_amean_ptr = h1d_pow_amean;
    *h1d_pow_num_ptr = h1d_pow_num;
}


void GenPow(const GraphData2d* const g2d, double mjdref, string tunit,
            double tbinfwidth, 
            int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
            double epoch_mjd, string powspec_type,
            HistData1d** h1d_pow_max_ptr,
            HistData1d** h1d_pow_amean_ptr,
            HistData1d** h1d_pow_num_ptr,
            GraphData2d** g2d_pow_sel_ptr)
{
    // powspec_type = "Press",  "Leahy"
    
    double lc_time_lo = g2d->GetXvalArr()->GetValMin() - 0.5 * tbinfwidth;
    double lc_time_up = g2d->GetXvalArr()->GetValMax() + 0.5 * tbinfwidth;
    long nbin_lc = MxkwMath::GetNbinEven(lc_time_lo, lc_time_up, tbinfwidth);
    printf("nbin_lc = %ld\n", nbin_lc);
    
    HistData1d* h1d_lcbin = new HistData1d;
    h1d_lcbin->Init(nbin_lc, lc_time_lo, lc_time_up);

    HistData1d* h1d_pow_max   = new HistData1d;
    HistData1d* h1d_pow_amean = new HistData1d;
    HistData1d* h1d_pow_num   = new HistData1d;
    HistData1d* h1d_pow_sum   = new HistData1d;
    h1d_pow_max->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_amean->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_num->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    h1d_pow_sum->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);    

    double time_epoch = TimeConv::MjdToTime(epoch_mjd, mjdref, tunit);
    printf("%s: epoch_mjd = %e, time_epoch = %e\n",
           __func__, epoch_mjd, time_epoch);

    for(long idata = 0; idata < g2d->GetNdata(); idata ++){
        double time = g2d->GetXvalElm(idata);
        h1d_lcbin->Fill(time, g2d->GetOvalElm(idata));
    }
    
    // powspec
    HistData1d* h1d_powspec = new HistData1d;
    if("Press" == powspec_type){
        HistData1dOpe::GetPowSpec(h1d_lcbin, h1d_powspec);
    } else if("Leahy" == powspec_type){
        HistData1dOpe::GetPowSpecLeahyNorm(h1d_lcbin, h1d_powspec);
    } else {
        MPrintErr("bad powspec_type");
        abort();
    }

    // select
    long nbin_freq = h1d_powspec->GetNbinX();
    double freq_lo = h1d_powspec->GetXvalLo();
    double freq_up = h1d_powspec->GetXvalUp();
    double delta_freq = (freq_up - freq_lo) / nbin_freq;
    long ibin_st = MxkwMath::GetNbin(freq_lo, nu_plot_lo, delta_freq, "floor") -1;
    long ibin_ed = MxkwMath::GetNbin(freq_lo, nu_plot_up, delta_freq, "ceil") +1;
    
    GraphData2d* g2d_pow_sel = new GraphData2d;
    vector<double> pow_xval_sel_vec;
    vector<double> pow_oval_sel_vec;
    for(long ibin = ibin_st; ibin < ibin_ed; ibin ++){
        if(nu_plot_lo < h1d_powspec->GetBinCenterX(ibin) &&
           h1d_powspec->GetBinCenterX(ibin) < nu_plot_up){
            h1d_pow_sum->Fill(h1d_powspec->GetBinCenterX(ibin),
                              h1d_powspec->GetOvalElm(ibin));
            h1d_pow_num->Fill(h1d_powspec->GetBinCenterX(ibin));
            h1d_pow_max->FillByMax(h1d_powspec->GetBinCenterX(ibin),
                                   h1d_powspec->GetOvalElm(ibin));
            pow_xval_sel_vec.push_back(h1d_powspec->GetBinCenterX(ibin));
            pow_oval_sel_vec.push_back(h1d_powspec->GetOvalElm(ibin));
        }
    }
    vector<long> index_bad_vec;
    h1d_pow_amean->Div(h1d_pow_sum, h1d_pow_num, &index_bad_vec);
    delete h1d_lcbin;
    delete h1d_powspec;
    delete h1d_pow_sum;

    g2d_pow_sel->Init();
    g2d_pow_sel->SetXvalArrDbl(pow_xval_sel_vec);
    g2d_pow_sel->SetOvalArrDbl(pow_oval_sel_vec);

    *h1d_pow_max_ptr = h1d_pow_max;
    *h1d_pow_amean_ptr = h1d_pow_amean;
    *h1d_pow_num_ptr = h1d_pow_num;
    *g2d_pow_sel_ptr = g2d_pow_sel;
}


//
// ratio = nu_dot / nu
//
void GenPowRatio(const DataArray1d* const data_arr,
                 double mjdref, string tunit,
                 double tbinfwidth,
                 int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
                 long nbin_ratio, double ratio_lo, double ratio_up,
                 double epoch_mjd, string powspec_type,
                 HistData2d** h2d_pow_max_ptr,
                 HistData2d** h2d_pow_amean_ptr,
                 HistData2d** h2d_pow_num_ptr,
                 HistData1d*** h1d_pow_max_arr_ptr)
{
    // powspec_type = "Press",  "Leahy"
    
    if (ratio_up - ratio_lo < 0){
        printf("bad ratio_lo, ratio_up: %e %e\n", ratio_lo, ratio_up);
        abort();
    }

    double time_epoch = TimeConv::MjdToTime(epoch_mjd, mjdref, tunit);
    printf("%s: epoch_mjd = %e, time_epoch = %e\n",
           __func__, epoch_mjd, time_epoch);
    
    double time_shift_end_arr[4];
    time_shift_end_arr[0] = data_arr->GetValMin() + ratio_lo / 2.0
        * pow(data_arr->GetValMin() - time_epoch, 2);
    time_shift_end_arr[1] = data_arr->GetValMin() + ratio_up / 2.0
        * pow(data_arr->GetValMin() - time_epoch, 2);
    time_shift_end_arr[2] = data_arr->GetValMax() + ratio_lo / 2.0
        * pow(data_arr->GetValMax() - time_epoch, 2);
    time_shift_end_arr[3] = data_arr->GetValMax() + ratio_up / 2.0
        * pow(data_arr->GetValMax() - time_epoch, 2);

    double lc_time_lo = MxkwMath::GetMin(4, time_shift_end_arr) - 0.5 * tbinfwidth;
    double lc_time_up = MxkwMath::GetMax(4, time_shift_end_arr) + 0.5 * tbinfwidth;
    long nbin_lc = MxkwMath::GetNbinEven(lc_time_lo, lc_time_up, tbinfwidth);
    printf("nbin_lc = %ld\n", nbin_lc);
    
    HistData2d* h2d_pow_max = new HistData2d;
    HistData2d* h2d_pow_amean = new HistData2d;
    HistData2d* h2d_pow_num = new HistData2d;
    HistData2d* h2d_pow_sum = new HistData2d;
    h2d_pow_max->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up,
                      nbin_ratio, ratio_lo, ratio_up);
    h2d_pow_amean->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up,
                        nbin_ratio, ratio_lo, ratio_up);
    h2d_pow_num->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up,
                      nbin_ratio, ratio_lo, ratio_up);
    h2d_pow_sum->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up,
                      nbin_ratio, ratio_lo, ratio_up);     
    
    HistData1d** h1d_pow_max_arr = new HistData1d* [nbin_ratio];
    for(long iratio = 0; iratio < nbin_ratio; iratio++){
        h1d_pow_max_arr[iratio] = new HistData1d;
        h1d_pow_max_arr[iratio]->Init(nbin_nu_plot, nu_plot_lo, nu_plot_up);
    }


    double delta_ratio = (ratio_up - ratio_lo) / nbin_ratio;
    printf("%s: delta_ratio    = %e\n",
            __func__, delta_ratio);

    HistData1d* h1d_lcbin = new HistData1d;
    h1d_lcbin->Init(nbin_lc, lc_time_lo, lc_time_up);
    for(long iratio = 0; iratio < nbin_ratio; iratio ++){
        double ratio = ratio_lo + (iratio + 0.5) * delta_ratio;
        printf("iratio = %ld, ratio = %e\n", iratio, ratio);
        
        h1d_lcbin->SetZero();
        for(long idata = 0; idata < data_arr->GetNdata(); idata ++){
            double time = data_arr->GetValElm(idata);
            double time_shift = time + ratio / 2.0 * pow(time - time_epoch, 2);
            h1d_lcbin->Fill(time_shift);
        }

        // powspec
        HistData1d* h1d_powspec = new HistData1d;
        if("Press" == powspec_type){
            HistData1dOpe::GetPowSpec(h1d_lcbin, h1d_powspec);
        } else if("Leahy" == powspec_type){
            HistData1dOpe::GetPowSpecLeahyNorm(h1d_lcbin, h1d_powspec);
        } else {
            MPrintErr("bad powspec_type");
            abort();
        }

        // select
        long nbin_freq = h1d_powspec->GetNbinX();
        double freq_lo = h1d_powspec->GetXvalLo();
        double freq_up = h1d_powspec->GetXvalUp();
        double delta_freq = (freq_up - freq_lo) / nbin_freq;
        long ibin_st = MxkwMath::GetNbin(freq_lo, nu_plot_lo,
                                         delta_freq, "floor") -1;
        long ibin_ed = MxkwMath::GetNbin(freq_lo, nu_plot_up, delta_freq,
                                         "ceil") +1;
        for(long ibin = ibin_st; ibin < ibin_ed; ibin ++){
            if(nu_plot_lo < h1d_powspec->GetBinCenterX(ibin) &&
               h1d_powspec->GetBinCenterX(ibin) < nu_plot_up){

                h2d_pow_sum->Fill(h1d_powspec->GetBinCenterX(ibin), ratio,
                                  h1d_powspec->GetOvalElm(ibin));
                h2d_pow_num->Fill(h1d_powspec->GetBinCenterX(ibin), ratio);
                h2d_pow_max->FillByMax(h1d_powspec->GetBinCenterX(ibin), ratio,
                                       h1d_powspec->GetOvalElm(ibin));
                h1d_pow_max_arr[iratio]->FillByMax(h1d_powspec->GetBinCenterX(ibin),
                                                   h1d_powspec->GetOvalElm(ibin));
            }
        }
        delete h1d_powspec;
    } // for(long iratio = 0; iratio < nbin_ratio; iratio ++){

    vector<long> index_bad_vec;
    h2d_pow_amean->Div(h2d_pow_sum, h2d_pow_num, &index_bad_vec);
    delete h1d_lcbin;
    delete h2d_pow_sum;

    *h2d_pow_max_ptr = h2d_pow_max;
    *h2d_pow_amean_ptr = h2d_pow_amean;
    *h2d_pow_num_ptr = h2d_pow_num;
    *h1d_pow_max_arr_ptr = h1d_pow_max_arr;
}
