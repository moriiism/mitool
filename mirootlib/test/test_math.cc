#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_math.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    int IsZero(double val);
    {
        printf("--- test IsZero(double val)\n");
        int val = MirMath::IsZero(10.0);
        printf("val = %d\n", val);
        val = MirMath::IsZero(0.0);
        printf("val = %d\n", val);
        printf("=== \n");
    }

//    int IsOne(double val);
    {
        printf("--- test IsOne(double val)\n");
        int val1 = MirMath::IsOne(10.0);
        printf("val1 = %d\n", val1);
        int val2 = MirMath::IsOne(1.0);
        printf("val2 = %d\n", val2);
        printf("=== \n");
    }
    
//    int IsOneOrZero(double val);
    {
        printf("--- test IsOneOrZero(double val)\n");
        int val1 = MirMath::IsOneOrZero(10.0);
        printf("val1 = %d\n", val1);
        int val2 = MirMath::IsOneOrZero(1.0);
        printf("val2 = %d\n", val2);
        int val3 = MirMath::IsOneOrZero(0.0);
        printf("val3 = %d\n", val3);        
        printf("=== \n");
    }

//    int IsPlus(double val);
    {
        printf("--- test IsPlus(double val)\n");
        int val1 = MirMath::IsPlus(10.0);
        printf("val1 = %d\n", val1);
        int val2 = MirMath::IsPlus(-10.0);
        printf("val2 = %d\n", val2);
        

        printf("=== \n");
    }
    
//    int IsMinus(double val);
    {
        printf("--- test IsMinus(double val)\n");
        int val1 = MirMath::IsMinus(10.0);
        printf("val1 = %d\n", val1);
        int val2 = MirMath::IsMinus(-10.0);
        printf("val2 = %d\n", val2);

        printf("=== \n");
    }
    
//    int Sign(double val);
    {
        printf("--- test Sign(double val)\n");
        int val1 = MirMath::Sign(10.0);
        printf("val1 = %d\n", val1);
        int val2 = MirMath::Sign(-10.0);
        printf("val2 = %d\n", val2);
        int val3 = MirMath::Sign(0.0);
        printf("val3 = %d\n", val3);
        
        printf("=== \n");
    }
    
//    double FilterPlus(double val);
    {
        printf("--- test FilterPlus(double val)\n");
        double val1 = MirMath::FilterPlus(10.0);
        printf("val1 = %e\n", val1);
        double val2 = MirMath::FilterPlus(-10.0);
        printf("val2 = %e\n", val2);
        double val3 = MirMath::FilterPlus(0.0);
        printf("val3 = %e\n", val3);
        
        printf("=== \n");
    }

   
//    double FilterMinus(double val);
    {
        printf("--- test FilterMinus(double val)\n");
        double val1 = MirMath::FilterMinus(10.0);
        printf("val1 = %e\n", val1);
        double val2 = MirMath::FilterMinus(-10.0);
        printf("val2 = %e\n", val2);
        double val3 = MirMath::FilterMinus(0.0);
        printf("val3 = %e\n", val3);
        
        printf("=== \n");
    }
    
//    int Not(double val);
    {
        printf("--- test Not(double val)\n");
        //double val1 = MirMath::Not(10.0);
        //printf("val1 = %e\n", val1);
        //double val2 = MirMath::Not(-10.0);
        //printf("val2 = %e\n", val2);
        double val3 = MirMath::Not(0.0);
        printf("val3 = %e\n", val3);
        double val4 = MirMath::Not(1.0);
        printf("val4 = %e\n", val4);        
        
        printf("=== \n");
    }

//    int Not(int val);
    {
        printf("--- test Not(int val)\n");
        //int val1 = MirMath::Not(10);
        //printf("val1 = %d\n", val1);
        //int val2 = MirMath::Not(-10);
        //printf("val2 = %d\n", val2);
        int val3 = MirMath::Not(0);
        printf("val3 = %d\n", val3);
        int val4 = MirMath::Not(1);
        printf("val4 = %d\n", val4);        
        
        printf("=== \n");
    }
    
//    void GetScaled(double val, double val_err, double scale, double offset,
//                   double* const ans_ptr, double* const ans_err_ptr);
    {
        printf("--- test GetScaled\n");

        double val = 10.0;
        double val_err = 0.2;
        double scale = 2.0;
        double offset = 3.0;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetScaled(val, val_err, scale, offset,
                           &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n",
               ans, ans_err);
        
        printf("=== \n");
    }
   
//    int IsSame(double aval, double bval);
    {
        printf("--- test IsSame(double aval, double bval)\n");
        double aval = 2.0;
        double bval = 4.0;
        int ret = MirMath::IsSame(aval, bval);
        printf("ret = %d\n", ret);
        printf("=== \n");
    }

    {
        printf("--- test IsSame(double aval, double bval)\n");
        double aval = 2.0;
        double bval = 2.0;
        int ret = MirMath::IsSame(aval, bval);
        printf("ret = %d\n", ret);
        printf("=== \n");
    }

