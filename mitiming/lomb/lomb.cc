#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"

#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "arg_lomb.h"
#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValLomb* argval = new ArgValLomb;
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

    DataArray1d* da1d = NULL;
    DataArray1d* da1d_mjd_sec = NULL;
    
    GraphData2d* gd2d  = NULL;
    GraphData2d* gd2d_mjd_sec  = NULL;
   
    if("x" == argval->GetFormat()){
        da1d = new DataArray1d;
        da1d->Load(argval->GetFile());
        da1d->Sort();
        DataArray1d* da1d_mjd
            = TimeConv::GenTimeToMjd(da1d,
                                     Telescope::GetMjdref(
                                         argval->GetTelescope()),
                                     argval->GetTunit());
        da1d_mjd_sec
            = TimeConv::GenMjdToTime(da1d_mjd, 0.0, "sec");
        delete da1d_mjd;
    } else {
        gd2d = GraphData2d::GenGd2dByLoad(argval->GetFile(), argval->GetFormat());
        gd2d->Sort();
        GraphData2d* gd2d_mjd
            = TimeConv::GenTimeToMjd(gd2d,
                                     Telescope::GetMjdref(
                                         argval->GetTelescope()),
                                     argval->GetTunit());
        gd2d_mjd_sec
            = TimeConv::GenMjdToTime(gd2d_mjd, 0.0, "sec");
        
        delete gd2d_mjd;
    }

    MxkwSearchPar* plot_dat_par = new MxkwSearchPar;
    plot_dat_par->Load(argval->GetSearchDat());
    plot_dat_par->Print(stdout);
    plot_dat_par->Print(fp_log);
    
    
    if(1 == plot_dat_par->GetNpar()){
        HistData1d* hd1d_lomb = NULL;
        if("x" == argval->GetFormat()){

            // not defined
            abort();
            
            hd1d_lomb = GenHd1dLomb(da1d_mjd_sec,
                                    plot_dat_par->GetNbinElm(0),
                                    plot_dat_par->GetLoElm(0),
                                    plot_dat_par->GetUpElm(0));
        } else {
            hd1d_lomb = GenHd1dLomb(gd2d_mjd_sec,
                                    plot_dat_par->GetNbinElm(0),
                                    plot_dat_par->GetLoElm(0),
                                    plot_dat_par->GetUpElm(0));
        }
        MxkwQdpTool::MkQdp(hd1d_lomb, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_lomb.qdp",
                           "x,y");
        delete hd1d_lomb;
    } else if(2 == plot_dat_par->GetNpar()){
        double epoch_mjd_sec = TimeConv::MjdToTime(argval->GetEpochMjd(), 0.0, "sec");
        HistData2d* hd2d_lomb = NULL;
        if("x" == argval->GetFormat()){
            // ratio : nu_dot / nu

            // not defined
            abort();
            
            
            hd2d_lomb = GenHd2dLomb(da1d_mjd_sec,
                                    plot_dat_par->GetNbinElm(0),
                                    plot_dat_par->GetLoElm(0),
                                    plot_dat_par->GetUpElm(0),
                                    plot_dat_par->GetNbinElm(1),
                                    plot_dat_par->GetLoElm(1),
                                    plot_dat_par->GetUpElm(1),
                                    epoch_mjd_sec);
        } else {
            hd2d_lomb = GenHd2dLomb(gd2d_mjd_sec,
                                    plot_dat_par->GetNbinElm(0),
                                    plot_dat_par->GetLoElm(0),
                                    plot_dat_par->GetUpElm(0),
                                    plot_dat_par->GetNbinElm(1),
                                    plot_dat_par->GetLoElm(1),
                                    plot_dat_par->GetUpElm(1),
                                    epoch_mjd_sec);
        }
        hd2d_lomb->MkTH2Fig(argval->GetOutdir() + "/"
                            + argval->GetOutfileHead() + "_lomb.png",
                            root_tool);
        delete hd2d_lomb;
    } else {
        MPrintErr("bad search dat");
        abort();
    }

    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;
    if(NULL != da1d) {delete da1d;}
    if(NULL != da1d_mjd_sec) {delete da1d_mjd_sec;}
    if(NULL != gd2d) {delete gd2d;}
    if(NULL != gd2d_mjd_sec) {delete gd2d_mjd_sec;}
    delete plot_dat_par;

    return status;
}

