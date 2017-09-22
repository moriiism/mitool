
#include "mxkw_hist1d_serr.h"

#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"

#include "arg.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValTconv* argval = new ArgValTconv;
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
    
    DataArray1d* data_arr = NULL;
    GraphDataSerr2d* g2d  = NULL;

    if("x" == argval->GetLcFormat()){
        data_arr = new DataArray1d;
        data_arr->Load(argval->GetLcFile());
        DataArray1d* data_arr_mjd
            = TimeConv::GenTimeToMjd(data_arr,
                                     Telescope::GetMjdref(argval->GetTelescope()),
                                     argval->GetLcTunit());
        DataArray1d* data_arr_tconv
            = TimeConv::GenMjdToTime(data_arr_mjd,
                                     Telescope::GetMjdref(argval->GetTelescopeOut()),
                                     argval->GetLcTunitOut());

        string outfile = argval->GetOutdir() + "/" + argval->GetOutfileHead()
            + "_tconv.dat";
        int show_index = 0;
        data_arr_tconv->SaveData(outfile, show_index);
        delete data_arr_mjd;
        delete data_arr_tconv;
    } else {
        g2d = new GraphDataSerr2d;
        g2d->Load(argval->GetLcFile(), argval->GetLcFormat());
        GraphDataSerr2d* g2d_mjd
            = TimeConv::GenTimeToMjd(g2d,
                                     Telescope::GetMjdref(argval->GetTelescope()),
                                     argval->GetLcTunit());
        GraphDataSerr2d* g2d_tconv
            = TimeConv::GenMjdToTime(g2d_mjd,
                                     Telescope::GetMjdref(argval->GetTelescopeOut()),
                                     argval->GetLcTunitOut());

        string outfile = argval->GetOutdir() + "/" + argval->GetOutfileHead()
            + "_tconv.qdp";

        g2d_tconv->MkQdp(outfile);
        delete g2d_mjd;
        delete g2d_tconv;
    }

    
    // cleaning
    delete argval;
    if(NULL != g2d) {delete g2d;}
    if(NULL != data_arr) { delete data_arr;}

    return status;
}

