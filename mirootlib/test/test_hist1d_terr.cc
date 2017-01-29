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
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

   
//    void Init(const HistInfo1d* const hist_info);
    {
        printf("--- test Init;\n");
        HistInfo1d* hi1d = new HistInfo1d;
        hi1d->InitSetByNbin(0.0, 4.0, 4);
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(hi1d);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        delete hi1d;
        
        printf("=== \n");
    }
  
//    void SetOvalTerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
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
        hd1d->SetOvalTerrArr(4, oval_serr);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
   
//    void SetOvalTerrArr(vector<double> val_serr);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
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
        hd1d->SetOvalTerrArr(oval_serr);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        double oval[4];
        double oval_terr_plus[4];
        double oval_terr_minus[4];        
        oval[0] = 1;
        oval[1] = 2;
        oval[2] = 3;
        oval[3] = 4;
        oval_terr_plus[0] = 0.1;
        oval_terr_plus[1] = 0.2;
        oval_terr_plus[2] = 0.3;
        oval_terr_plus[3] = 0.4;
        oval_terr_minus[0] = -1.1;
        oval_terr_minus[1] = -1.2;
        oval_terr_minus[2] = -1.3;
        oval_terr_minus[3] = -1.4;
        hd1d->SetOvalArr(4, oval);
        hd1d->SetOvalTerrArr(4, oval_terr_plus, oval_terr_minus);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        vector<double> oval(4);
        vector<double> oval_terr_plus(4);
        vector<double> oval_terr_minus(4);
        oval[0] = 1;
        oval[1] = 2;
        oval[2] = 3;
        oval[3] = 4;
        oval_terr_plus[0] = 0.1;
        oval_terr_plus[1] = 0.2;
        oval_terr_plus[2] = 0.3;
        oval_terr_plus[3] = 0.4;
        oval_terr_minus[0] = -1.1;
        oval_terr_minus[1] = -1.2;
        oval_terr_minus[2] = -1.3;
        oval_terr_minus[3] = -1.4;
        
        hd1d->SetOvalArr(oval);
        hd1d->SetOvalTerrArr(oval_terr_plus, oval_terr_minus);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }
    

