#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

#include "mir_hist2d.h"
#include "mir_graph3d_nerr.h"

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
    TH2D* const GenTH2D(double offset_xval,
                        double offset_yval,
                        double offset_oval) const;

    void FillRandom(const MirFunc* const func,
                    const double* const func_par,
                    int rand_seed);
    void FillRandom(const HistData2d* const hist_data,
                    int rand_seed);

    HistDataNerr2d* GenSubHist(long ibinx_st, long ibinx_ed,
                               long ibiny_st, long ibiny_ed) const;
    
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_NERR_H_

