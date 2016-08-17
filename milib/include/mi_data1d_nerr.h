#ifndef MITOOL_MILIB_DATA1D_NERR_H_
#define MITOOL_MILIB_DATA1D_NERR_H_

#include "mi_math.h"
#include "mi_stat1d.h"
#include "mi_interval.h"

class DataArraySerr1d;
class DataArrayTerr1d;

class DataArrayNerr1d : public DataArray1d{
public:
    explicit DataArrayNerr1d(string title = "") :
        MiObject("DataArrayNerr1d", title),
        ndata_(0),
        val_(NULL),
        flag_val_sorted_(0),
        num_under_(0),
        num_over_(0) {}
    DataArrayNerr1d(string class_name, string title) :
        MiObject(class_name, title),
        ndata_(0),
        val_(NULL),
        flag_val_sorted_(0),
        num_under_(0),
        num_over_(0) {}
    virtual ~DataArrayNerr1d() {
        NullDataArrayNerr1d();
    }

    // Init
    void Init(long ndata);

    // Set
    void Set(const DataArray1d* const org);

    // Set each
    void SetVal(long ndata, const double* const val);
    void SetVal(vector<double> val);
    void SetFlagValSorted(int flag_val_sorted)
        {flag_val_sorted_ = flag_val_sorted;};
    void SetNumUnder(long num_under)
        {num_under_ = num_under;};
    void SetNumOver(long num_over)
        {num_over_ = num_over;};    

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
    
    virtual void Fill(long idata);
    // add an event on the idata-bin of the data
    virtual void Fill(long idata, double weight);
    // add weight events on the idata-bin of the data
    virtual void FillByMax(long idata, double val);
    virtual void FillByMax(long idata,
                           double val,
                           double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMax(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus)
        {MPrintErrVFunc; abort();};
    
    virtual void FillByMin(long idata, double val);
    virtual void FillByMin(long idata,
                           double val,
                           double val_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMin(long idata,
                           double val,
                           double val_terr_plus,
                           double val_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void SetZero();
    virtual void SetOne();
    virtual void SetConst(double constant);

    virtual void SetValErrByPoissonErr()
        {MPrintErrVFunc; abort();};
    
    // kinds of InitSet
    void Copy(const DataArray1d* const org);
    virtual DataArray1d* const Clone() const;
    virtual void Load(string file);
    static DataArray1d* const GenDa1dByLoad(string file, string format);
    static void ReadInfo(string file, int* flag_val_sorted_ptr);

    // operation
    virtual void Sort();
    void Not(const DataArray1d* const data_array);
    virtual void Scale(const DataArray1d* const data_array,
                       double scale, double offset);
    virtual void Min(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    void Min(const DataArray1d* const* const data_array_arr,
             int ndata_array);
    virtual void Min(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array)
        {MPrintErrVFunc; abort();};    
    virtual void Min(const DataArrayTerr1d* const* const data_array_arr,
                     int ndata_array)
        {MPrintErrVFunc; abort();};
    
    virtual void Max(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    void Max(const DataArray1d* const* const data_array_arr,
             int ndata_array);
    virtual void Max(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array)
        {MPrintErrVFunc; abort();};
    virtual void Max(const DataArrayTerr1d* const* const data_array_arr,
                     int ndata_array)
        {MPrintErrVFunc; abort();};

    virtual void Add(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    void Add(const DataArray1d* const* const data_array_arr,
             int ndata_array);
    virtual void Add(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array)
        {MPrintErrVFunc; abort();};
    
    virtual void Sub(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    virtual void Mul(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    virtual int  Div(const DataArray1d* const data_array_num,
                     const DataArray1d* const data_array_den,
                     vector<long>* const index_bad_vec_ptr);
    virtual void AMean(const DataArray1d* const data_array1,
                       const DataArray1d* const data_array2);
    void AMean(const DataArray1d* const* const data_array_arr,
               int ndata_array);
    virtual void AMean(const DataArraySerr1d* const* const data_array_arr,
                       int ndata_array)
        {MPrintErrVFunc; abort();};
    
    virtual long WMean(const DataArraySerr1d* const data_array1,
                       const DataArraySerr1d* const data_array2,
                       vector<long>* const index_bad_vec_ptr)
        {MPrintErrVFunc; abort();};
    virtual long WMean(const DataArraySerr1d* const* const data_array_arr,
                       int ndata_array,
                       vector<long>* const index_bad_vec_ptr)
        {MPrintErrVFunc; abort();};

    // sub_add_ratio = (h1 - h2) / (h1 + h2)
    virtual void SubAddRatio(const DataArray1d* const data_array1,
                             const DataArray1d* const data_array2);

    virtual void Variance(const DataArray1d* const* const data_array_arr,
                          int ndata_array);
    virtual void Stddev(const DataArray1d* const* const data_array_arr,
                        int ndata_array);
    virtual void UnbiasedVariance(const DataArray1d* const* const data_array_arr,
                                  int ndata_array);
    virtual void SqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
                                        int ndata_array);
    virtual void RMS(const DataArray1d* const* const data_array_arr,
                     int ndata_array);
    virtual void Median(const DataArray1d* const* const data_array_arr,
                        int ndata_array);

    void AddWithMask(const DataArray1d* const* const data_array_arr,
                     const DataArray1d* const* const mask_array_arr,
                     int ndata_array);
    virtual void AddWithMask(const DataArraySerr1d* const* const data_array_arr,
                             const DataArray1d* const* const mask_array_arr,
                             int ndata_array)
        {MPrintErrVFunc; abort();};
    void AMeanWithMask(const DataArray1d* const* const data_array_arr,
                       const DataArray1d* const* const mask_array_arr,
                       int ndata_array,
                       DataArray1d* const nvalid_array_out);
    virtual long WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
                               const DataArray1d* const* const mask_array_arr,
                               int ndata_array,
                               vector<long>* const index_bad_vec_ptr,
                               DataArraySerr1d* const nvalid_array_out)
        {MPrintErrVFunc; abort();};

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
    double GetOffsetIndexFromTag(string offset_tag) const;
    virtual double GetOffsetValFromTag(string offset_tag) const;
  
protected:    
    void NullDataArray1d();
    void InitDataArray1d(long ndata);
    void SetByDataArray1d(const DataArray1d* const org);
    virtual void SetByDataArraySerr1d(const DataArraySerr1d* const org);
    virtual void SetByDataArrayTerr1d(const DataArrayTerr1d* const org);

    int IsValidRange(long idata) const;
    int IsValNotNull() const;
    
private:    
    long ndata_;
    double* val_;
    int flag_val_sorted_; // -1: not sorted, 0: not checked, 1: sorted
    long num_under_;
    long num_over_;

    virtual int IsValidForSetVal(long idata) const;
};


#endif // MITOOL_MILIB_DATA1D_NERR_H_

