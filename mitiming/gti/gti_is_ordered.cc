#include "mxkw_interval.h"
#include "arg_gti_is_ordered.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status = kRetNormal;

    ArgValGtiIsOrdered* argval = new ArgValGtiIsOrdered;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGti());

    int ret = gti->IsOrdered();
    printf("%d\n", ret);
    
    // clean
    delete argval;
    delete gti;
    return status;
}
