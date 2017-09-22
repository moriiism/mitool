#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "mxkw_qdp_tool.h"

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
     // photon flux (c/s/cm2) function
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

     // hist (phflux function)
     HistData1d* h1d_func_phflux = new HistData1d;
     h1d_func_phflux->Init(hist_info);
     h1d_func_phflux->SetByFunc(func, NULL);

     // hist (effarea file)
     HistData1d* h1d_effarea = new HistData1d;
     h1d_effarea->Init(hist_info);
     GraphData2d* g2d_effarea = new GraphData2d;
     g2d_effarea->Load(argval->GetEffareaFile(), "x,y");
     h1d_effarea->SetByGraphData2d(g2d_effarea);

     // hist (rate function)
     HistData1d* h1d_func_rate = new HistData1d;
     h1d_func_rate->Mul(h1d_func_phflux, h1d_effarea);

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

         // hist (phflux)
         HistDataSerr1d* h1d_bin_count_phflux = new HistDataSerr1d;
         vector<long> index_bad_vec;
         h1d_bin_count_phflux->Div(h1d_bin_count_rate, h1d_effarea, &index_bad_vec);
         h1d_bin_count_phflux->Save(argval->GetOutdir() + "/"
                                    + argval->GetOutfileHead() + "_bin_phflux.dat",
                                    "x,xe,y,ye");         
         //MxkwQdpTool::MkQdpDiff3(h1d_bin_count_phflux, func, func_par,
         //                        argval->GetOutdir(), argval->GetOutfileHead() + "_bin_phflux");

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
         h1d_evt_fill_rate->Scale(h1d_evt_fill,
                                  1./h1d_evt_fill->GetBinWidth(),
                                  0.0);
         HistDataSerr1d* h1d_evt_fill_phflux = new HistDataSerr1d;
         vector<long> index_bad_vec;
         h1d_evt_fill_phflux->Div(h1d_evt_fill_rate, h1d_effarea, &index_bad_vec);
         h1d_evt_fill_phflux->Save(argval->GetOutdir() + "/"
                                   + argval->GetOutfileHead() + "_evt_fill_phflux.dat",
                                   "x,xe,y,ye");   
         //MxkwQdpTool::MkQdpDiff3(h1d_evt_fill_phflux, func, func_par,
         //                        argval->GetOutdir(),
         //                        argval->GetOutfileHead() + "_evt_fill_phflux");

         delete h1d_evt_fill;
         delete h1d_evt_fill_rate;
         delete h1d_evt_fill_phflux;
         delete data1d_evt;
     } else {
         MPrintErr("bad sim mode");
         abort();
     }

  
     //
     // cleaning
     //
  
     fclose(fp_log);
     delete argval;
     delete eph;
     delete func;
     delete hist_info;
     delete h1d_func_rate;
     delete h1d_func_count;
     

     return status;
}

