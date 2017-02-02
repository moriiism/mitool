#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_nerr.h"

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

//    virtual void Init(long nbin_xval, double xval_lo, double xval_up,
//                      long nbin_yval, double yval_lo, double yval_up) = 0;
    {
        printf("--- test Init \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");
        
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->SetConst(2.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp.png");

        delete th2d;
        delete hd2d;
        delete root_tool;
        printf("=== \n");
    }

//    virtual void Init(const HistInfo2d* const hist_info) = 0;
    {
        printf("--- test Init \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistInfo2d* hi2d = new HistInfo2d;
        hi2d->InitSetByNbin(0.0, 4.0, 4, 0.0, 4.0, 4);
        HistDataNerr2d* hd2d = new HistDataNerr2d("hd2d");
        hd2d->Init(hi2d);
        hd2d->SetConst(2.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp2.png");

        delete hi2d;
        delete th2d;
        delete hd2d;
        delete root_tool;
        printf("=== \n");
    }
   
//    void SetOvalArr(const DataArray1d* const oval_arr);
//    void SetConst(double constant);    
    {
        printf("--- test SetOvalArr(const DataArray1d* const oval_arr) \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        DataArrayNerr1d* oval_arr = new DataArrayNerr1d;
        oval_arr->Init(16);
        oval_arr->SetConst(3.0);
        
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->SetOvalArr(oval_arr);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp3.png");

        delete th2d;
        delete hd2d;
        delete root_tool;
        printf("=== \n");
    }
    
//    void SetOvalArr(long ndata, const double* const val);
    {
        printf("--- test SetOvalArr(long ndata, const double* const val) \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        double val[16];
        for(long iarr = 0; iarr < 16; iarr ++){
            val[iarr] = iarr + 1;
        }
        hd2d->SetOvalArr(16, val);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp4.png");

        delete root_tool;
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }
   
//    void SetOvalArr(vector<double> val);
    {
        printf("--- test SetOvalArr(vector<double> val) \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        vector<double> val(16);
        for(long iarr = 0; iarr < 16; iarr ++){
            val[iarr] = iarr + 1;
        }
        hd2d->SetOvalArr(val);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp5.png");

        delete root_tool;
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }

//    void SetOvalElm(long ibin_xval, long ibin_yval, double oval);
    {
        printf("--- test SetOvalElm \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        for(long iarr = 0; iarr < 16; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             2*(iarr + 1));
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp6.png");

        delete root_tool;
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }
    
//    void Fill(double xval, double yval);
    {
        printf("--- test Fill(double xval, double yval) \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->Fill(2.5, 3.5);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp7.png");

        delete root_tool;
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }

    
//    void Fill(double xval, double yval, double weight);
    {
        printf("--- test Fill(double xval, double yval, double weight)\n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->Fill(2.5, 3.5, 5.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp8.png");

        delete root_tool;
        delete hd2d;
        delete th2d;

        printf("=== \n");
    }
   
//    void FillByLarger(double xval, double yval, double oval);
    {
        printf("--- test FillByLarger(double xval, double yval, double oval)\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->Fill(2.5, 3.5, 5.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));
        hd2d->FillByLarger(2.5, 3.5, 4.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));
        hd2d->FillByLarger(2.5, 3.5, 9.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));        
        
        delete hd2d;

        printf("=== \n");
    }

   
//    void FillBySmaller(double xval, double yval, double oval);
    {
        printf("--- test FillBySmaller(double xval, double yval, double oval)\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        hd2d->Fill(2.5, 3.5, 5.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));
        hd2d->FillBySmaller(2.5, 3.5, 4.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));
        hd2d->FillBySmaller(2.5, 3.5, 9.0);
        printf("oval = %e\n", hd2d->GetOvalElmAtXY(2.5, 3.5));        
        
        delete hd2d;

        printf("=== \n");
    }

    
//    void SetOneAtIntervalXY(const Interval* const interval_x,
//                            const Interval* const interval_y);
    {
        printf("--- test SetOneAtIntervalXY\n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        double tstart_x[3];
        double tstop_x[3];
        tstart_x[0] = 2.0; tstop_x[0] = 3.0;
        tstart_x[1] = 3.5; tstop_x[1] = 7.0;
        tstart_x[2] = 8.0; tstop_x[2] = 9.0;
        double tstart_y[3];
        double tstop_y[3];
        tstart_y[0] = 2.0; tstop_y[0] = 3.0;
        tstart_y[1] = 3.5; tstop_y[1] = 7.0;
        tstart_y[2] = 8.0; tstop_y[2] = 9.0;
        Interval* int_x = new Interval;
        Interval* int_y = new Interval;
        int_x->Init(3);
        int_x->Set(3, tstart_x, tstop_x);
        int_y->Init(3);
        int_y->Set(3, tstart_y, tstop_y);


        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(300, 0.0, 10.0, 300, 0.0, 10.0);
        hd2d->SetOneAtIntervalXY(int_x, int_y);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("colz");
        root_tool->GetTCanvas()->Print("temp9.png");

        delete root_tool;
        delete hd2d;
        delete th2d;
        delete int_x;
        delete int_y;
        
        printf("=== \n");
    }
    
  
//    void SetByFunc(const MirFunc* const func, const double* const par);
    {
        printf("--- test SetByFunc\n");
        FuncTest* func = new FuncTest;
        double par[3] = {100.0, 2.0, 3.0};
        
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(300, 0.0, 10.0, 300, 0.0, 10.0);
        hd2d->SetByFunc(func, par);

        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("colz");
        root_tool->GetTCanvas()->Print("temp9.png");

        delete root_tool;
        delete hd2d;
        delete th2d;
        delete func;
        
        printf("=== \n");
    }
   
//    void Copy(const HistData2d* const org);
    {
        printf("--- test Copy \n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
        for(long iarr = 0; iarr < 16; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             2*(iarr + 1));
        }
        TH2D* th2d = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d->Draw("text");
        root_tool->GetTCanvas()->Print("temp1.png");

        HistDataNerr2d* hd2d_new = new HistDataNerr2d;
        hd2d_new->Copy(hd2d);
        TH2D* th2d_new = hd2d->GenTH2D(0.0, 0.0, 0.0);
        th2d_new->Draw("text");
        root_tool->GetTCanvas()->Print("temp2.png");
        
        delete root_tool;
        delete hd2d;
        delete th2d;
        delete hd2d_new;
        delete th2d_new;        

        printf("=== \n");
    }

//    virtual void Load(string file) = 0;
    {
        printf("--- test Load \n");
//        // make temp.dat
//        HistDataNerr2d* hd2d = new HistDataNerr2d;
//        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
//        for(long iarr = 0; iarr < 16; iarr ++){
//            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
//                             hd2d->GetHi2d()->GetIbinY(iarr),
//                             2*(iarr + 1));
//        }
//        hd2d->Save("temp.dat", "x,y,z");
//        delete hd2d;

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Load("data/test_hist2d.dat");
        hd2d->PrintInfo(stdout);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);        

        delete hd2d;

        printf("=== \n");
    }
   
//    const HistInfo2d* const GetHi2d() const {return hi2d_;};
    {
        printf("--- test  GetHi2d()\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(3, 0.0, 3.0, 3, 0.0, 3.0);
        for(long iarr = 0; iarr < 9; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             2*(iarr + 1));
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        hd2d->GetHi2d()->Print(stdout);
        

        delete hd2d;


        printf("=== \n");
    }

   
//    virtual const DataArray1d* const GetOvalArr() const = 0;
    {
        printf("--- test  GetOvalArr()\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(3, 0.0, 3.0, 3, 0.0, 3.0);
        for(long iarr = 0; iarr < 9; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             2*(iarr + 1));
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        hd2d->GetOvalArr()->PrintData(stdout, 1, 0.0);

        delete hd2d;


        printf("=== \n");
    }

//    long GetNbinX() const {return GetHi2d()->GetNbinX();};
//    long GetNbinY() const {return GetHi2d()->GetNbinY();};
//    long GetNbin()  const {return GetHi2d()->GetNbin();};
//    double GetXvalLo() const {return GetHi2d()->GetLoX();};
//    double GetXvalUp() const {return GetHi2d()->GetUpX();};
//    double GetYvalLo() const {return GetHi2d()->GetLoY();};
//    double GetYvalUp() const {return GetHi2d()->GetUpY();};
//    double GetXvalMd() const {return GetHi2d()->GetMdX();};
//    double GetYvalMd() const {return GetHi2d()->GetMdY();};
//    double GetXvalFullWidth() const {return GetHi2d()->GetFullWidthX();};
//    double GetYvalFullWidth() const {return GetHi2d()->GetFullWidthY();};
//    double GetBinWidthX() const {return GetHi2d()->GetBinWidthX();};
//    double GetBinWidthY() const {return GetHi2d()->GetBinWidthY();};
//    double GetBinArea() const {return GetHi2d()->GetBinArea();};
//    double GetFullArea() const {return GetHi2d()->GetFullArea();};
    {
        printf("--- test GetNbinX() \n");
        printf("--- test GetNbinY() \n");
        printf("--- test GetNbin()  \n");
        printf("--- test GetXvalLo() \n");
        printf("--- test GetXvalUp() \n");
        printf("--- test GetYvalLo() \n");
        printf("--- test GetYvalUp() \n");
        printf("--- test GetXvalMd() \n");
        printf("--- test GetYvalMd() \n");
        printf("--- test GetXvalFullWidth() \n");
        printf("--- test GetYvalFullWidth() \n");
        printf("--- test GetBinWidthX() \n");
        printf("--- test GetBinWidthY() \n");
        printf("--- test GetBinArea()   \n");
        printf("--- test GetFullArea()  \n");        

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(6, 0.0, 3.0, 4, 0.0, 4.0);
        for(long iarr = 0; iarr < 24; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             iarr + 1);
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        printf("hd2d->GetNbinX() = %ld\n", hd2d->GetNbinX());
        printf("hd2d->GetNbinY() = %ld\n", hd2d->GetNbinY());
        printf("hd2d->GetNbin() = %ld\n", hd2d->GetNbin());        
        printf("hd2d->GetXvalLo() = %e\n", hd2d->GetXvalLo());
        printf("hd2d->GetXvalUp() = %e\n", hd2d->GetXvalUp());        
        printf("hd2d->GetYvalLo() = %e\n", hd2d->GetYvalLo());
        printf("hd2d->GetYvalUp() = %e\n", hd2d->GetYvalUp());        
        printf("hd2d->GetXvalMd() = %e\n", hd2d->GetXvalMd());
        printf("hd2d->GetYvalMd() = %e\n", hd2d->GetYvalMd());
        printf("hd2d->GetXvalFullWidth() = %e\n", hd2d->GetXvalFullWidth());
        printf("hd2d->GetYvalFullWidth() = %e\n", hd2d->GetYvalFullWidth());
        printf("hd2d->GetBinWidthX() = %e\n", hd2d->GetBinWidthX());                        
        printf("hd2d->GetBinWidthY() = %e\n", hd2d->GetBinWidthY());
        printf("hd2d->GetBinArea() = %e\n", hd2d->GetBinArea());
        printf("hd2d->GetFullArea() = %e\n", hd2d->GetFullArea());
        
        delete hd2d;

        printf("=== \n");
    }

//    double GetOvalElm(long ibin_xval, long ibin_yval) const;
    {
        printf("--- test GetOvalElm(long ibin_xval, long ibin_yval)\n");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        for(long iarr = 0; iarr < 6; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             iarr + 1);
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        for(long iarr = 0; iarr < hd2d->GetNbin(); iarr ++){
            long ibin_xval = hd2d->GetHi2d()->GetIbinX(iarr);
            long ibin_yval = hd2d->GetHi2d()->GetIbinY(iarr);
            printf("hd2d->GetOvalElm(%ld, %ld) = %e\n",
                   ibin_xval, ibin_yval,
                   hd2d->GetOvalElm(ibin_xval, ibin_yval));
        }
        
        delete hd2d;

        printf("=== \n");
    }
    
//    double GetOvalElmAtXY(double xval, double yval) const;
    {
        printf("--- test GetOvalElmAtXY(double xval, double yval)\n");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        for(long iarr = 0; iarr < 6; iarr ++){
            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
                             hd2d->GetHi2d()->GetIbinY(iarr),
                             iarr + 1);
        }
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        printf("hd2d->GetOvalElmAtXY(1.5, 2.5) = %e\n",
               hd2d->GetOvalElmAtXY(1.5, 2.5));
        
        delete hd2d;

        printf("=== \n");
    }

//    double GetXvalAtOvalMin() const;
//    double GetXvalAtOvalMax() const;
//    double GetYvalAtOvalMin() const;
//    double GetYvalAtOvalMax() const;
    {
        printf("--- test GetXvalAtOvalMin()\n");
        printf("--- test GetXvalAtOvalMax()\n");
        printf("--- test GetYvalAtOvalMin()\n");
        printf("--- test GetYvalAtOvalMax()\n");

        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        printf("hd2d->GetXvalAtOvalMin() = %e\n",
               hd2d->GetXvalAtOvalMin());        
        printf("hd2d->GetXvalAtOvalMax() = %e\n",
               hd2d->GetXvalAtOvalMax());
        printf("hd2d->GetYvalAtOvalMin() = %e\n",
               hd2d->GetYvalAtOvalMin());
        printf("hd2d->GetYvalAtOvalMax() = %e\n",
               hd2d->GetYvalAtOvalMax());                
        delete hd2d;

        printf("=== \n");
    }

   
//    void GenXYvalArr(double** const xval_arr_ptr,
//                     double** const yval_arr_ptr,
//                     long* const nbin_ptr) const;
//    void GenOvalArr(double** const oval_arr_ptr,
//                    long* const nbin_ptr) const;
    {
        printf("--- test GenXYvalArr\n");
        printf("--- test GenOvalArr\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);
        double* xval_arr = NULL;
        double* yval_arr = NULL;
        double* oval_arr = NULL;
        long nbin_xy = 0;
        long nbin_o = 0;
        hd2d->GenXYvalArr(&xval_arr, &yval_arr, &nbin_xy);
        hd2d->GenOvalArr(&oval_arr, &nbin_o);

        printf("nbin_xy = %ld\n", nbin_xy);
        printf("nbin_o = %ld\n", nbin_o);
        for(long ibin = 0; ibin < nbin_xy; ibin ++){
            printf("%ld: xval_arr, yval_arr, oval_arr = %e, %e, %e\n",
                   ibin, xval_arr[ibin], yval_arr[ibin], oval_arr[ibin]);
        }
        delete [] xval_arr;
        delete [] yval_arr;
        delete [] oval_arr;

        delete hd2d;

        printf("=== \n");
    }

//    void Save(string outfile, string format,
//              double offset_xval = 0.0,
//              double offset_yval = 0.0,
//              double offset_oval = 0.0) const;
    {
        printf("--- test Save\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->Save("temp.dat", "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;

        printf("=== \n");
    }
    
//    void SaveData(string outfile, string format,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0) const;
    {
        printf("--- test SaveData\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SaveData("temp.dat", "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;

        printf("=== \n");
    }
    
//    void PrintInfo(FILE* fp) const;
    {
        printf("--- test PrintInfo\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->PrintInfo(stdout);

        delete hd2d;

        printf("=== \n");
    }

    
//    virtual void PrintData(FILE* fp, string format,
//                           double offset_xval,
//                           double offset_yval,
//                           double offset_oval) const = 0;
    {
        printf("--- test PrintData\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d;
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);

        delete hd2d;

        printf("=== \n");
    }

    
//    void SaveRoot(string outfile,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0) const;
    {
        printf("--- test SaveRoot\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);
        hd2d->SaveRoot("temp.root");

        delete hd2d;

        // TFile* f = new TFile("temp.root");
        // f->ls();
        // TH2D* h = (TH2D*) f->Get("aaa");
        // h->Draw("LEGO");
        printf("=== \n");
    }


//    void MkTH2Fig(string outfig,
//                  MirRootTool* const root_tool,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0,
//                  string title_xaxis = "",
//                  string title_yaxis = "",
//                  string title_oaxis = "",
//                  string style = "def") const;
    {
        printf("--- test MkTH2Fig\n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");        
        
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        hd2d->MkTH2Fig("temp.png", root_tool);
        delete hd2d;
        delete root_tool;

        printf("=== \n");
    }

   
//    void MkTH2FigZrange(string outfig,
//                        MirRootTool* const root_tool,
//                        double zrange_lo, double zrange_up,
//                        double offset_xval = 0.0,
//                        double offset_yval = 0.0,
//                        double offset_oval = 0.0,
//                        string title_xaxis = "",
//                        string title_yaxis = "",
//                        string title_oaxis = "") const;
    {
        printf("--- test MkTH2FigZrange\n");
        MirRootTool* root_tool = new MirRootTool;
        root_tool->InitTCanvas("pub");        
        
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        hd2d->MkTH2FigZrange("temp.png", root_tool, 2.0, 5.0);
        delete hd2d;
        delete root_tool;

        printf("=== \n");
    }

//    GraphDataNerr2d* const GenRandomEvt(int rand_seed = 1) const;
    {
        printf("--- test GenRandomEvt\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        GraphDataNerr2d* gd2d = hd2d->GenRandomEvt(1);
        gd2d->PrintData(stdout, "x,y", 0.0, 0.0);
        
        delete hd2d;
        delete gd2d;

        printf("=== \n");
    }


//    double GetOffsetXFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetXFromTag(string offset_tag)\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        printf("st = %e\n", hd2d->GetOffsetXFromTag("st"));
        printf("md = %e\n", hd2d->GetOffsetXFromTag("md"));
        printf("ed = %e\n", hd2d->GetOffsetXFromTag("ed"));
        printf("no = %e\n", hd2d->GetOffsetXFromTag("no"));
        printf("val = %e\n", hd2d->GetOffsetXFromTag("7.77"));
        
        delete hd2d;

        printf("=== \n");
    }

//    double GetOffsetYFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetYFromTag(string offset_tag)\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        printf("st = %e\n", hd2d->GetOffsetYFromTag("st"));
        printf("md = %e\n", hd2d->GetOffsetYFromTag("md"));
        printf("ed = %e\n", hd2d->GetOffsetYFromTag("ed"));
        printf("no = %e\n", hd2d->GetOffsetYFromTag("no"));
        printf("val = %e\n", hd2d->GetOffsetYFromTag("7.77"));
        
        delete hd2d;

        printf("=== \n");
    }

  
//    double GetOffsetOFromTag(string offset_tag) const;
    {
        printf("--- test GetOffsetOFromTag(string offset_tag)\n");
        HistDataNerr2d* hd2d = new HistDataNerr2d("aaa");
        hd2d->Init(2, 0.0, 2.0, 3, 0.0, 3.0);
        hd2d->SetOvalElm(0, 0, 1.0);
        hd2d->SetOvalElm(1, 0, 2.0);
        hd2d->SetOvalElm(0, 1, 3.0);
        hd2d->SetOvalElm(1, 1, 4.0);
        hd2d->SetOvalElm(0, 2, 5.0);
        hd2d->SetOvalElm(1, 2, 6.0);

        printf("st = %e\n", hd2d->GetOffsetOFromTag("st"));
        printf("md = %e\n", hd2d->GetOffsetOFromTag("md"));
        printf("ed = %e\n", hd2d->GetOffsetOFromTag("ed"));
        printf("no = %e\n", hd2d->GetOffsetOFromTag("no"));
        printf("val = %e\n", hd2d->GetOffsetOFromTag("7.77"));
        
        delete hd2d;

        printf("=== \n");
    }
    
//    static void ReadInfo(string file, 
//                         long* nbin_xval_ptr,
//                         double* xval_lo_ptr,
//                         double* xval_up_ptr,
//                         long* nbin_yval_ptr,
//                         double* yval_lo_ptr,
//                         double* yval_up_ptr,
//                         string* format_ptr);
    {
        printf("--- test ReadInfo\n");
        long nbin_xval = 0;
        double xval_lo = 0.0;
        double xval_up = 0.0;
        long nbin_yval = 0;
        double yval_lo = 0.0;
        double yval_up = 0.0;
        string format = "";
        HistData2d::ReadInfo("data/test_hist2d.dat",
                             &nbin_xval, &xval_lo, &xval_up,
                             &nbin_yval, &yval_lo, &yval_up,
                             &format);
        printf("nbin_xval = %ld\n", nbin_xval);
        printf("xval_lo   = %e\n", xval_lo);
        printf("xval_up   = %e\n", xval_up);
        printf("nbin_yval = %ld\n", nbin_yval);
        printf("yval_lo   = %e\n", yval_lo);
        printf("yval_up   = %e\n", yval_up);
        printf("format    = %s\n", format.c_str());
        
        printf("=== \n");
    }

    
    return status_prog;
}
