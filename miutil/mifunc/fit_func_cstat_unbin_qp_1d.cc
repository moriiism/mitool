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

#include "func_user.h"
#include "arg_fit_func_cstat_unbin_qp_1d.h"

// func_rate : count rate function (c/sec)
double GetGoodnessOfFit(const HistData1d* const hd1d_evt_fill,
                        const FitStatHG* const fit_stat_hg,
                        const MirFunc* const func_rate);

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status = kRetNormal;
    
    ArgValFitFuncCstatUnbinQp1d* argval = new ArgValFitFuncCstatUnbinQp1d;
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
    DataArray1d* da1d = new DataArrayNerr1d;
    da1d->Load(argval->GetDataFile());
    da1d->Sort();
    MirQdpTool::MkQdpMode2(da1d,
                            argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_da1d.qdp",
                            "", 0.0);

    //
    // hist of mask
    //
    HistData1d* hd1d_mask = new HistDataNerr1d;
    if("none" == argval->GetHistMask()){
        printf("not supported.\n");
        abort();
    } else if("hist_info=" == argval->GetHistMask().substr(0, 10)){
        string hist_info_file = argval->GetHistMask().substr(10);
        HistInfo1d* hi1d = new HistInfo1d;
        hi1d->Load(hist_info_file);
        hd1d_mask->Init(hi1d);
        hd1d_mask->SetConst(1.0);
        delete hi1d;
    } else {
        hd1d_mask->Load(argval->GetHistMask());
    }
    MirQdpTool::MkQdp(hd1d_mask,
                       argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_hd1d_mask.qdp",
                       "x,y");

    //
    // extract data according to hd1d_mask
    //
    DataArray1d* da1d_sel = new DataArrayNerr1d;
    vector<double> da1d_sel_vec;
    for(long idata = 0; idata < da1d->GetNdata(); idata ++){
        double xval = da1d->GetValElm(idata);
        if(1 == hd1d_mask->GetOvalElmAtX( xval )){
            da1d_sel_vec.push_back(xval);
        }
    }
    da1d_sel->Init(da1d_sel_vec.size());
    da1d_sel->SetVal(da1d_sel_vec);
    MirQdpTool::MkQdpMode2(da1d_sel,
                            argval->GetOutdir() + "/" + argval->GetOutfileHead() + "_da1d_sel.qdp",
                            "", 0.0);
    delete da1d;



    HistDataSerr1d* hd1d_evt_fill = new HistDataSerr1d;
    hd1d_evt_fill->Init(hd1d_mask->GetNbinX(),
                        hd1d_mask->GetXvalLo(),
                        hd1d_mask->GetXvalUp());
    for(long idata = 0; idata < da1d_sel->GetNdata(); idata++){
        hd1d_evt_fill->Fill(da1d_sel->GetValElm(idata));
    }
    HistDataSerr1d* hd1d_evt_fill_rate = new HistDataSerr1d;
    HistData1dOpe::GetScale(hd1d_evt_fill, 1./hd1d_evt_fill->GetHi1d()->GetBinWidth(), 0.0,
                            hd1d_evt_fill_rate);

    //
    // function & parfile
    //
    long nfunc;
    string* func_list_line_arr = NULL;
    string* func_name_arr = NULL;
    string* par_file_arr = NULL;
    int* styleid_arr = NULL;
    int* colorid_arr = NULL;
    double* plot_lo_arr = NULL;
    double* plot_up_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncParList(), &func_list_line_arr, &nfunc);
    func_name_arr = new string [nfunc];
    par_file_arr = new string [nfunc];
    styleid_arr = new int [nfunc];
    colorid_arr = new int [nfunc];
    plot_lo_arr = new double [nfunc];
    plot_up_arr = new double [nfunc];    
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        int ncolumn = MiStr::GetNcolumn(func_list_line_arr[ifunc]);
        if(6 != ncolumn){
            MPrintErr("ncolumn != 6");
            abort();
        }
        char func_name_tmp[kLineSize];
        char par_file_tmp[kLineSize];
        sscanf(func_list_line_arr[ifunc].c_str(), "%s %s %d %d %lf %lf",
               func_name_tmp, par_file_tmp,
               &styleid_arr[ifunc], &colorid_arr[ifunc],
               &plot_lo_arr[ifunc], &plot_up_arr[ifunc]);        
        func_name_arr[ifunc] = func_name_tmp;
        par_file_arr[ifunc] = par_file_tmp;

        printf("func_name, par_file, style, color, lo, up  "
               " = %s  %s %d %d %e %e\n",
               func_name_arr[ifunc].c_str(),
               par_file_arr[ifunc].c_str(),
               styleid_arr[ifunc], colorid_arr[ifunc],
               plot_lo_arr[ifunc], plot_up_arr[ifunc]);
    }
    MiIolib::DelReadFile(func_list_line_arr);

    //
    // plot configuration
    //
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    
    
    MirFunc** func_arr = new MirFunc* [nfunc];
    MirFuncPar** func_par_arr = new MirFuncPar* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_arr[ifunc] = FuncUser::GenFunc(func_name_arr[ifunc]);
        func_par_arr[ifunc] = new MirFuncPar;
        func_par_arr[ifunc]->Load(par_file_arr[ifunc]);
    }


    //
    // solve by QP
    //
    long nbin_hd1d_evt_fill = 0;
    double* xval_arr_hd1d_evt_fill = NULL;
    hd1d_evt_fill->GenXvalArr(&xval_arr_hd1d_evt_fill,
                              &nbin_hd1d_evt_fill);
    double* par_arr_best_lsqp = NULL;
    double chi2_min = 0.0;
    double aic = 0.0;
    double bic = 0.0;
    MimLS::GenLeastSquarePoissonQuadProgPlus(hd1d_evt_fill->GetNbinX(),
                                             xval_arr_hd1d_evt_fill,
                                             hd1d_evt_fill->GetOvalArr()->GetVal(),
                                             nfunc,
                                             func_arr,
                                             func_par_arr,
                                             &par_arr_best_lsqp,
                                             &chi2_min,
                                             &aic,
                                             &bic);

    //
