#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_

#include "mir_data1d.h"

class DataArraySerr1d : public DataArray1d{
public:
    explicit DataArraySerr1d(string title = "") :
        DataArray1d("DataArraySerr1d", title),
        val_serr_(NULL) {}
    ~DataArraySerr1d() {
        NullDataArray1d();
        NullDataArraySerr1d();
    }

    // Init
    void Init(long ndata);

    // Set
    void SetValSerr(long ndata,
                    const double* const val_serr);
    void SetValSerr(vector<double> val_serr);
    void SetValAndSerr(long ndata,
                       const double* const val,
                       const double* const val_serr);
    void SetValAndSerr(vector<double> val,
                       vector<double> val_serr);

    // Init & Set
    void InitSetValAndSerr(long ndata,
                           const double* const val,
                           const double* const val_serr);
    void InitSetValAndSerr(vector<double> val,
                           vector<double> val_serr);

    // kinds of Set
    void SetValSerrElm(long idata, double val_serr);

  
    void Fill(long idata);
    void Fill(long idata, double weight);
    // poisson error
    void FillByMax(long idata, double val);
    void FillByMax(long idata,
                   double val,
                   double val_serr);
    void FillByMin(long idata, double val);
    void FillByMin(long idata,
                   double val,
                   double val_serr);

    void SetZero();
    void SetOne();
    void SetConst(double constant);

    void SetValErrByPoissonErr();
    
    // kinds of InitSet
    DataArraySerr1d* const Clone() const;
    void Load(string file);

//    // operation
//    void Sort();
//    void Scale(const DataArray1d* const data_array,
//               double scale, double offset);
//    void Min(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Min(const DataArraySerr1d* const* const data_array_arr,
//             int ndata_array);
//
//    void Max(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Max(const DataArraySerr1d* const* const data_array_arr,
//             int ndata_array);
//    
//    void Add(const DataArray1d* const data_array1,
//             const DataArray1d* const data_array2);
//    void Add(const DataArraySerr1d* const* const data_array_arr,
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
//    void AMean(const DataArraySerr1d* const* const data_array_arr,
//               int ndata_array);
//    
//    long WMean(const DataArraySerr1d* const data_array1,
//               const DataArraySerr1d* const data_array2,
//               vector<long>* const index_bad_vec_ptr);
//    long WMean(const DataArraySerr1d* const* const data_array_arr,
//               int ndata_array,
//               vector<long>* const index_bad_vec_ptr);
//
//    void SubAddRatio(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2);
//    
//    void AddWithMask(const DataArraySerr1d* const* const data_array_arr,
//                     const DataArray1d* const* const mask_array_arr,
//                     int ndata_array);
//    long WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
//                       const DataArray1d* const* const mask_array_arr,
//                       int ndata_array,
//                       vector<long>* const index_bad_vec_ptr,
//                       DataArraySerr1d* const nvalid_array_out);

    //
    // const functions
    //
  
    // get
    const double* const GetValSerr() const {return val_serr_;};
    double GetValSerrElm(long idata) const;

    // statistic
    using DataArray1d::GetSum;
    void GetSum(double* const add_ptr,
                double* const add_err_ptr) const;
    long GetWMean(double* const wmean_ptr,
                  double* const wmean_err_ptr,
                  vector<long>* const index_bad_vec_ptr) const;
    double GetAMeanOfSerr() const;
    long GetChi2byConst(double* const chi2_ptr,
                        long* const dof_ptr,
                        double* const chi2_red_ptr,
                        double* const prob_ptr) const;
    // void GetStat1dim(Stat1dim* const stat_1dim_out) const;

    // useful for qdp
    // min of val - val_serr
    // max of val + val_serr
    double GetValAndErrMin() const;
    double GetValAndErrMax() const;
    void GetRangeValQdp(double* const lo_ptr,
                        double* const up_ptr) const;
    
    // output
    void PrintData(FILE* fp, int mode,
                   double offset_val) const;

    double GetOffsetValFromTag(string offset_tag) const;
    
private:
    double* val_serr_;  // >= 0
    
    void NullDataArraySerr1d();
    void InitDataArraySerr1d(long ndata);
    int IsValSerrNotNull() const;
};


#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_SERR_H_
