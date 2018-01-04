#include "fftw3.h"
#include "mi_iolib.h"
#include "mir_hist1d_nerr.h"
#include "mir_qdp_tool.h"
#include "arg_mipow.h"

// global variable 
int g_flag_debug = 0;
int g_flag_help = 0;
int g_flag_verbose = 0;

int main(int argc, char* argv[]){
    int status = kRetNormal;
  
    ArgValMipow* argval = new ArgValMipow;
    argval->Init(argc, argv);

    HistDataNerr1d* hd1d = new HistDataNerr1d;
    hd1d->Load(argval->GetInfile());
    // hd1d->PrintData(stdout, "x,y", 0.0, 0.0);

    long nbin = hd1d->GetNbinX();
    long nbin_half = nbin / 2;
    
    fftw_complex* in = NULL;
    fftw_complex* out = NULL;
    fftw_plan plan = NULL;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nbin);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nbin);

    plan = fftw_plan_dft_1d(nbin, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for(long ibin = 0; ibin < nbin; ibin ++){
        in[ibin][0] = 0.0;
        in[ibin][1] = 0.0;
        out[ibin][0] = 0.0;
        out[ibin][1] = 0.0;
    }

    for(long ibin = 0; ibin < nbin; ibin ++){
        in[ibin][0] = hd1d->GetOvalElm(ibin);
        in[ibin][1] = 0.0;
    }
  
    fftw_execute(plan);
    double* output    = new double [2 * (nbin_half + 1)];
    double* out_real  = new double [nbin_half + 1];
    double* out_image = new double [nbin_half + 1];
  
    for(long ibin = 0; ibin < nbin_half + 1; ibin++ ){
        out_real[ibin]  = out[ibin][0];
        out_image[ibin] = out[ibin][1];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);


    // calculate Power Spectrum
    double* freq  = new double [nbin_half + 1];
    double* power = new double [nbin_half + 1];
    double nbin_pow2 = pow(nbin, 2);
    freq[0] = 0.0;
    power[0] = (pow(out_real[0], 2) + pow(out_image[0], 2)) / nbin_pow2;
    for(long ibin = 1; ibin < nbin_half; ibin++){
        freq[ibin] = ibin / nbin;
        power[ibin] = 2.0 * (pow(out_real[ibin], 2) + pow(out_image[ibin], 2)) / nbin_pow2;

        printf("%d %e\n", ibin, power[ibin]);
    }
    freq[nbin_half] = 1.0 / 2.0;
    power[nbin_half] = (pow(out_real[nbin_half], 2) + pow(out_image[nbin_half], 2)) / nbin_pow2;



    
    delete argval;
    
    return status;
}

