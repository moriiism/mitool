#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_

#include "TH2D.h"

#include "mir_data1d.h"
#include "mir_hist_info.h"
#include "mir_interval.h"
#include "mir_func.h"
#include "mir_hist1d.h"
#include "mir_graph2d_nerr.h"

class HistDataNerr2d;
class HistDataSerr2d;
class HistDataTerr2d;

class HistData2d : public MiObject{
public:
    HistData2d(string class_name, string title) :
        MiObject(class_name, title),
        hi2d_(NULL),
        oval_arr_(NULL) {}
    virtual ~HistData2d() {}
   
    virtual void Init(long nbin_xval, double xval_lo, double xval_up,
                      long nbin_yval, double yval_lo, double yval_up) = 0;
    virtual void Init(const HistInfo2d* const hist_info) = 0;
    void SetOvalArr(const DataArray1d* const oval_arr);
    void SetOvalArr(long ndata, const double* const val);
    void SetOvalArr(vector<double> val);    
    virtual void SetOvalSerrArr(long ndata, const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalSerrArr(vector<double> val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(long ndata, const double* const val_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(vector<double> val_serr)
        {MPrintErrVFunc; abort();};    
    virtual void SetOvalTerrArr(long ndata,
                                const double* const val_terr_plus,
                                const double* const val_terr_minus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrArr(vector<double> val_terr_plus,
                                vector<double> val_terr_minus)
        {MPrintErrVFunc; abort();};    

    void SetOvalElm(long ibin_xval, long ibin_yval, double oval);
    virtual void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrElm(long ibin_xval, long ibin_yval, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrPlusElm(long ibin_xval, long ibin_yval, double oval_terr_plus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrMinusElm(long ibin_xval, long ibin_yval, double oval_terr_minus)
        {MPrintErrVFunc; abort();};

    void Fill(double xval, double yval);
    void Fill(double xval, double yval, double weight);
    void FillByLarger(double xval, double yval, double oval);
    virtual void FillByLarger(double xval, double yval,
                              double oval,
                              double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByLarger(double xval, double yval,
                              double oval,
                              double oval_terr_plus,
                              double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void FillBySmaller(double xval, double yval, double oval);
    virtual void FillBySmaller(double xval, double yval,
                               double oval,
                               double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillBySmaller(double xval, double yval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
        {MPrintErrVFunc; abort();};

    void SetConst(double constant);
    void SetOneAtIntervalXY(const Interval* const interval_x,
                            const Interval* const interval_y);
    virtual void SetOvalErrArrByPoissonErr()
        {MPrintErrVFunc; abort();};

    // Set by Func
    void SetByFunc(const MirFunc* const func, const double* const par);

    // Init & Set by graph3d, only if xval_arr of graph3d is equally-spaced.
    // virtual void InitSetByGraphData3d(const GraphData3d* const g3d);

    void Copy(const HistData2d* const org);
    virtual void Load(string file) = 0;

    const HistInfo2d* const GetHi2d() const {return hi2d_;};
    virtual const DataArray1d* const GetOvalArr() const = 0;

    long GetNbinX() const {return GetHi2d()->GetNbinX();};
    long GetNbinY() const {return GetHi2d()->GetNbinY();};
    long GetNbin()  const {return GetHi2d()->GetNbin();};
    double GetXvalLo() const {return GetHi2d()->GetLoX();};
    double GetXvalUp() const {return GetHi2d()->GetUpX();};
    double GetYvalLo() const {return GetHi2d()->GetLoY();};
    double GetYvalUp() const {return GetHi2d()->GetUpY();};
    double GetXvalMd() const {return GetHi2d()->GetMdX();};
    double GetYvalMd() const {return GetHi2d()->GetMdY();};
    double GetXvalFullWidth() const {return GetHi2d()->GetFullWidthX();};
    double GetYvalFullWidth() const {return GetHi2d()->GetFullWidthY();};
    double GetBinWidthX() const {return GetHi2d()->GetBinWidthX();};
    double GetBinWidthY() const {return GetHi2d()->GetBinWidthY();};
    double GetBinArea() const {return GetHi2d()->GetBinArea();};
    double GetFullArea() const {return GetHi2d()->GetFullArea();};

    // get element
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
    

//    // calc_mode: "add", "integral", "amean", "min", "max"
//    HistData1d* const GenProjectX(long ibin_ylo, long ibin_yup,
//                                  string calc_mode) const;
//    HistData1d* const GenProjectY(long ibin_xlo, long ibin_xup,
//                                  string calc_mode) const;  

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
    void PrintInfo(FILE* fp) const;    
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_yval,
                           double offset_oval) const = 0;
    void SaveRoot(string outfile,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0) const;


//    virtual HistData2d* const GenHd2MaxInBin(long nbinx_new, long nbiny_new) const = 0;
    // virtual GraphData3d* const GenGraph3d() const = 0;
    virtual TH2D* const GenTH2D(double offset_xval,
                                double offset_yval,
                                double offset_oval) const
        {MPrintErrVFunc; abort();};
        
    void MkTH2Fig(string outfig,
                  MirRootTool* const root_tool,
                  double offset_xval = 0.0,
                  double offset_yval = 0.0,
                  double offset_oval = 0.0,
                  string title_xaxis = "",
                  string title_yaxis = "",
                  string title_oaxis = "",
                  string style = "def") const;
    void MkTH2FigZrange(string outfig,
                        MirRootTool* const root_tool,
                        double zrange_lo, double zrange_up,
                        double offset_xval = 0.0,
                        double offset_yval = 0.0,
                        double offset_oval = 0.0,
                        string title_xaxis = "",
                        string title_yaxis = "",
                        string title_oaxis = "") const;

    // generate HistData2d adding margin region in x and y directions
//    virtual HistData2d* const GenHd2AddMargin(double margin_xval, double margin_yval) const = 0;

    // poisson error
    virtual void FillRandom(const MirFunc* const func,
                            const MirFuncPar* const func_par,
                            int rand_seed)
        {MPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MirFunc* const func,
                            const MirFuncPar* const func_par,
                            const MirFunc* const func_sigma,
                            const MirFuncPar* const func_par_sigma,
                            int rand_seed)
        {MPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData2d* const hist_data,
                            int rand_seed)
        {MPrintErrVFunc; abort();};
    
    // generate events from histogram with poisson statistic
    GraphDataNerr2d* const GenRandomEvt(int rand_seed = 1) const;

    
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetYFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    //
    // static
    //
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         long* nbin_yval_ptr,
                         double* yval_lo_ptr,
                         double* yval_up_ptr,
                         string* format_ptr);

protected:
    void NullHistData2d();
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    void NewHi2d();
    HistInfo2d* GetHi2dNonConst() const {return hi2d_;};
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};
    void IsHi2dNotNull() const;
    void IsOvalArrNotNull() const;
    void IsValidIbinX(long ibin_xval) const;
    void IsValidIbinY(long ibin_yval) const;
    void IsValidRangeX(double xval) const;
    void IsValidRangeY(double yval) const;
    
private:
    // ibin_xval_ = 0, 1, ..., nbin_xval_
    // ibin_yval_ = 0, 1, ..., nbin_yval_
    // ibin = ibin_xval_ + nbin_xval_ * ibin_yval_
    
    HistInfo2d* hi2d_;
    DataArray1d* oval_arr_;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_H_
