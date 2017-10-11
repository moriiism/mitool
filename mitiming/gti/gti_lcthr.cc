#include "mir_graph2d_serr.h"
#include "mir_hist1d_nerr.h"
#include "mir_qdp_tool.h"

#include "arg_gti_lcthr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;

    ArgValLcthr* argval = new ArgValLcthr;
    argval->Init(argc, argv);
    argval->Print(stdout);

    if(MiIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log = NULL;
    fp_log = fopen((argval->GetOutdir() + "/" + argval->GetProgname() + ".log").c_str(), "w");


    GraphDataSerr2d* g2d = new GraphDataSerr2d;
    g2d->Load(argval->GetFile(), argval->GetFormat());
    g2d->Sort();

    HistDataNerr1d* h1d = new HistDataNerr1d;
    HistData1dOpe::FillByGd2d(g2d, h1d);
    
    Interval* gti = h1d->GenIntervalAboveThreshold(argval->GetThreshold());

    double offset = gti->GetOffsetFromTag(argval->GetOffsetTag());
    MiIolib::Printf2(fp_log, "gti->GetNterm(): %d\n", gti->GetNterm());
    MirQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
                       argval->GetOutfileHead() + "_" +
                       argval->GetProgname() + ".qdp");
    MirQdpTool::MkQdp(gti, argval->GetOutdir() + "/" +
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
