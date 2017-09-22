#include "mxkw_iolib.h"
#include "mxkw_graph2d_ope.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_qdp_tool.h"

#include "arg_tconv_da1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValTconvDa1d* argval = new ArgValTconvDa1d;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    DataArray1d* da1d = DataArray1d::GenDa1dByLoad(argval->GetLcDa1d(),
                                                   argval->GetFormat());
    DataArray1d* da1d_mjd = TimeConv::GenTimeToMjd(da1d,
                                                   Telescope::GetMjdref(argval->GetTelescopeIn()),
                                                   argval->GetTunitIn());
    DataArray1d* da1d_out = TimeConv::GenMjdToTime(da1d_mjd,
                                                   Telescope::GetMjdref(argval->GetTelescopeOut()),
                                                   argval->GetTunitOut());
    da1d_out->Save(argval->GetLcDa1dOut(), 0, 0.0);
    
    //
    // cleaning
    //
    
    delete argval;
    delete da1d;
    delete da1d_mjd;
    delete da1d_out;

    return status;
}

