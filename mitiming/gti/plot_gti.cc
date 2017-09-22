#include "mxkw_timing_gti.h"
#include "arg_plot_gti.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValPlotGti* argval = new ArgValPlotGti;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = fopen((argval->GetOutdir() + "/"
                          + argval->GetProgname() + ".log").c_str(), "w");
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());
    
    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    printf("gti->GetNterm(): %ld\n", gti->GetNterm());
    fprintf(fp_log, "gti->GetNterm(): %ld\n", gti->GetNterm());

    MxkwQdpTool::MkQdp(gti, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead()
                       + ".qdp");
    MxkwQdpTool::MkQdp(gti, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() 
                       + "_offset.qdp",
                       "", offset);
    return status;
}
