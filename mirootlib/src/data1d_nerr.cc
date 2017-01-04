#include "mir_data1d_nerr.h"
#include "mir_data1d_ope.h"

//
// public
//

void DataArrayNerr1d::Init(long ndata)
{
    InitDataArray1d(ndata);
}

void DataArrayNerr1d::Fill(long idata)
{
    double val_pre = GetValElm(idata);
    SetValElm(idata, val_pre + 1.0);
}

void DataArrayNerr1d::Fill(long idata, double weight)
{
    double val_pre = GetValElm(idata);
    SetValElm(idata, val_pre + weight);
}

void DataArrayNerr1d::FillByMax(long idata, double oval)
{
    double val_pre = GetValElm(idata);
    if(val_pre < oval){
        SetValElm(idata, oval);
    }
}

void DataArrayNerr1d::FillByMin(long idata, double oval)
{
    double val_pre = GetValElm(idata);
    if(val_pre > oval){
        SetValElm(idata, oval);
    }
}

void DataArrayNerr1d::SetZero()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 0.0);
    }
}

void DataArrayNerr1d::SetOne()
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, 1.0);        
    }
}

void DataArrayNerr1d::SetConst(double constant)
{
    for(long idata = 0; idata < GetNdata(); idata ++){
        SetValElm(idata, constant);        
    }
}

