#ifndef MXKWTOOL_MXKWTIMING_GLS_SUB_H_
#define MXKWTOOL_MXKWTIMING_GLS_SUB_H_

#include "mxkw_data.h"
#include "mxkw_hist1d_ope.h"
#include "mxkw_hist2d.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_timing_gls.h"
#include "mxkw_qdp_tool.h"

HistData1d* const GenHd1dGls(const GraphDataSerr2d* const gd2d_sec,
                             long nnu, double nu_lo, double nu_up);

HistData2d* const GenHd2dGls(const GraphDataSerr2d* const gd2d_sec,
                             int nnu, double nu_lo, double nu_up,
                             long nratio, double ratio_lo, double ratio_up,
                             double epoch_sec);

#endif // MXKWTOOL_MXKWTIMING_GLS_SUB_H_
