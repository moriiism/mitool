#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_data1d_nerr.h"

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
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->PrintInfo(stdout);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void Fill(long idata);
    {
        printf("--- test Fill(long idata)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->Fill(1);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
   
//    void Fill(long idata, double weight);
    {
        printf("--- test Fill(long idata, double weight)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->Fill(1, 3.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    void FillByLarger(long idata, double val);
    {
        printf("--- test FillByLarger(long idata, double val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->FillByLarger(1, 3.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
   
//    void FillBySmaller(long idata, double val);
    {
        printf("--- test FillBySmaller(long idata, double val)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->FillBySmaller(1, 3.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    void SetConst(double constant);
    {
        printf("--- test SetConst(double constant)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetConst(4.0);
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }

//    DataArrayNerr1d* const Clone() const;
    {
        printf("--- test Clone()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetConst(4.0);
        da1d_1->PrintData(stdout, 1, 0.0);

        DataArrayNerr1d* da1d_2 = da1d_1->Clone();
        da1d_2->PrintData(stdout, 1, 0.0);
        
        delete da1d_1;
        delete da1d_2;
        printf("=== \n");
    }
    
//    void Load(string file);
    {
        printf("--- test Load(string file)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Load("data/test_data1d_nerr.dat");
        da1d_1->PrintData(stdout, 1, 0.0);

        delete da1d_1;
        printf("=== \n");
    }

//    void Sort();
    {
        printf("--- test Sort()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 12);
        da1d_1->SetValElm(2, 11);
        da1d_1->SetValElm(3, 13);
        da1d_1->PrintData(stdout, 1, 0.0);
        da1d_1->Sort();
        da1d_1->PrintData(stdout, 1, 0.0);
        delete da1d_1;
        printf("=== \n");
    }
    
//    double GetValAndErrMin() const;
//    double GetValAndErrMax() const;    
    {
        printf("--- test GetValAndErrMin()\n");
        printf("--- test GetValAndErrMax()\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 11);
        da1d_1->SetValElm(2, 12);
        da1d_1->SetValElm(3, 13);        
        double val_min = da1d_1->GetValAndErrMin();
        printf("val_min = %e\n", val_min);
        double val_max = da1d_1->GetValAndErrMax();
        printf("val_max = %e\n", val_max);
        delete da1d_1;
        printf("=== \n");
    }

//    void PrintData(FILE* fp, int mode,
//                   double offset_val) const;
    {
        printf("--- test PrintData\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 11);
        da1d_1->SetValElm(2, 12);
        da1d_1->SetValElm(3, 13);

        da1d_1->PrintData(stdout, 0, 0.0);        
        da1d_1->PrintData(stdout, 1, 0.0);
        da1d_1->PrintData(stdout, 2, 0.0);
        da1d_1->PrintData(stdout, 0, 1.0);
        da1d_1->PrintData(stdout, 1, 1.0);
        da1d_1->PrintData(stdout, 2, 1.0);
        delete da1d_1;
        printf("=== \n");
    }

//    double GetOffsetValFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetValFromTag(string offset_tag)\n");
        DataArrayNerr1d* da1d_1 = new DataArrayNerr1d("da1d_1");
        da1d_1->Init(4);
        da1d_1->SetValElm(0, 10);
        da1d_1->SetValElm(1, 11);
        da1d_1->SetValElm(2, 12);
        da1d_1->SetValElm(3, 13);        
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
