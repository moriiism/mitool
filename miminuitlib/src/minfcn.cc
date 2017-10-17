#include "mim_minfcn.h"

//
// MinFcn
//

// public

double MinFcn::Eval(vector<double> par_vec) const
{
    int npar = par_vec.size();
    double* par_arr = new double [npar];
    for(int ipar = 0; ipar < npar; ipar ++){
        par_arr[ipar] = par_vec[ipar];
    }
    double chi2 = Eval(par_vec.size(), par_arr);
    delete [] par_arr;
    return chi2;
}


void MinFcn::SetErrorDef(double up_minfcn)
{
    up_minfcn_ = up_minfcn;
    if(0 < g_flag_verbose){
        char msg[kLineSize];
        sprintf(msg, "MinFcn::SetErrorDef: up_minfcn_ = %e", up_minfcn_);
        MPrintInfo(msg);
    }
};


double MinFcn::GetUpMinfcn(double value, string mode, int as_npar)
{
    double confidence_level = 0.0;
    if("cl" == mode){
        confidence_level = value;
    } else if ("sigma" == mode){
        confidence_level = MirMath::Sigma2CL(value);
    }
    if(confidence_level < 0.0 || confidence_level > 1.0){
        char msg[kLineSize];
        sprintf(msg, "bad confidence_level (=%e).\n", confidence_level);
        MPrintErr(msg);
        abort();
    }
    //  double up_minfcn = ROOT::Math::chisquared_quantile(confidence_level, as_npar);
    //    double up_minfcn = ROOT::MathMore::chisquared_quantile(confidence_level, as_npar);
    double up_minfcn = ROOT::MathMore::chisquared_quantile(confidence_level, as_npar);
    return up_minfcn;
}

//
// MinFcnOne
//

