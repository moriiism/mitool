#include "mim_ls.h"

//
// Least Square fit
//

void MimLS::GenLeastSquarePoissonQuadProgPlus(int ndata,
                                               const double* const xval_arr,
                                               const double* const oval_arr,
                                               int nfunc,
                                               const MirFunc* const* const func_arr,
                                               const MirFuncPar* const* const func_par_arr,
                                               double** const par_best_arr_ptr,
                                               double* const chi2_min_ptr,
                                               double* const aic_ptr,
                                               double* const bic_ptr)
{
    //
    // matrix A_ij, b
    //

    long nrow = ndata;
    long ncol = nfunc;
    TMatrixD Mat_A(nrow, ncol);
    TMatrixD Mat_b(nrow, 1);    
    for(long irow = 0; irow < nrow; irow ++){
        for(long icol = 0; icol < ncol; icol ++){
            double xval = xval_arr[irow];
            double oval = oval_arr[irow];
            double xval_arr[1];
            xval_arr[0] = xval;
            Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) /
                sqrt(oval + 1.0);
        }
    }
    // Mat_A.Print();

    for(long irow = 0; irow < nrow; irow ++){
        double oval = oval_arr[irow];
        Mat_b[irow][0]  = (oval + MirMath::GetMin(oval, 1.0))/ sqrt(oval + 1.0);
    }
    // Mat_b.Print();

    TMatrixD Mat_A_trans(ncol, nrow);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol, ncol);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);
    
    
    //
    // solve by QP
    //
    int nrVar = ncol;
    int nrEqual = 0;
    int nrInEqual = 0;

    // equality equation
    TMatrixD Mat_Qp_A(nrEqual, nrVar); Mat_Qp_A = 0;
    TVectorD Vec_Qp_b(nrEqual); Vec_Qp_b = 0;

    // inequality equation
    TMatrixD Mat_C(nrInEqual, nrVar);
    TVectorD Vec_clo(nrInEqual);
    TVectorD Vec_cup(nrInEqual);
    TVectorD Vec_iclo(nrInEqual);
    TVectorD Vec_icup(nrInEqual);

    // simple square boundary condtion
    TVectorD Vec_xlo(nrVar); Vec_xlo = 0;
    TVectorD Vec_xup(nrVar); Vec_xup = 0;
    TVectorD Vec_ixlo(nrVar); Vec_ixlo = 1;
    TVectorD Vec_ixup(nrVar); Vec_ixup = 0;    
    
    // minimizing function
    TVectorD Vec_Qp_c(nrVar);
    for(int icol = 0; icol < ncol; icol ++){
        Vec_Qp_c[icol] = -2 * Mat_beta[icol][0];
    }
    TMatrixDSym Mat_Qp_Q(ncol);
    Mat_Qp_Q.TMult(Mat_A);
    Mat_Qp_Q *= 2.0;

    TQpProbDens* qp = new TQpProbDens(nrVar, nrEqual, nrInEqual);
    TQpDataDens* prob = (TQpDataDens *)qp->MakeData(Vec_Qp_c, Mat_Qp_Q,
                                                    Vec_xlo, Vec_ixlo, Vec_xup, Vec_ixup,
                                                    Mat_Qp_A, Vec_Qp_b,
                                                    Mat_C, Vec_clo, Vec_iclo, Vec_cup, Vec_icup);

    TQpVar* vars = qp->MakeVariables(prob);
    TQpResidual* resid = qp->MakeResiduals(prob);

    // Now we have to choose the method of solving, either TGondzioSolver or TMehrotraSolver
    // The Gondzio method is more sophisticated and therefore numerically more involved
    // If one want the Mehrotra method, simply replace "Gondzio" by "Mehrotra" .

    TGondzioSolver* solver = new TGondzioSolver(qp, prob);
    int ret = solver->Solve(prob, vars, resid);
    printf("ret = %d\n", ret);
    TVectorD weight = vars->fX;


    // function_minimum

    // vector_answer
    TMatrixD Mat_best(ncol, 1);
    for(int icol = 0; icol < ncol; icol ++){
        Mat_best[icol][0] = weight[icol];
    }
    TMatrixD Mat_Q_x_best(ncol, 1);
    Mat_Q_x_best.Mult(Mat_Qp_Q, Mat_best);

    double term1 = 0.0;
    for(int icol = 0; icol < ncol; icol ++){
        term1 += Mat_best[icol][0] * Mat_Q_x_best[icol][0];
    }
    term1 /= 2.0;
    double term2 = 0.0;
    for(int icol = 0; icol < ncol; icol ++){
        term2 += Vec_Qp_c[icol] * Mat_best[icol][0];
    }
    double term3 = 0.0;
    for(int irow = 0; irow < nrow; irow ++){
        term3 += Mat_b[irow][0] * Mat_b[irow][0];
    }
    double chi2_min = term1 + term2 + term3;

    printf("term1, term2, term3 = %e %e %e\n", term1, term2, term3);
    
    printf("chi2_min = %e\n", chi2_min);
    int npar_free = ncol - nrEqual;
    double aic = chi2_min + 2 * npar_free;
    printf("aic = %e\n", aic);
    double bic = chi2_min + npar_free * (log(nrow) - log(2 * kPi));
    printf("bic = %e\n", bic);
    
    //printf("---- QP --- \n");
    weight.Print();
    //printf("==== QP === \n");
    
    delete qp;
    delete prob;
    delete vars;
    delete resid;
    delete solver;

    double* par_best_arr = new double [ncol];
    for(int icol = 0; icol < ncol; icol ++){
        par_best_arr[icol] = weight[icol];
    }

    //
    // print results
    //
    printf("---- QP -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par = %e\n",
               icol, par_best_arr[icol]);
    }
    printf("==== QP =====\n");

    *par_best_arr_ptr = par_best_arr;
    *chi2_min_ptr = chi2_min;
    *aic_ptr = aic;
    *bic_ptr = bic;
}