//    double GetMin(double aval, double bval);
    {
        printf("--- test GetMin(double aval, double bval)\n");
        double aval = 2.0;
        double bval = 2.0;
        double ans = MirMath::GetMin(aval, bval);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }
    {
        printf("--- test GetMin(double aval, double bval)\n");
        double aval = 5.0;
        double bval = 2.0;
        double ans = MirMath::GetMin(aval, bval);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }
    
//    double GetMax(double aval, double bval);
    {
        printf("--- test GetMax(double aval, double bval)\n");
        double aval = 5.0;
        double bval = 2.0;
        double ans = MirMath::GetMax(aval, bval);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }
    
//    int GetLocMin(double aval, double bval); // 0, 1
    {
        printf("--- test GetLocMin(double aval, double bval)\n");
        double aval = 5.0;
        double bval = 2.0;
        int ans = MirMath::GetLocMin(aval, bval);
        printf("ans = %d\n", ans);
        printf("=== \n");
    }
    
//    int GetLocMax(double aval, double bval); // 0, 1
    {
        printf("--- test GetLocMax(double aval, double bval)\n");
        double aval = 5.0;
        double bval = 2.0;
        int ans = MirMath::GetLocMax(aval, bval);
        printf("ans = %d\n", ans);
        printf("=== \n");
    }
    
//    double GetAMean(double aval, double bval);
    {
        printf("--- test GetAMean(double aval, double bval)\n");
        double aval = 5.0;
        double bval = 2.0;
        int ans = MirMath::GetAMean(aval, bval);
        printf("ans = %d\n", ans);
        printf("=== \n");
    }
    
