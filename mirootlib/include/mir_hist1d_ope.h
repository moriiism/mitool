#ifndef MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_

#include "TH1D.h"
#include "TText.h"
#include "TPaveLabel.h"
#include "TPaletteAxis.h"

#include "mir_data1d_ope.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist1d_terr.h"
#include "mir_graph2d.h"

namespace HistData1dOpe
{
    HistData1d* const GenHd1dByLoad(string file);

    DataArray1d** const GenDa1dArrNerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrSerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    DataArray1d** const GenDa1dArrTerr(const HistData1d* const* const hd1d_arr,
                                       int narr);
    void DelHd1dArr(HistData1d** const hd1d_arr, int narr);

    int IsFormatSame(const HistData1d* const data1,
                     const HistData1d* const data2);
    int IsFormatSame(const HistData1d* const* const data_arr,
                     int nhist);
    
    // For one HistData1d
    void GetNot(const HistData1d* const in,
                HistDataNerr1d* const out);
    void GetNot(const HistData1d* const in,
                HistDataSerr1d* const out);
    void GetNot(const HistData1d* const in,
                HistDataTerr1d* const out);
    
    void GetScale(const HistData1d* const in,
                  double scale, double offset,
                  HistDataNerr1d* const out);
    void GetScale(const HistData1d* const in,
                  double scale, double offset,
                  HistDataSerr1d* const out);
    void GetScale(const HistData1d* const in,
                  double scale, double offset,
                  HistDataTerr1d* const out);

