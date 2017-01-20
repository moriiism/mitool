#ifndef MORIIISM_MITOOL_MIROOTLIB_QDP_TOOL_H_
#define MORIIISM_MITOOL_MIROOTLIB_QDP_TOOL_H_

#include "mir_plot_conf.h"

#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_graph2d_ope.h"

#include "mir_hist1d_nerr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist1d_terr.h"
#include "mir_hist1d_ope.h"

#include "mir_hist2d_nerr.h"
#include "mir_hist2d_serr.h"
#include "mir_hist2d_terr.h"
#include "mir_hist2d_ope.h"


namespace MirQdpTool
{
    void GetRangeQdp(double min, double max,
                     double* const low_ptr, double* const up_ptr);
    
    void PrintQdpRead(FILE* fp, string format);
    void PrintQdpCmdStd(FILE* fp);
    void PrintQdpAxisRescale(FILE* fp, string xy,
                             double val_lo, double val_up);
    void PrintQdpAxisTitle(FILE* fp, string xy,
                           string title, double offset);
    void PrintQdpScale(FILE* fp, string xy, string scale);

    // format: index  data
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    string title_oval,
                    double offset_oval,
                    string scale_xval = "lin",
                    string scale_oval = "lin");
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    const MirPlotConf* const plot_conf);

    // format: data  1.0
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    string title_xval,
                    double offset_xval,
                    string scale_xval = "lin");
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    const MirPlotConf* const plot_conf);
    
    // also valid for GraphDataSerr2d, GraphDataTerr2d by polymorphism
    void MkQdp(const GraphData2d* const graph_data,
               string qdpout,
               string format,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin");
    void MkQdp(const GraphData2d* const graph_data,
               string qdpout,
               string format,
               const MirPlotConf* const plot_conf);

    // also valid for HistDataSerr1d, HistDataTerr1d by polymorphism
    void MkQdp(const HistData1d* const hist_data,
               string outqdp,
               string format,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin");
    void MkQdp(const HistData1d* const hist_data,
               string outqdp,
               string format,
               const MirPlotConf* const plot_conf);

    void MkQdp(const MirFunc* const func, const double* const par,
               int npoint, double xval_lo, double xval_up,
               string outqdp,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin");
    void MkQdp(const MirFunc* const func, const double* const par,
               int npoint, double xval_lo, double xval_up,
               string outqdp,
               const MirPlotConf* const plot_conf);

    void MkQdp(const Interval* const interval,
               string qdpout,
               string title_xval = "",
               double offset_xval = 0.0,
               string scale_xval = "lin");
    void MkQdp(const Interval* const interval,
               string qdpout,
               const MirPlotConf* const plot_conf);

    void MkQdpDiff(const GraphData2d* const graph_data,
                   const GraphData2d* const graph_model,
                   const GraphData2d* const graph_res,
                   string qdpout,
                   string format,
                   string title_xval = "",
                   string title_oval = "",
                   string title_oval_res = "",
                   double offset_xval = 0.0,
                   double offset_oval = 0.0,
                   double offset_oval_res = 0.0,
                   string scale_xval = "lin",
                   string scale_oval = "lin",
                   string scale_oval_res = "lin");
    void MkQdpDiff(const GraphData2d* const graph_data,
                   const GraphData2d* const graph_model,
                   const GraphData2d* const graph_res,
                   string qdpout,
                   string format,
                   const MirPlotConf* const plot_conf);
    
    void MkQdpDiff(const HistData1d* const hist_data,
                   const HistData1d* const hist_model,
                   const HistData1d* const hist_res,
                   string qdpout,
                   string format,
                   string title_xval = "",
                   string title_oval = "",
                   string title_oval_res = "",
                   double offset_xval = 0.0,
                   double offset_oval = 0.0,
                   double offset_oval_res = 0.0,
                   string scale_xval = "lin",
                   string scale_oval = "lin",
                   string scale_oval_res = "lin");
    void MkQdpDiff(const HistData1d* const hist_data,
                   const HistData1d* const hist_model,
                   const HistData1d* const hist_res,
                   string qdpout,
                   string format,
                   const MirPlotConf* const plot_conf);
    
    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
                    const MirFunc* const func, const double* const par,
                    int npoint_func,
                    string outdir, string qdpout_head,
                    string title_xval = "",
                    string title_oval = "",
                    double offset_xval = 0.0,
                    double offset_oval = 0.0,
                    string scale_xval = "lin",
                    string scale_oval = "lin");
    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
                    const MirFunc* const func, const double* const par,
                    int npoint_func,
                    string outdir, string qdpout_head,
                    const MirPlotConf* const plot_conf);
    void MkQdpDiff3(const GraphDataSerr2d* const graph_data,
                    const GraphData2d* const graph_model,
                    string outdir, string qdpout_head,
                    const MirPlotConf* const plot_conf);
    
    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
                    const MirFunc* const func, const double* const par,
                    int npoint_func,
                    string outdir, string qdpout_head,
                    string title_xval = "",
                    string title_oval = "",
                    double offset_xval = 0.0,
                    double offset_oval = 0.0,
                    string scale_xval = "lin",
                    string scale_oval = "lin");
    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
                    const MirFunc* const func, const double* const par,
                    int npoint_func,
                    string outdir, string qdpout_head,
                    const MirPlotConf* const plot_conf);
    void MkQdpDiff3(const HistDataSerr1d* const hist_data,
                    const HistData1d* const hist_model,
                    string outdir, string qdpout_head,
                    const MirPlotConf* const plot_conf);

    void MkQdpMinFcn(const HistData1d* const hist_data,
                     string outqdp,
                     double xval_at_fcnmin,
                     double xval_terr_minus,
                     double xval_terr_plus,
                     double fcnmin,
                     string title_xval = "");
    
    // plot N HistData in one qdp file
    void MkQdpNhist(const HistData1d* const* const hist_arr, int nhist,
                    string qdpout,
                    double offset_xval = 0.0);

