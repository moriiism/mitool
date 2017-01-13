#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_TERR_H_

#include "mir_graph2d_terr.h"
#include "mir_hist1d.h"

class HistDataTerr1d : public HistData1d{
public:
    HistDataTerr1d(string title = "") :
        HistData1d("HistDataTerr1d", title) {}
    ~HistDataTerr1d() {}

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    using HistData1d::Init;
    
    // SetData
    using HistData1d::SetData;    
    void SetData(long nbin_xval,
                 const double* const oval,
                 const double* const oval_terr_plus,
                 const double* const oval_terr_minus);

    // InitSet each
    using HistData1d::InitSet;
    void InitSet(long nbin_xval,
                 double xval_lo,
                 double xval_up,
                 const double* const oval,
                 const double* const oval_terr_plus,
                 const double* const oval_terr_minus);
    void InitSet(const TH1D* const th1d);

    // kinds of Set
    void SetOvalTerrPlusElm(long ibin, double oval_terr_plus);
    void SetOvalTerrMinusElm(long ibin, double oval_terr_minus);

    // Init & Set by graph2d_terr,
    // only if xval_arr of graph2d_terr is equally-spaced and
    // appropriate errors.
    // void InitSetByGraphData2dTerr(const GraphDataTerr2d* const g2d);

    using HistData1d::FillByMax;
    void FillByMax(double xval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);
    using HistData1d::FillByMin;
    void FillByMin(double xval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);

    void SetOvalErrArrByPoissonErr();
    
    HistDataTerr1d* const Clone() const;
    
    void Load(string file);

    
    //
    // const functions
    //

    // get
    const DataArrayTerr1d* const GetOvalArr() const;

    // get internal of oval_arr_
    const double* const GetOvalTerrPlusArrDbl() const;
    const double* const GetOvalTerrMinusArrDbl() const;
    double GetOvalTerrPlusElm(long ibin) const;
    double GetOvalTerrMinusElm(long ibin) const;
    double GetOvalTerrPlusElmAtX(double xval) const;    
    double GetOvalTerrMinusElmAtX(double xval) const;

    // gen xval_arr, oval_arr
    void GenOvalTerrArr(double** const oval_terr_plus_arr_ptr,
                        double** const oval_terr_minus_arr_ptr,
                        long* const nbin_ptr) const;

    //
    // output
    //
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_oval = 0.0) const;

    HistDataTerr1d* const GenHd1MaxInBin(long nbin_new) const;
    GraphDataTerr2d* const GenGraph2d() const;
    TH1D* const GenTH1D(double offset_xval = 0.0,
                        double offset_oval = 0.0) const;

    // qdp range
    void GetORangeQdp(double* const low_ptr,
                      double* const up_ptr) const;

    double GetOffsetOFromTag(string offset_tag) const;

};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_TERR_H_