//    // solve by SVD
//    //
//    double* par_arr_best_svd = NULL;
//    double* par_serr_arr_svd = NULL;
//    double** par_cov_arr_svd = NULL;
//    MimLS::GenLeastSquarePoissonSvd(hd1d_evt_fill->GetNbinX(),
//                                     xval_arr_hd1d_evt_fill,
//                                     hd1d_evt_fill->GetOvalArrDbl(),
//                                     nfunc,
//                                     func_arr,
//                                     func_par_arr,
//                                     &par_arr_best_svd,
//                                     &par_serr_arr_svd,
//                                     &par_cov_arr_svd);
//    delete [] xval_arr_hd1d_evt_fill;

    //
    // fit result of QP & SVD
    //

    //
    // count rate function (c/sec)
    //
    LinCombFunc* func_lincomb = new LinCombFunc;
    func_lincomb->InitSet(nfunc, func_arr);
    int ipar_tot = 0;
    double* par_func_lincomb = new double [func_lincomb->GetNpar()];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        for(int ipar = 0; ipar < func_par_arr[ifunc]->GetNpar(); ipar ++){
            par_func_lincomb[ipar_tot] = func_par_arr[ifunc]->GetParElm(ipar);
            ipar_tot ++;
        }
    }
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        par_func_lincomb[ipar_tot] = par_arr_best_lsqp[ifunc] / hd1d_evt_fill->GetHi1d()->GetBinWidth();
        ipar_tot ++;
    }
    
    for(int ipar = 0; ipar < func_lincomb->GetNpar(); ipar ++){
        printf("par_func_lincomb[%d] = %e\n", ipar, par_func_lincomb[ipar]);
    }

    FitStatHG::MkOutFitPlot(hd1d_evt_fill_rate, func_lincomb,
                            par_func_lincomb,
                            argval->GetNpointFunc(),
                            argval->GetOutdir(),
                            argval->GetOutfileHead() + "_qp",
                            plot_conf);

    //
