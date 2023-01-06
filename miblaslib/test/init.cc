#include "mi_time.h"
#include "mi_base.h"
#include "mib_blas.h"

int main(int argc, char* argv[])
{
    int nelm = 100000000;
    double val0 = 0.0;
    double* val1_arr = new double[nelm];

    double time_st = MiTime::GetTimeSec();
    dcopy_(nelm, &val0, 0, val1_arr, 1);
    double time_ed = MiTime::GetTimeSec();
    printf("time_diff = %e\n", time_ed - time_st);
    
    double sum = 0.0;
    for(int ielm = 0; ielm < nelm; ielm++){
        sum += val1_arr[ielm];
    }
    printf("sum = %e\n", sum);
    delete [] val1_arr;

    double* val2_arr = new double[nelm];
    time_st = MiTime::GetTimeSec();
    for(int ielm = 0; ielm < nelm; ielm++){
        val2_arr[ielm] = val0;
    }
    time_ed = MiTime::GetTimeSec();
    printf("time_diff = %e\n", time_ed - time_st);

    sum = 0.0;
    for(int ielm = 0; ielm < nelm; ielm++){
        sum += val2_arr[ielm];
    }
    printf("sum = %e\n", sum);
    delete [] val2_arr;

    return 0;
}
