#ifndef MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_

#include "mir_graph2d.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"

namespace GraphData2dOpe
{

    void ReadInfo(string file, int* flag_xval_sorted_ptr);

    GraphData2d* const GenGd2dByLoad(string file, string format);

    // select_type: center, varbinwidth, exclusive
    //   center:      select a bin whose center is located in an interval.
    //   varbinwidth: select a bin whose center is located in an interval and
    //                change the bin width to be included in the interval.
    //   exclusive:   select only the full bins, meaning to exclude bins at the interval edge.

    void GetSelectG2dByInterval(const GraphData2d* const graph_data,
                                const Interval* const interval,
                                GraphData2d* const graph_out);
    void GetSelectG2dByInterval(const GraphDataSerr2d* const graph_data,
                                const Interval* const interval,
                                GraphDataSerr2d* const graph_out,
                                string select_type = "exclusive");
    void GetSelectG2dByInterval(const GraphDataTerr2d* const graph_data,
                                const Interval* const interval,
                                GraphDataTerr2d* const graph_out,
                                string select_type = "exclusive");
    
    
    void GenSelectG2dArrByInterval(const GraphData2d* const graph_data,
                                   const Interval* const interval,
                                   GraphData2d*** g2d_arr_ptr);
    void GenSelectG2dArrByInterval(const GraphDataSerr2d* const graph_data,
                                   const Interval* const interval,
                                   GraphDataSerr2d*** g2d_arr_ptr,
                                   string select_type = "exclusive");
    void GenSelectG2dArrByInterval(const GraphDataTerr2d* const graph_data,
                                   const Interval* const interval,
                                   GraphDataTerr2d*** g2d_arr_ptr,
                                   string select_type = "exclusive");

    GraphDataSerr2d* const GenGd2dByMergeGd2dArr(long ngraph,
                                                 const GraphDataSerr2d* const* const gd2d_arr);

    void GetResValGd2(const GraphData2d* const graph_data,
                      const MirFunc* const func,
                      const double* const par,
                      GraphData2d* const graph_res_out);
    void GetResValGd2(const GraphDataSerr2d* const graph_data,
                      const MirFunc* const func,
                      const double* const par,
                      GraphDataSerr2d* const graph_res_out);
    void GetResValGd2(const GraphDataTerr2d* const graph_data,
                      const MirFunc* const func,
                      const double* const par,
                      GraphDataTerr2d* const graph_res_out);
  
    void GetResRatioGd2(const GraphData2d* const graph_data,
                        const MirFunc* const func,
                        const double* const par,
                        GraphData2d* const graph_res_out);
    void GetResRatioGd2(const GraphDataSerr2d* const graph_data,
                        const MirFunc* const func,
                        const double* const par,
                        GraphDataSerr2d* const graph_res_out);
    void GetResRatioGd2(const GraphDataTerr2d* const graph_data,
                        const MirFunc* const func,
                        const double* const par,
                        GraphDataTerr2d* const graph_res_out);

    void GetResChiGd2(const GraphDataSerr2d* const graph_data,
                      const MirFunc* const func,
                      const double* const par,
                      GraphDataSerr2d* const graph_res_out);
    void GetResChiGd2(const GraphDataTerr2d* const graph_data,
                      const MirFunc* const func,
                      const double* const par,
                      GraphDataTerr2d* const graph_res_out);

    GraphDataSerr2d* const GenGd2dBinBySigVar(const GraphDataSerr2d* const gd2d,
                                              double pval_threshold);

    GraphDataSerr2d* const GenGd2dBinBySigDet(const GraphDataSerr2d* const gd2d,
                                              double pval_threshold);


    void GetValBinned(vector<double> xval_vec,
                      vector<double> xval_serr_vec,
                      vector<double> oval_vec,
                      vector<double> oval_serr_vec,
                      double* xval_bin_center_ptr,
                      double* xval_bin_half_width_ptr,
                      double* wmean_ptr,
                      double* wmean_err_ptr);
    
}  // namespace GraphData2dOpe

#endif // MORIIISM_MITOOL_MIROOTLIB_GRAPH2D_OPE_H_
