#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_

#include "mir_data1d_ope.h"
#include "mir_hist2d_nerr.h"
#include "mir_hist2d_serr.h"
#include "mir_hist2d_terr.h"
#include "mir_cont.h"

namespace HistData2dOpe
{
    void FillGd2d(const HistDataNerr2d* const hd2d,
                  const GraphDataNerr2d* const gd2d,
                  HistDataNerr2d* const hist_res_out);
    
    void GetResValHd2(const HistDataNerr2d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataNerr2d* const hist_res_out);
    void GetResValHd2(const HistDataSerr2d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataSerr2d* const hist_res_out);
    void GetResValHd2(const HistDataTerr2d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataTerr2d* const hist_res_out);
    
    void GetResRatioHd2(const HistDataNerr2d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistDataNerr2d* const hist_res_out);
    void GetResRatioHd2(const HistDataSerr2d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistDataSerr2d* const hist_res_out);
    void GetResRatioHd2(const HistDataTerr2d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        HistDataTerr2d* const hist_res_out);
    
    void GetResChiHd2(const HistDataSerr2d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataSerr2d* const hist_res_out);
    void GetResChiHd2(const HistDataTerr2d* const hist_data,
                      const MirFunc* const func, const double* const par,
                      HistDataTerr2d* const hist_res_out);
    
    int IsFormatSame(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2);
    int IsFormatSame(const HistDataNerr2d* const* const hist_data_arr,
                     int nhist);
    int IsFormatSame(const HistDataSerr2d* const* const hist_data_arr,
                     int nhist);
    int IsFormatSame(const HistDataTerr2d* const* const hist_data_arr,
                     int nhist);

    void GenContMinFcn(const HistDataNerr2d* const hd2d,
                       double zval_min,
                       int nlevel,
                       const double* const delta_minfcn_arr,
                       MirCont*** const cont_arr_ptr,
                       MirRootTool* const root_tool,
                       double offset_xval = 0.0,
                       double offset_yval = 0.0);

    void GenContWithBestMinFcn(const HistDataNerr2d* const hd2d,
                               double zval_min, double xval_best, double yval_best,
                               int nlevel, const double* const delta_minfcn_arr,
                               MirContWithBest*** const cont_with_best_arr_ptr,
                               MirRootTool* const root_tool,
                               double offset_xval = 0.0,
                               double offset_yval = 0.0);


    // hd2d_mask: 1 or 0
    void GetHd2dMaskWithMargin(const HistDataNerr2d* const hd2d_mask,
                               double xval_margin, double yval_margin,
                               HistData2d* const hd2d_with_margin_out);
    

} // namespace HistData2dOpe


#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_
