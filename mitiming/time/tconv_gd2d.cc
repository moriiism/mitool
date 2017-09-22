#include "mxkw_iolib.h"
#include "mxkw_graph2d_ope.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_qdp_tool.h"

#include "arg_tconv_gd2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValTconvGd2d* argval = new ArgValTconvGd2d;
    argval->Init(argc, argv);
    argval->Print(stdout);
    
    GraphData2d* gd2d = GraphData2d::GenGd2dByLoad(argval->GetLcGd2d(),
                                                   argval->GetFormat());
    GraphData2d* gd2d_mjd = TimeConv::GenTimeToMjd(gd2d,
                                                   Telescope::GetMjdref(argval->GetTelescopeIn()),
                                                   argval->GetTunitIn());
    GraphData2d* gd2d_out = TimeConv::GenMjdToTime(gd2d_mjd,
                                                   Telescope::GetMjdref(argval->GetTelescopeOut()),
                                                   argval->GetTunitOut());
    gd2d_out->Save(argval->GetLcGd2dOut(), argval->GetFormat());
    
    //
    // cleaning
    //
    
    delete argval;
    delete gd2d;
    delete gd2d_mjd;
    delete gd2d_out;

    return status;
}

