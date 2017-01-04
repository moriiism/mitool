#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    //    DataArray1d(string class_name, string title)
//    {
//        DataArray1d* da1d = new DataArray1d;
//        // ---> cannot allocate
//    }
//    {
//        DataArray1d* da1d = new DataArray1d("aaaa", "jjjj");
//        // ---> cannot allocate
//    }
//    virtual ~DataArray1d() {}

    
    {
        printf("--- test DataArray1d(string class_name, string title)\n");
        DataArrayNerr1d* da1d = new DataArrayNerr1d;
        printf("%s\n", da1d->GetClassName().c_str());
        printf("%s\n", da1d->GetTitle().c_str());
        delete da1d;
        printf("=== \n");
    }
    {
        printf("--- test DataArray1d(string class_name, string title)\n");        
        DataArrayNerr1d* da1d = new DataArrayNerr1d("jjjj");
        printf("%s\n", da1d->GetClassName().c_str());
        printf("%s\n", da1d->GetTitle().c_str());
        delete da1d;
        printf("=== \n");
    }

    //    virtual void Init(long ndata) = 0;
    {
        printf("--- test Init(long ndata)\n");        
        DataArrayNerr1d* da1d = new DataArrayNerr1d("jjjj");
        da1d->Init(2);
        da1d->PrintInfo(stdout);
        da1d->PrintData(stdout, 1, 0.0);
        delete da1d;
        printf("=== \n");
    }
//    void Set(const DataArray1d* const org);
    {
        printf("--- test Set(const DataArray1d* const org)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(2);
        da1d_1->SetValElm(0, 5);
        da1d_1->SetValElm(1, 10);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        DataArrayNerr1d* da1d_2 = new DataArrayNerr1d("da1d_2");
        da1d_2->Init(2);
        da1d_2->Set(da1d_1);
        delete da1d_1;
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);
        delete da1d_2;
        printf("=== \n");
    }
    
