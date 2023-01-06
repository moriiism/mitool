//
// mib_blas.cc
//
// using blas
//

#include "mib_blas.h"

// addition: vec1_arr + vec2_arr
void MibBlas::Add(const double* const vec1_arr,
                  const double* const vec2_arr,
                  int nelm,
                  double* const add_arr)
{
    dcopy_(nelm, const_cast<double*>(vec1_arr), 1, add_arr, 1);
    daxpy_(nelm, 1.0, const_cast<double*>(vec2_arr), 1, add_arr, 1);
}

// subtraction: vec1_arr - vec2_arr
void MibBlas::Sub(const double* const vec1_arr,
                  const double* const vec2_arr,
                  int nelm,
                  double* const sub_arr)
{
    dcopy_(nelm, const_cast<double*>(vec1_arr), 1, sub_arr, 1);
    daxpy_(nelm, -1.0, const_cast<double*>(vec2_arr), 1, sub_arr, 1);
}

double MibBlas::Sum(const double* const arr, int narr)
{
    //double* dummy_arr = new double[1];
    double dummy_arr[1];
    dummy_arr[0] = 1.0;
    double sum = ddot_(narr, const_cast<double*>(arr), 1,
                       dummy_arr, 0);
    return sum;
}

// element-wise multiplication of two vectors
// out_arr = alpha * x_arr * y_arr
void MibBlas::ElmWiseMul(int narr,
                         double alpha,
                         const double* const x_arr,
                         const double* const y_arr,
                         double* const out_arr)
{
    char uplo[2];
    strcpy(uplo, "U");
    int k = 0; // diagonal matrix; 0 super-diagonal bands
    int lda = 1;
    int incx = 1;
    double beta = 0.0;
    int incy = 1;
    dsbmv_(uplo, narr, k,
           alpha, const_cast<double*>(x_arr), lda,
           const_cast<double*>(y_arr), incx,
           beta, out_arr, incy);

}
