#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "mxkw_qdp_tool.h"

#include "arg_sim_lcpls_rate.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValSimLcplsRate* argval = new ArgValSimLcplsRate;
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
     MxkwFuncPar* func_par = new MxkwFuncPar;
     func_par->Load(argval->GetParFile());
     func_par->Print(stdout);

     // HistInfo1d
     HistInfo1d* hist_info = new HistInfo1d;
     hist_info->Load(argval->GetHistInfo());

     // hist (rate function)
     HistData1d* h1d_func_rate = new HistData1d;
     h1d_func_rate->Init(hist_info);
     h1d_func_rate->SetByFunc(func, func_par->GetPar());

     // hist (count function)
     HistData1d* h1d_func_count = new HistData1d;
     h1d_func_count->Scale(h1d_func_rate,
                           h1d_func_rate->GetBinWidth(),
                           0.0);

     if("bin" == argval->GetSimMode()){
         // hist (count function random)
         HistDataSerr1d* h1d_bin_count = new HistDataSerr1d;
         h1d_bin_count->Init(hist_info);
         h1d_bin_count->FillRandom(h1d_func_count, argval->GetRandSeed());
         h1d_bin_count->Save(argval->GetOutdir() + "/"
                             + argval->GetOutfileHead() + "_bin_count.dat",
                             "x,xe,y,ye");
         // hist (rate)
         HistDataSerr1d* h1d_bin_count_rate = new HistDataSerr1d;
         h1d_bin_count_rate->Scale(h1d_bin_count,
                                   1./h1d_bin_count->GetBinWidth(),
                                   0.0);
         MxkwQdpTool::MkQdpDiff3(h1d_bin_count_rate, func, func_par->GetPar(),
                                 argval->GetNpointFunc(),
                                 argval->GetOutdir(), argval->GetOutfileHead() + "_bin_rate");
         h1d_bin_count_rate->Save(argval->GetOutdir() + "/"
                                  + argval->GetOutfileHead() + "_bin_rate.dat",
                                  "x,xe,y,ye");
         delete h1d_bin_count;
         delete h1d_bin_count_rate;        
     } else if("evt" == argval->GetSimMode()){
         DataArray1d* data1d_evt = h1d_func_count->GenRandomEvt(argval->GetRandSeed());
         data1d_evt->Save(argval->GetOutdir() + "/"
                          + argval->GetOutfileHead() + "_evt.dat", 0, 0.0);

         HistDataSerr1d* h1d_evt_fill = new HistDataSerr1d;
         h1d_evt_fill->Init(hist_info);
         for(long idata = 0; idata < data1d_evt->GetNdata(); idata++){
             h1d_evt_fill->Fill(data1d_evt->GetValElm(idata));
         }
         h1d_evt_fill->Save(argval->GetOutdir() + "/"
                            + argval->GetOutfileHead() + "_evt_fill_count.dat",
                            "x,xe,y,ye");

         HistDataSerr1d* h1d_evt_fill_rate = new HistDataSerr1d;
         h1d_evt_fill_rate->Scale(h1d_evt_fill, 1./h1d_evt_fill->GetBinWidth(), 0.0);
         h1d_evt_fill_rate->Save(argval->GetOutdir() + "/"
                                 + argval->GetOutfileHead() + "_evt_fill_rate.dat",
                                 "x,xe,y,ye");
    
         MxkwQdpTool::MkQdpDiff3(h1d_evt_fill_rate, func, func_par->GetPar(),
                                 argval->GetNpointFunc(),
                                 argval->GetOutdir(),
                                 argval->GetOutfileHead() + "_evt_fill_rate");
         delete h1d_evt_fill;
         delete h1d_evt_fill_rate;        
         delete data1d_evt;
     } else {
         MPrintErr("bad sim mode");
         abort();
     }

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

