#include "mxkw_timing_gti.h"
#include "mxkw_timing_telescope.h"
#include "arg_gti_tconv.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValGtiTconv* argval = new ArgValGtiTconv;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    Interval* gti = new Interval;
    gti->Load(argval->GetGtiIn());

    Interval* gti_mjd
        = TimeConv::GenTimeToMjd(
            gti,
            Telescope::GetMjdref(argval->GetTelescopeIn()),
            argval->GetTunitIn());
    Interval* gti_new
        = TimeConv::GenMjdToTime(
            gti_mjd,
            Telescope::GetMjdref(argval->GetTelescopeOut()),
            argval->GetTunitOut());
    gti_new->Save(argval->GetGtiOut());
    
    // clean
    delete argval;
    delete gti;
    delete gti_mjd;
    delete gti_new;
    
    return status;
}
