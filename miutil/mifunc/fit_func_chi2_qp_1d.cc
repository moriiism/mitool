#include "TMatrixD.h"
#include "TDecompSVD.h"
#include "TQpDataDens.h"
#include "TQpProbDens.h"
#include "TMatrixD.h"
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TQpProbDens.h"
#include "TGondzioSolver.h"

#include "mi_iolib.h"
#include "mir_data1d_serr.h"
#include "mir_graph2d_serr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist2d_serr.h"
#include "mim_fitparam.h"
#include "mim_chi2plot.h"
#include "mim_fitstat_hg.h"
#include "mim_fitfunc.h"
#include "mim_minfcn.h"
#include "mifc_gen.h"
#include "mir_func_ope.h"
#include "mir_qdp_tool.h"

#include "func_user.h"
#include "arg_fit_func_chi2_qp_1d.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){

    int status = kRetNormal;
    
    ArgValFitFuncChi2Qp1d* argval = new ArgValFitFuncChi2Qp1d;
    argval->Init(argc, argv);
    argval->Print(stdout);

    MirRootTool* root_tool = new MirRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());
    
    char logfile[kLineSize];
    if( MiIolib::TestFileExist(argval->GetOutdir()) ){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    sprintf(logfile, "%s/%s_%s.log",
            argval->GetOutdir().c_str(),
            argval->GetOutfileHead().c_str(),
            argval->GetProgname().c_str());
    FILE* fp_log = fopen(logfile, "w");
    MiIolib::Printf2(fp_log, "-----------------------------\n");
    argval->Print(fp_log);
    
    //
    // data
    //
    GraphDataSerr2d* g2d = new GraphDataSerr2d;
    g2d->Load(argval->GetDataFile(), argval->GetDataFmt());


    //
    // function & parfile
    //
    long nfunc;
    string* func_list_line_arr = NULL;
    string* func_name_arr = NULL;
    string* par_file_arr = NULL;
    int* func_line_style_arr = NULL;
    int* func_line_color_arr  = NULL;
    string* func_range_lo_arr = NULL;
    string* func_range_up_arr = NULL;
    MiIolib::GenReadFileSkipComment(argval->GetFuncParList(), &func_list_line_arr, &nfunc);
    func_name_arr = new string [nfunc];
    par_file_arr = new string [nfunc];
    func_line_style_arr = new int [nfunc];
    func_line_color_arr = new int [nfunc];
    func_range_lo_arr = new string [nfunc];
    func_range_up_arr = new string [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        int ncolumn = MiStr::GetNcolumn(func_list_line_arr[ifunc]);
        if(6 != ncolumn){
            MPrintErr("ncolumn != 6");
            abort();
        }
        char func_name_tmp[kLineSize];
        char par_file_tmp[kLineSize];
        char func_range_lo_tmp[kLineSize];
        char func_range_up_tmp[kLineSize];
        sscanf(func_list_line_arr[ifunc].c_str(), "%s %s %d %d %s %s",
               func_name_tmp, par_file_tmp,
               &func_line_style_arr[ifunc], &func_line_color_arr[ifunc],
               func_range_lo_tmp, func_range_up_tmp);
        func_name_arr[ifunc] = func_name_tmp;
        par_file_arr[ifunc] = par_file_tmp;
        func_range_lo_arr[ifunc] = func_range_lo_tmp;
        func_range_up_arr[ifunc] = func_range_up_tmp;        
        printf("func_name, par_file = %s  %s\n", func_name_arr[ifunc].c_str(), par_file_arr[ifunc].c_str());
    }
    MiIolib::DelReadFile(func_list_line_arr);


    //
    // plot configuration
    //
    MirPlotConf* plot_conf = new MirPlotConf;
    plot_conf->Load(argval->GetPlotConfFile());
    plot_conf->Print(stdout);
    root_tool->SetPlotConf(plot_conf);
    

    MirFunc** func_arr = new MirFunc* [nfunc];
    MirFuncPar** func_par_arr = new MirFuncPar* [nfunc];
    TF1** tf1_func_arr  = new TF1* [nfunc];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        func_arr[ifunc] = FuncUser::GenFunc(func_name_arr[ifunc]);
        func_par_arr[ifunc] = new MirFuncPar;
        func_par_arr[ifunc]->Load(par_file_arr[ifunc]);
        double func_range_lo = 0.0;
        double func_range_up = 0.0;
        if("none" == func_range_lo_arr[ifunc]){
            func_range_lo = atof(plot_conf->GetLoStrElm(0).c_str());
        } else {
            func_range_lo = atof(func_range_lo_arr[ifunc].c_str());
        }
        if("none" == func_range_up_arr[ifunc]){
            func_range_up = atof(plot_conf->GetUpStrElm(0).c_str());
        } else {
            func_range_up = atof(func_range_up_arr[ifunc].c_str());
        }
        tf1_func_arr[ifunc] = MirFuncOpe::GenTF1(func_arr[ifunc], func_range_lo, func_range_up);
        MirFuncPar::CopyPar(func_par_arr[ifunc], tf1_func_arr[ifunc]);
        tf1_func_arr[ifunc]->SetLineStyle(func_line_style_arr[ifunc]);
        tf1_func_arr[ifunc]->SetLineColor(func_line_color_arr[ifunc]);

        printf("ifunc = %d: %s\n", ifunc, func_arr[ifunc]->GetClassName().c_str());
        
        tf1_func_arr[ifunc]->Draw("SAME");
        tf1_func_arr[ifunc]->Draw("sameaxis");
    }

    //
    // matrix A_ij, b
    //

    long nrow = g2d->GetNdata();
    long ncol = nfunc;
    TMatrixD Mat_A(nrow, ncol);
    TMatrixD Mat_b(nrow, 1);    
    if("gauss" == argval->GetStat()){
        for(long irow = 0; irow < nrow; irow ++){
            for(long icol = 0; icol < ncol; icol ++){
                double xval      = g2d->GetXvalElm(irow);
                double yval_serr = g2d->GetOvalSerrElm(irow);
                double xval_arr[1];
                xval_arr[0] = xval;
                Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) / yval_serr;
            }
        }
        Mat_A.Print();

        for(long irow = 0; irow < nrow; irow ++){
            double yval = g2d->GetOvalElm(irow);
            double yval_serr = g2d->GetOvalSerrElm(irow);
            Mat_b[irow][0]  = yval / yval_serr;
        }
        Mat_b.Print();
    } else if ("poisson" == argval->GetStat()){
        for(long irow = 0; irow < nrow; irow ++){
            for(long icol = 0; icol < ncol; icol ++){
                double xval = g2d->GetXvalElm(irow);
                double yval = g2d->GetOvalElm(irow);
                double xval_arr[1];
                xval_arr[0] = xval;
                Mat_A[irow][icol] = func_arr[icol]->Eval(xval_arr, func_par_arr[icol]->GetPar()) /
                    sqrt(yval + 1.0);
            }
        }
        Mat_A.Print();

        for(long irow = 0; irow < nrow; irow ++){
            double yval = g2d->GetOvalElm(irow);
            Mat_b[irow][0]  = (yval + MirMath::GetMin(yval, 1.0))/ sqrt(yval + 1.0);
        }
        Mat_b.Print();
    } else {
        abort();
    }

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

    TQpProbDens* qp = new TQpProbDens(nrVar,nrEqual,nrInEqual);
    TQpDataDens* prob = (TQpDataDens *)qp->MakeData(Vec_Qp_c, Mat_Qp_Q,
                                                    Vec_xlo, Vec_ixlo, Vec_xup, Vec_ixup,
                                                    Mat_Qp_A, Vec_Qp_b,
                                                    Mat_C, Vec_clo, Vec_iclo, Vec_cup, Vec_icup);

    TQpVar* vars = qp->MakeVariables(prob);
    TQpResidual* resid = qp->MakeResiduals(prob);

    // Now we have to choose the method of solving, either TGondzioSolver or TMehrotraSolver
    // The Gondzio method is more sophisticated and therefore numerically more involved
    // If one want the Mehrotra method, simply replace "Gondzio" by "Mehrotra" .

    TGondzioSolver* s = new TGondzioSolver(qp, prob);
    int ret = s->Solve(prob, vars, resid);
    TVectorD weight = vars->fX;

    printf("---- QP --- \n");
    weight.Print();
    
    
    delete qp;
    delete prob;
    delete vars;
    delete resid;
    delete s;

    
    //
    // solve by SVD
    //

    TDecompSVD Mat_A_SVD(Mat_A);
    printf("%d\n", Mat_A_SVD.Decompose());

    TVectorD Vec_b(nrow);
    for(long irow = 0; irow < nrow; irow ++){
        Vec_b[irow] = Mat_b[irow][0];
    }
    Vec_b.Print();
    
    Mat_A_SVD.Solve(Vec_b);

    TMatrixD Mat_U = Mat_A_SVD.GetU();
    TMatrixD Mat_V = Mat_A_SVD.GetV();
    TVectorD Vec_Sig = Mat_A_SVD.GetSig();

    Mat_A_SVD.GetSig().Print();

    
    TMatrixD Mat_cov_svd(ncol, ncol);
    for(long irow_cov = 0; irow_cov < ncol; irow_cov ++){
        for(long icol_cov = 0; icol_cov < ncol; icol_cov ++){
            double cov = 0.0;
            for(long icol_this = 0; icol_this < ncol; icol_this ++){
                cov += Mat_A_SVD.GetV()[irow_cov][icol_this] * Mat_A_SVD.GetV()[icol_cov][icol_this]
                    / (Mat_A_SVD.GetSig()[icol_this] * Mat_A_SVD.GetSig()[icol_this]);
            }
            Mat_cov_svd[irow_cov][icol_cov] = cov;
        }
    }
    
    double* par_serr_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_serr_svd[icol] = sqrt(Mat_cov_svd[icol][icol]);
    }
    
    Vec_b.Print();

    double* par_best_svd = new double[ncol];
    for(long icol = 0; icol < ncol; icol ++){
        par_best_svd[icol] = Vec_b[icol];
    }

    //
    // print results
    //
    printf("---- svd -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par +- err = %e +/- %e\n",
               icol, par_best_svd[icol], par_serr_svd[icol]);
    }
    printf("==== svd =====\n");    

    //
    // solve by matrix operation
    //
    

    TMatrixD Mat_cov(ncol, ncol);
    Mat_cov = Mat_alpha.Invert();
    // Mat_cov.Print();

    TMatrixD Mat_a(ncol, 1);
    Mat_a = Mat_cov * Mat_A_trans * Mat_b;
    //Mat_a.Print();
    
    double* par_best = new double[ncol];
    for(int icol = 0; icol < ncol; icol ++){
        par_best[icol] = Mat_a[icol][0];
    }
    double* par_serr = new double[ncol];
    for(int icol = 0; icol < ncol; icol ++){
        par_serr[icol] = sqrt(Mat_cov[icol][icol]);
    }

    //
    // print results
    //
    printf("---- usual -----\n");
    for(int icol = 0; icol < ncol; icol ++){
        printf("icol = %d: par +- err = %e +/- %e\n",
               icol, par_best[icol], par_serr[icol]);
    }
    printf("==== usual =====\n");    
    
    // compare results
    for(int icol = 0; icol < ncol; icol ++){
        printf("par_best, par_best_svd = %e %e\n", par_best[icol], par_best_svd[icol]);
    }

    //
    // fit result
    //

    LinCombFunc* func_lincomb = new LinCombFunc;
    func_lincomb->InitSet(nfunc, func_arr);
    int ipar_tot = 0;
    double* par_func_lincomb = new double [func_lincomb->GetNpar()];
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        for(int ipar = 0; ipar < func_par_arr[ifunc]->GetNpar(); ipar ++){
            par_func_lincomb[ipar_tot] = func_par_arr[ifunc]->GetParElm(ipar);
            ipar_tot ++;
        }
    }
    for(int ifunc = 0; ifunc < nfunc; ifunc ++){
        par_func_lincomb[ipar_tot] = par_best[ifunc];
        ipar_tot ++;
    }
    
    for(int ipar = 0; ipar < func_lincomb->GetNpar(); ipar ++){
        printf("par_func_lincomb[%d] = %e\n", ipar, par_func_lincomb[ipar]);
    }
    
    FitStatHG::MkOutFitPlot(g2d, func_lincomb,
                            par_func_lincomb,
                            argval->GetNpointFunc(),
                            argval->GetOutdir(),
                            argval->GetOutfileHead(),
                            plot_conf);
    
    printf("%s: end.\n", argval->GetProgname().c_str());

    delete argval;
    delete g2d;

    fclose(fp_log);

    return status;
}
