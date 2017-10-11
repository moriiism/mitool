#include "mi_iolib.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mir_func_par.h"
#include "mit_telescope.h"
#include "mit_func_pls.h"
#include "mit_folding.h"
#include "mir_qdp_tool.h"

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

     if(MiIolib::TestFileExist(argval->GetOutdir())){
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
  
     Ephemeris* eph = new Ephemeris;
     eph->Load(argval->GetEphfile());
     eph->Print(stdout);
     eph->Print(fp_log);
  
     //
     // count rate (c/s) function
     //
     FuncPls* func = FuncPls::GenFuncPls(argval->GetFuncName());
     func->InitSet(argval->GetTunit(),
                   Telescope::GetMjdref(argval->GetTelescope()),
                   eph, NULL);
     MirFuncPar* func_par = new MirFuncPar;
     func_par->Load(argval->GetParFile());
     func_par->Print(stdout);

     // HistInfo1d
     HistInfo1d* hist_info = new HistInfo1d;
     hist_info->Load(argval->GetHistInfo());

     // hist (rate function)
     HistDataNerr1d* h1d_func_rate = new HistDataNerr1d;
     h1d_func_rate->Init(hist_info);
     h1d_func_rate->SetByFunc(func, func_par->GetPar());

     // hist (count function)
     HistDataNerr1d* h1d_func_count = new HistDataNerr1d;
     HistData1dOpe::GetScale(h1d_func_rate,
                             hist_info->GetBinWidth(),
                             0.0, h1d_func_count);
     h1d_func_rate->Save(argval->GetOutdir() + "/"
                         + argval->GetOutfileHead() + "_rate.dat",
                         "x,xe,y,ye");
     h1d_func_count->Save(argval->GetOutdir() + "/"
                          + argval->GetOutfileHead() + "_count.dat",
                          "x,xe,y,ye");

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
     delete func_par;
     delete hist_info;
     delete h1d_func_rate;
    delete h1d_func_count;    

    return status;
}

