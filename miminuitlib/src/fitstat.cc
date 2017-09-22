#include "mim_fitstat.h"

// public

void FitStat::Init()
{
    Null();

    fit_param_ = new FitParam;
    ndata_fit_ = 0;
    ndf_       = 0;
    up_minfcn_ = 0;
    valid_     = 0;
    fcn_min_   = 0.0;
    edm_       = 0.0;
    nfcn_      = 0;
    p_value_   = 0.0;
    flag_bad_neg_ = 0;
    aic_       = 0.0;
    bic_       = 0.0;
    aic_c_     = 0.0;
}

void FitStat::Set(const MinFcn* const min_fcn,
                  const FitParam* const fit_param_in,
                  ROOT::Minuit2::FunctionMinimum function_minimum,
                  ROOT::Minuit2::MnUserParameters upar)
{
    int npar          = upar.Params().size();
    double* par       = new double [npar];
    double* par_serr  = new double [npar];
    for(int ipar = 0; ipar < npar; ipar ++){
        par[ipar]      = upar.Params().at(ipar);
        par_serr[ipar] = upar.Errors().at(ipar);
    }
    fit_param_->Init(npar);
    fit_param_->SetOut(fit_param_in, npar, par, par_serr);
    delete [] par;
    delete [] par_serr;

    ndata_fit_    = min_fcn->GetNdataValid();
    ndf_          = ndata_fit_ - fit_param_in->GetNparFree();
    up_minfcn_    = min_fcn->Up();
    valid_        = function_minimum.IsValid();
    fcn_min_      = function_minimum.Fval();
    edm_          = function_minimum.Edm();
    nfcn_         = function_minimum.NFcn();

    flag_bad_neg_ = min_fcn->GetFlagBadNeg();
    aic_          = fcn_min_ + 2.0 * fit_param_in->GetNparFree();
    bic_          = fcn_min_ + fit_param_in->GetNparFree() * ( log(ndata_fit_) - log(2 * M_PI) );


    if(0 != ndata_fit_ - fit_param_in->GetNparFree() - 1){
        aic_c_        = aic_
            + 2 * fit_param_in->GetNparFree() * (fit_param_in->GetNparFree() + 1)
            / (ndata_fit_ - fit_param_in->GetNparFree() - 1);
    } else {
        aic_c_ = 0.0;
    }
    for(int ipar = 0; ipar < npar; ipar ++){
        fit_param_->SetValidParElm(ipar, valid_);
    }

    //
    // p_value (= goodness-of-fit)
    //

    if("Chi2Fcn1d"              == min_fcn->GetClassName() ||
       "Chi2FcnAsym1d"          == min_fcn->GetClassName() ||
       "Chi2PearsonFcn1d"       == min_fcn->GetClassName() ||
       "Chi2PearsonPhysFcn1d"   == min_fcn->GetClassName() ||
       "Chi2NeymanFcn1d"        == min_fcn->GetClassName() ||
       "Chi2NeymanPhysFcn1d"    == min_fcn->GetClassName() ||
       "Chi2NeymanModFcn1d"     == min_fcn->GetClassName() ||
       "Chi2NeymanModPhysFcn1d" == min_fcn->GetClassName() ||
       "Chi2GammaFcn1d"         == min_fcn->GetClassName() ||
       "Chi2GammaPhysFcn1d"     == min_fcn->GetClassName() ||
       "CstatDeltaFcn1d"        == min_fcn->GetClassName() ||
       "CstatDeltaPhysFcn1d"    == min_fcn->GetClassName() ||
       
       "Chi2Fcn2d"              == min_fcn->GetClassName() ||
       "Chi2FcnAsym2d"          == min_fcn->GetClassName() ||
       "Chi2PearsonFcn2d"       == min_fcn->GetClassName() ||
       "Chi2PearsonPhysFcn2d"   == min_fcn->GetClassName() ||
       "Chi2NeymanFcn2d"        == min_fcn->GetClassName() ||
       "Chi2NeymanPhysFcn2d"    == min_fcn->GetClassName() ||
       "Chi2NeymanModFcn2d"     == min_fcn->GetClassName() ||
       "Chi2NeymanModPhysFcn2d" == min_fcn->GetClassName() ||
       "Chi2GammaFcn2d"         == min_fcn->GetClassName() ||
       "Chi2GammaPhysFcn2d"     == min_fcn->GetClassName() ||
       "CstatDeltaFcn2d"        == min_fcn->GetClassName() ||
       "CstatDeltaPhysFcn2d"    == min_fcn->GetClassName() ) {

        p_value_ = TMath::Prob(fcn_min_, ndf_);

    } else if("CstatFcn1d"           == min_fcn->GetClassName() ||
              "CstatPhysFcn1d"       == min_fcn->GetClassName() ||
              "CstatUnbinFcn1d"      == min_fcn->GetClassName() ||
              "CstatUnbinPhysFcn1d"  == min_fcn->GetClassName() ||

              "CstatFcn2d"           == min_fcn->GetClassName() ||
              "CstatPhysFcn2d"       == min_fcn->GetClassName() ||
              "CstatUnbinFcn2d"      == min_fcn->GetClassName() ||
              "CstatUnbinPhysFcn2d"  == min_fcn->GetClassName() ) {

        p_value_ = -1.0;
    
    } else {
        if(0 < g_flag_verbose){
            char msg[kLineSize];
            sprintf(msg, "%s: not supported yet for p_value",
                    min_fcn->GetClassName().c_str());
            MPrintWarnClass(msg);
        }
    }
}

