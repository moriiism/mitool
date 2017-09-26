#include "mit_gti.h"
#include "arg_gti_rmgap.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char *argv[]){
    int status = kRetNormal;

    ArgValGtiRmGap* argval = new ArgValGtiRmGap;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/" + argval->GetProgname() + ".log").c_str(), "w");

    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());
    gti->Sort("st");
    
    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    fprintf(fp_log, "gti->GetNterm(): %ld\n", gti->GetNterm());


    gti->Clean(argval->GetTimeGap());
    
    MirQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MirQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti->Save(argval->GetGtiOut());
    
    return status;
}
