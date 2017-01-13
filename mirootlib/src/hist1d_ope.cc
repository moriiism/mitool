#include "mir_data_ope.h"
#include "mir_hist1d_ope.h"

// For a HistData1d

void HistData1dOpe::GetPowSpec(const HistData1d* const hist_data,
                               HistData1d* hist_data_out)
{
    long ntime = hist_data->GetNbinX();
    double tbinfwidth = hist_data->GetBinWidth();
    if(0 != ntime % 2){
        printf("powspec error.\n");
        abort();
    }

    fftw_complex* in = NULL;
    fftw_complex* out = NULL;
    fftw_plan plan = NULL;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ntime);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ntime);

    plan = fftw_plan_dft_1d(ntime, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  
    for(long idata = 0; idata < ntime; idata ++){
        in[idata][0] = 0.0;
        in[idata][1] = 0.0;
        out[idata][0] = 0.0;
        out[idata][1] = 0.0;
    }

    for(long idata = 0; idata < ntime; idata ++){
        in[idata][0] = hist_data->GetOvalElm(idata);
        in[idata][1] = 0.0;
    }
  
    fftw_execute(plan);

    long ntime_half = ntime / 2 ;
    double* output    = new double [2 * (ntime_half + 1)];
    double* out_real  = new double [ntime_half + 1];
    double* out_image = new double [ntime_half + 1];
  
    for(long itime = 0; itime < ntime_half + 1; itime++ ){
        //out_real[itime]  = out[2 * itime];
        //out_image[itime] = out[2 * itime + 1];
        out_real[itime]  = out[itime][0];
        out_image[itime] = out[itime][1];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    // calculate Power Spectrum
    double* freq  = new double [ntime_half + 1];
    double* power = new double [ntime_half + 1];
    double ntime_pow2 = pow(ntime, 2);
    freq[0] = 0.0;
    power[0] = (pow(out_real[0], 2) + pow(out_image[0], 2)) / ntime_pow2;
    for(long itime = 1; itime < ntime_half; itime++){
        freq[itime] = itime / (ntime * tbinfwidth);
        power[itime] = 2.0 * (pow(out_real[itime], 2) + pow(out_image[itime], 2)) / ntime_pow2;
    }
    freq[ntime_half] = 1.0 / (2.0 * tbinfwidth);
    power[ntime_half] = (pow(out_real[ntime_half], 2) + pow(out_image[ntime_half], 2)) / ntime_pow2;

    hist_data_out->InitSet(ntime_half + 1, -0.5 / (ntime * tbinfwidth),
                           (ntime_half + 0.5) / (ntime * tbinfwidth),
                           power);

    delete [] output;
    delete [] out_real;
    delete [] out_image;
    delete [] freq;
    delete [] power;
}


//
// Leahy normalized Power spectrum for counts (Poisson statistics)
//

void HistData1dOpe::GetPowSpecLeahyNorm(const HistData1d* const hist_data,
                                        HistData1d* hist_data_out)
{
    long ntime = hist_data->GetNbinX();
    double tbinfwidth = hist_data->GetBinWidth();
    if(0 != ntime % 2){
        printf("powspec error.\n");
        abort();
    }
    long n_total = (long) hist_data->GetOvalArr()->GetSum();
      
    fftw_complex *in = NULL;
    fftw_complex *out = NULL;
    fftw_plan plan = NULL;
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ntime);
    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * ntime);

    plan = fftw_plan_dft_1d(ntime, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  
    for(long idata = 0; idata < ntime; idata ++){
        in[idata][0] = 0.0;
        in[idata][1] = 0.0;
        out[idata][0] = 0.0;
        out[idata][1] = 0.0;
    }

    for(long idata = 0; idata < ntime; idata ++){
        in[idata][0] = hist_data->GetOvalElm(idata);
        in[idata][1] = 0.0;
    }
  
    fftw_execute(plan);
  
    long ntime_half = ntime / 2 ;
    double* output    = new double [2 * (ntime_half + 1)];
    double* out_real  = new double [ntime_half + 1];
    double* out_image = new double [ntime_half + 1];
  
    for(long itime = 0; itime < ntime_half + 1; itime++ ){
        out_real[itime]  = out[itime][0];
        out_image[itime] = out[itime][1];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    // calculate Leahy normalized Power Spectrum
    double* freq  = new double [ntime_half + 1];
    double* power_leahy = new double [ntime_half + 1];
    // double ntime_pow2 = pow(ntime, 2);
    freq[0] = 0.0;
    power_leahy[0] = 2 * (pow(out_real[0], 2) + pow(out_image[0], 2)) / n_total;
    for(long itime = 1; itime < ntime_half; itime++){
        freq[itime] = itime / (ntime * tbinfwidth);
        power_leahy[itime] = 2.0 * (pow(out_real[itime], 2) + pow(out_image[itime], 2)) / n_total;
    }
    freq[ntime_half] = 1.0 / (2.0 * tbinfwidth);
    power_leahy[ntime_half] = (pow(out_real[ntime_half], 2) + pow(out_image[ntime_half], 2)) / n_total;

    hist_data_out->InitSet(ntime_half + 1, -0.5 / (ntime * tbinfwidth),
                           (ntime_half + 0.5) / (ntime * tbinfwidth),
                           power_leahy);

    delete [] output;
    delete [] out_real;
    delete [] out_image;
    delete [] freq;
    delete [] power_leahy;
}

void HistData1dOpe::GetPowSpecNonfft(const HistData1d* const hist_data,
                                     HistData1d* hist_data_out)
{
    long nbin = hist_data->GetNbinX();
    double tbinfwidth = hist_data->GetBinWidth();
  
    double* out_real = new double [nbin];
    double* out_imag = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        out_real[ibin] = 0.0;
        out_imag[ibin] = 0.0;
        for(long jbin = 0; jbin < nbin; jbin++){
            out_real[ibin] += cos(2 * M_PI * jbin * ibin /(nbin))
                * hist_data->GetOvalElm(jbin);
            out_imag[ibin] += sin(2 * M_PI * jbin * ibin /(nbin))
                * hist_data->GetOvalElm(jbin);
        }
    }

    // calculate Power Spectrum
    double* freq  = new double [nbin + 1];
    double* power = new double [nbin + 1];
    double nbin_pow2 = pow(nbin, 2);
    freq[0] = 0.0;
    power[0] = (pow(out_real[0], 2) + pow(out_imag[0], 2)) / nbin_pow2;
    for(long itime = 1; itime < nbin; itime++){
        freq[itime]  = itime / (nbin * tbinfwidth);
        power[itime] = 2.0 * (pow(out_real[itime], 2) + pow(out_imag[itime], 2)) / nbin_pow2;
    }
    freq[nbin] = 1.0 / (2.0 * tbinfwidth);
    power[nbin] = (pow(out_real[nbin], 2) + pow(out_imag[nbin], 2)) / nbin_pow2;

    double xval_lo = -0.5 / (nbin * tbinfwidth);
    double xval_up = (nbin + 0.5) / (nbin * tbinfwidth);
    hist_data_out->InitSet(nbin + 1, xval_lo, xval_up, power);

    delete [] out_real;
    delete [] out_imag;
    delete [] freq;
    delete [] power;
}


