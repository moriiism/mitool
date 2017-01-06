#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_H_

#include "mir_math.h"
#include "mir_stat1d.h"
#include "mir_interval.h"

class DataArrayNerr1d;
class DataArraySerr1d;
class DataArrayTerr1d;

class DataArray1d : public MiObject{
public:
    DataArray1d(string class_name, string title) :
        MiObject(class_name, title),
        ndata_(0),
        val_(NULL),
        flag_val_sorted_(0) {}
    virtual ~DataArray1d() {}

    // Init
    virtual void Init(long ndata) = 0;

    // Set
    void Set(const DataArray1d* const org);
    void SetVal(long ndata, const double* const val);
    void SetVal(vector<double> val);
    void SetFlagValSorted(int flag_val_sorted)
        {flag_val_sorted_ = flag_val_sorted;};

    // DataArraySerr1d
    virtual void SetValSerr(long ndata,
                            const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValSerr(vector<double> val_serr)
        {MPrintErrVFunc; abort();};

    // DataArrayTerr1d
    virtual void SetValTerr(long ndata,
                            const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerr(vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerr(long ndata,
                            const double* const val_terr_plus,
                            const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerr(vector<double> val_terr_plus,
                            vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};
  
    // DataArraySerr1d
    virtual void SetValAndSerr(long ndata,
                               const double* const val,
                               const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValAndSerr(vector<double> val,
                               vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    // DataArrayTerr1d
    virtual void SetValAndTerr(long ndata,
                               const double* const val,
                               const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValAndTerr(vector<double> val,
                               vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValAndTerr(long ndata,
                               const double* const val,
                               const double* const val_terr_plus,
                               const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetValAndTerr(vector<double> val,
                               vector<double> val_terr_plus,
                               vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};

    // Init & Set
    void InitSetVal(long ndata, const double* const val);
    void InitSetVal(vector<double> val);
    
    // DataArraySerr1d
    virtual void InitSetValAndSerr(long ndata,
                                   const double* const val,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void InitSetValAndSerr(vector<double> val,
                                   vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    // DataArrayTerr1d
    virtual void InitSetValAndTerr(long ndata,
                                   const double* const val,
                                   const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void InitSetValAndTerr(vector<double> val,
                                   vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void InitSetValAndTerr(long ndata,
                                   const double* const val,
                                   const double* const val_terr_plus,
                                   const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void InitSetValAndTerr(vector<double> val,
                                   vector<double> val_terr_plus,
                                   vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};

    // kinds of Set 
    void SetValElm(long idata, double val);
    virtual void SetValSerrElm(long idata, double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerrElm(long idata, double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerrPlusElm(long idata, double val_terr_plus)
        {MPrintErrVFunc; abort();};
    virtual void SetValTerrMinusElm(long idata, double val_terr_minus)
        {MPrintErrVFunc; abort();};
    
    virtual void Fill(long idata) = 0;
    // add an event on the idata-bin of the data
    virtual void Fill(long idata, double weight) = 0;
    // add weight events on the idata-bin of the data
    virtual void FillByMax(long idata, double val) = 0;
    virtual void FillByMax(long idata,
                           double val,
                           double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMax(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void FillByMin(long idata, double val) = 0;
    virtual void FillByMin(long idata,
                           double val,
                           double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMin(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void SetZero() = 0;
    virtual void SetOne() = 0;
    virtual void SetConst(double constant) = 0;

    virtual void SetValErrByPoissonErr()
        {MPrintErrVFunc; abort();};
    
    // kinds of InitSet
    void Copy(const DataArray1d* const org);
    virtual void Load(string file) = 0;
    static void ReadInfo(string file, int* flag_val_sorted_ptr);

//    // operation
//    virtual void Sort() = 0;
//    void Not(const DataArray1d* const data_array);
//    virtual void Scale(const DataArray1d* const data_array,
//                       double scale, double offset) = 0;
//    virtual void Min(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2) = 0;
//    virtual void Min(const DataArrayNerr1d* const* const data_array_arr,
//                     int ndata_array);
//    virtual void Min(const DataArraySerr1d* const* const data_array_arr,
//                     int ndata_array);
//    virtual void Min(const DataArrayTerr1d* const* const data_array_arr,
//                     int ndata_array);
//
//    virtual void Max(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2) = 0;
//    virtual void Max(const DataArrayNerr1d* const* const data_array_arr,
//                     int ndata_array);
//    virtual void Max(const DataArraySerr1d* const* const data_array_arr,
//                     int ndata_array) = 0;
//    virtual void Max(const DataArrayTerr1d* const* const data_array_arr,
//                     int ndata_array) = 0;
//
//    virtual void Add(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2) = 0;
//    virtual void Add(const DataArrayNerr1d* const* const data_array_arr,
//                     int ndata_array) = 0;
//    virtual void Add(const DataArraySerr1d* const* const data_array_arr,
//                     int ndata_array) = 0;
//
//    virtual void Sub(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2) = 0;
//    virtual void Mul(const DataArray1d* const data_array1,
//                     const DataArray1d* const data_array2) = 0;
//    virtual int  Div(const DataArray1d* const data_array_num,
//                     const DataArray1d* const data_array_den,
//                     vector<long>* const index_bad_vec_ptr) = 0;
//    virtual void AMean(const DataArray1d* const data_array1,
//                       const DataArray1d* const data_array2) = 0;
//    virtual void AMean(const DataArrayNerr1d* const* const data_array_arr,
//                       int ndata_array);
//    virtual void AMean(const DataArraySerr1d* const* const data_array_arr,
//                       int ndata_array);
//    virtual long WMean(const DataArraySerr1d* const data_array1,
//                       const DataArraySerr1d* const data_array2,
//                       vector<long>* const index_bad_vec_ptr);
//    virtual long WMean(const DataArraySerr1d* const* const data_array_arr,
//                       int ndata_array,
//                       vector<long>* const index_bad_vec_ptr);
//
//    // sub_add_ratio = (h1 - h2) / (h1 + h2)
//    virtual void SubAddRatio(const DataArray1d* const data_array1,
//                             const DataArray1d* const data_array2) = 0;
//
//    virtual void Variance(const DataArray1d* const* const data_array_arr,
//                          int ndata_array) = 0;
//    virtual void Stddev(const DataArray1d* const* const data_array_arr,
//                        int ndata_array) = 0;
//    virtual void UnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                                  int ndata_array) = 0;
//    virtual void SqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
//                                        int ndata_array) = 0;
//    virtual void RMS(const DataArray1d* const* const data_array_arr,
//                     int ndata_array) = 0;
//    virtual void Median(const DataArray1d* const* const data_array_arr,
//                        int ndata_array) = 0;
//
//    virtual void AddWithMask(const DataArray1d* const* const data_array_arr,
//                             const DataArrayNerr1d* const* const mask_array_arr,
//                             int ndata_array) = 0;
//    virtual void AddWithMask(const DataArraySerr1d* const* const data_array_arr,
//                             const DataArrayNerr1d* const* const mask_array_arr,
//                             int ndata_array);
//    virtual void AMeanWithMask(const DataArray1d* const* const data_array_arr,
//                               const DataArrayNerr1d* const* const mask_array_arr,
//                               int ndata_array,
//                               DataArrayNerr1d* const nvalid_array_out) = 0;
//    virtual long WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
//                               const DataArray1d* const* const mask_array_arr,
//                               int ndata_array,
//                               vector<long>* const index_bad_vec_ptr,
//                               DataArraySerr1d* const nvalid_array_out) = 0;

    //
    // const functions
    //

    // get
    long GetNdata() const {return ndata_;};
    const double* const GetVal() const {return val_;};
    double GetValElm(long idata) const;
    int GetFlagValSorted() const {return flag_val_sorted_;};
    
    virtual const double* const GetValSerr() const
        {MPrintErrVFunc; abort(); return NULL;};
    virtual const double* const GetValTerrPlus() const
        {MPrintErrVFunc; abort(); return NULL;};
    virtual const double* const GetValTerrMinus() const
        {MPrintErrVFunc; abort(); return NULL;};
    virtual double GetValSerrElm(long idata) const
        {MPrintErrVFunc; abort(); return 0;};
    virtual double GetValTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort(); return 0;};
    virtual double GetValTerrMinusElm(long idata) const
        {MPrintErrVFunc; abort(); return 0;};

    // terr --> serr by average
    virtual double* const GenValSerr() const
        {MPrintErrVFunc; abort(); return NULL;};

    // statistic
    double GetValMin() const;
    double GetValMax() const;
    long GetLocValMin() const;
    long GetLocValMax() const;

    double GetSum() const;
    virtual void GetSum(double* const add_ptr,
                        double* const add_err_ptr) const
        {MPrintErrVFunc; abort();};

    double GetAMean() const;
    double GetVariance() const;
    double GetStddev() const;
    double GetUnbiasedVariance() const;
    double GetSqrtOfUnbiasedVariance() const;
    double GetRMS() const;
    //    double GetMedian() const;

    virtual long GetWMean(double* const wmean_ptr,
                          double* const wmean_err_ptr,
                          vector<long>* const index_bad_vec_ptr) const
        {MPrintErrVFunc; abort(); return 0;};
    virtual double GetAMeanOfSerr() const
        {MPrintErrVFunc; abort(); return 0;};
    virtual long GetChi2byConst(double* const chi2_ptr,
                                int* const dof_ptr,
                                double* const chi2_red_ptr,
                                double* const prob_ptr) const
        {MPrintErrVFunc; abort(); return 0;};
    // virtual void GetStat1dim(Stat1dim* const stat_1dim_out) const {};

    // for qdp
    // min of val - val_serr
    // max of val + val_serr
    virtual double GetValAndErrMin() const
        {MPrintErrVFunc; abort(); return 0;};
    virtual double GetValAndErrMax() const
        {MPrintErrVFunc; abort(); return 0;};
    void GetRangeIndexQdp(double* const lo_ptr,
                          double* const up_ptr) const;
    virtual void GetRangeValQdp(double* const lo_ptr,
                                double* const up_ptr) const = 0;

    // output
    // mode: 0, 1, 2
    //    0: data
    //    1: index data
    //    2: data   1.0
    void Save(string outfile, int mode, double offset_val) const;
    void SaveData(string outfile, int mode, double offset_val) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, int mode,
                           double offset_val) const = 0;

    // Is functions
    int IsAllOne() const;

    // offset_tag = "st", "md", "ed", "no", value
    double GetOffsetIndexFromTag(string offset_tag) const;
    virtual double GetOffsetValFromTag(string offset_tag) const = 0;

protected:
    void NullDataArray1d();
    void InitDataArray1d(long ndata);
    int IsValNotNull() const;
    int IsValSerrPlus(double val_serr) const;
    int IsValidRange(long idata) const;
    
private:
    long ndata_;
    double* val_;
    int flag_val_sorted_; // -1: not sorted, 0: not checked, 1: sorted
};

#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_H_
