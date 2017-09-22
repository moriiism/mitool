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
#include "arg_fit_func_cstat_em_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status = kRetNormal;
    
    ArgValFitFuncCstatEm1d* argval = new ArgValFitFuncCstatEm1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());
    
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
    
    //
    // data
    //
    GraphData2d* g2d = NULL;
    g2d = GraphData2d::GenGd2dByLoad(argval->GetDataFile(), argval->GetDataFmt());

    //
    // function & parfile
    //
    long nfunc = 0;
    string* func_list_line_arr = NULL;
    string* func_name_arr = NULL;
    string* par_file_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncParList(), &func_list_line_arr, &nfunc);
    func_name_arr = new string [nfunc];
    par_file_arr = new string [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        int ncolumn = MiStr::GetNcolumn(func_list_line_arr[ifunc]);
        if(2 != ncolumn){
            MPrintErr("ncolumn != 2");
            abort();
        }
        char func_name_tmp[kLineSize];
        char par_file_tmp[kLineSize];
        sscanf(func_list_line_arr[ifunc].c_str(), "%s %s",
               func_name_tmp, par_file_tmp);
        func_name_arr[ifunc] = func_name_tmp;
        par_file_arr[ifunc] = par_file_tmp;
        printf("func_name, par_file = %s  %s\n",
               func_name_arr[ifunc].c_str(), par_file_arr[ifunc].c_str());
    }
    MiIolib::DelReadFile(func_list_line_arr);


    MirFunc** func_arr = new MirFunc* [nfunc];
    MirFuncPar** func_par_arr = new MirFuncPar* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_arr[ifunc] = FuncUser::GenFunc(func_name_arr[ifunc]);
        func_par_arr[ifunc] = new MirFuncPar;
        func_par_arr[ifunc]->Load(par_file_arr[ifunc]);
    }


    




    


    
    //
    // fit result
    //
    fit_stat_hg->PrintInfo(stdout);
    fit_stat_hg->PrintInfo(fp_log);
    GraphDataSerr2d* g2d_serr = new GraphDataSerr2d;
    g2d_serr->Copy(g2d);
    g2d_serr->SetOvalErrArrByPoissonErr();
    FitStatHG::MkOutFitPlot(g2d_serr, func,
                            fit_stat_hg->GetFitParamBest()->GetPar(),
                            argval->GetNpointFunc(),
                            argval->GetOutdir(),
                            argval->GetOutfileHead(),
                            plot_conf);
    delete g2d_serr;
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
    delete g2d;
    delete func;
    delete fitparam;
    delete chi2plot_par;
    delete chi2plot_cont_par;
    delete minfcn;
    delete fit_stat_hg;
    fclose(fp_log);

    return status;
}
