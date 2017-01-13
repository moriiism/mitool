#include "mir_func.h"

//
// public
//

double MirFunc::Eval1d(double xval,
                        const double* const par) const
{
    double xval_arr[1];
    xval_arr[0] = xval;
    double ans = Eval(xval_arr, par);
    return ans;
}

double MirFunc::Eval2d(double xval, double yval,
                        const double* const par) const
{
    double xval_arr[2];
    xval_arr[0] = xval;
    xval_arr[1] = yval;
    double ans = Eval(xval_arr, par);
    return ans;
}

//
// private
//

void MirFunc::NullMirFunc()
{
    npar_ = 0;
    ndim_ = 0;
}

