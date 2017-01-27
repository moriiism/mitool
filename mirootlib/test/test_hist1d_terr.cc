#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist1d_terr.h"
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
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
    
//    void Init(const HistInfo1d* const hist_info);
    {
        printf("--- test Init;\n");
        HistInfo1d* hi1d = new HistInfo1d;
        hi1d->InitSetByNbin(0.0, 4.0, 4);
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(hi1d);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        delete hi1d;
        
        printf("=== \n");
    }
   
//    void SetOvalSerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetOvalSerrArr\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        double oval[4];
        double oval_serr[4];
        oval[0] = 1;
        oval[1] = 2;
        oval[2] = 3;
        oval[3] = 4;
        oval_serr[0] = 0.1;
        oval_serr[1] = 0.2;
        oval_serr[2] = 0.3;
        oval_serr[3] = 0.4;
        hd1d->SetOvalArr(4, oval);
        hd1d->SetOvalSerrArr(4, oval_serr);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void SetOvalSerrArr(vector<double> val_serr);
    {
        printf("--- test SetOvalSerrArr\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        vector<double> oval(4);
        vector<double> oval_serr(4);
        oval[0] = 1;
        oval[1] = 2;
        oval[2] = 3;
        oval[3] = 4;
        oval_serr[0] = 0.1;
        oval_serr[1] = 0.2;
        oval_serr[2] = 0.3;
        oval_serr[3] = 0.4;
        hd1d->SetOvalArr(oval);
        hd1d->SetOvalSerrArr(oval_serr);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
  
//    void SetOvalSerrElm(long ibin, double oval_serr);
    {
        printf("--- test SetOvalSerrElm(long ibin, double oval_serr)\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);

        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
 
//    void FillByLarger(double xval,
//                      double oval,
//                      double oval_serr);
    {
        printf("--- test FillByLarger\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);

        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillByLarger(0.1, 1.0, 0.1);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillByLarger(0.1, -1.0, 5.0);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        printf("--- \n");        
        hd1d->FillByLarger(0.1, 5.0, 0.7);        
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

  
//    void FillBySmaller(double xval,
//                       double oval,
//                       double oval_serr);
    {
        printf("--- test FillBySmaller\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);

        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillBySmaller(0.1, 1.0, 0.1);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillBySmaller(0.1, -1.0, 5.0);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        printf("--- \n");        
        hd1d->FillBySmaller(0.1, -5.0, 0.7);        
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
   
//    void SetOvalErrArrByPoissonErr();
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        printf("--- \n");
        hd1d->SetOvalErrArrByPoissonErr();
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
 
//    HistDataSerr1d* const Clone() const;
    {
        printf("--- test Clone()\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);
        hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        printf("--- \n");
        HistDataSerr1d* hd1d_new = hd1d->Clone();
        hd1d_new->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);

        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }
   
//    void Load(string file);
    {
        printf("--- test Load\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);
        hd1d->Save("temp.dat", "x,y,ye", 0.0, 0.0);

        hd1d->Load("data/test_hist1d_serr.dat");
        hd1d->PrintInfo(stdout);
        hd1d->PrintData(stdout, "x,y,ye", 0.0, 0.0);
        
        delete hd1d;
        
        printf("=== \n");
    }

//    const DataArraySerr1d* const GetOvalArr() const;
    {
        printf("--- test GetOvalArr()\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);

        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValSerrElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValSerrElm(idata));
        }
        
        delete hd1d;
        
        printf("=== \n");
    }

//    double GetOvalSerrElm(long ibin) const;
    {
        printf("--- test GetOvalSerrElm(long ibin)\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);

        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalElm(%ld) = %e\n",
                   idata, hd1d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalSerrElm(%ld) = %e\n",
                   idata, hd1d->GetOvalSerrElm(idata));
        }
        
        delete hd1d;
        
        printf("=== \n");
    }
    
//    double GetOvalSerrElmAtX(double xval) const;
    {
        printf("--- test GetOvalSerrElmAtX(double xval)\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);

        printf("hd1d->GetOvalSerrElmAtX(2.3) = %e\n",
               hd1d->GetOvalSerrElmAtX(2.3));
        
        delete hd1d;
        
        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
    {
        printf("--- test PrintData\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalSerrElm(0, 0.1);
        hd1d->SetOvalSerrElm(1, 0.2);
        hd1d->SetOvalSerrElm(2, 0.3);
        hd1d->SetOvalSerrElm(3, 0.4);
        
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

//    HistDataSerr1d* const GenHd1MaxInBin(long nbin_new) const;
    {
        printf("--- test GenHd1MaxInBin(long nbin_new)\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(8, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        hd1d->SetOvalElm(4, 0.3);
        hd1d->SetOvalElm(5, 1.3);
        hd1d->SetOvalElm(6, 0.4);
        hd1d->SetOvalElm(7, 1.4);                        

        hd1d->SetOvalSerrElm(0, 5.1);
        hd1d->SetOvalSerrElm(1, 6.1);
        hd1d->SetOvalSerrElm(2, 5.2);
        hd1d->SetOvalSerrElm(3, 6.2);
        hd1d->SetOvalSerrElm(4, 5.3);
        hd1d->SetOvalSerrElm(5, 6.3);
        hd1d->SetOvalSerrElm(6, 5.4);
        hd1d->SetOvalSerrElm(7, 6.4);
        
        HistDataSerr1d* hd1d_new = hd1d->GenHd1MaxInBin(4);
        hd1d_new->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }

    
//    GraphDataSerr2d* const GenGraph2d() const;
    {
        printf("--- test GenGraph2d()\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);

        hd1d->SetOvalSerrElm(0, 4.1);
        hd1d->SetOvalSerrElm(1, 4.1);
        hd1d->SetOvalSerrElm(2, 4.2);
        hd1d->SetOvalSerrElm(3, 4.2);
        
        GraphDataSerr2d* gd2d = hd1d->GenGraph2d();
        gd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        
        delete hd1d;
        delete gd2d;
        
        printf("=== \n");
    }

    
//    TH1D* const GenTH1D(double offset_xval,
//                        double offset_oval) const;
//    void MkTH1Fig(string outfig,
//                  MirRootTool* const root_tool,
//                  double offset_xval,
//                  double offset_oval) const;
    {
        printf("--- test GenTH1D()\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 10);
        hd1d->SetOvalElm(1, 20);
        hd1d->SetOvalElm(2, 30);
        hd1d->SetOvalElm(3, 40);
        hd1d->SetOvalErrArrByPoissonErr();

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        TH1D* th1d = hd1d->GenTH1D(0.0, 0.0);
        th1d->Draw("E");
        root_tool->GetTCanvas()->Print("temp.png");

        hd1d->MkTH1Fig("temp_fig.png", root_tool,
                       0.0, 0.0);
        delete hd1d;
        delete th1d;
        delete root_tool;
        
        printf("=== \n");
    }
    
//    void FillRandom(const MirFunc* const func,
//                    const double* const func_par,
//                    int rand_seed);
    {
        printf("--- test FillRandom\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(8, 0.0, 4.0);

        double par[3] = {100.0, 1.0, 2.0};
        FuncTest* func = new FuncTest;
        hd1d->FillRandom(func, par, 1);

        MirQdpTool::MkQdp(hd1d, "temp_1.qdp", "x,xe,y,ye");

        delete hd1d;
        delete func;
        
        printf("=== \n");
    }
    
//    void FillRandom(const MirFunc* const func,
//                    const double* const func_par,
//                    const MirFunc* const func_sigma,
//                    const double* const func_par_sigma,
//                    int rand_seed);
    {
        printf("--- test FillRandom\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(8, 0.0, 4.0);

        double par[3] = {100.0, 10.0, -2.0};
        FuncTest* func = new FuncTest;

        double par_sigma[3] = {1.0, 1.0, 1.0};
        FuncTest* func_sigma = new FuncTest;
        
        hd1d->FillRandom(func, par, func_sigma, par_sigma, 1);
        MirQdpTool::MkQdp(hd1d, "temp_2.qdp", "x,xe,y,ye");

        delete hd1d;
        delete func;
        delete func_sigma;
        
        printf("=== \n");
    }


    
//    void FillRandom(const HistData1d* const hist_data,
//                    int rand_seed);
    {
        printf("--- test FillRandom\n");
        HistDataSerr1d* hd1d = new HistDataSerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 10);
        hd1d->SetOvalElm(1, 20);
        hd1d->SetOvalElm(2, 30);
        hd1d->SetOvalElm(3, 40);

        HistDataSerr1d* hd1d_rand = new HistDataSerr1d;
        hd1d_rand->FillRandom(hd1d, 0);
        MirQdpTool::MkQdp(hd1d, "temp_3.qdp", "x,xe,y,ye");
        MirQdpTool::MkQdp(hd1d_rand, "temp_3_rand.qdp", "x,xe,y,ye");        

        delete hd1d;
        delete hd1d_rand;
        
        printf("=== \n");
    }


    return status_prog;
}
