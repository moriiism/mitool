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
    {
        printf("--- test GetVariance\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetVariance(narr, val_arr);
        printf("ans = %e\n", ans);

        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0)/5. = 12.0
        // ( (10.0 - 12.0)**2 + (11.0 - 12.0)**2 + (12.0 - 12.0)**2
        // + (13.0 - 12.0)**2 + (14.0 - 12.0)**2 ) / 5. = 2.0
        printf("=== \n");
    }
   
//    double GetStddev(long narr, const double* const val_arr);
    {
        printf("--- test GetStddev\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetStddev(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }


//    double GetUnbiasedVariance(long narr, const double* const val_arr);
    {
        printf("--- test GetUnbiasedVariance\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetUnbiasedVariance(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }

//    double GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr);
    {
        printf("--- test GetSqrtOfUnbiasedVariance\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetSqrtOfUnbiasedVariance(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }
    
//    double GetRMS(long narr, const double* const val_arr);
    {
        printf("--- test GetRMS\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetRMS(narr, val_arr);
        printf("ans = %e\n", ans);
        // sqrt( ( 10.0**2 + 11.0**2 + 12.0**2 + 13.0**2 + 14.0**2 ) / 5.) = 12.08304597
        printf("=== \n");
    }
    
//    double GetMedian(long narr, const double* const val_arr);
    {
        printf("--- test GetMedian\n");
        long narr = 5;
        double val_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        double ans = MirMath::GetMedian(narr, val_arr);
        printf("ans = %e\n", ans);
        printf("=== \n");
    }

//    double GetMin(vector<double> vec);
    {
        printf("--- test GetMin\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetMin(val_vec);
        printf("val = %e\n", val);
        
        printf("=== \n");
    }
    
//    double GetMax(vector<double> vec);
    {
        printf("--- test GetMax\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetMax(val_vec);
        printf("val = %e\n", val);
        
        printf("=== \n");
    }
    
//    long GetLocMin(vector<double> vec);
    {
        printf("--- test GetLocMin\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        long index = MirMath::GetLocMin(val_vec);
        printf("index = %ld\n", index);
        
        printf("=== \n");
    }

    
//    long GetLocMax(vector<double> vec);
    {
        printf("--- test GetLocMax\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        long index = MirMath::GetLocMax(val_vec);
        printf("index = %ld\n", index);
        
        printf("=== \n");
    }

//    double GetAdd(vector<double> vec);
    {
        printf("--- test GetAdd\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetAdd(val_vec);
        printf("val = %e\n", val);
        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0) = 60.0
        printf("=== \n");
    }
    
//    double GetAMean(vector<double> vec);
    {
        printf("--- test GetAMean\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetAMean(val_vec);
        printf("val = %e\n", val);
        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0)/5. = 12.0
        printf("=== \n");
    }
   
//    double GetVariance(vector<double> vec);
    {
        printf("--- test GetVariance\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetVariance(val_vec);
        printf("val = %e\n", val);
        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0)/5. = 12.0
        // ( (10.0 - 12.0)**2 + (11.0 - 12.0)**2 + (12.0 - 12.0)**2
        // + (13.0 - 12.0)**2 + (14.0 - 12.0)**2 ) / 5. = 2.0
        printf("=== \n");
    }
    
//    double GetStddev(vector<double> vec);
    {
        printf("--- test GetStddev\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetStddev(val_vec);
        printf("val = %e\n", val);
        // sqrt(variance) = sqrt(2.0) = 1.4142135623731
        printf("=== \n");
    }
    
//    double GetUnbiasedVariance(vector<double> vec);
    {
        printf("--- test GetUnbiasedVariance\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetUnbiasedVariance(val_vec);
        printf("val = %e\n", val);
        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0)/5. = 12.0
        // ( (10.0 - 12.0)**2 + (11.0 - 12.0)**2 + (12.0 - 12.0)**2
        // + (13.0 - 12.0)**2 + (14.0 - 12.0)**2 ) / 4.  = 2.5
        printf("=== \n");
    }
    
//    double GetSqrtOfUnbiasedVariance(vector<double> vec);
    {
        printf("--- test GetSqrtOfUnbiasedVariance\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetSqrtOfUnbiasedVariance(val_vec);
        printf("val = %e\n", val);
        // sqrt(unbiased variance) = sqrt(2.5) = 1.58113883008419
        printf("=== \n");
    }
    
//    double GetRMS(vector<double> vec);
    {
        printf("--- test GetRMS\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetRMS(val_vec);
        printf("val = %e\n", val);
        // sqrt( ( 10.0**2 + 11.0**2 + 12.0**2 + 13.0**2 + 14.0**2 ) / 5.) = 12.08304597         
        printf("=== \n");
    }
    
//    double GetMedian(vector<double> vec);
    {
        printf("--- test GetMedian\n");
        long narr = 5;
        vector<double> val_vec(narr);
        val_vec[0] = 10.0;
        val_vec[1] = 11.0;
        val_vec[2] = 12.0;
        val_vec[3] = 13.0;
        val_vec[4] = 14.0;
        double val = MirMath::GetMedian(val_vec);
        printf("val = %e\n", val);
        printf("=== \n");
    }
    
//    void GetAdd(long narr, const double* const val_arr, const double* const val_err_arr,
//                double* const val_add_ptr, double* const val_add_err_ptr);
    {
        printf("--- test GetAdd\n");
        long narr = 5;
        double val_arr[5];
        double val_err_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        val_err_arr[0] = 1.0;
        val_err_arr[1] = 2.0;
        val_err_arr[2] = 3.0;
        val_err_arr[3] = 4.0;
        val_err_arr[4] = 5.0;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetAdd(narr, val_arr, val_err_arr, &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        // 10.0 + 11.0 + 12.0 + 13.0 + 14.0 = 60.0
        // sqrt(1.0**2 + 2.0**2 + 3.0**2 + 4.0**2 + 5.**2) = 7.41619848709566
        printf("=== \n");
    }
    
//    void GetAMean(long narr, const double* const val_arr, const double* const val_err_arr,
//                  double* const amean_ptr, double* const amean_err_ptr);
    {
        printf("--- test GetAMean\n");
        long narr = 5;
        double val_arr[5];
        double val_err_arr[5];
        val_arr[0] = 10.0;
        val_arr[1] = 11.0;
        val_arr[2] = 12.0;
        val_arr[3] = 13.0;
        val_arr[4] = 14.0;
        val_err_arr[0] = 1.0;
        val_err_arr[1] = 2.0;
        val_err_arr[2] = 3.0;
        val_err_arr[3] = 4.0;
        val_err_arr[4] = 5.0;
        double ans = 0.0;
        double ans_err = 0.0;
        MirMath::GetAMean(narr, val_arr, val_err_arr, &ans, &ans_err);
        printf("ans, ans_err = %e, %e\n", ans, ans_err);
        // (10.0 + 11.0 + 12.0 + 13.0 + 14.0)/5. = 12.0
        // ( sqrt(1.0**2 + 2.0**2 + 3.0**2 + 4.0**2 + 5.**2))/5. = 1.48323969741913
        printf("=== \n");
    }
   
////    int GetWMean(long narr, const double* const val_arr, const double* const val_err_arr,
////                 double* const wmean_ptr, double* const wmean_err_ptr,
////                 vector<long>* const index_bad_vec_ptr);
//    {
//        printf("--- test GetWMean\n");
//        long narr = 5;
//        double val_arr[5];
//        double val_err_arr[5];
//        val_arr[0] = 10.0;
//        val_arr[1] = 11.0;
//        val_arr[2] = 12.0;
//        val_arr[3] = 13.0;
//        val_arr[4] = 14.0;
//        val_err_arr[0] = 1.0;
//        val_err_arr[1] = 2.0;
//        val_err_arr[2] = 3.0;
//        val_err_arr[3] = 4.0;
//        val_err_arr[4] = 5.0;
//        double ans = 0.0;
//        double ans_err = 0.0;
//        vector<long> index_bad_vec;
//        MirMath::GetWMean(narr, val_arr, val_err_arr, &ans, &ans_err, &index_bad_vec);
//        printf("ans, ans_err = %e, %e\n", ans, ans_err);
//        printf("=== \n");
//    }

    
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
//    int IsSorted(long narr, const double* const val_arr);
//    double* const GenArray(vector<double> vec);
//    double GetInProd(double vec0_xval, double vec0_yval,
//                     double vec1_xval, double vec1_yval);
    



    
    return status_prog;
}