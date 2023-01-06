#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mim_fitparam.h"
#include "mim_chi2plot.h"
#include "mim_fitstat_hg.h"
#include "mim_fitfunc.h"
//#include "mxkw_fitfunc_multi.h"
#include "mim_minfcn.h"
//#include "mxkw_minfcn_multi.h"

#include "mifc_gen.h"
#include "mir_qdp_tool.h"
#include "func_user.h"
#include "arg_fit_func_chi2_multi_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValFitFuncChi2Multi1d* argval = new ArgValFitFuncChi2Multi1d;
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
    // data file
    //
    long nfile;
    string* data_file_line_arr = NULL;
    string* files_arr = NULL;
    string* data_fmt_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetDataFileList(), &data_file_line_arr, &nfile);
    files_arr = new string [nfile];
    data_fmt_arr = new string [nfile];    
    for(long ifile = 0; ifile < nfile; ifile ++){
        int ncolumn = MiStr::GetNcolumn(data_file_line_arr[ifile], " ");
        if(2 != ncolumn){
            MPrintWarn("ncolumn != 2");
        }
        char file_name_tmp[kLineSize];
        char data_fmt_tmp[kLineSize];
        sscanf(data_file_line_arr[ifile].c_str(), "%s %s",
               file_name_tmp, data_fmt_tmp);
        files_arr[ifile] = file_name_tmp;
        data_fmt_arr[ifile] = data_fmt_tmp;
    }
    MiIolib::DelReadFile(data_file_line_arr);

    //
    // data
    //
    GraphData2d** gd2d_arr = new GraphData2d* [nfile];
    TGraph** tgraph_arr = new TGraph* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        if("x" == data_fmt_arr[ifile]){
            MPrintErr("bad format");
            abort();
        } else if("x,y" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataNerr2d;
        } else if("x,y,ye" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataSerr2d;        
        } else if("x,xe,y,ye" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataSerr2d;
        } else if("x,xe,y" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataSerr2d;        
        } else if("x,y,ye+,ye-" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataTerr2d;
        } else if("x,xe,y,ye+,ye-" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataTerr2d;        
        } else if("x,xe+,xe-,y,ye+,ye-" == data_fmt_arr[ifile]){
            gd2d_arr[ifile] = new GraphDataTerr2d;        
        } else {
            MPrintErr("bad format");
            abort();
        }
        gd2d_arr[ifile]->Load(files_arr[ifile], data_fmt_arr[ifile]);
        tgraph_arr[ifile] = gd2d_arr[ifile]->GenTGraph(0.0, 0.0);
    }

    MirFunc* func = FuncUser::GenFunc(argval->GetFuncName());
    FitParam* fitparam = new FitParam;
    fitparam->LoadIn(argval->GetFitpar());
    fitparam->Print(stdout);

    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    
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
    MinFcnOne** minfcn_arr = new MinFcnOne* [nfile];
    for(int iminfcn = 0; iminfcn < nfile; iminfcn ++){
        minfcn_arr[iminfcn] = MinFcnOne::GenMinFcnOne("Chi2Fcn1d",
                                                      func,
                                                      gd2d_arr[iminfcn]->GetNdata(),
                                                      gd2d_arr[iminfcn]->GetXvalArr()->GetVal(), NULL,
                                                      gd2d_arr[iminfcn]->GetOvalArr()->GetVal(),
                                                      gd2d_arr[iminfcn]->GetOvalArr()->GetValSerr(),
                                                      NULL, NULL,
                                                      NULL, NULL);

        printf("get flag_bad Neg = %d\n", minfcn_arr[iminfcn]->GetFlagBadNeg());
        
    }
    
    MinFcnMultiSame* minfcn_multi = new MinFcnMultiSame;
    minfcn_multi->InitSetMinfcn1Arr(nfile, minfcn_arr);

    //
    // fit
    //
    double value_in_sigma_or_cl = 1.0;
    string sigma_or_cl = "sigma";
    int as_npar = 1;
    double tolerance = 0.1;
    FitStatHG* fit_stat_hg = NULL;
    int maxfcn = 0;
    FitFunc::GenFitStatHG(stdout, minfcn_multi, fitparam,
                          chi2plot_par, chi2plot_cont_par,
                          &fit_stat_hg,
                          value_in_sigma_or_cl, sigma_or_cl, as_npar,
                          tolerance, maxfcn);
    
    //
    // fit result
    //
    fit_stat_hg->PrintInfo(stdout);
    fit_stat_hg->PrintInfo(fp_log);
    for(int ifile = 0; ifile < nfile; ifile ++){
        char outfile_head[kLineSize];
        sprintf(outfile_head, "%s_%2.2d", argval->GetOutfileHead().c_str(), ifile);
        FitStatHG::MkOutFitPlot( dynamic_cast<GraphDataSerr2d*>(gd2d_arr[ifile]), func,
                                 fit_stat_hg->GetFitParamBest()->GetPar(),
                                 argval->GetNpointFunc(),
                                 argval->GetOutdir(),
                                 outfile_head,
                                 plot_conf);
    }
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
    delete gd2d_arr;
    delete func;
    delete fitparam;
    delete chi2plot_par;
    delete chi2plot_cont_par;
    delete plot_conf;
    //delete minfcn;
    delete fit_stat_hg;
    fclose(fp_log);

    return status;
}
