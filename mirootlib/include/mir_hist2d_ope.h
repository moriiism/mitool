#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_

#include "mir_data1d_ope.h"

#include "mir_hist1d_nerr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist1d_terr.h"

#include "mir_hist2d_nerr.h"
#include "mir_hist2d_serr.h"
#include "mir_hist2d_terr.h"
#include "mir_cont.h"

namespace HistData2dOpe
{
    HistData2d* const GenHd2dByLoad(string file);

    DataArray1d** const GenDa1dArrNerr(const HistData2d* const* const hd2d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrSerr(const HistData2d* const* const hd2d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrTerr(const HistData2d* const* const hd2d_arr,
                                       int narr);
    void DelHd2dArr(HistData2d** const hd2d_arr, int narr);

    int IsFormatSame(const HistData2d* const data1,
                     const HistData2d* const data2);
    int IsFormatSame(const HistData2d* const* const data_arr,
                     int nhist);
    
    // For one HistData2d
    void GetNot(const HistData2d* const in,
                HistDataNerr2d* const out);
    void GetNot(const HistData2d* const in,
                HistDataSerr2d* const out);
    void GetNot(const HistData2d* const in,
                HistDataTerr2d* const out);
    
    void GetScale(const HistData2d* const in,
                  double scale, double offset,
                  HistDataNerr2d* const out);
    void GetScale(const HistData2d* const in,
                  double scale, double offset,
                  HistDataSerr2d* const out);
    void GetScale(const HistData2d* const in,
                  double scale, double offset,
                  HistDataTerr2d* const out);

    // For two HistData2d
    void GetMin(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataNerr2d* const out);
    void GetMin(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataSerr2d* const out);
    void GetMin(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataTerr2d* const out);
    
    void GetMax(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataNerr2d* const out);
    void GetMax(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataSerr2d* const out);
    void GetMax(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataTerr2d* const out);
    
    void GetAdd(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataNerr2d* const out);
    void GetAdd(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataSerr2d* const out);
    
    void GetSub(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataNerr2d* const out);
    void GetSub(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataSerr2d* const out);
    
    void GetMul(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataNerr2d* const out);
    void GetMul(const HistData2d* const in1,
                const HistData2d* const in2,
                HistDataSerr2d* const out);
    
    int GetDiv(const HistData2d* const num,
               const HistData2d* const den,
               HistDataNerr2d* const mask_sel_out,
               HistDataNerr2d* const out);
    int GetDiv(const HistData2d* const num,
               const HistData2d* const den,
               HistDataNerr2d* const mask_sel_out,
               HistDataSerr2d* const out);
    
    void GetAMean(const HistData2d* const in1,
                  const HistData2d* const in2,
                  HistDataNerr2d* const out);
    void GetAMean(const HistData2d* const in1,
                  const HistData2d* const in2,
                  HistDataSerr2d* const out);
    
    int GetWMean(const HistData2d* const in1,
                 const HistData2d* const in2,
                 HistDataNerr2d* const mask_sel_out,
                 HistDataSerr2d* const out);

    int GetSubAddRatio(const HistData2d* const in1,
                       const HistData2d* const in2,
                       HistDataNerr2d* const mask_sel_out,
                       HistDataNerr2d* const out);

    int GetSubAddRatio(const HistData2d* const in1,
                       const HistData2d* const in2,
                       HistDataNerr2d* const mask_sel_out,
                       HistDataSerr2d* const out);
    
    // For N HistData2d
    void GetMin(const HistData2d* const* const in_arr,
                int narr,
                HistDataNerr2d* const out);
    void GetMin(const HistData2d* const* const in_arr,
                int narr,
                HistDataSerr2d* const out);
    void GetMin(const HistData2d* const* const in_arr,
                int narr,
                HistDataTerr2d* const out);
    
    void GetMax(const HistData2d* const* const in_arr,
                int narr,
                HistDataNerr2d* const out);
    void GetMax(const HistData2d* const* const in_arr,
                int narr,
                HistDataSerr2d* const out);
    void GetMax(const HistData2d* const* const in_arr,
                int narr,
                HistDataTerr2d* const out);
    
    void GetSum(const HistData2d* const* const in_arr,
                int narr,
                HistDataNerr2d* const out);
    void GetSum(const HistData2d* const* const in_arr,
                int narr,
                HistDataSerr2d* const out);
    
    void GetAMean(const HistData2d* const* const in_arr,
                  int narr,
                  HistDataNerr2d* const out);
    void GetAMean(const HistData2d* const* const in_arr,
                  int narr,
                  HistDataSerr2d* const out);
    
    int GetWMean(const HistData2d* const* const in_arr,
                 int narr,
                 HistDataNerr2d* const mask_sel_out,
                 HistDataSerr2d* const out);
    
    void GetVariance(const HistData2d* const* const in_arr,
                     int narr,
                     HistDataNerr2d* const out);
    void GetStddev(const HistData2d* const* const in_arr,
                   int narr,
                   HistDataNerr2d* const out);
    void GetUnbiasedVariance(const HistData2d* const* const in_arr,
                             int narr,
                             HistDataNerr2d* const out);
    void GetSqrtOfUnbiasedVariance(const HistData2d* const* const in_arr,
                                   int narr,
                                   HistDataNerr2d* const out);
    void GetRMS(const HistData2d* const* const in_arr,
                int narr,
                HistDataNerr2d* const out);
    void GetMedian(const HistData2d* const* const in_arr,
                   int narr,
                   HistDataNerr2d* const out);
                   
    void GetSumWithMask(const HistData2d* const* const in_arr,
                        const HistData2d* const* const mask_arr,
                        int narr,
                        HistDataNerr2d* const out);
    void GetSumWithMask(const HistData2d* const* const in_arr,
                        const HistData2d* const* const mask_arr,
                        int narr,
                        HistDataSerr2d* const out);
    
    void GetAMeanWithMask(const HistData2d* const* const in_arr,
                          const HistData2d* const* const mask_arr,
                          int narr,
                          HistDataNerr2d* const out);
    void GetAMeanWithMask(const HistData2d* const* const in_arr,
                          const HistData2d* const* const mask_arr,
                          int narr,
                          HistDataSerr2d* const out);
    
    int GetWMeanWithMask(const HistData2d* const* const in_arr,
                         const HistData2d* const* const mask_arr,
                         int narr,
                         HistDataNerr2d* const mask_sel_out,
                         HistDataSerr2d* const out);

    // residual
    void GetResValHd2d(const HistData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataNerr2d* const out);
    void GetResValHd2d(const HistData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataSerr2d* const out);
    void GetResValHd2d(const HistData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataTerr2d* const out);
    
    void GetResValHd2d(const HistData2d* const data,
                       const HistDataNerr2d* const func,
                       HistDataNerr2d* const out);
    void GetResValHd2d(const HistData2d* const data,
                       const HistDataNerr2d* const func,
                       HistDataSerr2d* const out);
    void GetResValHd2d(const HistData2d* const data,
                       const HistDataNerr2d* const func,
                       HistDataTerr2d* const out);

    void GetResRatioHd2d(const HistData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataNerr2d* const out);
    void GetResRatioHd2d(const HistData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataSerr2d* const out);
    void GetResRatioHd2d(const HistData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataTerr2d* const out);
    
    void GetResRatioHd2d(const HistData2d* const data,
                         const HistDataNerr2d* const func,
                         HistDataNerr2d* const out);
    void GetResRatioHd2d(const HistData2d* const data,
                         const HistDataNerr2d* const func,
                         HistDataSerr2d* const out);
    void GetResRatioHd2d(const HistData2d* const data,
                         const HistDataNerr2d* const func,
                         HistDataTerr2d* const out);

    void GetResChiHd2d(const HistData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataSerr2d* const out);
    void GetResChiHd2d(const HistData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataTerr2d* const out);

    void GetResChiHd2d(const HistData2d* const data,
                       const HistDataNerr2d* const func,
                       HistDataSerr2d* const out);
    void GetResChiHd2d(const HistData2d* const data,
                       const HistDataNerr2d* const func,
                       HistDataTerr2d* const out);    


    void FillGd2d(const GraphDataNerr2d* const gd2d,
                  HistDataNerr2d* const hist_res_out);

    double FindMdXbyEdge(const HistDataNerr2d* const hd2d);
    double FindMdYbyEdge(const HistDataNerr2d* const hd2d);

    // calc_mode : "add", "integral", "amean", "min", "max"
    // error_mode: gauss, poisson, zero    
    void GetProjectX(const HistData2d* const in,
                     long ibin_ylo, long ibin_yup,
                     string calc_mode,
                     HistDataNerr1d* const out);
    void GetProjectX(const HistData2d* const in,
                     long ibin_ylo, long ibin_yup,
                     string calc_mode, string error_mode,
                     HistDataSerr1d* const out);

    void GetProjectY(const HistData2d* const in,
                     long ibin_xlo, long ibin_xup,
                     string calc_mode,
                     HistDataNerr1d* const out);
    void GetProjectY(const HistData2d* const in,
                     long ibin_xlo, long ibin_xup,
                     string calc_mode, string error_mode,
                     HistDataSerr1d* const out);

    // calc_mode: "add", "integral", "amean", "min", "max"
    // error_mode: gauss, poisson, zero    
    void GetProject(long ndata,
                    const double* const array,
                    string calc_mode, double bin_width,
                    double* const val_proj_ptr);
    void GetProject(long ndata,
                    const double* const array,
                    const double* const array_err,
                    string calc_mode, string error_mode,
                    double bin_width,
                    double* const val_proj_ptr,
                    double* const val_proj_err_ptr);
    
    // hd2d_mask: 1 or 0
    void GetHd2dMaskWithMargin(const HistDataNerr2d* const hd2d_mask,
                               double xval_margin, double yval_margin,
                               HistData2d* const hd2d_with_margin_out);
    

} // namespace HistData2dOpe


#endif // MORIIISM_MITOOL_MIROOTLIB_HIST2D_OPE_H_
