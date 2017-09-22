#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"

#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "arg_lasso.h"

#include <vigra/regression.hxx>

#ifdef PI
#undef PI
#endif

#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValLasso* argval = new ArgValLasso;
    argval->Init(argc, argv);
    argval->Print(stdout);
 
    if(MxkwIolib::TestFileExist(argval->GetOutdir())){
        char cmd[kLineSize];
        sprintf(cmd, "mkdir -p %s", argval->GetOutdir().c_str());
        system(cmd);
    }
    FILE* fp_log;
    fp_log = fopen((argval->GetOutdir() + "/"
                    + argval->GetProgname() + ".log").c_str(), "w");
    argval->Print(fp_log);

    MxkwRootTool* root_tool = new MxkwRootTool;
    root_tool->InitTCanvas(argval->GetRootStyle());

    GraphData2d* gd2d = GraphData2d::GenGd2dByLoad(argval->GetFile(),
                                                   argval->GetFormat());
    double xval_lo = gd2d->GetXvalElm(0) - gd2d->GetXvalSerrElm(0);
    double xval_up = gd2d->GetXvalElm(gd2d->GetNdata() - 1)
        - gd2d->GetXvalSerrElm(gd2d->GetNdata() - 1);
    long nbin_xval = (long) floor( (xval_up - xval_lo)
                                   / argval->GetTbinfwidth());

    HistDataSerr1d* hd1d = new HistDataSerr1d;
    HistData1d* hd1d_mask = new HistData1d;
    hd1d->Init(nbin_xval, xval_lo, xval_up);
    hd1d->SetZero();
    hd1d_mask->Init(nbin_xval, xval_lo, xval_up);
    hd1d_mask->SetZero();
    for(long idata = 0; idata < gd2d->GetNdata(); idata ++){
        long ibin = hd1d->GetIbin( gd2d->GetXvalElm(idata) );
        hd1d->SetOvalElm( ibin, gd2d->GetOvalElm(idata));
        hd1d->SetOvalSerrElm( ibin, gd2d->GetOvalSerrElm(idata));
        hd1d_mask->SetOvalElm( ibin, 1.0);
    }        

    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
        printf("%ld %e  %e\n", ibin, hd1d->GetOvalElm(ibin), hd1d_mask->GetOvalElm(ibin) );
    }

    // test
    {
        // get Number of mask-on bin
        long nbin_mask_on = 0;
        for(long ibin = 0; ibin < hd1d_mask->GetNbinX(); ibin ++){
            if(0.0 < hd1d_mask->GetOvalElm(ibin)){
                nbin_mask_on ++;
            }
        }
        printf("nbin_mask_on = %ld\n", nbin_mask_on);

        // shrinked array
        DataArraySerr1d* da1d_shrink = new DataArraySerr1d;
        DataArray1d* da1d_shrink_index_org = new DataArray1d;
        da1d_shrink->Init(nbin_mask_on);
        da1d_shrink_index_org->Init(nbin_mask_on);
        long idata = 0;
        for(long ibin = 0; ibin < hd1d_mask->GetNbinX(); ibin ++){
            if(0.0 < hd1d_mask->GetOvalElm(ibin)){
                da1d_shrink->SetValElm(idata, hd1d->GetOvalElm(ibin));
                da1d_shrink->SetValSerrElm(idata, hd1d->GetOvalSerrElm(ibin));
                da1d_shrink_index_org->SetValElm(idata, ibin);
                idata ++;
            }
        }

        // nrow_A, ncol_A
        long nrow_A = da1d_shrink->GetNdata();
        long ncol_A_half = hd1d->GetNbinX();
        long ncol_A = ncol_A_half * 2;
        vigra::Matrix<double> A(nrow_A, ncol_A);
        vigra::Matrix<double> b(nrow_A, 1);

        for(long irow = 0; irow < nrow_A; irow ++){
            long index_org = (long) da1d_shrink_index_org->GetValElm(irow);
            for(long icol = 0; icol < ncol_A_half; icol ++){
                double arg = 2 * M_PI * index_org * icol / ncol_A_half;
                A(irow, icol)               = cos(arg);
                A(irow, ncol_A_half + icol) = sin(arg);
            }
            b(irow, 0) = da1d_shrink->GetValElm(irow);
        }

        printf("aaa\n");
        
        //// normalize the input
        vigra::Matrix<double> offset(1,ncol_A), scaling(1,ncol_A);
        vigra::prepareColumns(A, A, offset, scaling,
                             vigra::linalg::DataPreparationGoals(
                                  vigra::linalg::ZeroMean|vigra::linalg::UnitVariance));
        vigra::prepareColumns(b, b, vigra::linalg::DataPreparationGoals(vigra::linalg::ZeroMean));
        
        // arrays to hold the output
        vigra::ArrayVector< vigra::ArrayVector<int> > activeSets;
        vigra::ArrayVector< vigra::Matrix<double> > solutions;
        // run leastAngleRegression() in non-negative LASSO mode
        int numSolutions = vigra::leastAngleRegression(A, b, activeSets, solutions,
                                                       vigra::LeastAngleRegressionOptions().lasso());
        printf("numSolutions = %d\n", numSolutions);
        
        // print results
        vigra::Matrix<double> denseSolution(1, ncol_A);
        for(vigra::MultiArrayIndex k = 0; k < numSolutions; ++k){

            if(k == 10){
                // transform the sparse solution into a dense vector
                denseSolution.init(0.0); // ensure that inactive variables are zero
                for (unsigned int i = 0; i < activeSets[k].size(); ++i)
                    {
                        // set the values of the active variables;
                        // activeSets[k][i] is the true index of the i-th variable in the active set
                        denseSolution(0, activeSets[k][i]) = solutions[k](i,0);
                    }
                // invert the input normalization
                denseSolution = denseSolution * pointWise(scaling);
//            // output the solution
                std::cout << "solution " << k << ":\n" << denseSolution << std::endl;
            }
            
        }


        double delta_nu = 0.0;
        if("day" == argval->GetTunit()){
            delta_nu = 1./(hd1d->GetNbinX() * hd1d->GetBinWidth() * kDayToSec);
        } else if ("sec" == argval->GetTunit()){
            delta_nu = 1./(hd1d->GetNbinX() * hd1d->GetBinWidth());
        }

        HistData1d* hd1d_freq = new HistData1d;
        long nbin_freq = nbin_xval;
        double freq_lo = -1 * delta_nu / 2.0;
        double freq_up = delta_nu * (nbin_freq - 0.5);
        hd1d_freq->Init(nbin_freq, freq_lo, freq_up);
        hd1d_freq->SetZero();
        for(long ibin = 0; ibin < nbin_freq; ibin ++){
            double freq = delta_nu * ibin;
            double power = pow(denseSolution(0, ibin), 2)
                + pow(denseSolution(0, ibin + nbin_xval), 2);
            hd1d_freq->SetOvalElm(ibin, power);
        }

        MxkwQdpTool::MkQdp(hd1d_freq, argval->GetOutdir() + "/"
                           + argval->GetOutfileHead() + "_lasso.qdp",
                           "x,y");
        
    } // test

    

    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;

    return status;
}


