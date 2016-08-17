//
// linalg.cc
//
// linear algebra
//

#include "mi_linalg.h"

// dgeqrf(M, N, A, LDA, TAU, WORK, LWORK, INFO)
// DGEQRF computes a QR factorization of a real M-by-N matrix A: A = Q * R.
// [in]      int  M
// [in]      int  N
// [in,out]  double* A
//           On entry, the M-by-N matrix A.
//           On exit, the elements on and above the diagonal of the array contain
//           the min(M,N)-by-N upper trapezoidal matrix R
//           (R is upper triangular if m >= n);
//           the elements below the diagonal, with the array TAU,
//           represent the orthogonal matrix Q as a product of min(m,n) elementary
//           reflectors.
// [in]      int  LDA
// [out]     double* TAU
//           dimension (min(M,N)).
//           The scalar factors of the elementary reflectors
// [workspace]  double* WORK
//           dimension (LWORK).
//           On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// [in]         int     LWORK
//           The dimension of the array WORK.  LWORK >= max(1,N).
//           For optimum performance LWORK >= N*NB, where NB is
//           the optimal blocksize.
//           If LWORK = -1, then a workspace query is assumed; the routine
//           only calculates the optimal size of the WORK array, returns
//           this value as the first entry of the WORK array, and no error
//           message related to LWORK is issued by XERBLA.
// [out]        int     INFO
//           = 0:  successful exit
//           < 0:  if INFO = -i, the i-th argument had an illegal value

// The matrix Q is represented as a product of elementary reflectors
//   Q = H(1) H(2) . . . H(k), where k = min(m,n).
// Each H(i) has the form
//   H(i) = I - tau * v * v'
// where tau is a real scalar, and v is a real vector with
// v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in
// A(i+1:m,i), and tau in TAU(i).
//

// dorgqr(M, N, K, A, LDA, TAU, WORK, LWORK, INFO)
// [in]   int M
//        The number of rows of the matrix Q. M >= 0.
// [in]   int N
//        The number of columns of the matrix Q. M >= N >= 0.
// [in]   int K
//        The number of elementary reflectors whose product defines the
//        matrix Q. N >= K >= 0.
// [in,out]  double* A_mat
//           dimension (LDA,N).
//           On entry, the i-th column must contain the vector which
//           defines the elementary reflector H(i), for i = 1,2,...,k, as
//           returned by DGEQRF in the first k columns of its array
//           argument A.
//           On exit, the M-by-N matrix Q.
// [in]   int     LDA
// [in]   double* TAU
//        dimension (K). TAU(i) must contain the scalar factor of the elementary
//        reflector H(i), as returned by DGEQRF.
// [out]  double* WORK
//        dimension (MAX(1,LWORK)). On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
// [in]   int     LWORK
// [out]  int     INFO
//        = 0:  successful exit
//        < 0:  if INFO = -i, the i-th argument has an illegal value

// Usage:
//   MiLinalg::GenQR(X_mat, nrow, ncol, &Q_mat, &R_mat);
//
void MiLinalg::GenQR(const double* const X_mat, int nrow, int ncol,
                      double** const Q_mat_ptr, double** const R_mat_ptr,
                      int* const lwork_QR1_ptr,  int* const lwork_QR2_ptr)
{
    int nelem = nrow * ncol;
    int incX = 1;
    int incY = 1;
    double* QR_mat = new double [nelem];
    dcopy_(nelem, const_cast<double*>(X_mat), incX, QR_mat, incY);

    int k_QR = MiMath::GetMin(nrow, ncol);
    double* tau_QR  = new double [k_QR];

    // printf("nrow, ncol, k_QR = %d, %d, %d\n", nrow, ncol, k_QR);

    int info_QR = 0;
    int lwork_QR1 = 0;
    // query of workspace
    if(0 == *lwork_QR1_ptr){
        int lwork_query = -1;
        double work_query[1];
        dgeqrf_(nrow, ncol, QR_mat, nrow, tau_QR, work_query, lwork_query, info_QR);
        if(0 > info_QR){
            printf("ERROR: the %d-th argument had an illegal value.\n", -1 * info_QR);
            abort();
        } else if(0 < info_QR){
            printf("ERROR: info_QR(%d) > 0\n", info_QR);
            abort();
        }
        lwork_QR1 = (int) work_query[0];
        printf("optimal lwork(QR1) = %d\n", lwork_QR1);
    } else {
        lwork_QR1 = *lwork_QR1_ptr;
    }
    double* work_QR1 = new double [lwork_QR1];
    dgeqrf_(nrow, ncol, QR_mat, nrow, tau_QR, work_QR1, lwork_QR1, info_QR);
    if(0 > info_QR){
        printf("ERROR: the %d-th argument had an illegal value.\n", -1 * info_QR);
        abort();
    } else if(0 < info_QR){
        printf("ERROR: info_QR(%d) > 0\n", info_QR);
        abort();
    }
    delete [] work_QR1;

    // Get R matrix
    double* R_mat = new double [nelem];
    dcopy_(nelem, QR_mat, incX, R_mat, incY);
    for(int icol = 0; icol < ncol; icol ++){
        for(int irow = 0; irow < nrow; irow ++){
            if(irow > icol){
                int ielem = irow + icol * nrow;
                R_mat[ielem] = 0.0;
            }
        }
    }
    
    //
    // Get Q matrix
    //

    int lwork_QR2 = 0;
    info_QR = 0;
    // query of workspace
    if(0 == *lwork_QR2_ptr){
        int lwork_query = -1;
        double work_query[1];
        dorgqr_(nrow, k_QR, k_QR, QR_mat, nrow, tau_QR, work_query, lwork_query, info_QR);
        if(0 > info_QR){
            printf("ERROR: the %d-th argument had an illegal value.\n", -1 * info_QR);
            abort();
        } else if(0 < info_QR){
            printf("ERROR: info_QR(%d) > 0\n", info_QR);
            abort();
        }
        lwork_QR2 = (int) work_query[0];        
        printf("optimal lwork(QR2) = %d\n", lwork_QR2);
    } else {
        lwork_QR2 = *lwork_QR2_ptr;
    }

    double* work_QR2 = new double [lwork_QR2];
    dorgqr_(nrow, k_QR, k_QR, QR_mat, nrow, tau_QR, work_QR2, lwork_QR2, info_QR);
    if(0 > info_QR){
        printf("ERROR: the %d-th argument had an illegal value.\n", -1 * info_QR);
        abort();
    } else if(0 < info_QR){
        printf("ERROR: info_QR(%d) > 0\n", info_QR);
        abort();
    }
    delete [] work_QR2;
    delete [] tau_QR;

//    //
//    // check QR
//    //
//    double* X_by_QR_mat = new double [nelem];
//    dgemm_('N', 'N', nrow, nrow, k_QR,
//           1.0, QR_mat, nrow, R_mat, nrow,
//           0.0, X_by_QR_mat, nrow);
//    for(int icol = 0; icol < ncol; icol ++){
//        for(int irow = 0; irow < nrow; irow ++){
//            int ielem = irow + icol * nrow;
//            printf("%e %e: %e \n", X_mat[ielem], X_by_QR_mat[ielem],
//                   X_mat[ielem] - X_by_QR_mat[ielem]);
//        }
//    }
//    delete [] X_by_QR_mat;


    *Q_mat_ptr = QR_mat;
    *R_mat_ptr = R_mat;
    *lwork_QR1_ptr = lwork_QR1;
    *lwork_QR2_ptr = lwork_QR2;
}
