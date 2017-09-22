#include "mxkw_data_serr.h"
#include "mxkw_timing_gti.h"

#include "arg_select_hd1d_by_gti.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValSelectHd1dByGti* argval = new ArgValSelectHd1dByGti;
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

    HistData1d* hd1d = new HistData1d;
    hd1d->Load(argval->GetLcFile());

    HistData1d* hd1d_sel = new HistData1d;
    HistData1dOpe::GetSelectHd1dByInterval(hd1d, gti,
                                           hd1d);

    char outfile[kLineSize];
    sprintf(outfile, "%s/%s_sel.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    hd1d_sel->Save(outfile, 0);

    // cleaning
    fclose(fp_log);
    delete argval;
    delete gti;
    if(NULL != hd1d) { delete hd1d;}
    if(NULL != hd1d_sel) { delete hd1d_sel;}

    return status;
}

