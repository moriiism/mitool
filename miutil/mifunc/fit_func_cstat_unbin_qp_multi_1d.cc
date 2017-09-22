#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mifc_graph2d.h"
#include "mim_fitparam.h"
#include "mim_chi2plot.h"
#include "mim_fitstat_hg.h"
#include "mim_fitfunc.h"
#include "mim_minfcn.h"
#include "mifc_gen.h"
#include "mir_func_ope.h"
#include "mir_qdp_tool.h"
#include "mim_ls.h"
#include "mim_tie.h"

#include "func_user.h"
#include "arg_fit_func_cstat_unbin_qp_multi_1d.h"

// func_rate : count rate function (c/sec)
double GetGoodnessOfFit(const HistData1d* const hd1d_evt_fill,
                        const FitStatHG* const fit_stat_hg,
                        const MirFunc* const func_rate);

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValFitFuncCstatUnbinQpMulti1d* argval = new ArgValFitFuncCstatUnbinQpMulti1d;
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
    // data file
    //
    long nfile;
    string* data_file_line_arr = NULL;
    string* file_arr = NULL;
    string* file_mask_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetDataFileList(), &data_file_line_arr, &nfile);
    file_arr = new string [nfile];
    file_mask_arr = new string [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        int ncolumn = MiStr::GetNcolumn(data_file_line_arr[ifile], " ");
        if(2 != ncolumn){
            MPrintErr("ncolumn != 2");
            abort();
        }
        char file_name_tmp[kLineSize];
        char file_mask_tmp[kLineSize];
        sscanf(data_file_line_arr[ifile].c_str(), "%s %s",
               file_name_tmp, file_mask_tmp);
        file_arr[ifile]      = file_name_tmp;
        file_mask_arr[ifile] = file_mask_tmp;
    }
    MiIolib::DelReadFile(data_file_line_arr);

    //
    // data & hist of mask
    //
    DataArray1d** da1d_arr = new DataArray1d* [nfile];
    HistData1d** hd1d_mask_arr = new HistData1d* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        da1d_arr[ifile] = new DataArray1d;
        da1d_arr[ifile]->Load(file_arr[ifile]);
        da1d_arr[ifile]->Sort();
        hd1d_mask_arr[ifile] = new HistData1d;
        hd1d_mask_arr[ifile]->Load(file_mask_arr[ifile]);

        char subdir[kLineSize];
        sprintf(subdir, "%s/%2.2ld", argval->GetOutdir().c_str(), ifile);
        if( MiIolib::TestFileExist( subdir ) ){
            char cmd[kLineSize];
            sprintf(cmd, "mkdir -p %s", subdir);
            system(cmd);
        }
        MirQdpTool::MkQdpMode2(da1d_arr[ifile],
                                string() + subdir + "/" +
                                argval->GetOutfileHead() + "_da1d.qdp",
                                "", 0.0);        
        MirQdpTool::MkQdp(hd1d_mask_arr[ifile],
                           string() + subdir + "/" +
                           argval->GetOutfileHead() + "_hd1d_mask.qdp",
                           "x,y");
    }

    //
    // extract data according to hd1d_mask
    //
    DataArray1d** da1d_sel_arr = new DataArray1d* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        da1d_sel_arr[ifile] = new DataArray1d;

        vector<double> da1d_sel_vec;
        for(long idata = 0; idata < da1d_arr[ifile]->GetNdata(); idata ++){
            double xval = da1d_arr[ifile]->GetValElm(idata);
            if(1 == hd1d_mask_arr[ifile]->GetOvalElmAtX( xval )){
                da1d_sel_vec.push_back(xval);
            }
        }
        da1d_sel_arr[ifile]->InitSetVal(da1d_sel_vec);

        char subdir[kLineSize];
        sprintf(subdir, "%s/%2.2ld", argval->GetOutdir().c_str(), ifile);
        if( MiIolib::TestFileExist( subdir ) ){
            char cmd[kLineSize];
            sprintf(cmd, "mkdir -p %s", subdir);
            system(cmd);
        }
        MirQdpTool::MkQdpMode2(da1d_sel_arr[ifile],
                                string() + subdir + "/" +
                                argval->GetOutfileHead() + "_da1d_sel.qdp",
                                "", 0.0);
    }

    HistDataSerr1d** hd1d_evt_fill_arr = new HistDataSerr1d* [nfile];
    HistDataSerr1d** hd1d_evt_fill_rate_arr = new HistDataSerr1d* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        hd1d_evt_fill_arr[ifile] = new HistDataSerr1d;
        hd1d_evt_fill_arr[ifile]->Init(hd1d_mask_arr[ifile]->GetNbinX(),
                                       hd1d_mask_arr[ifile]->GetXvalLo(),
                                       hd1d_mask_arr[ifile]->GetXvalUp());
        for(long idata = 0; idata < da1d_sel_arr[ifile]->GetNdata(); idata++){
            hd1d_evt_fill_arr[ifile]->Fill(da1d_sel_arr[ifile]->GetValElm(idata));
        }
        hd1d_evt_fill_rate_arr[ifile] = new HistDataSerr1d;
        hd1d_evt_fill_rate_arr[ifile]->Scale(hd1d_evt_fill_arr[ifile],
                                             1./hd1d_evt_fill_arr[ifile]->GetBinWidth(), 0.0);
    }


    //
    // func_par_id_list
    //
    long nfunc = 0;
    string* func_par_id_list_line_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncParIdList(),
                                      &func_par_id_list_line_arr, &nfunc);
    string* func_name_arr = new string[nfunc];
    string* par_file_arr = new string[nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        int ncolumn = MiStr::GetNcolumn(func_par_id_list_line_arr[ifunc]);
        if(3 != ncolumn){
            MPrintErr("ncolumn != 3");
            abort();
        }
        char func_name_tmp[kLineSize];
        char par_file_tmp[kLineSize];
        int id_func_dummy = 0;
        sscanf(func_par_id_list_line_arr[ifunc].c_str(), "%d %s %s",
               &id_func_dummy, func_name_tmp, par_file_tmp);
        func_name_arr[ifunc] = func_name_tmp;
        par_file_arr[ifunc]  = par_file_tmp;
        printf("ifile, func_name, par_file = %d  %s  %s\n",
               ifunc, func_name_arr[ifunc].c_str(), par_file_arr[ifunc].c_str());
    }
    MiIolib::DelReadFile(func_par_id_list_line_arr);

    //
    // func_id_list
    //
    long nline_func_id = 0;
    string* func_id_list_line_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncIdList(), &func_id_list_line_arr, &nline_func_id);
    if(nline_func_id != nfile){
        printf("nline_func_id (=%ld) != nfile (=%ld)\n",
               nline_func_id, nfile);
        abort();
    }
    int*  nfunc_id_arr = new int [nfile];
    int** func_id_arr = new int* [nfile];
    for(long ifile = 0; ifile < nfile; ifile ++){
        int nsplit = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(func_id_list_line_arr[ifile], &nsplit, &split_arr, " ");
        nfunc_id_arr[ifile] = nsplit;
        func_id_arr[ifile] = new int [nsplit];
        for(int isplit = 0; isplit < nsplit; isplit ++){
            func_id_arr[ifile][isplit] = atoi(split_arr[isplit].c_str());
        }
        delete [] split_arr;
    }
    MiIolib::DelReadFile(func_id_list_line_arr);

    for(int ifile = 0; ifile < nfile; ifile ++){
        printf("ifile = %d: nfunc = %d\n",
               ifile, nfunc_id_arr[ifile]);
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            printf("%d ", func_id_arr[ifile][ifunc]);
        }
        printf("\n");
    }
    
    //
    // func_arr
    //
    MirFunc*** func_arr = new MirFunc** [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        func_arr[ifile] = new MirFunc* [nfunc_id_arr[ifile]];
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            func_arr[ifile][ifunc] = FuncUser::GenFunc(func_name_arr[ func_id_arr[ifile][ifunc] ]);
        }
    }

    //
    // func_par_arr
    //
    MirFuncPar*** func_par_arr = new MirFuncPar** [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        func_par_arr[ifile] = new MirFuncPar* [ nfunc_id_arr[ifile] ];
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            func_par_arr[ifile][ifunc] = new MirFuncPar;
            func_par_arr[ifile][ifunc]->Load( par_file_arr[ func_id_arr[ifile][ifunc] ] );
        }
    }
    for(int ifile = 0; ifile < nfile; ifile ++){
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            func_par_arr[ifile][ifunc]->Print(stdout);
        }
    }
    
    //
    // tie
    //
    MimTie* mxkw_tie = new MimTie;
    mxkw_tie->Load(argval->GetTieCoeffList());
    
    //
    // plot configuration
    //
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    
    //
    // solve by QP
    //
    GraphData2d** gd2d_arr = new GraphData2d* [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        long nbin_hd1d_evt_fill = 0;
        double* xval_arr_hd1d_evt_fill = NULL;
        hd1d_evt_fill_arr[ifile]->GenXvalArr(&xval_arr_hd1d_evt_fill,
                                             &nbin_hd1d_evt_fill);
        gd2d_arr[ifile] = new GraphData2d;
        gd2d_arr[ifile]->Init();
        gd2d_arr[ifile]->SetXvalArrDbl(nbin_hd1d_evt_fill, xval_arr_hd1d_evt_fill);
        gd2d_arr[ifile]->SetOvalArr(hd1d_evt_fill_arr[ifile]->GetOvalArr());
        delete [] xval_arr_hd1d_evt_fill;
    }

    double** par_arr_best_lsqp = NULL;
    double chi2_min = 0.0;
    double aic = 0.0;
    double bic = 0.0;
    MimLS::GenLeastSquarePoissonQuadProgPlusMulti(nfile,
                                                   gd2d_arr,
                                                   nfunc_id_arr,
                                                   func_arr,
                                                   func_par_arr,
                                                   mxkw_tie,
                                                   &par_arr_best_lsqp,
                                                   &chi2_min,
                                                   &aic,
                                                   &bic);

    //
    // solve by SVD w/o tie
    //
    double** par_arr_best_svd = new double* [nfile];
    double** par_serr_arr_svd = new double* [nfile];
    double*** par_cov_arr_svd = new double** [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        long nbin_hd1d_evt_fill = 0;
        double* xval_arr_hd1d_evt_fill = NULL;
        hd1d_evt_fill_arr[ifile]->GenXvalArr(&xval_arr_hd1d_evt_fill,
                                             &nbin_hd1d_evt_fill);
        MimLS::GenLeastSquarePoissonSvd(hd1d_evt_fill_arr[ifile]->GetNbinX(),
                                         xval_arr_hd1d_evt_fill,
                                         hd1d_evt_fill_arr[ifile]->GetOvalArrDbl(),
                                         nfunc_id_arr[ifile],
                                         func_arr[ifile],
                                         func_par_arr[ifile],
                                         &par_arr_best_svd[ifile],
                                         &par_serr_arr_svd[ifile],
                                         &par_cov_arr_svd[ifile]);
        delete [] xval_arr_hd1d_evt_fill;
    }
    
    //
    // fit result of QP
    //

    //
    // count rate function (c/sec)
    //
    
    //
    // func_lincomb_arr
    //
    LinCombFunc** func_lincomb_arr = new LinCombFunc* [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        func_lincomb_arr[ifile] = new LinCombFunc;
        func_lincomb_arr[ifile]->InitSet(nfunc_id_arr[ifile], func_arr[ifile]);
    }
    
    //
    // func_lincomb_par_arr
    //
    MirFuncPar** func_lincomb_par_arr = new MirFuncPar* [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        func_lincomb_par_arr[ifile] = new MirFuncPar;
        func_lincomb_par_arr[ifile]->Init(func_lincomb_arr[ifile]->GetNpar());
        int ipar_tot = 0;
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            for(int ipar = 0; ipar < func_par_arr[ifile][ifunc]->GetNpar() ; ipar ++){
                char func_par_name_this[kLineSize];
                int func_id_this = func_id_arr[ifile][ifunc];
                sprintf(func_par_name_this, "func%2.2d_%s_%s",
                        func_id_this,
                        func_name_arr[func_id_this].c_str(),
                        func_par_arr[ifile][ifunc]->GetParNameElm(ipar).c_str());
                func_lincomb_par_arr[ifile]->SetElm(ipar_tot,
                                                    func_par_name_this,
                                                    func_par_arr[ifile][ifunc]->GetParElm(ipar));
                ipar_tot ++;
            }
        }
        for(int ifunc = 0; ifunc < nfunc_id_arr[ifile]; ifunc ++){
            int func_id_this = func_id_arr[ifile][ifunc];
            char func_par_name_this[kLineSize];
            sprintf(func_par_name_this, "func%2.2d_%s_coeff",
                    func_id_this,
                    func_name_arr[func_id_this].c_str());
            double coeff = par_arr_best_lsqp[ifile][ifunc] / hd1d_evt_fill_arr[ifile]->GetBinWidth();
            func_lincomb_par_arr[ifile]->SetElm(ipar_tot,
                                                func_par_name_this,
                                                coeff);
            ipar_tot ++;
        }
    }
    for(int ifile = 0; ifile < nfile; ifile ++){
        func_lincomb_par_arr[ifile]->Print(stdout);
    }

    
    for(int ifile = 0; ifile < nfile; ifile ++){
        char subdir[kLineSize];
        sprintf(subdir, "%s/%2.2d", argval->GetOutdir().c_str(), ifile);
        printf("subdir = %s\n", subdir);
        if( MiIolib::TestFileExist( subdir ) ){
            char cmd[kLineSize];
            sprintf(cmd, "mkdir -p %s", subdir);
            system(cmd);
        }
        FitStatHG::MkOutFitPlot(hd1d_evt_fill_rate_arr[ifile],
                                func_lincomb_arr[ifile],
                                func_lincomb_par_arr[ifile]->GetPar(),
                                argval->GetNpointFunc(),
                                subdir,
                                argval->GetOutfileHead() + "_qp",
                                plot_conf);
    }


    //
    // fit by Minuit
    //
    
    //
    // func_lincomb_par_index
    //
    
    MirFuncLincombParIndex* func_lincomb_par_index = new MirFuncLincombParIndex;
    func_lincomb_par_index->InitSet(nfile,
                                    func_lincomb_arr,
                                    mxkw_tie);
    func_lincomb_par_index->Print(stdout);

    
    //
    // fitparam_lincomb
    //

    FitParam* fitparam = new FitParam;
    fitparam->Init(func_lincomb_par_index->GetNparTotal());
    for(int ifile = 0; ifile < func_lincomb_par_index->GetNfile(); ifile ++){
        int ipar_tot = 0;
        for(int ifunc = 0; ifunc < func_lincomb_par_index->GetNfuncArrElm(ifile); ifunc ++){
            for(int ipar = 0; ipar < func_lincomb_par_index->GetNparBaseArrElm(ifile, ifunc); ipar ++){
                if(NULL == func_lincomb_par_index->GetIndexBaseArrElm(ifile, ifunc, ipar)->GetPtr()){
                    int index = func_lincomb_par_index->GetIndexBaseArrElm(ifile, ifunc, ipar)->GetValLink();
                    char par_name[kLineSize];
                    sprintf(par_name, "file%2.2d_%s", ifile, func_lincomb_par_arr[ifile]->GetParNameElm(ipar_tot).c_str());
                    fitparam->SetInElm(index,
                                       par_name,
                                       func_lincomb_par_arr[ifile]->GetParElm(ipar_tot),
                                       -1.0,
                                       "none",
                                       "none",
                                       0,
                                       ifunc);
                }
                ipar_tot ++;
            }
        }
        for(int ifunc = 0; ifunc < func_lincomb_par_index->GetNparCoeffArrElm(ifile); ifunc ++){
            if(NULL == func_lincomb_par_index->GetIndexCoeffArrElm(ifile, ifunc)->GetPtr()){
                int index = func_lincomb_par_index->GetIndexCoeffArrElm(ifile, ifunc)->GetValLink();
                char par_name[kLineSize];
                sprintf(par_name, "file%2.2d_%s", ifile, func_lincomb_par_arr[ifile]->GetParNameElm(ipar_tot).c_str());
                fitparam->SetInElm(index,
                                   par_name,
                                   func_lincomb_par_arr[ifile]->GetParElm(ipar_tot),
                                   par_serr_arr_svd[ifile][ifunc] / hd1d_evt_fill_arr[ifile]->GetBinWidth() / 10.0,
                                   "0.0",
                                   "1.e5",
                                   1,
                                   ifunc);
            }
            ipar_tot ++;            
        }
    }
    fitparam->Print(stdout);

    
