#include "mir_math.h"

// For a value

int MirMath::IsZero(double val)
{
    if(-DBL_EPSILON < val && val < DBL_EPSILON){
        return 1;
    } else {
        return 0;
    }
}

int MirMath::IsOne(double val)
{
    if( fabs(val - 1) < DBL_EPSILON){
        return 1;
    } else {
        return 0;
    }
}

int MirMath::IsOneOrZero(double val)
{
    int ans = IsOne(val) + IsZero(val);
    return ans;
}

int MirMath::IsPlus(double val)
{
    if (val > 0) {
        return 1;
    } else {
        return 0;
    }
}

int MirMath::IsMinus(double val)
{
    if (val < 0) {
        return 1;
    } else {
        return 0;
    }
}

int MirMath::Sign(double val)
{
    if (val > 0) {
        return 1;
    } else if (val < 0) {
        return -1;
    } else {
        return 0;
    }
}

double MirMath::FilterPlus(double val)
{
    if (val > 0) {
        return val;
    } else {
        return 0.0;
    }
}

double MirMath::FilterMinus(double val)
{
    if (val < 0) {
        return val;
    } else {
        return 0.0;
    }
}

// 0 --> 1
// 1 --> 0
// others --> abort
int MirMath::Not(double val)
{
    if(1 != IsOneOrZero(val)){
        char msg[kLineSize];
        sprintf(msg, "bad input val (=%e)", val);
        MPrintErr(msg);
        abort();
    }
    int val_int = IsOne(val);
    int ans = Not(val_int);
    return ans;
}

// 0 --> 1
// 1 --> 0
// others --> abort
int MirMath::Not(int val)
{
    int ans = 0;
    if(0 == val){
        ans = 1;
    } else if(1 == val){
        ans = 0;
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad input val (=%d)", val);
        MPrintErr(msg);
        abort();
    }
    return ans;
}


// For a value with a gaussian error

void MirMath::GetScaled(double val, double val_err, double scale, double offset,
                        double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = scale * val + offset;
    double ans_err = fabs(scale) * val_err;
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}


// For two values without errors

int MirMath::IsSame(double aval, double bval)
{
    int retval = 0;
    if( fabs(aval - bval) < DBL_EPSILON ) {
        // same
        retval = 1;
    } else {
        // not same
        retval = 0;
    }
    return retval;
}

