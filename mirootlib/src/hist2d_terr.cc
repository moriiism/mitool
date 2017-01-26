#include "mir_hist2d_terr.h"

//
// public
//

void HistDataTerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval,
                                     yval_lo, yval_up, nbin_yval);
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(nbin_xval * nbin_yval);
}

void HistDataTerr2d::Init(const HistInfo2d* const hist_info)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(hist_info->GetLoX(),
                                     hist_info->GetUpX(),
                                     hist_info->GetNbinX(),
                                     hist_info->GetLoY(),
                                     hist_info->GetUpY(),
                                     hist_info->GetNbinY());  
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataTerr2d::SetOvalTerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void HistDataTerr2d::SetOvalTerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_serr);
}

void HistDataTerr2d::SetOvalTerrArr(long ndata,
                                    const double* const val_terr_plus,
                                    const double* const val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void HistDataTerr2d::SetOvalTerrArr(vector<double> val_terr_plus,
                                    vector<double> val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_terr_plus, val_terr_minus);
}

void HistDataTerr2d::SetOvalTerrElm(long ibin_xval, long ibin_yval,
                                    double oval_serr)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValTerrElm(ibin, oval_serr);
}

void HistDataTerr2d::SetOvalTerrElm(long ibin_xval, long ibin_yval,
                                    double oval_terr_plus,
                                    double oval_terr_minus)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValTerrPlusElm(ibin, oval_terr_plus);
    GetOvalArrNonConst()->SetValTerrMinusElm(ibin, oval_terr_minus);
}


void HistDataTerr2d::FillByLarger(double xval, double yval,
                                  double oval,
                                  double oval_terr_plus,
                                  double oval_terr_minus)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByLarger(ibin,
                                       oval,
                                       oval_terr_plus,
                                       oval_terr_minus);
}

void HistDataTerr2d::FillBySmaller(double xval, double yval,
                                   double oval,
                                   double oval_terr_plus,
                                   double oval_terr_minus)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillBySmaller(ibin,
                                        oval,
                                        oval_terr_plus,
                                        oval_terr_minus);
}

void HistDataTerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


HistDataTerr2d* const HistDataTerr2d::Clone() const
{
    HistDataTerr2d* obj_new = new HistDataTerr2d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataTerr2d::Load(string file)
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
    
    if("x,y,z,ze+,ze-" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
//    GraphDataTerr3d* gdata3d = new GraphDataTerr3d;
//    gdata3d->Load(file, format);
//    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
//        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
//        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
//        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
//        SetOvalTerrElm(ibin_x, ibin_y,
//                       gdata3d->GetOvalTerrPlusElm(idata),
//                       gdata3d->GetOvalTerrMinusElm(idata));
//    }
//    delete gdata3d;

}

const DataArrayTerr1d* const HistDataTerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetOvalArrNonConst());
}

double HistDataTerr2d::GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    return GetOvalArr()->GetValTerrPlusElm(ibin);
}

double HistDataTerr2d::GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    return GetOvalArr()->GetValTerrMinusElm(ibin);
}


double HistDataTerr2d::GetOvalTerrPlusElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    return GetOvalTerrPlusElm(ibin_x, ibin_y);
}

double HistDataTerr2d::GetOvalTerrMinusElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    return GetOvalTerrMinusElm(ibin_x, ibin_y);

}

void HistDataTerr2d::GenOvalTerrPlusArr(double** const oval_terr_plus_arr_ptr,
                                        long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_terr_plus_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_terr_plus_arr[ibin] = GetOvalArr()->GetValTerrPlusElm(ibin);
    }
    *oval_terr_plus_arr_ptr = oval_terr_plus_arr;
    *nbin_ptr = nbin;
}

void HistDataTerr2d::GenOvalTerrMinusArr(double** const oval_terr_minus_arr_ptr,
                                         long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_terr_minus_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_terr_minus_arr[ibin] = GetOvalArr()->GetValTerrMinusElm(ibin);
    }
    *oval_terr_minus_arr_ptr = oval_terr_minus_arr;
    *nbin_ptr = nbin;
}

void HistDataTerr2d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval) const
{
    long nbin = GetNbin();
    if("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp,
                    "%.15e  %.15e  "
                    "%.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval,
                    GetOvalTerrPlusElm(ibin_x, ibin_y),
                    GetOvalTerrMinusElm(ibin_x, ibin_y));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}


//GraphDataTerr3d* const HistDataTerr2d::GenGraph3d() const
//{
//    long nbin = GetNbin();
//    double* xval_arr = NULL;
//    double* yval_arr = NULL;
//    double* xval_serr_arr = NULL;
//    double* yval_serr_arr = NULL;
//    long nbin_g3d;
//    long nbin_g3d_tmp;
//    GenXYvalArr(&xval_arr, &yval_arr, &nbin_g3d);
//    GenXYvalSerrArr(&xval_serr_arr, &yval_serr_arr, &nbin_g3d_tmp);
//
//    GraphDataTerr3d* g3d = new GraphDataTerr3d;
//    g3d->Init();
//    g3d->SetXvalAndTerrArrDbl(nbin, xval_arr, xval_serr_arr);
//    g3d->SetYvalAndTerrArrDbl(nbin, yval_arr, yval_serr_arr);
//    g3d->SetOvalAndTerrArrDbl(nbin, GetOvalArrDbl(),
//                              GetOvalTerrPlusArrDbl(),
//                              GetOvalTerrMinusArrDbl());
//    delete [] xval_arr;
//    delete [] yval_arr;
//    delete [] xval_serr_arr;
//    delete [] yval_serr_arr;
//    return g3d;
//}