// svd

void MimLS::GenLeastSquarePoissonSvd(int ndata,
                                      const double* const xval_arr,
                                      const double* const oval_arr,
                                      int nfunc,
                                      const MirFunc* const* const func_arr,
                                      const MirFuncPar* const* const func_par_arr,
                                      double** const par_best_svd_ptr,
                                      double** const par_serr_svd_ptr,
                                      double*** const par_cov_svd_ptr)
{
    //
    // matrix A_ij, b
    //

    long nrow = ndata;
    long ncol = nfunc;
    TMatrixD Mat_A(nrow, ncol);
    TMatrixD Mat_b(nrow, 1);    
    for(long irow = 0; irow < nrow; irow ++){
        for(long icol = 0; icol < ncol; icol ++){
            double xval = xval_arr[irow];
            double yval = oval_arr[irow];
            double xval_arr[1];
            xval_arr[0] = xval;
            Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) /
                sqrt(yval + 1.0);
        }
    }
    // Mat_A.Print();

    for(long irow = 0; irow < nrow; irow ++){
        double yval = oval_arr[irow];
        Mat_b[irow][0]  = (yval + MirMath::GetMin(yval, 1.0))/ sqrt(yval + 1.0);
    }
    // Mat_b.Print();

    TMatrixD Mat_A_trans(ncol, nrow);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol, ncol);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);
    

    //
    // solve by SVD
    //

    TDecompSVD Mat_A_SVD(Mat_A);
    TVectorD Vec_b(nrow);
    for(long irow = 0; irow < nrow; irow ++){
        Vec_b[irow] = Mat_b[irow][0];
    }
    // Vec_b.Print();
    Mat_A_SVD.Solve(Vec_b);

    TMatrixD Mat_U = Mat_A_SVD.GetU();
    TMatrixD Mat_V = Mat_A_SVD.GetV();
    TVectorD Vec_Sig = Mat_A_SVD.GetSig();
    // Mat_A_SVD.GetSig().Print();


    double* par_best_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_best_svd[icol] = Vec_b[icol];
    }
    double** par_cov_svd = new double* [ncol];
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        par_cov_svd[irow_cov] = new double [ncol];
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            par_cov_svd[irow_cov][icol_cov] = 0.0;
        }
    }
    TMatrixD Mat_cov_svd(ncol, ncol);
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            double cov = 0.0;
            for(long icol_this = 0; icol_this < ncol; icol_this ++){
                cov += Mat_A_SVD.GetV()[irow_cov][icol_this] * Mat_A_SVD.GetV()[icol_cov][icol_this]
                    / (Mat_A_SVD.GetSig()[icol_this] * Mat_A_SVD.GetSig()[icol_this]);
            }
            Mat_cov_svd[irow_cov][icol_cov] = cov;
            par_cov_svd[irow_cov][icol_cov] = cov;
        }
    }
    double* par_serr_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_serr_svd[icol] = sqrt(Mat_cov_svd[icol][icol]);
    }

    //
    // print results
    //
    printf("---- svd -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par +- err = %e +/- %e\n",
               icol, par_best_svd[icol], par_serr_svd[icol]);
    }
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            printf("cov[%ld][%ld] = %e\n",
                   irow_cov, icol_cov, par_cov_svd[irow_cov][icol_cov]);
        }
    }
    printf("==== svd =====\n");

    
    *par_best_svd_ptr = par_best_svd;
    *par_serr_svd_ptr = par_serr_svd;
    *par_cov_svd_ptr = par_cov_svd;
}

//
// svd
//

