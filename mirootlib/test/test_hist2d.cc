#include "mi_str.h"
#include "mi_iolib.h"
#include "mir_hist2d_nerr.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[])
{
    int status_prog = kRetNormal;


    {
        printf("--- test Init \n");
        HistDataNerr1d* hd1d = new HistDataNerr1d("hd1d");
        hd1d->Init(4, 0.0, 4.0);
        hd1d->PrintData(stdout, "x,y", 0.0, 0.0);

        delete hd1d;
        printf("=== \n");
    }

//    virtual void Init(long nbin_xval, double xval_lo, double xval_up,
//                      long nbin_yval, double yval_lo, double yval_up) = 0;
//    virtual void Init(const HistInfo2d* const hist_info) = 0;
//    void SetOvalArr(const DataArray1d* const oval_arr);
//    void SetOvalArr(long ndata, const double* const val);
//    void SetOvalArr(vector<double> val);
//    void SetOvalElm(long ibin_xval, long ibin_yval, double oval);
//    void Fill(double xval, double yval);
//    void Fill(double xval, double yval, double weight);
//    void FillByLarger(double xval, double yval, double oval);
//    void FillBySmaller(double xval, double yval, double oval);
//    void SetConst(double constant);
//    void SetOneAtIntervalXY(const Interval* const interval_x,
//                            const Interval* const interval_y);
//    void SetByFunc(const MirFunc* const func, const double* const par);
//    void Copy(const HistData2d* const org);
//    virtual void Load(string file) = 0;
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
