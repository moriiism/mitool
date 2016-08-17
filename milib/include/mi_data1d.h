#ifndef MITOOL_MILIB_DATA1D_H_
#define MITOOL_MILIB_DATA1D_H_

#include "mi_math.h"
#include "mi_stat1d.h"
#include "mi_interval.h"

class DataArrayNerr1d;
class DataArraySerr1d;
class DataArrayTerr1d;

class DataArray1d : public MiObject{
public:
    explicit DataArray1d(string title = "") :
        MiObject("DataArray1d", title) {}
    DataArray1d(string class_name, string title) :
        MiObject(class_name, title) {}
    virtual ~DataArray1d() {}

    // Init
    virtual void Init(long ndata) = 0;

    // Set
    virtual void Set(const DataArray1d* const org) = 0;

    // Set each
    // DataArrayNerr1d
    virtual void SetVal(long ndata, const double* const val) = 0;
    virtual void SetVal(vector<double> val) = 0;
    virtual void SetFlagValSorted(int flag_val_sorted) = 0;
    virtual void SetNumUnder(long num_under) = 0;
    virtual void SetNumOver(long num_over) = 0;

    // DataArraySerr1d
    virtual void SetValSerr(long ndata,
                            const double* const val_serr) = 0;
    virtual void SetValSerr(vector<double> val_serr) = 0;

    // DataArrayTerr1d
    virtual void SetValTerr(long ndata,
                            const double* const val_serr) = 0;

    virtual void SetValTerr(vector<double> val_serr) = 0;
    virtual void SetValTerr(long ndata,
                            const double* const val_terr_plus,
                            const double* const val_terr_minus) = 0;
    virtual void SetValTerr(vector<double> val_terr_plus,
                            vector<double> val_terr_minus) = 0;
  
    // DataArraySerr1d
    virtual void SetValAndSerr(long ndata,
                               const double* const val,
                               const double* const val_serr) = 0;
    virtual void SetValAndSerr(vector<double> val,
                               vector<double> val_serr) = 0;
    // DataArrayTerr1d
    virtual void SetValAndTerr(long ndata,
                               const double* const val,
                               const double* const val_serr) = 0;
    virtual void SetValAndTerr(vector<double> val,
                               vector<double> val_serr) = 0;
    virtual void SetValAndTerr(long ndata,
                               const double* const val,
                               const double* const val_terr_plus,
                               const double* const val_terr_minus) = 0;
    virtual void SetValAndTerr(vector<double> val,
                               vector<double> val_terr_plus,
                               vector<double> val_terr_minus) = 0;

    // Init & Set
    virtual void InitSetVal(long ndata, const double* const val) = 0;
    virtual void InitSetVal(vector<double> val) = 0;

    // DataArraySerr1d
    virtual void InitSetValAndSerr(long ndata,
                                   const double* const val,
                                   const double* const val_serr) = 0;
    virtual void InitSetValAndSerr(vector<double> val,
                                   vector<double> val_serr) = 0;
    // DataArrayTerr1d
    virtual void InitSetValAndTerr(long ndata,
                                   const double* const val,
                                   const double* const val_serr) = 0;
    virtual void InitSetValAndTerr(vector<double> val,
                                   vector<double> val_serr) = 0;
    virtual void InitSetValAndTerr(long ndata,
                                   const double* const val,
                                   const double* const val_terr_plus,
                                   const double* const val_terr_minus) = 0;
    virtual void InitSetValAndTerr(vector<double> val,
                                   vector<double> val_terr_plus,
                                   vector<double> val_terr_minus) = 0;

    // kinds of Set 
    virtual void SetValElm(long idata, double val) = 0;
    virtual void SetValSerrElm(long idata, double val_serr) = 0;
    virtual void SetValTerrElm(long idata, double val_serr) = 0;
    virtual void SetValTerrPlusElm(long idata, double val_terr_plus) = 0;
    virtual void SetValTerrMinusElm(long idata, double val_terr_minus) = 0;
    
    virtual void Fill(long idata) = 0;
    // add an event on the idata-bin of the data
    virtual void Fill(long idata, double weight) = 0;
    // add weight events on the idata-bin of the data
    virtual void FillByMax(long idata, double val) = 0;
    virtual void FillByMax(long idata,
                           double val,
                           double val_serr) = 0;
    virtual void FillByMax(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus) = 0;
    virtual void FillByMin(long idata, double val) = 0;
    virtual void FillByMin(long idata,
                           double val,
                           double val_serr) = 0;
    virtual void FillByMin(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus) = 0;

    virtual void SetZero() = 0;
    virtual void SetOne() = 0;
    virtual void SetConst(double constant) = 0;

    virtual void SetValErrByPoissonErr() = 0;
    
    // kinds of InitSet
    virtual void Copy(const DataArray1d* const org) = 0;
    virtual DataArray1d* const Clone() const = 0;
    virtual void Load(string file) = 0;
    static DataArray1d* const GenDa1dByLoad(string file, string format);
    static void ReadInfo(string file, int* flag_val_sorted_ptr);