void MimLS::GenLeastSquarePoissonSvd(const HistData2d* const hd2d,
                                      int nfunc,
                                      const MirFunc* const* const func_arr,
                                      const MirFuncPar* const* const func_par_arr,
                                      double** const par_best_svd_ptr,
                                      double** const par_serr_svd_ptr,
                                      double*** const par_cov_svd_ptr)
{
    //
    // matrix A_ij, b
    //

    long nrow = hd2d->GetNbin();
    long ncol = nfunc;
    TMatrixD Mat_A(nrow, ncol);
    TMatrixD Mat_b(nrow, 1);    
    for(long irow = 0; irow < nrow; irow ++){
        for(long icol = 0; icol < ncol; icol ++){
            double xval = hd2d->GetHi2d()->GetBinCenterXFromIbin(irow);
            double yval = hd2d->GetHi2d()->GetBinCenterYFromIbin(irow);
            double oval = hd2d->GetOvalArr()->GetValElm(irow);
            double xval_arr[2];
            xval_arr[0] = xval;
            xval_arr[1] = yval;
            Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) /
                sqrt(oval + 1.0);
        }
    }
    // Mat_A.Print();

    for(long irow = 0; irow < nrow; irow ++){
        double oval = hd2d->GetOvalArr()->GetValElm(irow);
        Mat_b[irow][0]  = (oval + MirMath::GetMin(oval, 1.0))/ sqrt(oval + 1.0);
    }
    // Mat_b.Print();

    TMatrixD Mat_A_trans(ncol, nrow);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol, ncol);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);
    

    //
    // solve by SVD
    //

    TDecompSVD Mat_A_SVD(Mat_A);
    TVectorD Vec_b(nrow);
    for(long irow = 0; irow < nrow; irow ++){
        Vec_b[irow] = Mat_b[irow][0];
    }
    // Vec_b.Print();
    Mat_A_SVD.Solve(Vec_b);

    TMatrixD Mat_U = Mat_A_SVD.GetU();
    TMatrixD Mat_V = Mat_A_SVD.GetV();
    TVectorD Vec_Sig = Mat_A_SVD.GetSig();
    // Mat_A_SVD.GetSig().Print();


    double* par_best_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_best_svd[icol] = Vec_b[icol];
    }
    double** par_cov_svd = new double* [ncol];
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        par_cov_svd[irow_cov] = new double [ncol];
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            par_cov_svd[irow_cov][icol_cov] = 0.0;
        }
    }
    TMatrixD Mat_cov_svd(ncol, ncol);
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            double cov = 0.0;
            for(long icol_this = 0; icol_this < ncol; icol_this ++){
                cov += Mat_A_SVD.GetV()[irow_cov][icol_this] * Mat_A_SVD.GetV()[icol_cov][icol_this]
                    / (Mat_A_SVD.GetSig()[icol_this] * Mat_A_SVD.GetSig()[icol_this]);
            }
            Mat_cov_svd[irow_cov][icol_cov] = cov;
            par_cov_svd[irow_cov][icol_cov] = cov;
        }
    }
    double* par_serr_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_serr_svd[icol] = sqrt(Mat_cov_svd[icol][icol]);
    }

    //
    // print results
    //
    printf("---- svd -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par +- err = %e +/- %e\n",
               icol, par_best_svd[icol], par_serr_svd[icol]);
    }
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            printf("cov[%ld][%ld] = %e\n",
                   irow_cov, icol_cov, par_cov_svd[irow_cov][icol_cov]);
        }
    }
    printf("==== svd =====\n");

    
    *par_best_svd_ptr = par_best_svd;
    *par_serr_svd_ptr = par_serr_svd;
    *par_cov_svd_ptr = par_cov_svd;
}



// svd 

