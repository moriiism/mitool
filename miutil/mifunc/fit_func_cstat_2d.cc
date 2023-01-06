#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mim_fitparam.h"
#include "mim_chi2plot.h"
#include "mim_fitstat_hg.h"
#include "mim_fitfunc.h"
#include "mim_minfcn.h"
#include "mifc_gen.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_fit_func_cstat_2d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValFitFuncCstat2d* argval = new ArgValFitFuncCstat2d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());
    
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
    
    //
    // data
    //
    GraphDataSerr3d* g3d = new GraphDataSerr3d;
    g3d->Load(argval->GetDataFile(), argval->GetDataFmt());

    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    FitParam* fitparam = new FitParam;
    fitparam->LoadIn(argval->GetFitpar());
    fitparam->Print(stdout);

    MirPlotConf* plot_conf_projx = new MirPlotConf;
    MirPlotConf* plot_conf_projy = new MirPlotConf;
    plot_conf_projx->Load(argval->GetPlotConfProjxFile());
    plot_conf_projy->Load(argval->GetPlotConfProjyFile());

    //
    // chi2, chi2cont
    //
    Chi2PlotPar* chi2plot_par = NULL;
    Chi2PlotContPar* chi2plot_cont_par = NULL;
    if("none" != argval->GetChi2par()){
        chi2plot_par = new Chi2PlotPar;
        chi2plot_par->Load(argval->GetChi2par());
        chi2plot_par->SetIndex1Arr(fitparam);        
        chi2plot_par->Print(stdout);
        chi2plot_par->Print(fp_log);
    }
    if("none" != argval->GetChi2contPar()){
        chi2plot_cont_par = new Chi2PlotContPar;
        chi2plot_cont_par->Load(argval->GetChi2contPar());
        chi2plot_cont_par->SetIndex2Arr(fitparam);        
        chi2plot_cont_par->Print(stdout);
        chi2plot_cont_par->Print(fp_log);
    }
    

    //
    // minfcn
    //
    MinFcn* minfcn = NULL;
    if("CstatFcn2d" == argval->GetMinfcnName() ||
       "CstatPhysFcn2d" == argval->GetMinfcnName() ){
        minfcn = MinFcnOne::GenMinFcnOne(argval->GetMinfcnName(), func,
                                         g3d->GetNdata(),
                                         g3d->GetXvalArr()->GetVal(),
                                         g3d->GetYvalArr()->GetVal(),
                                         g3d->GetOvalArr()->GetVal(),
                                         g3d->GetOvalArr()->GetValSerr(), NULL, NULL,
                                         NULL, NULL);
    } else {
        MPrintErr("bad minfcn\n");
        abort();
    }

    
    //
    // fit
    //
    double value_in_sigma_or_cl = 1.0;
    string sigma_or_cl = "sigma";
    int as_npar = 1;
    double tolerance = 0.1;
    FitStatHG* fit_stat_hg = NULL;
    int maxfcn = 0;
    FitFunc::GenFitStatHG(stdout, minfcn, fitparam,
                          chi2plot_par, chi2plot_cont_par,
                          &fit_stat_hg,
                          value_in_sigma_or_cl, sigma_or_cl, as_npar,
                          tolerance, maxfcn);

    //
    // fit result
    //
    fit_stat_hg->PrintInfo(stdout);
    fit_stat_hg->PrintInfo(fp_log);

    HistDataSerr2d* h2d_plot = new HistDataSerr2d;
    h2d_plot->Load(argval->GetDataFile());
    FitStatHG::MkOutFitPlot(h2d_plot, func,
                            fit_stat_hg->GetFitParamBest()->GetPar(),
                            argval->GetOutdir(),
                            argval->GetOutfileHead(),
                            plot_conf_projx,
                            plot_conf_projy,
                            root_tool);
    delete h2d_plot;
    if("none" != argval->GetChi2par()){
        fit_stat_hg->MkOutParSearch1d(argval->GetOutdir(),
                                      argval->GetOutfileHead(),
                                      "short");
        fit_stat_hg->PrintErrByParSearch1d(stdout);
        fit_stat_hg->PrintErrByParSearch1d(fp_log);
    }
    if("none" != argval->GetChi2contPar()){
        fit_stat_hg->MkOutParSearch2d(argval->GetOutdir(),
                                      argval->GetOutfileHead(),
                                      "short",
                                      root_tool);
        fit_stat_hg->PrintErrByParSearch2d(stdout);
        fit_stat_hg->PrintErrByParSearch2d(fp_log);
    }
    
    printf("%s: end.\n", argval->GetProgname().c_str());
    
    delete argval;
    delete g3d;
    delete func;
    delete fitparam;
    delete chi2plot_par;
    delete chi2plot_cont_par;
    delete minfcn;
    delete fit_stat_hg;
    delete plot_conf_projx;
    delete plot_conf_projy;
    fclose(fp_log);

    return status;
}
