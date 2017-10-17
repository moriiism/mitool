#include "mi_iolib.h"
#include "mifc_gen.h"
#include "mir_hist1d_serr.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_sim_func_rate_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValSimFuncRate1d* argval = new ArgValSimFuncRate1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
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
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);
    MiIolib::Printf2(fp_log, "%s: --- START ---\n",
                       argval->GetProgname().c_str());
    
    // func: count rate function
    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);

    // HistInfo1d for simulation
    HistInfo1d* hi1d_sim = new HistInfo1d;
    hi1d_sim->Load(argval->GetHistInfoSim());
    
    // hist (rate function)
    HistData1d* hd1d_func_rate = new HistDataNerr1d;
    hd1d_func_rate->Init(hi1d_sim);
    hd1d_func_rate->SetByFunc(func, func_par->GetPar());

    // hist (count function)
    HistDataNerr1d* hd1d_func_count = new HistDataNerr1d;
    HistData1dOpe::GetScale(hd1d_func_rate, hi1d_sim->GetBinWidth(), 0.0,
                            hd1d_func_count);

    // sim_mode:
    //   bin: calculate binned value directly
    //   evt: calculate only event data
    //   evt+bin: calculate event data and make binned value from the event data,
    //            So, the binned values are consistent with event data
    
    if("bin" == argval->GetSimMode()){
        if("none" != argval->GetHistInfoOut()){
            char msg[kLineSize];
            sprintf(msg, "Since sim_mode is bin, hist_info_out must be none.");
            MPrintErr(msg);
            abort();
        }
        
        // hist (count function random)
        HistDataSerr1d* hd1d_sim_count = new HistDataSerr1d;
        hd1d_sim_count->Init(hi1d_sim);
        hd1d_sim_count->FillRandom(hd1d_func_count, argval->GetRandSeed());
        hd1d_sim_count->Save(argval->GetOutdir() + "/"
                             + argval->GetOutfileHead() + "_bin_count.dat",
                             "x,xe,y,ye");
        // hist (rate)
        HistDataSerr1d* hd1d_sim_count_rate = new HistDataSerr1d;
        HistData1dOpe::GetScale(hd1d_sim_count, 1./hi1d_sim->GetBinWidth(), 0.0,
                                hd1d_sim_count_rate);

        MirQdpTool::MkQdpDiff3Serr(hd1d_sim_count_rate, func, func_par->GetPar(),
                                   argval->GetNpointFunc(),
                                   argval->GetOutdir(), argval->GetOutfileHead() + "_bin_rate");
        hd1d_sim_count_rate->Save(argval->GetOutdir() + "/"
                                  + argval->GetOutfileHead() + "_bin_rate.dat",
                                  "x,xe,y,ye");
        delete hd1d_sim_count;
        delete hd1d_sim_count_rate;

    } else if("evt" == argval->GetSimMode()){
        
        DataArray1d* da1d_evt = hd1d_func_count->GenRandomEvt(argval->GetRandSeed());
        da1d_evt->Save(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt.dat", 0, 0.0);
        delete da1d_evt;

    } else if("evt+bin" == argval->GetSimMode()){

        // HistInfo1d for output
        HistInfo1d* hi1d_out = new HistInfo1d;
        if("none" == argval->GetHistInfoOut()){
            hi1d_out->Copy(hi1d_sim);
        } else {
            hi1d_out->Load(argval->GetHistInfoOut());
        }
        DataArray1d* da1d_evt = hd1d_func_count->GenRandomEvt(argval->GetRandSeed());
        da1d_evt->Save(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt.dat", 0, 0.0);

        HistDataSerr1d* hd1d_evt_fill = new HistDataSerr1d;
        hd1d_evt_fill->Init(hi1d_out);
        for(long idata = 0; idata < da1d_evt->GetNdata(); idata++){
            hd1d_evt_fill->Fill(da1d_evt->GetValElm(idata));
        }
        hd1d_evt_fill->Save(argval->GetOutdir() + "/"
                            + argval->GetOutfileHead() + "_evt_fill_count.dat",
                            "x,xe,y,ye");

        HistDataSerr1d* hd1d_evt_fill_rate = new HistDataSerr1d;
        HistData1dOpe::GetScale(hd1d_evt_fill, 1./hi1d_out->GetBinWidth(), 0.0,
                                hd1d_evt_fill_rate);
        
        hd1d_evt_fill_rate->Save(argval->GetOutdir() + "/"
                                 + argval->GetOutfileHead() + "_evt_fill_rate.dat",
                                 "x,xe,y,ye");
    
        MirQdpTool::MkQdpDiff3Serr(hd1d_evt_fill_rate, func, func_par->GetPar(),
                                   argval->GetNpointFunc(),
                                   argval->GetOutdir(),
                                   argval->GetOutfileHead() + "_evt_fill_rate");
        delete hi1d_out;
        delete da1d_evt;
        delete hd1d_evt_fill;
        delete hd1d_evt_fill_rate;        

    } else {
        MPrintErr("bad sim mode");
        abort();
    }

    MiIolib::Printf2(fp_log, "%s: === END ===\n",
                       argval->GetProgname().c_str());
    fclose(fp_log);
    delete argval;
    delete func;
    delete func_par;
    delete hi1d_sim;
    delete hd1d_func_rate;
    delete hd1d_func_count;
    
    return status;
}