DataArrayNerr1d* const DataArrayNerr1d::Clone() const
{
    DataArrayNerr1d* obj_new = new DataArrayNerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void DataArrayNerr1d::Load(string file)
{
    NullDataArray1d();

    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(1 != ncolumn){
            MPrintWarnClass("ncolumn != 1");
        }
        istringstream iss(line_arr[idata]);
        double val_tmp;
        iss >> val_tmp;
        SetValElm(idata, val_tmp);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_val_sorted = 0;
    ReadInfo(file, &flag_val_sorted);
    SetFlagValSorted(flag_val_sorted);
}

//
//// operation
//
//void DataArray1d::Sort()
//{
//    if(1 == GetFlagValSorted()){
//        MPrintInfoClass("It has been already sorted.");
//        return;
//    }
//    if(NULL == GetVal()){
//        MPrintErrClass("GetVal() == NULL");
//        abort();
//    }
//    long ndata = GetNdata();
//    double* val_org = new double [ndata];
//    for(long idata = 0; idata < ndata; idata++){
//        val_org[idata] = GetValElm(idata);
//    }
//
//    long* index = new long [ndata];  // to store sort result
//    TMath::Sort(ndata, val_org, index, kFALSE);
//
//    for(long idata = 0; idata < ndata; idata++){
//        SetValElm(idata, val_org[index[idata]]);
//    }
//
//    delete [] index; index = NULL;
//    delete [] val_org; val_org = NULL;
//
//    SetFlagValSorted(1);
//    if(0 < g_flag_verbose){
//        MPrintInfoClass("sorted.");
//    }
//}
//
//void DataArray1d::Not(const DataArray1d* const data_array)
//{
//    DataArray1d* data_array_tmp = new DataArray1d;
//    data_array_tmp->Copy(data_array);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetNot(data_array_tmp, out);
//    Copy(out);
//    delete data_array_tmp;
//    delete out;
//}
//
//void DataArray1d::Scale(const DataArray1d* const data_array,
//                        double scale, double offset)
//{
//    DataArray1d* data_array_tmp = new DataArray1d;
//    data_array_tmp->Copy(data_array);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetScale(data_array_tmp, scale, offset, out);
//    Copy(out);
//    delete data_array_tmp;
//    delete out;
//}
//
//
//void DataArray1d::Min(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMin(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//
//void DataArray1d::Min(const DataArray1d* const* const data_array_arr,
//                      int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        //data_array_arr_tmp[idata] = new DataArray1d;
//        // data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//        data_array_arr_tmp[idata] = data_array_arr[idata]->Clone();
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMin(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::Max(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMax(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArray1d::Max(const DataArray1d* const* const data_array_arr,
//                      int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMax(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::Add(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetAdd(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArray1d::Add(const DataArray1d* const* const data_array_arr,
//                      int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetAdd(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::Sub(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetSub(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArray1d::Mul(const DataArray1d* const data_array1,
//                      const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMul(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//int DataArray1d::Div(const DataArray1d* const data_array_num,
//                     const DataArray1d* const data_array_den,
//                     vector<long>* const index_bad_vec_ptr)
//{
//    DataArray1d* data_array_num_tmp = new DataArray1d;
//    data_array_num_tmp->Copy(data_array_num);
//    DataArray1d* data_array_den_tmp = new DataArray1d;
//    data_array_den_tmp->Copy(data_array_den);
//    DataArray1d* out = new DataArray1d;
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
//void DataArray1d::AMean(const DataArray1d* const data_array1,
//                        const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetAMean(data_array1_tmp, data_array2_tmp, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArray1d::AMean(const DataArray1d* const* const data_array_arr,
//                        int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetAMean(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::SubAddRatio(const DataArray1d* const data_array1,
//                              const DataArray1d* const data_array2)
//{
//    DataArray1d* data_array1_tmp = new DataArray1d;
//    data_array1_tmp->Copy(data_array1);
//    DataArray1d* data_array2_tmp = new DataArray1d;
//    data_array2_tmp->Copy(data_array2);
//    DataArray1d* out = new DataArray1d;
//    vector<long> index_bad_vec;
//    DataArray1dOpe::GetSubAddRatio(data_array1_tmp, data_array2_tmp,
//                                   &index_bad_vec, out);
//    Copy(out);
//    delete data_array1_tmp;
//    delete data_array2_tmp;    
//    delete out;
//}
//
//void DataArray1d::Variance(const DataArray1d* const* const data_array_arr,
//                           int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetVariance(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::Stddev(const DataArray1d* const* const data_array_arr,
//                         int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetStddev(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::UnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                         int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetUnbiasedVariance(data_array_arr_tmp, ndata_array, out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::SqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                         int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetSqrtOfUnbiasedVariance(data_array_arr_tmp,
//                                              ndata_array,
//                                              out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::RMS(const DataArray1d* const* const data_array_arr,
//                      int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetRMS(data_array_arr_tmp,
//                           ndata_array,
//                           out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::Median(const DataArray1d* const* const data_array_arr,
//                         int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetMedian(data_array_arr_tmp,
//                              ndata_array,
//                              out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}
//
//void DataArray1d::AddWithMask(const DataArray1d* const* const data_array_arr,
//                              const DataArray1d* const* const mask_array_arr,
//                              int ndata_array)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
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
//void DataArray1d::AMeanWithMask(const DataArray1d* const* const data_array_arr,
//                                const DataArray1d* const* const mask_array_arr,
//                                int ndata_array,
//                                DataArray1d* const nvalid_array_out)
//{
//    DataArray1d** data_array_arr_tmp = new DataArray1d* [ndata_array];
//    for(int idata = 0; idata < ndata_array; idata++){
//        data_array_arr_tmp[idata] = new DataArray1d;
//        data_array_arr_tmp[idata]->Copy(data_array_arr[idata]);
//    }
//    DataArray1d* out = new DataArray1d;
//    DataArray1dOpe::GetAMeanWithMask(data_array_arr_tmp,
//                                     mask_array_arr,
//                                     ndata_array,
//                                     nvalid_array_out,
//                                     out);
//    Copy(out);
//    for(int idata = 0; idata < ndata_array; idata++){
//        delete data_array_arr_tmp[idata];
//    }
//    delete [] data_array_arr_tmp;
//    delete out;
//}


// get


void DataArrayNerr1d::GetRangeValQdp(double* const lo_ptr,
                                     double* const up_ptr) const
{
    double lo, up;
    MirMath::GetRangeQdp(GetValMin(), GetValMax(), &lo, &up);
    *lo_ptr = lo;
    *up_ptr = up;
}

void DataArrayNerr1d::PrintData(FILE* fp, int mode,
                                double offset_val) const
{
    long ndata = GetNdata();    
    if(0 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e\n",
                    GetValElm(idata) - offset_val);
        }
    } else if (1 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%ld   %.10e\n",
                    idata, GetValElm(idata) - offset_val);
        }
    } else if (2 == mode){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.10e  1.0\n",
                    GetValElm(idata) - offset_val);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad mode (=%d).", mode);
        MPrintErrClass(msg);
        abort();
    }
}

double DataArrayNerr1d::GetOffsetValFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetValMin() + GetValMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}
