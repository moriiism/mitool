#include "mi_data1d_serr.h"
#include "mi_data1d_ope.h"

//
// public
//

void DataArraySerr1d::Init(long ndata)
{
    InitDataArray1d(ndata);
    InitDataArraySerr1d(ndata);
}

void DataArraySerr1d::SetValSerr(long ndata,
                                 const double* const val_serr)
{
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    if(1 != IsValSerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < ndata; idata++){
        IsValSerrPlus(val_serr[idata]);
        val_serr_[idata] = val_serr[idata];
    }
}


void DataArraySerr1d::SetValSerr(vector<double> val_serr)
{
    if(GetNdata() != (long) val_serr.size()){
        MPrintErrClass("GetNdata() != val_serr.size()");
        abort();
    }
    if(1 != IsValSerrNotNull()){
        abort();
    }
    for(long idata = 0; idata < (long) val_serr.size(); idata++){
        IsValSerrPlus(val_serr[idata]);
        val_serr_[idata] = val_serr[idata];
    }
}

void DataArraySerr1d::SetValAndSerr(long ndata,
                                    const double* const val,
                                    const double* const val_serr)
{
    SetVal(ndata, val);
    SetValSerr(ndata, val_serr);
}


void DataArraySerr1d::SetValAndSerr(vector<double> val,
                                    vector<double> val_serr)
{
    SetVal(val);
    SetValSerr(val_serr);
}

void DataArraySerr1d::InitSetValAndSerr(long ndata,
                                        const double* const val,
                                        const double* const val_serr)
{
    Init(ndata);
    SetValAndSerr(ndata, val, val_serr);
}


void DataArraySerr1d::InitSetValAndSerr(vector<double> val,
                                        vector<double> val_serr)
{
    Init(val.size());
    SetValAndSerr(val, val_serr);
}

void DataArraySerr1d::SetValSerrElm(long idata, double val_serr)
{
    if(1 != IsValSerrNotNull()){
        abort();
    }
    if(1 == IsValidRange(idata)){
        val_serr_[idata] = val_serr;
    } else {
        abort();
    }
}


void DataArraySerr1d::Fill(long idata)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + 1.0;
    SetValElm(idata, val_new);
    SetValSerrElm(idata, sqrt(val_new));
    // poisson error    
}

void DataArraySerr1d::Fill(long idata, double weight)
{
    double val_pre = GetValElm(idata);
    double val_new = val_pre + weight;
    SetValElm(idata, val_new);
    SetValSerrElm(idata, sqrt(val_new));
    // poisson error
}

void DataArraySerr1d::FillByMax(long idata, double val)
{
    double val_pre = GetValElm(idata);
    if(val_pre < val){
        SetValElm(idata, val);
        if(val < 0.0){
            SetValSerrElm(idata, 0.0);
        } else {
            SetValSerrElm(idata, sqrt(val));
        }
    }
}

void DataArraySerr1d::FillByMax(long idata,
                                double val,
                                double val_serr)
{
    double val_pre = GetValElm(idata);
    if(val_pre < val){
        SetValElm(idata, val);
        SetValSerrElm(idata, val_serr);
    }
}


void DataArraySerr1d::FillByMin(long idata, double val)
{
    double val_pre = GetValElm(idata);
    if(val_pre > val){
        SetValElm(idata, val);
        if(val < 0.0){
            SetValSerrElm(idata, 0.0);
        } else {
            SetValSerrElm(idata, sqrt(val));
        }
    }
}

void DataArraySerr1d::FillByMin(long idata,
                                double val,
                                double val_serr)
{
    double val_pre = GetValElm(idata);
    if(val_pre > val){
        SetValElm(idata, val);
        SetValSerrElm(idata, val_serr);
    }
}

void DataArraySerr1d::SetZero()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 0.0);
        SetValSerrElm(idata, 0.0);
    }
}

void DataArraySerr1d::SetOne()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 1.0);
        SetValSerrElm(idata, 1.0);
    }
}

void DataArraySerr1d::SetConst(double constant)
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, constant);
        SetValSerrElm(idata, sqrt(constant));
    }
}

void DataArraySerr1d::SetValErrByPoissonErr()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        double val = GetValElm(idata);
        SetValSerrElm(idata, sqrt(val));
    }
}

