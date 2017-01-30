#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_nerr.h"
#include "mir_root_tool.h"
#include "mir_qdp_tool.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


class FuncTest : public MirFunc{
public:
    explicit FuncTest(string title = "") :
        MirFunc("FuncTest", title)
        {
            SetNpar(3);
            SetNdim(2);           
        }
    ~FuncTest() {
        NullMirFunc();
    }

    void Copy(const FuncTest* const org);
    FuncTest* const Clone() const;
    double Eval(const double* const xval,
                const double* const par) const;
};

void FuncTest::Copy(const FuncTest* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    NullMirFunc();
    SetNpar(org->GetNpar());
    SetNdim(org->GetNdim());
}

FuncTest* const FuncTest::Clone() const
{
    FuncTest* obj_new = new FuncTest;
    obj_new->Copy(this);
    return obj_new;
}

double FuncTest::Eval(const double* const xval,
                      const double* const par) const
{
    double argx = xval[0];
    double argy = xval[1];
    double ans = par[0] + par[1] * pow(argx, 2.) + par[2] * pow(argy, 2.);
    return ans;
}



int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long nbin_xval, double xval_lo, double xval_up,
//              long nbin_yval, double yval_lo, double yval_up);
    {
        printf("--- test Init;\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void Init(const HistInfo2d* const hist_info);
    {
        printf("--- test Init;\n");
        HistInfo2d* hi2d = new HistInfo2d;
        hi2d->InitSetByNbin(0.0, 2.0, 2, 0.0, 3.0, 3);
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(hi2d);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;
        delete hi2d;
        
        printf("=== \n");
    }

    
//    HistDataNerr2d* const Clone() const;
    {
        printf("--- test Clone\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);        
        hd2d->SetConst(2.0);
        HistDataNerr2d* hd2d_new = hd2d->Clone();
        hd2d_new->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;
        delete hd2d_new;
        
        printf("=== \n");
    }
  
//    void Load(string file);
    {
        printf("--- test Load\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Load("data/test_hist2d_nerr.dat");
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

    
//    const DataArrayNerr1d* const GetOvalArr() const;
    {
        printf("--- test GetOvalArr()\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 0.1);
        hd2d->SetOvalElm(1, 0, 0.2);
        hd2d->SetOvalElm(0, 1, 0.3);
        hd2d->SetOvalElm(1, 1, 0.4);
        hd2d->SetOvalElm(0, 2, 0.5);
        hd2d->SetOvalElm(1, 2, 0.6);        
        for(long idata = 0; idata < hd2d->GetNbin(); idata ++){
            printf("hd2d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValElm(idata));
        }
        delete hd2d;
        
        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_yval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 0.1);
        hd2d->SetOvalElm(1, 0, 0.2);
        hd2d->SetOvalElm(0, 1, 0.3);
        hd2d->SetOvalElm(1, 1, 0.4);
        hd2d->SetOvalElm(0, 2, 0.5);
        hd2d->SetOvalElm(1, 2, 0.6);        

        printf("--- x,y,z \n");
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        printf("--- x,y,z,ze \n");
        hd2d->PrintData(stdout, "x,y,z,ze", 0.0, 0.0, 0.0);
        printf("--- x,xe,y,ye,z,ze \n");
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze", 0.0, 0.0, 0.0);
        printf("--- x,xe,y,ye,z \n");
        hd2d->PrintData(stdout, "x,xe,y,ye,z", 0.0, 0.0, 0.0);
        printf("--- x,y,z,ze+,ze- \n");
        hd2d->PrintData(stdout, "x,y,z,ze+,ze-", 0.0, 0.0, 0.0);        
        printf("--- x,xe,y,ye,z,ze+,ze- \n");
        hd2d->PrintData(stdout, "x,xe,y,ye,z,ze+,ze-", 0.0, 0.0, 0.0);        
        printf("--- x,xe+,xe-,y,ye+,ye-,z,ze+,ze- \n");
        hd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);        

        delete hd2d;
        
        printf("=== \n");
    }

    return status_prog;
}

   
//    TH2D* const GenTH2D(double offset_xval,
//                        double offset_yval,
//                        double offset_oval) const;
//    void FillRandom(const MirFunc* const func,
//                    const double* const func_par,
//                    int rand_seed);
//    void FillRandom(const HistData2d* const hist_data,
//                    int rand_seed);
