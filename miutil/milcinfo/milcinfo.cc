#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_qdp_tool.h"
#include "arg_milcinfo.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMilcinfo* argval = new ArgValMilcinfo;
    argval->Init(argc, argv);
    
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }

    char file_summary[kLineSize];
    sprintf(file_summary, "%s/%s_sum.txt",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    FILE* fp_summary = fopen(file_summary, "w");
    MiIolib::Printf2(fp_summary,
                     "%s: -----------------------------\n",
                     argval->GetProgname().c_str());
    argval->Print(stdout);
    argval->Print(fp_summary);
    MiIolib::Printf2(fp_summary,
                     "%s: -----------------------------\n",
                     argval->GetProgname().c_str());    
    //
    // load data
    //
    GraphData2d* gd2d = GraphData2dOpe::GenGd2dByLoad(argval->GetInfile(),
                                                      argval->GetFormat());
    // head 10 line
    long nline_head = 10;    
    MiIolib::Printf2(fp_summary, "--- head %ld line ---\n", nline_head);
    long idata_ed = MirMath::GetMin(nline_head, gd2d->GetNdata());
    MiIolib::Printf2(fp_summary, "index  time  diff\n");
    for(long idata = 0; idata < idata_ed; idata ++){
        double diff = gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata);
        MiIolib::Printf2(fp_summary, "%ld  %.10e  %e\n", idata, gd2d->GetXvalElm(idata), diff);
    }
    MiIolib::Printf2(fp_summary, "=========\n");
    
    // last 10 line
    long nline_last = 10;    
    MiIolib::Printf2(fp_summary, "--- last %ld line ---\n", nline_last);
    long idata_st = MirMath::GetMax(0, gd2d->GetNdata() - nline_last);
    for(long idata = idata_st; idata < gd2d->GetNdata(); idata ++){
        double diff = gd2d->GetXvalElm(idata) - gd2d->GetXvalElm(idata - 1);
        MiIolib::Printf2(fp_summary, "%ld  %.10e  %e\n", idata, gd2d->GetXvalElm(idata), diff);
    }
    MiIolib::Printf2(fp_summary, "=========\n");

    //
    // check sorted or not
    //
    int sorted_org = MirMath::IsSorted(gd2d->GetNdata(),
                                       gd2d->GetXvalArr()->GetVal());
    MiIolib::Printf2(fp_summary, "Org data: Is sorted (Y/N)? = %d\n", sorted_org);
    gd2d->Sort();
    int sorted = MirMath::IsSorted(gd2d->GetNdata(),
                                   gd2d->GetXvalArr()->GetVal());
    MiIolib::Printf2(fp_summary, "Sorted data: Is sorted (Y/N)? = %d\n", sorted);

    //
    // save sorted light curve
    //
    char lcfile_sorted[kLineSize];
    sprintf(lcfile_sorted, "%s/%s_sorted.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    MirQdpTool::MkQdp(gd2d, lcfile_sorted, argval->GetFormat(),
                      "", "", 0.0, 0.0,
                      "lin", "lin");

    char lcfile_sorted_offset[kLineSize];
    sprintf(lcfile_sorted_offset, "%s/%s_sorted_offset.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    MirQdpTool::MkQdp(gd2d, lcfile_sorted_offset, argval->GetFormat(),
                      "", "", gd2d->GetOffsetXFromTag(argval->GetTimeOffset()), 0.0,
                      "lin", "lin");

    //
    // save sorted light curve with format of "xval, oval"
    //
    char lcqdp_sorted_format2_offset[kLineSize];
    sprintf(lcqdp_sorted_format2_offset, "%s/%s_sorted_format2_offset.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    MirQdpTool::MkQdp(gd2d, lcqdp_sorted_format2_offset, "x,y",
                      "", "", gd2d->GetOffsetXFromTag(argval->GetTimeOffset()), 0.0,
                      "lin", "lin");
    
    char lcdat_sorted_format2_offset[kLineSize];
    sprintf(lcdat_sorted_format2_offset, "%s/%s_sorted_format2_offset.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    gd2d->Save(lcdat_sorted_format2_offset, "x,y",
               gd2d->GetOffsetXFromTag(argval->GetTimeOffset()));
    
    char lcfile_sorted_format2[kLineSize];
    sprintf(lcfile_sorted_format2, "%s/%s_sorted_format2.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    gd2d->Save(lcfile_sorted_format2, "x,y");

    //
    // standardize
    //
    long narr_oval_std = gd2d->GetOvalArr()->GetNdata();
    double mean = MirMath::GetAMean(narr_oval_std,
                                    gd2d->GetOvalArr()->GetVal());
    double stddev = MirMath::GetStddev(narr_oval_std,
                                       gd2d->GetOvalArr()->GetVal());
    double* oval_std_arr = new double [narr_oval_std];
    for(long iarr = 0; iarr < narr_oval_std; iarr++){
        oval_std_arr[iarr] = (gd2d->GetOvalElm(iarr) - mean) / stddev;
    }
    GraphDataNerr2d* gd2d_std = new GraphDataNerr2d;
    gd2d_std->Init(narr_oval_std);
    gd2d_std->SetXvalArr(gd2d->GetXvalArr());
    gd2d_std->SetOvalArr(narr_oval_std, oval_std_arr);

    //
    // save standardized light curve with format of "xval, oval"
    //
    char lcdat_std_offset[kLineSize];
    sprintf(lcdat_std_offset, "%s/%s_std_offset.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    gd2d_std->Save(lcdat_std_offset, "x,y",
                   gd2d_std->GetOffsetXFromTag(argval->GetTimeOffset()));
    
    //
    // summary
    //
    double time_st = gd2d->GetXvalElm(0);
    double time_ed = gd2d->GetXvalElm(gd2d->GetNdata() - 1);
    double time_span = time_ed - time_st;

    MiIolib::Printf2(fp_summary, "ndata   = %ld\n", gd2d->GetNdata());
    MiIolib::Printf2(fp_summary, "time_st = %e\n", time_st);
    MiIolib::Printf2(fp_summary, "time_ed = %e\n", time_ed);
    MiIolib::Printf2(fp_summary, "time_span = %e\n", time_span);

    vector<double> diff_vec;
    for(long idata = 0; idata < gd2d->GetNdata() - 1; idata ++){
        diff_vec.push_back(gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata) );
    }
    DataArrayNerr1d* da1d_diff = new DataArrayNerr1d;
    da1d_diff->Init(diff_vec.size());
    da1d_diff->SetVal(diff_vec);
    double diff_min = da1d_diff->GetValMin();
    double diff_max = da1d_diff->GetValMax();
    MiIolib::Printf2(fp_summary, "diff_min = %e\n", diff_min);
    MiIolib::Printf2(fp_summary, "diff_max = %e\n", diff_max);

    double diff_min_plus = diff_max;
    for(int idata = 0; idata < (int) diff_vec.size(); idata ++){
        if(diff_vec[idata] > 0){
            if(diff_min_plus > diff_vec[idata]){
                diff_min_plus = diff_vec[idata];
            }
        }
    }
    MiIolib::Printf2(fp_summary, "diff_min_plus = %e\n", diff_min_plus);
    
    //
    // diff time histogram
    //
    HistInfo1d* hi1d = new HistInfo1d;
    hi1d->Load(argval->GetHistInfoDiffTimeFile());
    
    double diff_hist_lo = hi1d->GetLo();
    double diff_hist_up = hi1d->GetUp();
    long nbin_hd1d_diff = hi1d->GetNbin();
    HistDataNerr1d* hd1d_diff = new HistDataNerr1d;
    hd1d_diff->Init(nbin_hd1d_diff, diff_hist_lo, diff_hist_up);
    for(long idata = 0; idata < da1d_diff->GetNdata(); idata ++){
        if(diff_hist_lo < da1d_diff->GetValElm(idata) &&
           da1d_diff->GetValElm(idata) < diff_hist_up){
            hd1d_diff->Fill(da1d_diff->GetValElm(idata));
        }
    }
    char diff_time_file[kLineSize];
    sprintf(diff_time_file, "%s/%s_diff_time.qdp",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());    
    MirQdpTool::MkQdp(hd1d_diff, diff_time_file, "x,y");

    //
    // mode of diff time 
    //
    double mode_diff_time = hd1d_diff->GetXvalAtOvalMax();
    MiIolib::Printf2(fp_summary,
                     "mode of diff_time distribution = %e\n",
                     mode_diff_time);

    //
    // frequency info
    // 
    double freq_min = 1./time_span;
    double freq_max = 1./diff_min_plus;
    double freq_mode_diff_time = 1./mode_diff_time;
    MiIolib::Printf2(fp_summary, "freq_min = %e\n", freq_min);
    MiIolib::Printf2(fp_summary, "freq_max = %e\n", freq_max);
    MiIolib::Printf2(fp_summary, "freq_mode_diff_time = %e\n", freq_mode_diff_time);

    //
    // nfreq
    //
    long nfreq = (long) floor(freq_max / freq_min);
    MiIolib::Printf2(fp_summary, "nfreq = %ld \n", nfreq);

    long nfreq_dominant_tic = (long) floor(freq_mode_diff_time / freq_min);
    MiIolib::Printf2(fp_summary, "nfreq_dominant_tic = %ld \n", nfreq_dominant_tic);
    
    MiIolib::Printf2(fp_summary,
                     "%s: =============================\n",
                     argval->GetProgname().c_str());    
    
    delete argval;
    
    return status;
}

