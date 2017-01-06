#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"

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
    {
        printf("--- test SetFlagValSorted(int flag_val_sorted)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(2);
        vector<double> in_vec(2);
        in_vec[0] = 1;
        in_vec[1] = 5;
        da1d_1->SetVal(in_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        da1d_1->SetFlagValSorted(1);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);        

        delete da1d_1;
        printf("=== \n");
    }
    
////    virtual void SetValSerr(long ndata,
////                            const double* const val_serr)
//    {
//        printf("--- test SetValSerr()\n");
//        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
//        da1d_1->Init(2);
//        da1d_1->Init(2);
//        da1d_1->SetValElm(0, 5);
//        da1d_1->SetValElm(1, 10);
//
//        double* val_serr = new double [2];
//        val_serr[0] = 0.1;
//        val_serr[1] = 0.2;
//        da1d_1->SetValSerr(2, val_serr);
//        // ---> abort
//        
//        da1d_1->PrintInfo(stdout);
//        da1d_1->PrintData(stdout, 1, 0.0);        
//
//        delete da1d_1;
//        delete [] val_serr;
//        
//        printf("=== \n");
//    }

//    virtual void SetValSerr(long ndata,
//                            const double* const val_serr)
    {
        printf("--- test SetValSerr()\n");
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        da1d_1->Init(2);
        da1d_1->Init(2);
        da1d_1->SetValElm(0, 5);
        da1d_1->SetValElm(1, 10);

        double* val_serr = new double [2];
        val_serr[0] = 0.1;
        val_serr[1] = 0.2;
        da1d_1->SetValSerr(2, val_serr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        delete [] val_serr;
        
        printf("=== \n");
    }
    
//    void InitSetVal(long ndata, const double* const val);
    {
        printf("--- test InitSetVal(long ndata, const double* const val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        double* val_arr = new double [ndata];
        val_arr[0] = 5.0;
        val_arr[1] = 6.0;
        da1d_1->InitSetVal(ndata, val_arr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        delete [] val_arr;
        
        printf("=== \n");
    }

//    void InitSetVal(vector<double> val);
    {
        printf("--- test InitSetVal(vector<double> val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->InitSetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

//    void SetValElm(long idata, double val);
    {
        printf("--- test SetValElm(long idata, double val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetValElm(1, 24.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

//    virtual void Fill(long idata) = 0;
    {
        printf("--- test Fill(long idata)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Fill(0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }
   
//    virtual void Fill(long idata, double weight) = 0;
    {
        printf("--- test Fill(long idata, double weight)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Fill(0, 2.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

    
//    virtual void FillByMax(long idata, double val) = 0;
    {
        printf("--- test FillByMax(long idata, double val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->FillByMax(0, 2.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->FillByMax(0, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }


//    virtual void FillByMin(long idata, double val) = 0;
    {
        printf("--- test FillByMin(long idata, double val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->FillByMin(0, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        da1d_1->FillByMin(0, 2.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }

//    virtual void SetZero() = 0;
    {
        printf("--- test SetZero()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetZero();
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }
   
//    virtual void SetOne() = 0;
    {
        printf("--- test SetOne()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetOne();
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    virtual void SetConst(double constant) = 0;
    {
        printf("--- test SetConst(double constant)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetConst(3.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }

////    virtual void SetValErrByPoissonErr()
//    {
//        printf("--- test SetValErrByPoissonErr()\n");
//        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
//        int ndata = 2;
//        da1d_1->Init(ndata);
//        vector<double> val_vec(ndata);
//        val_vec[0] = 5.0;
//        val_vec[1] = 6.0;
//        da1d_1->SetVal(val_vec);
//        da1d_1->PrintInfo(stdout);
//        da1d_1->PrintData(stdout, 1, 0.0);
//
//        da1d_1->SetValErrByPoissonErr();
//        // ---> abort()
//        
//        da1d_1->PrintInfo(stdout);
//        da1d_1->PrintData(stdout, 1, 0.0);
//        
//        delete da1d_1;
//        
//        printf("=== \n");
//    }


//    virtual void SetValErrByPoissonErr()
    {
        printf("--- test SetValErrByPoissonErr()\n");
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetValErrByPoissonErr();
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }

//    virtual void SetValErrByPoissonErr()
    {
        printf("--- test SetValErrByPoissonErr()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->SetValErrByPoissonErr();
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        
        printf("=== \n");
    }

//    void Copy(const DataArray1d* const org);
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_1->SetValAndSerr(val_vec, val_vec_serr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_2 = new DataArrayNerr1d("da1d_2");
        da1d_2->Copy(da1d_1);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        delete da1d_2;
        
        printf("=== \n");
    }

//    void Copy(const DataArray1d* const org);
    {
        printf("--- test Copy(const DataArray1d* const org)\n");
        DataArray1d* da1d_1 = new DataArraySerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_vec_serr(ndata);
        val_vec_serr[0] = 0.1;
        val_vec_serr[1] = 0.2;        
        da1d_1->SetValAndSerr(val_vec, val_vec_serr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        DataArraySerr1d* da1d_2 = new DataArraySerr1d("da1d_2");
        da1d_2->Copy(da1d_1);
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        delete da1d_2;
        
        printf("=== \n");
    }

    
    
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