//    void GetAdd(double val1, double val1_err, double val2, double val2_err,
//                double* const ans_ptr, double* const ans_err_ptr);
    {
        printf("--- test GetAdd\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 1.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetAdd(val1, val1_err, val2, val2_err,
                        &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }
    
//    void GetSub(double val1, double val1_err, double val2, double val2_err,
//                double* const ans_ptr, double* const ans_err_ptr);
    {
        printf("--- test GetSub\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 1.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetSub(val1, val1_err, val2, val2_err,
                        &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }

//    void GetMul(double val1, double val1_err, double val2, double val2_err,
//                double* const ans_ptr, double* const ans_err_ptr);
    {
        printf("--- test GetMul\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 1.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetMul(val1, val1_err, val2, val2_err,
                        &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }
    
//    int GetDiv(double val_num, double val_num_err, double val_den, double val_den_err,
//               double* const ans_ptr, double* const ans_err_ptr);
    {
        printf("--- test GetDiv\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 6.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetDiv(val1, val1_err, val2, val2_err,
                        &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }

    {
        printf("--- test GetDiv\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 0.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        int ret = MirMath::GetDiv(val1, val1_err, val2, val2_err,
                                  &ans, &ans_err);
        printf("ret = %d\n", ret);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }
    
//    int GetAMean(double val1, double val1_err, double val2, double val2_err,
//                 double* const amean_ptr, double* const amean_err_ptr);
    {
        printf("--- test GetAMean\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 7.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetAMean(val1, val1_err, val2, val2_err,
                          &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }

//    int GetWMean(double val1, double val1_err, double val2, double val2_err,
//                 double* const wmean_ptr, double* const wmean_err_ptr);
    {
        printf("--- test GetWMean\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 7.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        int ret = MirMath::GetWMean(val1, val1_err, val2, val2_err,
                                    &ans, &ans_err);
        printf("ret = %d\n", ret);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }
    
//    int GetSubAddRatio(double val1, double val1_err, double val2, double val2_err,
//                       double* const ans_ptr, double* const ans_err_ptr);

    {
        printf("--- test GetSubAddRatio\n");
        double val1     = 5.0;
        double val1_err = 0.3;
        double val2     = 7.0;
        double val2_err = 0.2;
        double ans = 0.0;
        double ans_err = 0.0;
        int ret = MirMath::GetSubAddRatio(val1, val1_err, val2, val2_err,
                                          &ans, &ans_err);
        printf("ret = %d\n", ret);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        printf("=== \n");
    }

//    double GetMin(long narr, const double* const val_arr);
    {
        printf("--- test GetMin\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double val = MirMath::GetMin(narr, val_arr);
        printf("val = %e\n", val);
        
        printf("=== \n");
    }

//    {
//        printf("--- test GetMin\n");
//        double val_arr[5];
//        val_arr[0] = 10.0;
//        val_arr[1] = 11.0;
//        val_arr[2] = 12.0;
//        val_arr[3] = 13.0;
//        val_arr[4] = 14.0;
//        double val = MirMath::GetMin(0, val_arr);
//        printf("val = %e\n", val);
//        
//        printf("=== \n");
//    }

//    {
//        printf("--- test GetMin\n");
//        double* val_arr = NULL;
//        double val = MirMath::GetMin(5, val_arr);
//        printf("val = %e\n", val);
//        
//        printf("=== \n");
//    }

    
//    double GetMax(long narr, const double* const val_arr);
    {
        printf("--- test GetMax\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double val = MirMath::GetMax(narr, val_arr);
        printf("val = %e\n", val);
        
        printf("=== \n");
    }

   
//    long GetLocMin(long narr, const double* const val_arr);
    {
        printf("--- test GetLocMin\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        long index = MirMath::GetLocMin(narr, val_arr);
        printf("index = %ld\n", index);
        printf("=== \n");
    }
   
//    long GetLocMax(long narr, const double* const val_arr);
    {
        printf("--- test GetLocMax\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        long index = MirMath::GetLocMax(narr, val_arr);
        printf("index = %ld\n", index);
        printf("=== \n");
    }
    
//    double GetAdd(long narr, const double* const val_arr);
    {
        printf("--- test GetAdd\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetAdd(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }

//    double GetAMean(long narr, const double* const val_arr);
    {
        printf("--- test GetAMean\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetAMean(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }

    
//    double GetVariance(long narr, const double* const val_arr);
//    double GetStddev(long narr, const double* const val_arr);
//    double GetUnbiasedVariance(long narr, const double* const val_arr);
//    double GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr);
//    double GetRMS(long narr, const double* const val_arr);
//    double GetMedian(long narr, const double* const val_arr);
//
//    double GetMin(vector<double> vec);
//    double GetMax(vector<double> vec);
//    long GetLocMin(vector<double> vec);
//    long GetLocMax(vector<double> vec);
//    double GetAdd(vector<double> vec);
//    double GetAMean(vector<double> vec);
//    double GetVariance(vector<double> vec);
//    double GetStddev(vector<double> vec);
//    double GetUnbiasedVariance(vector<double> vec);
//    double GetSqrtOfUnbiasedVariance(vector<double> vec);
//    double GetRMS(vector<double> vec);
//    double GetMedian(vector<double> vec);
//    double GetMedian(vector<double> vec);
//    
//    void GetAdd(long narr, const double* const val_arr, const double* const val_err_arr,
//                double* const val_add_ptr, double* const val_add_err_ptr);
//    void GetAMean(long narr, const double* const val_arr, const double* const val_err_arr,
//                  double* const amean_ptr, double* const amean_err_ptr);
//    int GetWMean(long narr, const double* const val_arr, const double* const val_err_arr,
//                 double* const wmean_ptr, double* const wmean_err_ptr,
//                 vector<long>* const index_bad_vec_ptr);
//
//    void GetAddWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
//                        const int* const mask_arr,
//                        double* const val_add_ptr, double* const val_add_err_ptr);
//    int GetWMeanWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
//                         const int* const mask_arr,
//                         double* const wmean_ptr, double* const wmean_err_ptr,
//                         vector<long>* const index_bad_vec_ptr);
//
//    long GetChi2byConst(long narr,
//                        const double* const val_arr,
//                        const double* const val_err_arr,
//                        double* const chi2_ptr,
//                        long* const dof_ptr,
//                        double* const chi2_red_ptr,
//                        double* const prob_ptr);
//    double IntPolLin(double xval,
//                     double xval_lo, double xval_up,
//                     double yval_lo, double yval_up);
//    double IntPolLin(double xval, double yval,
//                     double xval0, double xval1,
//                     double yval0, double yval1,
//                     double oval_x0y0, double oval_x1y0,
//                     double oval_x1y1, double oval_x0y1);
//
//    double ProbGaus(double xval, double mu, double sigma);
//    double ProbGausAsym(double xval, double mu,
//                        double sigma_plus, double sigma_minus);
//    double Sigma2CL(double sigma);
//    double CL2Sigma(double cl);
//    double GetUpMinfcn(double value, string mode, int as_npar);
//    int GetPermutation(int n, int r);
//    int GetCombination(int n, int r);
//    long GetNbin(double val_lo, double val_up, double delta_val, string mode);
//    long GetNbinEven(double val_lo, double val_up, double delta_val);
//    void GetRangeQdp(double min, double max,
//                     double* const low_ptr, double* const up_ptr);
//    int IsSorted(long narr, const double* const val_arr);
//    double* const GenArray(vector<double> vec);
//    double GetInProd(double vec0_xval, double vec0_yval,
//                     double vec1_xval, double vec1_yval);
    



    
    return status_prog;
}
