#include "mim_fitfunc.h"

//
// FitFunc
//

ROOT::Minuit2::FunctionMinimum FitFunc::GenExecFit(MinFcn* const minfcn,
                                                   const FitParam* const fit_param,
                                                   FitStat** const fit_stat_ptr,
                                                   double value_in_sigma_or_cl,
                                                   string sigma_or_cl,
                                                   int as_npar,
                                                   double tolerance,
                                                   int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }
    ROOT::Minuit2::MnUserParameters upar;
    for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
        if("none" != fit_param->GetParLoStrElm(ipar) &&
           "none" != fit_param->GetParUpStrElm(ipar)){
            double par_lo = atof(fit_param->GetParLoStrElm(ipar).c_str());
            double par_up = atof(fit_param->GetParUpStrElm(ipar).c_str());            
            upar.Add(fit_param->GetParNameElm(ipar),
                     fit_param->GetParInitElm(ipar),
                     fit_param->GetParSerrInitElm(ipar),
                     par_lo, par_up);
        } else {
            upar.Add(fit_param->GetParNameElm(ipar),
                     fit_param->GetParInitElm(ipar),
                     fit_param->GetParSerrInitElm(ipar));
        }
        if(fit_param->GetParSerrInitElm(ipar) < 0){
            upar.Fix(ipar);
        }
    }
    double up_minfcn = MinFcn::GetUpMinfcn(value_in_sigma_or_cl,
                                           sigma_or_cl,
                                           as_npar);
    minfcn->SetErrorDef(up_minfcn);
    int strategy = 1;
    std::cout << upar << std::endl;

    ROOT::Minuit2::MnMigrad migrad(*minfcn, upar, strategy);
    ROOT::Minuit2::FunctionMinimum function_minimum = migrad(maxfcn, tolerance);
    ROOT::Minuit2::MnUserParameters upar_out = migrad.Parameters();
    
    //
    // check best par whether it is pegged or not
    //
    int* flag_peg_arr = new int [fit_param->GetNpar()];
    int npeg = 0;
    for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
        if("none" != fit_param->GetParLoStrElm(ipar) &&
           "none" != fit_param->GetParUpStrElm(ipar)) {
            double par_lo_tmp = atof(fit_param->GetParLoStrElm(ipar).c_str());
            double par_up_tmp = atof(fit_param->GetParUpStrElm(ipar).c_str());
            flag_peg_arr[ipar] = 0;
            double par_tmp      = upar_out.Params().at(ipar);
            double par_serr_tmp = upar_out.Errors().at(ipar);
            if(par_tmp - par_serr_tmp < par_lo_tmp ||
               par_up_tmp < par_tmp + par_serr_tmp   ){
                flag_peg_arr[ipar] = 1;
                npeg ++;
            }
        }
    }
    if(0 < g_flag_verbose){
        if(npeg > 0){
            for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
                if(1 == flag_peg_arr[ipar]){
                    char msg[kLineSize];
                    sprintf(msg, "pegged(%d): %s",
                            ipar, fit_param->GetParNameElm(ipar).c_str());
                    MPrintWarn(msg);
                }
            }
        }
    }

    //
    // If fitting is not valid, fit again by simplex, and again by mnscan
    //
    if(1 != function_minimum.IsValid()){
        if(0 < g_flag_verbose){
            MPrintInfo("fitting by simplex and migrad start ...");
        }
        ROOT::Minuit2::MnSimplex simplex(*minfcn, upar, strategy);
        function_minimum = migrad(maxfcn, tolerance);
    }

    if(1 != function_minimum.IsValid()){
        if(0 < g_flag_verbose){
            MPrintInfo("fitting by mnscan and migrad start ...");
        }
        ROOT::Minuit2::MnScan mnscan(*minfcn, upar, strategy);
        function_minimum = migrad(maxfcn, tolerance);
    }
    upar_out = migrad.Parameters();
    FitStat* fit_stat = new FitStat;

    fit_stat->Init();
    fit_stat->Set(minfcn, fit_param, function_minimum, upar_out);
    *fit_stat_ptr = fit_stat;
    
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
    return function_minimum;
}


ROOT::Minuit2::FunctionMinimum FitFunc::GenExecFitSimplex(MinFcn* const minfcn,
                                                          const FitParam* const fit_param,
                                                          FitStat** const fit_stat_ptr,
                                                          double value_in_sigma_or_cl,
                                                          string sigma_or_cl,
                                                          int as_npar,
                                                          double tolerance,
                                                          int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }
    ROOT::Minuit2::MnUserParameters upar;
    for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
        if("none" != fit_param->GetParLoStrElm(ipar) &&
           "none" != fit_param->GetParUpStrElm(ipar)){
            double par_lo = atof(fit_param->GetParLoStrElm(ipar).c_str());
            double par_up = atof(fit_param->GetParUpStrElm(ipar).c_str());            
            upar.Add(fit_param->GetParNameElm(ipar),
                     fit_param->GetParInitElm(ipar),
                     fit_param->GetParSerrInitElm(ipar),
                     par_lo, par_up);
        } else {
            upar.Add(fit_param->GetParNameElm(ipar),
                     fit_param->GetParInitElm(ipar),
                     fit_param->GetParSerrInitElm(ipar));
        }
        if(fit_param->GetParSerrInitElm(ipar) < 0){
            upar.Fix(ipar);
        }
    }
    double up_minfcn = MinFcn::GetUpMinfcn(value_in_sigma_or_cl,
                                           sigma_or_cl,
                                           as_npar);
    minfcn->SetErrorDef(up_minfcn);
    int strategy = 1;
    ROOT::Minuit2::MnSimplex simplex(*minfcn, upar, strategy);
    ROOT::Minuit2::FunctionMinimum function_minimum = simplex(maxfcn, tolerance);
    ROOT::Minuit2::MnUserParameters upar_out = simplex.Parameters();

    FitStat* fit_stat = new FitStat;
    fit_stat->Init();
    fit_stat->Set(minfcn, fit_param, function_minimum, upar_out);
    *fit_stat_ptr = fit_stat;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }    
    return function_minimum;
}


void FitFunc::GetAsymErr(MinFcn* const minfcn,
                         const FitParam* const fit_param,
                         ROOT::Minuit2::FunctionMinimum function_minimum, // migrad result
                         FitStat* const fit_stat_out,
                         double value_in_sigma_or_cl,
                         string sigma_or_cl,
                         double tolerance,
                         int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }
    int as_npar = 1;
    double up_minfcn = MinFcn::GetUpMinfcn(value_in_sigma_or_cl,
                                           sigma_or_cl,
                                           as_npar);
    minfcn->SetErrorDef(up_minfcn);
    ROOT::Minuit2::MnUserParameterState upar_result = function_minimum.UserState();

    pair<double,double>* err_asym = new pair<double,double>[fit_param->GetNpar()];
    int* valid_terr_minus_arr = new int [fit_param->GetNpar()];
    int* valid_terr_plus_arr  = new int [fit_param->GetNpar()];
    for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
        valid_terr_minus_arr[ipar] = 0;
        valid_terr_plus_arr[ipar]  = 0;
    }

    for(int ipar = 0; ipar < fit_param->GetNpar(); ipar ++){
        if(1 == fit_param->GetFlagCalcTerrElm(ipar)){
            if(fit_param->GetParSerrInitElm(ipar) < 0){
                err_asym[ipar].first = 0.0;
                err_asym[ipar].second = 0.0;
            } else {
                ROOT::Minuit2::MnMinos minos(*minfcn, function_minimum);
                ROOT::Minuit2::MinosError minos_err = minos.Minos(ipar, maxfcn, tolerance);

                // minos result check
                err_asym[ipar] = minos_err();
                valid_terr_minus_arr[ipar] = minos_err.LowerValid();
                valid_terr_plus_arr[ipar]  = minos_err.UpperValid();
            }
            fit_stat_out->SetParTerrElm(ipar, err_asym[ipar].first, err_asym[ipar].second);
            fit_stat_out->SetValidTerrElm(ipar,
                                          valid_terr_minus_arr[ipar],
                                          valid_terr_plus_arr[ipar]);
            printf("GetAsymErr: ipar = %d: minos err- / err+ (valid-/valid+): %e / %e (%d/%d)\n",
                   ipar, 
                   err_asym[ipar].first, err_asym[ipar].second,
                   valid_terr_minus_arr[ipar], valid_terr_plus_arr[ipar]);
        }
    }
    delete [] err_asym;
    delete [] valid_terr_minus_arr;
    delete [] valid_terr_plus_arr;
}

