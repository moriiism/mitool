#ifndef MITOOL_MILIB_DATA1D_NERR_H_
#define MITOOL_MILIB_DATA1D_NERR_H_

#include "mi_data1d.h"

class DataArrayNerr1d : public DataArray1d{
public:
    explicit DataArrayNerr1d(string title = "") :
        DataArray1d("DataArrayNerr1d", title) {}
    ~DataArrayNerr1d() {
        NullDataArray1d();
    }

    // Init
    void Init(long ndata);
    
    void Fill(long idata);
    void Fill(long idata, double weight);
    void FillByMax(long idata, double val);
    void FillByMin(long idata, double val);

    void SetZero();
    void SetOne();
    void SetConst(double constant);

    // kinds of InitSet
    DataArrayNerr1d* const Clone() const;
    void Load(string file);

//    // operation
//    void Sort();
//    void Scale(const DataArray1d* const data_array,
//               double scale, double offset);
//    void Min(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Min(const DataArrayNerr1d* const* const data_array_arr,
//             int ndata_array);
//    void Max(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Max(const DataArrayNerr1d* const* const data_array_arr,
//             int ndata_array);
//
//    void Add(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Add(const DataArrayNerr1d* const* const data_array_arr,
//             int ndata_array);
//
//    void Sub(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Mul(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    int  Div(const DataArray1d* const data_array_num,
//             const DataArray1d* const data_array_den,
//             vector<long>* const index_bad_vec_ptr);
//    void AMean(const DataArray1d* const data_array1,
//               const DataArray1d* const data_array2);
//    void AMean(const DataArray1d* const* const data_array_arr,
//               int ndata_array);
//
//    // sub_add_ratio = (h1 - h2) / (h1 + h2)
//    void SubAddRatio(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2);
//    void Variance(const DataArrayNerr1d* const* const data_array_arr,
//                  int ndata_array);
//    void Stddev(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array);
//    void UnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
//                          int ndata_array);
//    void SqrtOfUnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
//                                int ndata_array);
//    void RMS(const DataArrayNerr1d* const* const data_array_arr,
//             int ndata_array);
//    void Median(const DataArrayNerr1d* const* const data_array_arr,
//                int ndata_array);
//    void AddWithMask(const DataArrayNerr1d* const* const data_array_arr,
//                     const DataArrayNerr1d* const* const mask_array_arr,
//                     int ndata_array);
//    void AMeanWithMask(const DataArrayNerr1d* const* const data_array_arr,
//                       const DataArrayNerr1d* const* const mask_array_arr,
//                       int ndata_array,
//                       DataArray1d* const nvalid_array_out);

    //
    // const functions
    //

    // void GetStat1dim(Stat1dim* const stat_1dim_out) const;
    
//    // for qdp
//    // min of val - val_serr
//    // max of val + val_serr
    void GetRangeValQdp(double* const lo_ptr,
                        double* const up_ptr) const;

    // output
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
};


#endif // MITOOL_MILIB_DATA1D_NERR_H_