    // For two HistData1d
    void GetMin(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMin(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    void GetMin(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataTerr1d* const out);
    
    void GetMax(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMax(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    void GetMax(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataTerr1d* const out);
    
    void GetAdd(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetAdd(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetSub(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetSub(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    void GetMul(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataNerr1d* const out);
    void GetMul(const HistData1d* const in1,
                const HistData1d* const in2,
                HistDataSerr1d* const out);
    
    int GetDiv(const HistData1d* const num,
               const HistData1d* const den,
               HistDataNerr1d* const mask_sel_out,
               HistDataNerr1d* const out);
    int GetDiv(const HistData1d* const num,
               const HistData1d* const den,
               HistDataNerr1d* const mask_sel_out,
               HistDataSerr1d* const out);
    
    void GetAMean(const HistData1d* const in1,
                  const HistData1d* const in2,
                  HistDataNerr1d* const out);
    void GetAMean(const HistData1d* const in1,
                  const HistData1d* const in2,
                  HistDataSerr1d* const out);
    
    int GetWMean(const HistData1d* const in1,
                 const HistData1d* const in2,
                 HistDataNerr1d* const mask_sel_out,
                 HistDataSerr1d* const out);

    int GetSubAddRatio(const HistData1d* const in1,
                       const HistData1d* const in2,
                       HistDataNerr1d* const mask_sel_out,
                       HistDataNerr1d* const out);

    int GetSubAddRatio(const HistData1d* const in1,
                       const HistData1d* const in2,
                       HistDataNerr1d* const mask_sel_out,
                       HistDataSerr1d* const out);
    
    // For N HistData1d
    void GetMin(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMin(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    void GetMin(const HistData1d* const* const in_arr,
                int narr,
                HistDataTerr1d* const out);
    
    void GetMax(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMax(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    void GetMax(const HistData1d* const* const in_arr,
                int narr,
                HistDataTerr1d* const out);
    
    void GetSum(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetSum(const HistData1d* const* const in_arr,
                int narr,
                HistDataSerr1d* const out);
    
    void GetAMean(const HistData1d* const* const in_arr,
                  int narr,
                  HistDataNerr1d* const out);
    void GetAMean(const HistData1d* const* const in_arr,
                  int narr,
                  HistDataSerr1d* const out);
    
    int GetWMean(const HistData1d* const* const in_arr,
                 int narr,
                 HistDataNerr1d* const mask_sel_out,
                 HistDataSerr1d* const out);
    
    void GetVariance(const HistData1d* const* const in_arr,
                     int narr,
                     HistDataNerr1d* const out);
    void GetStddev(const HistData1d* const* const in_arr,
                   int narr,
                   HistDataNerr1d* const out);
    void GetUnbiasedVariance(const HistData1d* const* const in_arr,
                             int narr,
                             HistDataNerr1d* const out);
    void GetSqrtOfUnbiasedVariance(const HistData1d* const* const in_arr,
                                   int narr,
                                   HistDataNerr1d* const out);
    void GetRMS(const HistData1d* const* const in_arr,
                int narr,
                HistDataNerr1d* const out);
    void GetMedian(const HistData1d* const* const in_arr,
                   int narr,
                   HistDataNerr1d* const out);
                   
    void GetSumWithMask(const HistData1d* const* const in_arr,
                        const HistData1d* const* const mask_arr,
                        int narr,
                        HistDataNerr1d* const out);
    void GetSumWithMask(const HistData1d* const* const in_arr,
                        const HistData1d* const* const mask_arr,
                        int narr,
                        HistDataSerr1d* const out);
    
    void GetAMeanWithMask(const HistData1d* const* const in_arr,
                          const HistData1d* const* const mask_arr,
                          int narr,
                          HistDataNerr1d* const out);
    void GetAMeanWithMask(const HistData1d* const* const in_arr,
                          const HistData1d* const* const mask_arr,
                          int narr,
                          HistDataSerr1d* const out);
    
    int GetWMeanWithMask(const HistData1d* const* const in_arr,
                         const HistData1d* const* const mask_arr,
                         int narr,
                         HistDataNerr1d* const mask_sel_out,
                         HistDataSerr1d* const out);
  
    // residual
    void GetResValHd1d(const HistData1d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataNerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataSerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataTerr1d* const out);
    
    void GetResValHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataNerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataSerr1d* const out);
    void GetResValHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataTerr1d* const out);

    void GetResRatioHd1d(const HistData1d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataNerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataSerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         HistDataTerr1d* const out);
    
    void GetResRatioHd1d(const HistData1d* const data,
                         const HistDataNerr1d* const func,
                         HistDataNerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const HistDataNerr1d* const func,
                         HistDataSerr1d* const out);
    void GetResRatioHd1d(const HistData1d* const data,
                         const HistDataNerr1d* const func,
                         HistDataTerr1d* const out);

    void GetResChiHd1d(const HistData1d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataSerr1d* const out);
    void GetResChiHd1d(const HistData1d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       HistDataTerr1d* const out);

    void GetResChiHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataSerr1d* const out);
    void GetResChiHd1d(const HistData1d* const data,
                       const HistDataNerr1d* const func,
                       HistDataTerr1d* const out);    

    void FillGd1d(const GraphDataNerr2d* const gd2d,
                  HistDataNerr1d* const out);

    
    // power spectrum
    void GetPowSpec(const HistData1d* const in,
                    HistDataNerr1d* const out);
    void GetPowSpecLeahyNorm(const HistData1d* const in,
                             HistDataNerr1d* const out);
    void GetPowSpecNonfft(const HistData1d* const in,
                          HistDataNerr1d* const out);
    
    void GetPowSpecDecomp(long mbin, const HistData1d* const in,
                          HistDataNerr1d* const out);
    void GetPowSpecDecompNonfft(long mbin, const HistData1d* const in,
                                HistDataNerr1d* const out);
    void GetAutoCorr(const HistData1d* const in,
                     HistDataNerr1d* out);
    void GetCrossCorr(const HistData1d* const in1,
                      const HistData1d* const in2,
                      HistDataNerr1d* const out);
    
    // Init & Set by graph2d, only if xval_arr of graph2d is the same as hist_info
    HistData1d* const GenHd1dByHistInfoAndGraphData2d(const HistInfo1d* const hist_info,
                                                      const GraphData2d* const g2d);

    void IsValidForSetByGd2d(const HistData1d* const hd1d,
                             const GraphData2d* const gd2d);
    
} // namespace HistData1dOpe

#endif // MORIIISM_MITOOL_MIROOTLIB_HIST1D_OPE_H_
