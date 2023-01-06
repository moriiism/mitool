#include "TF2.h"

#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_qdp_tool.h"
#include "func_user.h"
#include "arg_draw_func_2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

double GetXvalLoUpFromPlotConfTag(string tag);
double GetOffsetFromPlotConfTag(string tag);

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValDrawFunc2d* argval = new ArgValDrawFunc2d;
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

    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);

    MirPlotConf* plot_conf_projx = new MirPlotConf;
    plot_conf_projx->Load(argval->GetPlotConfProjxFile());
    plot_conf_projx->Print(stdout);
    MirPlotConf* plot_conf_projy = new MirPlotConf;
    plot_conf_projy->Load(argval->GetPlotConfProjyFile());
    plot_conf_projy->Print(stdout);

    double xval_lo = GetXvalLoUpFromPlotConfTag(plot_conf_projx->GetLoStrElm(0));
    double xval_up = GetXvalLoUpFromPlotConfTag(plot_conf_projx->GetUpStrElm(0));
    double yval_lo = GetXvalLoUpFromPlotConfTag(plot_conf_projy->GetLoStrElm(0));
    double yval_up = GetXvalLoUpFromPlotConfTag(plot_conf_projy->GetUpStrElm(0));
    
    double offset_xval = GetOffsetFromPlotConfTag(plot_conf_projx->GetOffsetTagElm(0));
    double offset_yval = GetOffsetFromPlotConfTag(plot_conf_projy->GetOffsetTagElm(0));
    
    //
    // plot by qdp
    //
    string calc_mode = "amean";
    MirQdpTool::MkQdpProj(func, func_par->GetPar(),
                           xval_lo + offset_xval, xval_up + offset_xval,
                           yval_lo + offset_yval, yval_up + offset_yval,
                           argval->GetOutdir(), argval->GetOutfileHead(), calc_mode,
                           argval->GetNpointFunc(),
                           plot_conf_projx,
                           plot_conf_projy);
    //
    // plot by root
    //
    TF2* tf2_func = new TF2("func", func, &MirFunc::Eval,
                            xval_lo, xval_up,
                            yval_lo, yval_up,
                            func->GetNpar(), "FuncUser", "Eval");
    MirFuncPar::CopyPar(func_par, tf2_func);


    // colz
    tf2_func->Draw("COLZ");
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s_colz.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig);

    // LEGO
    tf2_func->Draw("LEGO");
    sprintf(outfig, "%s/%s_lego.png",
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
