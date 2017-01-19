#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_

#include "TH1D.h"
#include "TText.h"
#include "TPaveLabel.h"
#include "TPaletteAxis.h"
//#include "TFFTRealComplex.h"
//#include "TFFTComplex.h"
//#include <fftw3.h>

#include "mir_data1d_ope.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist1d_terr.h"

namespace HistData1dOpe
{
    HistData1d* const GenHd1dByLoad(string file);

    // select_type: center, exclusive
    //   center:      select a bin whose center is located in an interval.
    //   exclusive:   select only the full bins, meaning to exclude bins at the interval edge.
    void GetSelectHd1dByInterval(const HistData1d* const hist_data,
                                 const Interval* const interval,
                                 HistData1d* const hist_out,
                                 string select_type = "exclusive");
    void GetSelectHd1dByInterval(const HistDataSerr1d* const hist_data,
                                 const Interval* const interval,
                                 HistDataSerr1d* const hist_out,
                                 string select_type = "exclusive");
    void GetSelectHd1dByInterval(const HistDataTerr1d* const hist_data,
                                 const Interval* const interval,
                                 HistDataTerr1d* const hist_out,
                                 string select_type = "exclusive");    
    
    void GenSelectHd1dArrByInterval(const HistData1d* const hist_data,
                                    const Interval* const interval,
                                    HistData1d*** hd1d_arr_ptr,
                                    string select_type = "exclusive");
    void GenSelectHd1dArrByInterval(const HistDataSerr1d* const hist_data,
                                    const Interval* const interval,
                                    HistDataSerr1d*** hd1d_arr_ptr,
                                    string select_type = "exclusive");
    void GenSelectHd1dArrByInterval(const HistDataTerr1d* const hist_data,
                                    const Interval* const interval,
                                    HistDataTerr1d*** hd1d_arr_ptr,
                                    string select_type = "exclusive");    
    
    void GetPowSpec(const HistData1d* const hist_data,
                    HistData1d* hist_data_out);
    void GetPowSpecLeahyNorm(const HistData1d* const hist_data,
                             HistData1d* hist_data_out);
    void GetPowSpecNonfft(const HistData1d* const hist_data,
                          HistData1d* hist_data_out);
    
    void GetPowSpecDecomp(long mbin, const HistData1d* const hist_data,
                          HistData1d* hist_data_out);
    void GetPowSpecDecompNonfft(long mbin, const HistData1d* const hist_data,
                                HistData1d* hist_data_out);
    void GetAutoCorr(const HistData1d* const hist_data,
                     HistData1d* hist_data_out);
    void GetCrossCorr(const HistData1d* const hist_data1,
                      const HistData1d* const hist_data2,
                      HistData1d* hist_data_out);

    void GetResValHd1(const HistData1d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistData1d* const hist_res_out);
    void GetResValHd1(const HistDataSerr1d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataSerr1d* const hist_res_out);
    void GetResValHd1(const HistDataTerr1d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataTerr1d* const hist_res_out);
    
    void GetResValHd1(const HistData1d* const hist_data,
                      const HistData1d* const hist_func,
                      HistData1d* const hist_res_out);
    void GetResValHd1(const HistDataSerr1d* const hist_data,
                      const HistData1d* const hist_func,
                      HistDataSerr1d* const hist_res_out);
    void GetResValHd1(const HistDataTerr1d* const hist_data,
                      const HistData1d* const hist_func,
                      HistDataTerr1d* const hist_res_out);

    void GetResRatioHd1(const HistData1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistData1d* const hist_res_out);
    void GetResRatioHd1(const HistDataSerr1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistDataSerr1d* const hist_res_out);
    void GetResRatioHd1(const HistDataTerr1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistDataTerr1d* const hist_res_out);
    
    void GetResRatioHd1(const HistData1d* const hist_data,
                        const HistData1d* const hist_func,
                        HistData1d* const hist_res_out);
    void GetResRatioHd1(const HistDataSerr1d* const hist_data,
                        const HistData1d* const hist_func,
                        HistDataSerr1d* const hist_res_out);
    void GetResRatioHd1(const HistDataTerr1d* const hist_data,
                        const HistData1d* const hist_func,
                        HistDataTerr1d* const hist_res_out);

    void GetResChiHd1(const HistDataSerr1d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataSerr1d* const hist_res_out);
    void GetResChiHd1(const HistDataSerr1d* const hist_data,
                      const HistData1d* const hist_func,
                      HistDataSerr1d* const hist_res_out);

    int IsFormatSame(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2);
    int IsFormatSame(const HistData1d* const* const hist_data_arr,
                     int nhist);
    int IsFormatSame(const HistDataSerr1d* const* const hist_data_arr,
                     int nhist);
    int IsFormatSame(const HistDataTerr1d* const* const hist_data_arr,
                     int nhist);

    // Init & Set by graph2d, only if xval_arr of graph2d is the same as hist_info
    HistData1d* const GenHd1dByHistInfoAndGraphData2d(const HistInfo1d* const hist_info,
                                                      const GraphData2d* const g2d);

    int IsValidForSetByGd2d(const HistData1d* const hd1d,
                            const GraphData2d* const gd2d);
    
} // namespace HistData1dOpe

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_