MinFcnOne* const MinFcnOne::GenMinFcnOne(string minfcn_name,
                                         const MirFunc* const func,
                                         long ndata,
                                         const double* const xval_arr,
                                         const double* const yval_arr,
                                         const double* const oval_arr,
                                         const double* const oval_serr_arr,
                                         const double* const oval_terr_plus_arr,
                                         const double* const oval_terr_minus_arr,
                                         const HistData1d* const hd1d_mask,
                                         const HistData2d* const hd2d_mask)
{
    MinFcnOne* min_fcn = NULL;
    if("Chi2Fcn1d" == minfcn_name){
        min_fcn = new Chi2Fcn1d;
        min_fcn->InitSetData1d_ErrGt0(ndata,
                                      xval_arr,
                                      oval_arr,
                                      oval_serr_arr);
    } else if ("Chi2FcnAsym1d" == minfcn_name) {
        min_fcn = new Chi2FcnAsym1d;
        min_fcn->InitSetData1d_ErrGt0(ndata,
                                      xval_arr,
                                      oval_arr,
                                      oval_terr_plus_arr,
                                      oval_terr_minus_arr);
    } else if("Chi2PearsonFcn1d" == minfcn_name){
        min_fcn = new Chi2PearsonFcn1d;
        min_fcn->InitSetData1d_ValGt0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if("Chi2PearsonPhysFcn1d" == minfcn_name){
        min_fcn = new Chi2PearsonPhysFcn1d;
        min_fcn->InitSetData1d_ValGt0(ndata,
                                      xval_arr,
                                      oval_arr);        
    } else if("Chi2NeymanFcn1d" == minfcn_name){
        min_fcn = new Chi2NeymanFcn1d;
        min_fcn->InitSetData1d_ValGt0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if("Chi2NeymanPhysFcn1d" == minfcn_name){
        min_fcn = new Chi2NeymanPhysFcn1d;
        min_fcn->InitSetData1d_ValGt0(ndata,
                                      xval_arr,
                                      oval_arr);        
    } else if("Chi2NeymanModFcn1d" == minfcn_name){
        min_fcn = new Chi2NeymanModFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if("Chi2NeymanModPhysFcn1d" == minfcn_name){
        min_fcn = new Chi2NeymanModPhysFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);     
    } else if("Chi2GammaFcn1d" == minfcn_name){
        min_fcn = new Chi2GammaFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if("Chi2GammaPhysFcn1d" == minfcn_name){
        min_fcn = new Chi2GammaPhysFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);     
    } else if ("CstatFcn1d" == minfcn_name) {
        min_fcn = new CstatFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if ("CstatPhysFcn1d" == minfcn_name) {
        min_fcn = new CstatPhysFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if ("CstatDeltaFcn1d" == minfcn_name) {
        min_fcn = new CstatDeltaFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if ("CstatDeltaPhysFcn1d" == minfcn_name) {
        min_fcn = new CstatDeltaPhysFcn1d;
        min_fcn->InitSetData1d_ValGe0(ndata,
                                      xval_arr,
                                      oval_arr);
    } else if ("CstatUnbinFcn1d" == minfcn_name) {
        min_fcn = new CstatUnbinFcn1d;
        min_fcn->InitSetData1d(ndata,
                               xval_arr);
        dynamic_cast<CstatUnbinFcn1d*>(min_fcn)->InitSetHd1dMask(hd1d_mask);
    } else if ("CstatUnbinPhysFcn1d" == minfcn_name) {
        min_fcn = new CstatUnbinPhysFcn1d;
        min_fcn->InitSetData1d(ndata,
                               xval_arr);
        dynamic_cast<CstatUnbinPhysFcn1d*>(min_fcn)->InitSetHd1dMask(hd1d_mask);


        
    } else if ("Chi2Fcn2d" == minfcn_name) {
        min_fcn = new Chi2Fcn2d;
        min_fcn->InitSetData2d_ErrGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr,
                                      oval_serr_arr);
    } else if ("Chi2FcnAsym2d" == minfcn_name) {
        min_fcn = new Chi2FcnAsym2d;
        min_fcn->InitSetData2d_ErrGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr,
                                      oval_terr_plus_arr,
                                      oval_terr_minus_arr);        
    } else if("Chi2PearsonFcn2d" == minfcn_name){
        min_fcn = new Chi2PearsonFcn2d;
        min_fcn->InitSetData2d_ValGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if("Chi2PearsonPhysFcn2d" == minfcn_name){
        min_fcn = new Chi2PearsonPhysFcn2d;
        min_fcn->InitSetData2d_ValGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if("Chi2NeymanFcn2d" == minfcn_name){
        min_fcn = new Chi2NeymanFcn2d;
        min_fcn->InitSetData2d_ValGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if("Chi2NeymanPhysFcn2d" == minfcn_name){
        min_fcn = new Chi2NeymanPhysFcn2d;
        min_fcn->InitSetData2d_ValGt0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);  
    } else if("Chi2NeymanModFcn2d" == minfcn_name){
        min_fcn = new Chi2NeymanModFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if("Chi2NeymanModPhysFcn2d" == minfcn_name){
        min_fcn = new Chi2NeymanModPhysFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);  
    } else if("Chi2GammaFcn2d" == minfcn_name){
        min_fcn = new Chi2GammaFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if("Chi2GammaPhysFcn2d" == minfcn_name){
        min_fcn = new Chi2GammaPhysFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if ("CstatFcn2d" == minfcn_name) {
        min_fcn = new CstatFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if ("CstatPhysFcn2d" == minfcn_name) {
        min_fcn = new CstatPhysFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if ("CstatDeltaFcn2d" == minfcn_name) {
        min_fcn = new CstatDeltaFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if ("CstatDeltaPhysFcn2d" == minfcn_name) {
        min_fcn = new CstatDeltaPhysFcn2d;
        min_fcn->InitSetData2d_ValGe0(ndata,
                                      xval_arr,
                                      yval_arr,
                                      oval_arr);
    } else if ("CstatUnbinFcn2d" == minfcn_name) {
        min_fcn = new CstatUnbinFcn2d;
        min_fcn->InitSetData2d(ndata,
                               xval_arr,
                               yval_arr);
        dynamic_cast<CstatUnbinFcn2d*>(min_fcn)->InitSetHd2dMask(hd2d_mask);
    } else if ("CstatUnbinPhysFcn2d" == minfcn_name) {
        min_fcn = new CstatUnbinPhysFcn2d;
        min_fcn->InitSetData2d(ndata,
                               xval_arr,
                               yval_arr);
        dynamic_cast<CstatUnbinPhysFcn2d*>(min_fcn)->InitSetHd2dMask(hd2d_mask);


//   } else if ("PsdFcn1d" == minfcn_name) {
//        min_fcn = new PsdFcn1d;
//        min_fcn->InitSetData1d_ValGe0(ndata,
//                                      xval_arr,
//                                      oval_arr);
    } else {
        min_fcn = NULL;
    }

    static int flag_bad_neg = 0;    
    if(NULL != min_fcn){
        min_fcn->InitSetFunc(func);
        min_fcn->SetFlagBadNegPtrAssign(&flag_bad_neg);
    }
    return min_fcn;
}


//double MinFcn::GetRepulsion(double val_neg) const
//{
//    if(val_neg > DBL_EPSILON){
//        char msg[kLineSize];
//        sprintf(msg, "val_neg (%e) > DBL_EPSILON", val_neg);
//        MPrintErr(msg);
//        abort();
//    }
//    double cstat_slope = 1.0e5; 
//    double power_slope = 2.03e5;
//    double large_val = 1.0e5;
//        
//    double abs_val_neg = -1 * val_neg;
//    double abs_val_neg_thres = log(large_val/cstat_slope + 1.0) / power_slope;
//
//    double add_val = 0.0;
//    if(abs_val_neg < abs_val_neg_thres){
//        add_val = cstat_slope * (exp(power_slope * abs_val_neg) - 1.0);
//    } else {
//        add_val = cstat_slope * power_slope
//            * exp(power_slope * abs_val_neg_thres) * abs_val_neg_thres
//            * ( log(abs_val_neg) - log(abs_val_neg_thres) )
//            + cstat_slope * ( exp(power_slope * abs_val_neg_thres) - 1.0 );
//    }
//    return add_val;
//}


double MinFcn::GetRepulsion(double val_neg) const
{
    if(val_neg > DBL_EPSILON){
        char msg[kLineSize];
        sprintf(msg, "val_neg (%e) > DBL_EPSILON", val_neg);
        MPrintErr(msg);
        abort();
    }

    double add_val = 1e5 * pow(DBL_EPSILON - val_neg, 2) +
        1e5 * pow(DBL_EPSILON - val_neg, 4) +
        1e5 * pow(DBL_EPSILON - val_neg, 6);
    return add_val;
}



// protected

void MinFcn::CopyMinFcn(const MinFcn* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    NullMinFcn();
    up_minfcn_ = org->up_minfcn_;
    flag_bad_neg_ptr_assign_ = org->flag_bad_neg_ptr_assign_;
}

// private

void MinFcn::NullMinFcn()
{
    up_minfcn_ = 0.0;
    if(NULL != flag_bad_neg_ptr_assign_) { flag_bad_neg_ptr_assign_ = NULL;}
}


//
// MinFcnOne
//

//
// Init & Set
//

void MinFcnOne::InitSetFunc(const MirFunc* const func)
{
    if(NULL != func_) {delete func_; func_ = NULL;}
    func_ = dynamic_cast<MirFunc*>(func->Clone());
}

void MinFcnOne::InitSetData1d(long ndata,
                              const double* const xval_arr)
{
    if(NULL == xval_arr){
        MPrintErrClass("NULL == xval_arr");
        abort();
    }
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData1d(long ndata,
                              const double* const xval_arr,
                              const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr   ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr  ");
        abort();
    }
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData1d(long ndata,
                              const double* const xval_arr,
                              const double* const oval_arr,
                              const double* const oval_serr_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ||
       NULL == oval_serr_arr ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_serr_arr");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_serr_arr_) {delete [] oval_serr_arr_; oval_serr_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}    

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_serr_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_serr_arr_[idata] = oval_serr_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData1d(long ndata,
                              const double* const xval_arr,
                              const double* const oval_arr,
                              const double* const oval_terr_plus_arr,
                              const double* const oval_terr_minus_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ||
       NULL == oval_terr_plus_arr ||
       NULL == oval_terr_minus_arr  ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_terr_plus_arr || "
                       "NULL == oval_terr_minus_arr");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_terr_plus_arr_) {delete [] oval_terr_plus_arr_; oval_terr_plus_arr_ = NULL;}
    if(NULL != oval_terr_minus_arr_) {delete [] oval_terr_minus_arr_; oval_terr_minus_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}        

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_terr_plus_arr_ = new double [ndata];
    oval_terr_minus_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];    
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_terr_plus_arr_[idata] = oval_terr_plus_arr[idata];
        oval_terr_minus_arr_[idata] = oval_terr_minus_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData2d(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr)  
{
    if(NULL == xval_arr ||
       NULL == yval_arr ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr " );
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}    

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData2d(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,                    
                              const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr  ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData2d(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr,
                              const double* const oval_serr_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr ||
       NULL == oval_serr_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_serr_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}    
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_serr_arr_) {delete [] oval_serr_arr_; oval_serr_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];    
    oval_arr_ = new double [ndata];
    oval_serr_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_serr_arr_[idata] = oval_serr_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}


void MinFcnOne::InitSetData2d(long ndata,
                              const double* const xval_arr,
                              const double* const yval_arr,
                              const double* const oval_arr,
                              const double* const oval_terr_plus_arr,
                              const double* const oval_terr_minus_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr ||
       NULL == oval_terr_plus_arr ||
       NULL == oval_terr_minus_arr  ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_terr_plus_arr || "
                       "NULL == oval_terr_minus_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_terr_plus_arr_) {delete [] oval_terr_plus_arr_; oval_terr_plus_arr_ = NULL;}
    if(NULL != oval_terr_minus_arr_) {delete [] oval_terr_minus_arr_; oval_terr_minus_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}    

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_terr_plus_arr_ = new double [ndata];
    oval_terr_minus_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_terr_plus_arr_[idata] = oval_terr_plus_arr[idata];
        oval_terr_minus_arr_[idata] = oval_terr_minus_arr[idata];
        flag_bad_arr_[idata] = 0;
    }
}

void MinFcnOne::InitSetData1d_ValGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        if(oval_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData1d_ValGe0(long ndata,
                                     const double* const xval_arr,
                                     const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        if(oval_arr[idata] < 0.0 ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData1d_ErrGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const oval_arr,
                                     const double* const oval_serr_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ||
       NULL == oval_serr_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_serr_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_serr_arr_) {delete [] oval_serr_arr_; oval_serr_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}    

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_serr_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_serr_arr_[idata] = oval_serr_arr[idata];
        if(oval_serr_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData1d_ErrGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const oval_arr,
                                     const double* const oval_terr_plus_arr,
                                     const double* const oval_terr_minus_arr)
{
    if(NULL == xval_arr ||
       NULL == oval_arr ||
       NULL == oval_terr_plus_arr ||
       NULL == oval_terr_minus_arr ){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_terr_plus_arr || "
                       "NULL == oval_terr_minus_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_terr_plus_arr_) {delete [] oval_terr_plus_arr_; oval_terr_plus_arr_ = NULL;}
    if(NULL != oval_terr_minus_arr_) {delete [] oval_terr_minus_arr_; oval_terr_minus_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}        

    xval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_terr_plus_arr_ = new double [ndata];
    oval_terr_minus_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];    
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_terr_plus_arr_[idata] = oval_terr_plus_arr[idata];
        oval_terr_minus_arr_[idata] = oval_terr_minus_arr[idata];
        if(oval_terr_plus_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else if (fabs(oval_terr_minus_arr[idata]) < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}


void MinFcnOne::InitSetData2d_ValGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const yval_arr,
                                     const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr  ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}    
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        if(oval_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData2d_ValGe0(long ndata,
                                     const double* const xval_arr,
                                     const double* const yval_arr,
                                     const double* const oval_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr  ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}    
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];    
    oval_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        if(oval_arr[idata] < 0.0 ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData2d_ErrGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const yval_arr,
                                     const double* const oval_arr,
                                     const double* const oval_serr_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr ||
       NULL == oval_serr_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_serr_arr");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_serr_arr_) {delete [] oval_serr_arr_; oval_serr_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}    

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];
    oval_arr_ = new double [ndata];
    oval_serr_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_serr_arr_[idata] = oval_serr_arr[idata];
        if(oval_serr_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

void MinFcnOne::InitSetData2d_ErrGt0(long ndata,
                                     const double* const xval_arr,
                                     const double* const yval_arr,
                                     const double* const oval_arr,
                                     const double* const oval_terr_plus_arr,
                                     const double* const oval_terr_minus_arr)
{
    if(NULL == xval_arr ||
       NULL == yval_arr ||
       NULL == oval_arr ||
       NULL == oval_terr_plus_arr ||
       NULL == oval_terr_minus_arr){
        MPrintErrClass("NULL == xval_arr || "
                       "NULL == yval_arr || "
                       "NULL == oval_arr || "
                       "NULL == oval_terr_plus_arr || "
                       "NULL == oval_terr_minus_arr ");
        abort();
    }
    
    ndata_ = ndata;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_terr_plus_arr_) {delete [] oval_terr_plus_arr_; oval_terr_plus_arr_ = NULL;}
    if(NULL != oval_terr_minus_arr_) {delete [] oval_terr_minus_arr_; oval_terr_minus_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}        

    xval_arr_ = new double [ndata];
    yval_arr_ = new double [ndata];    
    oval_arr_ = new double [ndata];
    oval_terr_plus_arr_ = new double [ndata];
    oval_terr_minus_arr_ = new double [ndata];
    flag_bad_arr_ = new int [ndata];    
    for(int idata = 0; idata < ndata; idata++){
        xval_arr_[idata] = xval_arr[idata];
        yval_arr_[idata] = yval_arr[idata];
        oval_arr_[idata] = oval_arr[idata];
        oval_terr_plus_arr_[idata] = oval_terr_plus_arr[idata];
        oval_terr_minus_arr_[idata] = oval_terr_minus_arr[idata];
        if(oval_terr_plus_arr[idata] < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else if (fabs(oval_terr_minus_arr[idata]) < DBL_EPSILON ){
            flag_bad_arr_[idata] = 1;
        } else {
            flag_bad_arr_[idata] = 0;
        }
    }
}

long MinFcnOne::GetNdataValid() const
{
    long ndata_valid = 0;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(0 == GetFlagBadArrElm(idata)){
            ndata_valid ++;
        }
    }
    return ndata_valid;
}

// protected

void MinFcnOne::CopyMinFcnOne(const MinFcnOne* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    NullMinFcnOne();

    if(NULL != org->func_){
        func_ = dynamic_cast<MirFunc*>(org->GetFunc()->Clone());
    }
    ndata_ = org->ndata_;
    if(NULL != org->xval_arr_){
        xval_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            xval_arr_[idata] = org->xval_arr_[idata];
        }
    }
    if(NULL != org->yval_arr_){
        yval_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            yval_arr_[idata] = org->yval_arr_[idata];
        }
    }
    if(NULL != org->oval_arr_){
        oval_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            oval_arr_[idata] = org->oval_arr_[idata];
        }
    }
    if(NULL != org->oval_serr_arr_){
        oval_serr_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            oval_serr_arr_[idata] = org->oval_serr_arr_[idata];
        }
    }
    if(NULL != org->oval_terr_plus_arr_){
        oval_terr_plus_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            oval_terr_plus_arr_[idata] = org->oval_terr_plus_arr_[idata];
        }
    }
    if(NULL != org->oval_terr_minus_arr_){
        oval_terr_minus_arr_ = new double [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            oval_terr_minus_arr_[idata] = org->oval_terr_minus_arr_[idata];
        }
    }
    if(NULL != org->flag_bad_arr_){
        flag_bad_arr_ = new int [ndata_];
        for(long idata = 0; idata < ndata_; idata ++){
            flag_bad_arr_[idata] = org->flag_bad_arr_[idata];
        }
    }
}

// private

void MinFcnOne::NullMinFcnOne()
{
    if(NULL != func_) {delete func_; func_ = NULL;}        
    ndata_ = 0;
    if(NULL != xval_arr_) {delete [] xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete [] yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete [] oval_arr_; oval_arr_ = NULL;}
    if(NULL != oval_serr_arr_) {delete [] oval_serr_arr_; oval_serr_arr_ = NULL;}
    if(NULL != oval_terr_plus_arr_) {delete [] oval_terr_plus_arr_; oval_terr_plus_arr_ = NULL;}
    if(NULL != oval_terr_minus_arr_) {delete [] oval_terr_minus_arr_; oval_terr_minus_arr_ = NULL;}
    if(NULL != flag_bad_arr_) {delete [] flag_bad_arr_; flag_bad_arr_ = NULL;}
}


//
// Gaussian error
//


//
// Chi2Fcn1d
//

void Chi2Fcn1d::Copy(const Chi2Fcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);
}

Chi2Fcn1d* const Chi2Fcn1d::Clone() const
{
    Chi2Fcn1d* obj_new = new Chi2Fcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2Fcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                / pow(GetOvalSerrArrElm(idata), 2);
        }
    }
    return chi2;
}

//
// Chi2FcnAsym1d (asymmetrical error)
//

void Chi2FcnAsym1d::Copy(const Chi2FcnAsym1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);
}


Chi2FcnAsym1d* const Chi2FcnAsym1d::Clone() const
{
    Chi2FcnAsym1d* obj_new = new Chi2FcnAsym1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2FcnAsym1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if( func_val < GetOvalArrElm(idata) ){
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / pow(GetOvalTerrMinusArrElm(idata), 2);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / pow(GetOvalTerrPlusArrElm(idata), 2);
            }
        }
    }
    return chi2;
}

//
// Poisson error
//

//
// Chi2PearsonFcn1d 
//

void Chi2PearsonFcn1d::Copy(const Chi2PearsonFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2PearsonFcn1d* const Chi2PearsonFcn1d::Clone() const
{
    Chi2PearsonFcn1d* obj_new = new Chi2PearsonFcn1d;
    obj_new->Copy(this);
    return obj_new;
}


double Chi2PearsonFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / func_val;
            }
        }
    }
    return chi2;
}


