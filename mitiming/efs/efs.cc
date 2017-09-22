#include "mi_iolib.h"
#include "mir_hist1d_serr.h"
#include "mir_hist_info.h"
#include "mir_qdp_tool.h"

#include "mit_eph.h"
#include "mit_telescope.h"
#include "mit_folding.h"

#include "sub.h"
#include "arg_efs.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValEfs* argval = new ArgValEfs;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;
    
    if("x" == argval->GetFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetFile());
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetFile(), argval->GetFormat());
    }

    HistInfo1d* search_par = new HistInfo1d;
    search_par->Load(argval->GetSearchDat());
    search_par->Print(stdout);

    Ephemeris* eph_best = NULL;
    HistDataSerr1d* h1d_pls_best = NULL;
    if(1 == search_par->GetNpar()){
        HistData1d* h1d_chi2 = NULL;
        double nu_dot = 0.0;
        if("x" == argval->GetFormat()){
            GenEfsNu(data_arr, Telescope::GetMjdref(argval->GetTelescope()),
                     argval->GetTunit(),
                     search_par->GetNbinElm(0), search_par->GetLoElm(0),
                     search_par->GetUpElm(0),
                     nu_dot,
                     argval->GetEpochMjd(), argval->GetNbin(),
                     &h1d_chi2,
                     &eph_best, &h1d_pls_best);
        } else {
            GenEfsNu(g2d, Telescope::GetMjdref(argval->GetTelescope()),
                     argval->GetTunit(),
                     search_par->GetNbinElm(0), search_par->GetLoElm(0),
                     search_par->GetUpElm(0),
                     nu_dot,
                     argval->GetEpochMjd(), argval->GetNbin(),
                     &h1d_chi2,
                     &eph_best, &h1d_pls_best);
        }
        MirQdpTool::MkQdp(h1d_chi2, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_chi2.qdp",
                           "x,xe,y,ye");
        delete h1d_chi2;
    } else if(2 == search_par->GetNpar()){
        HistData2d* h2d_chi2 = NULL;
        HistData1d** h1d_chi2_arr = NULL;
        double nu_dot2 = 0.0;
        if("x" == argval->GetFormat()){
            GenEfsNuNuDot(data_arr, Telescope::GetMjdref(argval->GetTelescope()),
                          argval->GetTunit(),
                          search_par->GetNbinElm(0), search_par->GetLoElm(0),
                          search_par->GetUpElm(0),
                          search_par->GetNbinElm(1), search_par->GetLoElm(1),
                          search_par->GetUpElm(1),
                          nu_dot2,
                          argval->GetEpochMjd(), argval->GetNbin(),
                          &h2d_chi2, &h1d_chi2_arr,
                          &eph_best, &h1d_pls_best);
        } else {
            GenEfsNuNuDot(g2d, Telescope::GetMjdref(argval->GetTelescope()),
                          argval->GetTunit(),
                          search_par->GetNbinElm(0), search_par->GetLoElm(0),
                          search_par->GetUpElm(0),
                          search_par->GetNbinElm(1), search_par->GetLoElm(1),
                          search_par->GetUpElm(1),
                          nu_dot2,
                          argval->GetEpochMjd(), argval->GetNbin(),
                          &h2d_chi2, &h1d_chi2_arr,
                          &eph_best, &h1d_pls_best);
        }
        h2d_chi2->MkTH2Fig(argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_chi2.png",
                           root_tool);
        MirQdpTool::MkQdpNhist(h1d_chi2_arr, search_par->GetNbinElm(1),
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
    MirQdpTool::MkQdp(h1d_pls_best, argval->GetOutdir() + "/"
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

