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

//    virtual void Load(string file) = 0;
    {
        printf("--- test Load(string file)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Load("data/test_data1d_nerr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Load("data/test_data1d_serr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Load("data/test_data1d_terr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);                
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
    {
        printf("--- test Load(string file)\n");
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        da1d_1->Load("data/test_data1d_nerr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Load("data/test_data1d_serr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Load("data/test_data1d_terr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);                
        
        delete da1d_1;
        
        printf("=== \n");
    }

    {
        printf("--- test Load(string file)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        //   da1d_1->Load("data/test_data1d_nerr.dat");
        //da1d_1->PrintInfo(stdout);
        //da1d_1->PrintData(stdout, 1, 0.0);

        // da1d_1->Load("data/test_data1d_serr.dat");
        // da1d_1->PrintInfo(stdout);
        // da1d_1->PrintData(stdout, 1, 0.0);

        da1d_1->Load("data/test_data1d_terr.dat");
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);                
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
    
//    long GetNdata() const {return ndata_;};
    {
        printf("--- test GetNdata()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        printf("da1d_1->GetNdata() = %ld\n", da1d_1->GetNdata());
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    const double* const GetVal() const {return val_;};
    {
        printf("--- test GetVal()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        for(long idata = 0; idata < da1d_1->GetNdata(); idata ++){
            printf("%ld , %e\n", idata, da1d_1->GetVal()[idata]);
        }
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    double GetValElm(long idata) const;
    {
        printf("--- test GetValElm(long idata)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        for(long idata = 0; idata < da1d_1->GetNdata(); idata ++){
            printf("%ld , %e\n", idata, da1d_1->GetValElm(idata));
        }
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    int GetFlagValSorted() const {return flag_val_sorted_;};
    {
        printf("--- test GetFlagValSorted()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        printf("GetFlagValSorted() = %d\n", da1d_1->GetFlagValSorted());

        da1d_1->Sort();

        printf("GetFlagValSorted() = %d\n", da1d_1->GetFlagValSorted());        
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    double GetValMin() const;
    {
        printf("--- test GetValMin()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%e\n", da1d_1->GetValMin());
        
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    double GetValMax() const;
    {
        printf("--- test GetValMax()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%e\n", da1d_1->GetValMax());
        delete da1d_1;
        
        printf("=== \n");
    }
   
//    long GetLocValMin() const;
    {
        printf("--- test GetLocValMin()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%ld\n", da1d_1->GetLocValMin());
        delete da1d_1;
        
        printf("=== \n");
    }
   
//    long GetLocValMax() const;
    {
        printf("--- test GetLocValMax()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%ld\n", da1d_1->GetLocValMax());
        delete da1d_1;
        
        printf("=== \n");
    }
    
//    virtual double GetValAndErrMin() const = 0;
//    virtual double GetValAndErrMax() const = 0;            
    {
        printf("--- test GetValAndErrMin()\n");
        printf("--- test GetValAndErrMax()\n");        
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%e , %e\n", da1d_1->GetValAndErrMin(), da1d_1->GetValAndErrMax());
        delete da1d_1;
        
        printf("=== \n");
    }

    {
        printf("--- test GetValAndErrMin()\n");
        printf("--- test GetValAndErrMax()\n");        
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_serr_vec(ndata);
        val_serr_vec[0] = 0.5;
        val_serr_vec[1] = 0.6;
        da1d_1->SetVal(val_vec);
        da1d_1->SetValSerr(val_serr_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%e , %e\n", da1d_1->GetValAndErrMin(), da1d_1->GetValAndErrMax());
        delete da1d_1;
        
        printf("=== \n");
    }

    {
        printf("--- test GetValAndErrMin()\n");
        printf("--- test GetValAndErrMax()\n");        
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;

        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->PrintData(stdout, 1, 0.0);
        printf("%e , %e\n", da1d_1->GetValAndErrMin(), da1d_1->GetValAndErrMax());
        delete da1d_1;
        
        printf("=== \n");
    }

//    void Save(string outfile, int mode, double offset_val) const;
    {
        printf("--- test Save(string outfile, int mode, double offset_val)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->Save("temp.dat", 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }
    
//    void SaveData(string outfile, int mode, double offset_val) const;
    {
        printf("--- test SaveData(string outfile, int mode, double offset_val)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->SaveData("temp.dat", 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }
    
//    void PrintInfo(FILE* fp) const;
    {
        printf("--- test PrintInfo(FILE* fp)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->PrintInfo(stdout);

        delete da1d_1;
        
        printf("=== \n");
    }

//    virtual void PrintData(FILE* fp, int mode,
//                           double offset_val) const = 0;
    {
        printf("--- test PrintData\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        
        da1d_1->SetVal(val_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

    {
        printf("--- test PrintData\n");
        DataArraySerr1d* da1d_1 = new DataArraySerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_serr_vec(ndata);
        val_serr_vec[0] = 0.5;
        val_serr_vec[1] = 0.6;

        da1d_1->SetVal(val_vec);
        da1d_1->SetValSerr(val_serr_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

    {
        printf("--- test PrintData\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        
        printf("=== \n");
    }

//    int IsAllOne() const;
    {
        printf("--- test IsAllOne()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 1.0;
        val_vec[1] = 1.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        printf("%d\n", da1d_1->IsAllOne());

        delete da1d_1;
        
        printf("=== \n");
    }

//    double GetOffsetIndexFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetIndexFromTag(string offset_tag)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        printf("st = %e\n", da1d_1->GetOffsetIndexFromTag("st"));
        printf("md = %e\n", da1d_1->GetOffsetIndexFromTag("md"));
        printf("ed = %e\n", da1d_1->GetOffsetIndexFromTag("ed"));
        printf("no = %e\n", da1d_1->GetOffsetIndexFromTag("no"));
        printf("value = %e\n", da1d_1->GetOffsetIndexFromTag("777.0"));

        delete da1d_1;
        
        printf("=== \n");
    }
//    virtual double GetOffsetValFromTag(string offset_tag) const = 0;
    {
        printf("--- test GetOffsetValFromTag(string offset_tag)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        printf("st = %e\n", da1d_1->GetOffsetValFromTag("st"));
        printf("md = %e\n", da1d_1->GetOffsetValFromTag("md"));
        printf("ed = %e\n", da1d_1->GetOffsetValFromTag("ed"));
        printf("no = %e\n", da1d_1->GetOffsetValFromTag("no"));
        printf("value = %e\n", da1d_1->GetOffsetValFromTag("777.0"));

        delete da1d_1;
        
        printf("=== \n");
    }
    
//    static void ReadInfo(string file, int* flag_val_sorted_ptr);
    {
        printf("--- test ReadInfo(string file, int* flag_val_sorted_ptr)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        int ndata = 2;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        val_vec[0] = 5.0;
        val_vec[1] = 6.0;
        vector<double> val_terr_plus_vec(ndata);
        val_terr_plus_vec[0] = 0.5;
        val_terr_plus_vec[1] = 0.6;
        vector<double> val_terr_minus_vec(ndata);
        val_terr_minus_vec[0] = -1.5;
        val_terr_minus_vec[1] = -1.6;
        
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->Save("temp.dat", 1, 0.0);

        int flag_val_sorted = 3;
        DataArray1d::ReadInfo("temp.dat", &flag_val_sorted);
        printf("flag_val_sorted = %d\n", flag_val_sorted);
        
        

        delete da1d_1;
        
        printf("=== \n");
    }

    return status_prog;
}