void HistData1dOpe::GetResValHd1(const HistData1d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistData1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = hist_data->GetOvalElm(ibin) - func->Eval(xval, par);
    }
    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResValHd1(const HistDataSerr1d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = hist_data->GetOvalElm(ibin) - func->Eval(xval, par);
        oval_res_serr[ibin] = hist_data->GetOvalSerrElm(ibin);
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData1dOpe::GetResValHd1(const HistData1d* const hist_data,
                                 const HistData1d* const hist_func,
                                 HistData1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = hist_data->GetOvalElm(ibin) - hist_func->GetOvalElm(ibin);
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResValHd1(const HistDataSerr1d* const hist_data,
                                 const HistData1d* const hist_func,
                                 HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = hist_data->GetBinCenterX(ibin);
        long ibin_func = hist_func->GetIbin(xval);
        oval_res[ibin] = hist_data->GetOvalElm(ibin) - hist_func->GetOvalElm(ibin_func);
        oval_res_serr[ibin] = hist_data->GetOvalSerrElm(ibin);
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData1dOpe::GetResRatioHd1(const HistData1d* const hist_data,
                                   const MirFunc* const func, const double* const par,
                                   HistData1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = (hist_data->GetOvalElm(ibin) - func->Eval(xval, par)) / func->Eval(xval, par);
    }
    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res);
    delete [] oval_res;
}


void HistData1dOpe::GetResRatioHd1(const HistDataSerr1d* const hist_data,
                                   const MirFunc* const func, const double* const par,
                                   HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        if( func->Eval(xval, par) > DBL_EPSILON){
            oval_res[ibin] = (hist_data->GetOvalElm(ibin) - func->Eval(xval, par)) / func->Eval(xval, par);
            oval_res_serr[ibin] = fabs(hist_data->GetOvalSerrElm(ibin) / func->Eval(xval, par));
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}

void HistData1dOpe::GetResRatioHd1(const HistData1d* const hist_data,
                                   const HistData1d* const hist_func,
                                   HistData1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = (hist_data->GetOvalElm(ibin) - hist_func->GetOvalElm(ibin)) /
            hist_func->GetOvalElm(ibin);
    }
    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res);
    delete [] oval_res;
}