//////    //
//////    // chi2, chi2cont
//////    //
//////    
//////    Chi2PlotPar* chi2plot_par = NULL;
//////    Chi2PlotContPar* chi2plot_cont_par = NULL;
//////    if("none" != argval->GetChi2par()){
//////        chi2plot_par = new Chi2PlotPar;
//////        chi2plot_par->Load(argval->GetChi2par());
//////        chi2plot_par->SetIndex1Arr(fitparam);
//////        chi2plot_par->Print(stdout);
//////        chi2plot_par->Print(fp_log);
//////    }
//////    if("none" != argval->GetChi2contPar()){
//////        chi2plot_cont_par = new Chi2PlotContPar;
//////        chi2plot_cont_par->Load(argval->GetChi2contPar());
//////        chi2plot_cont_par->SetIndex2Arr(fitparam);
//////        chi2plot_cont_par->Print(stdout);
//////        chi2plot_cont_par->Print(fp_log);
//////    }
//    


    //
    // minfcn
    //
    MinFcnOne** minfcn_arr = new MinFcnOne* [nfile];
    for(int ifile = 0; ifile < nfile; ifile ++){
        minfcn_arr[ifile] = MinFcnOne::GenMinFcnOne("CstatUnbinPhysFcn1d",
                                                    func_lincomb_arr[ifile],
                                                    da1d_sel_arr[ifile]->GetNdata(),
                                                    da1d_sel_arr[ifile]->GetVal(), NULL,
                                                    NULL, NULL, NULL, NULL,
                                                    hd1d_mask_arr[ifile], NULL);
    }
    MinFcnLincombMultiTie* minfcn_multi_tie = new MinFcnLincombMultiTie;
    minfcn_multi_tie->InitSetMinfcn1Arr(nfile, minfcn_arr);
    minfcn_multi_tie->SetFuncLincombParIndex(func_lincomb_par_index);
    
    //
    // fit
    //
    double value_in_sigma_or_cl = 1.0;
    string sigma_or_cl = "sigma";
    int as_npar = 1;
    double tolerance = 0.1;
    FitStatHG* fit_stat_hg = NULL;
    int maxfcn = 0;
    FitFunc::GenFitStatHG(stdout, minfcn_multi_tie, fitparam,
                          NULL, NULL,
                          &fit_stat_hg,
                          value_in_sigma_or_cl, sigma_or_cl, as_npar,
                          tolerance, maxfcn);
    //
    // fit result
    //
    fit_stat_hg->PrintInfo(stdout);
    fit_stat_hg->PrintInfo(fp_log);
    for(int ifile = 0; ifile < nfile; ifile ++){

        char subdir[kLineSize];
        sprintf(subdir, "%s/%2.2d", argval->GetOutdir().c_str(), ifile);
        printf("subdir = %s\n", subdir);
        if( MiIolib::TestFileExist( subdir ) ){
            char cmd[kLineSize];
            sprintf(cmd, "mkdir -p %s", subdir);
            system(cmd);
        }


        int ipar_tot = 0;
        double* par_best_arr = new double [func_lincomb_par_arr[ifile]->GetNpar()];
        for(int ifunc = 0; ifunc < func_lincomb_par_index->GetNfuncArrElm(ifile); ifunc ++){
            for(int ipar = 0; ipar < func_lincomb_par_index->GetNparBaseArrElm(ifile, ifunc); ipar ++){
                par_best_arr[ipar_tot] =
                    fit_stat_hg->GetFitParamBest()->GetParElm(
                        func_lincomb_par_index->GetIndexBaseArrElm(ifile, ifunc, ipar)->GetValLink()
                        );
                ipar_tot ++;
            }
        }
        for(int ifunc = 0; ifunc < func_lincomb_par_index->GetNparCoeffArrElm(ifile); ifunc ++){
            par_best_arr[ipar_tot] =
                    fit_stat_hg->GetFitParamBest()->GetParElm(
                        func_lincomb_par_index->GetIndexCoeffArrElm(ifile, ifunc)->GetValLink()
                        );
            ipar_tot ++;
        }
        
        FitStatHG::MkOutFitPlot(hd1d_evt_fill_rate_arr[ifile],
                                func_lincomb_arr[ifile],
                                par_best_arr,
                                argval->GetNpointFunc(),
                                subdir,
                                argval->GetOutfileHead() + "_minuit",
                                plot_conf);
    }
    
