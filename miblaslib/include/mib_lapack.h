#ifndef MORIIISM_MIBLASLIB_LAPACK_H_
#define MORIIISM_MIBLASLIB_LAPACK_H_

#ifdef __cplusplus
extern "C" {
#endif

    void dgeqrf_(const int& M, const int& N, double* A,
                 const int& LDA, double* TAU,
                 double* WORK, const int& LWORK, const int& INFO);
    void dorgqr_(const int& M, const int& N, const int& K, double* A,
                 const int& LDA, double* TAU,
                 double* WORK, const int& LWORK, const int& INFO);
    void dgesvd_(char* JOBU, char* JOBVT,
                 const int& M, const int& N,
                 double* A, const int& LDA,
                 double* S,
                 double* U, const int& LDU,
                 double* VT, const int& LDVT,
                 double* WORK, const int& LWORK, const int& INFO);

#ifdef __cplusplus
}
#endif

#endif // MORIIISM_MIBLASLIB_LAPACK_H_
