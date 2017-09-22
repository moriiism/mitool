#include "mxkw_timing_gti.h"
#include "arg_gti_index.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValGtiIndex* argval = new ArgValGtiIndex;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGti());
    
    long index = gti->GetIndexByTimeQuick(argval->GetTime());
    // long index = gti->GetIndexByTime(argval->GetTime());
    printf("%e  %e  !  st  ed\n",
           gti->GetTstartElm(index),
           gti->GetTstopElm(index));
    printf("%ld\n", index);
    
    delete argval;
    delete gti;
    
    return status;
}
