#include "mit_func_pls.h"

//
// FuncPls
//

void FuncPls::InitSet(string tunit, double mjdref,
                      const Ephemeris* const eph,
                      const BinaryOrb1* const binorb)
{
    NullFuncPls();
    
    tunit_  = tunit;
    mjdref_ = mjdref;
    if(NULL != eph){
        eph_ = new Ephemeris;
        eph_->Copy(eph);
    }
    if(NULL != binorb){
        binorb_ = new BinaryOrb1;
        binorb_->Copy(binorb);
        func_bin_orb_obs_time_ = new BinaryOrbObsTimeFunc;
        func_bin_orb_obs_time_->Init(binorb_);
    }
}

FuncPls* FuncPls::GenFuncPls(string func_name)
{
    FuncPls* func = NULL;
    if("SinePlusConstFunc" == func_name){
        func = new SinePlusConstFunc;
    } else if ("MaxiSankakuFunc" == func_name) {
        func = new MaxiSankakuFunc;
    } else if ("SinePlusConstBinOrbFunc" == func_name) {
        func = new SinePlusConstBinOrbFunc;
    } else {
        printf("GenFuncPls: error: bad func_name (=%s).\n", func_name.c_str());
        exit(1);
    }
    return func;
}

void FuncPls::NullFuncPls()
{
    tunit_  = ""; 
    mjdref_ = 0.0;
    if(NULL != eph_) {delete eph_; eph_ = NULL;}
    if(NULL != binorb_) {delete binorb_; binorb_ = NULL;}
    if(NULL != func_bin_orb_obs_time_) {delete func_bin_orb_obs_time_; func_bin_orb_obs_time_ = NULL;}
}

void FuncPls::CopyFuncPls(const FuncPls* const org)
{
    NullFuncPls();
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
}

//
// pulse profile
//


void SinePlusConstFunc::Copy(const SinePlusConstFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    CopyFuncPls(org);
    
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
}

SinePlusConstFunc* const SinePlusConstFunc::Clone() const
{
    SinePlusConstFunc* obj_new = new SinePlusConstFunc;
    obj_new->Copy(this);
    return obj_new;
}


double SinePlusConstFunc::Eval(const double* const xval,
                               const double* const par) const
{
    double time        = xval[0];
    double amplitude   = par[0];
    double constant    = par[1];
    
    double time_mjd
        = TimeConv::TimeToMjd(time,
                              GetMjdref(), GetTunit());
    double phase = GetEph()->GetPhaseAtTimeMjd(time_mjd);
    double ans = amplitude * sin( 2.0 * kPi * phase ) + constant;
    return ans;
}


//
//
//double FuncPulseSinConst::Eval(const double xval[], const double par[]) const
//{
//  double phase = xval[0]; // phase : 0 - 1
//  double val = constant_ * (pulsefraction_ * sin(2 * M_PI * phase) + 1.);
//  return val;
//}
//
//

//
// MaxiSankakuFunc
//

//
// unit (effective area, cm^2)
//

void MaxiSankakuFunc::Copy(const MaxiSankakuFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    CopyFuncPls(org);
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
}

MaxiSankakuFunc* const MaxiSankakuFunc::Clone() const
{
    MaxiSankakuFunc* obj_new = new MaxiSankakuFunc;
    obj_new->Copy(this);
    return obj_new;
}

double MaxiSankakuFunc::Eval(const double* const xval,
                             const double* const par) const
{
    double time = xval[0];
    double time_mjd
        = TimeConv::TimeToMjd(time,
                              GetMjdref(),
                              GetTunit());
    double phase = GetEph()->GetPhaseAtTimeMjd(time_mjd);    

    double phase_st = 0.0;
    double phase_ed = 1.0 / 90.0; // 1 min scan in 90. min
    double val_peak = 10.0;
    double phase_center = (phase_st + phase_ed)/2.;

    double val = 0.0;
    if(phase_st <= phase && phase < phase_center){
        val = val_peak * (phase - phase_st) / (phase_center - phase_st);
    } else if (phase_center <= phase && phase <= phase_ed){
        val = val_peak * (phase_ed - phase) / (phase_ed - phase_center);
    } else {
        val = 0.0;
    }
    return val;
}


//
// binary modulated pulse profile
//

void SinePlusConstBinOrbFunc::Copy(const SinePlusConstBinOrbFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    CopyFuncPls(org);
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
}

