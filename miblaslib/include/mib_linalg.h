#ifndef MORIIISM_MIBLASLIB_LINALG_H_
#define MORIIISM_MIBLASLIB_LINALG_H_


#include "mi_base.h"
#include "mib_blas.h"
#include "mib_lapack.h"

namespace MibLinalg
{
    void GenQR(const double* const X_mat, int nrow, int ncol,
               double** const Q_mat_ptr, double** const R_mat_ptr,
               int* const lwork_QR1_ptr,  int* const lwork_QR2_ptr);
    
} //  namespace MibLinalg

#endif // MORIIISM_MIBLASLIB_LINALG_H_
