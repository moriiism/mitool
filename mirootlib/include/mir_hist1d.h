#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_H_

#include "TH1D.h"
#include "TPaletteAxis.h"
#include "TRandom3.h"

#include "mir_graph2d.h"
#include "mir_hist_info.h"
#include "mir_root_tool.h"

class HistDataNerr1d;
class HistDataSerr1d;
class HistDataTerr1d;

class HistData1d : public MiObject{
public:
    HistData1d(string class_name, string title) :
        MiObject(class_name, title),
        hi1d_(NULL),
        oval_arr_(NULL) {}
    virtual ~HistData1d() {}
   
    virtual void Init(long nbin_xval,
                      double xval_lo,
                      double xval_up) = 0;
    virtual void Init(const HistInfo1d* const hist_info) = 0;
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
    
    void SetOvalElm(long ibin, double oval);
    virtual void SetOvalSerrElm(long ibin, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrElm(long ibin, double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrPlusElm(long ibin, double oval_terr_plus)
        {MPrintErrVFunc; abort();};
    virtual void SetOvalTerrMinusElm(long ibin, double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void Fill(double xval);
    void Fill(double xval, double weight);
    void FillByLarger(double xval, double oval);
    virtual void FillByLarger(double xval,
                              double oval,
                              double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByLarger(double xval,
                              double oval,
                              double oval_terr_plus,
                              double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void FillBySmaller(double xval, double oval);
    virtual void FillBySmaller(double xval,
                               double oval,
                               double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillBySmaller(double xval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void SetConst(double constant);
    void SetOneAtInterval(const Interval* const interval);
    void SetFracAtInterval(const Interval* const interval);

    virtual void SetOvalErrArrByPoissonErr()
        {MPrintErrVFunc; abort();};
    
    void SetByFunc(const MirFunc* const func, const double* const par);

    // set by amean of graph data
    void SetByGraphData2d(const GraphData2d* const g2d);
    
    // Init & Set by graph2d, only if xval_arr of graph2d is equally-spaced.
    void InitSetByGraphData2d(const GraphData2d* const g2d);
    
    // Init & Set by graph2d_serr,
    // only if xval_arr of graph2d_serr is equally-spaced and
    // appropriate errors.
    void InitSetByGraphData2dSerr(const GraphDataSerr2d* const g2d);

    void Copy(const HistData1d* const org);
    virtual void Load(string file) = 0;

    //
    // const functions
    //

    // get
    const HistInfo1d* const GetHi1d() const {return hi1d_;};
    virtual const DataArray1d* const GetOvalArr() const = 0;
    
    long GetNbinX() const {return GetHi1d()->GetNbin();};
    double GetXvalLo() const {return GetHi1d()->GetLo();};
    double GetXvalUp() const {return GetHi1d()->GetUp();};
    double GetXvalMd() const {return GetHi1d()->GetMd();};
    double GetXvalFullWidth() const {return GetHi1d()->GetFullWidth();};
    double GetXvalBinWidth() const {return GetHi1d()->GetBinWidth();};

    // get element
    double GetOvalElm(long ibin) const;
    double GetOvalElmAtX(double xval) const;
    virtual double GetOvalSerrElm(long ibin) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalSerrElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElm(long ibin) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElm(long ibin) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;

    void GenXvalArr(double** const xval_arr_ptr,
                    long* const nbin_ptr) const;
    void GenXvalSerrArr(double** const xval_serr_arr_ptr,
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

    long GetIbin(double xval) const;
    double GetBinCenter(long ibin) const;
    double GetBinLo(long ibin) const;
    double GetBinUp(long ibin) const;
    long GetIbin_WithHalfBinShifted(double val) const;
    double GetOvalIntPolLin(double xval) const;
    double GetIntegral(double xval_lo, double xval_up) const;

    
    //
    // output
    //
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_oval) const = 0;
    void SaveRoot(string outfile,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;

    virtual HistData1d* const GenHd1MaxInBin(long nbin_new) const = 0;
    virtual GraphData2d* const GenGraph2d() const = 0;
    virtual TH1D* const GenTH1D(double offset_xval,
                                double offset_oval) const = 0;
    virtual void MkTH1Fig(string outfig,
                          MirRootTool* const root_tool,
                          double offset_xval,
                          double offset_oval) const = 0;

    // poisson error
    virtual void FillRandom(const MirFunc* const func,
                            const double* const func_par,
                            int rand_seed)
        {MPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MirFunc* const func,
                            const double* const func_par,
                            const MirFunc* const func_sigma,
                            const double* const func_par_sigma,
                            int rand_seed)
        {MPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData1d* const hist_data,
                            int rand_seed)
        {MPrintErrVFunc; abort();};
    

    // generate events from histogram with poisson statistic
    DataArrayNerr1d* const GenRandomEvt(int rand_seed) const;
    
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;

    virtual HistData1d* GenSubHist(long ibinx_st, long ibinx_ed) const = 0;

    // offset_tag = "st", "md", "ed", "no"
    double GetOffsetXFromTag(string offset_tag) const;
    double GetOffsetOFromTag(string offset_tag) const;

    //
    // static 
    //
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         string* format_ptr);

protected:
    void NullHistData1d();
    void NewOvalArrAsDataArrayNerr1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    void NewHi1d();
    HistInfo1d* GetHi1dNonConst() const {return hi1d_;};
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};
    void IsHi1dNotNull() const;
    void IsOvalArrNotNull() const;
    void IsValidIbin(long ibin) const;
    void IsValidRange(double val) const;
    
private:
    HistInfo1d* hi1d_;
    DataArray1d* oval_arr_;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_H_
