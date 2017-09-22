#ifndef MXKWTOOL_MXKWTIMING_POW_SUB_H_
#define MXKWTOOL_MXKWTIMING_POW_SUB_H_

#include "mxkw_data.h"
#include "mxkw_hist1d_ope.h"
#include "mxkw_hist2d.h"
#include "mxkw_timing_eph.h"
#include "mxkw_timing_timeconv.h"
#include "mxkw_timing_pulseprof_stat.h"
#include "mxkw_qdp_tool.h"

void GenPow(const DataArray1d* const data_arr, double mjdref, string tunit,
            double tbinfwidth, 
            int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
            double epoch_mjd, string powspec_type,
            HistData1d** h1d_pow_max_ptr,
            HistData1d** h1d_pow_amean_ptr,
            HistData1d** h1d_pow_num_ptr);


// type of the light curve must be "bin_count"
void GenPow(const GraphData2d* const g2d, double mjdref, string tunit,
            double tbinfwidth, 
            int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
            double epoch_mjd, string powspec_type,
            HistData1d** h1d_pow_max_ptr,
            HistData1d** h1d_pow_amean_ptr,
            HistData1d** h1d_pow_num_ptr,
            GraphData2d** g2d_pow_sel_ptr);

void GenPowRatio(const DataArray1d* const data_arr,
                 double mjdref, string tunit,
                 double tbinfwidth,
                 int nbin_nu_plot, double nu_plot_lo, double nu_plot_up,
                 long nbin_ratio, double ratio_lo, double ratio_up,
                 double epoch_mjd, string powspec_type,
                 HistData2d** h2d_pow_max_ptr,
                 HistData2d** h2d_pow_amean_ptr,
                 HistData2d** h2d_pow_num_ptr,
                 HistData1d*** h1d_pow_max_arr_ptr);



#endif // MXKWTOOL_MXKWTIMING_POW_SUB_H_