//////    if("none" != argval->GetChi2par()){
//////        fit_stat_hg->MkOutParSearch1d(argval->GetOutdir(),
//////                                      argval->GetOutfileHead(),
//////                                      "short");
//////        fit_stat_hg->PrintErrByParSearch1d(stdout);
//////        fit_stat_hg->PrintErrByParSearch1d(fp_log);
//////    }
//////    if("none" != argval->GetChi2contPar()){
//////        fit_stat_hg->MkOutParSearch2d(argval->GetOutdir(),
//////                                      argval->GetOutfileHead(),
//////                                      "short",
//////                                      root_tool);
//////        fit_stat_hg->PrintErrByParSearch2d(stdout);
//////        fit_stat_hg->PrintErrByParSearch2d(fp_log);
//////    }
//////
//////    
//////    //// dump likelihood ratio (delta-c = c_sim - c_best)
//////    //double lr = fit_stat_hg->GetFitStatInit()->GetFcnMin()
//////    //    - fit_stat_hg->GetFitStat()->GetFcnMin();
//////    //fprintf(fp_log, "likelihood ratio = delta-c = c_sim - c_best = %e\n", lr);
//////    //printf("likelihood ratio = delta-c = c_sim - c_best = %e\n", lr);
//////
//////
//////    //
//////    // calc goodness-of-fit
//////    //
//////    printf("# --- calc goodness-of-fit ---\n");
//////    double p_value = GetGoodnessOfFit(hd1d_evt_fill,
//////                                      fit_stat_hg,
//////                                      func);
//////    printf("goodness-of-fit (p_value) = %e\n", p_value);
//////    printf("# === calc goodness-of-fit ===\n");
//////    
////
////    printf("%s: end.\n", argval->GetProgname().c_str());
//////    
//////    delete argval;
//////    delete da1d_sel;
//////    delete hd1d_evt_fill;
//////    delete hd1d_evt_fill_rate;
//////    delete hd1d_mask;
//////    delete func;
//////    delete fitparam;
//////    delete chi2plot_par;
//////    delete chi2plot_cont_par;
//////    delete minfcn;
//////    delete fit_stat_hg;
//////    delete plot_conf;
//////    fclose(fp_log);


    return status;
}
















