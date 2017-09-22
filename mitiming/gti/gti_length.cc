#include "mxkw_interval.h"
#include "arg_gti_length.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status = kRetNormal;

    ArgValGtiLength* argval = new ArgValGtiLength;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGti());

    double length = gti->GetTotalInterval();
    printf("%e\n", length);
    
    // clean
    delete argval;
    delete gti;
    return status;
}
