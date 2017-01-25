#include "mir_hist2d_serr.h"

//
// public
//

void HistDataSerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval,
                                     yval_lo, yval_up, nbin_yval);
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin_xval * nbin_yval);
}

void HistDataSerr2d::Init(const HistInfo2d* const hist_info)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(hist_info->GetLoX(),
                                     hist_info->GetUpX(),
                                     hist_info->GetNbinX(),
                                     hist_info->GetLoY(),
                                     hist_info->GetUpY(),
                                     hist_info->GetNbinY());  
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataSerr2d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void HistDataSerr2d::SetOvalSerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerr(val_serr);
}

void HistDataSerr2d::SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);
}

void HistDataSerr2d::FillByMax(double xval, double yval,
                               double oval,
                               double oval_serr)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByMax(ibin, oval, oval_serr);
}

void HistDataSerr2d::FillByMin(double xval, double yval,
                               double oval,
                               double oval_serr)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByMin(ibin, oval, oval_serr);
}

void HistDataSerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


HistDataSerr2d* const HistDataSerr2d::Clone() const
{
    HistDataSerr2d* obj_new = new HistDataSerr2d;
    obj_new->Copy(this);
    return obj_new;
}


void HistDataSerr2d::Load(string file)
{
    NullHistData2d();

    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    long nbin_yval = 0;
    double yval_lo = 0.0;
    double yval_up = 0.0;
    string format = "";
    ReadInfo(file,
             &nbin_xval, &xval_lo, &xval_up,
             &nbin_yval, &yval_lo, &yval_up, &format);
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);

    abort();
    
//    //GraphDataSerr3d* gdata3d = new GraphDataSerr3d;
//    gdata3d->Load(file, format);
//    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
//        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
//        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
//        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
//        SetOvalSerrElm(ibin_x, ibin_y, gdata3d->GetOvalSerrElm(idata) );
//    }
//    delete gdata3d;
}


const DataArraySerr1d* const HistDataSerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double HistDataSerr2d::GetOvalSerrElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    return GetOvalArr()->GetValSerrElm(ibin);
}

double HistDataSerr2d::GetOvalSerrElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    return GetOvalSerrElm(ibin_x, ibin_y);
}

void HistDataSerr2d::GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                    long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_serr_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_serr_arr[ibin] = GetOvalArr()->GetValSerrElm(ibin);
    }
    *oval_serr_arr_ptr = oval_serr_arr;
    *nbin_ptr = nbin;
}

//// calc_mode  : "add", "integral", "amean"
//// error_mode: gauss, poisson, zero
//HistDataSerr1d* const HistDataSerr2d::GenProjectX(long ibin_ylo, long ibin_yup,
//                                                  string calc_mode, string error_mode) const
//{
//    int ret = IsValidIbinY(ibin_ylo) * IsValidIbinY(ibin_yup);
//    if(1 != ret){
//        char msg[kLineSize];
//        sprintf(msg, "bad ibin_ylo(=%ld) or ibin_yup(=%ld)\n",
//                ibin_ylo, ibin_yup);
//        MPrintErrClass(msg);
//        abort();
//    }
//    HistDataSerr1d* h1d = new HistDataSerr1d;
//    h1d->Init(GetNbinX(), GetXvalLo(), GetXvalUp());
//    for(long ibin_xval = 0; ibin_xval < GetNbinX(); ibin_xval++){
//        long nbin_tmp = ibin_yup - ibin_ylo + 1;
//        double* tmp_arr = new double [nbin_tmp];
//        double* tmp_err_arr = new double [nbin_tmp];
//        long ibin_tmp = 0;
//        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
//            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
//            tmp_err_arr[ibin_tmp] = GetOvalSerrElm(ibin_xval, ibin_yval);
//            ibin_tmp ++;
//        }
//        double val_proj;
//        double val_proj_err;
//    
//        GetProject(nbin_tmp,
//                   tmp_arr, tmp_err_arr,
//                   calc_mode, error_mode,
//                   GetBinWidthY(),
//                   &val_proj, &val_proj_err);
//        delete [] tmp_arr;
//        delete [] tmp_err_arr;
//        h1d->SetOvalElm(ibin_xval, val_proj);
//        h1d->SetOvalSerrElm(ibin_xval, val_proj_err);
//    }
//    return h1d;
//}
//
//// calc_mode  : "add", "integral", "amean"
//// error_mode: gauss, poisson, zero
//HistDataSerr1d* const HistDataSerr2d::GenProjectY(long ibin_xlo, long ibin_xup,
//                                                  string calc_mode, string error_mode) const
//{
//    int ret = IsValidIbinX(ibin_xlo) * IsValidIbinX(ibin_xup);
//    if(1 != ret){
//        char msg[kLineSize];
//        sprintf(msg, "bad ibin_xlo(=%ld) or ibin_xup(=%ld)\n",
//                ibin_xlo, ibin_xup);
//        MPrintErrClass(msg);
//        abort();
//    }
//    
//    HistDataSerr1d* h1d = new HistDataSerr1d;
//    h1d->Init(GetNbinY(), GetYvalLo(), GetYvalUp());
//    for(long ibin_yval = 0; ibin_yval < GetNbinY(); ibin_yval++){
//        long nbin_tmp = ibin_xup - ibin_xlo + 1;
//        double* tmp_arr = new double [nbin_tmp];
//        double* tmp_err_arr = new double [nbin_tmp];
//        long ibin_tmp = 0;
//        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
//            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
//            tmp_err_arr[ibin_tmp] = GetOvalSerrElm(ibin_xval, ibin_yval);
//            ibin_tmp ++;
//        }
//        double val_proj;
//        double val_proj_err;
//        GetProject(nbin_tmp,
//                   tmp_arr, tmp_err_arr,
//                   calc_mode, error_mode,
//                   GetBinWidthX(),
//                   &val_proj, &val_proj_err);
//        delete [] tmp_arr;
//        delete [] tmp_err_arr;
//        h1d->SetOvalElm(ibin_yval, val_proj);
//        h1d->SetOvalSerrElm(ibin_yval, val_proj_err);
//    }
//    return h1d;
//}


