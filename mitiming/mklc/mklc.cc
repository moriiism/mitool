#include "mi_iolib.h"
#include "mir_func_par.h"
#include "mir_hist1d_serr.h"
#include "mit_eph.h"
#include "mit_telescope.h"
#include "mit_binary_orb.h"
#include "mit_func_pls.h"
#include "mit_folding.h"
#include "mir_qdp_tool.h"

#include "arg_mklc.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValMklc* argval = new ArgValMklc;
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

    // HistInfo1d for display
    HistInfo1d* hist_info_disp = new HistInfo1d;
    hist_info_disp->Load(argval->GetHistInfoDisp());

    // HistInfo1d for simulation
    HistInfo1d* hist_info_sim = new HistInfo1d;
    hist_info_sim->InitSetByWidth(hist_info_disp->GetLo(),
                                  hist_info_disp->GetUp(),
                                  argval->GetDeltaTimeSim(),
                                  "ceil");

    // hist (rate function)
    HistData1d* h1d_func_rate = new HistDataNerr1d;
    h1d_func_rate->Init(hist_info_sim);
    h1d_func_rate->SetByFunc(func, func_par->GetPar());

    // hist (count function)
    HistDataNerr1d* h1d_func_count = new HistDataNerr1d;
    HistData1dOpe::GetScale(h1d_func_rate,
                            hist_info_sim->GetBinWidth(), 0.0,
                            h1d_func_count);

    DataArray1d* data1d_evt
        = h1d_func_count->GenRandomEvt(argval->GetRandSeed());
    data1d_evt->Save(argval->GetOutdir() +
                     "/" + argval->GetOutfileHead() + "_evt.dat", 0, 0.0);

    HistDataSerr1d* h1d_evt_fill = new HistDataSerr1d;
    h1d_evt_fill->Init(hist_info_disp);
    for(long idata = 0; idata < data1d_evt->GetNdata(); idata++){
        h1d_evt_fill->Fill(data1d_evt->GetValElm(idata));
    }
    h1d_evt_fill->Save(argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_evt_fill_count.dat",
                       "x,xe,y,ye");

    HistDataSerr1d* h1d_evt_fill_rate = new HistDataSerr1d;
    HistData1dOpe::GetScale(h1d_evt_fill,
                            1./hist_info_disp->GetBinWidth(), 0.0,
                            h1d_evt_fill_rate);

    h1d_evt_fill_rate->Save(argval->GetOutdir() + "/"
                            + argval->GetOutfileHead() + "_evt_fill_rate.dat",
                            "x,xe,y,ye");
    
//    MirQdpTool::MkQdpDiff3(h1d_evt_fill_rate, func, func_par->GetPar(),
//                           argval->GetOutdir(),
//                           argval->GetOutfileHead() + "_evt_fill_rate");
    
    //
    // folding to check the generated light curve
    //
    int nphase = 32;
    HistDataSerr1d* h1d_pulse_evt
        = MitFolding::GenFolding(
            data1d_evt,
            Telescope::GetMjdref(argval->GetTelescope()),
            argval->GetTunit(),
            eph, nphase);
    MirQdpTool::MkQdp(h1d_pulse_evt,
                       argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_evt_fold.qdp",
                       "x,xe,y,ye");
    delete h1d_pulse_evt;
    
    delete h1d_evt_fill;
    delete h1d_evt_fill_rate;        
    delete data1d_evt;

    //
    // cleaning
    //
    
    fclose(fp_log);
    delete argval;
    delete eph;
    delete func;
    delete func_par;
    delete hist_info_disp;
    delete hist_info_sim;
    delete h1d_func_rate;
    delete h1d_func_count;

    return status;
}

