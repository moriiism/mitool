#ifndef MORIIISM_MILIB_LINALG_H_
#define MORIIISM_MILIB_LINALG_H_

#include "mi_blas.h"
#include "mi_lapack.h"
#include "mi_math.h"

namespace MiLinalg
{
    void GenQR(const double* const X_mat, int nrow, int ncol,
               double** const Q_mat_ptr, double** const R_mat_ptr,
               int* const lwork_QR1_ptr,  int* const lwork_QR2_ptr);
    
} //  namespace MiLinalg

#endif // MORIIISM_MILIB_LINALG_H_
