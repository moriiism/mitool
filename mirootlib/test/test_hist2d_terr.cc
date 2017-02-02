#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_terr.h"
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
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-,z,ze+,ze-", 0.0, 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

/*
    
//    void Init(const HistInfo2d* const hist_info);
    {
        printf("--- test Init;\n");
        HistInfo2d* hi2d = new HistInfo2d;
        hi2d->InitSetByNbin(0.0, 4.0, 4);
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(hi2d);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        delete hi2d;
        
        printf("=== \n");
    }
  
//    void SetOvalTerrArr(long ndata, const double* const val_serr);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
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
        hd2d->SetOvalArr(4, oval);
        hd2d->SetOvalTerrArr(4, oval_serr);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }
   
//    void SetOvalTerrArr(vector<double> val_serr);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
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
        hd2d->SetOvalArr(oval);
        hd2d->SetOvalTerrArr(oval_serr);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
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
        hd2d->SetOvalArr(4, oval);
        hd2d->SetOvalTerrArr(4, oval_terr_plus, oval_terr_minus);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
    {
        printf("--- test SetOvalTerrArr\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
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
        
        hd2d->SetOvalArr(oval);
        hd2d->SetOvalTerrArr(oval_terr_plus, oval_terr_minus);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }
    

//    void SetOvalTerrElm(long ibin, double oval_serr);
    {
        printf("--- test SetOvalTerrElm(long ibin, double oval_serr)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrElm(0, 0.1);
        hd2d->SetOvalTerrElm(1, 0.2);
        hd2d->SetOvalTerrElm(2, 0.3);
        hd2d->SetOvalTerrElm(3, 0.4);

        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void SetOvalTerrPlusElm(long ibin, double oval_terr_plus);
//    void SetOvalTerrMinusElm(long ibin, double oval_terr_minus);
    {
        printf("--- test SetOvalTerrPlusElm(long ibin, double oval_terr_plus)\n");
        printf("--- test SetOvalTerrMinusElm(long ibin, double oval_terr_minus)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -1.1);
        hd2d->SetOvalTerrMinusElm(1, -1.2);
        hd2d->SetOvalTerrMinusElm(2, -1.3);
        hd2d->SetOvalTerrMinusElm(3, -1.4);

        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void FillByLarger(double xval,
//                      double oval,
//                      double oval_terr_plus,
//                      double oval_terr_minus);
    {
        printf("--- test FillByLarger\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);

        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd2d->FillByLarger(0.1, 1.0, 0.1, -1.0);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd2d->FillByLarger(0.1, -1.0, 5.0, -3.0);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");        
        hd2d->FillByLarger(0.1, 5.0, 0.7, -2.0);        
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void FillBySmaller(double xval,
//                       double oval,
//                       double oval_terr_plus,
//                       double oval_terr_minus);
    {
        printf("--- test FillBySmaller\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);

        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd2d->FillBySmaller(0.1, 1.0, 0.1, -0.1);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        printf("--- \n");        
        hd2d->FillBySmaller(0.1, -1.0, 5.0, -3.0);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");        
        hd2d->FillBySmaller(0.1, -5.0, 0.7, -1.0);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    void SetOvalErrArrByPoissonErr();  
    {
        printf("--- test SetOvalErrArrByPoissonErr()\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrElm(0, 0.1);
        hd2d->SetOvalTerrElm(1, 0.2);
        hd2d->SetOvalTerrElm(2, 0.3);
        hd2d->SetOvalTerrElm(3, 0.4);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");
        hd2d->SetOvalErrArrByPoissonErr();
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        
        printf("=== \n");
    }

//    HistDataTerr2d* const Clone() const;
    {
        printf("--- test Clone()\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrElm(0, 0.1);
        hd2d->SetOvalTerrElm(1, 0.2);
        hd2d->SetOvalTerrElm(2, 0.3);
        hd2d->SetOvalTerrElm(3, 0.4);
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        printf("--- \n");
        HistDataTerr2d* hd2d_new = hd2d->Clone();
        hd2d_new->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);

        delete hd2d;
        delete hd2d_new;
        
        printf("=== \n");
    }

//    void Load(string file);
    {
        printf("--- test Load\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -1.1);
        hd2d->SetOvalTerrMinusElm(1, -1.2);
        hd2d->SetOvalTerrMinusElm(2, -1.3);
        hd2d->SetOvalTerrMinusElm(3, -1.4);
        hd2d->Save("temp.dat", "x,y,ye+,ye-", 0.0, 0.0);

        hd2d->Load("data/test_hist2d_terr.dat");
        hd2d->PrintInfo(stdout);
        hd2d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);
        
        delete hd2d;
        
        printf("=== \n");
    }

//    const DataArrayTerr2d* const GetOvalArr() const;
    {
        printf("--- test GetOvalArr()\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -1.1);
        hd2d->SetOvalTerrMinusElm(1, -1.2);
        hd2d->SetOvalTerrMinusElm(2, -1.3);
        hd2d->SetOvalTerrMinusElm(3, -1.4);

        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalArr()->GetValElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalArr()->GetValTerrPlusElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValTerrPlusElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalArr()->GetValTerrMinusElm(%ld) = %e\n",
                   idata, hd2d->GetOvalArr()->GetValTerrMinusElm(idata));
        }
        
        delete hd2d;
        
        printf("=== \n");
    }
 
//    double GetOvalSerrElm(long ibin) const;
    {
        printf("--- test GetOvalSerrElm(long ibin)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8);
        
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalElm(%ld) = %e\n",
                   idata, hd2d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalSerrElm(%ld) = %e\n",
                   idata, hd2d->GetOvalSerrElm(idata));
        }
        
        delete hd2d;
        
        printf("=== \n");
    }

//    double GetOvalTerrPlusElm(long ibin) const;
//    double GetOvalTerrMinusElm(long ibin) const;
    {
        printf("--- test GetOvalTerrPlusElm(long ibin)\n");
        printf("--- test GetOvalTerrMinusElm(long ibin)\n");        
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8);
        
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalElm(%ld) = %e\n",
                   idata, hd2d->GetOvalElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalTerrPlusElm(%ld) = %e\n",
                   idata, hd2d->GetOvalTerrPlusElm(idata));
        }
        for(long idata = 0; idata < hd2d->GetNbinX(); idata ++){
            printf("hd2d->GetOvalTerrMinusElm(%ld) = %e\n",
                   idata, hd2d->GetOvalTerrMinusElm(idata));
        }
        
        delete hd2d;
        
        printf("=== \n");
    }

//    double GetOvalSerrElmAtX(double xval) const;    
    {
        printf("--- test GetOvalSerrElmAtX(double xval)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8); 

        printf("hd2d->GetOvalSerrElmAtX(2.3) = %e\n",
               hd2d->GetOvalSerrElmAtX(2.3));
        
        delete hd2d;
        
        printf("=== \n");
    }
    
    
//    double GetOvalTerrPlusElmAtX(double xval) const;    
//    double GetOvalTerrMinusElmAtX(double xval) const;
    {
        printf("--- test GetOvalTerrPlusElmAtX(double xval)\n");
        printf("--- test GetOvalTerrMinusElmAtX(double xval)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8);        

        printf("hd2d->GetOvalTerrPlusElmAtX(2.3) = %e\n",
               hd2d->GetOvalTerrPlusElmAtX(2.3));
        printf("hd2d->GetOvalTerrMinusElmAtX(2.3) = %e\n",
               hd2d->GetOvalTerrMinusElmAtX(2.3));
        
        delete hd2d;
        
        printf("=== \n");
    }

//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_oval) const;
//
    {
        printf("--- test PrintData\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 1);
        hd2d->SetOvalElm(1, 2);
        hd2d->SetOvalElm(2, 3);
        hd2d->SetOvalElm(3, 4);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8);
        
        printf("--- x,y \n");
        hd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        //printf("--- x,y,ye \n");
        //hd2d->PrintData(stdout, "x,y,ye", 0.0, 0.0);
        printf("--- x,y,ye+,ye- \n");
        hd2d->PrintData(stdout, "x,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe,y \n");
        hd2d->PrintData(stdout, "x,xe,y", 0.0, 0.0);
        //printf("--- x,xe,y,ye \n");
        //hd2d->PrintData(stdout, "x,xe,y,ye", 0.0, 0.0);
        printf("--- x,xe,y,ye+,ye- \n");
        hd2d->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        printf("--- x,xe+,xe-,y \n");
        hd2d->PrintData(stdout, "x,xe+,xe-,y", 0.0, 0.0);
        //printf("--- x,xe+,xe-,y,ye \n");
        //hd2d->PrintData(stdout, "x,xe+,xe-,y,ye", 0.0, 0.0);
        printf("--- x,xe+,xe-,y,ye+,ye- \n");
        hd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);        
        
        delete hd2d;
        
        printf("=== \n");
    }

   
//    HistDataTerr2d* const GenHd1MaxInBin(long nbin_new) const;
    {
        printf("--- test GenHd1MaxInBin(long nbin_new)\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(8, 0.0, 4.0);
        hd2d->SetOvalElm(0, 0.1);
        hd2d->SetOvalElm(1, 1.1);
        hd2d->SetOvalElm(2, 0.2);
        hd2d->SetOvalElm(3, 1.2);
        hd2d->SetOvalElm(4, 0.3);
        hd2d->SetOvalElm(5, 1.3);
        hd2d->SetOvalElm(6, 0.4);
        hd2d->SetOvalElm(7, 1.4);                        

        hd2d->SetOvalTerrPlusElm(0, 5.1);
        hd2d->SetOvalTerrPlusElm(1, 6.1);
        hd2d->SetOvalTerrPlusElm(2, 5.2);
        hd2d->SetOvalTerrPlusElm(3, 6.2);
        hd2d->SetOvalTerrPlusElm(4, 5.3);
        hd2d->SetOvalTerrPlusElm(5, 6.3);
        hd2d->SetOvalTerrPlusElm(6, 5.4);
        hd2d->SetOvalTerrPlusElm(7, 6.4);

        hd2d->SetOvalTerrMinusElm(0, -0.1);
        hd2d->SetOvalTerrMinusElm(1, -0.2);
        hd2d->SetOvalTerrMinusElm(2, -0.3);
        hd2d->SetOvalTerrMinusElm(3, -0.4);
        hd2d->SetOvalTerrMinusElm(4, -0.5);
        hd2d->SetOvalTerrMinusElm(5, -0.6);
        hd2d->SetOvalTerrMinusElm(6, -0.7);
        hd2d->SetOvalTerrMinusElm(7, -0.8);
        
        HistDataTerr2d* hd2d_new = hd2d->GenHd1MaxInBin(4);
        hd2d_new->PrintData(stdout, "x,xe,y,ye+,ye-", 0.0, 0.0);
        
        delete hd2d;
        delete hd2d_new;
        
        printf("=== \n");
    }

//    GraphDataTerr2d* const GenGraph2d() const;    
    {
        printf("--- test GenGraph2d()\n");
        HistDataTerr2d* hd2d = new HistDataTerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 0.1);
        hd2d->SetOvalElm(1, 1.1);
        hd2d->SetOvalElm(2, 0.2);
        hd2d->SetOvalElm(3, 1.2);
        hd2d->SetOvalTerrPlusElm(0, 0.1);
        hd2d->SetOvalTerrPlusElm(1, 0.2);
        hd2d->SetOvalTerrPlusElm(2, 0.3);
        hd2d->SetOvalTerrPlusElm(3, 0.4);
        hd2d->SetOvalTerrMinusElm(0, -0.3);
        hd2d->SetOvalTerrMinusElm(1, -0.4);
        hd2d->SetOvalTerrMinusElm(2, -0.7);
        hd2d->SetOvalTerrMinusElm(3, -0.8);
        
        GraphDataTerr2d* gd2d = hd2d->GenGraph2d();
        gd2d->PrintData(stdout, "x,xe+,xe-,y,ye+,ye-", 0.0, 0.0);
        
        delete hd2d;
        delete gd2d;
        
        printf("=== \n");
    }

   
//    TH2D* const GenTH2D(double offset_xval,
//                        double offset_oval) const;
//    void MkTH1Fig(string outfig,
//                  MirRootTool* const root_tool,
//                  double offset_xval,
//                  double offset_oval) const;
    {
        printf("--- test GenTH2D()\n");
        printf("--- test MkTH1Fig\n");        
        HistDataTerr2d* hd2d = new HistDataTerr2d;
        hd2d->Init(4, 0.0, 4.0);
        hd2d->SetOvalElm(0, 10);
        hd2d->SetOvalElm(1, 20);
        hd2d->SetOvalElm(2, 30);
        hd2d->SetOvalElm(3, 40);
        hd2d->SetOvalTerrPlusElm(0, 1);
        hd2d->SetOvalTerrPlusElm(1, 2);
        hd2d->SetOvalTerrPlusElm(2, 3);
        hd2d->SetOvalTerrPlusElm(3, 4);
        hd2d->SetOvalTerrMinusElm(0, -2);
        hd2d->SetOvalTerrMinusElm(1, -4);
        hd2d->SetOvalTerrMinusElm(2, -6);
        hd2d->SetOvalTerrMinusElm(3, -8);

        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0);
        th2d->Draw("E");
        root_tool->GetTCanvas()->Print("temp.png");

        hd2d->MkTH1Fig("temp_fig.png", root_tool,
                       0.0, 0.0);
        delete hd2d;
        delete th2d;
        delete root_tool;
        
        printf("=== \n");
    }

*/

    return status_prog;
}