//
// Chi2PearsonPhysFcn1d 
//

void Chi2PearsonPhysFcn1d::Copy(const Chi2PearsonPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2PearsonPhysFcn1d* const Chi2PearsonPhysFcn1d::Clone() const
{
    Chi2PearsonPhysFcn1d* obj_new = new Chi2PearsonPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}


double Chi2PearsonPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / func_val;
            }
        }
    }
    return chi2;
}

//
// Chi2NeymanFcn1d 
//

void Chi2NeymanFcn1d::Copy(const Chi2NeymanFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanFcn1d* const Chi2NeymanFcn1d::Clone() const
{
    Chi2NeymanFcn1d* obj_new = new Chi2NeymanFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / GetOvalArrElm(idata);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanPhysFcn1d 
//

void Chi2NeymanPhysFcn1d::Copy(const Chi2NeymanPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanPhysFcn1d* const Chi2NeymanPhysFcn1d::Clone() const
{
    Chi2NeymanPhysFcn1d* obj_new = new Chi2NeymanPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / GetOvalArrElm(idata);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanModFcn1d 
//

void Chi2NeymanModFcn1d::Copy(const Chi2NeymanModFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanModFcn1d* const Chi2NeymanModFcn1d::Clone() const
{
    Chi2NeymanModFcn1d* obj_new = new Chi2NeymanModFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanModFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / MirMath::GetMax(GetOvalArrElm(idata), 1.0);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanModPhysFcn1d 
//

void Chi2NeymanModPhysFcn1d::Copy(const Chi2NeymanModPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);
}


Chi2NeymanModPhysFcn1d* const Chi2NeymanModPhysFcn1d::Clone() const
{
    Chi2NeymanModPhysFcn1d* obj_new = new Chi2NeymanModPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanModPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / MirMath::GetMax(GetOvalArrElm(idata), 1.0);
            }
        }
    }
    return chi2;
}



//
// Chi2GammaFcn1d 
//

void Chi2GammaFcn1d::Copy(const Chi2GammaFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2GammaFcn1d* const Chi2GammaFcn1d::Clone() const
{
    Chi2GammaFcn1d* obj_new = new Chi2GammaFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2GammaFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) + MirMath::GetMin(GetOvalArrElm(idata), 1.0) - func_val, 2)
                    / ( GetOvalArrElm(idata) + 1.0);
            }
        }
    }
    return chi2;
}


