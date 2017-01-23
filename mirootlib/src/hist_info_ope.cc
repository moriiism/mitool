#include "mir_hist_info_ope.h"

void HistInfo1dOpe::GenSelectHi1dArrByInterval(const HistInfo1d* const hist_info,
                                               const Interval* const interval,
                                               long* nhi1d_sel_ptr,
                                               HistInfo1d*** hi1d_sel_arr_ptr,
                                               Interval** interval_sel_ptr,
                                               string select_type)
{
    long nhi1d_sel = 0;    
    HistInfo1d** hi1d_sel_arr = NULL;
    Interval* interval_sel = new Interval;
    if("exclusive" == select_type){
        vector<double> xval_lo_vec;
        vector<double> xval_up_vec;
        vector<long>   nbin_vec;
        for(long iterm = 0; iterm < interval->GetNterm(); iterm ++){
            long ibin_lo = MirMath::GetNbin(hist_info->GetLo(),
                                             interval->GetTstartElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "ceil");
            long ibin_up = MirMath::GetNbin(hist_info->GetLo(),
                                             interval->GetTstopElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "floor");
            if(ibin_lo < ibin_up){
                double xval_lo = hist_info->GetLo()
                    + ibin_lo * hist_info->GetBinWidth();
                double xval_up = hist_info->GetLo()
                    + ibin_up * hist_info->GetBinWidth();
                long ibin = ibin_up - ibin_lo;
                xval_lo_vec.push_back(xval_lo);
                xval_up_vec.push_back(xval_up);
                nbin_vec.push_back(ibin);
            }
        }

        nhi1d_sel = xval_lo_vec.size();
        hi1d_sel_arr = new HistInfo1d* [nhi1d_sel];
        for(int ihi1d = 0; ihi1d < nhi1d_sel; ihi1d++){
            hi1d_sel_arr[ihi1d] = new HistInfo1d;
            hi1d_sel_arr[ihi1d]->InitSetByNbin(
                xval_lo_vec[ihi1d],
                xval_up_vec[ihi1d],
                nbin_vec[ihi1d]);
        }
        interval_sel->Init(xval_lo_vec.size());
        interval_sel->Set(xval_lo_vec, xval_up_vec);
    } else if ("inclusive" == select_type){
        vector<double> xval_lo_vec;
        vector<double> xval_up_vec;
        vector<long>   nbin_vec;
        for(long iterm = 0; iterm < interval->GetNterm(); iterm ++){
            long ibin_lo = MirMath::GetNbin(hist_info->GetLo(),
                                             interval->GetTstartElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "floor");
            long ibin_up = MirMath::GetNbin(hist_info->GetLo(),
                                             interval->GetTstopElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "ceil");
            if(ibin_lo < ibin_up){
                double xval_lo = hist_info->GetLo()
                    + ibin_lo * hist_info->GetBinWidth();
                double xval_up = hist_info->GetLo()
                    + ibin_up * hist_info->GetBinWidth();
                long ibin = ibin_up - ibin_lo;
                xval_lo_vec.push_back(xval_lo);
                xval_up_vec.push_back(xval_up);
                nbin_vec.push_back(ibin);
            }
        }

        nhi1d_sel = xval_lo_vec.size();
        hi1d_sel_arr = new HistInfo1d* [nhi1d_sel];
        for(int ihi1d = 0; ihi1d < nhi1d_sel; ihi1d++){
            hi1d_sel_arr[ihi1d] = new HistInfo1d;
            hi1d_sel_arr[ihi1d]->InitSetByNbin(
                xval_lo_vec[ihi1d],
                xval_up_vec[ihi1d],
                nbin_vec[ihi1d]);
        }
        interval_sel->Init(xval_lo_vec.size());
        interval_sel->Set(xval_lo_vec, xval_up_vec);
    } else if ("center" == select_type){
        vector<double> xval_lo_vec;
        vector<double> xval_up_vec;
        vector<long>   nbin_vec;
        for(long iterm = 0; iterm < interval->GetNterm(); iterm ++){
            long ibin_lo = MirMath::GetNbin(hist_info->GetLo() +
                                             hist_info->GetBinWidth()/2.,
                                             interval->GetTstartElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "ceil");
            long ibin_up = MirMath::GetNbin(hist_info->GetLo() +
                                             hist_info->GetBinWidth()/2.,
                                             interval->GetTstopElm(iterm),
                                             hist_info->GetBinWidth(),
                                             "floor");
            if(ibin_lo <= ibin_up){
                double xval_lo = hist_info->GetLo()
                    + ibin_lo * hist_info->GetBinWidth();
                double xval_up = hist_info->GetLo()
                    + (ibin_up + 1) * hist_info->GetBinWidth();
                long ibin = ibin_up - ibin_lo + 1;
                xval_lo_vec.push_back(xval_lo);
                xval_up_vec.push_back(xval_up);
                nbin_vec.push_back(ibin);
            }
        }
        nhi1d_sel = xval_lo_vec.size();
        hi1d_sel_arr = new HistInfo1d* [nhi1d_sel];
        for(int ihi1d = 0; ihi1d < nhi1d_sel; ihi1d++){
            hi1d_sel_arr[ihi1d] = new HistInfo1d;
            hi1d_sel_arr[ihi1d]->InitSetByNbin(
                xval_lo_vec[ihi1d],
                xval_up_vec[ihi1d],
                nbin_vec[ihi1d]);
        }
        interval_sel->Init(xval_lo_vec.size());
        interval_sel->Set(xval_lo_vec, xval_up_vec);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad select_type(=%s)", select_type.c_str());
        MPrintErr(msg);
        abort();
    }

    *nhi1d_sel_ptr = nhi1d_sel;    
    *hi1d_sel_arr_ptr = hi1d_sel_arr;
    *interval_sel_ptr = interval_sel;
}
