#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_

#include "mir_data1d.h"
#include "mir_hist_info.h"

class HistDataNerr2d;
class HistDataSerr2d;
class HistDataTerr2d;

class HistData2d : public MiObject{
public:
    explicit HistData2d(string title = "") :
        MiObject("HistData2d", title),
        hist_info_(NULL) {}
    HistData2d(string class_name, string title) :
        MiObject(class_name, title),
        hist_info_(NULL) {}
    virtual ~HistData2d() {}
   
    // Init
    virtual void Init(long nbin_xval, double xval_lo, double xval_up,
                      long nbin_yval, double yval_lo, double yval_up) = 0;
    virtual void Init(const HistInfo2d* const hist_info) = 0;

    // Set
    virtual void Set(const HistData2d* const org);
    virtual void Set(long nbin_xval, double xval_lo, double xval_up,
                     long nbin_yval, double yval_lo, double yval_up,
                     const DataArray1d* const oval_arr);
    
    // SetInfo
    virtual void SetInfo(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up);
    // SetData
    virtual void SetData(const DataArray1d* const oval_arr);

    // set each
    virtual void SetData(long nbin_xval, long nbin_yval,
                         const double* const oval);
    virtual void SetData(long nbin_xval, long nbin_yval,
                         const double* const oval,
                         const double* const oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetData(long nbin_xval, long nbin_yval,
                         const double* const oval,
                         const double* const oval_terr_plus,
                         const double* const oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    // InitSet
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const DataArray1d* const oval_arr);
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const double* const oval);
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const double* const oval,
                         const double* const oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const double* const oval,
                         const double* const oval_terr_plus,
                         const double* const oval_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void InitSet(const TH2D* const th2d);


