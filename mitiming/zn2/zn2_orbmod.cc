#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"

#include "arg.h"
#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValZn2* argval = new ArgValZn2;
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

    MxkwRootTool::Set(argval->GetPlotmode(),
                      argval->GetPrintmode(),
                      argval->GetRootStyle());
    
    Telescope* tel = new Telescope;
    tel->Set(argval->GetTelescope());
    printf("mjdref = %f\n", tel->GetMjdref());
    fprintf(fp_log, "mjdref = %f\n", tel->GetMjdref());

    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;
    
    if("x" == argval->GetLcFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetLcFile());
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetLcFile(), argval->GetLcFormat());
    }

    MxkwSearchPar* search_par = new MxkwSearchPar;
    search_par->Load(argval->GetSearchDat());
    search_par->Print(stdout);

    if(1 == search_par->GetNpar()){
        HistData1d* h1d_zn2 = NULL;
        double nu_dot = 0.0;
        if("x" == argval->GetLcFormat()){
            GenZn2Nu(data_arr, tel->GetMjdref(), argval->GetLcTunit(),
                     search_par->GetNstepElm(0), search_par->GetLowElm(0),
                     search_par->GetUpElm(0),
                     nu_dot,
                     argval->GetEpochMjd(), argval->GetNharmonics(),
                     &h1d_zn2);
        } else {
            GenZn2Nu(g2d, tel->GetMjdref(), argval->GetLcTunit(),
                     search_par->GetNstepElm(0), search_par->GetLowElm(0),
                     search_par->GetUpElm(0),
                     nu_dot,
                     argval->GetEpochMjd(), argval->GetNharmonics(),
                     &h1d_zn2);
        }
        h1d_zn2->MkQdp(argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_zn2.qdp");
        delete h1d_zn2;
    } else if(2 == search_par->GetNpar()){
        HistData2d* h2d_zn2 = NULL;
        HistData1d** h1d_zn2_arr = NULL;
        double nu_dot2 = 0.0;
        if("x" == argval->GetLcFormat()){
            GenZn2NuNuDot(data_arr, tel->GetMjdref(), argval->GetLcTunit(),
                          search_par->GetNstepElm(0), search_par->GetLowElm(0),
                          search_par->GetUpElm(0),
                          search_par->GetNstepElm(1), search_par->GetLowElm(1),
                          search_par->GetUpElm(1),
                          nu_dot2,
                          argval->GetEpochMjd(), argval->GetNharmonics(),
                          &h2d_zn2, &h1d_zn2_arr);
        } else {
            GenZn2NuNuDot(g2d, tel->GetMjdref(), argval->GetLcTunit(),
                          search_par->GetNstepElm(0), search_par->GetLowElm(0),
                          search_par->GetUpElm(0),
                          search_par->GetNstepElm(1), search_par->GetLowElm(1),
                          search_par->GetUpElm(1),
                          nu_dot2,
                          argval->GetEpochMjd(), argval->GetNharmonics(),
                          &h2d_zn2, &h1d_zn2_arr);
        }
        h2d_zn2->MkTH2Fig(argval->GetOutdir() + "/"
                          + argval->GetOutfileHead() + "_zn2.png");
        MxkwQdpTool::MkQdpNhist(h1d_zn2_arr, search_par->GetNstepElm(1),
                                argval->GetOutdir() + "/"
                                + argval->GetOutfileHead() + "_nhist_zn2.qdp",
                                0.0);
        delete h2d_zn2;
        for(int inudot = 0; inudot < search_par->GetNstepElm(1); inudot ++){
            delete h1d_zn2_arr[inudot];
        }
        delete [] h1d_zn2_arr;
    } else {
        MPrintErr("bad search dat");
        abort();
    }

    // cleaning
    fclose(fp_log);
    delete argval;
    delete tel;
    if(NULL != g2d) {delete g2d;}
    if(NULL != data_arr) { delete data_arr;}
    delete search_par;

    return status;
}

