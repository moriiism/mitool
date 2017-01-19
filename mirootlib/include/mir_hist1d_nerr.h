#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_

#include "mir_hist1d.h"
#include "mir_graph2d_nerr.h"

class HistDataNerr1d : public HistData1d{
public:
    explicit HistDataNerr1d(string title = "") :
        HistData1d("HistDataNerr1d", title) {}
    virtual ~HistDataNerr1d() {
        NullHistData1d();
    }

    void Init(long nbin_xval,
              double xval_lo,
              double xval_up);
    void Init(const HistInfo1d* const hist_info);
    HistDataNerr1d* const Clone() const;
    void Load(string file);
    const DataArrayNerr1d* const GetOvalArr() const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_oval) const;
    HistDataNerr1d* const GenHd1MaxInBin(long nbin_new) const;
    GraphDataNerr2d* const GenGraph2d() const;
    TH1D* const GenTH1D(double offset_xval,
                        double offset_oval) const;

     void FillRandom(const MirFunc* const func,
                     const MirFuncPar* const func_par,
                     int rand_seed = 1);
    void FillRandom(const HistData1d* const hist_data,
                    int rand_seed = 1);
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_NERR_H_
