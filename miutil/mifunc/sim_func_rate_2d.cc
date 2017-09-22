#include "mi_iolib.h"
#include "mifc_gen.h"
#include "mir_hist2d_serr.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_sim_func_rate_2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValSimFuncRate2d* argval = new ArgValSimFuncRate2d;
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

    
    // HistInfo2d for simulation
    HistInfo2d* hi2d_sim = new HistInfo2d;
    hi2d_sim->Load(argval->GetHistInfoSim());
    
    // hist (rate function)
    HistData2d* hd2d_func_rate = new HistData2d;
    hd2d_func_rate->Init(hi2d_sim);
    hd2d_func_rate->SetByFunc(func, func_par->GetPar());

    // hist (count function)
    HistData2d* hd2d_func_count = new HistData2d;
    hd2d_func_count->Scale(hd2d_func_rate, hi2d_sim->GetBinArea(), 0.0);

    // sim_mode:
    //   bin: calculate binned value directly
    //   evt: calculate only event data
    //   evt+bin: calculate event data and make binned value from the event data,
    //            So, the binned values are consistent with event data
    
    string add_mode = "amean";
    string error_mode = "gauss";
    if("bin" == argval->GetSimMode()){
        if("none" != argval->GetHistInfoOut()){
            char msg[kLineSize];
            sprintf(msg, "Since sim_mode is bin, hist_info_out must be none.");
            MPrintErr(msg);
            abort();
        }
        
        // hist (count function random)
        HistDataSerr2d* hd2d_sim_count = new HistDataSerr2d;
        hd2d_sim_count->Init(hi2d_sim);
        hd2d_sim_count->FillRandom(hd2d_func_count, argval->GetRandSeed());
        hd2d_sim_count->Save(argval->GetOutdir() + "/"
                             + argval->GetOutfileHead() + "_bin_count.dat",
                             "x,xe,y,ye,z,ze");

        // hist (rate)
        HistDataSerr2d* hd2d_sim_count_rate = new HistDataSerr2d;
        hd2d_sim_count_rate->Scale(hd2d_sim_count, 1./hi2d_sim->GetBinArea(), 0.0);

        MirQdpTool::MkQdpDiffProj(hd2d_sim_count_rate, func, func_par->GetPar(),
                                   argval->GetOutdir(), argval->GetOutfileHead() + "_bin_rate",
                                   add_mode, error_mode);
        hd2d_sim_count_rate->Save(argval->GetOutdir() + "/"
                                  + argval->GetOutfileHead() + "_bin_rate.dat",
                                  "x,xe,y,ye,z,ze");
        delete hd2d_sim_count;
        delete hd2d_sim_count_rate;

    } else if("evt" == argval->GetSimMode()){

        GraphData2d* gd2d_evt = hd2d_func_count->GenRandomEvt(argval->GetRandSeed());
        gd2d_evt->Save(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt.dat",
                          "x,y");
        delete gd2d_evt;
        
    } else if("evt+bin" == argval->GetSimMode()){

        // HistInfo2d for output
        HistInfo2d* hi2d_out = new HistInfo2d;
        if("none" == argval->GetHistInfoOut()){
            hi2d_out->Copy(hi2d_sim);
        } else {
            hi2d_out->Load(argval->GetHistInfoOut());
        }
        GraphData2d* gd2d_evt = hd2d_func_count->GenRandomEvt(argval->GetRandSeed());
        gd2d_evt->Save(argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_evt.dat",
                       "x,y");

        HistDataSerr2d* hd2d_evt_fill = new HistDataSerr2d;
        hd2d_evt_fill->Init(hi2d_out);
        for(long idata = 0; idata < gd2d_evt->GetNdata(); idata++){
            hd2d_evt_fill->Fill(gd2d_evt->GetXvalElm(idata),
                                gd2d_evt->GetOvalElm(idata));
        }
        hd2d_evt_fill->Save(argval->GetOutdir() + "/"
                            + argval->GetOutfileHead() + "_evt_fill_count.dat",
                            "x,xe,y,ye,z,ze");

        HistDataSerr2d* hd2d_evt_fill_rate = new HistDataSerr2d;
        hd2d_evt_fill_rate->Scale(hd2d_evt_fill, 1./hi2d_out->GetBinArea(), 0.0);

        hd2d_evt_fill_rate->Save(argval->GetOutdir() + "/"
                                 + argval->GetOutfileHead() + "_evt_fill_rate.dat",
                                 "x,xe,y,ye,z,ze");

        MirQdpTool::MkQdpDiffProj(hd2d_evt_fill_rate, func, func_par->GetPar(),
                                   argval->GetOutdir(), argval->GetOutfileHead() + "_evt_fill_rate",
                                   add_mode, error_mode);
        delete hi2d_out;
        delete gd2d_evt;
        delete hd2d_evt_fill;
        delete hd2d_evt_fill_rate;

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
    delete hi2d_sim;
    delete hd2d_func_rate;
    delete hd2d_func_count;
    
    return status;
}
