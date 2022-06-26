#ifndef MORIIISM_MITOOL_MIBLASLIB_BLAS_H_
#define MORIIISM_MITOOL_MIBLASLIB_BLAS_H_

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
    double dnrm2_(const int& N, double* X, const int& INCX);
    // daxpy_: y <-- ax + y
    void daxpy_(const int& N, const double& DA, double* DX,
                const int& INCX, double* DY, const int& INCY);
    void dscal_(const int& N, const double& DA, double* DX,
                const int& INCX);
    void dcopy_(const int& N, double* DX, const int& INCX,
                double* DY, const int& INCY);
    void dgemm_(char* TRANSA, char* TRANSB,
                const int& M, const int& N, const int& K,
                const double& ALPHA, double* A, const int& LDA,
                double* B, const int& LDB,
                const double& BETA, double* C, const int& LDC);
    // dgemv_: y <-- alpha A x + beta y
    void dgemv_(char* TRANS, const int& M, const int& N,
		const double& ALPHA, double* A, const int& LDA,
		double* X, const int& INCX,
		const double& BETA,
		double* Y, const int& INCY);
    double ddot_(const int& N, double* DX, const int& INCX,
                 double* DY, const int& INCY);

    // y := alpha*A*x + beta*y, or y := alpha*A**T*x + beta*y
    // A is an m by n band matrix,
    // with kl sub-diagonals and ku super-diagonals.
    void dgbmv_(char* TRANS, const int& M, const int& N,
                const int& KL, const int& KU,
                const double& ALPHA,
                double* A, const int& LDA,
                double* X, const int& INCX,
                const double& BETA,
                double* Y, const int& INCY);

    // y := alpha*A*x + beta*y
    // x and y are n element vectors and
    // A is an n by n symmetric band matrix, with k super-diagonals.
    // UPLO = 'U' or 'u': The upper triangular part of A is being supplied.
    // UPLO = 'L' or 'l': The lower triangular part of A is being supplied.
    void dsbmv_(char* UPLO, const int& N, const int& K,
                const double& ALPHA,
                double* A, const int& LDA,
                double* X, const int& INCX,
                const double& BETA,
                double* Y, const int& INCY);

#ifdef __cplusplus
}
#endif


namespace MibBlas
{
    // addition: vec1_arr + vec2_arr
    void Add(const double* const vec1_arr,
             const double* const vec2_arr,
             int nelm,
             double* const add_arr);
    // subtraction: vec1_arr - vec2_arr
    void Sub(const double* const vec1_arr,
             const double* const vec2_arr,
             int nelm,
             double* const sub_arr);

    double Sum(const double* const arr, int narr);

    // element-wise multiplication of two vectors
    // out_arr = alpha * x_arr * y_arr
    void ElmWiseMul(int narr,
                    double alpha,
                    const double* const x_arr,
                    const double* const y_arr,
                    double* const out_arr);
} //  namespace MibBlas


#endif // MORIIISM_MITOOL_MIBLASLIB_BLAS_H_