DataArraySerr1d* const DataArraySerr1d::Clone() const
{
    DataArraySerr1d* obj_new = new DataArraySerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void DataArraySerr1d::Load(string file)
{
    NullDataArray1d();
    NullDataArraySerr1d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(2 != ncolumn){
            MPrintWarnClass("ncolumn != 2");
        }
        istringstream iss(line_arr[idata]);
        double val_tmp;
        double val_serr_tmp;
        iss >> val_tmp >> val_serr_tmp;
        SetValElm(idata, val_tmp);
        SetValSerrElm(idata, val_serr_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_val_sorted = 0;
    ReadInfo(file, &flag_val_sorted);
    SetFlagValSorted(flag_val_sorted);
}

//
//// operation
//
//void DataArraySerr1d::Sort()
//{
//    if(1 == GetFlagValSorted()){
//        MPrintInfoClass("It has been already sorted.");
//        return;
//    }
//    if(NULL == GetVal() || NULL == GetValSerr()){
//        MPrintErrClass("GetVal() == NULL or GetValSerr() == NULL");
//        abort();
//    }
//    long ndata = GetNdata();
//    double* val_org = new double [ndata];
//    double* val_serr_org = new double [ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        val_org[idata] = GetValElm(idata);
//        val_serr_org[idata] = GetValSerrElm(idata);
//    }
//
//    long* index = new long [ndata];  // to store sort result
//    TMath::Sort(ndata, val_org, index, kFALSE);
//
//    for(long idata = 0; idata < ndata; idata++){
//        SetValElm(idata, val_org[index[idata]]);
//        SetValSerrElm(idata, val_serr_org[index[idata]]);
//    }
//
//    delete [] index; index = NULL;
//    delete [] val_org; val_org = NULL;
//    delete [] val_serr_org; val_serr_org = NULL;
//
//    SetFlagValSorted(1);
//    if(0 < g_flag_verbose){
//        MPrintInfoClass("sorted.");
//    }
//}
//
//void DataArraySerr1d::Scale(const DataArray1d* const data_array,
//                            double scale, double offset)
//{
//    DataArraySerr1d* data_array_tmp = new DataArraySerr1d;
//    data_array_tmp->Copy(data_array);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetScale(data_array_tmp, scale, offset, out);
//    Copy(out);
//    delete data_array_tmp;
//    delete out;
//}
//
//void DataArraySerr1d::Min(const DataArray1d* const data_array1,
//                          const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetMin(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArraySerr1d::Min(const DataArraySerr1d* const* const data_array_arr,
//                          int ndata_array)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//        // data_array_arr_tmp[idata] = data_array_arr[idata]->Clone();
//    }
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetMin(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//
//void DataArraySerr1d::Max(const DataArray1d* const data_array1,
//                          const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetMax(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArraySerr1d::Max(const DataArraySerr1d* const* const data_array_arr,
//                          int ndata_array)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetMax(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//
//void DataArraySerr1d::Add(const DataArray1d* const data_array1,
//                          const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetAdd(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArraySerr1d::Add(const DataArraySerr1d* const* const data_array_arr,
//                          int ndata_array)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetAdd(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArraySerr1d::Sub(const DataArray1d* const data_array1,
//                          const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetSub(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArraySerr1d::Mul(const DataArray1d* const data_array1,
//                          const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetMul(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//int DataArraySerr1d::Div(const DataArray1d* const data_array_num,
//                         const DataArray1d* const data_array_den,
//                         vector<long>* const index_bad_vec_ptr)
//{
//    DataArraySerr1d* data_array_num_tmp = new DataArraySerr1d;
//    data_array_num_tmp->Copy(data_array_num);
//    DataArraySerr1d* data_array_den_tmp = new DataArraySerr1d;
//    data_array_den_tmp->Copy(data_array_den);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    vector<long> index_bad_vec;
//    DataArray1dOpe::GetDiv(data_array_num_tmp,
//                           data_array_den_tmp,
//                           &index_bad_vec,
//                           out);
//    Copy(out);
//    delete data_array_num_tmp;
//    delete data_array_den_tmp;
//    delete out;
//    *index_bad_vec_ptr = index_bad_vec;
//    return index_bad_vec.size();
//}
//
//void DataArraySerr1d::AMean(const DataArray1d* const data_array1,
//                            const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetAMean(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArraySerr1d::AMean(const DataArraySerr1d* const* const data_array_arr,
//                            int ndata_array)
//
//{
//    abort();
//}
//
//
//long DataArraySerr1d::WMean(const DataArraySerr1d* const data_array1,
//                            const DataArraySerr1d* const data_array2,
//                            vector<long>* const index_bad_vec_ptr)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    vector<long> index_bad_vec;
//    DataArray1dOpe::GetWMean(data_array1_tmp,
//                             data_array2_tmp,
//                             &index_bad_vec,
//                             out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;
//    delete out;
//    *index_bad_vec_ptr = index_bad_vec;
//    return index_bad_vec.size();
//}
//
//
//long DataArraySerr1d::WMean(const DataArraySerr1d* const* const data_array_arr,
//                            int ndata_array,
//                            vector<long>* const index_bad_vec_ptr)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArraySerr1d* out = new DataArraySerr1d;
//    vector<long> index_bad_vec;
//    DataArray1dOpe::GetWMean(data_array_arr,
//                             ndata_array,
//                             &index_bad_vec,
//                             out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//    *index_bad_vec_ptr = index_bad_vec;
//    return index_bad_vec.size();
//}
//
//
//void DataArraySerr1d::SubAddRatio(const DataArray1d* const data_array1,
//                                  const DataArray1d* const data_array2)
//{
//    DataArraySerr1d* data_array1_tmp = new DataArraySerr1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArraySerr1d* data_array2_tmp = new DataArraySerr1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArraySerr1d* out = new DataArraySerr1d;
//    vector<long> index_bad_vec;
//    DataArray1dOpe::GetSubAddRatio(data_array1_tmp, data_array2_tmp,
//                                   &index_bad_vec, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//
//void DataArraySerr1d::AddWithMask(const DataArraySerr1d* const* const data_array_arr,
//                                  const DataArray1d* const* const mask_array_arr,
//                                  int ndata_array)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetAddWithMask(data_array_arr_tmp,
//                                   mask_array_arr,
//                                   ndata_array,
//                                   out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//long DataArraySerr1d::WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
//                                    const DataArray1d* const* const mask_array_arr,
//                                    int ndata_array,
//                                    vector<long>* const index_bad_vec_ptr,
//                                    DataArraySerr1d* const nvalid_array_out)
//{
//    DataArraySerr1d** data_array_arr_tmp = new DataArraySerr1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArraySerr1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    vector<long> index_bad_vec;
//    DataArraySerr1d* out = new DataArraySerr1d;
//    DataArray1dOpe::GetWMeanWithMask(data_array_arr_tmp,
//                                     mask_array_arr,
//                                     ndata_array,
//                                     &index_bad_vec,
//                                     nvalid_array_out,
//                                     out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//    *index_bad_vec_ptr = index_bad_vec;
//    return index_bad_vec.size();
//}
//

// get

double DataArraySerr1d::GetValSerrElm(long idata) const
{
    if(1 == IsValidRange(idata)){
        return val_serr_[idata];
    } else {
        abort();
    }
}


// statistic

void DataArraySerr1d::GetSum(double* const add_ptr,
                             double* const add_err_ptr) const
{
    double add = 0.0;
    double add_err = 0.0;
    MiMath::GetAdd(GetNdata(), GetVal(), GetValSerr(), &add, &add_err);

    *add_ptr = add;
    *add_err_ptr = add_err;
}


long DataArraySerr1d::GetWMean(double* const wmean_ptr,
                               double* const wmean_err_ptr,
                               vector<long>* const index_bad_vec_ptr) const
{
    double wmean = 0.0;
    double wmean_err = 0.0;
    vector<long> index_bad_vec;
    long num_bad = MiMath::GetWMean(GetNdata(), GetVal(), GetValSerr(),
                                    &wmean, &wmean_err, &index_bad_vec);
    if(num_bad > 0){
        char msg[kLineSize];
        sprintf(msg, "num_bad = %ld", num_bad);
        MPrintInfoClass(msg);
    }
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
    *index_bad_vec_ptr = index_bad_vec;
    return num_bad;
}


double DataArraySerr1d::GetAMeanOfSerr() const
{
    double ans = MiMath::GetAMean(GetNdata(), GetValSerr());
    return ans;
}

long DataArraySerr1d::GetChi2byConst(double* const chi2_ptr,
                                     long* const dof_ptr,
                                     double* const chi2_red_ptr,
                                     double* const prob_ptr) const
{
    double chi2 = 0.0;
    long dof = 0;
    double chi2_red = 0.0;
    double prob = 0.0;
    abort();
    
///    long num_bad = MiMath::GetChi2byConst(GetNdata(), GetVal(), GetValSerr(),
//                                          &chi2, &dof, &chi2_red, &prob);

    *chi2_ptr = chi2;
    *dof_ptr = dof;
    *chi2_red_ptr = chi2_red;
    *prob_ptr = prob;
//    return num_bad;
    abort();
    return 0;
}

//void DataArraySerr1d::GetStat1dim(Stat1dim* const stat_1dim_out) const
//{
//    long ndata        = GetNdata();
//    double min        = GetValMin();
//    double max        = GetValMax();
//
//    double sum = 0.0;
//    double sum_err = 0.0;
//    GetSum(&sum, &sum_err);
//    double amean      = GetAMean();
//    double variance   = GetVariance();
//    double stddev     = GetStddev();
//    double unbiased_variance = GetUnbiasedVariance();
//    double sqrt_of_unbiased_variance = GetSqrtOfUnbiasedVariance();
//    double rms        = GetRMS();
//    // double median     = GetMedian();
//    double median     = 0.0;
//    
//    double wmean, wmean_err;
//    vector<long> index_bad_vec;
//    long num_bad_wmean = GetWMean(&wmean, &wmean_err, &index_bad_vec);
//    double amean_of_err = GetAMeanOfSerr();
//  
//    double chi2;
//    long ndf;
//    double chi2_red;
//    double prob_chi2;
//    GetChi2byConst(&chi2, &ndf, &chi2_red, &prob_chi2);
//    stat_1dim_out->Set(ndata, min, max,
//                       sum, sum_err, amean, variance, stddev,
//                       unbiased_variance, sqrt_of_unbiased_variance,
//                       rms, median, wmean, wmean_err, num_bad_wmean, 
//                       amean_of_err,
//                       ndf, chi2, chi2_red, prob_chi2);
//}

// for qdp

double DataArraySerr1d::GetValAndErrMin() const
{
    long ndata = GetNdata();
    double* val_tmp = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        val_tmp[idata] = GetValElm(idata) - GetValSerrElm(idata);
    }
    double min = MiMath::GetMin(ndata, val_tmp);
    delete [] val_tmp;
    return min;
}

double DataArraySerr1d::GetValAndErrMax() const
{
    long ndata = GetNdata();
    double* val_tmp = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        val_tmp[idata] = GetValElm(idata) + GetValSerrElm(idata);
    }
    double max = MiMath::GetMax(ndata, val_tmp);
    delete [] val_tmp;
    return max;
}


void DataArraySerr1d::GetRangeValQdp(double* const lo_ptr,
                                     double* const up_ptr) const
{
    double lo, up;
    MiMath::GetRangeQdp(GetValAndErrMin(), GetValAndErrMax(), &lo, &up);
    *lo_ptr = lo;
    *up_ptr = up;
}

// output

void DataArraySerr1d::PrintData(FILE* fp, int mode,
                                double offset_val) const
{
    long ndata = GetNdata();
    if(0 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e\n",
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else if (1 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%ld   %.10e  %.10e\n",
                    idata,
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else if (2 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  %.10e  1.0\n",
                    GetValElm(idata) - offset_val,
                    GetValSerrElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%d).", mode);
        MPrintErrClass(msg);
        abort();
    }
}

double DataArraySerr1d::GetOffsetValFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetValAndErrMin() + GetValAndErrMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

//
// private
//


void DataArraySerr1d::NullDataArraySerr1d()
{
    if(NULL != val_serr_) {delete [] val_serr_; val_serr_ = NULL;}
}


void DataArraySerr1d::InitDataArraySerr1d(long ndata)
{
    NullDataArraySerr1d();
    if(GetNdata() != ndata){
        MPrintErrClass("GetNdata() != ndata");
        abort();
    }
    val_serr_ = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        val_serr_[idata] = 0.0;
    }
}

int DataArraySerr1d::IsValSerrNotNull() const
{
    if(NULL == GetValSerr()){
        MPrintErrClass("bad GetValSerr() (=NULL)");
        abort();
    }
    return 1;
}