void MimLS::GenLeastSquareGaussSvd(int ndata,
                                    const double* const xval_arr,
                                    const double* const oval_arr,
                                    const double* const oval_serr_arr,
                                    int nfunc,
                                    const MirFunc* const* const func_arr,
                                    const MirFuncPar* const* const func_par_arr,
                                    double** const par_best_svd_ptr,
                                    double** const par_serr_svd_ptr,
                                    double*** const par_cov_svd_ptr)
{
    //
    // matrix A_ij, b
    //

    long nrow = ndata;
    long ncol = nfunc;
    TMatrixD Mat_A(nrow, ncol);
    TMatrixD Mat_b(nrow, 1);    
    for(long irow = 0; irow < nrow; irow ++){
        for(long icol = 0; icol < ncol; icol ++){
            double xval = xval_arr[irow];
            double yval_serr = oval_serr_arr[irow];
            double xval_arr[1];
            xval_arr[0] = xval;
            Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) / yval_serr;
        }
    }
    // Mat_A.Print();

    for(long irow = 0; irow < nrow; irow ++){
        double yval = oval_arr[irow];
        double yval_serr = oval_serr_arr[irow];
        Mat_b[irow][0]  = yval / yval_serr;
    }
    // Mat_b.Print();

    TMatrixD Mat_A_trans(ncol, nrow);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol, ncol);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);
    

    //
    // solve by SVD
    //

    TDecompSVD Mat_A_SVD(Mat_A);
    TVectorD Vec_b(nrow);
    for(long irow = 0; irow < nrow; irow ++){
        Vec_b[irow] = Mat_b[irow][0];
    }
    // Vec_b.Print();
    Mat_A_SVD.Solve(Vec_b);

    TMatrixD Mat_U = Mat_A_SVD.GetU();
    TMatrixD Mat_V = Mat_A_SVD.GetV();
    TVectorD Vec_Sig = Mat_A_SVD.GetSig();
    // Mat_A_SVD.GetSig().Print();


    double* par_best_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_best_svd[icol] = Vec_b[icol];
    }
    double** par_cov_svd = new double* [ncol];
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        par_cov_svd[irow_cov] = new double [ncol];
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            par_cov_svd[irow_cov][icol_cov] = 0.0;
        }
    }
    TMatrixD Mat_cov_svd(ncol, ncol);
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            double cov = 0.0;
            for(long icol_this = 0; icol_this < ncol; icol_this ++){
                cov += Mat_A_SVD.GetV()[irow_cov][icol_this] * Mat_A_SVD.GetV()[icol_cov][icol_this]
                    / (Mat_A_SVD.GetSig()[icol_this] * Mat_A_SVD.GetSig()[icol_this]);
            }
            Mat_cov_svd[irow_cov][icol_cov] = cov;
            par_cov_svd[irow_cov][icol_cov] = cov;
        }
    }
    double* par_serr_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_serr_svd[icol] = sqrt(Mat_cov_svd[icol][icol]);
    }

    //
    // print results
    //
    printf("---- svd -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par +- err = %e +/- %e\n",
               icol, par_best_svd[icol], par_serr_svd[icol]);
    }
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            printf("cov[%ld][%ld] = %e\n",
                   irow_cov, icol_cov, par_cov_svd[irow_cov][icol_cov]);
        }
    }
    printf("==== svd =====\n");

    
    *par_best_svd_ptr = par_best_svd;
    *par_serr_svd_ptr = par_serr_svd;
    *par_cov_svd_ptr = par_cov_svd;
}


// ----------------------------------------------------------------------

//
// multi data
//

