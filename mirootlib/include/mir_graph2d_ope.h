#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_

#include "mir_geom.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"

namespace GraphData2dOpe
{
    void GetMotion(const GraphData2d* const gd2d,
                   double shiftx, double shifty, double angle, int flag,
                   GraphDataNerr2d* const gd2d_out);
    
    GraphData2d* const GenGd2dByLoad(string file, string format);

    
    // select_type: center, varbinwidth, exclusive
    //   center:      select a bin whose center is located in an interval.
    //   varbinwidth: select a bin whose center is located in an interval and
    //                change the bin width to be included in the interval.
    //   exclusive:   select only the full bins, meaning to exclude bins at the interval edge.

    void GetSelectGd2dByIntervalCenter(const GraphData2d* const graph_data,
                                       const Interval* const interval,
                                       GraphDataNerr2d* const graph_out);
    void GetSelectGd2dByIntervalCenter(const GraphData2d* const graph_data,
                                       const Interval* const interval,
                                       GraphDataSerr2d* const graph_out);
    void GetSelectGd2dByIntervalCenter(const GraphData2d* const graph_data,
                                       const Interval* const interval,
                                       GraphDataTerr2d* const graph_out);
    void GetSelectGd2dByIntervalExclusive(const GraphData2d* const graph_data,
                                          const Interval* const interval,
                                          GraphDataNerr2d* const graph_out);
    void GetSelectGd2dByIntervalExclusive(const GraphData2d* const graph_data,
                                          const Interval* const interval,
                                          GraphDataSerr2d* const graph_out);
    void GetSelectGd2dByIntervalExclusive(const GraphData2d* const graph_data,
                                          const Interval* const interval,
                                          GraphDataTerr2d* const graph_out);
    void GetSelectGd2dByIntervalVarbinwidth(const GraphData2d* const graph_data,
                                            const Interval* const interval,
                                            GraphDataTerr2d* const graph_out);      
  
    void GenSelectGd2dArrByIntervalCenterNerr(const GraphData2d* const graph_data,
                                              const Interval* const interval,
                                              GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalCenterSerr(const GraphData2d* const graph_data,
                                              const Interval* const interval,
                                              GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalCenterTerr(const GraphData2d* const graph_data,
                                              const Interval* const interval,
                                              GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalExclusiveNerr(const GraphData2d* const graph_data,
                                                 const Interval* const interval,
                                                 GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalExclusiveSerr(const GraphData2d* const graph_data,
                                                 const Interval* const interval,
                                                 GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalExclusiveTerr(const GraphData2d* const graph_data,
                                                 const Interval* const interval,
                                                 GraphData2d*** const gd2d_arr_ptr);
    void GenSelectGd2dArrByIntervalVarbinwidthTerr(const GraphData2d* const graph_data,
                                                   const Interval* const interval,
                                                   GraphData2d*** const gd2d_arr_ptr);

    void GetGd2dByMergeGd2dArr(long ngraph,
                               const GraphData2d* const* const gd2d_arr,
                               GraphDataNerr2d* const gd2d_out);
    void GetGd2dByMergeGd2dArr(long ngraph,
                               const GraphData2d* const* const gd2d_arr,
                               GraphDataSerr2d* const gd2d_out);
    void GetGd2dByMergeGd2dArr(long ngraph,
                               const GraphData2d* const* const gd2d_arr,
                               GraphDataTerr2d* const gd2d_out);
    

    void GetResValGd2d(const GraphData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       GraphDataNerr2d* const out);
    void GetResValGd2d(const GraphData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       GraphDataSerr2d* const out);
    void GetResValGd2d(const GraphData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       GraphDataTerr2d* const out);
  
    void GetResRatioGd2d(const GraphData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         GraphDataNerr2d* const out);
    void GetResRatioGd2d(const GraphData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         GraphDataSerr2d* const out);
    void GetResRatioGd2d(const GraphData2d* const data,
                         const MirFunc* const func,
                         const double* const par,
                         GraphDataTerr2d* const out);

    void GetResChiGd2d(const GraphData2d* const data,
                       const MirFunc* const func,
                       const double* const par,
                       GraphDataSerr2d* const out);

    double GetIntegral(const GraphData2d* const gd2d,
                       double xval_lo, double xval_up);
    double GetIntegralPlus(const GraphData2d* const gd2d,
                           double xval_lo, double xval_up);
    double GetIntegralByTrapezoidApprox(const GraphData2d* const gd2d,
                                        long idata_st, long idata_ed);
    
    GraphDataSerr2d* const GenGd2dBinBySigVar(const GraphData2d* const gd2d,
                                              double pval_threshold);
    GraphDataSerr2d* const GenGd2dBinBySigDet(const GraphData2d* const gd2d,
                                              double pval_threshold);

    void GetPoint2dSerrByBinning(long narr,
                                 const double* const xval_arr,
                                 const double* const xval_serr_arr,
                                 const double* const oval_arr,
                                 const double* const oval_serr_arr,
                                 double* const xval_bin_center_ptr,
                                 double* const xval_bin_half_width_ptr,
                                 double* const wmean_ptr,
                                 double* const wmean_err_ptr);
    void GetPoint2dSerrByBinning(vector<double> xval_vec,
                                 vector<double> xval_serr_vec,
                                 vector<double> oval_vec,
                                 vector<double> oval_serr_vec,
                                 double* const xval_bin_center_ptr,
                                 double* const xval_bin_half_width_ptr,
                                 double* const wmean_ptr,
                                 double* const wmean_err_ptr);

    
}  // namespace GraphData2dOpe

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_