//    void Init(const HistInfo2d* const hist_info);
//    void SetOvalTerrArr(long ndata, const double* const val_serr);
//    void SetOvalTerrArr(vector<double> val_serr);
//    void SetOvalTerrArr(long ndata,
//                        const double* const val_terr_plus,
//                        const double* const val_terr_minus);
//    void SetOvalTerrArr(vector<double> val_terr_plus,
//                        vector<double> val_terr_minus);
//    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
//                        double oval_serr);
//    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
//                        double oval_terr_plus,
//                        double oval_terr_minus);
//    void FillByLarger(double xval, double yval,
//                      double oval,
//                      double oval_terr_plus,
//                      double oval_terr_minus);
//    void FillBySmaller(double xval, double yval,
//                       double oval,
//                       double oval_terr_plus,
//                       double oval_terr_minus);
//    void SetOvalErrArrByPoissonErr();
//    HistDataTerr2d* const Clone() const;
//    void Load(string file);
//
//    const DataArrayTerr1d* const GetOvalArr() const;
//    double GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const;    
//    double GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const;
//    double GetOvalTerrPlusElmAtXY(double xval, double yval) const;
//    double GetOvalTerrMinusElmAtXY(double xval, double yval) const;
//    void GenOvalTerrPlusArr(double** const oval_terr_plus_arr_ptr,
//                            long* const nbin_ptr) const;
//    void GenOvalTerrMinusArr(double** const oval_terr_minus_arr_ptr,
//                             long* const nbin_ptr) const;
//
//   
//    void PrintData(FILE* fp, string format,
//                   double offset_xval,
//                   double offset_yval,
//                   double offset_oval) const;




