#include "mi_iolib.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_ope.h"
#include "mir_qdp_tool.h"
#include "arg_milcwin.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

double GetHanningWindow(double phase);

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMilcwin* argval = new ArgValMilcwin;
    argval->Init(argc, argv);
    
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }

    //
    // load data
    //
    GraphData2d* gd2d = GraphData2dOpe::GenGd2dByLoad(argval->GetInfile(),
                                                      argval->GetFormat());
    GraphDataNerr2d* gd2d_new = new GraphDataNerr2d;
    gd2d_new->Init(gd2d->GetNdata());

    double time_st = gd2d->GetXvalElm(0);
    double time_ed = gd2d->GetXvalElm(gd2d->GetNdata() - 1);
    for(long idata = 0; idata < gd2d->GetNdata(); idata++){
        double time = gd2d->GetXvalElm(idata);
        double phase = (time - time_st) / (time_ed - time_st);
        double winval = GetHanningWindow(phase);
        double oval_new = gd2d->GetOvalElm(idata) * winval;
        gd2d_new->SetPoint(idata,
                           gd2d->GetXvalElm(idata),
                           oval_new);
    }

    char outfile[kLineSize];
    sprintf(outfile, "%s/%s.dat",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    gd2d_new->Save(outfile, "x,y");

    
    delete argval;
    
    return status;
}


double GetHanningWindow(double phase){
    double val = 0.0;
    if( 0.0 <= phase && phase <= 1.0){
        val = 0.5 - 0.5 * cos(2 * M_PI * phase);
    } else {
        val = 0.0;
    }
    return val;
}