//
// Chi2GammaPhysFcn1d 
//

void Chi2GammaPhysFcn1d::Copy(const Chi2GammaPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2GammaPhysFcn1d* const Chi2GammaPhysFcn1d::Clone() const
{
    Chi2GammaPhysFcn1d* obj_new = new Chi2GammaPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2GammaPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) + MirMath::GetMin(GetOvalArrElm(idata), 1.0) - func_val, 2)
                    / ( GetOvalArrElm(idata) + 1.0);                
            }
        }
    }
    return chi2;
}


//
// CstatFcn1d
//

void CstatFcn1d::Copy(const CstatFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatFcn1d* const CstatFcn1d::Clone() const
{
    CstatFcn1d* obj_new = new CstatFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else{
                cstat += -1 * func_val + GetOvalArrElm(idata) * log(func_val);
            }
        }
    }
    cstat *= -2.0;
    return cstat;
}


//
// CstatPhysFcn1d
//

void CstatPhysFcn1d::Copy(const CstatPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatPhysFcn1d* const CstatPhysFcn1d::Clone() const
{
    CstatPhysFcn1d* obj_new = new CstatPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    double func_val_min = DBL_MAX;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                if(func_val < func_val_min){
                    func_val_min = func_val;
                }
            } else {
                cstat += -1 * func_val + GetOvalArrElm(idata) * log(func_val);
            }
        }
    }
    cstat *= -2.0;
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(func_val_min);
    }
    return cstat;
}


//
// CstatDeltaFcn1d = chi2_lambda
//

void CstatDeltaFcn1d::Copy(const CstatDeltaFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatDeltaFcn1d* const CstatDeltaFcn1d::Clone() const
{
    CstatDeltaFcn1d* obj_new = new CstatDeltaFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatDeltaFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                if(GetOvalArrElm(idata) < DBL_EPSILON){
                    cstat += -1 * func_val + GetOvalArrElm(idata);
                } else {
                    cstat += -1 * func_val + GetOvalArrElm(idata)
                        - GetOvalArrElm(idata) * log( GetOvalArrElm(idata) / func_val);
                }
            }
        }
    }
    cstat *= -2.0;
    return cstat;
}

//
// CstatDeltaPhysFcn1d = chi2_lambda
//

void CstatDeltaPhysFcn1d::Copy(const CstatDeltaPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatDeltaPhysFcn1d* const CstatDeltaPhysFcn1d::Clone() const
{
    CstatDeltaPhysFcn1d* obj_new = new CstatDeltaPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatDeltaPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    double func_val_min = DBL_MAX;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                if(func_val < func_val_min){
                    func_val_min = func_val;
                }                
            } else {
                if(GetOvalArrElm(idata) < DBL_EPSILON){
                    cstat += -1 * func_val + GetOvalArrElm(idata);
                } else {
                    cstat += -1 * func_val + GetOvalArrElm(idata)
                        - GetOvalArrElm(idata) * log( GetOvalArrElm(idata) / func_val);
                }
            }
        }
    }
    cstat *= -2.0;
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(func_val_min);
    }
    return cstat;
}


//
// CstatUnbinFcn1d
//

void CstatUnbinFcn1d::InitSetHd1dMask(const HistData1d* const hd1d_mask)
{
    Null();
    
    hd1d_mask_ = new HistDataNerr1d;
    hd1d_mask_->Copy(hd1d_mask);
    long nbin_mask      = hd1d_mask_->GetNbinX();
    double xval_lo_mask = hd1d_mask_->GetXvalLo();
    double xval_up_mask = hd1d_mask_->GetXvalUp();
    hd1d_inner_ = new HistDataNerr1d;
    hd1d_inner_->Init(nbin_mask * 100, xval_lo_mask, xval_up_mask);
}


void CstatUnbinFcn1d::Copy(const CstatUnbinFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);

    Null();
    
    hd1d_mask_ = new HistDataNerr1d;
    hd1d_mask_->Copy(org->GetHd1dMask());
    hd1d_inner_ = new HistDataNerr1d;
    hd1d_inner_->Copy(org->GetHd1dInner());
}


CstatUnbinFcn1d* const CstatUnbinFcn1d::Clone() const
{
    CstatUnbinFcn1d* obj_new = new CstatUnbinFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatUnbinFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if(func_val < DBL_EPSILON){
            SetFlagBadNeg(1);
        } else {
            cstat += log(func_val);
        }
    }
    cstat -= GetIntegral(npar, par_arr);    
    cstat *= -2.0;
    return cstat;
}

double CstatUnbinFcn1d::GetIntegral(int npar, const double* const par_arr) const
{
    hd1d_inner_->SetByFunc(GetFunc(), par_arr);
    for(long ibin = 0; ibin < GetHd1dInner()->GetNbinX(); ibin ++){
        double mask_val = GetHd1dMask()->GetOvalElmAtX( GetHd1dInner()->GetBinCenter(ibin) );
        double oval = GetHd1dInner()->GetOvalElm(ibin) * mask_val;
        hd1d_inner_->SetOvalElm(ibin, oval);
        if(oval < 0){
            SetFlagBadNeg(1);
        }
    }

    double sum = MirMath::GetSum(GetHd1dInner()->GetOvalArr()->GetNdata(),
                                 GetHd1dInner()->GetOvalArr()->GetVal());
    double integral = sum * GetHd1dInner()->GetHi1d()->GetBinWidth();
    return integral;
}

void CstatUnbinFcn1d::Null()
{
    if(NULL != hd1d_mask_){delete hd1d_mask_; hd1d_mask_ = NULL;}
    if(NULL != hd1d_inner_){delete hd1d_inner_; hd1d_inner_ = NULL;}
}


//
// CstatUnbinPhysFcn1d
//

void CstatUnbinPhysFcn1d::InitSetHd1dMask(const HistData1d* const hd1d_mask)
{
    Null();
    hd1d_mask_ = new HistDataNerr1d;
    hd1d_mask_->Copy(hd1d_mask);
    long nbin_mask      = hd1d_mask_->GetNbinX();
    double xval_lo_mask = hd1d_mask_->GetXvalLo();
    double xval_up_mask = hd1d_mask_->GetXvalUp();
    hd1d_inner_ = new HistDataNerr1d;
    hd1d_inner_->Init(nbin_mask * 100, xval_lo_mask, xval_up_mask);
}