SinePlusConstBinOrbFunc* const SinePlusConstBinOrbFunc::Clone() const
{
    SinePlusConstBinOrbFunc* obj_new = new SinePlusConstBinOrbFunc;
    obj_new->Copy(this);
    return obj_new;
}

double SinePlusConstBinOrbFunc::Eval(const double* const xval,
                                     const double* const par) const
{
    double time_obs    = xval[0];
    double amplitude   = par[0];
    double constant    = par[1];

    double time_obs_mjd
        = TimeConv::TimeToMjd(time_obs,
                              GetMjdref(), GetTunit());
    double time_obj_mjd = BinaryOrb1::GetTimeObj(GetFuncBinOrbObsTime(),
                                                 time_obs_mjd,
                                                 GetBinorb()->GetPeriod());
    double phase = GetEph()->GetPhaseAtTimeMjd(time_obj_mjd);
    double ans = amplitude * sin( 2.0 * kPi * phase ) + constant;
    return ans;
}


//
// histogram repeat
//

void HistPlsFunc::InitSetHd1d(const HistData1d* const hd1d)
{
    Null();
    
    long nbin = hd1d->GetNbinX();
    long nbin_new = nbin + 2;
    double delta_xval  = hd1d->GetHi1d()->GetBinWidth();
    double xval_lo_new = hd1d->GetXvalLo() - delta_xval;
    double xval_up_new = hd1d->GetXvalUp() + delta_xval;

    hd1d_with_margin_ = new HistDataNerr1d;
    hd1d_with_margin_->Init(nbin_new, xval_lo_new, xval_up_new);
    hd1d_with_margin_->SetOvalElm(0, hd1d->GetOvalElm(nbin - 1));
    for(long ibin = 0; ibin < nbin; ibin ++){
        hd1d_with_margin_->SetOvalElm(ibin + 1, hd1d->GetOvalElm(ibin));
    }
    hd1d_with_margin_->SetOvalElm(nbin_new - 1, hd1d->GetOvalElm(0));
}

void HistPlsFunc::Copy(const HistPlsFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    CopyFuncPls(org);
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
    Null();
    hd1d_with_margin_ = new HistDataNerr1d;
    hd1d_with_margin_->Copy(org->GetHd1dWithMargin());
}

HistPlsFunc* const HistPlsFunc::Clone() const
{
    HistPlsFunc* obj_new = new HistPlsFunc;
    obj_new->Copy(this);
    return obj_new;
}

double HistPlsFunc::Eval(const double* const xval,
                         const double* const par) const
{
    double time        = xval[0];
    double time_mjd
        = TimeConv::TimeToMjd(time,
                              GetMjdref(), GetTunit());
    double phase = GetEph()->GetPhaseAtTimeMjd(time_mjd);
    double ans = GetHd1dWithMargin()->GetOvalIntPolLin(phase);
    return ans;
}

// private

void HistPlsFunc::Null()
{
    if(NULL != hd1d_with_margin_)
        {delete hd1d_with_margin_; hd1d_with_margin_ = NULL;}
}

//
// GraphPlsFunc
//
// graph repeat
//

void GraphPlsFunc::InitSetGd2d(const GraphData2d* const gd2d)
{
    Null();
    
    gd2d_ = new GraphDataNerr2d;
    gd2d_->Copy(gd2d);
}

void GraphPlsFunc::Copy(const GraphPlsFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
    CopyMirFunc(org);
    CopyFuncPls(org);
    
    InitSet(org->GetTunit(),
            org->GetMjdref(),
            org->GetEph(),
            org->GetBinorb());
    InitSetGd2d(org->GetGd2d());
}

GraphPlsFunc* const GraphPlsFunc::Clone() const
{
    GraphPlsFunc* obj_new = new GraphPlsFunc;
    obj_new->Copy(this);
    return obj_new;
}

double GraphPlsFunc::Eval(const double* const xval,
                          const double* const par) const
{
    double time        = xval[0];
    double time_mjd
        = TimeConv::TimeToMjd(time,
                              GetMjdref(), GetTunit());
    double phase = GetEph()->GetPhaseAtTimeMjd(time_mjd);
    double ans = GetGd2d()->GetOvalIntPolLin(phase);
    return ans;
}

// private

void GraphPlsFunc::Null()
{
    if(NULL != gd2d_) {delete gd2d_; gd2d_ = NULL;}
}

