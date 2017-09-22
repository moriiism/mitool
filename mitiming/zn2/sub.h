#ifndef MXKWTOOL_MXKWTIMING_ZN2_SUB_H_
#define MXKWTOOL_MXKWTIMING_ZN2_SUB_H_

#include "mxkw_data.h"
#include "mxkw_hist2d.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_timing_zn2.h"

void GenZn2Nu(const DataArray1d* const data_arr, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nharmonics,
              HistData1d** h1d_zn2_ptr);

void GenZn2NuNuDot(const DataArray1d* const data_arr, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nharmonics,
                   HistData2d**  h2d_zn2_ptr,
                   HistData1d*** h1d_zn2_arr_ptr);

void GenZn2Nu(const GraphData2d* const g2d, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nharmonics,
              HistData1d** h1d_zn2_ptr);

void GenZn2NuNuDot(const GraphData2d* const g2d, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nharmonics,
                   HistData2d**  h2d_zn2_ptr,
                   HistData1d*** h1d_zn2_arr_ptr);

#endif // MXKWTOOL_MXKWTIMING_ZN2_SUB_H_
