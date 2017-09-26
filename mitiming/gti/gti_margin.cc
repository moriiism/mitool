#include "mit_gti.h"
#include "mit_telescope.h"

#include "arg_gti_margin.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValMargin* argval = new ArgValMargin;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = NULL;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");

    Interval* gti = new Interval;
    gti->Load(argval->GetGtiFile());
  
    Interval* gti_out = new Interval;
    gti_out->AddMargin(gti, argval->GetTimeMargin(),
                       Telescope::GetTimeAccuracy(argval->GetTelescope(),
                                                  argval->GetTunit()));
    double offset = gti_out->GetOffsetFromTag(argval->GetOffsetTag());
    MiIolib::Printf2(fp_log, "gti_out->GetNterm(): %d\n", gti_out->GetNterm());
    MirQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MirQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti_out->Save(argval->GetGtiOut());
  
    return status;
}