void MimLS::GenLeastSquarePoissonQuadProgPlusMulti(int ngraph,
                                                    const GraphData2d* const* const gd2d_arr,
                                                    const int* const nfunc_arr,
                                                    const MirFunc* const* const* const func_arr,
                                                    const MirFuncPar* const* const* const func_par_arr,
                                                    const MimTie* const mim_tie,
                                                    double*** const par_best_arr_ptr,
                                                    double* const chi2_min_ptr,
                                                    double* const aic_ptr,
                                                    double* const bic_ptr)
{

    //
    // matrix A_ij, b
    //
    long nrow_tot = 0;
    for(int igraph = 0; igraph < ngraph; igraph ++){
        nrow_tot += gd2d_arr[igraph]->GetNdata();
    }
    long ncol_tot = 0;
    for(int igraph = 0; igraph < ngraph; igraph ++){
        ncol_tot += nfunc_arr[igraph];
    }
    TMatrixD Mat_A(nrow_tot, ncol_tot);
    TMatrixD Mat_b(nrow_tot, 1);

    long irow_tot_pivot = 0;
    long icol_tot_pivot = 0; 
    for(int igraph = 0; igraph < ngraph; igraph ++){
        for(long irow = 0; irow < gd2d_arr[igraph]->GetNdata(); irow ++){
            long irow_tot = irow_tot_pivot + irow;
            for(long icol = 0; icol < nfunc_arr[igraph]; icol ++){
                double xval = gd2d_arr[igraph]->GetXvalElm(irow);
                double yval = gd2d_arr[igraph]->GetOvalElm(irow);
                double xval_arr[1];
                xval_arr[0] = xval;

                long icol_tot = icol_tot_pivot + icol;
                Mat_A[irow_tot][icol_tot] =
                    func_arr[igraph][icol]->Eval(xval_arr, func_par_arr[igraph][icol]->GetPar()) /
                    sqrt(yval + 1.0);
            }
        }
        irow_tot_pivot += gd2d_arr[igraph]->GetNdata();
        icol_tot_pivot += nfunc_arr[igraph];
    }
    //Mat_A.Print();
    
    irow_tot_pivot = 0;
    for(int igraph = 0; igraph < ngraph; igraph ++){
        for(long irow = 0; irow < gd2d_arr[igraph]->GetNdata(); irow ++){
            double yval = gd2d_arr[igraph]->GetOvalElm(irow);
            long irow_tot = irow_tot_pivot + irow;
            Mat_b[irow_tot][0]  = (yval + MirMath::GetMin(yval, 1.0))/ sqrt(yval + 1.0);
        }
        irow_tot_pivot += gd2d_arr[igraph]->GetNdata();
    }
    // Mat_b.Print();

    TMatrixD Mat_A_trans(ncol_tot, nrow_tot);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol_tot, ncol_tot);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol_tot, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);

    //
    // solve by QP
    //
    int nrVar = ncol_tot;
    int nrEqual = mim_tie->GetNtie();
    int nrInEqual = 0;

    // equality equation
    TVectorD Vec_Qp_b(nrEqual); Vec_Qp_b = 0;
    TMatrixD Mat_Qp_A(nrEqual, nrVar); 


    
    mim_tie->Print(stdout);
    
    if(nrEqual > 0){
        for(int itie = 0; itie < mim_tie->GetNtie(); itie ++){
            int icol_tot_lhs = 0;
            for(int idata = 0; idata < mim_tie->GetIdDataLhsElm(itie); idata ++){
                icol_tot_lhs += nfunc_arr[idata];
            }
            icol_tot_lhs += mim_tie->GetIdFuncLhsElm(itie);
                
            int icol_tot_rhs = 0;
            for(int idata = 0; idata < mim_tie->GetIdDataRhsElm(itie); idata ++){
                icol_tot_rhs += nfunc_arr[idata];
            }
            icol_tot_rhs += mim_tie->GetIdFuncRhsElm(itie);


            printf("icol_tot_lhs = %d\n", icol_tot_lhs);
            printf("icol_tot_rhs = %d\n", icol_tot_rhs);
                
            Mat_Qp_A[itie][icol_tot_lhs] =  1;
            Mat_Qp_A[itie][icol_tot_rhs] = -1;
        }
    } else {
        Mat_Qp_A = 0;
    }
    Mat_Qp_A.Print();

    // inequality equation
    TMatrixD Mat_C(nrInEqual, nrVar);
    TVectorD Vec_clo(nrInEqual);
    TVectorD Vec_cup(nrInEqual);
    TVectorD Vec_iclo(nrInEqual);
    TVectorD Vec_icup(nrInEqual);

    // simple square boundary condtion
    TVectorD Vec_xlo(nrVar); Vec_xlo = 0;
    TVectorD Vec_xup(nrVar); Vec_xup = 0;
    TVectorD Vec_ixlo(nrVar); Vec_ixlo = 1;
    TVectorD Vec_ixup(nrVar); Vec_ixup = 0;    
    
    // minimizing function
    TVectorD Vec_Qp_c(nrVar);
    for(int icol = 0; icol < ncol_tot; icol ++){
        Vec_Qp_c[icol] = -2 * Mat_beta[icol][0];
    }
    TMatrixDSym Mat_Qp_Q(ncol_tot);
    Mat_Qp_Q.TMult(Mat_A);
    Mat_Qp_Q *= 2.0;

    TQpProbDens* qp = new TQpProbDens(nrVar, nrEqual, nrInEqual);
    TQpDataDens* prob = (TQpDataDens *)qp->MakeData(Vec_Qp_c, Mat_Qp_Q,
                                                    Vec_xlo, Vec_ixlo, Vec_xup, Vec_ixup,
                                                    Mat_Qp_A, Vec_Qp_b,
                                                    Mat_C, Vec_clo, Vec_iclo, Vec_cup, Vec_icup);

    TQpVar* vars = qp->MakeVariables(prob);
    TQpResidual* resid = qp->MakeResiduals(prob);

    // Now we have to choose the method of solving, either TGondzioSolver or TMehrotraSolver
    // The Gondzio method is more sophisticated and therefore numerically more involved
    // If one want the Mehrotra method, simply replace "Gondzio" by "Mehrotra" .

    TGondzioSolver* solver = new TGondzioSolver(qp, prob);
    int ret = solver->Solve(prob, vars, resid);
    printf("ret = %d\n", ret);
    TVectorD weight = vars->fX;


    // function_minimum

    // vector_answer
    TMatrixD Mat_best(ncol_tot, 1);
    for(int icol = 0; icol < ncol_tot; icol ++){
        Mat_best[icol][0] = weight[icol];
    }
    TMatrixD Mat_Q_x_best(ncol_tot, 1);
    Mat_Q_x_best.Mult(Mat_Qp_Q, Mat_best);

    double term1 = 0.0;
    for(int icol = 0; icol < ncol_tot; icol ++){
        term1 += Mat_best[icol][0] * Mat_Q_x_best[icol][0];
    }
    term1 /= 2.0;
    double term2 = 0.0;
    for(int icol = 0; icol < ncol_tot; icol ++){
        term2 += Vec_Qp_c[icol] * Mat_best[icol][0];
    }
    double term3 = 0.0;
    for(int irow = 0; irow < nrow_tot; irow ++){
        term3 += Mat_b[irow][0] * Mat_b[irow][0];
    }
    double chi2_min = term1 + term2 + term3;

    printf("term1, term2, term3 = %e %e %e\n", term1, term2, term3);
    
    printf("chi2_min = %e\n", chi2_min);
    int npar_free = ncol_tot - nrEqual;
    double aic = chi2_min + 2 * npar_free;
    printf("aic = %e\n", aic);
    double bic = chi2_min + npar_free * (log(nrow_tot) - log(2 * kPi));
    printf("bic = %e\n", bic);
    
    //printf("---- QP --- \n");
    weight.Print();
    //printf("==== QP === \n");
    
    
    delete qp;
    delete prob;
    delete vars;
    delete resid;
    delete solver;


    int icol_tot = 0;
    double** par_best_arr = new double* [ngraph];
    for(int igraph = 0; igraph < ngraph; igraph ++){
        par_best_arr[igraph] = new double [nfunc_arr[igraph]];
        for(int ifunc = 0; ifunc < nfunc_arr[igraph]; ifunc ++){
            par_best_arr[igraph][ifunc] = weight[icol_tot];
            icol_tot ++;
        }
    }
    //
    // print results
    //
    printf("---- QP -----\n");
    for(int igraph = 0; igraph < ngraph; igraph ++){
        for(int ifunc = 0; ifunc < nfunc_arr[igraph]; ifunc ++){
            printf("igraph = %d: ifunc = %d: par = %e\n",
                   igraph, ifunc, par_best_arr[igraph][ifunc]);
        }
    }
    printf("==== QP =====\n");
    *par_best_arr_ptr = par_best_arr;
}