void CstatUnbinPhysFcn1d::Copy(const CstatUnbinPhysFcn1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);

    Null();    

    hd1d_mask_ = new HistDataNerr1d;
    hd1d_mask_->Copy(org->GetHd1dMask());
    hd1d_inner_ = new HistDataNerr1d;
    hd1d_inner_->Copy(org->GetHd1dInner());    
}


CstatUnbinPhysFcn1d* const CstatUnbinPhysFcn1d::Clone() const
{
    CstatUnbinPhysFcn1d* obj_new = new CstatUnbinPhysFcn1d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatUnbinPhysFcn1d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[1];
        val_in[0] = GetXvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if(func_val < DBL_EPSILON){
            SetFlagBadNeg(1);
        } else {
            cstat += log(func_val);
        }
    }
    double sum_of_val_minus = 0.0;
    cstat -= GetIntegral(npar, par_arr, &sum_of_val_minus);
    cstat *= -2.0;
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(sum_of_val_minus);
    }
    return cstat;
}

double CstatUnbinPhysFcn1d::GetIntegral(int npar, const double* const par_arr,
                                        double* const sum_of_val_minus_ptr) const
{
    double sum_of_val_minus = 0.0;
    hd1d_inner_->SetByFunc(GetFunc(), par_arr);
    for(long ibin = 0; ibin < GetHd1dInner()->GetNbinX(); ibin ++){
        double mask_val = GetHd1dMask()->GetOvalElmAtX( GetHd1dInner()->GetBinCenter(ibin) );
        double oval = GetHd1dInner()->GetOvalElm(ibin) * mask_val;
        hd1d_inner_->SetOvalElm(ibin, oval);
        if(oval < 0){
            SetFlagBadNeg(1);
            sum_of_val_minus += oval;
        }
    }
    *sum_of_val_minus_ptr = sum_of_val_minus;
    double sum = MirMath::GetSum(GetHd1dInner()->GetOvalArr()->GetNdata(),
                                 GetHd1dInner()->GetOvalArr()->GetVal());
    double integral = sum * GetHd1dInner()->GetHi1d()->GetBinWidth();
    return integral;
}

void CstatUnbinPhysFcn1d::Null()
{
    if(NULL != hd1d_mask_){delete hd1d_mask_; hd1d_mask_ = NULL;}
    if(NULL != hd1d_inner_){delete hd1d_inner_; hd1d_inner_ = NULL;}
}



//
// 2-dim
//

//
// Gaussian
//

//
// Chi2Fcn2d
//

void Chi2Fcn2d::Copy(const Chi2Fcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2Fcn2d* const Chi2Fcn2d::Clone() const
{
    Chi2Fcn2d* obj_new = new Chi2Fcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2Fcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long idata = 0; idata < GetNdata(); idata++){    
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                / pow(GetOvalSerrArrElm(idata), 2);
        }
    }
    return chi2;
}

//
// Chi2FcnAsym2d (asymmetrical error)
//

void Chi2FcnAsym2d::Copy(const Chi2FcnAsym2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2FcnAsym2d* const Chi2FcnAsym2d::Clone() const
{
    Chi2FcnAsym2d* obj_new = new Chi2FcnAsym2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2FcnAsym2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if( func_val < GetOvalArrElm(idata) ){
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / pow(GetOvalTerrMinusArrElm(idata), 2);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / pow(GetOvalTerrPlusArrElm(idata), 2);
            }
        }
    }
    return chi2;
}

//
// Poisson error
//

//
// Chi2PearsonFcn2d 
//

void Chi2PearsonFcn2d::Copy(const Chi2PearsonFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2PearsonFcn2d* const Chi2PearsonFcn2d::Clone() const
{
    Chi2PearsonFcn2d* obj_new = new Chi2PearsonFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2PearsonFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / func_val;
            }
        }
    }
    return chi2;
}


//
// Chi2PearsonPhysFcn2d 
//

void Chi2PearsonPhysFcn2d::Copy(const Chi2PearsonPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2PearsonPhysFcn2d* const Chi2PearsonPhysFcn2d::Clone() const
{
    Chi2PearsonPhysFcn2d* obj_new = new Chi2PearsonPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2PearsonPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / func_val;
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanFcn2d 
//

void Chi2NeymanFcn2d::Copy(const Chi2NeymanFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanFcn2d* const Chi2NeymanFcn2d::Clone() const
{
    Chi2NeymanFcn2d* obj_new = new Chi2NeymanFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / GetOvalArrElm(idata);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanPhysFcn2d 
//

void Chi2NeymanPhysFcn2d::Copy(const Chi2NeymanPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanPhysFcn2d* const Chi2NeymanPhysFcn2d::Clone() const
{
    Chi2NeymanPhysFcn2d* obj_new = new Chi2NeymanPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / GetOvalArrElm(idata);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanModFcn2d 
//

void Chi2NeymanModFcn2d::Copy(const Chi2NeymanModFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanModFcn2d* const Chi2NeymanModFcn2d::Clone() const
{
    Chi2NeymanModFcn2d* obj_new = new Chi2NeymanModFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanModFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / MirMath::GetMax(GetOvalArrElm(idata), 1.0);
            }
        }
    }
    return chi2;
}


//
// Chi2NeymanModPhysFcn2d 
//

void Chi2NeymanModPhysFcn2d::Copy(const Chi2NeymanModPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2NeymanModPhysFcn2d* const Chi2NeymanModPhysFcn2d::Clone() const
{
    Chi2NeymanModPhysFcn2d* obj_new = new Chi2NeymanModPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2NeymanModPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) - func_val, 2)
                    / MirMath::GetMax(GetOvalArrElm(idata), 1.0);
            }
        }
    }
    return chi2;
}


//
// Chi2GammaFcn2d 
//

void Chi2GammaFcn2d::Copy(const Chi2GammaFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2GammaFcn2d* const Chi2GammaFcn2d::Clone() const
{
    Chi2GammaFcn2d* obj_new = new Chi2GammaFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2GammaFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                chi2 += pow(GetOvalArrElm(idata) + MirMath::GetMin(GetOvalArrElm(idata), 1.0) - func_val, 2)
                    / ( GetOvalArrElm(idata) + 1.0);
            }
        }
    }
    return chi2;
}


//
// Chi2GammaPhysFcn2d 
//

void Chi2GammaPhysFcn2d::Copy(const Chi2GammaPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


Chi2GammaPhysFcn2d* const Chi2GammaPhysFcn2d::Clone() const
{
    Chi2GammaPhysFcn2d* obj_new = new Chi2GammaPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double Chi2GammaPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                chi2 += GetRepulsion(func_val);
            } else{
                chi2 += pow(GetOvalArrElm(idata) + MirMath::GetMin(GetOvalArrElm(idata), 1.0) - func_val, 2)
                    / ( GetOvalArrElm(idata) + 1.0);                
            }
        }
    }
    return chi2;
}


//
// CstatFcn2d
//

void CstatFcn2d::Copy(const CstatFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);
}


CstatFcn2d* const CstatFcn2d::Clone() const
{
    CstatFcn2d* obj_new = new CstatFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);        
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else{
                cstat += -1 * func_val + GetOvalArrElm(idata) * log(func_val);
            }
        }
    }
    cstat *= -2.0;
    return cstat;
}


//
// CstatPhysFcn2d
//

void CstatPhysFcn2d::Copy(const CstatPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatPhysFcn2d* const CstatPhysFcn2d::Clone() const
{
    CstatPhysFcn2d* obj_new = new CstatPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;
    SetFlagBadNeg(0);
    double func_val_min = DBL_MAX;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);

        if(func_val >1.0){
            // printf("func_val = %e\n", func_val);
        }
        
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                if(func_val < func_val_min){
                    func_val_min = func_val;
                }
            } else {
                cstat += -1 * func_val + GetOvalArrElm(idata) * log(func_val);
            }
        }
    }
    cstat *= -2.0;

    // printf("cstat_before = %e\n", cstat);
    
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(func_val_min);
    }
    // printf("cstat_after = %e\n", cstat);
    
    return cstat;
}

