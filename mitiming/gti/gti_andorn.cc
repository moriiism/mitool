#include "mxkw_timing_gti.h"
#include "arg_gti_andorn.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValAndOrN* argval = new ArgValAndOrN;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = NULL;
    fp_log = fopen((argval->GetOutdir() + "/" + argval->GetProgname() + ".log").c_str(), "w");

    string* gtifile_arr = NULL;
    long ngti;
    MxkwIolib::GenReadFile(argval->GetGtiFileList(), &gtifile_arr, &ngti);
    MxkwIolib::Printf2(fp_log, "ngti = %d\n", ngti);

    Interval** gti_arr = new Interval* [ngti];
    for (int igti = 0; igti < ngti; igti ++){
        gti_arr[igti] = new Interval;
    }

    for (int igti = 0; igti < ngti; igti ++){
        gti_arr[igti]->Load(gtifile_arr[igti]);
    }
    MxkwIolib::DelReadFile(gtifile_arr);

    Interval* gti_out = new Interval;
    if("and" == argval->GetAndOr()){
        gti_out->And(gti_arr, ngti);
    } else if ("or" == argval->GetAndOr()){
        gti_out->Or(gti_arr, ngti);
    } else {
        printf("bad operator.\n");
        exit(1);
    }
    
    double offset
        = gti_out->GetOffsetFromTag(argval->GetOffsetTag());
    MxkwIolib::Printf2(fp_log,
                       "gti_out->GetNterm(): %d\n",
                       gti_out->GetNterm());
    MxkwQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MxkwQdpTool::MkQdp(gti_out, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti_out->Save(argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + ".gti");

    for (int igti = 0; igti < ngti; igti ++){
        delete gti_arr[igti];
    }
    delete [] gti_arr;


    // clean
    delete argval;
    delete gti_out;
    fclose(fp_log);
    
    return status;
}
