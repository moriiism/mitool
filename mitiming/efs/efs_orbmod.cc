#include "mxkw_iolib.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"

#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_folding.h"

#include "sub.h"
#include "arg_efs_orbmod.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValEfsOrbmod* argval = new ArgValEfsOrbmod;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");


    MxkwRootTool* root_tool = new MxkwRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());
    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;
    if("x" == argval->GetFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetFile());
        data_arr->Sort();
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetFile(), argval->GetFormat());
        g2d->Sort();
    }

    MxkwSearchPar* search_par = new MxkwSearchPar;
    search_par->Load(argval->GetSearchDat());
    search_par->Print(stdout);

    Ephemeris* eph_best = NULL;
    HistDataSerr1d* h1d_pls_best = NULL;
    if(2 == search_par->GetNpar()){
        HistData2d* h2d_chi2 = NULL;
        HistData1d** h1d_chi2_arr = NULL;
        if("x" == argval->GetFormat()){
            GenEfsNuOrbAmp(data_arr, Telescope::GetMjdref(argval->GetTelescope()),
                           argval->GetTunit(),
                           search_par->GetNbinElm(0), search_par->GetLoElm(0),
                           search_par->GetUpElm(0),
                           search_par->GetNbinElm(1), search_par->GetLoElm(1),
                           search_par->GetUpElm(1),
                           argval->GetEpochMjd(), argval->GetNbin(),
                           &h2d_chi2, &h1d_chi2_arr,
                           &eph_best, &h1d_pls_best);
        } else {
//            GenEfsNuOrbAmp(g2d, Telescope::GetMjdref(argval->GetTelescope()),
//                           argval->GetTunit(),
//                           search_par->GetNstepElm(0), search_par->GetLowElm(0),
//                           search_par->GetUpElm(0),
//                           search_par->GetNstepElm(1), search_par->GetLowElm(1),
//                           search_par->GetUpElm(1),
//                           argval->GetEpochMjd(), argval->GetNbin(),
//                           &h2d_chi2, &h1d_chi2_arr,
//                           &eph_best, &h1d_pls_best);
        }
        h2d_chi2->MkTH2Fig(argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_chi2.png",
                           root_tool);
        MxkwQdpTool::MkQdpNhist(h1d_chi2_arr, search_par->GetNbinElm(1),
                                argval->GetOutdir() + "/"
                                + argval->GetOutfileHead() + "_nhist_chi2.qdp",
                                0.0);
        delete h2d_chi2;
        for(int inudot = 0; inudot < search_par->GetNbinElm(1); inudot ++){
            delete h1d_chi2_arr[inudot];
        }
        delete [] h1d_chi2_arr;
    } else {
        MPrintErr("bad search dat");
        abort();
    }

    eph_best->Save(argval->GetOutdir() + "/"
                   + argval->GetOutfileHead() + "_best_eph.txt");
    h1d_pls_best->Save(argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_best_pls.txt",
                       "x,xe,y,ye");
    MxkwQdpTool::MkQdp(h1d_pls_best, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_best_pls.qdp", "x,xe,y,ye");

    // cleaning
    fclose(fp_log);
    delete argval;
    if(NULL != g2d) {delete g2d;}
    if(NULL != data_arr) { delete data_arr;}
    delete search_par;
    delete eph_best;
    delete h1d_pls_best;
    
    return status;
}

