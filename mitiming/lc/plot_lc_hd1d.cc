#include "mxkw_hist1d_serr.h"
#include "mxkw_qdp_tool.h"

#include "arg_plot_lc_hd1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValPlotLcHd1d* argval = new ArgValPlotLcHd1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MxkwPlotConf* plot_conf = new MxkwPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);

    HistData1d* hd1d = HistData1d::GenHd1dByLoad(argval->GetFileIn());
    MxkwQdpTool::MkQdp(hd1d, argval->GetFileOut(),
                       argval->GetFormat(), plot_conf);

    //
    // cleaning
    //
    delete argval;
    if(NULL != hd1d) {delete hd1d;}
    if(NULL != plot_conf) {delete plot_conf;}
    
    return status;
}