void FitStat::Set(const TF1* const tf1, double chi2)
{
    ndata_fit_ = tf1->GetNumberFitPoints();
    int npar_free = tf1->GetNumberFreeParameters();
    int ndf = ndata_fit_ - npar_free;
    ndf_ = tf1->GetNDF();
    if(ndf != ndf_){
        char msg[kLineSize];
        sprintf(msg, "something is wrong: ndf(%d) != ndf_(%d)",
                ndf, ndf_);
        MPrintErrClass(msg);
        abort();
    }
  
    if(0 != npar_free){
        fcn_min_  = tf1->GetChisquare();
        p_value_  = tf1->GetProb();
    } else {
        if(0 > chi2){
            printf("error: chi2 must be not minus\n");
            exit(1);
        }
        fcn_min_  = chi2;
        p_value_  = TMath::Prob(fcn_min_, ndf_);
    }
  
    int npar = tf1->GetNpar();
    string* par_name = new string [npar];
    double* par      = new double [npar];
    double* par_serr = new double [npar];
    int*    flag_calc_terr = new int [npar];
    int*    index_comp = new int [npar];
    double* par_lo     = new double [npar];
    double* par_up     = new double [npar];
    string* par_lo_str = new string [npar];
    string* par_up_str = new string [npar];
    for(int ipar = 0; ipar < npar; ipar ++){
        par_name[ipar] = tf1->GetParName(ipar);
        par[ipar]      = tf1->GetParameter(ipar);
        par_serr[ipar] = tf1->GetParError(ipar);
        flag_calc_terr[ipar] = 0;
        index_comp[ipar] = 0;
        
        tf1->GetParLimits(ipar, par_lo[ipar], par_up[ipar]);
        if(0 == par_lo[ipar] &&
           0 == par_up[ipar]   ){
            par_lo_str[ipar] = "none";
            par_up_str[ipar] = "none";
        } else {
            char par_lo_char[kLineSize];
            char par_up_char[kLineSize];
            sprintf(par_lo_char, "%.10e", par_lo[ipar]);
            sprintf(par_up_char, "%.10e", par_up[ipar]);
            par_lo_str[ipar] = par_lo_char;
            par_up_str[ipar] = par_up_char;
        }
    }
    fit_param_->Init(npar);
    fit_param_->SetIn(npar, par_name, par, par_serr, par_lo_str, par_up_str, flag_calc_terr, index_comp);
    fit_param_->SetPar(npar, par);
    fit_param_->SetPar(npar, par_serr);
    
    delete [] par_name;
    delete [] par;
    delete [] par_serr;
    delete [] par_lo;
    delete [] par_up;
    delete [] flag_calc_terr;
    delete [] index_comp;
}

// before fit