double CstatPhysFcn2d::GetProb(int npar, const double* const par_arr) const
{
    double cstat = Eval(npar, par_arr);
    double factor = 1.0;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val >= DBL_EPSILON){
                factor *= TMath::Factorial(GetOvalArrElm(idata));
            }
        }
    }
    printf("factor = %e\n", factor);
    printf("cstat = %e\n", cstat);
    double prob = exp( - cstat / 2.0) / factor;
    return prob;
}


//
// CstatDeltaFcn2d = chi2_lambda
//

void CstatDeltaFcn2d::Copy(const CstatDeltaFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatDeltaFcn2d* const CstatDeltaFcn2d::Clone() const
{
    CstatDeltaFcn2d* obj_new = new CstatDeltaFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatDeltaFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
            } else {
                if(GetOvalArrElm(idata) < DBL_EPSILON){
                    cstat += -1 * func_val + GetOvalArrElm(idata);
                } else {
                    cstat += -1 * func_val + GetOvalArrElm(idata)
                        - GetOvalArrElm(idata) * log( GetOvalArrElm(idata) / func_val);
                }
            }
        }
    }
    cstat *= -2.0;
    return cstat;
}

//
// CstatDeltaPhysFcn2d = chi2_lambda
//

void CstatDeltaPhysFcn2d::Copy(const CstatDeltaPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);    
}


CstatDeltaPhysFcn2d* const CstatDeltaPhysFcn2d::Clone() const
{
    CstatDeltaPhysFcn2d* obj_new = new CstatDeltaPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatDeltaPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    double func_val_min = DBL_MAX;
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);        
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if( 0 == GetFlagBadArrElm(idata) ){
            if(func_val < DBL_EPSILON){
                SetFlagBadNeg(1);
                if(func_val < func_val_min){
                    func_val_min = func_val;
                }                
            } else {
                if(GetOvalArrElm(idata) < DBL_EPSILON){
                    cstat += -1 * func_val + GetOvalArrElm(idata);
                } else {
                    cstat += -1 * func_val + GetOvalArrElm(idata)
                        - GetOvalArrElm(idata) * log( GetOvalArrElm(idata) / func_val);
                }
            }
        }
    }
    cstat *= -2.0;
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(func_val_min);
    }
    return cstat;
}

//
// CstatUnbinFcn2d
//

void CstatUnbinFcn2d::InitSetHd2dMask(const HistData2d* const hd2d_mask)
{
    Null();
    
    hd2d_mask_ = new HistDataNerr2d;
    hd2d_mask_->Copy(hd2d_mask);
    long nbinx_mask     = hd2d_mask_->GetNbinX();
    double xval_lo_mask = hd2d_mask_->GetXvalLo();
    double xval_up_mask = hd2d_mask_->GetXvalUp();
    long nbiny_mask     = hd2d_mask_->GetNbinY();
    double yval_lo_mask = hd2d_mask_->GetYvalLo();
    double yval_up_mask = hd2d_mask_->GetYvalUp();    
    
    hd2d_inner_ = new HistDataNerr2d;
    hd2d_inner_->Init(nbinx_mask * 100, xval_lo_mask, xval_up_mask,
                      nbiny_mask * 100, yval_lo_mask, yval_up_mask);
}

void CstatUnbinFcn2d::Copy(const CstatUnbinFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);

    Null();

    hd2d_mask_ = new HistDataNerr2d;
    hd2d_mask_->Copy(org->GetHd2dMask());
    hd2d_inner_ = new HistDataNerr2d;
    hd2d_inner_->Copy(org->GetHd2dInner());
}


CstatUnbinFcn2d* const CstatUnbinFcn2d::Clone() const
{
    CstatUnbinFcn2d* obj_new = new CstatUnbinFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatUnbinFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if(func_val < DBL_EPSILON){
            SetFlagBadNeg(1);
        } else {
            cstat += log(func_val);
        }
    }
    cstat -= GetIntegral(npar, par_arr);
    cstat *= -2.0;
    return cstat;
}

double CstatUnbinFcn2d::GetIntegral(int npar, const double* const par_arr) const
{
    hd2d_inner_->SetByFunc(GetFunc(), par_arr);
    for(long ibin = 0; ibin < GetHd2dInner()->GetNbin(); ibin ++){
        double mask_val = GetHd2dMask()->GetOvalElmAtXY(
            GetHd2dInner()->GetHi2d()->GetBinCenterXFromIbin(ibin),
            GetHd2dInner()->GetHi2d()->GetBinCenterYFromIbin(ibin));
        long ibin_x = GetHd2dInner()->GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHd2dInner()->GetHi2d()->GetIbinY(ibin);
        double oval = GetHd2dInner()->GetOvalElm(ibin_x, ibin_y) * mask_val;
        hd2d_inner_->SetOvalElm(ibin_x, ibin_y, oval);
        if(oval < 0){
            SetFlagBadNeg(1);
        }
    }
    double sum = MirMath::GetSum(GetHd2dInner()->GetOvalArr()->GetNdata(),
                                 GetHd2dInner()->GetOvalArr()->GetVal());
    double integral = sum * GetHd2dInner()->GetBinArea();
    return integral;
}

void CstatUnbinFcn2d::Null()
{
    if(NULL != hd2d_mask_){delete hd2d_mask_; hd2d_mask_ = NULL;}
    if(NULL != hd2d_inner_){delete hd2d_inner_; hd2d_inner_ = NULL;}
}

//
// CstatUnbinPhysFcn2d
//

void CstatUnbinPhysFcn2d::InitSetHd2dMask(const HistData2d* const hd2d_mask)
{
    Null();
    
    hd2d_mask_ = new HistDataNerr2d;
    hd2d_mask_->Copy(hd2d_mask);
    long nbinx_mask     = hd2d_mask_->GetNbinX();
    double xval_lo_mask = hd2d_mask_->GetXvalLo();
    double xval_up_mask = hd2d_mask_->GetXvalUp();
    long nbiny_mask     = hd2d_mask_->GetNbinY();
    double yval_lo_mask = hd2d_mask_->GetYvalLo();
    double yval_up_mask = hd2d_mask_->GetYvalUp();    
    hd2d_inner_ = new HistDataNerr2d;
    hd2d_inner_->Init(nbinx_mask * 100, xval_lo_mask, xval_up_mask,
                      nbiny_mask * 100, yval_lo_mask, yval_up_mask);
}

void CstatUnbinPhysFcn2d::Copy(const CstatUnbinPhysFcn2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnOne(org);

    Null();

    hd2d_mask_ = new HistDataNerr2d;
    hd2d_mask_->Copy(org->GetHd2dMask());
    hd2d_inner_ = new HistDataNerr2d;
    hd2d_inner_->Copy(org->GetHd2dInner());
}


CstatUnbinPhysFcn2d* const CstatUnbinPhysFcn2d::Clone() const
{
    CstatUnbinPhysFcn2d* obj_new = new CstatUnbinPhysFcn2d;
    obj_new->Copy(this);
    return obj_new;
}

double CstatUnbinPhysFcn2d::Eval(int npar, const double* const par_arr) const
{
    double cstat = 0.0;    
    SetFlagBadNeg(0);
    for(long idata = 0; idata < GetNdata(); idata++){
        double val_in[2];
        val_in[0] = GetXvalArrElm(idata);
        val_in[1] = GetYvalArrElm(idata);
        double func_val = GetFunc()->Eval(val_in, par_arr);
        if(func_val < DBL_EPSILON){
            SetFlagBadNeg(1);
        } else {
            cstat += log(func_val);
        }
    }
    double sum_of_val_minus = 0.0;
    cstat -= GetIntegral(npar, par_arr, &sum_of_val_minus);
    cstat *= -2.0;
    if(1 == GetFlagBadNeg()){
        cstat += GetRepulsion(sum_of_val_minus);
    }
    return cstat;
}


