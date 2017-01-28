#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

#include "mir_hist2d.h"

class HistDataNerr2d : public HistData2d{
public:
    explicit HistDataNerr2d(string title = "") :
        HistData2d("HistDataNerr2d", title) {}
    virtual ~HistDataNerr2d() {
        NullHistData2d();
    }
   
    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    void Init(const HistInfo2d* const hist_info);
    HistDataNerr2d* const Clone() const;
    void Load(string file);
    const DataArrayNerr1d* const GetOvalArr() const;
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;
    HistData2d* const GenHd2MaxInBin(long nbinx_new, long nbiny_new) const;
    // virtual GraphData3d* const GenGraph3d() const;
    TH2D* const GenTH2D(double offset_xval,
                        double offset_yval,
                        double offset_oval) const;
    HistData2d* const GenHd2AddMargin(double margin_xval, double margin_yval) const;

    void FillRandom(const MirFunc* const func,
                    const double* const func_par,
                    int rand_seed);
    void FillRandom(const HistData2d* const hist_data,
                    int rand_seed);
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

