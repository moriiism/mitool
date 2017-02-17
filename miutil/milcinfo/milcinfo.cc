//#include "TFile.h"
//#include "TTree.h"
//#include "TMath.h"
//#include "TCanvas.h"

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
    argval->Print(stdout);

    //
    // data file
    //
    long nline = 0;
    string* line_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetInfile(),
                                    &line_arr, &nline);
    printf("nline = %ld\n", nline);
    for(long iline = 0; iline < nline; iline ++){
        int ncol = MiStr::GetNcolumn(line_arr[iline]);
        printf("ncol = %d\n", ncol);
    }
    
    GraphDataNerr2d* gd2d = new GraphDataNerr2d;
    gd2d->Load(argval->GetInfile());
    //int sorted = MirMath::IsSorted(gd2d->GetNdata(),
    //                               gd2d->GetXvalArr()->GetVal());
    //printf("sorted ? = %d\n", sorted);
    gd2d->Sort();
    int sorted = MirMath::IsSorted(gd2d->GetNdata(),
                                   gd2d->GetXvalArr()->GetVal());
    printf("sorted ? = %d\n", sorted);
    MirQdpTool::MkQdp(gd2d, "temp.qdp", "x,y");

    double time_st = gd2d->GetXvalElm(0);
    double time_ed = gd2d->GetXvalElm(gd2d->GetNdata() - 1);
    double time_span = time_ed - time_st;

    printf("time_st = %e\n", time_st);
    printf("time_ed = %e\n", time_ed);
    printf("time_span = %e\n", time_span);

    vector<double> diff_vec;
    for(long idata = 0; idata < gd2d->GetNdata() - 1; idata ++){
        diff_vec.push_back(gd2d->GetXvalElm(idata + 1) - gd2d->GetXvalElm(idata) );
    }
    DataArrayNerr1d* da1d_diff = new DataArrayNerr1d;
    da1d_diff->Init(diff_vec.size());
    da1d_diff->SetVal(diff_vec);
    double diff_min = da1d_diff->GetValMin();
    double diff_max = da1d_diff->GetValMax();
    printf("diff_min = %e\n", diff_min);
    printf("diff_max = %e\n", diff_max);

    double diff_min_plus = diff_max;
    for(int idata = 0; idata < (int) diff_vec.size(); idata ++){
        if(diff_vec[idata] > 0){
            if(diff_min_plus > diff_vec[idata]){
                diff_min_plus = diff_vec[idata];
            }
        }
    }
    printf("diff_min_plus = %e\n", diff_min_plus);
    
    double diff_hist_lo = 0.0;
    double diff_hist_up = 1.0e-4;
    long nbin_hd1d_diff = 100;
    HistDataNerr1d* hd1d_diff = new HistDataNerr1d;
    hd1d_diff->Init(nbin_hd1d_diff, diff_hist_lo, diff_hist_up);
    for(long idata = 0; idata < da1d_diff->GetNdata(); idata ++){
        if(diff_hist_lo < da1d_diff->GetValElm(idata) &&
           da1d_diff->GetValElm(idata) < diff_hist_up){
            hd1d_diff->Fill(da1d_diff->GetValElm(idata));
        }
    }
    MirQdpTool::MkQdp(hd1d_diff, "temp_diff.qdp", "x,y");

    double freq_min = 1./time_span;    
    double freq_max = 1./diff_min_plus;
    printf("freq_min = %e\n", freq_min);
    printf("freq_max = %e\n", freq_max);
    
    
    delete argval;
    
    return status;
}