//
// Multi data, 2 dim
//

void MimLS::GenLeastSquarePoissonQuadProgPlusMulti(int nhist,
                                                    const HistData2d* const* const hd2d_arr,
                                                    const int* const nfunc_arr,
                                                    const MirFunc* const* const* const func_arr,
                                                    const MirFuncPar* const* const* const func_par_arr,
                                                    const MimTie* const mim_tie,
                                                    double*** const par_best_arr_ptr,
                                                    double* const chi2_min_ptr,
                                                    double* const aic_ptr,
                                                    double* const bic_ptr)
{
    //
    // matrix A_ij, b
    //
    long nrow_tot = 0;
    for(int ihist = 0; ihist < nhist; ihist ++){
        nrow_tot += hd2d_arr[ihist]->GetNbin();
    }
    long ncol_tot = 0;
    for(int ihist = 0; ihist < nhist; ihist ++){
        ncol_tot += nfunc_arr[ihist];
    }
    TMatrixD Mat_A(nrow_tot, ncol_tot);
    TMatrixD Mat_b(nrow_tot, 1);

    long irow_tot_pivot = 0;
    long icol_tot_pivot = 0; 
    for(int ihist = 0; ihist < nhist; ihist ++){
        for(long irow = 0; irow < hd2d_arr[ihist]->GetNbin(); irow ++){
            long irow_tot = irow_tot_pivot + irow;
            for(long icol = 0; icol < nfunc_arr[ihist]; icol ++){
                double xval = hd2d_arr[ihist]->GetHi2d()->GetBinCenterXFromIbin(irow);
                double yval = hd2d_arr[ihist]->GetHi2d()->GetBinCenterYFromIbin(irow);
                double oval = hd2d_arr[ihist]->GetOvalArr()->GetValElm(irow);
                double xval_arr[2];
                xval_arr[0] = xval;
                xval_arr[1] = yval;
                long icol_tot = icol_tot_pivot + icol;
                Mat_A[irow_tot][icol_tot] = func_arr[ihist][icol]->Eval(xval_arr, func_par_arr[ihist][icol]->GetPar()) /
                    sqrt(oval + 1.0);
            }
        }
        irow_tot_pivot += hd2d_arr[ihist]->GetNbin();
        icol_tot_pivot += nfunc_arr[ihist];
    }
    //Mat_A.Print();
    
    irow_tot_pivot = 0;
    for(int ihist = 0; ihist < nhist; ihist ++){
        for(long irow = 0; irow < hd2d_arr[ihist]->GetNbin(); irow ++){
            double oval = hd2d_arr[ihist]->GetOvalArr()->GetValElm(irow);
            long irow_tot = irow_tot_pivot + irow;
            Mat_b[irow_tot][0]  = (oval + MirMath::GetMin(oval, 1.0))/ sqrt(oval + 1.0);
        }
        irow_tot_pivot += hd2d_arr[ihist]->GetNbin();
    }
    //Mat_b.Print();

    TMatrixD Mat_A_trans(ncol_tot, nrow_tot);
    Mat_A_trans.Transpose(Mat_A);
    TMatrixD Mat_alpha(ncol_tot, ncol_tot);
    Mat_alpha.Mult(Mat_A_trans, Mat_A);
    TMatrixD Mat_beta(ncol_tot, 1);
    Mat_beta.Mult(Mat_A_trans, Mat_b);

    //
    // solve by QP
    //
    int nrVar = ncol_tot;
    int nrEqual = mim_tie->GetNtie();
    int nrInEqual = 0;

    // equality equation
    TVectorD Vec_Qp_b(nrEqual); Vec_Qp_b = 0;
    TMatrixD Mat_Qp_A(nrEqual, nrVar); 

    mim_tie->Print(stdout);
    
    if(nrEqual > 0){
        for(int itie = 0; itie < mim_tie->GetNtie(); itie ++){

            int icol_tot_lhs = 0;
            for(int idata = 0; idata < mim_tie->GetIdDataLhsElm(itie); idata ++){
                icol_tot_lhs += nfunc_arr[idata];
            }
            icol_tot_lhs += mim_tie->GetIdFuncLhsElm(itie);
                
            int icol_tot_rhs = 0;
            for(int idata = 0; idata < mim_tie->GetIdDataRhsElm(itie); idata ++){
                icol_tot_rhs += nfunc_arr[idata];
            }
            icol_tot_rhs += mim_tie->GetIdFuncRhsElm(itie);

            printf("icol_tot_lhs = %d\n", icol_tot_lhs);
            printf("icol_tot_rhs = %d\n", icol_tot_rhs);
                
            Mat_Qp_A[itie][icol_tot_lhs] =  1;
            Mat_Qp_A[itie][icol_tot_rhs] = -1;
        }
    } else {
        Mat_Qp_A = 0;
    }
    Mat_Qp_A.Print();

    // inequality equation
    TMatrixD Mat_C(nrInEqual, nrVar);
    TVectorD Vec_clo(nrInEqual);
    TVectorD Vec_cup(nrInEqual);
    TVectorD Vec_iclo(nrInEqual);
    TVectorD Vec_icup(nrInEqual);

    // simple square boundary condtion
    TVectorD Vec_xlo(nrVar); Vec_xlo = 0;
    TVectorD Vec_xup(nrVar); Vec_xup = 0;
    TVectorD Vec_ixlo(nrVar); Vec_ixlo = 1;
    TVectorD Vec_ixup(nrVar); Vec_ixup = 0;    
    
    // minimizing function
    TVectorD Vec_Qp_c(nrVar);
    for(int icol = 0; icol < ncol_tot; icol ++){
        Vec_Qp_c[icol] = -2 * Mat_beta[icol][0];
    }
    TMatrixDSym Mat_Qp_Q(ncol_tot);
    Mat_Qp_Q.TMult(Mat_A);
    Mat_Qp_Q *= 2.0;

    TQpProbDens* qp = new TQpProbDens(nrVar, nrEqual, nrInEqual);
    TQpDataDens* prob = (TQpDataDens *)qp->MakeData(Vec_Qp_c, Mat_Qp_Q,
                                                    Vec_xlo, Vec_ixlo, Vec_xup, Vec_ixup,
                                                    Mat_Qp_A, Vec_Qp_b,
                                                    Mat_C, Vec_clo, Vec_iclo, Vec_cup, Vec_icup);

    TQpVar* vars = qp->MakeVariables(prob);
    TQpResidual* resid = qp->MakeResiduals(prob);

    // Now we have to choose the method of solving, either TGondzioSolver or TMehrotraSolver
    // The Gondzio method is more sophisticated and therefore numerically more involved
    // If one want the Mehrotra method, simply replace "Gondzio" by "Mehrotra" .

    TGondzioSolver* solver = new TGondzioSolver(qp, prob);
    int ret = solver->Solve(prob, vars, resid);
    printf("ret = %d\n", ret);
    TVectorD weight = vars->fX;


    // function_minimum

    // vector_answer
    TMatrixD Mat_best(ncol_tot, 1);
    for(int icol = 0; icol < ncol_tot; icol ++){
        Mat_best[icol][0] = weight[icol];
    }
    TMatrixD Mat_Q_x_best(ncol_tot, 1);
    Mat_Q_x_best.Mult(Mat_Qp_Q, Mat_best);

    double term1 = 0.0;
    for(int icol = 0; icol < ncol_tot; icol ++){
        term1 += Mat_best[icol][0] * Mat_Q_x_best[icol][0];
    }
    term1 /= 2.0;
    double term2 = 0.0;
    for(int icol = 0; icol < ncol_tot; icol ++){
        term2 += Vec_Qp_c[icol] * Mat_best[icol][0];
    }
    double term3 = 0.0;
    for(int irow = 0; irow < nrow_tot; irow ++){
        term3 += Mat_b[irow][0] * Mat_b[irow][0];
    }
    double chi2_min = term1 + term2 + term3;

    printf("term1, term2, term3 = %e %e %e\n", term1, term2, term3);
    
    printf("chi2_min = %e\n", chi2_min);
    int npar_free = ncol_tot - nrEqual;
    double aic = chi2_min + 2 * npar_free;
    printf("aic = %e\n", aic);
    double bic = chi2_min + npar_free * (log(nrow_tot) - log(2 * kPi));
    printf("bic = %e\n", bic);
    
    //printf("---- QP --- \n");
    weight.Print();
    //printf("==== QP === \n");
    
    delete qp;
    delete prob;
    delete vars;
    delete resid;
    delete solver;

    int icol_tot = 0;
    double** par_best_arr = new double* [nhist];
    for(int ihist = 0; ihist < nhist; ihist ++){
        par_best_arr[ihist] = new double [nfunc_arr[ihist]];
        for(int ifunc = 0; ifunc < nfunc_arr[ihist]; ifunc ++){
            par_best_arr[ihist][ifunc] = weight[icol_tot];
            icol_tot ++;
        }
    }
    //
    // print results
    //
    printf("---- QP -----\n");
    for(int ihist = 0; ihist < nhist; ihist ++){
        for(int ifunc = 0; ifunc < nfunc_arr[ihist]; ifunc ++){
            printf("ihist = %d: ifunc = %d: par = %e\n",
                   ihist, ifunc, par_best_arr[ihist][ifunc]);
        }
    }
    printf("==== QP =====\n");
    *par_best_arr_ptr = par_best_arr;
    *chi2_min_ptr = chi2_min;
    *aic_ptr = aic;
    *bic_ptr = bic;
}


