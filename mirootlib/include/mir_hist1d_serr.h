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

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    void Init(const HistInfo1d* const hist_info);
    void SetOvalSerrArr(long ndata, const double* const val_serr);
    void SetOvalSerrArr(vector<double> val_serr);
    void SetOvalSerrElm(long ibin, double oval_serr);
    void FillByLarger(double xval,
                      double oval,
                      double oval_serr);
    void FillBySmaller(double xval,
                       double oval,
                       double oval_serr);
    void SetOvalErrArrByPoissonErr();
    // void InitSetByGraphData2dSerr(const GraphDataSerr2d* const g2d);
    HistDataSerr1d* const Clone() const;
    void Load(string file);

    const DataArraySerr1d* const GetOvalArr() const;
    double GetOvalSerrElm(long ibin) const;
    double GetOvalSerrElmAtX(double xval) const;

    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;

    HistDataSerr1d* const GenHd1MaxInBin(long nbin_new) const;
    GraphDataSerr2d* const GenGraph2d() const;
    TH1D* const GenTH1D(double offset_xval,
                        double offset_oval) const;
    void MkTH1Fig(string outfig,
                  MirRootTool* const root_tool,
                  double offset_xval,
                  double offset_oval) const;
    

    // poisson error
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    int rand_seed);
    void FillRandom(const MirFunc* const func,
                    const MirFuncPar* const func_par,
                    const MirFunc* const func_sigma,
                    const MirFuncPar* const func_par_sigma,
                    int rand_seed);
    void FillRandom(const HistData1d* const hist_data,
                    int rand_seed);
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_SERR_H_
