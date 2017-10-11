#include "mi_iolib.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mir_func_par.h"
#include "mit_telescope.h"
#include "mit_func_pls.h"
#include "mit_folding.h"
#include "mir_qdp_tool.h"

#include "arg_sim_lcpls_phflux.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValSimLcplsPhflux* argval = new ArgValSimLcplsPhflux;
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
     // photon flux (c/s/cm2) function
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

     // hist (phflux function)
     HistDataNerr1d* h1d_func_phflux = new HistDataNerr1d;
     h1d_func_phflux->Init(hist_info);
     h1d_func_phflux->SetByFunc(func, func_par->GetPar());

     // hist (effarea file)
     GraphDataNerr2d* g2d_effarea = new GraphDataNerr2d;
     g2d_effarea->Load(argval->GetEffareaFile(), "x,xe,y,ye");
     HistDataNerr1d* h1d_effarea = new HistDataNerr1d;
     HistData1dOpe::FillByGd2d(hist_info, g2d_effarea, h1d_effarea);

     // hist (rate function)
     HistDataNerr1d* h1d_func_rate = new HistDataNerr1d;
     HistData1dOpe::GetMul(h1d_func_phflux, h1d_effarea,
                           h1d_func_rate);
     // hist (count function)
     HistDataNerr1d* h1d_func_count = new HistDataNerr1d;
     HistData1dOpe::GetScale(h1d_func_rate,
                             h1d_func_rate->GetHi1d()->GetBinWidth(),
                             0.0, h1d_func_count);
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
         HistData1dOpe::GetScale(h1d_bin_count,
                                 1./h1d_bin_count->GetHi1d()->GetBinWidth(),
                                 0.0, h1d_bin_count_rate);
         // hist (phflux)
         HistDataSerr1d* h1d_bin_count_phflux = new HistDataSerr1d;
         vector<long> index_bad_vec;
         HistDataNerr1d* hd1d_mask_sel = new HistDataNerr1d;
         HistData1dOpe::GetDiv(h1d_bin_count_rate, h1d_effarea,
                               hd1d_mask_sel, h1d_bin_count_phflux);
         h1d_bin_count_phflux->Save(argval->GetOutdir() + "/"
                                    + argval->GetOutfileHead() + "_bin_phflux.dat",
                                    "x,xe,y,ye");         
         MirQdpTool::MkQdpDiff3Serr(h1d_bin_count_phflux, func, func_par->GetPar(),
                                    argval->GetNpointFunc(),
                                    argval->GetOutdir(),
                                    argval->GetOutfileHead() + "_bin_phflux");

         delete h1d_bin_count;
         delete h1d_bin_count_rate;
         delete h1d_bin_count_phflux;
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
         HistData1dOpe::GetScale(h1d_evt_fill,
                                 1./h1d_evt_fill->GetHi1d()->GetBinWidth(),
                                 0.0, h1d_evt_fill_rate);
         HistDataSerr1d* h1d_evt_fill_phflux = new HistDataSerr1d;
         vector<long> index_bad_vec;
         HistDataNerr1d* hd1d_mask_sel = new HistDataNerr1d;
         HistData1dOpe::GetDiv(h1d_evt_fill_rate, h1d_effarea,
                               hd1d_mask_sel, h1d_evt_fill_phflux);
         h1d_evt_fill_phflux->Save(argval->GetOutdir() + "/"
                                   + argval->GetOutfileHead() + "_evt_fill_phflux.dat",
                                   "x,xe,y,ye");   
         MirQdpTool::MkQdpDiff3Serr(h1d_evt_fill_phflux, func, func_par->GetPar(),
                                    argval->GetNpointFunc(),
                                    argval->GetOutdir(),
                                    argval->GetOutfileHead() + "_evt_fill_phflux");

         delete h1d_evt_fill;
         delete h1d_evt_fill_rate;
         delete h1d_evt_fill_phflux;
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

