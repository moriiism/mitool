#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_

#include "mir_hist1d_serr.h"
#include "mir_hist2d.h"
#include "mir_graph3d_serr.h"

class HistDataSerr2d : public HistData2d{
public:
    explicit HistDataSerr2d(string title = "") :
        HistData2d("HistDataSerr2d", title) {}
    ~HistDataSerr2d() {
        NullHistData2d();
    }

    // Init
    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    using HistData2d::Init;

    // SetData
    using HistData2d::SetData;
    void SetData(long nbin_xval, long nbin_yval, 
                 const double* const oval,
                 const double* const oval_serr);

    // InitSet each
    using HistData2d::InitSet;
    void InitSet(long nbin_xval, double xval_lo, double xval_up,
                 long nbin_yval, double yval_lo, double yval_up,
                 const double* const oval,
                 const double* const oval_serr);
    void InitSet(const TH2D* const th2d);

    // kinds of Set
    void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr);

    // Init & Set by graph3d_serr,
    // only if xval_arr of graph3d_serr is equally-spaced and
    // appropriate errors
    // void InitSetByGraphData3dSerr(const GraphDataSerr3d* const g3d);

    using HistData2d::FillByMax;
    void FillByMax(double xval, double yval,
                   double oval,
                   double oval_serr);
    using HistData2d::FillByMin;
    void FillByMin(double xval, double yval,
                   double oval,
                   double oval_serr);

    void SetOvalErrArrByPoissonErr();

    HistDataSerr2d* const Clone() const;

    void Load(string file);

    //
    // operation
    //
    using HistData2d::Min;
    void Min(const HistDataSerr2d* const* const hist_data_arr,
             int nhist);

    using HistData2d::Max;    
    void Max(const HistDataSerr2d* const* const hist_data_arr,
             int nhist);
    using HistData2d::Add;
    void Add(const HistDataSerr2d* const* const hist_data_arr,
             int nhist);
    using HistData2d::AMean;
    void AMean(const HistDataSerr2d* const* const hist_data_arr,
               int nhist);
    int WMean(const HistDataSerr2d* const hist_data1,
              const HistDataSerr2d* const hist_data2,
              vector<long>* const index_bad_vec_ptr);
    int WMean(const HistDataSerr2d* const* const hist_data_arr,
              int nhist,
              vector<long>* const index_bad_vec_ptr);

    //
    // const functions
    //
    
    // get
    const DataArraySerr1d* const GetOvalArr() const;

    // get internal of oval_arr_
    const double* const GetOvalSerrArrDbl() const;
    double GetOvalSerrElm(long ibin_xval, long ibin_yval) const;
    double GetOvalSerrElmAtXY(double xval, double yval) const;

    // gen xval_arr, yval_arr, oval_arr
    void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                        long* const nbin_ptr) const;

    // calc_mode  : "add", "integral", "amean"
    // error_mode: gauss, poisson, zero
    using HistData2d::GenProjectX;
    using HistData2d::GenProjectY;
    HistDataSerr1d* const GenProjectX(long ibin_ylo, long ibin_yup,
                                      string calc_mode, string error_mode) const;
    HistDataSerr1d* const GenProjectY(long ibin_xlo, long ibin_xup,
                                      string calc_mode, string error_mode) const;  

    //
    // output
    //
    void PrintData(FILE* fp, string format,
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0) const;


    // virtual GraphDataSerr3d* const GenGraph3d() const;
    TH2D* const GenTH2D(double offset_xval = 0.0,
                        double offset_yval = 0.0,
                        double offset_oval = 0.0) const;
    
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
    void FillRandom(const HistData2d* const hist_data,
                    int rand_seed = 1);

    double GetOffsetOFromTag(string offset_tag) const;
    
private:
    
    // calc_mode  : "add", "integral", "amean"
    // error_mode: gauss, poisson, zero
    void GetProject(long ndata,
                    const double* const array,
                    const double* const array_err,
                    string calc_mode, string error_mode,
                    double bin_width,
                    double* const val_proj_ptr,
                    double* const val_proj_err_ptr) const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_