//    // fit by Minuit
//    //
//    FitParam* fitparam = new FitParam;
//    fitparam->Init(func_lincomb->GetNpar());
//    ipar_tot = 0;
//    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
//        for(int ipar = 0; ipar < func_par_arr[ifunc]->GetNpar(); ipar ++){
//            char par_name_tmp[kLineSize];
//            sprintf(par_name_tmp, "%2.2d_%s_%s_fix",
//                    ifunc,
//                    func_name_arr[ifunc].c_str(), 
//                    func_par_arr[ifunc]->GetParNameElm(ipar).c_str());
//            fitparam->SetInElm(ipar_tot,
//                               par_name_tmp,
//                               func_par_arr[ifunc]->GetParElm(ipar),
//                               -1.0,
//                               "none",
//                               "none",
//                               0,
//                               ifunc);
//            ipar_tot ++;
//        }
//    }
//    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
//        char par_name_tmp[kLineSize];
//        sprintf(par_name_tmp, "%2.2d_%s_norm", ifunc, func_name_arr[ifunc].c_str());
//        fitparam->SetInElm(ipar_tot,
//                           par_name_tmp,
//                           par_arr_best_lsqp[ifunc] / hd1d_evt_fill->GetBinWidth(),
//                           par_serr_arr_svd[ifunc] / hd1d_evt_fill->GetBinWidth() / 10.0,
//                           "0.0",
//                           "1.e5",
//                           0,
//                           ifunc);
//        ipar_tot ++;
//    }
//    fitparam->Print(stdout);
//
////    //
////    // chi2, chi2cont
////    //
////    
////    Chi2PlotPar* chi2plot_par = NULL;
////    Chi2PlotContPar* chi2plot_cont_par = NULL;
////    if("none" != argval->GetChi2par()){
////        chi2plot_par = new Chi2PlotPar;
////        chi2plot_par->Load(argval->GetChi2par());
////        chi2plot_par->SetIndex1Arr(fitparam);
////        chi2plot_par->Print(stdout);
////        chi2plot_par->Print(fp_log);
////    }
////    if("none" != argval->GetChi2contPar()){
////        chi2plot_cont_par = new Chi2PlotContPar;
////        chi2plot_cont_par->Load(argval->GetChi2contPar());
////        chi2plot_cont_par->SetIndex2Arr(fitparam);
////        chi2plot_cont_par->Print(stdout);
////        chi2plot_cont_par->Print(fp_log);
////    }
//
//
//    //
//    // minfcn
//    //
//    MinFcn* minfcn = NULL;
//    minfcn = MinFcnOne::GenMinFcnOne("CstatUnbinPhysFcn1d",
//                                     func_lincomb,
//                                     da1d_sel->GetNdata(), da1d_sel->GetVal(), NULL,
//                                     NULL, NULL, NULL, NULL,
//                                     hd1d_mask, NULL);
//    //
//    // fit
//    //
//    double value_in_sigma_or_cl = 1.0;
//    string sigma_or_cl = "sigma";
//    int as_npar = 1;
//    double tolerance = 0.1;
//    FitStatHG* fit_stat_hg = NULL;
//    int maxfcn = 0;
//    FitFunc::GenFitStatHG(stdout, minfcn, fitparam,
//                          NULL, NULL,
//                          &fit_stat_hg,
//                          value_in_sigma_or_cl, sigma_or_cl, as_npar,
//                          tolerance, maxfcn);
//    //
//    // fit result
//    //
//    fit_stat_hg->PrintInfo(stdout);
//    fit_stat_hg->PrintInfo(fp_log);
//    FitStatHG::MkOutFitPlot(hd1d_evt_fill_rate, func_lincomb,
//                            fit_stat_hg->GetFitParamBest()->GetPar(),
//                            argval->GetNpointFunc(),
//                            argval->GetOutdir(),
//                            argval->GetOutfileHead() + "_minuit",
//                            plot_conf);
//    
////    if("none" != argval->GetChi2par()){
////        fit_stat_hg->MkOutParSearch1d(argval->GetOutdir(),
////                                      argval->GetOutfileHead(),
////                                      "short");
////        fit_stat_hg->PrintErrByParSearch1d(stdout);
////        fit_stat_hg->PrintErrByParSearch1d(fp_log);
////    }
////    if("none" != argval->GetChi2contPar()){
////        fit_stat_hg->MkOutParSearch2d(argval->GetOutdir(),
////                                      argval->GetOutfileHead(),
////                                      "short",
////                                      root_tool);
////        fit_stat_hg->PrintErrByParSearch2d(stdout);
////        fit_stat_hg->PrintErrByParSearch2d(fp_log);
////    }
////
////    
////    //// dump likelihood ratio (delta-c = c_sim - c_best)
////    //double lr = fit_stat_hg->GetFitStatInit()->GetFcnMin()
////    //    - fit_stat_hg->GetFitStat()->GetFcnMin();
////    //fprintf(fp_log, "likelihood ratio = delta-c = c_sim - c_best = %e\n", lr);
////    //printf("likelihood ratio = delta-c = c_sim - c_best = %e\n", lr);
////
////
////    //
////    // calc goodness-of-fit
////    //
////    printf("# --- calc goodness-of-fit ---\n");
////    double p_value = GetGoodnessOfFit(hd1d_evt_fill,
////                                      fit_stat_hg,
////                                      func);
////    printf("goodness-of-fit (p_value) = %e\n", p_value);
////    printf("# === calc goodness-of-fit ===\n");
////    
//
//    printf("%s: end.\n", argval->GetProgname().c_str());
////    
////    delete argval;
////    delete da1d_sel;
////    delete hd1d_evt_fill;
////    delete hd1d_evt_fill_rate;
////    delete hd1d_mask;
////    delete func;
////    delete fitparam;
////    delete chi2plot_par;
////    delete chi2plot_cont_par;
////    delete minfcn;
////    delete fit_stat_hg;
////    delete plot_conf;
////    fclose(fp_log);
//
    
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
        oval_gd2d_arr[ibin] = func_rate->Eval(val_in, par_arr) * hd1d_evt_fill->GetHi1d()->GetBinWidth();
    }
    GraphData2d* gd2d_func = new GraphDataNerr2d;
    gd2d_func->Init(nbin_xval);
    gd2d_func->SetXvalArr(nbin_xval, xval_arr);
    gd2d_func->SetOvalArr(nbin_xval, oval_gd2d_arr);
    gd2d_func->SetFlagXvalSorted(1);
    MirFunc* func_gd2d_for_count = new Gd2dFunc;
    dynamic_cast<Gd2dFunc*>(func_gd2d_for_count)->InitSetGd2d(gd2d_func);
        
    MinFcn* minfcn_tmp = MinFcnOne::GenMinFcnOne("CstatDeltaPhysFcn1d", func_gd2d_for_count,
                                                 hd1d_evt_fill->GetNbinX(),
                                                 xval_arr,
                                                 NULL,
                                                 hd1d_evt_fill->GetOvalArr()->GetVal(),
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
    