//    void SetVal(long ndata, const double* const val);
    {
        printf("--- test SetVal(long ndata, const double* const val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(2);
        double* in_arr = new double [2];
        in_arr[0] = 3;
        in_arr[1] = 5;
        da1d_1->SetVal(2, in_arr);
        delete [] in_arr;
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void SetVal(vector<double> val);
    {
        printf("--- test SetVal(vector<double> val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(2);
        vector<double> in_vec(2);
        in_vec[0] = 1;
        in_vec[1] = 5;
        da1d_1->SetVal(in_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

    

//    void SetFlagValSorted(int flag_val_sorted)
//    virtual void SetValSerr(long ndata,
//                            const double* const val_serr)
//    virtual void SetValSerr(vector<double> val_serr)
//    virtual void SetValTerr(long ndata,
//                            const double* const val_serr)
//    virtual void SetValTerr(vector<double> val_serr)
//    virtual void SetValTerr(long ndata,
//                            const double* const val_terr_plus,
//                            const double* const val_terr_minus)
//    virtual void SetValTerr(vector<double> val_terr_plus,
//                            vector<double> val_terr_minus)
//    virtual void SetValAndSerr(long ndata,
//                               const double* const val,
//                               const double* const val_serr)
//    virtual void SetValAndSerr(vector<double> val,
//                               vector<double> val_serr)
//    virtual void SetValAndTerr(long ndata,
//                               const double* const val,
//                               const double* const val_serr)
//    virtual void SetValAndTerr(vector<double> val,
//                               vector<double> val_serr)
//    virtual void SetValAndTerr(long ndata,
//                               const double* const val,
//                               const double* const val_terr_plus,
//                               const double* const val_terr_minus)
//    virtual void SetValAndTerr(vector<double> val,
//                               vector<double> val_terr_plus,
//                               vector<double> val_terr_minus)
//    void InitSetVal(long ndata, const double* const val);
//    void InitSetVal(vector<double> val);
//    virtual void InitSetValAndSerr(long ndata,
//                                   const double* const val,
//                                   const double* const val_serr)
//    virtual void InitSetValAndSerr(vector<double> val,
//                                   vector<double> val_serr)
//    virtual void InitSetValAndTerr(long ndata,
//                                   const double* const val,
//                                   const double* const val_serr)
//    virtual void InitSetValAndTerr(vector<double> val,
//                                   vector<double> val_serr)
//    virtual void InitSetValAndTerr(long ndata,
//                                   const double* const val,
//                                   const double* const val_terr_plus,
//                                   const double* const val_terr_minus)
//    virtual void InitSetValAndTerr(vector<double> val,
//                                   vector<double> val_terr_plus,
//                                   vector<double> val_terr_minus)
//    void SetValElm(long idata, double val);
//    virtual void SetValSerrElm(long idata, double val_serr)
//    virtual void SetValTerrElm(long idata, double val_serr)
//    virtual void SetValTerrPlusElm(long idata, double val_terr_plus)
//    virtual void SetValTerrMinusElm(long idata, double val_terr_minus)
//    virtual void Fill(long idata) = 0;
//    virtual void Fill(long idata, double weight) = 0;
//    virtual void FillByMax(long idata, double val) = 0;
//    virtual void FillByMax(long idata,
//                           double val,
//                           double val_serr)
//    virtual void FillByMax(long idata,
//                           double val,
//                           double val_terr_plus,
//                           double val_terr_minus)
//    virtual void FillByMin(long idata, double val) = 0;
//    virtual void FillByMin(long idata,
//                           double val,
//                           double val_serr)
//    virtual void FillByMin(long idata,
//                           double val,
//                           double val_terr_plus,
//                           double val_terr_minus)
//    virtual void SetZero() = 0;
//    virtual void SetOne() = 0;
//    virtual void SetConst(double constant) = 0;
//    virtual void SetValErrByPoissonErr()
//    void Copy(const DataArray1d* const org);
//    virtual DataArray1d* const Clone() const = 0;
//    virtual void Load(string file) = 0;
//    static void ReadInfo(string file, int* flag_val_sorted_ptr);
////    virtual void Sort() = 0;
////    void Not(const DataArray1d* const data_array);
////    virtual void Scale(const DataArray1d* const data_array,
////                       double scale, double offset) = 0;
////    virtual void Min(const DataArray1d* const data_array1,
////                     const DataArray1d* const data_array2) = 0;
////    virtual void Min(const DataArrayNerr1d* const* const data_array_arr,
////                     int ndata_array);
////    virtual void Min(const DataArraySerr1d* const* const data_array_arr,
////                     int ndata_array);
////    virtual void Min(const DataArrayTerr1d* const* const data_array_arr,
////                     int ndata_array);
////    virtual void Max(const DataArray1d* const data_array1,
////                     const DataArray1d* const data_array2) = 0;
////    virtual void Max(const DataArrayNerr1d* const* const data_array_arr,
////                     int ndata_array);
////    virtual void Max(const DataArraySerr1d* const* const data_array_arr,
////                     int ndata_array) = 0;
////    virtual void Max(const DataArrayTerr1d* const* const data_array_arr,
////                     int ndata_array) = 0;
////    virtual void Add(const DataArray1d* const data_array1,
////                     const DataArray1d* const data_array2) = 0;
////    virtual void Add(const DataArrayNerr1d* const* const data_array_arr,
////                     int ndata_array) = 0;
////    virtual void Add(const DataArraySerr1d* const* const data_array_arr,
////                     int ndata_array) = 0;
////    virtual void Sub(const DataArray1d* const data_array1,
////                     const DataArray1d* const data_array2) = 0;
////    virtual void Mul(const DataArray1d* const data_array1,
////                     const DataArray1d* const data_array2) = 0;
////    virtual int  Div(const DataArray1d* const data_array_num,
////                     const DataArray1d* const data_array_den,
////                     vector<long>* const index_bad_vec_ptr) = 0;
////    virtual void AMean(const DataArray1d* const data_array1,
////                       const DataArray1d* const data_array2) = 0;
////    virtual void AMean(const DataArrayNerr1d* const* const data_array_arr,
////                       int ndata_array);
////    virtual void AMean(const DataArraySerr1d* const* const data_array_arr,
////                       int ndata_array);
////    virtual long WMean(const DataArraySerr1d* const data_array1,
////                       const DataArraySerr1d* const data_array2,
////                       vector<long>* const index_bad_vec_ptr);
////    virtual long WMean(const DataArraySerr1d* const* const data_array_arr,
////                       int ndata_array,
////                       vector<long>* const index_bad_vec_ptr);
////    virtual void SubAddRatio(const DataArray1d* const data_array1,
////                             const DataArray1d* const data_array2) = 0;
////    virtual void Variance(const DataArray1d* const* const data_array_arr,
////                          int ndata_array) = 0;
////    virtual void Stddev(const DataArray1d* const* const data_array_arr,
////                        int ndata_array) = 0;
////    virtual void UnbiasedVariance(const DataArray1d* const* const data_array_arr,
////                                  int ndata_array) = 0;
////    virtual void SqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
////                                        int ndata_array) = 0;
////    virtual void RMS(const DataArray1d* const* const data_array_arr,
////                     int ndata_array) = 0;
////    virtual void Median(const DataArray1d* const* const data_array_arr,
////                        int ndata_array) = 0;
////    virtual void AddWithMask(const DataArray1d* const* const data_array_arr,
////                             const DataArrayNerr1d* const* const mask_array_arr,
////                             int ndata_array) = 0;
////    virtual void AddWithMask(const DataArraySerr1d* const* const data_array_arr,
////                             const DataArrayNerr1d* const* const mask_array_arr,
////                             int ndata_array);
////    virtual void AMeanWithMask(const DataArray1d* const* const data_array_arr,
////                               const DataArrayNerr1d* const* const mask_array_arr,
////                               int ndata_array,
////                               DataArrayNerr1d* const nvalid_array_out) = 0;
////    virtual long WMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
////                               const DataArray1d* const* const mask_array_arr,
////                               int ndata_array,
////                               vector<long>* const index_bad_vec_ptr,
////                               DataArraySerr1d* const nvalid_array_out) = 0;
//
//    long GetNdata() const {return ndata_;};
//    const double* const GetVal() const {return val_;};
//    double GetValElm(long idata) const;
//    int GetFlagValSorted() const {return flag_val_sorted_;};
//    virtual const double* const GetValSerr() const
//    virtual const double* const GetValTerrPlus() const
//    virtual const double* const GetValTerrMinus() const
//    virtual double GetValSerrElm(long idata) const
//    virtual double GetValTerrPlusElm(long idata) const
//    virtual double GetValTerrMinusElm(long idata) const
//    virtual double* const GenValSerr() const
//    double GetValMin() const;
//    double GetValMax() const;
//    long GetLocValMin() const;
//    long GetLocValMax() const;
//    double GetSum() const;
//    virtual void GetSum(double* const add_ptr,
//                        double* const add_err_ptr) const
//    double GetAMean() const;
//    double GetVariance() const;
//    double GetStddev() const;
//    double GetUnbiasedVariance() const;
//    double GetSqrtOfUnbiasedVariance() const;
//    double GetRMS() const;
//    double GetMedian() const;
//    virtual long GetWMean(double* const wmean_ptr,
//                          double* const wmean_err_ptr,
//                          vector<long>* const index_bad_vec_ptr) const
//    virtual double GetAMeanOfSerr() const
//    virtual long GetChi2byConst(double* const chi2_ptr,
//                                int* const dof_ptr,
//                                double* const chi2_red_ptr,
//                                double* const prob_ptr) const
//    // virtual void GetStat1dim(Stat1dim* const stat_1dim_out) const {};
//    virtual double GetValAndErrMin() const
//    virtual double GetValAndErrMax() const
//    void GetRangeIndexQdp(double* const lo_ptr,
//                          double* const up_ptr) const;
//    virtual void GetRangeValQdp(double* const lo_ptr,
//                                double* const up_ptr) const = 0;
//    void Save(string outfile, int mode, double offset_val) const;
//    void SaveData(string outfile, int mode, double offset_val) const;
//    void PrintInfo(FILE* fp) const;
//    virtual void PrintData(FILE* fp, int mode,
//                           double offset_val) const = 0;
//    int IsAllOne() const;
//    double GetOffsetIndexFromTag(string offset_tag) const;
//    virtual double GetOffsetValFromTag(string offset_tag) const = 0;
//    void NullDataArray1d();
//    void InitDataArray1d(long ndata);
//    int IsValNotNull() const;
//    int IsValSerrPlus(double val_serr) const;
//    int IsValidRange(long idata) const;

   
    return status_prog;
}
