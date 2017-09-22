#include "sub.h"

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

