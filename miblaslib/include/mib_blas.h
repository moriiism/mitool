#ifndef MORIIISM_MITOOL_MIBLASLIB_BLAS_H_
#define MORIIISM_MITOOL_MIBLASLIB_BLAS_H_

#ifdef __cplusplus
extern "C" {
#endif
    double dnrm2_(const int& N, double* X, const int& INCX);
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

#ifdef __cplusplus
}
#endif

#endif // MORIIISM_MITOOL_MIBLASLIB_BLAS_H_
