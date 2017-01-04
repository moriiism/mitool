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
    if (val > 0) return 1;
    return 0;
}

int MirMath::IsMinus(double val)
{
    if (val < 0) return 1;
    return 0;
}


int MirMath::Sign(double val)
{
    if (val > 0) return 1;
    if (val < 0) return -1;
    return 0;
}

double MirMath::FilterPlus(double val)
{
    if (val > 0) return val;
    return 0;
}

double MirMath::FilterMinus(double val)
{
    if (val < 0) return val;
    return 0;
}

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


int MirMath::GetAMean(double val1, double val1_err, double val2, double val2_err,
                       double* const amean_ptr, double* const amean_err_ptr)
{
    int status = kRetNormal;
    double amean = (val1 + val2) / 2.;
    double amean_err = sqrt(pow(val1_err, 2) + pow(val2_err, 2)) / 2.;
    
    *amean_ptr = amean;
    *amean_err_ptr = amean_err;
    return status;
}


int MirMath::GetWMean(double val1, double val1_err, double val2, double val2_err,
                       double* const wmean_ptr, double* const wmean_err_ptr)
{
    int status = kRetNormal;
    if(val1_err < DBL_EPSILON || val2_err < DBL_EPSILON) {
        status = kRetError;
        return status;
    }
    double num = val1 / pow(val1_err, 2) + val2 / pow(val2_err, 2);
    double den = 1.0 / pow(val1_err, 2) + 1.0 / pow(val2_err, 2);
    double wmean     = num / den;
    double wmean_err = sqrt( 1. / den);

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
    double val = *std::min_element(val_arr, val_arr + narr);
    return val;
}

double MirMath::GetMax(long narr, const double* const val_arr)
{
    double val = *std::max_element(val_arr, val_arr + narr);
    return val;
}

long MirMath::GetLocMin(long narr, const double* const val_arr)
{
    if(narr <= 0){
        abort();
    }
    if(NULL == val_arr){
        abort();
    }
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
    if(narr <= 0){
        abort();
    }
    if(NULL == val_arr){
        abort();
    }
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

double MirMath::GetAdd(long narr, const double* const val_arr)
{
    double ans = 0.0;
    for(long idata = 0; idata < narr; idata++){
        ans += val_arr[idata];
    }
    return ans;
}

double MirMath::GetAMean(long narr, const double* const val_arr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }
  
    double sum = 0.0;
    for (long index = 0; index < narr; index++){
        sum += val_arr[index];
    }
    double ave = sum / narr;
    return ave;
}


double MirMath::GetVariance(long narr, const double* const val_arr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }
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
    double stddev = sqrt( GetVariance(narr, val_arr) );
    return stddev;
}

double MirMath::GetUnbiasedVariance(long narr, const double* const val_arr)
{
    if(narr < 2){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
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
    double sqrt_of_unbiased_variance = sqrt( GetUnbiasedVariance(narr, val_arr) );
    return sqrt_of_unbiased_variance;
}


double MirMath::GetRMS(long narr, const double* const val_arr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }
    double sum2 = 0;
    for (long index = 0; index < narr; index++){
        sum2 += val_arr[index] * val_arr[index];
    }
    double rms = sqrt(sum2 / narr);
    return rms;
}



// For N values without errors
//  for vector

double MirMath::GetMin(vector<double> vec)
{
    double val = *min_element(vec.begin(), vec.end());
    return val;
}

double MirMath::GetMax(vector<double> vec)
{
    double val = *max_element(vec.begin(), vec.end());
    return val;
}

