#ifndef MORIIISM_MITOOL_MITIMING_EFS_SUB_H_
#define MORIIISM_MITOOL_MITIMING_EFS_SUB_H_

#include "mir_data1d_nerr.h"
#include "mir_data1d_ope.h"
#include "mir_hist2d.h"
#include "mit_eph.h"
#include "mit_timeconv.h"
#include "mit_folding.h"
#include "mit_pulseprof_stat.h"
#include "mit_binary_orb.h"
#include "mit_gti.h"

void GenEfsNu(const DataArray1d* const data_arr, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nbin,
              HistData1d** h1d_chi2_ptr,
              Ephemeris** eph_best_ptr,
              HistDataSerr1d** h1d_pls_best_ptr);

void GenEfsNuNuDot(const DataArray1d* const data_arr, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nbin,
                   HistData2d**  h2d_chi2_ptr,
                   HistData1d*** h1d_chi2_arr_ptr,
                   Ephemeris** eph_best_ptr,
                   HistDataSerr1d** h1d_pls_best_ptr);

void GenEfsNu(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
              int nbin_nu, double nu_lo, double nu_up,
              double nu_dot,
              double epoch_mjd, int nbin,
              HistData1d** h1d_chi2_ptr,
              Ephemeris** eph_best_ptr,
              HistDataSerr1d** h1d_pls_best_ptr);

void GenEfsNuNuDot(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
                   int nbin_nu, double nu_lo, double nu_up,
                   int nbin_nudot, double nudot_lo, double nudot_up,
                   double nu_dot2,
                   double epoch_mjd, int nbin,
                   HistData2d**  h2d_chi2_ptr,
                   HistData1d*** h1d_chi2_arr_ptr,
                   Ephemeris** eph_best_ptr,
                   HistDataSerr1d** h1d_pls_best_ptr);

// orbmod

void GenEfsNuOrbAmp(const DataArray1d* const data_arr, double mjdref, string tunit,
                    int nbin_nu, double nu_lo, double nu_up,
                    int nbin_orbamp, double orbamp_lo, double orbamp_up,
                    double epoch_mjd, int nbin,
                    HistData2d**  h2d_chi2_ptr,
                    HistData1d*** h1d_chi2_arr_ptr,
                    Ephemeris** eph_best_ptr,
                    HistDataSerr1d** h1d_pls_best_ptr);

void GenEfsNuOrbmod(const GraphDataSerr2d* const g2d, double mjdref, string tunit,
                    int nbin_nu, double nu_lo, double nu_up,
                    int nbin_orbamp, double orbamp_lo, double orbamp_up,
                    double epoch_mjd, int nbin,
                    HistData2d**  h2d_chi2_ptr,
                    HistData1d*** h1d_chi2_arr_ptr,
                    Ephemeris** eph_best_ptr,
                    HistDataSerr1d** h1d_pls_best_ptr);




#endif // MORIIISM_MITOOL_MITIMING_EFS_SUB_H_
