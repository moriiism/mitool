#ifndef MORIIISM_MITOOL_MIMINUITLIB_FITFUNC_H_
#define MORIIISM_MITOOL_MIMINUITLIB_FITFUNC_H_

#include "Minuit2/MnPrint.h"
#include "Minuit2/MnMigrad.h"
#include "Minuit2/MnMinos.h"
#include "Minuit2/MinosError.h"
#include "Minuit2/MnUserParameters.h"
#include "Minuit2/MnUserParameterState.h"
#include "Minuit2/MnMinimize.h"
#include "Minuit2/MnScan.h"
#include "Minuit2/MnSimplex.h"
#include "Minuit2/MnFumiliMinimize.h"
#include "Minuit2/Minuit2Minimizer.h"

#include "mim_fitstat_hg.h"

namespace FitFunc
{
    ROOT::Minuit2::FunctionMinimum GenExecFit(MinFcn* const minfcn,
                                              const FitParam* const fit_param,
                                              FitStat** const fit_stat_ptr,
                                              double value_in_sigma_or_cl = 1.0,
                                              string sigma_or_cl = "sigma",
                                              int as_npar = 1,
                                              double tolerance = 0.1,
                                              int maxfcn = 0);

    // Manual for ROOT::Minuit2::MnApplication::operator():
    // 
    //   maxfcn: max number of function calls (if = 0) default is used which is set to
    //           200 + 100 * npar + 5 * npar**2
    // tolerance: value used for terminating iteration procedure. For example, MIGRAD will stop
    //           iterating when edm (expected distance from minimum) will be:
    //           edm < tolerance * 10**-3 Default value of tolerance used is 0.1

    ROOT::Minuit2::FunctionMinimum GenExecFitSimplex(MinFcn* const minfcn,
                                                     const FitParam* const fit_param,
                                                     FitStat** const fit_stat_ptr,
                                                     double value_in_sigma_or_cl = 1.0,
                                                     string sigma_or_cl = "sigma",
                                                     int as_npar = 1,
                                                     double tolerance = 0.1,
                                                     int maxfcn = 0);
    void GetAsymErr(MinFcn* const minfcn,
                    const FitParam* const fit_param,
                    ROOT::Minuit2::FunctionMinimum function_minimum, // migrad result                    
                    FitStat* const fit_stat_out,
                    double value_in_sigma_or_cl = 1.0,
                    string sigma_or_cl = "sigma",
                    double tolerance = 0.1,
                    int maxfcn = 0);
  
    double GetErrBySecant(MinFcn* const minfcn,
                          const FitParam* const fit_param,
                          int ipar, double par_best,
                          double par_init_lo, double par_init_up,
                          double minfcn_aim, 
                          double minfcn_diff_precision,
                          double tolerance = 0.1,
                          int maxfcn = 0);

    void GenFitStatForParSearch1d(MinFcn* const minfcn, const FitParam* const fit_param,
                                  const Chi2PlotPar* const chi2plot_par,
                                  FitStat**** const fit_stat_arr_ptr,
                                  double tolerance = 0.1,
                                  int maxfcn = 0);

    void DelFitStatForParSearch1d(const Chi2PlotPar* const chi2plot_par,
                                  FitStat*** fit_stat_arr);
    
    void GenParSearch1d(const FitStat* const* const* const fit_stat_arr,
                        const Chi2PlotPar* const chi2plot_par,
                        HistData1d*** const hist_chi2_arr_ptr,
                        HistData1d*** const hist_valid_arr_ptr,
                        HistData1d*** const hist_edm_arr_ptr,
                        HistData1d*** const hist_flag_bad_neg_arr_ptr,
                        HistData1d**** const hist_index1_arr_ptr);

    void DelParSearch1d(const Chi2PlotPar* const chi2plot_par,
                        HistData1d** hist_chi2_arr,
                        HistData1d** hist_valid_arr,
                        HistData1d** hist_edm_arr,
                        HistData1d** hist_flag_bad_neg_arr,
                        HistData1d*** hist_index1_arr);

    void GenFitStatForParSearch2d(MinFcn* const minfcn, const FitParam* const fit_param,
                                  const Chi2PlotContPar* const chi2plot_cont_par,
                                  FitStat***** const fit_stat_arr_ptr,
                                  double tolerance = 0.1,
                                  int maxfcn = 0);

    void DelFitStatForParSearch2d(const Chi2PlotContPar* const chi2plot_cont_par,
                                  FitStat**** fit_stat_arr);

    void GenParSearch2d(const FitStat* const* const* const* const fit_stat_arr,
                        const Chi2PlotContPar* const chi2plot_cont_par,
                        HistData2d*** const hist_chi2_cont_arr_ptr,
                        HistData2d*** const hist_valid_cont_arr_ptr,
                        HistData2d*** const hist_edm_cont_arr_ptr,
                        HistData2d*** const hist_flag_bad_neg_cont_arr_ptr,
                        HistData2d**** const hist_index2_cont_arr_ptr);

    void DelParSearch2d(const Chi2PlotContPar* const chi2plot_cont_par,
                        HistData2d** hist_chi2_cont_arr,
                        HistData2d** hist_valid_cont_arr,
                        HistData2d** hist_edm_cont_arr,
                        HistData2d** hist_flag_bad_neg_cont_arr,
                        HistData2d*** hist_index2_cont_arr);
    
    void GenFitStatHG(FILE* fp_log, MinFcn* const minfcn, const FitParam* const fit_param,
                      Chi2PlotPar* const chi2plot_par,
                      Chi2PlotContPar* const chi2plot_cont_par,
                      FitStatHG** const fit_stat_hg_ptr,
                      double value_in_sigma_or_cl = 1.0,
                      string sigma_or_cl = "sigma",
                      int as_npar = 1,
                      double tolerance = 0.1,
                      int maxfcn = 0);

} // namespace FitFunc

#endif // MORIIISM_MITOOL_MIMINUITLIB_FITFUNC_H_
