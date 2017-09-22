#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"

#include "arg_mk_hist_info.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValMkHistInfo* argval = new ArgValMkHistInfo;
    argval->Init(argc, argv);
    argval->Print(stdout);

    double time_start = TimeConv::MjdToTime(argval->GetStartMjd(),
                                            Telescope::GetMjdref(argval->GetTelescopeOut()),
                                            argval->GetTunitOut());
    double time_end = TimeConv::MjdToTime(argval->GetEndMjd(),
                                          Telescope::GetMjdref(argval->GetTelescopeOut()),
                                          argval->GetTunitOut());
    double delta_time_out = 0.0;
    if("sec" == argval->GetDeltaTimeUnit() &&
       "sec" == argval->GetTunitOut()){
        delta_time_out = argval->GetDeltaTime();
    } else if ("sec" == argval->GetDeltaTimeUnit() &&
               "day" == argval->GetTunitOut()){
        delta_time_out = argval->GetDeltaTime() / kDayToSec;
    } else if ("day" == argval->GetDeltaTimeUnit() &&
               "sec" == argval->GetTunitOut()){
        delta_time_out = argval->GetDeltaTime() * kDayToSec;
    } else if ("day" == argval->GetDeltaTimeUnit() &&
               "day" == argval->GetTunitOut()){
        delta_time_out = argval->GetDeltaTime();
    } else {
        abort();
    }
    
    FILE* fp = fopen(argval->GetHistInfoOut().c_str(), "w");
    fprintf(fp, "# nbin  lo  up  delta_t  mode\n");
    fprintf(fp, "none  %.15e  %.15e  %.15e  ceil\n",
            time_start, time_end, delta_time_out);
    fclose(fp);
    
    // clean
    delete argval;
    return status;
}
