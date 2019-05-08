#ifndef MORIIISM_MITOOL_MIROOTLIB_MATH_UTIL_H_
#define MORIIISM_MITOOL_MIROOTLIB_MATH_UTIL_H_

#include "mi_sort.h"
#include "mir_math.h"

namespace MirMathUtil
{
    // get mean and stddev by clipping
    void GetMeanStddevClip(long narr, const double* const val_arr,
                           int nclip, double significance,
                           double* const mean_ptr,
                           double* const stddev_ptr);

    void GetMarginLoUp(double min, double max,
                       double margin_ratio,
                       double* const lo_ptr,
                       double* const up_ptr);

    void Uniq(long narr, const double* const val_arr,
              long* const nuniq, double** const uniq_arr_ptr,
              double epsilon);

    void GetQuantile(long narr, const double* const val_arr,
                     long nquantile,
                     double** const quantile_arr_ptr);
    
} //  namespace MirMathUtil

#endif // MORIIISM_MITOOL_MIROOTLIB_MATH_UTIL_H_
