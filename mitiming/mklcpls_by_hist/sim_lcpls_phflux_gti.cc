#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "mxkw_qdp_tool.h"
#include "mxkw_hist_info_ope.h"

#include "arg_sim_lcpls_phflux_gti.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValSimLcplsPhfluxGti* argval = new ArgValSimLcplsPhfluxGti;
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
     HistInfo1d* hi1d = new HistInfo1d;
     hi1d->Load(argval->GetLcInfo());

     // effective area (graph)
     printf("loading effarea file...\n");
     GraphData2d* g2d_effarea = new GraphData2d;
     g2d_effarea->Load(argval->GetEffareaFile(), "x,y");
     printf("loading effarea file: done.\n");

     // GTI
     Interval* gti = new Interval;
     if("none" == argval->GetGtifile()){
         gti->InitSet(hi1d->GetLo(), hi1d->GetUp());
     } else {
         gti->Load(argval->GetGtifile());
     }
     
     // GTI selection of HistInfo1d
     long nhi1d_sel = 0;
     HistInfo1d** hi1d_sel_arr = NULL;
     Interval* gti_sel = NULL;
     HistInfo1dOpe::GenSelectHi1dArrByInterval(
         hi1d, gti,
         &nhi1d_sel, &hi1d_sel_arr, &gti_sel,
         "exclusive");

     // GTI selection of GraphData2d
     GraphData2d** g2d_effarea_arr = NULL;
     GraphData2dOpe::GenSelectG2dArrByInterval(g2d_effarea,
                                               gti_sel,
                                               &g2d_effarea_arr);


     printf("making function hist ....\n");
     HistData1d** h1d_func_phflux_arr = new HistData1d* [nhi1d_sel];
     HistData1d** h1d_effarea_arr     = new HistData1d* [nhi1d_sel];
     HistData1d** h1d_func_rate_arr   = new HistData1d* [nhi1d_sel];
     HistData1d** h1d_func_count_arr  = new HistData1d* [nhi1d_sel];
     for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
         h1d_func_phflux_arr[ihi1d] = new HistData1d;
         h1d_effarea_arr[ihi1d]     = new HistData1d;
         h1d_func_rate_arr[ihi1d]   = new HistData1d;
         h1d_func_count_arr[ihi1d]  = new HistData1d;
     }
     for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
         // hist (phflux function)
         h1d_func_phflux_arr[ihi1d]->Init(hi1d_sel_arr[ihi1d]);
         h1d_func_phflux_arr[ihi1d]->SetByFunc(func, NULL);

         // hist (effarea file)
         h1d_effarea_arr[ihi1d]->Init(hi1d_sel_arr[ihi1d]);
         h1d_effarea_arr[ihi1d]->SetByGraphData2d(g2d_effarea_arr[ihi1d]);

         // hist (rate function)
         h1d_func_rate_arr[ihi1d]->Mul(h1d_func_phflux_arr[ihi1d],
                                       h1d_effarea_arr[ihi1d]);
         
         // hist (count function)
         h1d_func_count_arr[ihi1d]->Scale(h1d_func_rate_arr[ihi1d],
                                          h1d_func_rate_arr[ihi1d]->GetBinWidth(),
                                          0.0);
     }

     printf("making function hist: done.\n");
     
     if("bin" == argval->GetSimMode()){
         HistDataSerr1d** h1d_bin_count_arr        = new HistDataSerr1d* [nhi1d_sel];
         HistDataSerr1d** h1d_bin_count_rate_arr   = new HistDataSerr1d* [nhi1d_sel];
         HistDataSerr1d** h1d_bin_count_phflux_arr = new HistDataSerr1d* [nhi1d_sel];
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             h1d_bin_count_arr[ihi1d]        = new HistDataSerr1d;
             h1d_bin_count_rate_arr[ihi1d]   = new HistDataSerr1d;
             h1d_bin_count_phflux_arr[ihi1d] = new HistDataSerr1d;
         }
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             // hist (count function random)
             h1d_bin_count_arr[ihi1d]->Init(hi1d_sel_arr[ihi1d]);
             h1d_bin_count_arr[ihi1d]->FillRandom(h1d_func_count_arr[ihi1d],
                                                  argval->GetRandSeed());
             char outdat_bin_count[kLineSize];
             sprintf(outdat_bin_count, "%s/%s_bin_count_%4.4d.dat",
                     argval->GetOutdir().c_str(),
                     argval->GetOutfileHead().c_str(),
                     (int) ihi1d);
             h1d_bin_count_arr[ihi1d]->Save(outdat_bin_count, "x,xe,y,ye");
             
             // hist (rate)
             h1d_bin_count_rate_arr[ihi1d]->Scale(h1d_bin_count_arr[ihi1d],
                                                  1./h1d_bin_count_arr[ihi1d]->GetBinWidth(),
                                                  0.0);
             // hist (phflux)
             vector<long> index_bad_vec;
             h1d_bin_count_phflux_arr[ihi1d]->Div(h1d_bin_count_rate_arr[ihi1d],
                                                  h1d_effarea_arr[ihi1d],
                                                  &index_bad_vec);
             char outdat_bin_phflux[kLineSize];
             sprintf(outdat_bin_phflux, "%s/%s_bin_phflux_%4.4d.dat",
                     argval->GetOutdir().c_str(),
                     argval->GetOutfileHead().c_str(),
                     (int) ihi1d);
             h1d_bin_count_phflux_arr[ihi1d]->Save(outdat_bin_phflux, "x,xe,y,ye");
         }

         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             delete h1d_bin_count_arr[ihi1d];
             delete h1d_bin_count_rate_arr[ihi1d];
             delete h1d_bin_count_phflux_arr[ihi1d];
         }
         delete [] h1d_bin_count_arr;
         delete [] h1d_bin_count_rate_arr;
         delete [] h1d_bin_count_phflux_arr;
             
     } else if("evt" == argval->GetSimMode()){
         printf("simulation by events ...\n");
         
         DataArray1d** data1d_evt_arr = new DataArray1d* [nhi1d_sel];
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             data1d_evt_arr[ihi1d] = h1d_func_count_arr[ihi1d]->GenRandomEvt(argval->GetRandSeed());

             //char outdat_data1d_evt[kLineSize];
             //sprintf(outdat_data1d_evt, "%s/%s_evt_%4.4d.dat",
             //        argval->GetOutdir().c_str(),
             //        argval->GetOutfileHead().c_str(),
             //        (int) ihi1d);
             //data1d_evt_arr[ihi1d]->Save(outdat_data1d_evt, 0);
         }

         HistDataSerr1d** h1d_evt_fill_arr        = new HistDataSerr1d* [nhi1d_sel];
         HistDataSerr1d** h1d_evt_fill_rate_arr   = new HistDataSerr1d* [nhi1d_sel];
         HistDataSerr1d** h1d_evt_fill_phflux_arr = new HistDataSerr1d* [nhi1d_sel];
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             h1d_evt_fill_arr[ihi1d]        = new HistDataSerr1d;
             h1d_evt_fill_rate_arr[ihi1d]   = new HistDataSerr1d;
             h1d_evt_fill_phflux_arr[ihi1d] = new HistDataSerr1d;
         }

         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             h1d_evt_fill_arr[ihi1d]->Init(hi1d_sel_arr[ihi1d]);
             for(long idata = 0; idata < data1d_evt_arr[ihi1d]->GetNdata(); idata++){
                 h1d_evt_fill_arr[ihi1d]->Fill(data1d_evt_arr[ihi1d]->GetValElm(idata));
             }
             //char outdat_evt_fill[kLineSize];
             //sprintf(outdat_evt_fill, "%s/%s_evt_fill_count_%4.4d.dat",
             //        argval->GetOutdir().c_str(),
             //        argval->GetOutfileHead().c_str(),
             //        (int) ihi1d);
             //h1d_evt_fill_arr[ihi1d]->Save(outdat_evt_fill, "x,xe,y,ye");
             
             // hist (rate)
             h1d_evt_fill_rate_arr[ihi1d]->Scale(h1d_evt_fill_arr[ihi1d],
                                                 1./h1d_evt_fill_arr[ihi1d]->GetBinWidth(),
                                                 0.0);
             // hist (phflux)
             vector<long> index_bad_vec;
             h1d_evt_fill_phflux_arr[ihi1d]->Div(h1d_evt_fill_rate_arr[ihi1d],
                                                 h1d_effarea_arr[ihi1d], &index_bad_vec);

             //char outdat_evt_fill_phflux[kLineSize];
             //sprintf(outdat_evt_fill_phflux, "%s/%s_evt_fill_phflux_%4.4d.dat",
             //        argval->GetOutdir().c_str(),
             //        argval->GetOutfileHead().c_str(),
             //        (int) ihi1d);
             //h1d_evt_fill_phflux_arr[ihi1d]->Save(outdat_evt_fill_phflux, "x,xe,y,ye");
         }

         // save event
         char outdat_data1d_evt[kLineSize];
         sprintf(outdat_data1d_evt, "%s/%s_evt.dat",
                 argval->GetOutdir().c_str(),
                 argval->GetOutfileHead().c_str());
         FILE* fp = fopen(outdat_data1d_evt, "w");
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             data1d_evt_arr[ihi1d]->PrintData(fp, 0, 0.0);
         }
         fclose(fp);

         // save evt_fill_phflux
         char outdat_evt_fill_phflux[kLineSize];
         sprintf(outdat_evt_fill_phflux, "%s/%s_evt_fill_phflux.dat",
                argval->GetOutdir().c_str(),
                 argval->GetOutfileHead().c_str());
         fp = fopen(outdat_evt_fill_phflux, "w");
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){
             h1d_evt_fill_phflux_arr[ihi1d]->PrintData(fp, "x,xe,y,ye",
                                                       hi1d->GetLo());
         }
         fclose(fp);
         
         for(long ihi1d = 0; ihi1d < nhi1d_sel; ihi1d ++){         
             delete h1d_evt_fill_arr[ihi1d];
             delete h1d_evt_fill_rate_arr[ihi1d];
             delete h1d_evt_fill_phflux_arr[ihi1d];
             delete data1d_evt_arr[ihi1d];
         }
         delete [] h1d_evt_fill_arr;
         delete [] h1d_evt_fill_rate_arr;
         delete [] h1d_evt_fill_phflux_arr;
         delete [] data1d_evt_arr;

         printf("simulation by events: done.\n");         
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
//     delete hist_info;
//     delete h1d_func_rate;
//     delete h1d_func_count;
     

     return status;
}

