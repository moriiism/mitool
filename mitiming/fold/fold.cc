
#include "mxkw_qdp_tool.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_folding.h"

#include "arg_fold.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValFold* argval = new ArgValFold;
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

    HistDataSerr1d* h1d_pls = NULL;

    Ephemeris* eph = new Ephemeris;
    eph->Load(argval->GetEphfile());
    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;
    if("x" == argval->GetFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetFile());
        h1d_pls = MxkwFolding::GenFolding(data_arr,
                                          Telescope::GetMjdref(argval->GetTelescope()),
                                          argval->GetTunit(),
                                          eph, argval->GetNbin());
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetFile(), argval->GetFormat());
        h1d_pls = MxkwFolding::GenFoldingBinCenter(g2d,
                                                   Telescope::GetMjdref(argval->GetTelescope()),
                                                   argval->GetTunit(),
                                                   eph, argval->GetNbin());
    }

    MxkwQdpTool::MkQdp(h1d_pls, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_pls.qdp", "x,xe,y,ye");

    // cleaning
    fclose(fp_log);
    delete argval;
    if(NULL != g2d) {delete g2d;}
    if(NULL != data_arr) { delete data_arr;}
    delete h1d_pls;
    delete eph;

    return status;
}