double MirMath::GetMin(double aval, double bval)
{
    double val = 0.0;
    if(aval <= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

double MirMath::GetMax(double aval, double bval)
{
    double val = 0.0;
    if(aval >= bval){
        val = aval;
    } else {
        val = bval;
    }
    return val;
}

int MirMath::GetLocMin(double aval, double bval)
{
    if(aval <= bval){
        return 0;
    } else {
        return 1;
    }
}

int MirMath::GetLocMax(double aval, double bval)
{
    if(aval >= bval){
        return 0;
    } else {
        return 1;
    }
}


double MirMath::GetAMean(double aval, double bval)
{
    double ans = (aval + bval) / 2.;
    return ans;
}

// For two values with gaussian errors

void MirMath::GetAdd(double val1, double val1_err, double val2, double val2_err,
                     double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 + val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MirMath::GetSub(double val1, double val1_err, double val2, double val2_err,
                     double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 - val2;
    double ans_err = sqrt( pow(val1_err, 2) + pow(val2_err, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

void MirMath::GetMul(double val1, double val1_err, double val2, double val2_err,
                     double* const ans_ptr, double* const ans_err_ptr)
{
    double ans     = val1 * val2;
    double ans_err = sqrt( pow( val1_err * val2, 2) +
                           pow( val2_err * val1, 2) );
    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
}

int MirMath::GetDiv(double val_num, double val_num_err, double val_den, double val_den_err,
                    double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val_den) > DBL_EPSILON) {
        ans     = val_num / val_den;
        ans_err = sqrt( pow( val_num_err * val_den, 2) +
                        pow( val_den_err * val_num, 2) ) / pow( val_den, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


void MirMath::GetAMean(double val1, double val1_err, double val2, double val2_err,
                       double* const amean_ptr, double* const amean_err_ptr)
{
    double amean = (val1 + val2) / 2.;
    double amean_err = sqrt(pow(val1_err, 2) + pow(val2_err, 2)) / 2.;
    
    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}


int MirMath::GetWMean(double val1, double val1_err, double val2, double val2_err,
                      double* const wmean_ptr, double* const wmean_err_ptr)
{
    int status = kRetNormal;
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if(val1_err < DBL_EPSILON || val2_err < DBL_EPSILON) {
        status = kRetError;
    } else {
        double num = val1 / pow(val1_err, 2) + val2 / pow(val2_err, 2);
        double den = 1.0 / pow(val1_err, 2) + 1.0 / pow(val2_err, 2);
        if(den < DBL_EPSILON) {
            status = kRetError;
        } else {
            wmean     = num / den;
            wmean_err = sqrt( 1. / den);
        }
    }
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    return status;
}


// sub_add_ratio = (val1 - val2) / (val1 + val2)
int MirMath::GetSubAddRatio(double val1, double val1_err, double val2, double val2_err,
                            double* const ans_ptr, double* const ans_err_ptr)
{
    int status = kRetNormal;
  
    double ans     = 0.0;
    double ans_err = 0.0;
    if( fabs(val1 + val2) > DBL_EPSILON) {
        ans     = (val1 - val2) / (val1 + val2);
        ans_err = 2 * sqrt( pow(val2 * val1_err, 2) +  pow(val1 * val2_err, 2) )
            / pow(val1 + val2, 2);
        status = kRetNormal;
    } else {
        status = kRetError;
    }

    *ans_ptr = ans;
    *ans_err_ptr = ans_err;
    return status;
}


// For N values without errors
//  for array

double MirMath::GetMin(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
        }
    }
    return min;
}

double MirMath::GetMax(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
        }
    }
    return max;
}

long MirMath::GetLocMin(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);
    double min = val_arr[0];
    long imin = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(min > val_arr[iarr]){
            min = val_arr[iarr];
            imin = iarr;
        }
    }
    return imin;
}

long MirMath::GetLocMax(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double max = val_arr[0];
    long imax = 0;
    for(long iarr = 1; iarr < narr; iarr ++){
        if(max < val_arr[iarr]){
            max = val_arr[iarr];
            imax = iarr;
        }
    }
    return imax;
}

double MirMath::GetSum(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);
    double ans = 0.0;
    for(long idata = 0; idata < narr; idata++){
        ans += val_arr[idata];
    }
    return ans;
}

double MirMath::GetAMean(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double sum = 0.0;
    for (long index = 0; index < narr; index++){
        sum += val_arr[index];
    }
    double ave = sum / narr;
    return ave;
}

double MirMath::GetVariance(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double variance = ( sum2 - pow(sum, 2) / narr ) / narr;
    return variance;
}

double MirMath::GetStddev(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double stddev = sqrt( GetVariance(narr, val_arr) );
    return stddev;
}

double MirMath::GetUnbiasedVariance(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    if(narr < 2){
        char msg[kLineSize];
        sprintf(msg, "narr (=%ld) < 2", narr);
        MPrintErr(msg);
        abort();
    }
    double sum = 0;
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum  += val_arr[index];
        sum2 += val_arr[index] * val_arr[index];
    }
    double unbiased_variance = ( sum2 - pow(sum, 2) / narr ) / (narr - 1);
    return unbiased_variance;
}

double MirMath::GetSqrtOfUnbiasedVariance(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);
    double sqrt_of_unbiased_variance = sqrt( GetUnbiasedVariance(narr, val_arr) );
    return sqrt_of_unbiased_variance;
}


double MirMath::GetRMS(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum2 += val_arr[index] * val_arr[index];
    }
    double rms = sqrt(sum2 / narr);
    return rms;
}

double MirMath::GetMedian(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);
    double ans = TMath::Median(narr, val_arr);
    return ans;
}

// For N values without errors
//  for vector

