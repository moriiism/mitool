#include "mxkw_iolib.h"
#include "mxkw_graph2d_ope.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_qdp_tool.h"

#include "arg_tconv_hd1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValTconvHd1d* argval = new ArgValTconvHd1d;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    HistData1d* hd1d = HistData1d::GenHd1dByLoad(argval->GetLcHd1d());
    HistData1d* hd1d_mjd = TimeConv::GenTimeToMjd(hd1d,
                                                  Telescope::GetMjdref(argval->GetTelescopeIn()),
                                                  argval->GetTunitIn());
    HistData1d* hd1d_out = TimeConv::GenMjdToTime(hd1d_mjd,
                                                  Telescope::GetMjdref(argval->GetTelescopeOut()),
                                                  argval->GetTunitOut());
    hd1d_out->Save(argval->GetLcHd1dOut(), argval->GetFormat());
    
    //
    // cleaning
    //
    
    delete argval;
    delete hd1d;
    delete hd1d_mjd;
    delete hd1d_out;

    return status;
}