void HistData1dOpe::GetResRatioHd1(const HistDataSerr1d* const hist_data,
                                   const HistData1d* const hist_func,
                                   HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = hist_data->GetBinCenterX(ibin);
        long ibin_func = hist_func->GetIbin(xval);
        if( hist_func->GetOvalElm(ibin_func) > DBL_EPSILON){
            oval_res[ibin] = (hist_data->GetOvalElm(ibin) - hist_func->GetOvalElm(ibin_func)) /
                hist_func->GetOvalElm(ibin_func);
            oval_res_serr[ibin] = fabs(hist_data->GetOvalSerrElm(ibin) / hist_func->GetOvalElm(ibin_func));
        } else {
            oval_res[ibin] = 0.0;
            oval_res_serr[ibin] = 0.0;
        }
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData1dOpe::GetResChiHd1(const HistDataSerr1d* const hist_data,
                                 const MirFunc* const func, const double* const par,
                                 HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval[1];
        xval[0] = hist_data->GetBinCenterX(ibin);
        oval_res[ibin] = ( hist_data->GetOvalElm(ibin) - func->Eval(xval, par) ) / 
            hist_data->GetOvalSerrElm(ibin);
        oval_res_serr[ibin] = 1.0;
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}


void HistData1dOpe::GetResChiHd1(const HistDataSerr1d* const hist_data,
                                 const HistData1d* const hist_func,
                                 HistDataSerr1d* const hist_res_out)
{
    long nbin = hist_data->GetNbinX();
    double* oval_res = new double[nbin];
    double* oval_res_serr = new double[nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval = hist_data->GetBinCenterX(ibin);
        long ibin_func = hist_func->GetIbin(xval);
        oval_res[ibin] = (hist_data->GetOvalElm(ibin) - hist_func->GetOvalElm(ibin_func)) /
            hist_data->GetOvalSerrElm(ibin);
        oval_res_serr[ibin] = 1.0;
    }

    hist_res_out->InitSet(nbin, hist_data->GetXvalLo(), hist_data->GetXvalUp(),
                          oval_res, oval_res_serr);
    delete [] oval_res;
    delete [] oval_res_serr;
}



int HistData1dOpe::IsFormatSame(const HistData1d* const hist_data1,
                                const HistData1d* const hist_data2)
{
    if(hist_data1->GetNbinX() != hist_data2->GetNbinX() ||
       fabs(hist_data1->GetXvalLo() - hist_data2->GetXvalLo()) > DBL_EPSILON ||
       fabs(hist_data1->GetXvalUp() - hist_data2->GetXvalUp()) > DBL_EPSILON ){
        MPrintErr("format of hist_data1 and hist_data2 are diffenret.");
        char msg[kLineSize];
        sprintf(msg, "hist_data1: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)",
                hist_data1->GetNbinX(),
                hist_data1->GetXvalLo(),
                hist_data1->GetXvalUp());
        MPrintErr(msg);
        sprintf(msg, "hist_data2: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)",
                hist_data2->GetNbinX(),
                hist_data2->GetXvalLo(),
                hist_data2->GetXvalUp());
        MPrintErr(msg);
        abort();
    }
    return 1;
}

int HistData1dOpe::IsFormatSame(const HistData1d* const* const hist_data_arr,
                                int nhist)
{
    if(nhist < 2){
        char msg[kLineSize];
        sprintf(msg, "nhist(=%d) < 2\n", nhist);
        MPrintWarn(msg);
        MPrintWarn("skip check");
        return 0;
    }
    for(int ihist = 1; ihist < nhist; ihist++){
        if(hist_data_arr[0]->GetNbinX()  != hist_data_arr[ihist]->GetNbinX()  ||
           fabs(hist_data_arr[0]->GetXvalLo() - hist_data_arr[ihist]->GetXvalLo()) > DBL_EPSILON ||
           fabs(hist_data_arr[0]->GetXvalUp() - hist_data_arr[ihist]->GetXvalUp()) > DBL_EPSILON ){
            char msg[kLineSize];
            sprintf(msg, "format of hist_data_arr[0] and hist_data_arr[%d] are diffenret", ihist);
            MPrintErr(msg);
            sprintf(msg, "hist_data_arr[0]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)",
                    hist_data_arr[0]->GetNbinX(),
                    hist_data_arr[0]->GetXvalLo(),
                    hist_data_arr[0]->GetXvalUp());
            MPrintErr(msg);            
            sprintf(msg, "hist_data_arr[%d]: (GetNbinX(), GetXvalLo(), GetXvalUp()) = (%ld, %e, %e)",
                    ihist,
                    hist_data_arr[ihist]->GetNbinX(),
                    hist_data_arr[ihist]->GetXvalLo(),
                    hist_data_arr[ihist]->GetXvalUp());
            MPrintErr(msg);            
            sprintf(msg, "hist_data_arr[0]->GetXvalLo() - hist_data_arr[%d]->GetXvalLo() = %e\n",
                    ihist,
                    fabs(hist_data_arr[0]->GetXvalLo() - hist_data_arr[ihist]->GetXvalLo()));
            MPrintErr(msg);            
            sprintf(msg, "hist_data_arr[0]->GetXvalUp() - hist_data_arr[%d]->GetXvalUp() = %e\n",
                    ihist,
                    fabs(hist_data_arr[0]->GetXvalUp() - hist_data_arr[ihist]->GetXvalUp()));
            abort();
        }
    }
    return 1;
}


int HistData1dOpe::IsFormatSame(const HistDataSerr1d* const* const hist_data_arr,
                                int nhist)
{
    HistData1d** h1d_arr = new HistData1d* [nhist];
    for(int ihist = 1; ihist < nhist; ihist++){
        h1d_arr[ihist] = new HistData1d;
        h1d_arr[ihist]->Copy(hist_data_arr[ihist]);
    }
    IsFormatSame(h1d_arr, nhist);

    for(int ihist = 1; ihist < nhist; ihist++){
        delete h1d_arr[ihist]; h1d_arr[ihist] = NULL;
    }
    delete [] h1d_arr;
    return 1;
}



// Init & Set by graph2d, only if xval_arr of graph2d is the same as hist_info
HistData1d* const HistData1dOpe::GenHd1dByHistInfoAndGraphData2d(const HistInfo1d* const hist_info,
                                                                 const GraphData2d* const gd2d)
{
    HistData1d* hd1d = NULL;
    if("GraphData2d" == gd2d->GetClassName()){
        hd1d = new HistData1d;
        hd1d->Init(hist_info);
        IsValidForSetByGd2d(hd1d, gd2d);
        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
            hd1d->SetOvalElm(ibin, gd2d->GetOvalElm(ibin));
        }
    } else if ("GraphDataSerr2d" == gd2d->GetClassName()){
        hd1d = new HistDataSerr1d;
        hd1d->Init(hist_info);
        IsValidForSetByGd2d(hd1d, gd2d);
        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
            hd1d->SetOvalElm(ibin, gd2d->GetOvalElm(ibin));
            hd1d->SetOvalSerrElm(ibin, gd2d->GetOvalSerrElm(ibin));
        }
    } else if ("GraphDataTerr2d" == gd2d->GetClassName()){
        hd1d = new HistDataTerr1d;
        hd1d->Init(hist_info);
        IsValidForSetByGd2d(hd1d, gd2d);
        for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
            hd1d->SetOvalElm(ibin, gd2d->GetOvalElm(ibin));
            hd1d->SetOvalTerrPlusElm(ibin, gd2d->GetOvalTerrPlusElm(ibin));
            hd1d->SetOvalTerrMinusElm(ibin, gd2d->GetOvalTerrMinusElm(ibin));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "Bad classname: %s", gd2d->GetClassName().c_str());
        MPrintErr(msg);
        abort();
    }
    return hd1d;
}


int HistData1dOpe::IsValidForSetByGd2d(const HistData1d* const hd1d,
                                       const GraphData2d* const gd2d)
{
    if(hd1d->GetNbinX() != gd2d->GetNdata()){
        MPrintErr("different nbin");
        abort();
    }
    for(long ibin = 0; ibin < hd1d->GetNbinX(); ibin ++){
        if(1 != MirMath::IsSame(hd1d->GetBinCenterX(ibin),
                                 gd2d->GetXvalElm(ibin)) ){
            MPrintErr("different xval");
            abort();
        }
    }
    return 1;
}