double MirMath::GetMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMin(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMax(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

long MirMath::GetLocMin(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMin(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

long MirMath::GetLocMax(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    long ans = GetLocMax(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetSum(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSum(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetAMean(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetAMean(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetVariance(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetStddev(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetStddev(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetUnbiasedVariance(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetSqrtOfUnbiasedVariance(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetSqrtOfUnbiasedVariance(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetRMS(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetRMS(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

double MirMath::GetMedian(vector<double> vec)
{
    long narr = 0;
    double* val_arr = NULL;
    MiBase::GenArray(vec, &narr, &val_arr);
    double ans = GetMedian(narr, val_arr);
    MiBase::DelArray(val_arr);
    return ans;
}

// For N values with gaussian errors

void MirMath::GetSum(long narr, const double* const val_arr, const double* const val_err_arr,
                     double* const sum_ptr, double* const sum_err_ptr)
{
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){    
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}

void MirMath::GetAMean(long narr, const double* const val_arr, const double* const val_err_arr,
                       double* const amean_ptr, double* const amean_err_ptr)
{
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        sum += val_arr[index];
        sum_err2 += pow(val_err_arr[index], 2);
    }
    double amean = sum / narr;
    double amean_err = sqrt(sum_err2) / narr;

    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
}

int MirMath::GetWMean(long narr, const double* const val_arr, const double* const val_err_arr,
                      double* const wmean_ptr, double* const wmean_err_ptr,
                      long* const nsel_ptr, int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
            num_bad ++;
        } else {
            nsel ++;
            num += val_arr[index] / pow(val_err_arr[index], 2);
            den += 1. / pow(val_err_arr[index], 2);
            mask_sel_arr[index] = 1;
        }
    }
    double wmean     = num / den;
    double wmean_err = sqrt( 1. / den);
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}




void MirMath::GetSumWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                             const int* const mask_arr,
                             double* const sum_ptr, double* const sum_err_ptr)
{
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    MiBase::IsValidArray(narr, mask_arr);
    double sum      = 0.0;
    double sum_err2 = 0.0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double sum_err = sqrt(sum_err2);
    
    *sum_ptr     = sum;
    *sum_err_ptr = sum_err;
}


void MirMath::GetAMeanWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                               const int* const mask_arr,
                               double* const amean_ptr, double* const amean_err_ptr)
{
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    MiBase::IsValidArray(narr, mask_arr);
    double sum = 0.0;
    double sum_err2 = 0.0;
    long nsel = 0;
    for(long index = 0; index < narr; index++){
        if(1 == mask_arr[index]){
            nsel ++;
            sum += val_arr[index];
            sum_err2 += pow(val_err_arr[index], 2);
        }
    }
    double amean = 0.0;
    double amean_err = 0.0;
    if(nsel > 0){
        amean = sum / nsel;
        amean_err = sqrt(sum_err2) / nsel;
    }
    *amean_ptr     = amean;
    *amean_err_ptr = amean_err;
}


int MirMath::GetWMeanWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                              const int* const mask_arr,
                              double* const wmean_ptr, double* const wmean_err_ptr,
                              long* const nsel_ptr, int** const mask_sel_arr_ptr)
{
    int status = kRetNormal;
    MiBase::IsValidArray(narr, val_arr);
    MiBase::IsValidArray(narr, val_err_arr);
    MiBase::IsValidArray(narr, mask_arr);
    long num_bad = 0;
    double num = 0.0;
    double den = 0.0;
    long nsel = 0;
    int* mask_sel_arr = new int [narr];
    for(long index = 0; index < narr; index++){
        mask_sel_arr[index] = 0;
    }
    for(long index = 0; index < narr; index++){
        if(fabs(mask_arr[index] - 1.0) < DBL_EPSILON){
            if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
                num_bad ++;
            } else {
                nsel ++;
                num += val_arr[index] / pow(val_err_arr[index], 2);
                den += 1. / pow(val_err_arr[index], 2);
                mask_sel_arr[index] = 1;
            }
        }
    }
    double wmean     = 0.0;
    double wmean_err = 0.0;
    if( fabs(den) < DBL_EPSILON ){
        num_bad ++;
    } else {
        wmean     = num / den;
        wmean_err = sqrt( 1. / den);
    }

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;    

    if(num_bad > 0){
        status = kRetError;
    } else {
        status = kRetNormal;
    }
    return status;
}

int MirMath::GetChi2byConst(long narr,
                            const double* const val_arr,
                            const double* const val_err_arr,
                            double* const wmean_ptr,
                            double* const wmean_err_ptr,
                            long* const nsel_ptr,
                            int** const mask_sel_arr_ptr,
                            double* const chi2_ptr,
                            long* const dof_ptr,
                            double* const chi2_red_ptr,
                            double* const prob_ptr)
{
    int status = kRetNormal;
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    int status_getwmean = GetWMean(narr, val_arr, val_err_arr,
                                   &wmean, &wmean_err,
                                   &nsel, &mask_sel_arr);
    double chi2 = 0.0;
    for(long index = 0; index < narr; index ++){
        if(1 == mask_sel_arr[index]){
            if( pow(val_err_arr[index], 2) > DBL_EPSILON ){
                chi2 += pow(val_arr[index] - wmean, 2) / pow(val_err_arr[index], 2);
            }
        }
    }
    long dof = nsel - 1;
    if(dof < 1){
        printf("Error: dof(=%ld) < 1.", dof);
        abort();
    }
    double chi2_red = chi2 / dof;

    // the probability that an observed Chi-squared exceeds
    // the value chi2 by chance, even for a correct model.
    double prob = TMath::Prob(chi2, dof);

    // See Numerical Recipes, Section 6.2
    // prob = Q(chi2, dof) = gammq(dof/2, chi2/2) = 1 - gammp(dof/2, chi2/2)
    //                     = 1 - TMath::Gamma(dof/2, chi2/2)
    // double prob = 1. - TMath::Gamma(dof/2., chi2/2.));
    //

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;
    *chi2_ptr = chi2;
    *dof_ptr = dof;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;

    status = status_getwmean;
    return status;
}

int MirMath::GetChi2byConst(long narr,
                            const double* const val_arr,
                            const double* const val_err_arr,
                            const int* const mask_arr,
                            double* const wmean_ptr,
                            double* const wmean_err_ptr,
                            long* const nsel_ptr,
                            int** const mask_sel_arr_ptr,
                            double* const chi2_ptr,
                            long* const dof_ptr,
                            double* const chi2_red_ptr,
                            double* const prob_ptr)
{
    int status = kRetNormal;
    double wmean = 0.0;
    double wmean_err = 0.0;
    long nsel = 0;
    int* mask_sel_arr = NULL;
    int status_getwmean = GetWMeanWithMask(narr, val_arr, val_err_arr,
                                           mask_arr,
                                           &wmean, &wmean_err,
                                           &nsel, &mask_sel_arr);
    double chi2 = 0.0;
    for(long index = 0; index < narr; index ++){
        if(1 == mask_sel_arr[index]){
            if( pow(val_err_arr[index], 2) > DBL_EPSILON ){
                chi2 += pow(val_arr[index] - wmean, 2) / pow(val_err_arr[index], 2);
            }
        }
    }
    long dof = nsel - 1;
    if(dof < 1){
        printf("Error: dof(=%ld) < 1.", dof);
        abort();
    }
    double chi2_red = chi2 / dof;

    // the probability that an observed Chi-squared exceeds
    // the value chi2 by chance, even for a correct model.
    double prob = TMath::Prob(chi2, dof);

    // See Numerical Recipes, Section 6.2
    // prob = Q(chi2, dof) = gammq(dof/2, chi2/2) = 1 - gammp(dof/2, chi2/2)
    //                     = 1 - TMath::Gamma(dof/2, chi2/2)
    // double prob = 1. - TMath::Gamma(dof/2., chi2/2.));
    //

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *nsel_ptr = nsel;
    *mask_sel_arr_ptr = mask_sel_arr;
    *chi2_ptr = chi2;
    *dof_ptr = dof;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;

    status = status_getwmean;
    return status;
}

// ichiji-hokan
double MirMath::IntPolLin(double xval,
                          double xval_lo, double xval_up,
                          double yval_lo, double yval_up){
    double yval = 0.0;
    if( fabs(xval_up - xval_lo) < DBL_EPSILON ) {
        yval = (yval_up + yval_lo) / 2.;
    } else {
        yval = yval_lo +
            (xval - xval_lo) * (yval_up - yval_lo) / (xval_up - xval_lo);
    }
    return yval;
}



double MirMath::IntPolLin(double xval, double yval,
                          double xval0, double xval1,
                          double yval0, double yval1,
                          double oval_x0y0, double oval_x1y0,
                          double oval_x1y1, double oval_x0y1)
//
// Ichiji-hokan in two demension.
//  
// see Numerical Recipe "Interpolation in Two or More Dimensions"
// y
// ^
// |    (x0,y1):3      (x1,y1):2
// |          (x,y)
// |
// |    (x0,y0):0      (x1,y0):1
// +--------------------------------> x
//
  
{
    double ratio_x = (xval - xval0) / (xval1 - xval0);
    double ratio_y = (yval - yval0) / (yval1 - yval0);

    double oval =
        (1 - ratio_x) * (1 - ratio_y) * oval_x0y0 +
        ratio_x       * (1 - ratio_y) * oval_x1y0 +
        ratio_x       * ratio_y       * oval_x1y1 +
        (1 - ratio_x) * ratio_y       * oval_x0y1;

    return oval;
}

// statistics

double MirMath::ProbGaus(double xval, double mu, double sigma)
{
    double ans = 1./( sigma * sqrt(2.0*M_PI) )
        * exp( (-1.0)*(xval - mu)*(xval - mu)/2.0/sigma/sigma );
    return ans;
}

double MirMath::ProbGausAsym(double xval, double mu,
                             double sigma_plus, double sigma_minus)
{
    double sigma_mean = (sigma_plus + sigma_minus) / 2.0;
    double ans = 0.0;
    if (xval < mu){
        ans = sigma_minus / sigma_mean * ProbGaus(xval, mu, sigma_minus);
    } else {
        ans = sigma_plus  / sigma_mean * ProbGaus(xval, mu, sigma_plus);
    }
    return ans;
}

double MirMath::Sigma2CL(double sigma){
    double cl = TMath::Erf(sigma/sqrt(2));
    return cl;
}

double MirMath::CL2Sigma(double cl){
    double sigma = sqrt(2) * TMath::ErfInverse(cl);
    return sigma;
}

int MirMath::GetPermutation(int n, int r)
{
    // Permutation(n, r) = _nP_r = n! / (n - r)!
    int ans = (int) (TMath::Factorial(n) / TMath::Factorial(n - r));
    return ans;
}

int MirMath::GetCombination(int n, int r)
{
    // Combination(n, r) = _nC_r = _nP_r / r! =  n! / [r! (n - r)!]
    int ans = (int) (TMath::Factorial(n) / TMath::Factorial(r) / TMath::Factorial(n - r));
    return ans;
}

// for binning
long MirMath::GetNbin(double val_lo, double val_up, double delta_val, string mode)
{
    if(val_up <= val_lo){
        printf("ERROR: %s: %u: %s(): val_up <= val_lo.\n",
               __FILE__, __LINE__, __func__);
        abort();
    }
    if(delta_val <= 0){
        printf("ERROR: %s: %u: %s(): delta_val <= 0.\n",
               __FILE__, __LINE__, __func__);
        abort();
    }
    
    double gphase = (val_up - val_lo) / delta_val;
    double phase = gphase - floor(gphase);

    long nbin = 0;
    if(phase < DBL_EPSILON || 1 - phase < DBL_EPSILON){
        double gphase_plus_epsilon = gphase + DBL_EPSILON;
        nbin = (long) floor(gphase_plus_epsilon);
    } else {
        if("err" == mode){
            printf("ERROR: %s: %u: %s(): val_up - val_lo is not an interger of delta_val\n",
                   __FILE__, __LINE__, __func__);
            abort();
        } else if ("floor" == mode){
            nbin = (long) floor(gphase);
        } else if ("ceil" == mode){
            nbin = (long) ceil(gphase);
        } else {
            printf("ERROR: %s: %u: %s(): bad mode (=%s)\n",
                   __FILE__, __LINE__, __func__, mode.c_str());
            abort();
        }
    }
    return nbin;
}

// useful when you want to obtain even number of bin.
long MirMath::GetNbinEven(double val_lo, double val_up, double delta_val)
{
    long nbin_floor = GetNbin(val_lo, val_up, delta_val, "floor");
    if(0 == nbin_floor % 2){
        return nbin_floor;
    } else {
        return nbin_floor + 1;
    }
}

int MirMath::IsSorted(long narr, const double* const val_arr)
{
    MiBase::IsValidArray(narr, val_arr);    
    int ans = 1;
    double val_pre = val_arr[0];
    for (long index = 1; index < narr; index++){
        if(val_pre > val_arr[index]){
            ans = 0;
            break;
        }
        val_pre = val_arr[index];
    }
    return ans;
}

// inner product
double MirMath::GetInProd(double vec0_xval, double vec0_yval,
                          double vec1_xval, double vec1_yval)
{
    double ans = 0.0;
    ans = vec0_xval * vec1_xval + vec0_yval * vec1_yval;
    return ans;
}




