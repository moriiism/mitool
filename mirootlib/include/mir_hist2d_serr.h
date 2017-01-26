#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_

#include "mir_hist1d_serr.h"
#include "mir_hist2d.h"
//#include "mir_graph3d_serr.h"

class HistDataSerr2d : public HistData2d{
public:
    explicit HistDataSerr2d(string title = "") :
        HistData2d("HistDataSerr2d", title) {}
    ~HistDataSerr2d() {
        NullHistData2d();
    }

    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    void Init(const HistInfo2d* const hist_info);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    void SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr);

    void FillByLarger(double xval, double yval,
                      double oval,
                      double oval_serr);
    void FillBySmaller(double xval, double yval,
                       double oval,
                       double oval_serr);
    void SetOvalErrArrByPoissonErr();
    HistDataSerr2d* const Clone() const;
    void Load(string file);

    // Init & Set by graph3d_serr,
    // only if xval_arr of graph3d_serr is equally-spaced and
    // appropriate errors
    // void InitSetByGraphData3dSerr(const GraphDataSerr3d* const g3d);
    

    const DataArraySerr1d* const GetOvalArr() const;
    double GetOvalSerrElm(long ibin_xval, long ibin_yval) const;
    double GetOvalSerrElmAtXY(double xval, double yval) const;
    void GenOvalSerrArr(double** const oval_serr_arr_ptr,
                        long* const nbin_ptr) const;

//    // calc_mode  : "add", "integral", "amean"
//    // error_mode: gauss, poisson, zero
//    using HistData2d::GenProjectX;
//    using HistData2d::GenProjectY;
//    HistDataSerr1d* const GenProjectX(long ibin_ylo, long ibin_yup,
//                                      string calc_mode, string error_mode) const;
//    HistDataSerr1d* const GenProjectY(long ibin_xlo, long ibin_xup,
//                                      string calc_mode, string error_mode) const;  

    //
    // output
    //
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;

//    HistData2d* const GenHd2MaxInBin(long nbinx_new, long nbiny_new) const;
    // virtual GraphDataSerr3d* const GenGraph3d() const;
    TH2D* const GenTH2D(double offset_xval,
                        double offset_yval,
                        double offset_oval) const;

//    HistDataSerr2d* const GenHd2AddMargin(double margin_xval, double margin_yval) const;
    
    // poisson error
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    int rand_seed);

    // gaussian error
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    const MirFunc* const func_sigma,
                    const MirFuncPar* const func_par_sigma,
                    int rand_seed);

    // poisson error
    void FillRandom(const HistData2d* const hist_data,
                    int rand_seed);
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_SERR_H_
