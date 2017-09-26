#include "mit_gti.h"
#include "arg_gti_split.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValGtiSplit* argval = new ArgValGtiSplit;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti_one = new Interval;
    gti_one->InitSet(argval->GetTstart(), argval->GetTstop());
    Interval* gti_split = new Interval;
    gti_split->Split(gti_one, argval->GetNsplit());
    gti_split->Save(argval->GetGtiOut());

    // clean
    delete argval;
    delete gti_one;
    delete gti_split;

    return status;
}

