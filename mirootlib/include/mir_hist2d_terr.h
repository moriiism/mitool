#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_

#include "mir_hist1d_terr.h"
#include "mir_hist2d.h"
//#include "mir_graph3d_terr.h"

class HistDataTerr2d : public HistData2d{
public:
    explicit HistDataTerr2d(string title = "") :
        HistData2d("HistDataTerr2d", title) {}
    ~HistDataTerr2d() {
        NullHistData2d();
    }

    void Init(long nbin_xval, double xval_lo, double xval_up,
              long nbin_yval, double yval_lo, double yval_up);
    void Init(const HistInfo2d* const hist_info);
    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
                        double oval_serr);
    void SetOvalTerrElm(long ibin_xval, long ibin_yval,
                        double oval_terr_plus,
                        double oval_terr_minus);
    void FillByMax(double xval, double yval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);
    void FillByMin(double xval, double yval,
                   double oval,
                   double oval_terr_plus,
                   double oval_terr_minus);
    void SetOvalErrArrByPoissonErr();
    HistDataTerr2d* const Clone() const;
    void Load(string file);

    const DataArrayTerr1d* const GetOvalArr() const;
    double GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const;    
    double GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const;
    double GetOvalTerrPlusElmAtXY(double xval, double yval) const;
    double GetOvalTerrMinusElmAtXY(double xval, double yval) const;
    void GenOvalTerrPlusArr(double** const oval_terr_plus_arr_ptr,
                            long* const nbin_ptr) const;
    void GenOvalTerrMinusArr(double** const oval_terr_minus_arr_ptr,
                             long* const nbin_ptr) const;

   
    void PrintData(FILE* fp, string format,
                   double offset_xval,
                   double offset_yval,
                   double offset_oval) const;

    TH2D* const GenTH2D(double offset_xval,
                        double offset_yval,
                        double offset_oval) const
        {abort();}
    

    //virtual GraphDataTerr3d* const GenGraph3d() const;
};

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_TERR_H_
