#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_draw_func_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


double GetXvalLoUpFromPlotConfTag(string tag);
double GetOffsetFromPlotConfTag(string tag);

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValDrawFunc1d* argval = new ArgValDrawFunc1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    char logfile[kLineSize];
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
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
    
    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);

    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    
    double xval_lo = GetXvalLoUpFromPlotConfTag(plot_conf->GetLoStrElm(0));
    double xval_up = GetXvalLoUpFromPlotConfTag(plot_conf->GetUpStrElm(0));
    double offset_xval = GetOffsetFromPlotConfTag(plot_conf->GetOffsetTagElm(0));
    
    //
    // plot by qdp
    //
    MirQdpTool::MkQdp(func, func_par->GetPar(),
                       argval->GetNpointFunc(),
                       xval_lo + offset_xval,
                       xval_up + offset_xval,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + ".qdp",
                       plot_conf);

    //
    // plot by root
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


double GetXvalLoUpFromPlotConfTag(string tag)
{
    if("none" == tag){
        char msg[kLineSize];
        sprintf(msg, "bad plot_conf");
        MPrintErr(msg);
        abort();
    }
    double xval = atof(tag.c_str());
    return xval;
}


double GetOffsetFromPlotConfTag(string tag)
{
    double offset = 0.0;
    if("no" == tag){
        offset = 0.0;
    } else if ( ("st" == tag) ||
                ("md" == tag) ||
                ("ed" == tag) ) {
        char msg[kLineSize];
        sprintf(msg, "bad tag (=%s)",
                tag.c_str());
        MPrintErr(msg);
        abort();        
    } else {
        offset = atof(tag.c_str());
    }
    return offset;
}
