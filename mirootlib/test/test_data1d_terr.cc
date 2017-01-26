#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_terr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long ndata);
    {
        printf("--- test Init(long ndata)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void SetValTerr(long ndata,
//                    const double* const val_serr);
    {
        printf("--- test SetValTerr\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        double* val_arr = new double [ndata];
        double* val_err_arr = new double [ndata];
        val_arr[0] = 10.0;
        val_arr[1] = 20.0;
        val_arr[2] = 30.0;
        val_arr[3] = 40.0;
        val_err_arr[0] = 1.0;
        val_err_arr[1] = 2.0;
        val_err_arr[2] = 3.0;
        val_err_arr[3] = 4.0;
        da1d_1->SetVal(ndata, val_arr);
        da1d_1->SetValTerr(ndata, val_err_arr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        delete [] val_arr;
        delete [] val_err_arr;
        printf("=== \n");
    }

//    void SetValTerr(vector<double> val_serr);
    {
        printf("--- test SetValTerr\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        vector<double> val_err_vec(ndata);
        val_vec[0] = 10.0;
        val_vec[1] = 20.0;
        val_vec[2] = 30.0;
        val_vec[3] = 40.0;
        val_err_vec[0] = 1.0;
        val_err_vec[1] = 2.0;
        val_err_vec[2] = 3.0;
        val_err_vec[3] = 4.0;
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_err_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//  void SetValTerr(long ndata, 
//                    const double* const val_terr_plus,
//                    const double* const val_terr_minus);
    {
        printf("--- test SetValTerr\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        double* val_arr = new double [ndata];
        double* val_terr_plus_arr = new double [ndata];
        double* val_terr_minus_arr = new double [ndata];
        val_arr[0] = 10.0;
        val_arr[1] = 20.0;
        val_arr[2] = 30.0;
        val_arr[3] = 40.0;
        val_terr_plus_arr[0] = 1.0;
        val_terr_plus_arr[1] = 2.0;
        val_terr_plus_arr[2] = 3.0;
        val_terr_plus_arr[3] = 4.0;
        val_terr_minus_arr[0] = -1.0;
        val_terr_minus_arr[1] = -2.0;
        val_terr_minus_arr[2] = -3.0;
        val_terr_minus_arr[3] = -4.0;
        da1d_1->SetVal(ndata, val_arr);
        da1d_1->SetValTerr(ndata, val_terr_plus_arr, val_terr_minus_arr);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        delete [] val_arr;
        delete [] val_terr_plus_arr;
        delete [] val_terr_minus_arr;        
        printf("=== \n");
    }

//   void SetValTerr(vector<double> val_terr_plus,
//                    vector<double> val_terr_minus);
    {
        printf("--- test SetValTerr\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        vector<double> val_vec(ndata);
        vector<double> val_terr_plus_vec(ndata);
        vector<double> val_terr_minus_vec(ndata);
        val_vec[0] = 10.0;
        val_vec[1] = 20.0;
        val_vec[2] = 30.0;
        val_vec[3] = 40.0;
        val_terr_plus_vec[0] = 1.0;
        val_terr_plus_vec[1] = 2.0;
        val_terr_plus_vec[2] = 3.0;
        val_terr_plus_vec[3] = 4.0;
        val_terr_minus_vec[0] = -1.0;
        val_terr_minus_vec[1] = -2.0;
        val_terr_minus_vec[2] = -3.0;
        val_terr_minus_vec[3] = -4.0;
        da1d_1->SetVal(val_vec);
        da1d_1->SetValTerr(val_terr_plus_vec, val_terr_minus_vec);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void SetValTerrElm(long idata, double val_serr);
    {
        printf("--- test SetValTerrElm\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValTerrElm(1, 11111);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
//    void SetValTerrPlusElm(long idata, double val_terr_plus);
//    void SetValTerrMinusElm(long idata, double val_terr_minus);
    {
        printf("--- test SetValTerrPlusElm, SetValTerrMinusElm\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValTerrPlusElm(1, 11111);
        da1d_1->SetValTerrMinusElm(1, -111);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
  
//    void Fill(long idata);
    {
        printf("--- test Fill\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->Fill(2);
        da1d_1->Fill(2);
        da1d_1->Fill(2);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void Fill(long idata, double weight);
    {
        printf("--- test Fill\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->Fill(3, 5);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    void FillByLarger(long idata, double val);
    {
        printf("--- test FillByLarger\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->FillByLarger(1, 9.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//  void FillByLarger(long idata,
//                   double val,
//                   double val_serr);
    {
        printf("--- test FillByLarger\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->FillByLarger(1, 9.0, 7.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//  void FillByLarger(long idata,
//                   double val,
//                   double val_terr_plus,
//                   double val_terr_minus);
    {
        printf("--- test FillByLarger\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->FillByLarger(1, 9.0, 7.0, -4.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    void FillBySmaller(long idata, double val);
    {
        printf("--- test FillBySmaller\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetConst(3);
        da1d_1->FillBySmaller(1, 2.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//   void FillBySmaller(long idata,
//                   double val,
//                   double val_serr);
    {
        printf("--- test FillBySmaller\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetConst(3);
        da1d_1->FillBySmaller(1, 2.0, 0.8);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void FillBySmaller(long idata,
//                   double val,
//                   double val_terr_plus,
//                   double val_terr_minus);
    {
        printf("--- test FillBySmaller\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetConst(3);
        da1d_1->FillBySmaller(1, 2.0, 0.8, -0.5);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    void SetConst(double constant);
    {
        printf("--- test SetConst(double constant)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetConst(3);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    void SetValErrByPoissonErr();
    {
        printf("--- test SetValErrByPoissonErr()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        
        da1d_1->SetValErrByPoissonErr();
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    DataArraySerr1d* const Clone() const;
    {
        printf("--- test Clone()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);

        DataArrayTerr1d* da1d_2 = da1d_1->Clone();
        da1d_2->PrintInfo(stdout);
        da1d_2->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        delete da1d_2;        
        printf("=== \n");
    }
    
//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        da1d_1->Load("data/test_data1d_terr.dat");
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void Sort();
    {
        printf("--- test Sort()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 12);
        da1d_1->SetValElm(2, 11);
        da1d_1->SetValElm(3, 13);
        da1d_1->SetValTerrPlusElm(0, 0.1);
        da1d_1->SetValTerrPlusElm(1, 0.5);
        da1d_1->SetValTerrPlusElm(2, 0.3);
        da1d_1->SetValTerrPlusElm(3, 0.6);
        da1d_1->SetValTerrMinusElm(0, -1.0);
        da1d_1->SetValTerrMinusElm(1, -5.0);
        da1d_1->SetValTerrMinusElm(2, -3.0);
        da1d_1->SetValTerrMinusElm(3, -6.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        da1d_1->Sort();
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

// const double* const GetValTerrPlus() const {return val_terr_plus_;};
// const double* const GetValTerrMinus() const {return val_terr_minus_;};
    {
        printf("--- test GetValTerrPlus()\n");
        printf("--- test GetValTerrMinus()\n");        
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->SetValErrByPoissonErr();
        for(long idata = 0; idata < ndata; idata ++){
            printf("%e\n", da1d_1->GetValTerrPlus()[idata]);
            printf("%e\n", da1d_1->GetValTerrMinus()[idata]);
        }
        delete da1d_1;
        printf("=== \n");
    }
    
//    double GetValSerrElm(long idata) const;
//    double GetValTerrPlusElm(long idata) const;
//    double GetValTerrMinusElm(long idata) const;
//    double* const GenValSerr() const;

    {
        printf("--- test GetValSerrElm()\n");
        printf("--- test GetValTerrPlusElm()\n");
        printf("--- test GetValTerrMinusElm()\n");
        printf("--- test GenValSerr()\n");        
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->SetValTerrPlusElm(0, 1.0);
        da1d_1->SetValTerrPlusElm(1, 1.0);
        da1d_1->SetValTerrPlusElm(2, 1.0);
        da1d_1->SetValTerrPlusElm(3, 1.0);
        da1d_1->SetValTerrMinusElm(0, -3.0);
        da1d_1->SetValTerrMinusElm(1, -3.0);
        da1d_1->SetValTerrMinusElm(2, -3.0);
        da1d_1->SetValTerrMinusElm(3, -3.0);        
        for(long idata = 0; idata < ndata; idata ++){
            printf("serr %e, terr %e, %e\n",
                   da1d_1->GetValSerrElm(idata),
                   da1d_1->GetValTerrPlusElm(idata),
                   da1d_1->GetValTerrMinusElm(idata));
        }
        double* val_serr = da1d_1->GenValSerr();
        for(long idata = 0; idata < ndata; idata ++){
            printf("val_serr = %e\n", val_serr[idata]);
        }
        
        delete da1d_1;
        delete [] val_serr;
        printf("=== \n");
    }
    
    
//    double GetValAndErrMin() const;
//    double GetValAndErrMax() const;
    {
        printf("--- test GetValAndErrMin(), GetValAndErrMax()\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->SetValErrByPoissonErr();
        printf("%e\n", da1d_1->GetValAndErrMin());
        printf("%e\n", da1d_1->GetValAndErrMax());        
        delete da1d_1;
        // 2.76393202250021
        // 7.23606797749979
        printf("=== \n");
    }
    
//    void PrintData(FILE* fp, int mode,
//                   double offset_val) const;
    {
        printf("--- test PrintData\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        long ndata = 4;
        da1d_1->Init(ndata);
        da1d_1->SetValElm(0, 5.0);
        da1d_1->SetValElm(1, 5.0);
        da1d_1->SetValElm(2, 5.0);
        da1d_1->SetValElm(3, 5.0);
        da1d_1->SetValErrByPoissonErr();
        da1d_1->PrintData(stdout, 0, 0.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        da1d_1->PrintData(stdout, 2, 0.0);        
        delete da1d_1;
        printf("=== \n");
    }
    
//    double GetOffsetValFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetValFromTag(string offset_tag)\n");
        DataArrayTerr1d* da1d_1 = new DataArrayTerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 11);
        da1d_1->SetValElm(2, 12);
        da1d_1->SetValElm(3, 13);
        da1d_1->SetValErrByPoissonErr();
        double val_st = da1d_1->GetOffsetValFromTag("st");
        printf("val_st = %e\n", val_st);

        double val_md = da1d_1->GetOffsetValFromTag("md");
        printf("val_md = %e\n", val_md);        

        double val_ed = da1d_1->GetOffsetValFromTag("ed");
        printf("val_ed = %e\n", val_ed);

        double val_no = da1d_1->GetOffsetValFromTag("no");
        printf("val_no = %e\n", val_no);

        double val_val = da1d_1->GetOffsetValFromTag("777.0");
        printf("val_val = %e\n", val_val);                        
        
        delete da1d_1;
        printf("=== \n");
    }

    return status_prog;
}
