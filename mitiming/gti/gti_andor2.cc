#include "mit_gti.h"
#include "arg_gti_andor2.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValAndOr2* argval = new ArgValAndOr2;
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

    Interval* gti1 = new Interval;
    Interval* gti2 = new Interval;
    gti1->Load(argval->GetGti1());
    gti2->Load(argval->GetGti2());

    Interval* gti_out = new Interval;
    if("and" == argval->GetAndOr()){
        gti_out->And(gti1, gti2);
    } else if ("or" == argval->GetAndOr()){
        gti_out->Or(gti1, gti2);
    } else {
        printf("bad operator.\n");
        exit(1);
    }

    double offset = gti_out->GetOffsetFromTag(argval->GetOffsetTag());
    MiIolib::Printf2(fp_log, "gti_out->GetNterm(): %d\n",
                       gti_out->GetNterm());
    MirQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MirQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti_out->Save(argval->GetOutdir() + "/" +
                  argval->GetOutfileHead() + ".gti");

    // clean
    delete argval;
    delete gti1;
    delete gti2;
    delete gti_out;
    fclose(fp_log);
    
    return status;
}
