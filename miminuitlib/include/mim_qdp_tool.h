#ifndef MORIIISM_MITOOL_MIMINUITLIB_QDP_TOOL_H_
#define MORIIISM_MITOOL_MIMINUITLIB_QDP_TOOL_H_

#include "mir_plot_conf.h"

namespace MimQdpTool
{
    void MkQdpMinFcn(const HistData1d* const hist_data,
                     string outqdp,
                     double xval_at_fcnmin,
                     double xval_terr_minus,
                     double xval_terr_plus,
                     double fcnmin,
                     string title_xval = "");
    void MkQdpCont(const HistData2d* const h2d,
                   string qdpout, int ncont,
                   string title_xval = "",
                   string title_yval = "",
                   string title_oval = "",
                   double offset_xval = 0.0,
                   double offset_yval = 0.0,
                   double offset_oval = 0.0);
    void MkQdpContMinFcn(const HistData2d* const h2d,
                         string qdpout,
                         string title_xval = "",
                         string title_yval = "",
                         string title_oval = "",
                         double offset_xval = 0.0,
                         double offset_yval = 0.0,
                         double offset_oval = 0.0);
    void MkQdpContMinFcnWithBest(const HistData2d* const h2d,
                                 string qdpout,
                                 double xval_best,
                                 double yval_best,
                                 double zval_best,
                                 string title_xval = "",
                                 string title_yval = "",
                                 string title_oval = "",
                                 double offset_xval = 0.0,
                                 double offset_yval = 0.0,
                                 double offset_oval = 0.0);
}

#endif // MORIIISM_MITOOL_MIMINUITLIB_QDP_TOOL_H_