// output
void HistDataSerr2d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval) const
{
    long nbin = GetNbin();
    if("x,xe,y,ye,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalSerrElm(ibin_x, ibin_y));
        }
     } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}


TH2D* const HistDataSerr2d::GenTH2D(double offset_xval,
                                    double offset_yval,
                                    double offset_oval) const
{
    string name = GetTitle();
    TH2D* th2d = new TH2D(name.c_str(), name.c_str(),
                          GetNbinX(),
                          GetXvalLo() - offset_xval,
                          GetXvalUp() - offset_xval,
                          GetNbinY(),
                          GetYvalLo() - offset_yval,
                          GetYvalUp() - offset_yval);
    for(long ibin = 0; ibin < GetNbin(); ibin++){
        double xval, yval;
        GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval, &yval);
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        long index_th2d = th2d->FindBin(xval - offset_xval, yval - offset_yval);
        th2d->SetBinContent(index_th2d,
                            GetOvalElm(ibin_x, ibin_y) - offset_oval);
        th2d->SetBinError(index_th2d, GetOvalSerrElm(ibin_x, ibin_y));
    }
    return th2d;
}

// poisson error
void HistDataSerr2d::FillRandom(const MirFunc* const func,
                                const MirFuncPar* const func_par,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        double xval = GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
        double yval = GetHi2d()->GetBinCenterYFromIbinY(ibin_y);

        double xval_arr[2];
        xval_arr[0] = xval;
        xval_arr[1] = yval;
        double oval = func->Eval(xval_arr, func_par->GetPar());

        // poisson error
        double oval_rand = trand->PoissonD(oval);
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete trand;
}

// gaussian error
void HistDataSerr2d::FillRandom(const MirFunc* const func,
                                const MirFuncPar* const func_par,
                                const MirFunc* const func_sigma,
                                const MirFuncPar* const func_par_sigma,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        double xval = GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
        double yval = GetHi2d()->GetBinCenterYFromIbinY(ibin_y);
        
        double xval_arr[2];
        xval_arr[0] = xval;
        xval_arr[1] = yval;
        double oval = func->Eval(xval_arr, func_par->GetPar());
        
        // gaussian error
        double sigma = func_sigma->Eval(xval_arr, func_par_sigma->GetPar());
        double oval_rand = trand->Gaus(oval, sigma);
        double oval_err = sigma;
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete trand;
}

// poisson error
void HistDataSerr2d::FillRandom(const HistData2d* const hist_data,
                                int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp(),
         hist_data->GetNbinY(), hist_data->GetYvalLo(), hist_data->GetYvalUp());
    
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        
        // poisson error
        double oval_rand = trand->PoissonD(hist_data->GetOvalElm(ibin_x, ibin_y));
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete trand;
}

