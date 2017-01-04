#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

#include "mir_hist2d.h"

class HistDataNerr2d : public HistData2d{
public:
    explicit HistDataNerr2d(string title = "") :
        HistData2d("HistDataNerr2d", title),
        oval_arr_(NULL) {}
    HistDataNerr2d(string class_name, string title) :
        HistData2d(class_name, title),
        oval_arr_(NULL) {}
    virtual ~HistDataNerr2d() {
        Null();
    }
   
    // Set
    void Set(const HistData2d* const org);
    void Set(const HistInfo2d* const hi2d,
             const DataArray1d* const oval_arr);
    void Set(long nbin_xval, double xval_lo, double xval_up,
             long nbin_yval, double yval_lo, double yval_up,
             const DataArray1d* const oval_arr);
    
    // SetData
    void SetData(const DataArray1d* const oval_arr);

    // set each
    void SetData(long nbin_xval, long nbin_yval,
                 const double* const oval);
    
    // InitSet
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 long nbin_yval, double yval_lo, double yval_up,
                 const DataArray1d* const oval_arr);
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 long nbin_yval, double yval_lo, double yval_up,
                 const double* const oval);

    // kinds of Set
    void SetOvalElm(long ibin_xval, long ibin_yval, double oval);

    void Fill(double xval, double yval);
    void Fill(double xval, double yval, double weight);
    void FillByMax(double xval, double yval, double oval);
    void FillByMin(double xval, double yval, double oval);

    void SetZero();
    void SetOne();
    void SetConst(double constant);
    void SetOneAtIntervalXY(const Interval* const interval_x,
                            const Interval* const interval_y);

    // Set by Func
    void SetByFunc(const MiFunc* const func, const double* const par);

    // // Init & Set by graph3d, only if xval_arr of graph3d is equally-spaced.
    // void InitSetByGraphData3d(const GraphData3d* const g3d);

    void Copy(const HistData2d* const org);
    HistDataNerr2d* const Clone() const;
    void Load(string file);

    //
    // operation
    //
    void Not(const HistDataNerr2d* const hist_data);
    void Scale(const HistDataNerr2d* const hist_data,
               double scale, double offset);

    void Min(const HistDataNerr2d* const hist_data1,
             const HistDataNerr2d* const hist_data2);
    void Min(const HistDataNerr2d* const* const hist_data_arr,
             int nhist);
    void Max(const HistDataNerr2d* const hist_data1,
             const HistDataNerr2d* const hist_data2);
    void Max(const HistDataNerr2d* const* const hist_data_arr,
             int nhist);
    void Add(const HistDataNerr2d* const hist_data1,
             const HistDataNerr2d* const hist_data2);
    void Add(const HistDataNerr2d* const* const hist_data_arr,
             int nhist);
    void Sub(const HistDataNerr2d* const hist_data1,
             const HistDataNerr2d* const hist_data2);
    void Mul(const HistDataNerr2d* const hist_data1,
             const HistDataNerr2d* const hist_data2);
    int  Div(const HistDataNerr2d* const hist_data_num,
             const HistDataNerr2d* const hist_data_den,
             vector<long>* const index_bad_vec_ptr);
    void AMean(const HistDataNerr2d* const hist_data1,
               const HistDataNerr2d* const hist_data2);
    void AMean(const HistDataNerr2d* const* const hist_data_arr,
               int nhist);

    // sub_add_ratio = (h1 - h2) / (h1 + h2)
    void SubAddRatio(const HistDataNerr2d* const hist_data1,
                     const HistDataNerr2d* const hist_data2);

    void Variance(const HistDataNerr2d* const* const hist_data_arr,
                  int nhist);
    void Stddev(const HistDataNerr2d* const* const hist_data_arr,
                int nhist);
    void UnbiasedVariance(const HistDataNerr2d* const* const hist_data_arr,
                          int nhist);
    void SqrtOfUnbiasedVariance(const HistDataNerr2d* const* const hist_data_arr,
                                int nhist);
    void RMS(const HistDataNerr2d* const* const hist_data_arr,
             int nhist);
    void Median(const HistDataNerr2d* const* const hist_data_arr,
                int nhist);

    //
    // const functions
    //

    // get
    const DataArray1d* const GetOvalArr() const {return oval_arr_;};
    long GetNbinX() const {return nbin_xval_;};
    long GetNbinY() const {return nbin_yval_;};
    long GetNbin()  const {return nbin_xval_ * nbin_yval_;};
    double GetXvalLo() const {return xval_lo_;};
    double GetXvalUp() const {return xval_up_;};
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
    DataArrayNerr1d* oval_arr_;
    long num_outer_;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

