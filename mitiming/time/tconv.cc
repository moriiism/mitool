#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"
#include "arg_tconv.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValTconv* argval = new ArgValTconv;
    argval->Init(argc, argv);
    argval->Print(stdout);

    double time = argval->GetTime();
    double time_mjd = TimeConv::TimeToMjd(time,
                                          Telescope::GetMjdref(argval->GetTelescopeIn()),
                                          argval->GetTunitIn());
    double time_out = TimeConv::MjdToTime(time_mjd,
                                          Telescope::GetMjdref(argval->GetTelescopeOut()),
                                          argval->GetTunitOut());
    printf("time_out = %.15e\n", time_out);
    
    // cleaning
    delete argval;
    
    return status;
}

