#include "mi_iolib.h"
#include "mir_plot_conf.h"
#include "mir_root_tool.h"
#include "mifc_gen.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_qdp_tool.h"
#include "func_user.h"

#include "arg_draw_spec_data.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[]){

    int status = kRetNormal;
  
    ArgValDrawSpecData* argval = new ArgValDrawSpecData;
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

    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    
    GraphDataSerr2d* gdata2d = new GraphDataSerr2d;
    gdata2d->Load(argval->GetDataFile(), argval->GetDataFmt());

    TGraph* tgraph = NULL;
    tgraph = gdata2d->GenTGraph(0.0, 0.0);
    tgraph->Draw("P");

    FuncSpec* func = MifcGen::GenFuncSpec(argval->GetFuncName());
    MirFuncPar* func_par = new MirFuncPar;
    func_par->Load(argval->GetParFile());
    func_par->Print(stdout);


    double xval_lo = atof(plot_conf->GetLoStrElm(0).c_str());
    double xval_up = atof(plot_conf->GetUpStrElm(0).c_str());

    TF1* tf1_spec = NULL;
    if("f_nu" == argval->GetSpecType()){
        tf1_spec = func->GenTF1FNu(xval_lo, xval_up);
    } else if ("nu_f_nu" == argval->GetSpecType()){
        tf1_spec = func->GenTF1NuFNu(xval_lo, xval_up);
    } else if ("ph_nu" == argval->GetSpecType()){
        tf1_spec = func->GenTF1PhNu(xval_lo, xval_up);
    } else {
        MPrintErr("bad spec type");
        abort();
    }
    MirFuncPar::CopyPar(func_par, tf1_spec);

    tf1_spec->Draw("SAME");
    
    char outfig[kLineSize];
    sprintf(outfig, "%s/%s_%s.png",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetSpecType().c_str());
    root_tool->GetTCanvas()->Update();
    root_tool->GetTCanvas()->Print(outfig);

    int npoint_func = 1000;
    MirQdpTool::MkQdpDiff3Serr(gdata2d, func, func_par->GetPar(),
                               npoint_func,
                               argval->GetOutdir(),
                               argval->GetOutfileHead(),
                               plot_conf);

    
    return status;
}
