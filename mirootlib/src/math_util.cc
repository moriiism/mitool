#include "mir_math_util.h"

// get mean and stddev by clipping
void MirMathUtil::GetMeanStddevClip(long narr, const double* const val_arr,
                                    int nclip, double significance,
                                    double* const mean_ptr,
                                    double* const stddev_ptr)
{
    double mean   = 0.0;
    double stddev = 0.0;
    int* use_arr = new int[narr];
    for(long iarr = 0; iarr < narr; iarr++){
        use_arr[iarr] = 1;
    }
    
    for(int iclip = 0; iclip < nclip; iclip ++){
        // get mean, stddev
        vector<double> val_vec;
        for(long iarr = 0; iarr < narr; iarr++){
            if(use_arr[iarr] > 0){
                val_vec.push_back(val_arr[iarr]);
            }
        }
        mean   = MirMath::GetAMean(val_vec);
        stddev = MirMath::GetSqrtOfUnbiasedVariance(val_vec);
        printf("iclip, mean, stddev, nsize = %d, %e, %e, %d\n",
               iclip, mean, stddev, (int) val_vec.size());
        long ninc_unuse = 0;
        for(long iarr = 0; iarr < narr; iarr++){
            if( use_arr[iarr] > 0 &&
                fabs(val_arr[iarr] - mean) > significance * stddev){
                use_arr[iarr] = 0;
                ninc_unuse ++;
            }
        }
        if(0 == ninc_unuse){
            printf("clipping end.\n");
            break;
        }
    }
    *mean_ptr = mean;
    *stddev_ptr = stddev;
}

void MirMathUtil::GetMarginLoUp(double min, double max,
                                double margin_ratio,
                                double* const lo_ptr,
                                double* const up_ptr)
{
    double width = max - min;
    double margin = width * margin_ratio;
    double lo = min - margin;
    double up = max + margin;
    *lo_ptr = lo;
    *up_ptr = up;
}

void MirMathUtil::Uniq(long narr, const double* const val_arr,
                       long* const nuniq_ptr, double** const uniq_arr_ptr,
                       double epsilon)
{
    double* val_sort_arr = new double[narr];
    long* index_arr = new long[narr];
    MiSort::Sort(narr, val_arr, index_arr, 0);
    for(long iarr = 0; iarr < narr; iarr ++){
        val_sort_arr[iarr] = val_arr[index_arr[iarr]];
    }
    vector<double> val_vec;
    double val_mark = val_sort_arr[0];
    val_vec.push_back( val_sort_arr[0] );
    for(long iarr = 0; iarr < narr; iarr ++){
        if( fabs(val_mark - val_sort_arr[iarr]) > epsilon ){
            val_mark = val_sort_arr[iarr];
            val_vec.push_back( val_sort_arr[iarr] );
        }
    }
    long nuniq = val_vec.size();
    double* uniq_arr = new double [nuniq];
    for(long iuniq = 0; iuniq < nuniq; iuniq ++){
        uniq_arr[iuniq] = val_vec[iuniq];
    }
    delete [] val_sort_arr;
    delete [] index_arr;
    *nuniq_ptr = nuniq;
    *uniq_arr_ptr = uniq_arr;
}


void MirMathUtil::GetQuantile(long narr, const double* const val_arr,
                              long nquantile,
                              double** const quantile_arr_ptr)
{
    double* quantile_arr = new double [nquantile];
    for(int iqtl = 0; iqtl < nquantile; iqtl ++){
        quantile_arr[iqtl] = 0.0;
    }
    long* index_arr = new long [narr];
    MiSort::Sort(narr, val_arr, index_arr, 0);
    for(int iqtl = 0; iqtl < nquantile; iqtl ++){
        long index = floor( iqtl * narr / (double) nquantile );
        quantile_arr[iqtl] = val_arr[index_arr[index]];
    }
    delete [] index_arr;
    *quantile_arr_ptr = quantile_arr; 
}
