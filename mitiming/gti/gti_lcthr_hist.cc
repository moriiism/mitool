#include "mxkw_graph2d_serr.h"
#include "mxkw_hist_info.h"
#include "mxkw_hist1d.h"
#include "mxkw_qdp_tool.h"

#include "arg_gti_lcthr_hist.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValLcthrHist* argval = new ArgValLcthrHist;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = NULL;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");

    GraphDataSerr2d* g2d = new GraphDataSerr2d;
    g2d->Load(argval->GetFile(), argval->GetFormat());
    g2d->Sort();

    HistInfo1d* hist_info = new HistInfo1d;
    hist_info->Load(argval->GetHistInfo());
    
    HistData1d* h1d = new HistData1d;
    h1d->Init(hist_info);
    h1d->SetByGraphData2d(g2d);
    
    Interval* gti = h1d->GenIntervalAboveThreshold(argval->GetThreshold());

    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    MxkwIolib::Printf2(fp_log, "gti->GetNterm(): %d\n", gti->GetNterm());
    MxkwQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MxkwQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + "_offset.qdp",
                       "", offset);
    gti->Save(argval->GetGtiOut());

    // clean
    fclose(fp_log);
    delete argval;
    delete g2d;
    delete h1d;
    delete gti;

    return status;
}
