#ifndef MORIIISM_MITOOL_MIMINUITLIB_LS_H_
#define MORIIISM_MITOOL_MIMINUITLIB_LS_H_

//
// Least square fit
//

#include "TMatrixD.h"
#include "TDecompSVD.h"
#include "TQpDataDens.h"
#include "TQpProbDens.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TQpProbDens.h"
#include "TGondzioSolver.h"

#include "mifc_gen.h"
#include "mir_func_ope.h"
#include "mifc_ctn.h"
#include "mir_graph2d.h"
#include "mir_hist2d.h"
#include "mim_tie.h"

namespace MimLS
{

    void GenLeastSquarePoissonQuadProgPlus(int ndata,
                                           const double* const xval_arr,
                                           const double* const oval_arr,
                                           int nfunc,
                                           const MirFunc* const* const func_arr,
                                           const MirFuncPar* const* const func_par_arr,
                                           double** const par_best_arr_ptr,
                                           double* const chi2_min_ptr,
                                           double* const aic_ptr,
                                           double* const bic_ptr);

    void GenLeastSquarePoissonSvd(int ndata,
                                  const double* const xval_arr,
                                  const double* const oval_arr,
                                  int nfunc,
                                  const MirFunc* const* const func_arr,
                                  const MirFuncPar* const* const func_par_arr,
                                  double** const par_best_svd_ptr,
                                  double** const par_serr_svd_ptr,
                                  double*** const par_cov_svd_ptr);

    void GenLeastSquarePoissonSvd(const HistData2d* const hd2d,
                                  int nfunc,
                                  const MirFunc* const* const func_arr,
                                  const MirFuncPar* const* const func_par_arr,
                                  double** const par_best_svd_ptr,
                                  double** const par_serr_svd_ptr,
                                  double*** const par_cov_svd_ptr);

    void GenLeastSquareGaussSvd(int ndata,
                                const double* const xval_arr,
                                const double* const oval_arr,
                                const double* const oval_serr_arr,
                                int nfunc,
                                const MirFunc* const* const func_arr,
                                const MirFuncPar* const* const func_par_arr,
                                double** const par_best_svd_ptr,
                                double** const par_serr_svd_ptr,
                                double*** const par_cov_svd_ptr);
    
    
    //
    // Multi data
    //

    // 1 dim
    
    void GenLeastSquarePoissonQuadProgPlusMulti(int ngraph,
                                                const GraphData2d* const* const gd2d_arr,
                                                const int* const nfunc_arr,
                                                const MirFunc* const* const* const func_arr,
                                                const MirFuncPar* const* const* const func_par_arr,
                                                const MimTie* const mim_tie,
                                                double*** const par_best_arr_ptr,
                                                double* const chi2_min_ptr,
                                                double* const aic_ptr,
                                                double* const bic_ptr);

    void GenLeastSquarePoissonQuadProgPlusMulti(int ngraph,
                                                const GraphData2d* const* const gd2d_arr,
                                                const MifcLincombCtn* const* const func_ctn_arr,
                                                const MimTie* const mim_tie,
                                                MifcLincombCtn*** const func_ctn_best_arr_ptr,
                                                double* const chi2_min_ptr,
                                                double* const aic_ptr,
                                                double* const bic_ptr);

    // 2 dim

    void GenLeastSquarePoissonQuadProgPlusMulti(int nhist,
                                                const HistData2d* const* const hd2d_arr,
                                                const int* const nfunc_arr,
                                                const MirFunc* const* const* const func_arr,
                                                const MirFuncPar* const* const* const func_par_arr,
                                                const MimTie* const mim_tie,
                                                double*** const par_best_arr_ptr,
                                                double* const chi2_min_ptr,
                                                double* const aic_ptr,
                                                double* const bic_ptr);
    
    void GenLeastSquarePoissonQuadProgPlusMulti(int nhist,
                                                const HistData2d* const* const hd2d_arr,
                                                const MifcLincombCtn* const* const func_ctn_arr,
                                                const MimTie* const mim_tie,
                                                MifcLincombCtn*** const func_ctn_best_arr_ptr,
                                                double* const chi2_min_ptr,
                                                double* const aic_ptr,
                                                double* const bic_ptr);
    

} // namespace MimLS

#endif // MORIIISM_MITOOL_MIMINUITLIB_LS_H_