double MirMath::GetAdd(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetAdd(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetAMean(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetAMean(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetVariance(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetVariance(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetStddev(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetStddev(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetUnbiasedVariance(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetUnbiasedVariance(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetSqrtOfUnbiasedVariance(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetSqrtOfUnbiasedVariance(narr, val_arr);
    delete [] val_arr;
    return ans;
}

double MirMath::GetRMS(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    double ans = GetRMS(narr, val_arr);
    delete [] val_arr;
    return ans;
}

// For N values with gaussian errors

void MirMath::GetAdd(long narr, const double* const val_arr, const double* const val_err_arr,
                      double* const val_add_ptr, double* const val_add_err_ptr)
{
    double val_add      = 0.0;
    double val_add_err  = 0.0;
    double val_add_err2 = 0.0;
    for(long idata = 0; idata < narr; idata++){
        val_add += val_arr[idata];
        val_add_err2 += pow(val_err_arr[idata], 2);
    }
    val_add_err = sqrt(val_add_err2);
    
    *val_add_ptr     = val_add;
    *val_add_err_ptr = val_add_err;
}

void MirMath::GetAMean(long narr, const double* const val_arr, const double* const val_err_arr,
                        double* const amean_ptr, double* const amean_err_ptr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }

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
                       vector<long>* const index_bad_vec_ptr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }
  
    long num_bad = 0;
    vector<long> index_bad_vec;
    double num = 0.0;
    double den = 0.0;
    
    for(long index = 0; index < narr; index++){
        if( pow(val_err_arr[index], 2) < DBL_EPSILON ){
            index_bad_vec.push_back(index);
            num_bad ++;
        } else {
            num += val_arr[index] / pow(val_err_arr[index], 2);
            den += 1. / pow(val_err_arr[index], 2);
        }
    }
    double wmean     = num / den;
    double wmean_err = sqrt( 1. / den);

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *index_bad_vec_ptr = index_bad_vec;
    return num_bad;
}


void MirMath::GetAddWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                              const int* const mask_arr,
                              double* const val_add_ptr, double* const val_add_err_ptr)
{
    double val_add      = 0.0;
    double val_add_err  = 0.0;
    double val_add_err2 = 0.0;
    for(long idata = 0; idata < narr; idata++){
        val_add += val_arr[idata] * mask_arr[idata];
        val_add_err2 += pow(val_err_arr[idata] * mask_arr[idata], 2);
    }
    val_add_err = sqrt(val_add_err2);
    
    *val_add_ptr     = val_add;
    *val_add_err_ptr = val_add_err;
}

int MirMath::GetWMeanWithMask(long narr, const double* const val_arr, const double* const val_err_arr,
                               const int* const mask_arr,
                               double* const wmean_ptr, double* const wmean_err_ptr,
                               vector<long>* const index_bad_vec_ptr)
{
    if(narr < 1){
        printf("ERROR: %s: %u: %s(): bad narr (= %ld)\n",
               __FILE__, __LINE__, __func__, narr);
        abort();
    }
  
    long num_bad = 0;
    vector<long> index_bad_vec;
    double num = 0.0;
    double den = 0.0;
  
    for(long index = 0; index < narr; index++){
        if(fabs(mask_arr[index]) < DBL_EPSILON ||
           pow(val_err_arr[index], 2) < DBL_EPSILON ){
            index_bad_vec.push_back(index);
            num_bad ++;            
        } else {
            num += val_arr[index] / pow(val_err_arr[index], 2);
            den += 1. / pow(val_err_arr[index], 2);
        }
    }

    double wmean     = 0.0;
    double wmean_err = 0.0;
    if(num_bad == narr){
        wmean = 0.0;
        wmean_err = 0.0;
        printf("Warning: %s: %u: %s(): num_bad == narr (= %ld)\n",
               __FILE__, __LINE__, __func__, num_bad);
    } else if( fabs(den) < DBL_EPSILON ){
        wmean = 0.0;
        wmean_err = 0.0;
        printf("Warning: %s: %u: %s(): den < epsilon\n",
               __FILE__, __LINE__, __func__);
    } else {
        wmean     = num / den;
        wmean_err = sqrt( 1. / den);
    }

    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *index_bad_vec_ptr = index_bad_vec;
    return num_bad;
}


// --------------------------------------------------

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


// ---------------------------


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


void MirMath::GetRangeQdp(double min, double max,
                           double* const low_ptr, double* const up_ptr)
{
    double width = (max - min) * 1.2;
    double center = (max + min) / 2.;
    double low = center - width / 2.;
    double up  = center + width / 2.;
    *low_ptr = low;
    *up_ptr  = up;
}

int MirMath::IsSorted(long narr, const double* const val_arr)
{
    if(narr < 1){
        MPrintErr("bad narr");
        abort();
    }
    if(NULL == val_arr){
        MPrintErr("bad val_arr (=NULL)");
        abort();
    }
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


// vector --> array

double* const MirMath::GenArray(vector<double> vec)
{
    long narr = vec.size();
    double* val_arr = new double [narr];
    for(long idata = 0; idata < narr; idata ++){
        val_arr[idata] = vec[idata];
    }
    return val_arr;
}

// inner product
double MirMath::GetInProd(double vec0_xval, double vec0_yval,
                           double vec1_xval, double vec1_yval)
{
    double ans = 0.0;
    ans = vec0_xval * vec1_xval + vec0_yval * vec1_yval;
    return ans;
}
