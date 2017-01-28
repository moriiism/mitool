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
    double ans = par[0] + par[1] * argx + par[2] * pow(argy, 2.);
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

////    virtual void Load(string file) = 0;
//    {
//        printf("--- test Load \n");
////        // make temp.dat
////        HistDataNerr2d* hd2d = new HistDataNerr2d;
////        hd2d->Init(4, 0.0, 4.0, 4, 0.0, 4.0);
////        for(long iarr = 0; iarr < 16; iarr ++){
////            hd2d->SetOvalElm(hd2d->GetHi2d()->GetIbinX(iarr),
////                             hd2d->GetHi2d()->GetIbinY(iarr),
////                             2*(iarr + 1));
////        }
////        hd2d->Save("temp.dat", "x,y,z");
////        delete hd2d;
//
//        HistDataNerr2d* hd2d = new HistDataNerr2d;
//        hd2d->Load("data/test_hist2d.dat");
//        hd2d->PrintData(stdout, "x,y,z", 0.0, 0.0, 0.0);        
//
//        delete hd2d;
//
//        printf("=== \n");
//    }

// ----> Load is not yet implimented.
   

    
//
//    const HistInfo2d* const GetHi2d() const {return hi2d_;};
//    virtual const DataArray1d* const GetOvalArr() const = 0;

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
//
//    // get element
//    double GetOvalElm(long ibin_xval, long ibin_yval) const;
//    double GetOvalElmAtXY(double xval, double yval) const;
//    double GetXvalAtOvalMax() const;
//    double GetYvalAtOvalMin() const;
//    double GetYvalAtOvalMax() const;

//    void GenXYvalArr(double** const xval_arr_ptr,
//                     double** const yval_arr_ptr,
//                     long* const nbin_ptr) const;
//    void GenXYvalSerrArr(double** const xval_serr_arr_ptr,
//                         double** const yval_serr_arr_ptr,
//                         long* const nbin_ptr) const;
//    void GenOvalArr(double** const oval_arr_ptr,
//                    long* const nbin_ptr) const;
//    double GetOvalIntPolLin(double xval, double yval) const;
//
//    void Save(string outfile, string format,
//              double offset_xval = 0.0,
//              double offset_yval = 0.0,
//              double offset_oval = 0.0) const;
//    void SaveData(string outfile, string format,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0) const;
//    void PrintInfo(FILE* fp) const;    
//    virtual void PrintData(FILE* fp, string format,
//                           double offset_xval,
//                           double offset_yval,
//                           double offset_oval) const = 0;
//    void SaveRoot(string outfile,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0) const;
//
//
////    virtual HistData2d* const GenHd2MaxInBin(long nbinx_new, long nbiny_new) const = 0;
//    virtual TH2D* const GenTH2D(double offset_xval,
//                                double offset_yval,
//                                double offset_oval) const
//        {MPrintErrVFunc; abort();};
//        
//    void MkTH2Fig(string outfig,
//                  MirRootTool* const root_tool,
//                  double offset_xval = 0.0,
//                  double offset_yval = 0.0,
//                  double offset_oval = 0.0,
//                  string title_xaxis = "",
//                  string title_yaxis = "",
//                  string title_oaxis = "",
//                  string style = "def") const;
//    void MkTH2FigZrange(string outfig,
//                        MirRootTool* const root_tool,
//                        double zrange_lo, double zrange_up,
//                        double offset_xval = 0.0,
//                        double offset_yval = 0.0,
//                        double offset_oval = 0.0,
//                        string title_xaxis = "",
//                        string title_yaxis = "",
//                        string title_oaxis = "") const;
//
//    // generate HistData2d adding margin region in x and y directions
////    virtual HistData2d* const GenHd2AddMargin(double margin_xval, double margin_yval) const = 0;
//
//    // poisson error
//    virtual void FillRandom(const MirFunc* const func,
//                            const double* const func_par,
//                            int rand_seed)
//        {MPrintErrVFunc; abort();};
//
//    // gaussian error
//    virtual void FillRandom(const MirFunc* const func,
//                            const double* const func_par,
//                            const MirFunc* const func_sigma,
//                            const double* const func_par_sigma,
//                            int rand_seed)
//        {MPrintErrVFunc; abort();};    
//
//    // poisson error
//    virtual void FillRandom(const HistData2d* const hist_data,
//                            int rand_seed)
//        {MPrintErrVFunc; abort();};
//    
//    // generate events from histogram with poisson statistic
//    GraphDataNerr2d* const GenRandomEvt(int rand_seed = 1) const;
//
//    
//    double GetOffsetXFromTag(string offset_tag) const;
//    double GetOffsetYFromTag(string offset_tag) const;
//    double GetOffsetOFromTag(string offset_tag) const;
//
//    //
//    // static
//    //
//    static void ReadInfo(string file, 
//                         long* nbin_xval_ptr,
//                         double* xval_lo_ptr,
//                         double* xval_up_ptr,
//                         long* nbin_yval_ptr,
//                         double* yval_lo_ptr,
//                         double* yval_up_ptr,
//                         string* format_ptr);
//
    
    return status_prog;
}
