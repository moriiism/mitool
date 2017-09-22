#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"

#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "arg_pow.h"
#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPow* argval = new ArgValPow;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    argval->Print(fp_log);

    MxkwRootTool* root_tool = new MxkwRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;
    if("x" == argval->GetFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetFile());
        data_arr->Sort();
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetFile(), argval->GetFormat());
        g2d->Sort();
    }

    MxkwSearchPar* plot_dat_par = new MxkwSearchPar;
    plot_dat_par->Load(argval->GetSearchDat());
    plot_dat_par->Print(stdout);
    plot_dat_par->Print(fp_log);
    
    if(1 == plot_dat_par->GetNpar()){
        HistData1d* h1d_pow_max = NULL;
        HistData1d* h1d_pow_amean = NULL;
        HistData1d* h1d_pow_num = NULL;
        GraphData2d* g2d_pow_sel = NULL;
        if("x" == argval->GetFormat()){
            GenPow(data_arr, Telescope::GetMjdref(argval->GetTelescope()),
                   argval->GetTunit(),
                   argval->GetTbinfwidth(),
                   plot_dat_par->GetNbinElm(0),
                   plot_dat_par->GetLoElm(0),
                   plot_dat_par->GetUpElm(0),
                   argval->GetEpochMjd(),
                   argval->GetPowspecType(),
                   &h1d_pow_max,
                   &h1d_pow_amean,
                   &h1d_pow_num);
        } else {
            GenPow(g2d, Telescope::GetMjdref(argval->GetTelescope()),
                   argval->GetTunit(),
                   argval->GetTbinfwidth(),
                   plot_dat_par->GetNbinElm(0),
                   plot_dat_par->GetLoElm(0),
                   plot_dat_par->GetUpElm(0),
                   argval->GetEpochMjd(),
                   argval->GetPowspecType(),
                   &h1d_pow_max,
                   &h1d_pow_amean,
                   &h1d_pow_num,
                   &g2d_pow_sel);
            MxkwQdpTool::MkQdp(g2d_pow_sel, argval->GetOutdir() + "/"
                               + argval->GetOutfileHead() + "_pow_sel.qdp",
                               "x,xe,y,ye");
            delete g2d_pow_sel;
        }
        MxkwQdpTool::MkQdp(h1d_pow_max, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_pow_max.qdp",
                           "x,xe,y,ye");
        MxkwQdpTool::MkQdp(h1d_pow_amean, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_pow_amean.qdp",
                           "x,xe,y,ye");
        MxkwQdpTool::MkQdp(h1d_pow_num, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_pow_num.qdp",
                           "x,xe,y,ye");

        delete h1d_pow_max;
        delete h1d_pow_amean;
        delete h1d_pow_num;
    } else if(2 == plot_dat_par->GetNpar()){
        HistData2d* h2d_pow_max = NULL;
        HistData2d* h2d_pow_amean = NULL;
        HistData2d* h2d_pow_num = NULL;
        HistData1d** h1d_pow_max_arr = NULL;
        double nu_dot2 = 0.0;
        if("x" == argval->GetFormat()){
            // ratio : nu_dot / nu
            GenPowRatio(data_arr,
                        Telescope::GetMjdref(argval->GetTelescope()),
                        argval->GetTunit(),
                        argval->GetTbinfwidth(),
                        plot_dat_par->GetNbinElm(0),
                        plot_dat_par->GetLoElm(0),
                        plot_dat_par->GetUpElm(0),
                        plot_dat_par->GetNbinElm(1),
                        plot_dat_par->GetLoElm(1),
                        plot_dat_par->GetUpElm(1),
                        argval->GetEpochMjd(),
                        argval->GetPowspecType(),
                        &h2d_pow_max,
                        &h2d_pow_amean,
                        &h2d_pow_num,
                        &h1d_pow_max_arr);
        } else {
            
        }
        h2d_pow_max->MkTH2Fig(argval->GetOutdir() + "/"
                              + argval->GetOutfileHead() + "_pow_max.png",
                              root_tool);
        h2d_pow_amean->MkTH2Fig(argval->GetOutdir() + "/"
                                + argval->GetOutfileHead() + "_pow_amean.png",
                                root_tool);
        h2d_pow_num->MkTH2Fig(argval->GetOutdir() + "/"
                              + argval->GetOutfileHead() + "_pow_num.png",
                              root_tool);
        MxkwQdpTool::MkQdpNhist(h1d_pow_max_arr,
                                plot_dat_par->GetNbinElm(1),
                                argval->GetOutdir() + "/"
                                + argval->GetOutfileHead() + "_nhist_pow_max.qdp",
                                0.0);
        for(int iratio = 0; iratio < plot_dat_par->GetNbinElm(1); iratio ++){
            delete h1d_pow_max_arr[iratio];
        }
        delete [] h1d_pow_max_arr;
    } else {
        MPrintErr("bad search dat");
        abort();
    }

    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;
    delete data_arr;
    delete plot_dat_par;

    return status;
}

