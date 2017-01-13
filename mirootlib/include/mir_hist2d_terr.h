#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_

#include "mir_hist1d_terr.h"
#include "mir_hist2d.h"
#include "mir_graph3d_terr.h"

class HistDataTerr2d : public HistData2d{
public:
    explicit HistDataTerr2d(string title = "") :
        HistData2d("HistDataTerr2d", title) {}
    ~HistDataTerr2d() {}

    // Init
    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    using HistData2d::Init;
    
    // SetData
    using HistData2d::SetData;    
    void SetData(long nbin_xval, long nbin_yval, 
                 const double* const oval,
                 const double* const oval_terr_plus,
                 const double* const oval_terr_minus);

    // InitSet each
    using HistData2d::InitSet;    
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 long nbin_yval, double yval_lo, double yval_up,
                 const double* const oval,
                 const double* const oval_terr_plus,
                 const double* const oval_terr_minus);
    void InitSet(const TH2D* const th2d);

    // kinds of Set
    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
                        double oval_serr);
    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
                        double oval_terr_plus,
                        double oval_terr_minus);

    // Init & Set by graph3d_terr,
    // only if xval_arr of graph3d_terr is equally-spaced and
    // appropriate errors
    // void InitSetByGraphData3dTerr(const GraphDataTerr3d* const g3d);

    using HistData2d::FillByMax;    
    void FillByMax(double xval, double yval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);
    using HistData2d::FillByMin;        
    void FillByMin(double xval, double yval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);
    
    void SetOvalErrArrByPoissonErr();

    HistDataTerr2d* const Clone() const;
    
    void Load(string file);

    //
    // operation
    //
    using HistData2d::Min;
    void Min(const HistDataTerr2d* const* const hist_data_arr,
             int nhist);

    using HistData2d::Max;    
    void Max(const HistDataTerr2d* const* const hist_data_arr,
             int nhist);
    

    //
    // const functions
    //

    // get
    const DataArrayTerr1d* const GetOvalArr() const;

    // get internal of oval_arr_
    const double* const GetOvalTerrPlusArrDbl() const;
    const double* const GetOvalTerrMinusArrDbl() const;
    double GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const;    
    double GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const;
    double GetOvalTerrPlusElmAtXY(double xval, double yval) const;
    double GetOvalTerrMinusElmAtXY(double xval, double yval) const;
    
    // gen xval_arr, yval_arr, oval_arr
    void GenOvalTerrPlusArr(double** const oval_terr_plus_arr_ptr,
                            long* const nbin_ptr) const;
    void GenOvalTerrMinusArr(double** const oval_terr_minus_arr_ptr,
                             long* const nbin_ptr) const;

    // output
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0) const;

    virtual GraphDataTerr3d* const GenGraph3d() const;

    double GetOffsetOFromTag(string offset_tag) const;

private:
    long num_terr_outer_;

};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_
