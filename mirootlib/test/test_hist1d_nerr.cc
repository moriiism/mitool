#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist1d_nerr.h"
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
            SetNdim(1);           
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
    double ans = par[0] + par[1] * argx + par[2] * pow(argx, 2.);
    return ans;
}



int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;

//    void Init(long nbin_xval,
//              double xval_lo,
//              double xval_up);
    {
        printf("--- test Init;\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        long nbin = 4;
        double lo = 0.0;
        double up = 4.0;
        hd1d->Init(nbin, lo, up);
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void Init(const HistInfo1d* const hist_info);
    {
        printf("--- test Init;\n");
        HistInfo1d* hi1d = new HistInfo1d;
        hi1d->InitSetByNbin(0.0, 4.0, 4);
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(hi1d);
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);

        delete hd1d;
        delete hi1d;
        
        printf("=== \n");
    }
    
//    HistDataNerr1d* const Clone() const;
    {
        printf("--- test Clone\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetConst(2.0);
        HistDataNerr1d* hd1d_new = hd1d->Clone();
        hd1d_new->PrintData(stdout, "x,y", 0.0, 0.0);

        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }
   
//    void Load(string file);
    {
        printf("--- test Load\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Load("data/test_hist1d_nerr.dat");
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
    
//    const DataArrayNerr1d* const GetOvalArr() const;
    {
        printf("--- test GetOvalArr()\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 0.2);
        hd1d->SetOvalElm(2, 0.3);
        hd1d->SetOvalElm(3, 0.4);

        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValElm(idata));
        }
        delete hd1d;
        
        printf("=== \n");
    }

   
//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 0.2);
        hd1d->SetOvalElm(2, 0.3);
        hd1d->SetOvalElm(3, 0.4);

        printf("--- x,y \n");
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
        printf("--- x,y,ye \n");
        hd1d->PrintData(stdout, "x,y,ye", 0.0, 0.0);
        printf("--- x,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe,y \n");
        hd1d->PrintData(stdout, "x,xe,y", 0.0, 0.0);
        printf("--- x,xe,y,ye \n");
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        printf("--- x,xe,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe+,xe-,y \n");
        hd1d->PrintData(stdout, "x,xe+,xe-,y", 0.0, 0.0);
        printf("--- x,xe+,xe-,y,ye \n");
        hd1d->PrintData(stdout, "x,xe+,xe-,y,ye", 0.0, 0.0);
        printf("--- x,xe+,xe-,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);        

        delete hd1d;
        
        printf("=== \n");
    }
    
//    HistDataNerr1d* const GenHd1MaxInBin(long nbin_new) const;
    {
        printf("--- test GenHd1MaxInBin(long nbin_new)\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(8, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        
        hd1d->SetOvalElm(4, 0.3);
        hd1d->SetOvalElm(5, 1.3);
        
        hd1d->SetOvalElm(6, 0.4);
        hd1d->SetOvalElm(7, 1.4);                        

        HistDataNerr1d* hd1d_new = hd1d->GenHd1MaxInBin(4);
        hd1d_new->PrintData(stdout, "x,y", 0.0, 0.0);
        
        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }
    
//    GraphDataNerr2d* const GenGraph2d() const;
    {
        printf("--- test GenGraph2d()\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(8, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        hd1d->SetOvalElm(4, 0.3);
        hd1d->SetOvalElm(5, 1.3);
        hd1d->SetOvalElm(6, 0.4);
        hd1d->SetOvalElm(7, 1.4);

        GraphDataNerr2d* gd2d = hd1d->GenGraph2d();
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        
        delete hd1d;
        delete gd2d;
        
        printf("=== \n");
    }

   
//    TH1D* const GenTH1D(double offset_xval,
//                        double offset_oval) const;
    {
        printf("--- test GenTH1D()\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(8, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        hd1d->SetOvalElm(4, 0.3);
        hd1d->SetOvalElm(5, 1.3);
        hd1d->SetOvalElm(6, 0.4);
        hd1d->SetOvalElm(7, 1.4);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        TH1D* th1d = hd1d->GenTH1D(0.0, 0.0);
        th1d->Draw("HIST");
        root_tool->GetTCanvas()->Print("temp.png");
       
        delete hd1d;
        delete th1d;
        delete root_tool;
        
        printf("=== \n");
    }

//    void MkTH1Fig(string outfig,
//                  MirRootTool* const root_tool,
//                  double offset_xval,
//                  double offset_oval) const;
    {
        printf("--- test MkTH1Fig\n");

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 0.2);
        hd1d->SetOvalElm(2, 0.3);
        hd1d->SetOvalElm(3, 0.4);
        
        hd1d->MkTH1Fig("temp.png", root_tool, 0.0, 0.0);

        delete hd1d;
        delete root_tool;

        printf("=== \n");
    }


//void FillRandom(const MirFunc* const func,
//                               const double* const func_par,
//                               int rand_seed)
    {
        printf("--- test FillRandom\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(8, 0.0, 4.0);

        double par[3] = {100.0, 1.0, 2.0};
        FuncTest* func = new FuncTest;
        hd1d->FillRandom(func, par, 1);

        MirQdpTool::MkQdp(hd1d, "temp.qdp", "x,y");

        delete hd1d;
        delete func;
        
        printf("=== \n");
    }
    
//    void FillRandom(const HistData1d* const hist_data,
//                    int rand_seed);
    {
        printf("--- test FillRandom\n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 10);
        hd1d->SetOvalElm(1, 20);
        hd1d->SetOvalElm(2, 30);
        hd1d->SetOvalElm(3, 40);

        HistDataNerr1d* hd1d_rand = new HistDataNerr1d;
        hd1d_rand->FillRandom(hd1d, 0);
        MirQdpTool::MkQdp(hd1d, "temp.qdp", "x,y");
        MirQdpTool::MkQdp(hd1d_rand, "temp_rand.qdp", "x,y");        

        delete hd1d;
        delete hd1d_rand;
        
        printf("=== \n");
    }

    return status_prog;
}
