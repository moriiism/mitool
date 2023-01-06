#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_qdp_tool.h"
#include "func_user.h"
#include "arg_draw_func_data_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValDrawFuncData1d* argval = new ArgValDrawFuncData1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    char logfile[kLineSize];
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        int ret = system(cmd);
        (void) ret;
    }
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);
    
    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    GraphDataSerr2d* gdata2d = new GraphDataSerr2d;
    gdata2d->Load(argval->GetDataFile(), argval->GetDataFmt());
    
    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);

    MirQdpTool::MkQdpDiff3Serr(gdata2d, func, func_par->GetPar(),
                               argval->GetNpointFunc(),
                               argval->GetOutdir(), argval->GetOutfileHead(),
                               plot_conf);

    //
    // plot by root
    //
    
    //
    // draw data
    //

    double xval_lo = atof(plot_conf->GetLoStrElm(0).c_str());
    double xval_up = atof(plot_conf->GetUpStrElm(0).c_str());
    double yval_lo = atof(plot_conf->GetLoStrElm(1).c_str());
    double yval_up = atof(plot_conf->GetUpStrElm(1).c_str());

    TGraph* tgraph = gdata2d->GenTGraph(0.0, 0.0);
    tgraph->GetXaxis()->SetLimits(xval_lo, xval_up);
    tgraph->SetMinimum(yval_lo);
    tgraph->SetMaximum(yval_up);
    tgraph->Draw("SAME");


    //
    // draw function
    //

    TF1* tf1_func = new TF1("func", func, &MirFunc::Eval,
                            xval_lo, xval_up,
                            func->GetNpar(), "FuncUser", "Eval");
    MirFuncPar::CopyPar(func_par, tf1_func);
    tf1_func->Draw("SAME");
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig);
    
    return status;
}