//    void SetOvalTerrElm(long ibin, double oval_serr);
    {
        printf("--- test SetOvalTerrElm(long ibin, double oval_serr)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrElm(0, 0.1);
        hd1d->SetOvalTerrElm(1, 0.2);
        hd1d->SetOvalTerrElm(2, 0.3);
        hd1d->SetOvalTerrElm(3, 0.4);

        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void SetOvalTerrPlusElm(long ibin, double oval_terr_plus);
//    void SetOvalTerrMinusElm(long ibin, double oval_terr_minus);
    {
        printf("--- test SetOvalTerrPlusElm(long ibin, double oval_terr_plus)\n");
        printf("--- test SetOvalTerrMinusElm(long ibin, double oval_terr_minus)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -1.1);
        hd1d->SetOvalTerrMinusElm(1, -1.2);
        hd1d->SetOvalTerrMinusElm(2, -1.3);
        hd1d->SetOvalTerrMinusElm(3, -1.4);

        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void FillByLarger(double xval,
//                      double oval,
//                      double oval_terr_plus,
//                      double oval_terr_minus);
    {
        printf("--- test FillByLarger\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);

        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillByLarger(0.1, 1.0, 0.1, -1.0);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillByLarger(0.1, -1.0, 5.0, -3.0);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");        
        hd1d->FillByLarger(0.1, 5.0, 0.7, -2.0);        
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void FillBySmaller(double xval,
//                       double oval,
//                       double oval_terr_plus,
//                       double oval_terr_minus);
    {
        printf("--- test FillBySmaller\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);

        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillBySmaller(0.1, 1.0, 0.1, -0.1);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd1d->FillBySmaller(0.1, -1.0, 5.0, -3.0);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");        
        hd1d->FillBySmaller(0.1, -5.0, 0.7, -1.0);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    void SetOvalErrArrByPoissonErr();  
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrElm(0, 0.1);
        hd1d->SetOvalTerrElm(1, 0.2);
        hd1d->SetOvalTerrElm(2, 0.3);
        hd1d->SetOvalTerrElm(3, 0.4);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");
        hd1d->SetOvalErrArrByPoissonErr();
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        
        printf("=== \n");
    }

//    HistDataTerr1d* const Clone() const;
    {
        printf("--- test Clone()\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrElm(0, 0.1);
        hd1d->SetOvalTerrElm(1, 0.2);
        hd1d->SetOvalTerrElm(2, 0.3);
        hd1d->SetOvalTerrElm(3, 0.4);
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");
        HistDataTerr1d* hd1d_new = hd1d->Clone();
        hd1d_new->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -1.1);
        hd1d->SetOvalTerrMinusElm(1, -1.2);
        hd1d->SetOvalTerrMinusElm(2, -1.3);
        hd1d->SetOvalTerrMinusElm(3, -1.4);
        hd1d->Save("temp.dat", "x,y,ye+,ye-", 0.0, 0.0);

        hd1d->Load("data/test_hist1d_terr.dat");
        hd1d->PrintInfo(stdout);
        hd1d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);
        
        delete hd1d;
        
        printf("=== \n");
    }

//    const DataArrayTerr1d* const GetOvalArr() const;
    {
        printf("--- test GetOvalArr()\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -1.1);
        hd1d->SetOvalTerrMinusElm(1, -1.2);
        hd1d->SetOvalTerrMinusElm(2, -1.3);
        hd1d->SetOvalTerrMinusElm(3, -1.4);

        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, hd1d->GetOvalArr()->GetValTerrMinusElm(idata));
        }
        
        delete hd1d;
        
        printf("=== \n");
    }
 
//    double GetOvalSerrElm(long ibin) const;
    {
        printf("--- test GetOvalSerrElm(long ibin)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8);
        
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

//    double GetOvalTerrPlusElm(long ibin) const;
//    double GetOvalTerrMinusElm(long ibin) const;
    {
        printf("--- test GetOvalTerrPlusElm(long ibin)\n");
        printf("--- test GetOvalTerrMinusElm(long ibin)\n");        
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8);
        
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalElm(%ld) = %e\n",
                   idata, hd1d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalTerrPlusElm(%ld) = %e\n",
                   idata, hd1d->GetOvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < hd1d->GetNbinX(); idata ++){
            printf("hd1d->GetOvalTerrMinusElm(%ld) = %e\n",
                   idata, hd1d->GetOvalTerrMinusElm(idata));
        }
        
        delete hd1d;
        
        printf("=== \n");
    }

//    double GetOvalSerrElmAtX(double xval) const;    
    {
        printf("--- test GetOvalSerrElmAtX(double xval)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8); 

        printf("hd1d->GetOvalSerrElmAtX(2.3) = %e\n",
               hd1d->GetOvalSerrElmAtX(2.3));
        
        delete hd1d;
        
        printf("=== \n");
    }
    
    
//    double GetOvalTerrPlusElmAtX(double xval) const;    
//    double GetOvalTerrMinusElmAtX(double xval) const;
    {
        printf("--- test GetOvalTerrPlusElmAtX(double xval)\n");
        printf("--- test GetOvalTerrMinusElmAtX(double xval)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8);        

        printf("hd1d->GetOvalTerrPlusElmAtX(2.3) = %e\n",
               hd1d->GetOvalTerrPlusElmAtX(2.3));
        printf("hd1d->GetOvalTerrMinusElmAtX(2.3) = %e\n",
               hd1d->GetOvalTerrMinusElmAtX(2.3));
        
        delete hd1d;
        
        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
//
    {
        printf("--- test PrintData\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 1);
        hd1d->SetOvalElm(1, 2);
        hd1d->SetOvalElm(2, 3);
        hd1d->SetOvalElm(3, 4);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8);
        
        printf("--- x,y \n");
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);
        //printf("--- x,y,ye \n");
        //hd1d->PrintData(stdout, "x,y,ye", 0.0, 0.0);
        printf("--- x,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe,y \n");
        hd1d->PrintData(stdout, "x,xe,y", 0.0, 0.0);
        //printf("--- x,xe,y,ye \n");
        //hd1d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        printf("--- x,xe,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe+,xe-,y \n");
        hd1d->PrintData(stdout, "x,xe+,xe-,y", 0.0, 0.0);
        //printf("--- x,xe+,xe-,y,ye \n");
        //hd1d->PrintData(stdout, "x,xe+,xe-,y,ye", 0.0, 0.0);
        printf("--- x,xe+,xe-,y,ye+,ye- \n");
        hd1d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);        
        
        delete hd1d;
        
        printf("=== \n");
    }

   
//    HistDataTerr1d* const GenHd1MaxInBin(long nbin_new) const;
    {
        printf("--- test GenHd1MaxInBin(long nbin_new)\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(8, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        hd1d->SetOvalElm(4, 0.3);
        hd1d->SetOvalElm(5, 1.3);
        hd1d->SetOvalElm(6, 0.4);
        hd1d->SetOvalElm(7, 1.4);                        

        hd1d->SetOvalTerrPlusElm(0, 5.1);
        hd1d->SetOvalTerrPlusElm(1, 6.1);
        hd1d->SetOvalTerrPlusElm(2, 5.2);
        hd1d->SetOvalTerrPlusElm(3, 6.2);
        hd1d->SetOvalTerrPlusElm(4, 5.3);
        hd1d->SetOvalTerrPlusElm(5, 6.3);
        hd1d->SetOvalTerrPlusElm(6, 5.4);
        hd1d->SetOvalTerrPlusElm(7, 6.4);

        hd1d->SetOvalTerrMinusElm(0, -0.1);
        hd1d->SetOvalTerrMinusElm(1, -0.2);
        hd1d->SetOvalTerrMinusElm(2, -0.3);
        hd1d->SetOvalTerrMinusElm(3, -0.4);
        hd1d->SetOvalTerrMinusElm(4, -0.5);
        hd1d->SetOvalTerrMinusElm(5, -0.6);
        hd1d->SetOvalTerrMinusElm(6, -0.7);
        hd1d->SetOvalTerrMinusElm(7, -0.8);
        
        HistDataTerr1d* hd1d_new = hd1d->GenHd1MaxInBin(4);
        hd1d_new->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        delete hd1d;
        delete hd1d_new;
        
        printf("=== \n");
    }

//    GraphDataTerr2d* const GenGraph2d() const;    
    {
        printf("--- test GenGraph2d()\n");
        HistDataTerr1d* hd1d = new HistDataTerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 0.1);
        hd1d->SetOvalElm(1, 1.1);
        hd1d->SetOvalElm(2, 0.2);
        hd1d->SetOvalElm(3, 1.2);
        hd1d->SetOvalTerrPlusElm(0, 0.1);
        hd1d->SetOvalTerrPlusElm(1, 0.2);
        hd1d->SetOvalTerrPlusElm(2, 0.3);
        hd1d->SetOvalTerrPlusElm(3, 0.4);
        hd1d->SetOvalTerrMinusElm(0, -0.3);
        hd1d->SetOvalTerrMinusElm(1, -0.4);
        hd1d->SetOvalTerrMinusElm(2, -0.7);
        hd1d->SetOvalTerrMinusElm(3, -0.8);
        
        GraphDataTerr2d* gd2d = hd1d->GenGraph2d();
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        
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
        printf("--- test MkTH1Fig\n");        
        HistDataTerr1d* hd1d = new HistDataTerr1d;
        hd1d->Init(4, 0.0, 4.0);
        hd1d->SetOvalElm(0, 10);
        hd1d->SetOvalElm(1, 20);
        hd1d->SetOvalElm(2, 30);
        hd1d->SetOvalElm(3, 40);
        hd1d->SetOvalTerrPlusElm(0, 1);
        hd1d->SetOvalTerrPlusElm(1, 2);
        hd1d->SetOvalTerrPlusElm(2, 3);
        hd1d->SetOvalTerrPlusElm(3, 4);
        hd1d->SetOvalTerrMinusElm(0, -2);
        hd1d->SetOvalTerrMinusElm(1, -4);
        hd1d->SetOvalTerrMinusElm(2, -6);
        hd1d->SetOvalTerrMinusElm(3, -8);

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

    return status_prog;
}
