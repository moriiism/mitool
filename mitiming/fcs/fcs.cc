#include "mxkw_iolib.h"
#include "mxkw_hist1d.h"
#include "mxkw_hist1d_serr.h"
#include "mxkw_search_par.h"
#include "mxkw_qdp_tool.h"

#include "mxkw_timing_eph.h"
#include "mxkw_timing_telescope.h"
#include "mxkw_timing_func_pls.h"
#include "mxkw_timing_folding.h"
#include "arg_fcs.h"

#ifdef PI
#undef PI
#endif

// #define KSCI_ENABLE_DYNAMIC_FFTW
#include <KL1pInclude.h>
#include "armadillo_bits/config.hpp"
#include "sub.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;


int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValFcs* argval = new ArgValFcs;
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

    long nope = hd1d->GetNbinX();
    nope = nope;
    printf("nope = %ld\n", nope);    
    
    // klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > F = new kl1p::TFourier1DOperator<std::complex<klab::DoubleReal> >( nope );    // Create Fourier operator.

    klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > F = new kl1p::TInverseFourier1DOperator<std::complex<klab::DoubleReal> >( nope );    // Create Fourier operator.
    
    // klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > S = new kl1p::TRandomDownSamplingOperator<std::complex<klab::DoubleReal> >(5, nope);        // Create random measurement operator.

    //klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > S = new kl1p::TDownSamplingOperator<std::complex<klab::DoubleReal> >(5, nope);        // Create random measurement operator.
    
    klab::KBitArray mask(nope);
    long num_mask_on = 0;
    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
        if(1 == hd1d_mask->GetOvalElm(ibin)){
            mask.setBit(ibin, 1);
            num_mask_on ++;
        } else {
            mask.setBit(ibin, 0);
        }
    }

    printf("num_mask_on = %ld\n", num_mask_on);
    
    klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > S = new kl1p::TDownSamplingOperator<std::complex<klab::DoubleReal> >(mask);
    klab::TSmartPointer<kl1p::TOperator<std::complex<klab::DoubleReal> > > A = S * F;       //Create the sensing operator.  
    // A  = new kl1p::TScalingOperator<std::complex<klab::DoubleReal> >(A, 1.0/klab::Sqrt(klab::DoubleReal(num_mask_on)));
    // Pseudo-normalization of the matrix (required for AMP and EMBP solvers).

    //arma::Mat<std::complex<klab::DoubleReal> > KKK;
    // S->toMatrix(KKK);
    // KKK.print();
    
    arma::Col<std::complex<klab::DoubleReal> > y;
    y.set_size(num_mask_on);
    long ibin_fill = 0;
    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
        if(1 == hd1d_mask->GetOvalElm(ibin)){
            std::complex<klab::DoubleReal> cval(hd1d->GetOvalElm(ibin), 0.0);
            std::cout << cval << std::endl;
            y[ibin_fill] = cval;
            std::cout << y[ibin_fill] << std::endl;
            ibin_fill ++;
        }
    }
    
    klab::DoubleReal tolerance = 1e-3;      // Tolerance of the solution.
    arma::Col<std::complex<klab::DoubleReal> > cx;  // Will contain the complex solution of the reconstruction.
    // arma::Col<klab::DoubleReal> x;          // Will contain the solution of the reconstruction.

    klab::KTimer timer;

    // Compute Basis-Pursuit.
    std::cout<<"[BasisPursuit] Start."<<std::endl;
    timer.start();
    kl1p::TBasisPursuitSolver<klab::DoubleReal, std::complex<klab::DoubleReal> > bp(tolerance);

    printf("aaaa\n");
    bp.solve(y, A, cx);
    timer.stop();
    // x.set_size(cx.n_rows);
    printf("cx.n_rows = %d\n", cx.n_rows);


    
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
        // double freq = delta_nu * ibin;
        double power = pow(cx[ibin].real(), 2) + pow(cx[ibin].imag(), 2);
        hd1d_freq->SetOvalElm(ibin, power);
    }

    MxkwQdpTool::MkQdp(hd1d_freq, argval->GetOutdir() + "/"
                       + argval->GetOutfileHead() + "_fcs.qdp",
                       "x,y");
    
//    std::cout<<"[BasisPursuit] Done - SNR="<<std::setprecision(5)<<klab::SNR(x, x0)<<" - "
//             <<"Time="<<klab::UInt32(timer.durationInMilliseconds())<<"ms"<<" - "
//             <<"Iterations="<<bp.iterations()<<std::endl;
  
    //
    // cleaning
    //
    fclose(fp_log);
    delete argval;

    return status;
}


