#include "mi_time.h"
#include "mi_base.h"
#include "mib_blas.h"

int main(int argc, char* argv[])
{
//    int nelem = 100000000;
//    double* x_arr = new double [nelem];
//    double* y_arr = new double [nelem];
//
//    for (int idx = 0; idx < nelem; idx++){
//        x_arr[idx] = idx;
//        y_arr[idx] = 10;
//    }
//    double* out_arr = new double[nelem];
//
//    // blas
//    double time_st = MiTime::GetTimeSec();
//    MibBlas::ElmWiseMul(nelem, x_arr, y_arr, out_arr);
//    double time_ed = MiTime::GetTimeSec();
//    printf("time_diff = %e\n", time_ed - time_st);

//    // not blas
//    double time_st = MiTime::GetTimeSec();
//    for (int idx = 0; idx < nelem; idx++){
//        out_arr[idx] = x_arr[idx] * y_arr[idx];
//    }
//    MibBlas::ElmWiseMul(nelem, x_arr, y_arr, out_arr);
//    double time_ed = MiTime::GetTimeSec();
//    printf("time_diff = %e\n", time_ed - time_st);

    
    
    //for(int idx = 0; idx < 10000; idx++){
        //printf("out_arr[] = %e\n", out_arr[idx]);
    //}
    
    double time_st = MiTime::GetTimeSec();
    int M = 10000;
    int N = 10000;
    double alpha = 10;
    double* A = new double[100000000];
    for(int idx = 0; idx < 100000000; idx ++){
        A[idx] = 1.0;
    }
    long lda = 100;
    double* x = new double[10000];
    for(int idx = 0; idx < 10000; idx ++){
        x[idx] = 1.0;
    }
    double beta = 10;
    double* y = new double[10000];
    for(int idx = 0; idx < 10000; idx ++){
        y[idx] = 1.0;
    }
    char ca[1];
    strcpy(ca, "N");
    dgemv_(ca, M, N,
           1.0, A, M,
           x, 1,
           beta, y, 1);
    
    double time_ed = MiTime::GetTimeSec();
    printf("time_diff = %e\n", time_ed - time_st);

    return 0;
}
