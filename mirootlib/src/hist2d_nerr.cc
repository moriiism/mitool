#include "mir_hist2d_nerr.h"

//
// public
//

void HistDataNerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)

{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval,
                                     yval_lo, yval_up, nbin_yval);
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(nbin_xval * nbin_yval);
}

void HistDataNerr2d::Init(const HistInfo2d* const hist_info)
{
    NullHistData2d();
    NewHi2d();
    GetHi2dNonConst()->InitSetByNbin(hist_info->GetLoX(),
                                     hist_info->GetUpX(),
                                     hist_info->GetNbinX(),
                                     hist_info->GetLoY(),
                                     hist_info->GetUpY(),
                                     hist_info->GetNbinY());  
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

HistDataNerr2d* const HistDataNerr2d::Clone() const
{
    HistDataNerr2d* obj_new = new HistDataNerr2d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataNerr2d::Load(string file)
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

    if("x,y,z" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }

    abort();

//    GraphData3d* gdata3d = new GraphData3d;
//    gdata3d->Load(file, format);
//    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
//        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
//        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
//        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
//    }
//    delete gdata3d;
//

}

const DataArrayNerr1d* const HistDataNerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void HistDataNerr2d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval) const
{
    long nbin = GetNbin();
    if("x,y,z" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
        }
    } else if ("x,xe,y,ye,z" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, 
                    yval_bin_center - offset_yval, 
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetHi2d()->GetIbinX(ibin);
            long ibin_y = GetHi2d()->GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2., -1 * GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2., -1 * GetBinWidthX()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}


//HistData2d* const HistData2d::GenHd2MaxInBin(long nbinx_new, long nbiny_new) const
//{
//    if(nbinx_new > GetNbinX()){
//        MPrintErrClass("bad nbinx_new");
//        abort();
//    }
//    if(nbinx_new < 1){
//        MPrintErrClass("bad nbinx_new");
//        abort();
//    }
//    if(0 != GetNbinX() % nbinx_new){
//        MPrintErrClass("bad nbinx_new");
//        abort();
//    }
//
//    if(nbiny_new > GetNbinY()){
//        MPrintErrClass("bad nbiny_new");
//        abort();
//    }
//    if(nbiny_new < 1){
//        MPrintErrClass("bad nbiny_new");
//        abort();
//    }
//    if(0 != GetNbinY() % nbiny_new){
//        MPrintErrClass("bad nbiny_new");
//        abort();
//    }
//    
//    HistData2d* h2d_new = new HistData2d;
//    h2d_new->Init(nbinx_new, GetXvalLo(), GetXvalUp(),
//                  nbiny_new, GetYvalLo(), GetYvalUp());
//    for(long ibin = 0; ibin < GetNbin(); ibin ++){
//        double xval = GetBinCenterXFromIbin(ibin);
//        double yval = GetBinCenterYFromIbin(ibin);
//        long ibin_x = GetIbinX(ibin);
//        long ibin_y = GetIbinY(ibin);
//        h2d_new->FillByMax(xval, yval, GetOvalElm(ibin_x, ibin_y) );
//    }
//    return h2d_new;
//}
//
//
//GraphData3d* const HistData2d::GenGraph3d() const
//{
//    long nbin = nbin_xval_ * nbin_yval_;
//    double* xval_arr = NULL;
//    double* yval_arr = NULL;
//    long nbin_g3d;
//    GenXYvalArr(&xval_arr, &yval_arr, &nbin_g3d);
//    
//    GraphData3d* g3d = new GraphData3d;
//    g3d->Init();
//    g3d->SetXvalArrDbl(nbin_g3d, xval_arr);
//    g3d->SetYvalArrDbl(nbin_g3d, yval_arr);
//    g3d->SetOvalArrDbl(nbin, GetOvalArrDbl());
//    delete [] xval_arr;
//    delete [] yval_arr;
//    return g3d;
//}


TH2D* const HistDataNerr2d::GenTH2D(double offset_xval,
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
    }
    
    return th2d;
}

////
//// generate HistData2d adding margin region in x and y directions
////
//
//HistData2d* const HistData2d::GenHd2AddMargin(double margin_xval, double margin_yval) const
//{
//    long nbin_xval_margin = (long) ceil(margin_xval / GetBinWidthX());
//    long nbin_yval_margin = (long) ceil(margin_yval / GetBinWidthY());
//  
//    double xval_lo_new = GetXvalLo() - nbin_xval_margin * GetBinWidthX();
//    double xval_up_new = GetXvalUp() + nbin_xval_margin * GetBinWidthX();
//    double yval_lo_new = GetYvalLo() - nbin_yval_margin * GetBinWidthY();
//    double yval_up_new = GetYvalUp() + nbin_yval_margin * GetBinWidthY();
//    long nbin_xval_new = GetNbinX() + 2 * nbin_xval_margin;
//    long nbin_yval_new = GetNbinY() + 2 * nbin_yval_margin;
//
//    HistData2d* hd2_new = new HistData2d;
//    hd2_new->Init(nbin_xval_new, xval_lo_new, xval_up_new,
//                  nbin_yval_new, yval_lo_new, yval_up_new);
//    hd2_new->SetZero();
//
//    for(long ibin = 0; ibin < GetNbin(); ibin++){
//        long ibin_x = GetIbinX(ibin);
//        long ibin_y = GetIbinY(ibin);
//        double xval = GetBinCenterXFromIbinX(ibin_x);
//        double yval = GetBinCenterYFromIbinY(ibin_y);
//
//        long ibin_x_new = hd2_new->GetIbinXFromX(xval);
//        long ibin_y_new = hd2_new->GetIbinYFromY(yval);
//        hd2_new->SetOvalElm(ibin_x_new,
//                            ibin_y_new,
//                            GetOvalElm(ibin_x, ibin_y));
//    }
//    return hd2_new;
//}

void HistDataNerr2d::FillRandom(const MirFunc* const func,
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

        double oval_rand = trand->PoissonD(oval);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
    }
    delete trand;
}

void HistDataNerr2d::FillRandom(const HistData2d* const hist_data,
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
        SetOvalElm(ibin_x, ibin_y, oval_rand);
    }
    delete trand;
}

