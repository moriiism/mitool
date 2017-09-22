#include "mifc_std.h"

//
// Gauss1dFunc
//

void Gauss1dFunc::Copy(const Gauss1dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

Gauss1dFunc* const Gauss1dFunc::Clone() const
{
    Gauss1dFunc* obj_new = new Gauss1dFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Gauss1dFunc::Eval(const double* const xval,
                         const double* const par) const
{
    double xp         = xval[0];
    double mu_xp      = par[0];
    double sigma_xp   = par[1];
    double norm       = par[2];
    double ans = norm * MirMath::ProbGaus(xp, mu_xp, sigma_xp);
    return ans;
}

//
// Gauss1dPlusConstFunc 
//

void Gauss1dPlusConstFunc::Copy(const Gauss1dPlusConstFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

Gauss1dPlusConstFunc* const Gauss1dPlusConstFunc::Clone() const
{
    Gauss1dPlusConstFunc* obj_new = new Gauss1dPlusConstFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Gauss1dPlusConstFunc::Eval(const double* const xval,
                                  const double* const par) const
{
    double xp         = xval[0];
    double mu_xp      = par[0];
    double sigma_xp   = par[1];
    double norm       = par[2];
    double cons       = par[3];
    double ans = norm * MirMath::ProbGaus(xp, mu_xp, sigma_xp) + cons;
    return ans;
}


//
// Gauss1dAsymFunc
//

//
// 1-dim Gaussian distribution with asymmetrical error
//

void Gauss1dAsymFunc::Copy(const Gauss1dAsymFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

Gauss1dAsymFunc* const Gauss1dAsymFunc::Clone() const
{
    Gauss1dAsymFunc* obj_new = new Gauss1dAsymFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Gauss1dAsymFunc::Eval(const double* const xval,
                             const double* const par) const
{
    double xp        = xval[0];
    double mu_xp       = par[0];
    double sigma_minus = par[1];
    double sigma_plus  = par[2];
    double norm        = par[3];

    double sigma_mean = (sigma_minus + sigma_plus) / 2.0;
    double ans = 0.0;
    if (xval[0] < mu_xp){
        ans = norm * sigma_minus / sigma_mean
            * MirMath::ProbGaus(xp, mu_xp, sigma_minus);
    } else {
        ans = norm * sigma_plus  / sigma_mean
            * MirMath::ProbGaus(xp, mu_xp, sigma_plus);
    }

    return ans;
}


//
// Gauss2dFuncAtZero
//

void Gauss2dFuncAtZero::Copy(const Gauss2dFuncAtZero* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

Gauss2dFuncAtZero* const Gauss2dFuncAtZero::Clone() const
{
    Gauss2dFuncAtZero* obj_new = new Gauss2dFuncAtZero;
    obj_new->Copy(this);
    return obj_new;
}

double Gauss2dFuncAtZero::Eval(const double* const xval,
                               const double* const par) const
{
    double xp         = xval[0];
    double yp         = xval[1];
    double sigma_xp   = par[0];
    double sigma_yp   = par[1];
    double norm       = par[2];
    double mu_xp      = 0.0;
    double mu_yp      = 0.0;
    double ans = norm * MirMath::ProbGaus(xp, mu_xp, sigma_xp)
        * MirMath::ProbGaus(yp, mu_yp, sigma_yp);
    return ans;
}

//
// Gauss2dFunc
//

void Gauss2dFunc::Init()
{
    Null();

    gauss2d_func_at_zero_ = new Gauss2dFuncAtZero;
    rotation_func_ = new RotationFunc;
    parallel_shift_func_ = new ParallelShiftFunc;
    rotation_func_->InitSet(gauss2d_func_at_zero_);
    parallel_shift_func_->InitSet(rotation_func_);
}

void Gauss2dFunc::Copy(const Gauss2dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    gauss2d_func_at_zero_ = org->GetGauss2dFuncAtZero()->Clone();
    rotation_func_ = org->GetRotationFunc()->Clone();
    parallel_shift_func_ = org->GetParallelShiftFunc()->Clone();
}

Gauss2dFunc* const Gauss2dFunc::Clone() const
{
    Gauss2dFunc* obj_new = new Gauss2dFunc;
    obj_new->Copy(this);
    return obj_new;
}


double Gauss2dFunc::Eval(const double* const xval,
                         const double* const par) const
{
    // xval[0]:  xp
    // xval[1]:  yp
    // par[0] :  sigma_xp
    // par[1] :  sigma_yp
    // par[2] :  norm
    // par[3] :  rot_angle (radian)
    // par[4] :  mu_xp (parallel shift)
    // par[5] :  mu_yp (parallel shift)
    // par[6] :  shift_z

    double ans = parallel_shift_func_->Eval(xval, par);

    return ans;
}

void Gauss2dFunc::Null()
{
    if(NULL != gauss2d_func_at_zero_)
        {delete gauss2d_func_at_zero_; gauss2d_func_at_zero_ = NULL;}
    if(NULL != rotation_func_)
        {delete rotation_func_; rotation_func_ = NULL;}
    if(NULL != parallel_shift_func_)
        {delete parallel_shift_func_; parallel_shift_func_ = NULL;}
}


//
// -- simple function
//

//
// Const1dFunc
//

void Const1dFunc::Copy(const Const1dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}


Const1dFunc* const Const1dFunc::Clone() const
{
    Const1dFunc* obj_new = new Const1dFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Const1dFunc::Eval(const double* const xval,
                         const double* const par) const
{
    double ans = par[0];
    return ans;
}

//
// Const2dFunc
//

void Const2dFunc::Copy(const Const2dFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}


Const2dFunc* const Const2dFunc::Clone() const
{
    Const2dFunc* obj_new = new Const2dFunc;
    obj_new->Copy(this);
    return obj_new;
}

double Const2dFunc::Eval(const double* const xval,
                         const double* const par) const
{
    double ans = par[0];
    return ans;
}


//
// LinFunc
//

void LinFunc::Copy(const LinFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}

    CopyTitle(org);
}


LinFunc* const LinFunc::Clone() const
{
    LinFunc* obj_new = new LinFunc;
    obj_new->Copy(this);
    return obj_new;
}

double LinFunc::Eval(const double* const xval,
                     const double* const par) const
{
    double ans = xval[0] * par[1] + par[0];
    return ans;
}

//
// LinMidFunc
//

void LinMidFunc::Copy(const LinMidFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}


LinMidFunc* const LinMidFunc::Clone() const
{
    LinMidFunc* obj_new = new LinMidFunc;
    obj_new->Copy(this);
    return obj_new;
}

double LinMidFunc::Eval(const double* const xval,
                        const double* const par) const
{
    double ans = (xval[0] - par[2]) * par[1] + par[0];
    return ans;
}

//
// LinMidSlopeFunc
//

void LinMidSlopeFunc::Copy(const LinMidSlopeFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}



LinMidSlopeFunc* const LinMidSlopeFunc::Clone() const
{
    LinMidSlopeFunc* obj_new = new LinMidSlopeFunc;
    obj_new->Copy(this);
    return obj_new;
}

// lognote (2010/06/10), p145 & p148, p149
// ~/work/maxi/ana/crab/log/11011500.txt
double LinMidSlopeFunc::Eval(const double* const xval,
                             const double* const par) const
{
    double ans = par[0] * (par[1] * (xval[0] - par[2]) + 1.0);
    return ans;
}


//
// LinMidSlopeErrFunc
//

void LinMidSlopeErrFunc::Copy(const LinMidSlopeErrFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}


LinMidSlopeErrFunc* const LinMidSlopeErrFunc::Clone() const
{
    LinMidSlopeErrFunc* obj_new = new LinMidSlopeErrFunc;
    obj_new->Copy(this);
    return obj_new;
}

// lognote p28, 2011.03.16
double LinMidSlopeErrFunc::Eval(const double* const xval,
                                const double* const par) const
{
    double time = xval[0];
    double F_m = par[0];
    double S   = par[1];
    double t_m = par[2];

    double F_m_err = par[3];
    double S_err   = par[4];
    double t_m_err = par[5];

    double ans = sqrt(
        pow( (S * (time - t_m) + 1) * F_m_err, 2) +
        pow( F_m * (time - t_m) * S_err, 2) +
        pow( F_m * S * t_m_err, 2)
        );
    return ans;
}


//
// ParabolaFunc
//

void ParabolaFunc::Copy(const ParabolaFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}


ParabolaFunc* const ParabolaFunc::Clone() const
{
    ParabolaFunc* obj_new = new ParabolaFunc;
    obj_new->Copy(this);
    return obj_new;
}

double ParabolaFunc::Eval(const double* const xval,
                          const double* const par) const
{
    double ans = par[0] * pow(xval[0] - par[1], 2)  + par[2];
    return ans;
}

//
// power-law
//

void PowerlawFunc::Copy(const PowerlawFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);
}

PowerlawFunc* const PowerlawFunc::Clone() const
{
    PowerlawFunc* obj_new = new PowerlawFunc;
    obj_new->Copy(this);
    return obj_new;
}

double PowerlawFunc::Eval(const double* const xval,
                          const double* const par) const
{
    double ans = par[2] * pow(xval[0] - par[1], par[0]);
    return ans;
}

//
// PowerlawPegFunc 
//

void PowerlawPegFunc::SetRange(double xval_lo, double xval_up)
{
    xval_lo_ = xval_lo;
    xval_up_ = xval_up;
}

void PowerlawPegFunc::Copy(const PowerlawPegFunc* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyTitle(org);

    Null();
    xval_lo_ = org->GetXvalLo();
    xval_up_ = org->GetXvalUp();
}

PowerlawPegFunc* const PowerlawPegFunc::Clone() const
{
    PowerlawPegFunc* obj_new = new PowerlawPegFunc;
    obj_new->Copy(this);
    return obj_new;
}

double PowerlawPegFunc::Eval(const double* const xval,
                             const double* const par) const
{
    double pl_index = par[0];
    double xval0    = par[1];
    double norm_integral = par[2];
    double y0 = GetY0(pl_index, xval0, norm_integral);
    double ans = y0 * pow(xval[0] - xval0, pl_index);
    return ans;
}

// private

void PowerlawPegFunc::Null()
{
    xval_lo_ = 0.0;
    xval_up_ = 0.0;
}


double PowerlawPegFunc::GetY0(double pl_index,
                              double xval0,
                              double norm_integral) const
{
    double y0 = 0.0;
    if(-1 != pl_index){
        y0 = norm_integral * (pl_index + 1.0) /
            ( pow(xval_up_ - xval0, pl_index + 1)
              - pow(xval_lo_ - xval0, pl_index + 1) );
    } else {
        y0 = norm_integral / log ( fabs( xval_up_ - xval0) /
                                   fabs( xval_lo_ - xval0) );
    }
    return y0;
}

