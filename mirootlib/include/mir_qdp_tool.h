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
                           string title,
                           double offset);
    void PrintQdpScale(FILE* fp, string xy, string scale);
    void PrintQdpCmdDiffPlot(FILE* fp,
                             double xval_lo_data, double xval_up_data,
                             double oval_lo_w1_data, double oval_up_w1_data,
                             double oval_lo_w2_data, double oval_up_w2_data,
                             double offset_xval,
                             double offset_oval,
                             double offset_oval_res,
                             string title_xval,
                             string title_oval,
                             string title_oval_res,
                             string scale_xval,
                             string scale_oval,
                             string scale_oval_res);
    void PrintQdpCmdDiffPlot(FILE* fp,
                             double xval_lo_data, double xval_up_data,
                             double oval_lo_w1_data, double oval_up_w1_data,
                             double oval_lo_w2_data, double oval_up_w2_data,
                             double offset_xval,
                             double offset_oval,
                             double offset_oval_res,
                             const MirPlotConf* const plot_conf);

    // format: index  data
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    string title_oval = "",
                    double offset_oval = 0.0,
                    string scale_xval = "lin",
                    string scale_oval = "lin");
    void MkQdpMode1(const DataArray1d* const data_array,
                    string qdpout,
                    const MirPlotConf* const plot_conf);

    // format: data  1.0
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    string title_xval = "",
                    double offset_xval = 0.0,
                    string scale_xval = "lin");
    void MkQdpMode2(const DataArray1d* const data_array,
                    string qdpout,
                    const MirPlotConf* const plot_conf);
    
    void MkQdp(const GraphData2d* const graph_data,
               string qdpout,
               string format,
               string title_xval = "",
               string title_oval = "",
               double offset_xval = 0.0,
               double offset_oval = 0.0,
               string scale_xval = "lin",
               string scale_oval = "lin",
               int flag_line = 0,
               int flag_mark = 1);
    void MkQdp(const GraphData2d* const graph_data,
               string qdpout,
               string format,
               const MirPlotConf* const plot_conf,
               int flag_line = 0,
               int flag_mark = 1);

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

    // graph_data, func
    void MkQdpDiff3Serr(const GraphData2d* const graph_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff3Serr(const GraphData2d* const graph_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MirPlotConf* const plot_conf);

    void MkQdpDiff2Terr(const GraphData2d* const graph_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff2Terr(const GraphData2d* const graph_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MirPlotConf* const plot_conf);

    // hist_data, func
    void MkQdpDiff3Serr(const HistData1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff3Serr(const HistData1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MirPlotConf* const plot_conf);

    void MkQdpDiff2Terr(const HistData1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        string title_xval = "",
                        string title_oval = "",
                        double offset_xval = 0.0,
                        double offset_oval = 0.0,
                        string scale_xval = "lin",
                        string scale_oval = "lin");
    void MkQdpDiff2Terr(const HistData1d* const hist_data,
                        const MirFunc* const func, const double* const par,
                        int npoint_func,
                        string outdir, string qdpout_head,
                        const MirPlotConf* const plot_conf);

    // plot N HistData in one qdp file
    void MkQdpNhist(const HistData1d* const* const hist_arr, int nhist,
                    string qdpout,
                    double offset_xval = 0.0);

    void MkQdpProj(const MirFunc* const func, const double* const par,
                   double xval_lo, double xval_up, double yval_lo, double yval_up,
                   string outdir, string qdpout_head, string calc_mode,
                   int npoint_func,
                   string title_xval = "",
                   string title_yval = "",
                   string title_oval = "",
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0,
                   string scale_xval = "lin",
                   string scale_yval = "lin",
                   string scale_oval = "lin");
    void MkQdpProj(const MirFunc* const func, const double* const par,
                   double xval_lo, double xval_up, double yval_lo, double yval_up,
                   string outdir, string qdpout_head, string calc_mode,
                   int npoint_func,
                   const MirPlotConf* const plot_conf_projx,
                   const MirPlotConf* const plot_conf_projy);
    
    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
                       const MirFunc* const func, const double* const par,
                       string outdir, string qdpout_head,
                       string add_mode, string error_mode,
                       string title_xval = "",
                       string title_yval = "",
                       string title_oval = "",                              
                       double offset_xval = 0.0,
                       double offset_yval = 0.0,
                       double offset_oval = 0.0,
                       string scale_xval = "lin",
                       string scale_yval = "lin",
                       string scale_oval = "lin");
    void MkQdpDiffProj(const HistDataSerr2d* const hist_data,
                       const MirFunc* const func, const double* const par,
                       string outdir, string qdpout_head,
                       string add_mode, string error_mode,
                       const MirPlotConf* const plot_conf_projx,
                       const MirPlotConf* const plot_conf_projy);
}

#endif // MORIIISM_MITOOL_MIROOTLIB_QDP_TOOL_H_