double CstatUnbinPhysFcn2d::GetIntegral(int npar, const double* const par_arr,
                                        double* const sum_of_val_minus_ptr) const
{
    double sum_of_val_minus = 0.0;
    hd2d_inner_->SetByFunc(GetFunc(), par_arr);
    for(long ibin = 0; ibin < GetHd2dInner()->GetNbin(); ibin ++){
        double mask_val = GetHd2dMask()->GetOvalElmAtXY(
            GetHd2dInner()->GetHi2d()->GetBinCenterXFromIbin(ibin),
            GetHd2dInner()->GetHi2d()->GetBinCenterYFromIbin(ibin));
        long ibin_x = GetHd2dInner()->GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHd2dInner()->GetHi2d()->GetIbinY(ibin);
        double oval = GetHd2dInner()->GetOvalElm(ibin_x, ibin_y) * mask_val;
        hd2d_inner_->SetOvalElm(ibin_x, ibin_y, oval);
        if(oval < 0){
            SetFlagBadNeg(1);
            sum_of_val_minus += oval;
        }
    }
    *sum_of_val_minus_ptr = sum_of_val_minus;
    double sum = MirMath::GetSum(GetHd2dInner()->GetOvalArr()->GetNdata(),
                                 GetHd2dInner()->GetOvalArr()->GetVal());
    double integral = sum * GetHd2dInner()->GetBinArea();
    return integral;
}

void CstatUnbinPhysFcn2d::Null()
{
    if(NULL != hd2d_mask_){delete hd2d_mask_; hd2d_mask_ = NULL;}
    if(NULL != hd2d_inner_){delete hd2d_inner_; hd2d_inner_ = NULL;}
}


////
//////
////// PSD
//////
//
//void PsdFcn1d::Copy(const PsdFcn1d* const org)
//{
//    if(this == org) {return;}
//    if(NULL == org) {return;}
//    
//    CopyTitle(org);
//    CopyMinFcn(org);
//    CopyMinFcnOne(org);
//}
//
//
//PsdFcn1d* const PsdFcn1d::Clone() const
//{
//    PsdFcn1d* obj_new = new PsdFcn1d;
//    obj_new->Copy(this);
//    return obj_new;
//}
//
////
//double PsdFcn1d::Eval(int npar, const double* const par_arr) const
//{
//    double cstat = 0.0;
//    for(long idata = 0; idata < GetNdata(); idata++){
//        double val_in[1];
//        val_in[0] = GetXvaArrElm(idata);
//        double func_val = GetFunc()->Eval(val_in, par_arr);
//        cstat += GetOvaArrElm(idata) / func_val;
//    }
//    cstat *= 2.0;
//    return cstat;
//}
//

//
// MinFcnMulti
//

// public

void MinFcnMulti::InitSetMinfcn1Arr(int num_minfcn1, MinFcnOne** const minfcn1_arr)
{
    NullMinFcnMulti();
    
    num_minfcn1_ = num_minfcn1;
    minfcn1_arr_ = new MinFcnOne* [num_minfcn1_];
    for(int iminfcn1 = 0; iminfcn1 < num_minfcn1; iminfcn1 ++){
        minfcn1_arr_[iminfcn1] = minfcn1_arr[iminfcn1]->Clone();
    }
}

double MinFcnMulti::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long iminfcn1 = 0; iminfcn1 < GetNumMinfcn1(); iminfcn1++){
        chi2 += GetMinfcn1ArrElm(iminfcn1)->Eval(npar, par_arr);
    }
    return chi2;
}


int MinFcnMulti::GetFlagBadNeg() const
{
    int flag_bad_neg = 0;
    for(long iminfcn1 = 0; iminfcn1 < GetNumMinfcn1(); iminfcn1++){
        flag_bad_neg += GetMinfcn1ArrElm(iminfcn1)->GetFlagBadNeg();
    }
    return flag_bad_neg;
}

long MinFcnMulti::GetNdataValid() const
{
    long ndata_valid = 0;
    for(long iminfcn1 = 0; iminfcn1 < GetNumMinfcn1(); iminfcn1++){
        ndata_valid += GetMinfcn1ArrElm(iminfcn1)->GetNdataValid();
    }
    return ndata_valid;
}

// protected

void MinFcnMulti::CopyMinFcnMulti(const MinFcnMulti* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    NullMinFcnMulti();

    num_minfcn1_ = org->num_minfcn1_;
    minfcn1_arr_ = new MinFcnOne* [num_minfcn1_];
    for(int iminfcn1 = 0; iminfcn1 < num_minfcn1_; iminfcn1 ++){
        minfcn1_arr_[iminfcn1] = org->GetMinfcn1ArrElm(iminfcn1)->Clone();
    }
}

// private

void MinFcnMulti::NullMinFcnMulti()
{
    for(int iminfcn1 = 0; iminfcn1 < num_minfcn1_; iminfcn1 ++){
        if(NULL != minfcn1_arr_[iminfcn1]) { delete minfcn1_arr_[iminfcn1]; minfcn1_arr_[iminfcn1] = NULL;}
    }
    if(NULL != minfcn1_arr_) { delete [] minfcn1_arr_; minfcn1_arr_ = NULL;}
    num_minfcn1_ = 0;
}


//
// MinFcnMultiSame
//

// public


void MinFcnMultiSame::Copy(const MinFcnMultiSame* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnMulti(org);
}

MinFcnMultiSame* const MinFcnMultiSame::Clone() const
{
    MinFcnMultiSame* obj_new = new MinFcnMultiSame;
    obj_new->Copy(this);
    return obj_new;
}


double MinFcnMultiSame::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(long iminfcn1 = 0; iminfcn1 < GetNumMinfcn1(); iminfcn1++){
        chi2 += GetMinfcn1ArrElm(iminfcn1)->Eval(npar, par_arr);
    }
    return chi2;
}



//
// MinFcnLincombMultiTie
//

void MinFcnLincombMultiTie::SetFuncLincombParIndex(const MimFuncLincombParIndex* const func_lincomb_par_index)
{
    Null();
    func_lincomb_par_index_assign_ = func_lincomb_par_index;
}

void MinFcnLincombMultiTie::Copy(const MinFcnLincombMultiTie* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMinFcn(org);
    CopyMinFcnMulti(org);

    Null();
    SetFuncLincombParIndex(org->GetFuncLincombParIndex());
}


double MinFcnLincombMultiTie::Eval(int npar, const double* const par_arr) const
{
    double chi2 = 0.0;
    for(int iminfcn1 = 0; iminfcn1 < GetNumMinfcn1(); iminfcn1++){
        int npar_inner = GetMinfcn1ArrElm(iminfcn1)->GetFunc()->GetNpar();
        double* par_inner_arr = new double [npar_inner];
        int ipar_inner = 0;
        for(int ifunc = 0; ifunc < GetFuncLincombParIndex()->GetNfuncArrElm(iminfcn1); ifunc ++){
            for(int ipar = 0; ipar < GetFuncLincombParIndex()->GetNparBaseArrElm(iminfcn1, ifunc); ipar ++){
                int index = GetFuncLincombParIndex()->GetIndexBaseArrElm(iminfcn1, ifunc, ipar)->GetValLink();
                par_inner_arr[ipar_inner] = par_arr[index];
                ipar_inner ++;
            }
        }
        for(int ipar = 0; ipar < GetFuncLincombParIndex()->GetNparCoeffArrElm(iminfcn1); ipar ++){
            int index = GetFuncLincombParIndex()->GetIndexCoeffArrElm(iminfcn1, ipar)->GetValLink();
            par_inner_arr[ipar_inner] = par_arr[index];
            ipar_inner ++;
        }
        chi2 += GetMinfcn1ArrElm(iminfcn1)->Eval(npar_inner, par_inner_arr);
        delete [] par_inner_arr;
    }
    return chi2;
}

