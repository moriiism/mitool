#include "mxkw_data_serr.h"
#include "mxkw_timing_gti.h"

#include "arg_select_da1d_by_gti.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValSelectDa1dByGti* argval = new ArgValSelectDa1dByGti;
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

    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());

    DataArray1d* data_arr = new DataArray1d;
    data_arr->Load(argval->GetLcFile());
    data_arr->Sort();

    DataArray1d* data_sel_arr = new DataArray1d;
    DataArray1dOpe::GetSelectDa1dByInterval(data_arr, gti,
                                            data_sel_arr);

    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_sel.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    data_sel_arr->Save(outfile, 0, 0.0);

    // cleaning
    fclose(fp_log);
    delete argval;
    delete gti;
    if(NULL != data_arr) { delete data_arr;}
    if(NULL != data_sel_arr) { delete data_sel_arr;}

    return status;
}