    // operation
    virtual void Sort() = 0;
    virtual void Not(const DataArray1d* const data_array) = 0;
    virtual void Scale(const DataArray1d* const data_array,
                       double scale, double offset) = 0;
    virtual void Min(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2) = 0;
    virtual void Min(const DataArray1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Min(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Min(const DataArrayTerr1d* const* const data_array_arr,
                     int ndata_array) = 0;
    
    virtual void Max(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2) = 0;
    virtual void Max(const DataArray1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Max(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Max(const DataArrayTerr1d* const* const data_array_arr,
                     int ndata_array) = 0;

    virtual void Add(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2) = 0;
    virtual void Add(const DataArray1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Add(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array) = 0;
    
    virtual void Sub(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2) = 0;
    virtual void Mul(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2) = 0;
    virtual int  Div(const DataArray1d* const data_array_num,
                     const DataArray1d* const data_array_den,
                     vector<long>* const index_bad_vec_ptr) = 0;
    virtual void AMean(const DataArray1d* const data_array1,
                       const DataArray1d* const data_array2) = 0;
    virtual void AMean(const DataArray1d* const* const data_array_arr,
                       int ndata_array) = 0;
    virtual void AMean(const DataArraySerr1d* const* const data_array_arr,
                       int ndata_array) = 0;
    virtual long WMean(const DataArraySerr1d* const data_array1,
                       const DataArraySerr1d* const data_array2,
                       vector<long>* const index_bad_vec_ptr) = 0;
    virtual long WMean(const DataArraySerr1d* const* const data_array_arr,
                       int ndata_array,
                       vector<long>* const index_bad_vec_ptr) = 0;

    // sub_add_ratio = (h1 - h2) / (h1 + h2)
    virtual void SubAddRatio(const DataArray1d* const data_array1,
                             const DataArray1d* const data_array2) = 0;

    virtual void Variance(const DataArray1d* const* const data_array_arr,
                          int ndata_array) = 0;
    virtual void Stddev(const DataArray1d* const* const data_array_arr,
                        int ndata_array) = 0;
    virtual void UnbiasedVariance(const DataArray1d* const* const data_array_arr,
                                  int ndata_array) = 0;
    virtual void SqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
                                        int ndata_array) = 0;
    virtual void RMS(const DataArray1d* const* const data_array_arr,
                     int ndata_array) = 0;
    virtual void Median(const DataArray1d* const* const data_array_arr,
                        int ndata_array) = 0;

    virtual void AddWithMask(const DataArray1d* const* const data_array_arr,
                             const DataArray1d* const* const mask_array_arr,
                             int ndata_array) = 0;
    virtual void AddWithMask(const DataArraySerr1d* const* const data_array_arr,
                             const DataArray1d* const* const mask_array_arr,
                             int ndata_array) = 0;
    virtual void AMeanWithMask(const DataArray1d* const* const data_array_arr,
                               const DataArray1d* const* const mask_array_arr,
                               int ndata_array,
                               DataArray1d* const nvalid_array_out) = 0;
    virtual long WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
                               const DataArray1d* const* const mask_array_arr,
                               int ndata_array,
                               vector<long>* const index_bad_vec_ptr,
                               DataArraySerr1d* const nvalid_array_out) = 0;
    //
    // const functions
    //
    
    // get
    long GetNdata() const {return ndata_;};
    const double* const GetVal() const {return val_;};
    double GetValElm(long idata) const;
    int GetFlagValSorted() const {return flag_val_sorted_;};
    long GetNumUnder() const {return num_under_;};
    long GetNumOver() const {return num_over_;};
    
    virtual const double* const GetValSerr() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetValTerrPlus() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetValTerrMinus() const
        {MPrintErrVFunc; abort();};
    virtual double GetValSerrElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetValTerrPlusElm(long idata) const
        {MPrintErrVFunc; abort();};
    virtual double GetValTerrMinusElm(long idata) const
        {MPrintErrVFunc; abort();};

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
    double GetMedian() const;

    virtual long GetWMean(double* const wmean_ptr,
                          double* const wmean_err_ptr,
                          vector<long>* const index_bad_vec_ptr) const
        {MPrintErrVFunc; abort();};
    virtual double GetAMeanOfSerr() const
        {MPrintErrVFunc; abort();};
    virtual long GetChi2byConst(double* const chi2_ptr,
                                int* const dof_ptr,
                                double* const chi2_red_ptr,
                                double* const prob_ptr) const
        {MPrintErrVFunc; abort();};
    virtual void GetStat1dim(Stat1dim* const stat_1dim_out) const
        {MPrintErrVFunc; abort();};

    // for qdp
    // min of val - val_serr
    // max of val + val_serr
    virtual double GetValAndErrMin() const
        {MPrintErrVFunc; abort();};
    virtual double GetValAndErrMax() const
        {MPrintErrVFunc; abort();};
    void GetRangeIndexQdp(double* const lo_ptr,
                          double* const up_ptr) const;
    virtual void GetRangeValQdp(double* const lo_ptr,
                                double* const up_ptr) const;

    // output
    // mode: 0, 1, 2
    void Save(string outfile, int mode, double offset_val) const;
    void SaveData(string outfile, int mode, double offset_val) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, int mode,
                           double offset_val) const;

    // Is functions
    int IsAllOne() const;

    // offset_tag = "st", "md", "ed", "no", value
    virtual double GetOffsetIndexFromTag(string offset_tag) const;
    virtual double GetOffsetValFromTag(string offset_tag) const;
  
private:
    virtual void Null() = 0;
    virtual int IsValidForSetVal(long idata) const = 0;
};


#endif // MITOOL_MILIB_DATA1D_H_