// func_rate : count rate function (c/sec)
double GetGoodnessOfFit(const HistData1d* const hd1d_evt_fill,
                        const FitStatHG* const fit_stat_hg,
                        const MirFunc* const func_rate)
{
    double* xval_arr = NULL;
    long nbin_xval = 0;
    hd1d_evt_fill->GenXvalArr(&xval_arr,
                              &nbin_xval);
    const double* par_arr = fit_stat_hg->GetFitParamBest()->GetPar();
    double* oval_gd2d_arr = new double [nbin_xval];
    for(long ibin = 0; ibin < nbin_xval; ibin ++){
        double val_in[1];
        val_in[0] = xval_arr[ibin];
        oval_gd2d_arr[ibin] = func_rate->Eval(val_in, par_arr) * hd1d_evt_fill->GetBinWidth();
    }
    GraphData2d* gd2d_func = new GraphData2d;
    gd2d_func->Init();
    gd2d_func->SetXvalArrDbl(nbin_xval, xval_arr);
    gd2d_func->SetOvalArrDbl(nbin_xval, oval_gd2d_arr);
    gd2d_func->SetFlagXvalSorted(1);
    MirFunc* func_gd2d_for_count = new G2dFunc;
    dynamic_cast<G2dFunc*>(func_gd2d_for_count)->InitSetGd2d(gd2d_func);
        
    MinFcn* minfcn_tmp = MinFcnOne::GenMinFcnOne("CstatDeltaPhysFcn1d", func_gd2d_for_count,
                                                 hd1d_evt_fill->GetNbinX(),
                                                 xval_arr,
                                                 NULL,
                                                 hd1d_evt_fill->GetOvalArrDbl(),
                                                 NULL, NULL, NULL,
                                                 NULL, NULL);
    double fcn_min = minfcn_tmp->Eval(0, NULL);
    long ndata_valid = minfcn_tmp->GetNdataValid();
    int npar_free = fit_stat_hg->GetFitParamBest()->GetNparFree();
    long ndf = ndata_valid - npar_free;
    double p_value = TMath::Prob(fcn_min, ndf);

    //printf("fcn_min = %e\n", fcn_min);        
    //printf("ndata_valid = %ld\n", ndata_valid);        
    //printf("npar_free = %d\n", npar_free);       
    //printf("ndf = %ld\n", ndf);                
    // printf("goodness-of-fit (p_value) = %e\n", p_value);

    delete [] xval_arr;
    delete [] oval_gd2d_arr;
    delete gd2d_func;
    delete func_gd2d_for_count;
    delete minfcn_tmp;

    return p_value;
}
    

