#ifndef MORIIISM_MITOOL_MIROOTLIB_MATH_H_
#define MORIIISM_MITOOL_MIROOTLIB_MATH_H_

#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;

#include "mi_base.h"

// "Average" and "mean" are ambiguous, then we do not use these names.
// Instead, we use the followings:
//   Arithmetic mean --> AMean
//   Weighted mean   --> WMean

namespace MirMath
{
    // For a value
    int IsZero(double val);
    // if val == 0, return 1
    // if val != 0, return 0

    int IsOne(double val);
    // if val == 1, return 1
    // if val != 1, return 0

    int IsOneOrZero(double val);

    int IsPlus(double val);
    // if val > 0, return 1
    // if val <=0, return 0

    int IsMinus(double val);
    // if val < 0, return 1
    // if val >=0, return 0
    
    int Sign(double val);
    // if val > 0, return 1
    // if val < 0, return -1
    // if val == 0, return 0.

    double FilterPlus(double val);
    // if val > 0, return val
    // if val <= 0, return 0

    double FilterMinus(double val);
    // if val < 0, return val
    // if val >= 0, return 0

    int Not(double val);
    int Not(int val);
    // 0 ---> 1
    // 1 ---> 0
    
    // For a value with a gaussian error
    void GetScaled(double val, double val_err, double scale, double offset,
                   double* const ans_ptr, double* const ans_err_ptr);
    
    // For two values without errors
    int IsSame(double aval, double bval);
        
    double GetMin(double aval, double bval);
    double GetMax(double aval, double bval);
    int GetLocMin(double aval, double bval); // 0, 1
    int GetLocMax(double aval, double bval); // 0, 1
    double GetAMean(double aval, double bval);

    // For two values with gaussian errors
    void GetAdd(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    void GetSub(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    void GetMul(double val1, double val1_err, double val2, double val2_err,
                double* const ans_ptr, double* const ans_err_ptr);
    int GetDiv(double val_num, double val_num_err, double val_den, double val_den_err,
               double* const ans_ptr, double* const ans_err_ptr);
    int GetAMean(double val1, double val1_err, double val2, double val2_err,
                 double* const amean_ptr, double* const amean_err_ptr);
    int GetWMean(double val1, double val1_err, double val2, double val2_err,
                 double* const wmean_ptr, double* const wmean_err_ptr);

    // sub_add_ratio = (val1 - val2) / (val1 + val2)
    int GetSubAddRatio(double val1, double val1_err, double val2, double val2_err,
                       double* const ans_ptr, double* const ans_err_ptr);

    // For N values without errors
    //  for array
    double GetMin(long narr, const double* const val_arr);
    double GetMax(long narr, const double* const val_arr);
    long GetLocMin(long narr, const double* const val_arr);
    long GetLocMax(long narr, const double* const val_arr);
    double GetAdd(long narr, const double* const val_arr);    

    double GetAMean(long narr, const double* const val_arr);
    // Arithmetic Mean = Sum x_i / N

    double GetVariance(long narr, const double* const val_arr);
    // Variance           = [Sum (x_i - mu)^2] / N       = [ Sum x_i^2 - (Sum x_i)^2 / N ] / N
    
    double GetStddev(long narr, const double* const val_arr);
    // Standard Deviation = sqrt(Variance)

    double GetUnbiasedVariance(long narr, const double* const val_arr);
    // Unbiased Variance  = [Sum (x_i - mu)^2] / (N - 1) = [ Sum x_i^2 - (Sum x_i)^2 / N ] / (N - 1)    
    
    double GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr);
    // Square of Unbiased Variance  = sqrt (Unbiased Variance)
    
    double GetRMS(long narr, const double* const val_arr);
    // RMS = Root Mean Square = sqrt[ (Sum x_i^2) / N ]

    //  for vector
    double GetMin(vector<double> vec);
    double GetMax(vector<double> vec);
    long GetLocMin(vector<double> vec);
    long GetLocMax(vector<double> vec);
    double GetAdd(vector<double> vec);
    double GetAMean(vector<double> vec);
    double GetVariance(vector<double> vec);
    double GetStddev(vector<double> vec);
    double GetUnbiasedVariance(vector<double> vec);
    double GetSqrtOfUnbiasedVariance(vector<double> vec);
    double GetRMS(vector<double> vec);
    double GetMedian(vector<double> vec);
    
    
    // For N values with gaussian errors
    //   for array
    void GetAdd(long narr, const double* const val_arr, const double* const val_err_arr,
                double* const val_add_ptr, double* const val_add_err_ptr);
    void GetAMean(long narr, const double* const val_arr, const double* const val_err_arr,
                  double* const amean_ptr, double* const amean_err_ptr);
    int GetWMean(long narr, const double* const val_arr, const double* const val_err_arr,
                 double* const wmean_ptr, double* const wmean_err_ptr,
                 vector<long>* const index_bad_vec_ptr);

    //   for array with mask    
    // mask: use = 1, not use = 0
    void GetAddWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                        const int* const mask_arr,
                        double* const val_add_ptr, double* const val_add_err_ptr);
    int GetWMeanWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                         const int* const mask_arr,
                         double* const wmean_ptr, double* const wmean_err_ptr,
                         vector<long>* const index_bad_vec_ptr);


    // ----------------------------------------
    
    long GetChi2byConst(long narr,
                        const double* const val_arr,
                        const double* const val_err_arr,
                        double* const chi2_ptr,
                        long* const dof_ptr,
                        double* const chi2_red_ptr,
                        double* const prob_ptr);

    // interpolation, for 1dim
    double IntPolLin(double xval,
                     double xval_lo, double xval_up,
                     double yval_lo, double yval_up);

    // interpolation, for 2dim
    double IntPolLin(double xval, double yval,
                     double xval0, double xval1,
                     double yval0, double yval1,
                     double oval_x0y0, double oval_x1y0,
                     double oval_x1y1, double oval_x0y1);

    // statistics
    double ProbGaus(double xval, double mu, double sigma);
    double ProbGausAsym(double xval, double mu,
                        double sigma_plus, double sigma_minus);
    double Sigma2CL(double sigma);
    double CL2Sigma(double cl);
    double GetUpMinfcn(double value, string mode, int as_npar);

    int GetPermutation(int n, int r);
    // Permutation(n, r) = _nP_r = n! / (n - r)!
    
    int GetCombination(int n, int r);
    // Combination(n, r) = _nC_r = _nP_r / r! =  n! / [r! (n - r)!]

    // for binning
    long GetNbin(double val_lo, double val_up, double delta_val, string mode);
    long GetNbinEven(double val_lo, double val_up, double delta_val);

    void GetRangeQdp(double min, double max,
                     double* const low_ptr, double* const up_ptr);

    int IsSorted(long narr, const double* const val_arr);

    // vector --> arrray
    double* const GenArray(vector<double> vec);


    // inner product
    double GetInProd(double vec0_xval, double vec0_yval,
                     double vec1_xval, double vec1_yval);


    
} //  namespace MirMath

#endif // MORIIISM_MITOOL_MIROOTLIB_MATH_H_
