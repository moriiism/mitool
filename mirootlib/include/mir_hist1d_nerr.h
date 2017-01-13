#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_

#include "TH1D.h"
#include "TPaletteAxis.h"
#include "TRandom3.h"

#include "mir_graph2d.h"
#include "mir_hist_info.h"

class HistDataNerr1d : public HistData1d{
public:
    explicit HistDataNerr1d(string title = "") :
        HistData1d("HistDataNerr1d", title),
        nbin_xval_(0), xval_lo_(0.0), xval_up_(0.0),
        oval_arr_(NULL) {}
    virtual ~HistData1d() {
        Null();
    }
   
    // Init
    virtual void Init(long nbin_xval,
                      double xval_lo,
                      double xval_up);
    void Init(const HistInfo1d* const hist_info);

    // Set
    void Set(const HistData1d* const org);
    void Set(long nbin_xval, double xval_lo, double xval_up,
             const DataArray1d* const oval_arr);
    
    // SetInfo
    void SetInfo(long nbin_xval, double xval_lo, double xval_up);
    // SetData
    void SetData(const DataArray1d* const oval_arr);

    // set each
    void SetData(long nbin_xval, const double* const oval);
    virtual void SetData(long nbin_xval,
                         const double* const oval,
                         const double* const oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void SetData(long nbin_xval,
                         const double* const oval,
                         const double* const oval_terr_plus,
                         const double* const oval_terr_minus)
        {MPrintErrVFunc; abort();};


    // InitSet
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 const DataArray1d* const oval_arr);
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 const double* const oval);
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         const double* const oval,
                         const double* const oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void InitSet(long nbin_xval, double xval_lo, double xval_up,
                         const double* const oval,
                         const double* const oval_terr_plus,
                         const double* const oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    virtual void InitSet(const TH1D* const th1d);


    // kinds of Set
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
    void FillByMax(double xval, double oval);
    virtual void FillByMax(double xval,
                           double oval,
                           double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMax(double xval,
                           double oval,
                           double oval_terr_plus,
                           double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void FillByMin(double xval, double oval);
    virtual void FillByMin(double xval,
                           double oval,
                           double oval_serr)
        {MPrintErrVFunc; abort();};
    virtual void FillByMin(double xval,
                           double oval,
                           double oval_terr_plus,
                           double oval_terr_minus)
        {MPrintErrVFunc; abort();};
    
    void SetZero();
    void SetOne();
    void SetConst(double constant);
    void SetOneAtInterval(const Interval* const interval);

    virtual void SetOvalErrArrByPoissonErr()
        {MPrintErrVFunc; abort();};
    
    // Set by Func
    void SetByFunc(const MirFunc* const func, const double* const par);

    // set by amean of graph data
    void SetByGraphData2d(const GraphData2d* const g2d);

   
    // Init & Set by graph2d, only if xval_arr of graph2d is equally-spaced.
    void InitSetByGraphData2d(const GraphData2d* const g2d);

    
    void Copy(const HistData1d* const org);
    virtual HistData1d* const Clone() const;

    virtual void Load(string file);
    static HistData1d* const GenHd1dByLoad(string file);
    static void ReadInfo(string file, 
                         long* nbin_xval_ptr,
                         double* xval_lo_ptr,
                         double* xval_up_ptr,
                         string* format_ptr);

    //
    // operation
    //
    void Not(const HistData1d* const hist_data);
    void Scale(const HistData1d* const hist_data,
               double scale, double offset);
    void Min(const HistData1d* const hist_data1,
             const HistData1d* const hist_data2);
    void Min(const HistData1d* const* const hist_data_arr,
             int nhist);
    virtual void Min(const HistDataSerr1d* const* const hist_data_arr,
                     int nhist)
        {MPrintErrVFunc; abort();};
    
    void Max(const HistData1d* const hist_data1,
             const HistData1d* const hist_data2);
    void Max(const HistData1d* const* const hist_data_arr,
             int nhist);
    virtual void Max(const HistDataSerr1d* const* const hist_data_arr,
                     int nhist)
        {MPrintErrVFunc; abort();};
    
    void Add(const HistData1d* const hist_data1,
             const HistData1d* const hist_data2);
    void Add(const HistData1d* const* const hist_data_arr,
             int nhist);
    virtual void Add(const HistDataSerr1d* const* const hist_data_arr,
                     int nhist)
        {MPrintErrVFunc; abort();};
    
    void Sub(const HistData1d* const hist_data1,
             const HistData1d* const hist_data2);
    void Mul(const HistData1d* const hist_data1,
             const HistData1d* const hist_data2);
    int  Div(const HistData1d* const hist_data_num,
             const HistData1d* const hist_data_den,
             vector<long>* const index_bad_vec_ptr);
    void AMean(const HistData1d* const hist_data1,
               const HistData1d* const hist_data2);
    void AMean(const HistData1d* const* const hist_data_arr,
               int nhist);
    virtual void AMean(const HistDataSerr1d* const* const hist_data_arr,
                       int nhist)
        {MPrintErrVFunc; abort();};
    virtual int WMean(const HistDataSerr1d* const hist_data1,
                      const HistDataSerr1d* const hist_data2,
                      vector<long>* const index_bad_vec_ptr)
        {MPrintErrVFunc; abort();};
    virtual int WMean(const HistDataSerr1d* const* const hist_data_arr,
                      int nhist,
                      vector<long>* const index_bad_vec_ptr)
        {MPrintErrVFunc; abort();};

    // sub_add_ratio = (h1 - h2) / (h1 + h2)
    void SubAddRatio(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2);

    void Variance(const HistData1d* const* const hist_data_arr,
                  int nhist);
    void Stddev(const HistData1d* const* const hist_data_arr,
                int nhist);
    void UnbiasedVariance(const HistData1d* const* const hist_data_arr,
                          int nhist);
    void SqrtOfUnbiasedVariance(const HistData1d* const* const hist_data_arr,
                                int nhist);
    void RMS(const HistData1d* const* const hist_data_arr,
             int nhist);
    void Median(const HistData1d* const* const hist_data_arr,
                int nhist);

    //
    // const functions
    //

    // get
    virtual const DataArray1d* const GetOvalArr() const
        {return oval_arr_;};
    long GetNbinX() const {return nbin_xval_;};
    double GetXvalLo() const {return xval_lo_;};
    double GetXvalUp() const {return xval_up_;};
    double GetXvalMd() const {return (xval_lo_ + xval_up_) / 2.0;};
    double GetXvalFullWidth() const {return xval_up_ - xval_lo_;};
    double GetBinWidth() const
        {return (xval_up_ - xval_lo_) / nbin_xval_;};

    // get internal of oval_arr_
    const double* const GetOvalArrDbl() const;
    virtual const double* const GetOvalSerrArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrPlusArrDbl() const
        {MPrintErrVFunc; abort();};
    virtual const double* const GetOvalTerrMinusArrDbl() const
        {MPrintErrVFunc; abort();};
    
    double GetOvalElm(long ibin) const;
    virtual double GetOvalSerrElm(long ibin) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElm(long ibin) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElm(long ibin) const
        {MPrintErrVFunc; abort();};
    
    double GetOvalElmAtX(double xval) const;
    virtual double GetOvalSerrElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrPlusElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    virtual double GetOvalTerrMinusElmAtX(double xval) const
        {MPrintErrVFunc; abort();};
    

    // stat
    double GetXvalAtOvalMin() const;
    double GetXvalAtOvalMax() const;
    
    long GetIbin(double xval) const;
    long GetIbinWithHalfBinShifted(double xval) const;
    double GetBinCenterX(long ibin) const;
    double GetBinLoX(long ibin) const;
    double GetBinUpX(long ibin) const;
    double GetOvalIntPolLin(double xval) const;
    double GetIntegral(double xval_lo, double xval_up) const;

    // gen xval_arr, oval_arr
    void GenXvalArr(double** const xval_arr_ptr,
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

    
    //
    // output
    //
    void Save(string outfile, string format,
              double offset_xval = 0.0,
              double offset_oval = 0.0) const;
    void SaveData(string outfile, string format,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;
    void PrintInfo(FILE* fp, string format) const;
    virtual void PrintData(FILE* fp, string format,
                           double offset_xval = 0.0,
                           double offset_oval = 0.0) const;
    void SaveRoot(string outfile,
                  double offset_xval = 0.0,
                  double offset_oval = 0.0) const;

    virtual HistData1d* const GenHd1MaxInBin(long nbin_new) const;
    virtual GraphData2d* const GenGraph2d() const;
    virtual TH1D* const GenTH1D(double offset_xval = 0.0,
                                double offset_oval = 0.0) const;
    virtual void MkTH1Fig(string outfig,
                          MirRootTool* const root_tool,
                          double offset_xval = 0.0,
                          double offset_oval = 0.0) const;

    // qdp range
    void GetXRangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    virtual void GetORangeQdp(double* const low_ptr,
                              double* const up_ptr) const;

    // poisson error
    virtual void FillRandom(const MirFunc* const func,
                            const MirFuncPar* const func_par,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};

    // gaussian error
    virtual void FillRandom(const MirFunc* const func,
                            const MirFuncPar* const func_par,
                            const MirFunc* const func_sigma,
                            const MirFuncPar* const func_par_sigma,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};    

    // poisson error
    virtual void FillRandom(const HistData1d* const hist_data,
                            int rand_seed = 1)
        {MPrintErrVFunc; abort();};
    

    // generate events from histogram with poisson statistic
    DataArray1d* const GenRandomEvt(int rand_seed = 1) const;
    
    Interval* const GenIntervalAboveThreshold(double threshold) const;
    Interval* const GenIntervalBelowThreshold(double threshold) const;

    // offset_tag = "st", "md", "ed", "no"
    double GetOffsetXFromTag(string offset_tag) const;
    virtual double GetOffsetOFromTag(string offset_tag) const;
    
    int IsAllOne() const {return GetOvalArr()->IsAllOne();};

   
protected:
    void Null();
    void NewOvalArrAsDataArray1d();
    void NewOvalArrAsDataArraySerr1d();
    void NewOvalArrAsDataArrayTerr1d();
    DataArray1d* GetOvalArrNonConst() const {return oval_arr_;};

    int IsOvalNotNull() const;
    
private:
    long nbin_xval_;
    double xval_lo_;
    double xval_up_;

    //HistInfo1d* hi1d_;
    DataArray1d* oval_arr_;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_