void FitStat::SetByFixPar(const MinFcn* const min_fcn,
                          const FitParam* const fit_param_in)
{
    fit_param_->Copy(fit_param_in);
    ndata_fit_    = min_fcn->GetNdataValid();
    ndf_          = ndata_fit_ - fit_param_in->GetNparFree();
    up_minfcn_    = min_fcn->Up();
    valid_        = 1;
    fcn_min_      = min_fcn->Eval(fit_param_in->GetNpar(),
                                  fit_param_in->GetParInit());
    edm_          = 0.0;
    nfcn_         = 0;
    p_value_      = 0.0;
    flag_bad_neg_ = min_fcn->GetFlagBadNeg();
    aic_          = fcn_min_ + 2.0 * fit_param_in->GetNparFree();
    bic_          = fcn_min_ + fit_param_in->GetNparFree() * ( log(ndata_fit_) - log(2 * M_PI) );    
    aic_c_        = aic_
        + 2 * fit_param_in->GetNparFree() * (fit_param_in->GetNparFree() + 1)
        / (ndata_fit_ - fit_param_in->GetNparFree() - 1);
}


void FitStat::SetParTerrElm(int ipar, double terr_minus, double terr_plus)
{
    if(NULL == fit_param_){
        char msg[kLineSize];
        sprintf(msg, "fit_param_ == NULL");
        MPrintErrClass(msg);
        abort();
    }
    fit_param_->SetParTerrElm(ipar, terr_minus, terr_plus);
}

void FitStat::SetValidParElm(int ipar, int flag_valid_par)
{
    if(NULL == fit_param_){
        char msg[kLineSize];
        sprintf(msg, "fit_param_ == NULL");
        MPrintErrClass(msg);
        abort();
    }
    fit_param_->SetValidParElm(ipar, flag_valid_par);
}


void FitStat::SetValidTerrElm(int ipar, int flag_valid_terr_minus, int flag_valid_terr_plus)
{
    if(NULL == fit_param_){
        char msg[kLineSize];
        sprintf(msg, "fit_param_ == NULL");
        MPrintErrClass(msg);
        abort();
    }
    fit_param_->SetValidTerrElm(ipar, flag_valid_terr_minus, flag_valid_terr_plus);
}

void FitStat::Copy(const FitStat* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    fit_param_ = new FitParam;
    fit_param_->Copy(org->GetFitParam());
    ndata_fit_    = org->GetNdataFit();
    ndf_          = org->GetNdf();
    up_minfcn_ = org->GetUpMinfcn();
    valid_        = org->GetValid();
    fcn_min_      = org->GetFcnMin();
    edm_          = org->GetEdm();
    nfcn_         = org->GetNfcn();
    p_value_      = org->GetPValue();
    flag_bad_neg_ = org->GetFlagBadNeg();
    aic_          = org->GetAic();
    bic_          = org->GetBic();
    aic_c_        = org->GetAicC();
}

FitStat* const FitStat::Clone() const
{
    FitStat* obj_new = new FitStat;
    obj_new->Copy(this);
    return obj_new;
}

void FitStat::Print(FILE* fp) const
{
    string func_name = "FitStat::Print()";
    fprintf(fp, "%s: ndata_fit_     = %d\n", func_name.c_str(), ndata_fit_);
    fprintf(fp, "%s: ndf_           = %d\n", func_name.c_str(), ndf_);
    fprintf(fp, "%s: up_minfcn_     = %e\n", func_name.c_str(), up_minfcn_);
    fprintf(fp, "%s: valid_         = %d\n", func_name.c_str(), valid_);
    fprintf(fp, "%s: fcn_min_       = %e\n", func_name.c_str(), fcn_min_);
    fprintf(fp, "%s: edm_           = %e\n", func_name.c_str(), edm_);
    fprintf(fp, "%s: nfcn_          = %d\n", func_name.c_str(), nfcn_);
    fprintf(fp, "%s: p_value_       = %e\n", func_name.c_str(), p_value_);
    fprintf(fp, "%s: flag_bad_neg_  = %d\n", func_name.c_str(), flag_bad_neg_);
    fprintf(fp, "%s: aic_           = %e\n", func_name.c_str(), aic_);
    fprintf(fp, "%s: bic_           = %e\n", func_name.c_str(), bic_);    
    fprintf(fp, "%s: aic_c_         = %e\n", func_name.c_str(), aic_c_);
    fit_param_->Print(fp);
}

// private

void FitStat::Null()
{
    if(NULL != fit_param_) {delete fit_param_; fit_param_ = NULL;}
    ndata_fit_ = 0;
    ndf_       = 0;
    up_minfcn_ = 0.0;
    valid_     = 0;
    fcn_min_   = 0.0;
    edm_       = 0.0;
    nfcn_      = 0;
    p_value_   = 0.0;
    flag_bad_neg_ = 0;
    aic_       = 0.0;
    bic_       = 0.0;    
    aic_c_     = 0.0;
}