double FitFunc::GetErrBySecant(MinFcn* const minfcn,
                               const FitParam* const fit_param,
                               int ipar, double par_best,
                               double par_init_lo, double par_init_up,
                               double minfcn_aim,
                               double minfcn_diff_precision,
                               double tolerance,
                               int maxfcn)
{
    // Instead of minos, this tool search one side error
    // by secant method for the minfcn (minimized function: chi2 or likelihood, etc.)

    FitStat* fit_stat_this = NULL;
    FitParam* fit_param_this = new FitParam;
    fit_param_this->Copy(fit_param);
    int iterate = 0;
    double par_root = par_init_lo;
    double par_root0 = par_init_lo;
    double par_root1 = par_init_up;

    double value_in_sigma_or_cl_this = 1.0;
    string sigma_or_cl_this = "sigma";
    int as_npar_this = 1;
    fit_param_this->FixPar(ipar, par_root);
    GenExecFit(minfcn, fit_param_this, &fit_stat_this,
               value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar_this,
               tolerance, maxfcn);
    double minfcn_diff = fit_stat_this->GetFcnMin() - minfcn_aim;
    delete fit_stat_this; fit_stat_this = NULL;

    while(fabs(minfcn_diff) >  minfcn_diff_precision){
        fit_param_this->FixPar(ipar, par_root0);
        GenExecFit(minfcn, fit_param_this, &fit_stat_this,
                   value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar_this,
                   tolerance, maxfcn);
        double minfcn_diff0 = fit_stat_this->GetFcnMin() - minfcn_aim;
        delete fit_stat_this; fit_stat_this = NULL;

        fit_param_this->FixPar(ipar, par_root1);
        GenExecFit(minfcn, fit_param_this, &fit_stat_this,
                   value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar_this,
                   tolerance, maxfcn);
        double minfcn_diff1 = fit_stat_this->GetFcnMin() - minfcn_aim;
        delete fit_stat_this; fit_stat_this = NULL;

        par_root = (par_root0 * minfcn_diff1 - par_root1 * minfcn_diff0) / (minfcn_diff1 - minfcn_diff0);
        par_root0 = par_root1;
        par_root1 = par_root;

        fit_param_this->FixPar(ipar, par_root);
        GenExecFit(minfcn, fit_param_this, &fit_stat_this,
                   value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar_this,
                   tolerance, maxfcn);
        minfcn_diff = fit_stat_this->GetFcnMin() - minfcn_aim;
        delete fit_stat_this; fit_stat_this = NULL;        

        if(0 < g_flag_verbose){
            char msg[kLineSize];
            sprintf(msg, "%d: par_root = %e", iterate, par_root);
            MPrintInfo(msg);
        }
        iterate ++;
    }
    delete fit_param_this;
    return par_root - par_best;
}


