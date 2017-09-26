#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "mxkw_qdp_tool.h"

#include "arg_draw_lcpls_rate.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValDrawLcplsRate* argval = new ArgValDrawLcplsRate;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    char logfile[kLineSize];
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    argval->Print(fp_log);

    MxkwPlotConf* plot_conf = new MxkwPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    
    Ephemeris* eph = new Ephemeris;
    eph->Load(argval->GetEphfile());
    eph->Print(stdout);
    eph->Print(fp_log);
    
    //
    // count rate (c/s) function
    //
    HistData1d* hist_pls = new HistData1d;
    hist_pls->Load(argval->GetHistPls());

    HistPlsFunc* func = new HistPlsFunc;
    func->InitSet(argval->GetTunit(),
                  Telescope::GetMjdref(argval->GetTelescope()),
                  eph, NULL);
    func->InitSetHd1d(hist_pls);

    // HistInfo1d
    HistInfo1d* hist_info = new HistInfo1d;
    hist_info->Load(argval->GetHistInfo());

    // hist function
    HistData1d* h1d_func = new HistData1d;
    h1d_func->Init(hist_info);
    h1d_func->SetByFunc(func, NULL);
    h1d_func->Save(argval->GetOutdir() + "/"
                   + argval->GetOutfileHead() + ".dat",
                   "x,xe,y,ye");
    MxkwQdpTool::MkQdp(h1d_func, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + ".qdp", "x,xe,y,ye",
                       plot_conf);

//     // GTI selection
//     Interval* gti = new Interval;
//     gti->Load(argval->GetGtifile());
//     HistData1d* h1d_func_sel = new HistData1d;
//     HistData1dOpe::GetSelectHd1dByInterval(h1d_func, gti,
//                                            h1d_func_sel);
//     h1d_func_sel->Save(argval->GetOutdir() + "/"
//                        + argval->GetOutfileHead() + ".dat",
//                       "x,xe,y,ye");
    
    
    //
    // cleaning
    //
    
    fclose(fp_log);
    delete argval;
    delete eph;
    delete func;
    delete hist_info;
    delete h1d_func;
    delete plot_conf;

    return status;
}
