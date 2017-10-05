#include "mit_func_maxiobs.h"

//
// count rate (c/s) functions
//

void MaxiObsFunc::Init(const MirFunc* const func_flux)
{
    Null();

    func_maxi_sankaku_ = new MaxiSankakuFunc;
    Ephemeris* eph_maxi = new Ephemeris;
    double nu_maxi      = 1./(90. * 60.); // 90 min
    double nu_err_dummy      = 0.0;
    double nu_dot_dummy      = 0.0;
    double nu_dot_err_dummy  = 0.0;
    double nu_dot2_dummy     = 0.0;
    double nu_dot2_err_dummy = 0.0;
    double nu_dot3_dummy     = 0.0;
    double nu_dot3_err_dummy = 0.0;
    double phase_dummy       = 0.0;
    double phase_err_dummy   = 0.0;
    double epoch_mjd_dummy   = 0.0;
    double t_st_mjd_dummy    = 0.0;
    double t_ed_mjd_dummy    = 0.0;
    eph_maxi->Set(nu_maxi,
                  nu_err_dummy, nu_dot_dummy, nu_dot_err_dummy, nu_dot2_dummy,
                  nu_dot2_err_dummy, nu_dot3_dummy, nu_dot3_err_dummy,
                  phase_dummy, phase_err_dummy, epoch_mjd_dummy,
                  t_st_mjd_dummy, t_ed_mjd_dummy);
    // func_maxi_sankaku_->Set("sec", Telescope::GetMjdref("MAXI"), eph_maxi);
    delete eph_maxi;

    // func_flux_ = func_flux->Clone();
}

void MaxiObsFunc::Copy(const MaxiObsFunc* const org)
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
    Init(org->GetFuncFlux());
}

MaxiObsFunc* const MaxiObsFunc::Clone() const
{
    MaxiObsFunc* obj_new = new MaxiObsFunc;
    obj_new->Copy(this);
    return obj_new;
}

double MaxiObsFunc::Eval(const double* const xval,
                         const double* const par) const
{
    double ans = func_flux_->Eval(xval, par)
        * func_maxi_sankaku_->Eval(xval, NULL);
    return ans;
}

// private

void MaxiObsFunc::Null()
{
    if(NULL != func_flux_) {delete func_flux_; func_flux_ = NULL;}
    if(NULL != func_maxi_sankaku_) {delete func_maxi_sankaku_; func_maxi_sankaku_ = NULL;}
}

