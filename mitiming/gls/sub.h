#ifndef MORIIISM_MITOOL_MITIMING_GLS_SUB_H_
#define MORIIISM_MITOOL_MITIMING_GLS_SUB_H_

#include "mir_data1d_nerr.h"
#include "mir_hist1d_ope.h"
#include "mir_hist2d_nerr.h"
#include "mit_timeconv.h"
#include "mit_gls.h"
#include "mir_qdp_tool.h"

HistData1d* const GenHd1dGls(const GraphDataSerr2d* const gd2d_sec,
                             long nnu, double nu_lo, double nu_up);

HistData2d* const GenHd2dGls(const GraphDataSerr2d* const gd2d_sec,
                             int nnu, double nu_lo, double nu_up,
                             long nratio, double ratio_lo, double ratio_up,
                             double epoch_sec);

#endif // MORIIISM_MITOOL_MITIMING_GLS_SUB_H_
