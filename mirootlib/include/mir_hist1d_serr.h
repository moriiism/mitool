#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_SERR_H_

#include "mir_hist1d.h"
#include "mir_graph2d_serr.h"

class HistDataSerr1d : public HistData1d{
public:
    explicit HistDataSerr1d(string title = "") :
        HistData1d("HistDataSerr1d", title) {}
    ~HistDataSerr1d() {
        NullHistData1d();
    }

    // Init
    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    using HistData1d::Init;

    // SetData
    using HistData1d::SetData;    
    void SetData(long nbin_xval,
                 const double* const oval,
                 const double* const oval_serr);

    // InitSet each
    using HistData1d::InitSet;
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 const double* const oval,
                 const double* const oval_serr);
    
    void InitSet(const TH1D* const th1d);

    // kinds of Set
    void SetOvalSerrElm(long ibin, double oval_serr);

    // Init & Set by graph2d_serr,
    // only if xval_arr of graph2d_serr is equally-spaced and
    // appropriate errors.
    // void InitSetByGraphData2dSerr(const GraphDataSerr2d* const g2d);

    using HistData1d::FillByMax;
    void FillByMax(double xval,
                   double oval,
                   double oval_serr);
    using HistData1d::FillByMin;
    void FillByMin(double xval,
                   double oval,
                   double oval_serr);

    void SetOvalErrArrByPoissonErr();
    
    HistDataSerr1d* const Clone() const;
    
    void Load(string file);

    //
    // const functions
    //
    
    // get
    const DataArraySerr1d* const GetOvalArr() const;

    // get internal of oval_arr_
    const double* const GetOvalSerrArrDbl() const;
    double GetOvalSerrElm(long ibin) const;
    double GetOvalSerrElmAtX(double xval) const;

    // gen xval_arr, oval_arr
    void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                        long* const nbin_ptr) const;

    //
    // output
    //
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_oval = 0.0) const;

    HistDataSerr1d* const GenHd1MaxInBin(long nbin_new) const;
    GraphDataSerr2d* const GenGraph2d() const;
    TH1D* const GenTH1D(double offset_xval = 0.0,
                        double offset_oval = 0.0) const;

    //void MkTH1Fig(string outfig,
    //              double offset_xval = 0.0,
    //              double offset_oval = 0.0) const;
    
    // qdp range
    void GetORangeQdp(double* const low_ptr,
                      double* const up_ptr) const;
    
    // poisson error
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    int rand_seed = 1);

    // gaussian error
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    const MirFunc* const func_sigma,
                    const MirFuncPar* const func_par_sigma,
                    int rand_seed = 1);

    // poisson error
    void FillRandom(const HistData1d* const hist_data,
                    int rand_seed = 1);
    double GetOffsetOFromTag(string offset_tag) const;
        
};


#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_SERR_H_