//    void MkQdpProj(const MirFunc* const func, const double* const par,
//                   double xval_lo, double xval_up, double yval_lo, double yval_up,
//                   string outdir, string qdpout_head, string calc_mode,
//                   int npoint_func,
//                   string title_xval = "",
//                   string title_yval = "",
//                   string title_oval = "",
//                   double offset_xval = 0.0,
//                   double offset_yval = 0.0,
//                   double offset_oval = 0.0,
//                   string scale_xval = "lin",
//                   string scale_yval = "lin",
//                   string scale_oval = "lin");
//    void MkQdpProj(const MirFunc* const func, const double* const par,
//                   double xval_lo, double xval_up, double yval_lo, double yval_up,
//                   string outdir, string qdpout_head, string calc_mode,
//                   int npoint_func,
//                   const MirPlotConf* const plot_conf_projx,
//                   const MirPlotConf* const plot_conf_projy);
//    
//    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
//                       const MirFunc* const func, const double* const par,
//                       string outdir, string qdpout_head,
//                       string add_mode, string error_mode,
//                       string title_xval = "",
//                       string title_yval = "",
//                       string title_oval = "",                              
//                       double offset_xval = 0.0,
//                       double offset_yval = 0.0,
//                       double offset_oval = 0.0,
//                       string scale_xval = "lin",
//                       string scale_yval = "lin",
//                       string scale_oval = "lin");
//    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
//                       const MirFunc* const func, const double* const par,
//                       string outdir, string qdpout_head,
//                       string add_mode, string error_mode,
//                       const MirPlotConf* const plot_conf_projx,
//                       const MirPlotConf* const plot_conf_projy);
//    
//    void MkQdpCont(const HistData2d* const h2d,
//                   string qdpout, int ncont,
//                   string title_xval = "",
//                   string title_yval = "",
//                   string title_oval = "",
//                   double offset_xval = 0.0,
//                   double offset_yval = 0.0,
//                   double offset_oval = 0.0);
//
//    void MkQdpContMinFcn(const HistData2d* const h2d,
//                         string qdpout,
//                         string title_xval = "",
//                         string title_yval = "",
//                         string title_oval = "",
//                         double offset_xval = 0.0,
//                         double offset_yval = 0.0,
//                         double offset_oval = 0.0);
//
//    void MkQdpContMinFcnWithBest(const HistData2d* const h2d,
//                                 string qdpout,
//                                 double xval_best,
//                                 double yval_best,
//                                 double zval_best,
//                                 string title_xval = "",
//                                 string title_yval = "",
//                                 string title_oval = "",
//                                 double offset_xval = 0.0,
//                                 double offset_yval = 0.0,
//                                 double offset_oval = 0.0);
    
}

#endif // MORIIISM_MITOOL_MIROOTLIB_QDP_TOOL_H_