    // kinds of Set
    virtual void SetOvalElm(long ibin_xval, long ibin_yval, double oval);
    virtual void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrElm(long ibin_xval, long ibin_yval, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrPlusElm(long ibin_xval, long ibin_yval, double oval_terr_plus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrMinusElm(long ibin_xval, long ibin_yval, double oval_terr_minus)
        {MPrintErrVFunc; abort();};

    virtual void Fill(double xval, double yval);
    virtual void Fill(double xval, double yval, double weight);
    virtual void FillByMax(double xval, double yval, double oval);
    virtual void FillByMax(double xval, double yval,
                           double oval,
                           double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMax(double xval, double yval,
                           double oval,
                           double oval_terr_plus,
                           double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    virtual void FillByMin(double xval, double yval, double oval);
    virtual void FillByMin(double xval, double yval,
                           double oval,
                           double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMin(double xval, double yval,
                           double oval,
                           double oval_terr_plus,
                           double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    

    virtual void SetZero() = 0;
    virtual void SetOne() = 0;
    virtual void SetConst(double constant) = 0;
    virtual void SetOneAtIntervalXY(const Interval* const interval_x,
                                    const Interval* const interval_y) = 0;
    virtual void SetOvalErrArrByPoissonErr() = 0;

    // Set by Func
    virtual void SetByFunc(const MiFunc* const func, const double* const par) = 0;

    // Init & Set by graph3d, only if xval_arr of graph3d is equally-spaced.
    virtual void InitSetByGraphData3d(const GraphData3d* const g3d);

    virtual void Copy(const HistData2d* const org);
    virtual HistData2d* const Clone() const;
    
    virtual void Load(string file);
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         long* nbin_yval_ptr,
                         double* yval_lo_ptr,
                         double* yval_up_ptr,
                         string* format_ptr);

    //
    // operation
    //
    virtual void Not(const HistData2d* const hist_data) = 0;
    virtual void Scale(const HistData2d* const hist_data,
                       double scale, double offset) = 0;

    virtual void Min(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2) = 0;
    virtual void Min(const HistData2d* const* const hist_data_arr,
                     int nhist) = 0;
    virtual void Min(const HistDataSerr2d* const* const hist_data_arr,
                     int nhist) = 0;
    
    virtual void Max(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2) = 0;
    virtual void Max(const HistData2d* const* const hist_data_arr,
                     int nhist) = 0;
    virtual void Max(const HistDataSerr2d* const* const hist_data_arr,
                     int nhist) = 0;
    
    virtual void Add(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2) = 0;
    virtual void Add(const HistData2d* const* const hist_data_arr,
                     int nhist) = 0;
    virtual void Add(const HistDataSerr2d* const* const hist_data_arr,
                     int nhist) = 0;
    
    virtual void Sub(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2) = 0;
    virtual void Mul(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2) = 0;
    virtual int  Div(const HistData2d* const hist_data_num,
                     const HistData2d* const hist_data_den,
                     vector<long>* const index_bad_vec_ptr) = 0;
    virtual void AMean(const HistData2d* const hist_data1,
                       const HistData2d* const hist_data2) = 0;
    virtual void AMean(const HistData2d* const* const hist_data_arr,
                       int nhist) = 0;
    virtual void AMean(const HistDataSerr2d* const* const hist_data_arr,
                       int nhist) = 0;
    virtual int WMean(const HistDataSerr2d* const hist_data1,
                      const HistDataSerr2d* const hist_data2,
                      vector<long>* const index_bad_vec_ptr) = 0;
    virtual int WMean(const HistDataSerr2d* const* const hist_data_arr,
                      int nhist,
                      vector<long>* const index_bad_vec_ptr) = 0;

    // sub_add_ratio = (h1 - h2) / (h1 + h2)
    virtual void SubAddRatio(const HistData2d* const hist_data1,
                             const HistData2d* const hist_data2) = 0;
    virtual void Variance(const HistData2d* const* const hist_data_arr,
                          int nhist) = 0;
    virtual void Stddev(const HistData2d* const* const hist_data_arr,
                        int nhist) = 0;
    virtual void UnbiasedVariance(const HistData2d* const* const hist_data_arr,
                                  int nhist) = 0;
    virtual void SqrtOfUnbiasedVariance(const HistData2d* const* const hist_data_arr,
                                        int nhist) = 0;
    virtual void RMS(const HistData2d* const* const hist_data_arr,
                     int nhist) = 0;
    virtual void Median(const HistData2d* const* const hist_data_arr,
                        int nhist) = 0;

    //
    // const functions
    //

    // get
    virtual const DataArray1d* const GetOvalArr() const
        {return oval_arr_;};
    virtual long GetNbinX() const {return nbin_xval_;};
    virtual long GetNbinY() const {return nbin_yval_;};
    virtual long GetNbin()  const {return nbin_xval_ * nbin_yval_;};
    virtual double GetXvalLo() const {return xval_lo_;};
    virtual double GetXvalUp() const {return xval_up_;};
    double GetYvalLo() const {return yval_lo_;};
    double GetYvalUp() const {return yval_up_;};
    double GetXvalMd() const {return (xval_lo_ + xval_up_) / 2.0;};
    double GetYvalMd() const {return (yval_lo_ + yval_up_) / 2.0;};
    double GetXvalFullWidth() const {return xval_up_ - xval_lo_;};
    double GetYvalFullWidth() const {return yval_up_ - yval_lo_;};
    double GetFullArea() const {return GetXvalFullWidth() * GetYvalFullWidth();};
    double GetBinWidthX() const {return (xval_up_ - xval_lo_) / nbin_xval_;};
    double GetBinWidthY() const {return (yval_up_ - yval_lo_) / nbin_yval_;};
    double GetBinArea() const {return GetBinWidthX() * GetBinWidthY();};

    long GetIbin(long ibin_xval, long ibin_yval) const;
    long GetIbinX(long ibin) const;
    long GetIbinY(long ibin) const;
    long GetIbinXFromX(double xval) const;
    long GetIbinYFromY(double yval) const;
    long GetIbinFromXY(double xval, double yval) const;
    
    double GetBinCenterXFromIbinX(long ibin_xval) const;
    double GetBinCenterYFromIbinY(long ibin_yval) const;
    double GetBinCenterXFromIbin(long ibin) const;
    double GetBinCenterYFromIbin(long ibin) const;
    void GetBinCenterXYFromIbin(long ibin,
                                double* const xval_ptr,
                                double* const yval_ptr) const;

    long GetIbinX_WithHalfBinShifted(double xval) const;
    long GetIbinY_WithHalfBinShifted(double yval) const;

    
    // get internal of oval_arr_
    const double* const GetOvalArrDbl() const;
    virtual const double* const GetOvalSerrArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrPlusArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrMinusArrDbl() const
        {MPrintErrVFunc; abort();};
    
    double GetOvalElm(long ibin_xval, long ibin_yval) const;
    virtual double GetOvalSerrElm(long ibin_xval, long ibin_yval) const
        {MPrintErrVFunc; abort();};    
    virtual double GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const
        {MPrintErrVFunc; abort();};    
    virtual double GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const
        {MPrintErrVFunc; abort();};    
    
    double GetOvalElmAtXY(double xval, double yval) const;
    virtual double GetOvalSerrElmAtXY(double xval, double yval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElmAtXY(double xval, double yval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElmAtXY(double xval, double yval) const
        {MPrintErrVFunc; abort();};


    // stat
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    double GetYvalAtOvalMin() const;
    double GetYvalAtOvalMax() const;

    //
    // gen xval_arr, yval_arr, oval_arr
    //
    // By using GenXYvalArr() and GenOvalArr(),
    // orders of values in xval_arr[ibin], yval_arr[ibin], and oval_arr[ibin]
    // are the same, following ibin.
    //
    void GenXYvalArr(double** const xval_arr_ptr,
                     double** const yval_arr_ptr,
                     long* const nbin_ptr) const;
    void GenXYvalSerrArr(double** const xval_serr_arr_ptr,
                         double** const yval_serr_arr_ptr,
                         long* const nbin_ptr) const;
    void GenOvalArr(double** const oval_arr_ptr,
                    long* const nbin_ptr) const;
    virtual void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                long* const nbin_ptr) const
        {MPrintErrVFunc; abort();};
    virtual void GenOvalTerrArr(double** const oval_terr_plus_arr_ptr,
                                double** const oval_terr_minus_arr_ptr,
                                long* const nbin_ptr) const
        {MPrintErrVFunc; abort();};

    // calc_mode: "add", "integral", "amean", "min", "max"
    HistData1d* const GenProjectX(long ibin_ylo, long ibin_yup,
                                  string calc_mode) const;
    HistData1d* const GenProjectY(long ibin_xlo, long ibin_xup,
                                  string calc_mode) const;  
  
    double GetOvalIntPolLin(double xval, double yval) const;


    //
    // output
    //
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_yval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp, string format) const;    
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval = 0.0,
                           double offset_yval = 0.0,
                           double offset_oval = 0.0) const;
    void SaveRoot(string outfile,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0) const;


    virtual HistData2d* const GenHd2MaxInBin(long nbinx_new, long nbiny_new) const;
    virtual GraphData3d* const GenGraph3d() const;
    virtual TH2D* const GenTH2D(double offset_xval = 0.0,
                                double offset_yval = 0.0,
                                double offset_oval = 0.0,
                                string title_xaxis = "",
                                string title_yaxis = "",
                                string title_oaxis = "",
                                string style = "def") const;
    void MkTH2Fig(string outfig,
                  MxkwRootTool* const root_tool,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0,
                  string title_xaxis = "",
                  string title_yaxis = "",
                  string title_oaxis = "",
                  string style = "def") const;
    void MkTH2FigZrange(string outfig,
                        MxkwRootTool* const root_tool,
                        double zrange_lo, double zrange_up,
                        double offset_xval = 0.0,
                        double offset_yval = 0.0,
                        double offset_oval = 0.0,
                        string title_xaxis = "",
                        string title_yaxis = "",
                        string title_oaxis = "") const;

    // generate HistData2d adding margin region in x and y directions
    HistData2d* const GenHd2AddMargin(double margin_xval, double margin_yval) const;


    // poisson error
    virtual void FillRandom(const MxkwFunc* const func,
                            const MxkwFuncPar* const func_par,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MxkwFunc* const func,
                            const MxkwFuncPar* const func_par,
                            const MxkwFunc* const func_sigma,
                            const MxkwFuncPar* const func_par_sigma,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData2d* const hist_data,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};
    
    // generate events from histogram with poisson statistic
    GraphData2d* const GenRandomEvt(int rand_seed = 1) const;

    
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    virtual double GetOffsetOFromTag(string offset_tag) const;

    int IsAllOne() const {return GetOvalArr()->IsAllOne();};

    int IsValidIbinX(long ibin_xval) const;
    int IsValidIbinY(long ibin_yval) const;
    int IsValidRangeX(double xval) const;
    int IsValidRangeY(double yval) const;
    

   
private:
    // ibin_xval_ = 0, 1, ..., nbin_xval_
    // ibin_yval_ = 0, 1, ..., nbin_yval_
    // ibin = ibin_xval_ + nbin_xval_ * ibin_yval_
    
    HistInfo2d* hist_info_;

    virtual void Null() = 0;
    void NewOvalArrAsDataArray1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};

    int IsOvalNotNull() const;

    
    // calc_mode: "add", "integral", "amean", "min", "max"
    void GetProject(long ndata,
                    const double* const array,
                    string calc_mode, double bin_width,
                    double* const val_proj_ptr) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_