//
// Multi data, 2 dim
//

void MimLS::GenLeastSquarePoissonQuadProgPlusMulti(int nhist,
                                                    const HistData2d* const* const hd2d_arr,
                                                    const MifcLincombCtn* const* const func_ctn_arr,
                                                    const MimTie* const mim_tie,
                                                    MifcLincombCtn*** const func_ctn_best_arr_ptr,
                                                    double* const chi2_min_ptr,
                                                    double* const aic_ptr,
                                                    double* const bic_ptr)
{
    int* nfunc_arr = new int [nhist];
    MirFunc*** func_arr = new MirFunc** [nhist];
    MirFuncPar*** func_par_arr = new MirFuncPar** [nhist];
    for(int ihist = 0; ihist < nhist; ihist ++){
        nfunc_arr[ihist]    = func_ctn_arr[ihist]->GetNfunc();
        func_arr[ihist]     = new MirFunc* [ nfunc_arr[ihist] ];
        func_par_arr[ihist] = new MirFuncPar* [ nfunc_arr[ihist] ];
        for(int ifunc = 0; ifunc < nfunc_arr[ihist]; ifunc ++){
            func_arr[ihist][ifunc]     = dynamic_cast<MirFunc*>(func_ctn_arr[ihist]->GetFuncArrElm(ifunc)->Clone());
            func_par_arr[ihist][ifunc] = func_ctn_arr[ihist]->GetFuncParArrElm(ifunc)->Clone();
        }
    }

    double** par_best_arr = NULL;
    double chi2_min = 0.0;
    double aic = 0.0;
    double bic = 0.0;
    GenLeastSquarePoissonQuadProgPlusMulti(nhist,
                                           hd2d_arr,
                                           nfunc_arr,
                                           func_arr,
                                           func_par_arr,
                                           mim_tie,
                                           &par_best_arr,
                                           &chi2_min,
                                           &aic,
                                           &bic);
    MifcLincombCtn** func_ctn_best_arr = new MifcLincombCtn* [nhist];
    for(int ihist = 0; ihist < nhist; ihist ++){
        func_ctn_best_arr[ihist] = new MifcLincombCtn;
        func_ctn_best_arr[ihist]->Copy(func_ctn_arr[ihist]);
        for(int ifunc = 0; ifunc < nfunc_arr[ihist]; ifunc ++){
            func_ctn_best_arr[ihist]->SetCoeffArrElm(ifunc, par_best_arr[ihist][ifunc]);
        }
    }

    
    for(int ihist = 0; ihist < nhist; ihist ++){
        for(int ifunc = 0; ifunc < nfunc_arr[ihist]; ifunc ++){
            delete func_arr[ihist][ifunc]; func_arr[ihist][ifunc] = NULL;
            delete func_par_arr[ihist][ifunc]; func_par_arr[ihist][ifunc] = NULL;
        }
        delete [] func_arr[ihist]; func_arr[ihist] = NULL;
        delete [] func_par_arr[ihist]; func_par_arr[ihist] = NULL;
    }
    delete [] func_arr; func_arr = NULL;
    delete [] func_par_arr; func_par_arr = NULL;
    delete [] nfunc_arr; nfunc_arr = NULL;
    
    for(int ihist = 0; ihist < nhist; ihist ++){
        delete [] par_best_arr[ihist]; par_best_arr[ihist] = NULL;
    }
    delete [] par_best_arr; par_best_arr = NULL;
    
    *func_ctn_best_arr_ptr = func_ctn_best_arr;
    *chi2_min_ptr = chi2_min;
    *aic_ptr = aic;
    *bic_ptr = bic;
}

    