void FitFunc::GenFitStatForParSearch1d(MinFcn* const minfcn, const FitParam* const fit_param,
                                       const Chi2PlotPar* const chi2plot_par,
                                       FitStat**** const fit_stat_arr_ptr,
                                       double tolerance,
                                       int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start ...");
    }

    int npar = chi2plot_par->GetNpar();
    FitStat*** fit_stat_arr = new FitStat** [npar];
    for(int ipar = 0; ipar < npar; ipar++){
        int nstep = chi2plot_par->GetNstepElm(ipar);
        fit_stat_arr[ipar] = new FitStat* [nstep];
        for(int istep = 0; istep < nstep; istep ++){
            fit_stat_arr[ipar][istep] = new FitStat;
        }
    }

    for(int ipar = 0; ipar < npar; ipar++){
        int index       = chi2plot_par->GetIndexElm(ipar);
        int nstep       = chi2plot_par->GetNstepElm(ipar);

        FitParam* fit_param_this = new FitParam;
        fit_param_this->Copy(fit_param);

        for(int istep = 0; istep < nstep; istep++){
            printf("%d  ", istep);
            fflush(stdout);
            double par_plot = chi2plot_par->GetParVal(ipar, istep);
            fit_param_this->FixPar(index, par_plot);
            if(0 < g_flag_verbose){
                char msg[kLineSize];
                sprintf(msg, "ipar = %2.2d (npar = %2.2d): istep = %3.3d (nstep = %3.3d)",
                        ipar, npar, istep, nstep); 
                MPrintInfo(msg);
            }

            FitStat* fit_stat = NULL;
            double value_in_sigma_or_cl_this = 1.0;
            string sigma_or_cl_this = "sigma";
            int as_npar = 1;
            ROOT::Minuit2::FunctionMinimum function_minimum = GenExecFit(minfcn, fit_param_this, &fit_stat,
                                                                         value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar,
                                                                         tolerance, maxfcn);
            fit_stat_arr[ipar][istep]->Copy(fit_stat);
            delete fit_stat;
        }
        printf("\n");
        fflush(stdout);
        delete fit_param_this;
    }

    *fit_stat_arr_ptr = fit_stat_arr;
    
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void FitFunc::DelFitStatForParSearch1d(const Chi2PlotPar* const chi2plot_par,
                                       FitStat*** fit_stat_arr)
{
    int npar = chi2plot_par->GetNpar();
    for(int ipar = 0; ipar < npar; ipar++){
        int nstep = chi2plot_par->GetNstepElm(ipar);
        for(int istep = 0; istep < nstep; istep ++){
            delete fit_stat_arr[ipar][istep]; fit_stat_arr[ipar][istep] = NULL;
        }
        delete [] fit_stat_arr[ipar]; fit_stat_arr[ipar] = NULL;
    }
    delete [] fit_stat_arr; fit_stat_arr = NULL;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void FitFunc::GenParSearch1d(const FitStat* const* const* const fit_stat_arr,
                             const Chi2PlotPar* const chi2plot_par,
                             HistData1d*** const hist_chi2_arr_ptr,
                             HistData1d*** const hist_valid_arr_ptr,
                             HistData1d*** const hist_edm_arr_ptr,
                             HistData1d*** const hist_flag_bad_neg_arr_ptr,
                             HistData1d**** const hist_index1_arr_ptr)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start ...");
    }

    int npar = chi2plot_par->GetNpar();
    HistData1d** hist_chi2_arr    = new HistData1d* [npar];
    HistData1d** hist_valid_arr   = new HistData1d* [npar];
    HistData1d** hist_edm_arr     = new HistData1d* [npar];
    HistData1d** hist_flag_bad_neg_arr = new HistData1d* [npar];
    for(int ipar = 0; ipar < npar; ipar++){
        char title_tail[kLineSize];
        int index_par = chi2plot_par->GetIndexElm(ipar);
        sprintf(title_tail, "%2.2d", index_par);
            
        char chi2_title[kLineSize];
        sprintf(chi2_title, "chi2_%s", title_tail);
        hist_chi2_arr[ipar] = new HistDataNerr1d(chi2_title);

        char valid_title[kLineSize];
        sprintf(valid_title, "valid_%s", title_tail);
        hist_valid_arr[ipar] = new HistDataNerr1d(valid_title);

        char edm_title[kLineSize];
        sprintf(edm_title, "edm_%s", title_tail);
        hist_edm_arr[ipar] = new HistDataNerr1d(edm_title);

        char flag_bad_neg_title[kLineSize];
        sprintf(flag_bad_neg_title, "flag_bad_neg_%s", title_tail);
        hist_flag_bad_neg_arr[ipar] = new HistDataNerr1d(flag_bad_neg_title);
    }

    for(int ipar = 0; ipar < npar; ipar++){
        int nstep     = chi2plot_par->GetNstepElm(ipar);
        string par_lo_str = chi2plot_par->GetLoStrElm(ipar);
        string par_up_str = chi2plot_par->GetUpStrElm(ipar);
        if("none" == par_lo_str ||
           "none" == par_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par_lo = atof(par_lo_str.c_str());
        double par_up = atof(par_up_str.c_str());
        
        double* chi2_arr   = new double [nstep];
        double* valid_arr  = new double [nstep];
        double* edm_arr    = new double [nstep];
        double* flag_bad_neg_arr = new double [nstep];
      
        for(int istep = 0; istep < nstep; istep++){
            chi2_arr[istep]   = fit_stat_arr[ipar][istep]->GetFcnMin();
            valid_arr[istep]  = fit_stat_arr[ipar][istep]->GetValid();
            edm_arr[istep]    = fit_stat_arr[ipar][istep]->GetEdm();
            flag_bad_neg_arr[istep] = fit_stat_arr[ipar][istep]->GetFlagBadNeg();

        }
        hist_chi2_arr[ipar]->Init(nstep, par_lo, par_up);
        hist_chi2_arr[ipar]->SetOvalArr(nstep, chi2_arr);
        hist_valid_arr[ipar]->Init(nstep, par_lo, par_up);
        hist_valid_arr[ipar]->SetOvalArr(nstep, valid_arr);
        hist_edm_arr[ipar]->Init(nstep, par_lo, par_up);
        hist_edm_arr[ipar]->SetOvalArr(nstep, edm_arr);
        hist_flag_bad_neg_arr[ipar]->Init(nstep, par_lo, par_up);
        hist_flag_bad_neg_arr[ipar]->SetOvalArr(nstep, flag_bad_neg_arr);
        
        delete [] chi2_arr;
        delete [] valid_arr;
        delete [] edm_arr;
        delete [] flag_bad_neg_arr;
    }

    HistData1d*** hist_index1_arr  = new HistData1d** [npar];
    for(int ipar = 0; ipar < npar; ipar++){
        char title_tail[kLineSize];
        int index_par = chi2plot_par->GetIndexElm(ipar);
        sprintf(title_tail, "%2.2d", index_par);
        int num_index1 = chi2plot_par->GetNumIndex1Elm(ipar);
        hist_index1_arr[ipar] = new HistData1d* [num_index1];
        for(int inum = 0; inum < num_index1; inum ++){
            int index1 = chi2plot_par->GetIndex1ArrElm(ipar, inum);
            char index1_title[kLineSize];
            sprintf(index1_title, "index1_%s_%2.2d", title_tail, index1);
            hist_index1_arr[ipar][inum] = new HistDataNerr1d(index1_title);
        }
    }

    for(int ipar = 0; ipar < npar; ipar++){
        int nstep         = chi2plot_par->GetNstepElm(ipar);
        string par_lo_str = chi2plot_par->GetLoStrElm(ipar);
        string par_up_str = chi2plot_par->GetUpStrElm(ipar);
        if("none" == par_lo_str ||
           "none" == par_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par_lo = atof(par_lo_str.c_str());
        double par_up = atof(par_up_str.c_str());
        int num_index1 = chi2plot_par->GetNumIndex1Elm(ipar);
        for(int inum = 0; inum < num_index1; inum ++){
            int index1 = chi2plot_par->GetIndex1ArrElm(ipar, inum);
            double* index1_arr = new double [nstep];
            for(int istep = 0; istep < nstep; istep++){
                index1_arr[istep] = fit_stat_arr[ipar][istep]->GetFitParam()->GetParElm(index1);
            }
            hist_index1_arr[ipar][inum]->Init(nstep, par_lo, par_up);
            hist_index1_arr[ipar][inum]->SetOvalArr(nstep, index1_arr);
            delete [] index1_arr;
        }
    }
    
    *hist_chi2_arr_ptr = hist_chi2_arr;
    *hist_valid_arr_ptr = hist_valid_arr;
    *hist_edm_arr_ptr = hist_edm_arr;
    *hist_flag_bad_neg_arr_ptr = hist_flag_bad_neg_arr;
    *hist_index1_arr_ptr = hist_index1_arr;
    
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void FitFunc::DelParSearch1d(const Chi2PlotPar* const chi2plot_par,
                             HistData1d** hist_chi2_arr,
                             HistData1d** hist_valid_arr,
                             HistData1d** hist_edm_arr,
                             HistData1d** hist_flag_bad_neg_arr,
                             HistData1d*** hist_index1_arr)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start ...");
    }

    int npar = chi2plot_par->GetNpar();
    for(int ipar = 0; ipar < npar; ipar++){
        delete hist_chi2_arr[ipar];   hist_chi2_arr[ipar]  = NULL;
        delete hist_valid_arr[ipar];  hist_valid_arr[ipar] = NULL;
        delete hist_edm_arr[ipar];    hist_edm_arr[ipar]   = NULL;
        delete hist_flag_bad_neg_arr[ipar];  hist_flag_bad_neg_arr[ipar] = NULL;

        int num_index1 = chi2plot_par->GetNumIndex1Elm(ipar);
        for(int inum = 0; inum < num_index1; inum ++){
            delete hist_index1_arr[ipar][inum]; hist_index1_arr[ipar][inum] = NULL;
        }
        delete [] hist_index1_arr[ipar]; hist_index1_arr[ipar] = NULL;
        
    }
    delete [] hist_chi2_arr; hist_chi2_arr = NULL;
    delete [] hist_valid_arr; hist_valid_arr = NULL;
    delete [] hist_edm_arr; hist_edm_arr = NULL;
    delete [] hist_flag_bad_neg_arr; hist_flag_bad_neg_arr = NULL;    
    delete [] hist_index1_arr; hist_index1_arr = NULL;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void FitFunc::GenFitStatForParSearch2d(MinFcn* const minfcn, const FitParam* const fit_param,
                                       const Chi2PlotContPar* const chi2plot_cont_par,
                                       FitStat***** const fit_stat_arr_ptr,
                                       double tolerance,
                                       int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }

    int ncont = chi2plot_cont_par->GetNcont();
    FitStat**** fit_stat_arr = new FitStat*** [ncont];
    for(int icont = 0; icont < ncont; icont++){
        int nstep0 = chi2plot_cont_par->GetNstep0Elm(icont);
        int nstep1 = chi2plot_cont_par->GetNstep1Elm(icont);
        fit_stat_arr[icont] = new FitStat** [nstep0];
        for(int istep0 = 0; istep0 < nstep0; istep0++){
            fit_stat_arr[icont][istep0] = new FitStat* [nstep1];
            for(int istep1 = 0; istep1 < nstep1; istep1++){
                fit_stat_arr[icont][istep0][istep1] = new FitStat;
            }
        }
    }

    for(int icont = 0; icont < ncont; icont++){
        int index0 = chi2plot_cont_par->GetIndex0Elm(icont);
        int index1 = chi2plot_cont_par->GetIndex1Elm(icont);
        int nstep0 = chi2plot_cont_par->GetNstep0Elm(icont);
        int nstep1 = chi2plot_cont_par->GetNstep1Elm(icont);
        
        FitParam* fit_param_this = new FitParam;
        fit_param_this->Copy(fit_param);

        for(int istep0 = 0; istep0 < nstep0; istep0++){
            printf("%d  ", istep0);
            fflush(stdout);
            double par0_plot = chi2plot_cont_par->GetPar0Val(icont, istep0);
            for(int istep1 = 0; istep1 < nstep1; istep1++){
                double par1_plot = chi2plot_cont_par->GetPar1Val(icont, istep1);
                fit_param_this->FixPar(index0, par0_plot);
                fit_param_this->FixPar(index1, par1_plot);
                if(0 < g_flag_verbose){
                    char msg[kLineSize];
                    sprintf(msg, "icont = %2.2d (ncont = %2.2d): istep0 = %3.3d (nstep0 = %3.3d)"
                            "istep1 = %3.3d (nstep1 = %3.3d)",
                            icont, ncont, istep0, nstep0, istep1, nstep1);
                    MPrintInfo(msg);
                }

                FitStat* fit_stat = NULL;
                double value_in_sigma_or_cl_this = 1.0;
                string sigma_or_cl_this = "sigma";
                int as_npar = 1;
                GenExecFit(minfcn, fit_param_this, &fit_stat,
                           value_in_sigma_or_cl_this, sigma_or_cl_this, as_npar,
                           tolerance, maxfcn);
                fit_stat_arr[icont][istep0][istep1]->Copy(fit_stat);
                delete fit_stat;
            }
        }
        printf("\n");
        fflush(stdout);
        delete fit_param_this;
    }
    *fit_stat_arr_ptr = fit_stat_arr;
    
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void FitFunc::DelFitStatForParSearch2d(const Chi2PlotContPar* const chi2plot_cont_par,
                                       FitStat**** fit_stat_arr)
{
    int ncont = chi2plot_cont_par->GetNcont();
    for(int icont = 0; icont < ncont; icont++){
        int nstep0 = chi2plot_cont_par->GetNstep0Elm(icont);
        int nstep1 = chi2plot_cont_par->GetNstep1Elm(icont);
        for(int istep0 = 0; istep0 < nstep0; istep0++){
            for(int istep1 = 0; istep1 < nstep1; istep1++){
                delete fit_stat_arr[icont][istep0][istep1];
                fit_stat_arr[icont][istep0][istep1] = NULL;
            }
            delete [] fit_stat_arr[icont][istep0]; fit_stat_arr[icont][istep0] = NULL;
        }
        delete [] fit_stat_arr[icont]; fit_stat_arr[icont] = NULL;
    }
    delete [] fit_stat_arr; fit_stat_arr = NULL;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void FitFunc::GenParSearch2d(const FitStat* const* const* const* const fit_stat_arr,
                             const Chi2PlotContPar* const chi2plot_cont_par,
                             HistData2d*** const hist_chi2_cont_arr_ptr,
                             HistData2d*** const hist_valid_cont_arr_ptr,
                             HistData2d*** const hist_edm_cont_arr_ptr,
                             HistData2d*** const hist_flag_bad_neg_cont_arr_ptr,
                             HistData2d**** const hist_index2_cont_arr_ptr)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }

    int ncont = chi2plot_cont_par->GetNcont();
    HistData2d** hist_chi2_cont_arr   = new HistData2d* [ncont];
    HistData2d** hist_valid_cont_arr  = new HistData2d* [ncont];
    HistData2d** hist_edm_cont_arr    = new HistData2d* [ncont];
    HistData2d** hist_flag_bad_neg_cont_arr = new HistData2d* [ncont];
    
    for(int icont = 0; icont < ncont; icont++){
        char title_tail[kLineSize];
        int index0 = chi2plot_cont_par->GetIndex0Elm(icont);
        int index1 = chi2plot_cont_par->GetIndex1Elm(icont);
        sprintf(title_tail, "%2.2d-%2.2d", index0, index1);
            
        char chi2_title[kLineSize];
        sprintf(chi2_title, "chi2_cont_%s", title_tail);
        hist_chi2_cont_arr[icont] = new HistDataNerr2d(chi2_title);

        char valid_title[kLineSize];
        sprintf(valid_title, "valid_cont_%s", title_tail);
        hist_valid_cont_arr[icont] = new HistDataNerr2d(valid_title);

        char edm_title[kLineSize];
        sprintf(edm_title, "edm_cont_%s", title_tail);
        hist_edm_cont_arr[icont] = new HistDataNerr2d(edm_title);

        char flag_bad_neg_title[kLineSize];
        sprintf(flag_bad_neg_title, "flag_bad_neg_cont_%s", title_tail);
        hist_flag_bad_neg_cont_arr[icont] = new HistDataNerr2d(flag_bad_neg_title);
    }

    for(int icont = 0; icont < ncont; icont++){    
        int nstep0         = chi2plot_cont_par->GetNstep0Elm(icont);
        string par0_lo_str = chi2plot_cont_par->GetLo0StrElm(icont);
        string par0_up_str = chi2plot_cont_par->GetUp0StrElm(icont);
        int nstep1         = chi2plot_cont_par->GetNstep1Elm(icont);
        string par1_lo_str = chi2plot_cont_par->GetLo1StrElm(icont);
        string par1_up_str = chi2plot_cont_par->GetUp1StrElm(icont);
        if("none" == par0_lo_str ||
           "none" == par0_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par0_lo = atof(par0_lo_str.c_str());
        double par0_up = atof(par0_up_str.c_str());

        if("none" == par1_lo_str ||
           "none" == par1_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par1_lo = atof(par1_lo_str.c_str());
        double par1_up = atof(par1_up_str.c_str());

        int nstep = nstep0 * nstep1;
        double* chi2_arr   = new double [nstep];
        double* valid_arr  = new double [nstep];
        double* edm_arr    = new double [nstep];
        double* flag_bad_neg_arr    = new double [nstep];

        for(int istep0 = 0; istep0 < nstep0; istep0++){
            for(int istep1 = 0; istep1 < nstep1; istep1++){
                int istep = istep0 + nstep0 * istep1;
                chi2_arr[istep]   = fit_stat_arr[icont][istep0][istep1]->GetFcnMin();
                valid_arr[istep]  = fit_stat_arr[icont][istep0][istep1]->GetValid();
                edm_arr[istep]    = fit_stat_arr[icont][istep0][istep1]->GetEdm();
                flag_bad_neg_arr[istep] = fit_stat_arr[icont][istep0][istep1]->GetFlagBadNeg();
            }
        }

        hist_chi2_cont_arr[icont]->Init(nstep0, par0_lo, par0_up,
                                        nstep1, par1_lo, par1_up);
        hist_chi2_cont_arr[icont]->SetOvalArr(nstep0 * nstep1, chi2_arr);
        hist_valid_cont_arr[icont]->Init(nstep0, par0_lo, par0_up,
                                         nstep1, par1_lo, par1_up);
        hist_valid_cont_arr[icont]->SetOvalArr(nstep0 * nstep1, valid_arr);
        hist_edm_cont_arr[icont]->Init(nstep0, par0_lo, par0_up,
                                       nstep1, par1_lo, par1_up);
        hist_edm_cont_arr[icont]->SetOvalArr(nstep0 * nstep1, edm_arr);
        hist_flag_bad_neg_cont_arr[icont]->Init(nstep0, par0_lo, par0_up,
                                                nstep1, par1_lo, par1_up);
        hist_flag_bad_neg_cont_arr[icont]->SetOvalArr(nstep0 * nstep1, flag_bad_neg_arr);
        delete [] chi2_arr;
        delete [] valid_arr;
        delete [] edm_arr;
        delete [] flag_bad_neg_arr;
    }


    HistData2d*** hist_index2_cont_arr  = new HistData2d** [ncont];
    for(int icont = 0; icont < ncont; icont++){
        char title_tail[kLineSize];
        int index0_par = chi2plot_cont_par->GetIndex0Elm(icont);
        int index1_par = chi2plot_cont_par->GetIndex1Elm(icont);        
        sprintf(title_tail, "%2.2d-%2.2d", index0_par, index1_par);
        int num_index2 = chi2plot_cont_par->GetNumIndex2Elm(icont);
        hist_index2_cont_arr[icont] = new HistData2d* [num_index2];
        for(int inum = 0; inum < num_index2; inum ++){
            int index2 = chi2plot_cont_par->GetIndex2ArrElm(icont, inum);
            char index2_title[kLineSize];
            sprintf(index2_title, "index2-%2.2d_cont_%s", index2, title_tail);
            hist_index2_cont_arr[icont][inum] = new HistDataNerr2d(index2_title);
        }
    }

    for(int icont = 0; icont < ncont; icont++){
        int nstep0         = chi2plot_cont_par->GetNstep0Elm(icont);
        string par0_lo_str = chi2plot_cont_par->GetLo0StrElm(icont);
        string par0_up_str = chi2plot_cont_par->GetUp0StrElm(icont);
        int nstep1         = chi2plot_cont_par->GetNstep1Elm(icont);
        string par1_lo_str = chi2plot_cont_par->GetLo1StrElm(icont);
        string par1_up_str = chi2plot_cont_par->GetUp1StrElm(icont);
        
        if("none" == par0_lo_str ||
           "none" == par0_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par0_lo = atof(par0_lo_str.c_str());
        double par0_up = atof(par0_up_str.c_str());
        if("none" == par1_lo_str ||
           "none" == par1_up_str   ){
            MPrintErr("bad.");
            abort();
        }
        double par1_lo = atof(par1_lo_str.c_str());
        double par1_up = atof(par1_up_str.c_str());
        
        int num_index2 = chi2plot_cont_par->GetNumIndex2Elm(icont);
        for(int inum = 0; inum < num_index2; inum ++){
            int index2 = chi2plot_cont_par->GetIndex2ArrElm(icont, inum);

            int nstep = nstep0 * nstep1;            
            double* index2_arr = new double [nstep];
            for(int istep0 = 0; istep0 < nstep0; istep0++){
                for(int istep1 = 0; istep1 < nstep1; istep1++){
                    int istep = istep0 + nstep0 * istep1;
                    index2_arr[istep] = fit_stat_arr[icont][istep0][istep1]->GetFitParam()->GetParElm(index2);
                }
            }
            hist_index2_cont_arr[icont][inum]->Init(nstep0, par0_lo, par0_up,
                                                    nstep1, par1_lo, par1_up);
            hist_index2_cont_arr[icont][inum]->SetOvalArr(nstep0 * nstep1, index2_arr);
            delete [] index2_arr;
        }
    }
    
    *hist_chi2_cont_arr_ptr   = hist_chi2_cont_arr;
    *hist_valid_cont_arr_ptr  = hist_valid_cont_arr;
    *hist_edm_cont_arr_ptr    = hist_edm_cont_arr;
    *hist_flag_bad_neg_cont_arr_ptr  = hist_flag_bad_neg_cont_arr;
    *hist_index2_cont_arr_ptr = hist_index2_cont_arr;

     if(0 < g_flag_verbose){
         MPrintInfo("done.");
    }
}


void FitFunc::DelParSearch2d(const Chi2PlotContPar* const chi2plot_cont_par,
                             HistData2d** hist_chi2_cont_arr,
                             HistData2d** hist_valid_cont_arr,
                             HistData2d** hist_edm_cont_arr,
                             HistData2d** hist_flag_bad_neg_cont_arr,
                             HistData2d*** hist_index2_cont_arr)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start ...");
    }

    int ncont = chi2plot_cont_par->GetNcont();
    for(int icont = 0; icont < ncont; icont++){
        delete hist_chi2_cont_arr[icont];   hist_chi2_cont_arr[icont]   = NULL;
        delete hist_valid_cont_arr[icont];  hist_valid_cont_arr[icont]  = NULL;
        delete hist_edm_cont_arr[icont];    hist_edm_cont_arr[icont]    = NULL;
        delete hist_flag_bad_neg_cont_arr[icont]; hist_flag_bad_neg_cont_arr[icont] = NULL;

        int num_index2 = chi2plot_cont_par->GetNumIndex2Elm(icont);
        for(int inum = 0; inum < num_index2; inum ++){
            delete hist_index2_cont_arr[icont][inum]; hist_index2_cont_arr[icont][inum] = NULL;
        }
        delete hist_index2_cont_arr[icont]; hist_index2_cont_arr[icont] = NULL;
    }
    delete [] hist_chi2_cont_arr;   hist_chi2_cont_arr   = NULL;
    delete [] hist_valid_cont_arr;  hist_valid_cont_arr  = NULL;
    delete [] hist_edm_cont_arr;    hist_edm_cont_arr    = NULL;
    delete [] hist_flag_bad_neg_cont_arr; hist_flag_bad_neg_cont_arr    = NULL;    
    delete [] hist_index2_cont_arr; hist_index2_cont_arr = NULL;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


void FitFunc::GenFitStatHG(FILE* fp_log, MinFcn* const minfcn, const FitParam* const fit_param,
                           Chi2PlotPar* const chi2plot_par,
                           Chi2PlotContPar* const chi2plot_cont_par,
                           FitStatHG** const fit_stat_hg_ptr,
                           double value_in_sigma_or_cl, string sigma_or_cl, int as_npar,
                           double tolerance, int maxfcn)
{
    if(0 < g_flag_verbose){
        MPrintInfo("start...");
    }
    char prompt[kLineSize];
    sprintf(prompt, "%s", __func__);

    FitStatHG* fit_stat_hg = new FitStatHG;
    
    //
    // before fit
    //
    FitStat* fit_stat_init = new FitStat;
    fit_stat_init->Init();
    fit_stat_init->SetByFixPar(minfcn, fit_param);
    fit_stat_hg->InitSetFitStatInit(fit_stat_init);
    delete fit_stat_init;
    
    //
    // initial fit
    //
    MPrintInfo("initial fit ...");
    FitStat* fit_stat = NULL;
    ROOT::Minuit2::FunctionMinimum function_minimum = GenExecFit(minfcn, fit_param, &fit_stat,
                                                                 value_in_sigma_or_cl, sigma_or_cl, as_npar,
                                                                 tolerance, maxfcn);
    fit_stat->Print(stdout);
    MPrintInfo("initial fit: done.");
    
    if(1 == fit_param->IsCalcTerr()){
        if(NULL == chi2plot_par &&
           NULL == chi2plot_cont_par){
            if(1 == function_minimum.IsValid() &&
               ! isnan(function_minimum.Edm()) &&
               ! isinf(function_minimum.Edm())   ){
                GetAsymErr(minfcn, fit_param,
                           function_minimum,                       
                           fit_stat,
                           value_in_sigma_or_cl, sigma_or_cl,
                           tolerance, maxfcn);
            }
        }
    }

    printf("%s: ---------- best fit_stat in initial fit -------------\n", prompt);
    fit_stat->Print(stdout);
    printf("%s: ========== best fit_stat in initial fit =============\n", prompt);
    fit_stat_hg->InitSetFitStat(fit_stat);
    FitParam* fit_param_by_initial_fit = new FitParam;
    fit_param_by_initial_fit->Copy(fit_stat->GetFitParam());
    double chi2_min_initial_fit = DBL_MAX;
    if(1 == fit_stat->GetValid()){
        chi2_min_initial_fit = fit_stat->GetFcnMin();
    }


    FitParam* fit_param_best_by_chi2_search = NULL;
    FitParam* fit_param_best_by_chi2cont_search = NULL;
    double chi2_min_chi2_search = DBL_MAX;
    double chi2_min_chi2cont_search = DBL_MAX;
    
    printf("%s: ---------- chi2 search start -------------\n", prompt);        
    if(NULL == chi2plot_par){
        MPrintInfo("skip Chi2plot calculation");
    } else {
        if(chi2plot_par->GetNpar() > fit_param->GetNparFree()){
            char msg[kLineSize];
            sprintf(msg, "chi2plot_par->GetNpar() (=%d) > fit_param->GetNparFree() (=%d)",
                    chi2plot_par->GetNpar(), fit_param->GetNparFree());
            MPrintErr(msg);
            abort();
        }
        
        chi2plot_par->SetLoUpSigmaByFitStat(fit_stat);

        FitStat*** fit_stat_arr      = NULL;
        HistData1d** hist_chi2_arr   = NULL;
        HistData1d** hist_valid_arr  = NULL;
        HistData1d** hist_edm_arr    = NULL;
        HistData1d** hist_flag_bad_neg_arr = NULL;        
        HistData1d*** hist_index1_arr = NULL;

        GenFitStatForParSearch1d(minfcn, fit_param, 
                                 chi2plot_par,
                                 &fit_stat_arr,
                                 tolerance,
                                 maxfcn);
        GenParSearch1d(fit_stat_arr,
                       chi2plot_par,
                       &hist_chi2_arr,
                       &hist_valid_arr,
                       &hist_edm_arr,
                       &hist_flag_bad_neg_arr,
                       &hist_index1_arr);
        fit_stat_hg->InitSetChi2(chi2plot_par,
                                 hist_chi2_arr,
                                 hist_valid_arr,
                                 hist_edm_arr,
                                 hist_flag_bad_neg_arr,
                                 hist_index1_arr,
                                 fit_stat_arr);
        DelFitStatForParSearch1d(chi2plot_par,
                                 fit_stat_arr);
        DelParSearch1d(chi2plot_par,
                       hist_chi2_arr,
                       hist_valid_arr,
                       hist_edm_arr,
                       hist_flag_bad_neg_arr,
                       hist_index1_arr);

        //
        // search chi2 min
        //
        int npar = chi2plot_par->GetNpar();
        double* chi2_min_arr = new double [npar];
        double* par_at_min_chi2plot_arr = new double [npar];
        double* par_err_plus_end_chi2plot_arr = new double [npar];
        double* par_err_minus_end_chi2plot_arr = new double [npar];        
        for(int ipar = 0; ipar < npar; ipar ++){
            chi2_min_arr[ipar] = DBL_MAX;
            par_at_min_chi2plot_arr[ipar] = 0.0;
            par_err_plus_end_chi2plot_arr[ipar] = 0.0;
            par_err_minus_end_chi2plot_arr[ipar] = 0.0;
        }

        int ipar_min = 0;
        int istep_min = 0;
        for(int ipar = 0; ipar < chi2plot_par->GetNpar(); ipar++){
            int nstep = chi2plot_par->GetNstepElm(ipar);
            double par_min = 0.0;
            for(int istep = 0; istep < nstep; istep ++){
                int flag_valid_this = fit_stat_hg->GetFitStatChi2SearchArr()[ipar][istep]->GetValid();
                double chi2_this = fit_stat_hg->GetFitStatChi2SearchArr()[ipar][istep]->GetFcnMin();
                double par_this  = chi2plot_par->GetParVal(ipar, istep);
                if( 1 == flag_valid_this &&
                    chi2_this < chi2_min_arr[ipar] ) {
                    par_min  = par_this;
                    chi2_min_arr[ipar] = chi2_this;
                    ipar_min = ipar;
                    istep_min = istep;
                }
            }
            par_at_min_chi2plot_arr[ipar] = par_min;
        }
        fit_param_best_by_chi2_search = new FitParam;
        fit_param_best_by_chi2_search->Copy(
            fit_stat_hg->GetFitStatChi2SearchArr()[ipar_min][istep_min]->GetFitParam()
            );
        chi2_min_chi2_search = MirMath::GetMin(chi2plot_par->GetNpar(), chi2_min_arr);

        //
        // search error region
        //
        double up_minfcn = MinFcn::GetUpMinfcn(value_in_sigma_or_cl,
                                               sigma_or_cl,
                                               as_npar);
        for(int ipar = 0; ipar < chi2plot_par->GetNpar(); ipar++){
            double chi2_min_aim = chi2_min_arr[ipar] + up_minfcn;
            vector<double> par_vec;
            int nstep = chi2plot_par->GetNstepElm(ipar);
            for(int istep = 0; istep < nstep; istep ++){
                int flag_valid_this = fit_stat_hg->GetFitStatChi2SearchArr()[ipar][istep]->GetValid();
                double chi2_this = fit_stat_hg->GetFitStatChi2SearchArr()[ipar][istep]->GetFcnMin();
                if( 1 == flag_valid_this &&
                    chi2_this <= chi2_min_aim ) {
                    double par = chi2plot_par->GetParVal(ipar, istep);
                    par_vec.push_back(par);
                }
            }
            par_err_plus_end_chi2plot_arr[ipar]  = MirMath::GetMax(par_vec)
                + chi2plot_par->GetStepElm(ipar) / 2.;
            par_err_minus_end_chi2plot_arr[ipar] = MirMath::GetMin(par_vec)
                - chi2plot_par->GetStepElm(ipar) / 2.;
        }
        
        fit_stat_hg->InitSetChi2ErrEnd(npar,
                                       par_at_min_chi2plot_arr,
                                       par_err_plus_end_chi2plot_arr,
                                       par_err_minus_end_chi2plot_arr);

        for(int ipar = 0; ipar < chi2plot_par->GetNpar(); ipar++){
            printf("%s: ipar = %d: par_at_min_chi2par_arr [minus_end  plus_end]: %e [%e %e]\n",
                   prompt, ipar,
                   par_at_min_chi2plot_arr[ipar],
                   par_err_minus_end_chi2plot_arr[ipar],
                   par_err_plus_end_chi2plot_arr[ipar]);
        }
        delete [] chi2_min_arr;
        delete [] par_at_min_chi2plot_arr;
        delete [] par_err_plus_end_chi2plot_arr;
        delete [] par_err_minus_end_chi2plot_arr;


        printf("%s: ---------- best fit_param found in the chi2 search -------------\n", prompt);
        fit_param_best_by_chi2_search->Print(stdout);
        printf("%s: ========== best fit_param found in the chi2 search =============\n", prompt);
       
    }
    printf("%s: =========== chi2 search END =======\n", prompt);    

    
    if(NULL == chi2plot_cont_par){
        MPrintInfo("skip Chi2plotCont calculation");
    } else if (chi2plot_cont_par->GetNcont() < 1){
        printf("ncont = %d\n", chi2plot_cont_par->GetNcont());
        MPrintInfo("skip Chi2plotCont calculation");
    } else {
        if(chi2plot_cont_par->GetNcont() > MirMath::GetCombination(fit_param->GetNparFree(),
                                                                    fit_param->GetNparFree() - 1)){
            char msg[kLineSize];
            sprintf(msg, "chi2plot_cont_par->GetNcont() (=%d) > "
                    "Combination(fit_param->GetNparFree(), fit_param->GetNparFree() - 1) (=%d)\n",
                    chi2plot_cont_par->GetNcont(),
                    MirMath::GetCombination(fit_param->GetNparFree(),
                                             fit_param->GetNparFree() - 1));
            MPrintErr(msg);
            abort();
        }

        chi2plot_cont_par->SetLoUpSigmaByFitStat(fit_stat);
        chi2plot_cont_par->Print(stdout);
        
        FitStat**** fit_stat_arr = NULL;
        HistData2d** hist_chi2_cont_arr  = NULL;
        HistData2d** hist_valid_cont_arr = NULL;
        HistData2d** hist_edm_cont_arr   = NULL;
        HistData2d** hist_flag_bad_neg_cont_arr = NULL;
        HistData2d*** hist_index2_cont_arr  = NULL;
        
        GenFitStatForParSearch2d(minfcn, fit_param, 
                                 chi2plot_cont_par,
                                 &fit_stat_arr,
                                 tolerance,
                                 maxfcn);
        GenParSearch2d(fit_stat_arr,
                       chi2plot_cont_par,
                       &hist_chi2_cont_arr,
                       &hist_valid_cont_arr,
                       &hist_edm_cont_arr,
                       &hist_flag_bad_neg_cont_arr,
                       &hist_index2_cont_arr);
        fit_stat_hg->InitSetChi2Cont(chi2plot_cont_par,
                                     hist_chi2_cont_arr,
                                     hist_valid_cont_arr,
                                     hist_edm_cont_arr,
                                     hist_flag_bad_neg_cont_arr,
                                     hist_index2_cont_arr,
                                     fit_stat_arr);
        DelFitStatForParSearch2d(chi2plot_cont_par,
                                 fit_stat_arr);
        DelParSearch2d(chi2plot_cont_par,
                       hist_chi2_cont_arr,
                       hist_valid_cont_arr,
                       hist_edm_cont_arr,
                       hist_flag_bad_neg_cont_arr,
                       hist_index2_cont_arr);

        //
        // search chi2 min
        //
        int ncont = chi2plot_cont_par->GetNcont();
        double* chi2_min_arr = new double [ncont];
        double* par0_at_min_chi2plot_cont_arr        = new double [ncont];
        double* par0_err_plus_end_chi2plot_cont_arr  = new double [ncont];
        double* par0_err_minus_end_chi2plot_cont_arr = new double [ncont];
        double* par1_at_min_chi2plot_cont_arr        = new double [ncont];
        double* par1_err_plus_end_chi2plot_cont_arr  = new double [ncont];
        double* par1_err_minus_end_chi2plot_cont_arr = new double [ncont];
        for(int icont = 0; icont < ncont; icont ++){
            chi2_min_arr[icont] = DBL_MAX;
            par0_at_min_chi2plot_cont_arr[icont]        = 0.0;
            par0_err_plus_end_chi2plot_cont_arr[icont]  = 0.0;
            par0_err_minus_end_chi2plot_cont_arr[icont] = 0.0;
            par1_at_min_chi2plot_cont_arr[icont]        = 0.0;
            par1_err_plus_end_chi2plot_cont_arr[icont]  = 0.0;
            par1_err_minus_end_chi2plot_cont_arr[icont] = 0.0;
        }
        

        int icont_min = 0;
        int istep0_min = 0;
        int istep1_min = 0;
        for(int icont = 0; icont < chi2plot_cont_par->GetNcont(); icont++){
            int nstep0 = chi2plot_cont_par->GetNstep0Elm(icont);
            int nstep1 = chi2plot_cont_par->GetNstep1Elm(icont);
            double par0_min = 0.0;
            double par1_min = 0.0;
            for(int istep0 = 0; istep0 < nstep0; istep0 ++){
                for(int istep1 = 0; istep1 < nstep1; istep1 ++){
                    int flag_valid_this = fit_stat_hg->GetFitStatChi2ContSearchArr()[icont][istep0][istep1]->GetValid();
                    double chi2_this = fit_stat_hg->GetFitStatChi2ContSearchArr()[icont][istep0][istep1]->GetFcnMin();
                    double par0_this = chi2plot_cont_par->GetPar0Val(icont, istep0); 
                    double par1_this = chi2plot_cont_par->GetPar1Val(icont, istep1);
                    if( 1 == flag_valid_this &&
                        chi2_this < chi2_min_arr[icont]) {
                        par0_min = par0_this;
                        par1_min = par1_this;
                        chi2_min_arr[icont] = chi2_this;
                        icont_min = icont;
                        istep0_min = istep0;
                        istep1_min = istep1;
                    }
                }
            }
            par0_at_min_chi2plot_cont_arr[icont] = par0_min;
            par1_at_min_chi2plot_cont_arr[icont] = par1_min;
        }

        fit_param_best_by_chi2cont_search = new FitParam;
        fit_param_best_by_chi2cont_search->Copy(
            fit_stat_hg->GetFitStatChi2ContSearchArr()[icont_min][istep0_min][istep1_min]->GetFitParam()
            );
        chi2_min_chi2cont_search = MirMath::GetMin(ncont, chi2_min_arr);
        
        //
        // search error region
        //
        double up_minfcn = MinFcn::GetUpMinfcn(value_in_sigma_or_cl,
                                               sigma_or_cl,
                                               as_npar);
        for(int icont = 0; icont < chi2plot_cont_par->GetNcont(); icont++){
            double chi2_min_aim = chi2_min_arr[icont] + up_minfcn;
            vector<double> par_vec0;
            vector<double> par_vec1;
            int nstep0 = chi2plot_cont_par->GetNstep0Elm(icont);
            int nstep1 = chi2plot_cont_par->GetNstep1Elm(icont);
            for(int istep0 = 0; istep0 < nstep0; istep0 ++){
                for(int istep1 = 0; istep1 < nstep1; istep1 ++){
                    int flag_valid_this = fit_stat_hg->GetFitStatChi2ContSearchArr()[icont][istep0][istep1]->GetValid();
                    double chi2_this = fit_stat_hg->GetFitStatChi2ContSearchArr()[icont][istep0][istep1]->GetFcnMin();
                    if( 1 == flag_valid_this &&
                        chi2_this <= chi2_min_aim ) {
                        double par0 = chi2plot_cont_par->GetPar0Val(icont, istep0);
                        double par1 = chi2plot_cont_par->GetPar1Val(icont, istep1);
                        par_vec0.push_back(par0);
                        par_vec1.push_back(par1);
                    }
                }
            }
            par0_err_plus_end_chi2plot_cont_arr[icont]  = MirMath::GetMax(par_vec0)
                + chi2plot_cont_par->GetStep0Elm(icont) / 2.;
            par0_err_minus_end_chi2plot_cont_arr[icont] = MirMath::GetMin(par_vec0)
                - chi2plot_cont_par->GetStep0Elm(icont) / 2.;
            par1_err_plus_end_chi2plot_cont_arr[icont]  = MirMath::GetMax(par_vec1)
                + chi2plot_cont_par->GetStep1Elm(icont) / 2.;
            par1_err_minus_end_chi2plot_cont_arr[icont] = MirMath::GetMin(par_vec1)
                - chi2plot_cont_par->GetStep1Elm(icont) / 2.;
        }
        
        fit_stat_hg->InitSetChi2ContErrEnd(ncont,
                                           par0_at_min_chi2plot_cont_arr,
                                           par0_err_plus_end_chi2plot_cont_arr,
                                           par0_err_minus_end_chi2plot_cont_arr,
                                           par1_at_min_chi2plot_cont_arr,
                                           par1_err_plus_end_chi2plot_cont_arr,
                                           par1_err_minus_end_chi2plot_cont_arr);

        delete [] chi2_min_arr;
        delete [] par0_at_min_chi2plot_cont_arr;
        delete [] par0_err_plus_end_chi2plot_cont_arr;
        delete [] par0_err_minus_end_chi2plot_cont_arr;
        delete [] par1_at_min_chi2plot_cont_arr;
        delete [] par1_err_plus_end_chi2plot_cont_arr;
        delete [] par1_err_minus_end_chi2plot_cont_arr;
        
        printf("%s: ---------- best fit_param found in the chi2cont search -------------\n", prompt);
        fit_param_best_by_chi2cont_search->Print(stdout);
        printf("%s: ========== best fit_param found in the chi2cont search =============\n", prompt);
    }

    delete fit_stat; fit_stat = NULL;
    
    //
    // fit again
    //
    if(NULL != chi2plot_par ||
       NULL != chi2plot_cont_par){
        printf("fit again by using the best parameter set found in chi2 or chi2cont search.\n");
        
        double chi2_min_arr[3];
        chi2_min_arr[0] = chi2_min_initial_fit;
        chi2_min_arr[1] = chi2_min_chi2_search;
        chi2_min_arr[2] = chi2_min_chi2cont_search;
        printf("chi2_min found by initial fit: %e\n", chi2_min_arr[0]);
        printf("chi2_min found by chi2 search: %e\n", chi2_min_arr[1]);
        printf("chi2_min found by chi2 contour search: %e\n", chi2_min_arr[2]);
        int index_min = MirMath::GetLocMin(3, chi2_min_arr);

        FitParam* fit_param_for_fit_again = new FitParam;
        fit_param_for_fit_again->Copy(fit_param);
        if(0 == index_min){
            printf("Set the initial parameter by the best parameter found by initial fit\n");
            fit_param_for_fit_again->SetParInit(fit_param_by_initial_fit->GetNpar(),
                                                fit_param_by_initial_fit->GetPar() );
        } else if (1 == index_min){
            printf("Set the initial parameter by the best parameter found by chi2 search\n");
            fit_param_for_fit_again->SetParInit(fit_param_best_by_chi2_search->GetNpar(),
                                                fit_param_best_by_chi2_search->GetPar() );
        } else if (2 == index_min){
            printf("Set the initial parameter by the best parameter found by chi2 contour search\n");
            fit_param_for_fit_again->SetParInit(fit_param_best_by_chi2cont_search->GetNpar(),
                                                fit_param_best_by_chi2cont_search->GetPar() );            
        } else {
            MPrintErr("bad.");
            abort();
        }
        
        FitStat* fit_stat_for_fit_again = NULL;
        ROOT::Minuit2::FunctionMinimum function_minimum = GenExecFit(minfcn, fit_param_for_fit_again,
                                                                     &fit_stat_for_fit_again,
                                                                     value_in_sigma_or_cl, sigma_or_cl, as_npar,
                                                                     tolerance, maxfcn);
        if(1 == fit_param_for_fit_again->IsCalcTerr()){
            if(1 == function_minimum.IsValid() &&
               ! isnan(function_minimum.Edm()) &&
               ! isinf(function_minimum.Edm())   ){
                GetAsymErr(minfcn, fit_param_for_fit_again,
                           function_minimum,
                           fit_stat_for_fit_again,
                           value_in_sigma_or_cl, sigma_or_cl,
                           tolerance, maxfcn);
            }
        }
        fit_stat_hg->InitSetFitStat(fit_stat_for_fit_again);

        printf("%s: ---------- best fit_stat found in the final fit -------------\n", prompt);
        fit_stat_for_fit_again->Print(stdout);
        printf("%s: ========== best fit_stat found in the final fit =============\n", prompt);
        
        delete fit_stat_for_fit_again; fit_stat_for_fit_again = NULL;
        delete fit_param_for_fit_again; fit_param_for_fit_again = NULL;
    }

    //
    // Set fit_param_best
    //

    FitParam* fit_param_best = new FitParam;
    fit_param_best->Copy(fit_stat_hg->GetFitStat()->GetFitParam());
    int valid_fit = fit_stat_hg->GetFitStat()->GetValid();
    int npar_fit_param_best = fit_stat_hg->GetFitStat()->GetFitParam()->GetNpar();
    for(int ipar = 0; ipar < npar_fit_param_best; ipar ++){

        // par_center
        double par_center = 0.0;
        int valid_par = 0;
        if(1 == valid_fit){
            par_center = fit_stat_hg->GetFitStat()->GetFitParam()->GetParElm(ipar);
            valid_par  = 1;
        } else {
            for(int ihist = 0; ihist < fit_stat_hg->GetNhistChi2(); ihist ++){
                int index = fit_stat_hg->GetChi2PlotPar()->GetIndexElm(ihist);
                if(index == ipar){
                    par_center = fit_stat_hg->GetParAtMinChi2plotArrElm(ihist);
                    valid_par = fit_param_best_by_chi2_search->GetValidParElm(ipar);
                }
            }
        }

        // par_terr_plus
        double par_terr_plus = 0.0;
        int valid_terr_plus = fit_stat_hg->GetFitStat()->GetFitParam()->GetValidTerrPlusElm(ipar);
        if(1 == valid_terr_plus){
            par_terr_plus = fit_stat_hg->GetFitStat()->GetFitParam()->GetParTerrPlusElm(ipar);
        } else {
            double par_err_plus_end = 0.0;
            for(int ihist = 0; ihist < fit_stat_hg->GetNhistChi2(); ihist ++){
                int index = fit_stat_hg->GetChi2PlotPar()->GetIndexElm(ihist);
                if(index == ipar){
                    par_err_plus_end = fit_stat_hg->GetParErrPlusEndChi2plotArrElm(ihist);
                    valid_terr_plus = 1;
                }
            }
            par_terr_plus = par_err_plus_end - par_center;
        }
        
        // par_terr_minus
        double par_terr_minus = 0.0;
        int valid_terr_minus = fit_stat_hg->GetFitStat()->GetFitParam()->GetValidTerrMinusElm(ipar);
        if(1 == valid_terr_minus){
            par_terr_minus = fit_stat_hg->GetFitStat()->GetFitParam()->GetParTerrMinusElm(ipar);
        } else {
            double par_err_minus_end = 0.0;
            for(int ihist = 0; ihist < fit_stat_hg->GetNhistChi2(); ihist ++){
                int index = fit_stat_hg->GetChi2PlotPar()->GetIndexElm(ihist);
                if(index == ipar){
                    par_err_minus_end = fit_stat_hg->GetParErrMinusEndChi2plotArrElm(ihist);
                    valid_terr_minus = 1;
                }
            }
            par_terr_minus = par_err_minus_end - par_center;
        }
        fit_param_best->SetParElm(ipar, par_center);
        fit_param_best->SetParTerrElm(ipar, par_terr_minus, par_terr_plus);
        fit_param_best->SetValidParElm(ipar, valid_par);
        fit_param_best->SetValidTerrElm(ipar, valid_terr_minus, valid_terr_plus);
    }
    fit_stat_hg->InitSetFitParamBest(fit_param_best);

    printf("%s: ---------- fit_param_best -------------\n", prompt);
    fit_param_best->Print(stdout);
    printf("%s: ========== fit_param_best =============\n", prompt);

    
    delete fit_param_by_initial_fit; fit_param_by_initial_fit = NULL;
    if(NULL != fit_param_best_by_chi2_search) {
        delete fit_param_best_by_chi2_search;
        fit_param_best_by_chi2_search = NULL;
    }
    if(NULL != fit_param_best_by_chi2cont_search) {
        delete fit_param_best_by_chi2cont_search;
        fit_param_best_by_chi2cont_search = NULL;
    }    


    *fit_stat_hg_ptr = fit_stat_hg;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