MinFcnLincombMultiTie* const MinFcnLincombMultiTie::Clone() const
{
    MinFcnLincombMultiTie* obj_new = new MinFcnLincombMultiTie;
    obj_new->Copy(this);
    return obj_new;
}

// private

void MinFcnLincombMultiTie::Null()
{
    if(NULL != func_lincomb_par_index_assign_){
        func_lincomb_par_index_assign_ = NULL;
    }
}


//
// MinFcnPhot
//

void MinFcnPhot::InitSet(int ndata,
                         const int* const nevt_src_arr,
                         const int* const nevt_bg_arr,
                         const double* const effarea_arr,
                         const double* const area_src_arr,
                         const double* const area_bg_arr,
                         const double* const exposure_arr)
{
    Null();
    ndata_ = ndata;
    nevt_src_arr_  = new int [ndata];
    nevt_bg_arr_   = new int [ndata];
    effarea_arr_   = new double [ndata];
    area_src_arr_  = new double [ndata];
    area_bg_arr_   = new double [ndata];
    exposure_arr_  = new double [ndata];
    for(int idata = 0; idata < ndata; idata ++){
        nevt_src_arr_[idata] = nevt_src_arr[idata];
        nevt_bg_arr_[idata]  = nevt_bg_arr[idata];
        effarea_arr_[idata]  = effarea_arr[idata];
        area_src_arr_[idata] = area_src_arr[idata];
        area_bg_arr_[idata]  = area_bg_arr[idata];
        exposure_arr_[idata] = exposure_arr[idata];
    }
    static int flag_bad_neg = 0;
    SetFlagBadNegPtrAssign(&flag_bad_neg);
}

void MinFcnPhot::Copy(const MinFcnPhot* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
    CopyMinFcn(org);

    Null();
    InitSet(org->ndata_,
            org->nevt_src_arr_,
            org->nevt_bg_arr_,
            org->effarea_arr_,
            org->area_src_arr_,
            org->area_bg_arr_,
            org->exposure_arr_);
}

MinFcnPhot* const MinFcnPhot::Clone() const
{
    MinFcnPhot* obj_new = new MinFcnPhot;
    obj_new->Copy(this);
    return obj_new;
}


double MinFcnPhot::Eval(int npar, const double* const par_arr) const
{
    double flux = par_arr[0];
    double* rate_bg_arr = new double [npar - 1];
    for(int ipar = 1; ipar < npar; ipar ++){
        rate_bg_arr[ipar - 1]  = par_arr[ipar];
    }
    double cstat = 0.0;
    for(int idata = 0; idata < GetNdata(); idata ++){
        cstat += GetNevtSrcArrElm(idata)
            * log( flux * GetEffareaArrElm(idata) + rate_bg_arr[idata] * GetAreaSrcArrElm(idata) )
            + GetNevtBgArrElm(idata)
            * log( rate_bg_arr[idata] * GetAreaBgArrElm(idata) )
            - ( flux * GetEffareaArrElm(idata)
                + rate_bg_arr[idata] * GetAreaSrcArrElm(idata)
                + rate_bg_arr[idata] * GetAreaBgArrElm(idata) ) * GetExposureArrElm(idata);
    }
    cstat *= -2.0;
    delete [] rate_bg_arr;
    return cstat;
}

long MinFcnPhot::GetNdataValid() const
{
    long ndata_valid = GetNdata() * 2;
    return ndata_valid;
}

// private

void MinFcnPhot::Null()
{
    ndata_ = 0;
    if(NULL != nevt_src_arr_) {delete [] nevt_src_arr_; nevt_src_arr_ = NULL;}
    if(NULL != nevt_bg_arr_) {delete [] nevt_bg_arr_; nevt_bg_arr_ = NULL;}
    if(NULL != effarea_arr_) {delete [] effarea_arr_; effarea_arr_ = NULL;}
    if(NULL != area_src_arr_) {delete [] area_src_arr_; area_src_arr_ = NULL;}
    if(NULL != area_bg_arr_) {delete [] area_bg_arr_; area_bg_arr_ = NULL;}
    if(NULL != exposure_arr_) {delete [] exposure_arr_; exposure_arr_ = NULL;}
}


//
// MinFcnPhotScan
//

void MinFcnPhotScan::InitSet(int ndata,
                             const int* const nevt_src_arr,
                             const int* const nevt_bg_arr,
                             const double* const effarea_time_arr,
                             const double* const area_src_arr,
                             const double* const area_bg_arr)
{
    Null();
    ndata_ = ndata;
    nevt_src_arr_     = new int [ndata];
    nevt_bg_arr_      = new int [ndata];
    effarea_time_arr_ = new double [ndata];
    area_src_arr_     = new double [ndata];
    area_bg_arr_      = new double [ndata];
    for(int idata = 0; idata < ndata; idata ++){
        nevt_src_arr_[idata]     = nevt_src_arr[idata];
        nevt_bg_arr_[idata]      = nevt_bg_arr[idata];
        effarea_time_arr_[idata] = effarea_time_arr[idata];
        area_src_arr_[idata]     = area_src_arr[idata];
        area_bg_arr_[idata]      = area_bg_arr[idata];
    }
    static int flag_bad_neg = 0;
    SetFlagBadNegPtrAssign(&flag_bad_neg);
}

void MinFcnPhotScan::Copy(const MinFcnPhotScan* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
    CopyMinFcn(org);

    Null();
    InitSet(org->ndata_,
            org->nevt_src_arr_,
            org->nevt_bg_arr_,
            org->effarea_time_arr_,
            org->area_src_arr_,
            org->area_bg_arr_);
}

MinFcnPhotScan* const MinFcnPhotScan::Clone() const
{
    MinFcnPhotScan* obj_new = new MinFcnPhotScan;
    obj_new->Copy(this);
    return obj_new;
}


double MinFcnPhotScan::Eval(int npar, const double* const par_arr) const
{
    double flux = par_arr[0];
    double* rate_bg_arr = new double [npar - 1];
    for(int ipar = 1; ipar < npar; ipar ++){
        rate_bg_arr[ipar - 1]  = par_arr[ipar];
    }
    double cstat = 0.0;
    for(int idata = 0; idata < GetNdata(); idata ++){
        cstat += GetNevtSrcArrElm(idata)
            * log( flux * GetEffareaTimeArrElm(idata) + rate_bg_arr[idata] * GetAreaSrcArrElm(idata) )
            + GetNevtBgArrElm(idata)
            * log( rate_bg_arr[idata] * GetAreaBgArrElm(idata) )
            - ( flux * GetEffareaTimeArrElm(idata)
                + rate_bg_arr[idata] * GetAreaSrcArrElm(idata)
                + rate_bg_arr[idata] * GetAreaBgArrElm(idata) );
    }
    cstat *= -2.0;
    delete [] rate_bg_arr;
    return cstat;
}

long MinFcnPhotScan::GetNdataValid() const
{
    long ndata_valid = GetNdata() * 2;
    return ndata_valid;
}

// private

void MinFcnPhotScan::Null()
{
    ndata_ = 0;
    if(NULL != nevt_src_arr_) {delete [] nevt_src_arr_; nevt_src_arr_ = NULL;}
    if(NULL != nevt_bg_arr_) {delete [] nevt_bg_arr_; nevt_bg_arr_ = NULL;}
    if(NULL != effarea_time_arr_) {delete [] effarea_time_arr_; effarea_time_arr_ = NULL;}
    if(NULL != area_src_arr_) {delete [] area_src_arr_; area_src_arr_ = NULL;}
    if(NULL != area_bg_arr_) {delete [] area_bg_arr_; area_bg_arr_ = NULL;}
}


