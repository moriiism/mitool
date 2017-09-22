#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_func_maxiobs.h"
#include "mxkw_timing_folding.h"
#include "mxkw_timing_genlc.h"

#include "arg.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMklcMaxi* argval = new ArgValMklcMaxi;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = fopen((argval->GetOutdir() + "/" + argval->GetProgname() + ".log").c_str(), "w");
    argval->Print(fp_log);
    
    Ephemeris* eph = new Ephemeris;
    eph->Load(argval->GetEphfile());
    eph->Print(stdout);
    eph->Print(fp_log);
    
    Telescope* tel = new Telescope;
    tel->Set(argval->GetTelescope());
    printf("%s: mjdref = %f\n", argval->GetProgname().c_str(), tel->GetMjdref());
    fprintf(fp_log, "%s: mjdref = %f\n", argval->GetProgname().c_str(), tel->GetMjdref());
    

    //
    // flux (c/s/cm^2) function
    //
    FuncPls* func = FuncPls::GenFuncPls(argval->GetFuncName());
    func->Set(argval->GetLcTunit(), tel->GetMjdref(), eph);

    MxkwFuncPar* func_par = new MxkwFuncPar;
    func_par->Load(argval->GetFuncParFile());
    func_par->Print();
    
    MaxiObsFunc* func_maxiobs = new MaxiObsFunc;
    func_maxiobs->Init(func);

    double time_lo = TimeConv::MjdToTime(argval->GetTimeMjdSt(), tel->GetMjdref(), argval->GetLcTunit());
    double time_up = TimeConv::MjdToTime(argval->GetTimeMjdEd(), tel->GetMjdref(), argval->GetLcTunit());
    func_maxiobs->MkQdp(func_par, time_lo, time_up,
                        argval->GetOutdir() + "/" + argval->GetProgname() + "_func_tmp.qdp");

    long nbin_hist = MxkwMath::GetNbin(time_lo, time_up, argval->GetTbinfwidth(), "ceil");
    printf("nbin_hist = %ld\n", nbin_hist);


//    // hist_rate without error
//    HistData1d* h1d_rate = new HistData1d;
//    h1d_rate->CreateByFunc(func_maxiobs, func_par->GetPar(),
//                           time_lo, time_up, nbin_hist);
//    h1d_rate->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_func_rate.qdp");
//    h1d_rate->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_func_rate_offset.qdp", time_lo);
    
    // hist_count without error
    HistData1d* h1d_count = MxkwGenLc::GenH1dCountByFuncRate(func_maxiobs, func_par->GetPar(),
                                                             time_lo, time_up, nbin_hist);
    h1d_count->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_func_count.qdp");
    h1d_count->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_func_count_offset.qdp", time_lo);
    

//    // hist_count with poisson error
    string format = "x,xe,y,ye";
//    HistDataSerr1d* h1d_serr_count = MxkwGenLc::GenH1dSerrRandomCountByFuncRate(func_maxiobs, func_par->GetPar(),
//                                                                                time_lo, time_up, nbin_hist);
//    h1d_serr_count->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_poiss_count.qdp", format);
//    h1d_serr_count->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_poiss_count_offset.qdp", format, time_lo);
//
//    // hist_rate with poisson error
//    HistDataSerr1d* h1d_serr_rate = MxkwGenLc::GenH1dSerrRandomRateByFuncRate(func_maxiobs, func_par->GetPar(),
//                                                                              time_lo, time_up, nbin_hist);
//    h1d_serr_rate->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_poiss_rate.qdp", format);
//    h1d_serr_rate->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_poiss_rate_offset.qdp", format, time_lo);
//
    
    // gen random event
    DataArray1d* data_arr = h1d_count->GenRandomEvt(argval->GetSeed());
    data_arr->Save(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt.dat", 0);
    

    //
    // folding to check the generated light curve
    //
    
    int nphase = 10;
//    HistDataSerr1d* h1d_pulse_binlc = MxkwFolding::GenFoldingBinCenter(h1d_serr_count,
//                                                                       tel->GetMjdref(), argval->GetLcTunit(),
//                                                                       eph, nphase);
//    h1d_pulse_binlc->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_poiss_fold.qdp", format);
//

    HistDataSerr1d* h1d_pulse_evt = MxkwFolding::GenFolding(data_arr,
                                                            tel->GetMjdref(), argval->GetLcTunit(),
                                                            eph, nphase);
    h1d_pulse_evt->MkQdp(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt_fold.qdp", format);


    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;
    delete eph;
    delete tel;
    delete func;
    delete func_par;
    delete func_maxiobs;
//    delete h1d_rate;
    delete h1d_count;
//    delete h1d_serr_count;
//    delete h1d_serr_rate;
    delete data_arr;
//    delete h1d_pulse_binlc;
    delete h1d_pulse_evt;

    return status;
}

