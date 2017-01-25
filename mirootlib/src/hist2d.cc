#include "mir_hist2d.h"

//
// public
//

void HistData2d::SetOvalArr(const DataArray1d* const oval_arr)
{
    GetOvalArrNonConst()->Copy(oval_arr);
}

void HistData2d::SetOvalArr(long ndata, const double* const val)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetVal(ndata, val);
}

void HistData2d::SetOvalArr(vector<double> val)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetVal(val);
}

void HistData2d::SetOvalElm(long ibin_xval, long ibin_yval, double oval)
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    GetOvalArrNonConst()->SetValElm(ibin, oval);
}

void HistData2d::Fill(double xval, double yval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->Fill(ibin);
}

void HistData2d::Fill(double xval, double yval, double weight)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->Fill(ibin, weight);
}

void HistData2d::FillByMax(double xval, double yval, double oval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByMax(ibin, oval);
}

void HistData2d::FillByMin(double xval, double yval, double oval)
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin = GetHi2d()->GetIbinFromXY(xval, yval);
    GetOvalArrNonConst()->FillByMin(ibin, oval);
}

void HistData2d::SetConst(double constant)
{
    IsOvalArrNotNull();    
    GetOvalArrNonConst()->SetConst(constant);
}

void HistData2d::SetOneAtIntervalXY(const Interval* const interval_x,
                                    const Interval* const interval_y)
{
    IsOvalArrNotNull();    
    if(1 != interval_x->IsOrdered()){
        MPrintErrClass("bad interval_x.");
        abort();
    }
    if(1 != interval_y->IsOrdered()){
        MPrintErrClass("bad interval_y.");
        abort();
    }
    Interval* interval_x_hist = new Interval;
    interval_x_hist->InitSet(GetXvalLo(), GetXvalUp());
    Interval* interval_x_and = new Interval;
    interval_x_and->And(interval_x, interval_x_hist);

    Interval* interval_y_hist = new Interval;
    interval_y_hist->InitSet(GetYvalLo(), GetYvalUp());
    Interval* interval_y_and = new Interval;
    interval_y_and->And(interval_y, interval_y_hist);

    GetOvalArrNonConst()->SetConst(0.0);
    for(long iterm_x = 0; iterm_x < interval_x_and->GetNterm(); iterm_x++){
        for(long iterm_y = 0; iterm_y < interval_y_and->GetNterm(); iterm_y++){
            double xlo = interval_x_and->GetTstartElm(iterm_x);
            double xup = interval_x_and->GetTstopElm(iterm_x);
            double ylo = interval_y_and->GetTstartElm(iterm_y);
            double yup = interval_y_and->GetTstopElm(iterm_y);

            printf("GetIbinX(xlo) = %ld\n", GetHi2d()->GetIbinXFromX(xlo));
            printf("GetIbinX(xup) = %ld\n", GetHi2d()->GetIbinXFromX(xup));
            printf("GetIbinY(ylo) = %ld\n", GetHi2d()->GetIbinYFromY(ylo));
            printf("GetIbinY(yup) = %ld\n", GetHi2d()->GetIbinYFromY(yup));

            long ibin_x_lo = (long) MirMath::GetMax((double) GetHi2d()->GetIbinXFromX(xlo), 0.0);
            long ibin_x_up = (long) MirMath::GetMin((double) GetHi2d()->GetIbinXFromX(xup),
                                                    (double) (GetNbinX() - 1) );
            long ibin_y_lo = (long) MirMath::GetMax((double) GetHi2d()->GetIbinYFromY(ylo), 0.0);
            long ibin_y_up = (long) MirMath::GetMin((double) GetHi2d()->GetIbinYFromY(yup),
                                                    (double) (GetNbinY() - 1) );
            
            for(long ibin_x = ibin_x_lo; ibin_x <= ibin_x_up; ibin_x ++){
                for(long ibin_y = ibin_y_lo; ibin_y <= ibin_y_up; ibin_y ++){
                    SetOvalElm(ibin_x, ibin_y, 1);
                }
            }
        }
    }
    
    delete interval_x_hist;
    delete interval_x_and;
    delete interval_y_hist;
    delete interval_y_and;
}


// Set by Func
void HistData2d::SetByFunc(const MirFunc* const func, const double* const par)
{
    for(int ibinx = 0; ibinx < GetNbinX(); ibinx ++){
        for(int ibiny = 0; ibiny < GetNbinY(); ibiny ++){
            double xval = GetHi2d()->GetBinCenterXFromIbinX(ibinx);
            double yval = GetHi2d()->GetBinCenterYFromIbinY(ibiny);
            double xval_tmp[2];
            xval_tmp[0] = xval;
            xval_tmp[1] = yval;
            double oval = func->Eval(xval_tmp, par);
            SetOvalElm(ibinx, ibiny, oval);
        }
    }
}

void HistData2d::Copy(const HistData2d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetHi2d());
    SetOvalArr(org->GetOvalArr());
}


double HistData2d::GetOvalElm(long ibin_xval, long ibin_yval) const
{
    IsOvalArrNotNull();
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = GetHi2d()->GetIbin(ibin_xval, ibin_yval);
    double oval = GetOvalArr()->GetValElm(ibin);
    return oval;
}


double HistData2d::GetOvalElmAtXY(double xval, double yval) const
{
    IsOvalArrNotNull();
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_x = GetHi2d()->GetIbinXFromX(xval);
    long ibin_y = GetHi2d()->GetIbinYFromY(yval);
    double oval = GetOvalElm(ibin_x, ibin_y);
    return oval;
}

// stat
double HistData2d::GetXvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double xval = GetHi2d()->GetBinCenterXFromIbin(ibin);
    return xval;
}
    
double HistData2d::GetXvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double xval = GetHi2d()->GetBinCenterXFromIbin(ibin);
    return xval;
}


double HistData2d::GetYvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double yval = GetHi2d()->GetBinCenterYFromIbin(ibin);
    return yval;
}
    
double HistData2d::GetYvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double yval = GetHi2d()->GetBinCenterYFromIbin(ibin);
    return yval;
}

// gen xval_arr, yval_arr, oval_arr
void HistData2d::GenXYvalArr(double** const xval_arr_ptr,
                             double** const yval_arr_ptr,
                             long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* xval_arr = new double [nbin];
    double* yval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        double xval, yval;
        GetHi2d()->GetBinCenterXYFromIbin(ibin, &xval, &yval);
        xval_arr[ibin] = xval;
        yval_arr[ibin] = yval;
    }
    *xval_arr_ptr = xval_arr;
    *yval_arr_ptr = yval_arr;
    *nbin_ptr = nbin;
}

void HistData2d::GenXYvalSerrArr(double** const xval_serr_arr_ptr,
                                 double** const yval_serr_arr_ptr,
                                 long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* xval_serr_arr = new double [nbin];
    double* yval_serr_arr = new double [nbin];
    double xval_serr = GetBinWidthX() / 2.0;
    double yval_serr = GetBinWidthY() / 2.0;
    for(long ibin = 0; ibin < nbin; ibin++){
        xval_serr_arr[ibin] = xval_serr;
        yval_serr_arr[ibin] = yval_serr;
    }
    *xval_serr_arr_ptr = xval_serr_arr;
    *yval_serr_arr_ptr = yval_serr_arr;
    *nbin_ptr = nbin;
}


void HistData2d::GenOvalArr(double** const oval_arr_ptr,
                            long* const nbin_ptr) const
{
    long nbin = GetNbin();
    double* oval_arr = new double [nbin];
    for(long ibin = 0; ibin < nbin; ibin++){
        oval_arr[ibin] = GetOvalArr()->GetValElm(ibin);
    }
    *oval_arr_ptr = oval_arr;
    *nbin_ptr = nbin;
}


//
//// calc_mode : "add", "integral", "amean", "min", "max"
//HistData1d* const HistData2d::GenProjectX(long ibin_ylo, long ibin_yup,
//                                          string calc_mode) const
//{
//    IsValidIbinY(ibin_ylo);
//    IsValidIbinY(ibin_yup);
//    HistData1d* h1d = new HistData1d;
//    h1d->Init(nbin_xval_, xval_lo_, xval_up_);
//    for(long ibin_xval = 0; ibin_xval < nbin_xval_; ibin_xval++){
//        long nbin_tmp = ibin_yup - ibin_ylo + 1;
//        double* tmp_arr = new double [nbin_tmp];
//        long ibin_tmp = 0;
//        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
//            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
//            ibin_tmp ++;
//        }
//        double val_proj = 0.0;
//        GetProject(nbin_tmp, tmp_arr,
//                   calc_mode, GetBinWidthY(),
//                   &val_proj);
//        delete [] tmp_arr;
//        h1d->SetOvalElm(ibin_xval, val_proj);
//    }
//    return h1d;
//}
//
//// calc_mode : "add", "integral", "amean", "min", "max"
//HistData1d* const HistData2d::GenProjectY(long ibin_xlo, long ibin_xup,
//                                          string calc_mode) const
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
//    HistData1d* h1d = new HistData1d;
//    h1d->Init(nbin_yval_, yval_lo_, yval_up_);
//    for(long ibin_yval = 0; ibin_yval < nbin_yval_; ibin_yval++){
//        long nbin_tmp = ibin_xup - ibin_xlo + 1;
//        double* tmp_arr = new double [nbin_tmp];
//        long ibin_tmp = 0;
//        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
//            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
//            ibin_tmp ++;
//        }
//        double val_proj = 0.0;
//        GetProject(nbin_tmp, tmp_arr,
//                   calc_mode, GetBinWidthX(),
//                   &val_proj);
//        delete [] tmp_arr;
//        h1d->SetOvalElm(ibin_yval, val_proj);
//    }
//    return h1d;
//}
//

double HistData2d::GetOvalIntPolLin(double xval, double yval) const
{
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    double ans = 0.0;
    long index_xval = GetHi2d()->GetIbinX_WithHalfBinShifted(xval);
    long index_yval = GetHi2d()->GetIbinY_WithHalfBinShifted(yval);
    
    if (-1 < index_xval && index_xval < GetNbinX() - 1 &&
        -1 < index_yval && index_yval < GetNbinY() - 1   ){
        long index_xval0 = index_xval;
        long index_xval1 = index_xval0 + 1;
        long index_yval0 = index_yval;
        long index_yval1 = index_yval0 + 1;

        long index0 = index_xval0 + index_yval0 * GetNbinX();
        long index1 = index0 + 1;
        long index2 = index0 + GetNbinX() + 1;
        long index3 = index0 + GetNbinX();
        
        ans = MirMath::IntPolLin(xval, yval,
                                 GetHi2d()->GetBinCenterXFromIbinX(index_xval0),
                                 GetHi2d()->GetBinCenterXFromIbinX(index_xval1),
                                 GetHi2d()->GetBinCenterYFromIbinY(index_yval0),
                                 GetHi2d()->GetBinCenterYFromIbinY(index_yval1),
                                 GetOvalArr()->GetValElm(index0),
                                 GetOvalArr()->GetValElm(index1),
                                 GetOvalArr()->GetValElm(index2),
                                 GetOvalArr()->GetValElm(index3));
    } else {
        if(0 < g_flag_verbose){
            MPrintWarnClass("bad xval and/or yval, then just return 0.0");
        }
        ans = 0.0;
    }
    return ans;
}

//
// output
//

void HistData2d::Save(string outfile, string format,
                      double offset_xval,
                      double offset_yval,
                      double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp, format);
    PrintData(fp, format, offset_xval, offset_yval, offset_oval);
    fclose(fp);
}

void HistData2d::SaveData(string outfile, string format,
                          double offset_xval,
                          double offset_yval,
                          double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_yval, offset_oval);
    fclose(fp);
}

void HistData2d::PrintInfo(FILE* fp, string format) const
{
    fprintf(fp, "#\n");
    fprintf(fp, "# nbin_xval_  = %ld\n", GetNbinX());
    fprintf(fp, "# xval_lo_    = %e\n", GetXvalLo());
    fprintf(fp, "# xval_up_    = %e\n", GetXvalUp());
    fprintf(fp, "# nbin_yval_  = %ld\n", GetNbinY());
    fprintf(fp, "# yval_lo_    = %e\n", GetYvalLo());
    fprintf(fp, "# yval_up_    = %e\n", GetYvalUp());
    fprintf(fp, "# format      = %s\n", format.c_str());
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
}

void HistData2d::PrintData(FILE* fp, string format,
                           double offset_xval,
                           double offset_yval,
                           double offset_oval) const
{
    long nbin = GetNbinX() * GetNbinY();
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

void HistData2d::SaveRoot(string outfile,
                          double offset_xval,
                          double offset_yval,
                          double offset_oval) const
{
    TFile* tfile = new TFile(outfile.c_str(), "RECREATE");
    TH2D* th2d = GenTH2D(offset_xval, offset_yval, offset_oval);
    th2d->Write();
    delete th2d;
    delete tfile;
}

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
//


void HistData2d::MkTH2Fig(string outfig,
                          MirRootTool* const root_tool,
                          double offset_xval,
                          double offset_yval,
                          double offset_oval,                          
                          string title_xaxis,
                          string title_yaxis,
                          string title_oaxis,
                          string style) const
{
    TH2D* th2d = GenTH2D(offset_xval, offset_yval, offset_oval);
    th2d->SetTitle(GetTitle().c_str());

    th2d->Draw("colz");
    gPad->Update();
    TPaletteAxis* palette = (TPaletteAxis*) th2d->GetListOfFunctions()->FindObject("palette");
    palette->SetX1NDC(0.86);
    palette->SetX2NDC(0.89);

    th2d->GetXaxis()->SetTitleSize(0.05);
    th2d->GetYaxis()->SetTitleSize(0.05);
    th2d->GetXaxis()->SetLabelSize(0.05);
    th2d->GetYaxis()->SetLabelSize(0.05);
    
    //  char offset_str[100];
    //    sprintf(offset_str, "offset:(%e, %e)", offset_xval, offset_yval);
    //TPaveLabel* label = new TPaveLabel(0.1, 0.1, 0.9, 0.9, offset_str, "NDC");
    //label->Draw();
    
    root_tool->GetTCanvas()->Print(outfig.c_str());

    delete th2d;
//  delete label;
}

void HistData2d::MkTH2FigZrange(string outfig,
                                MirRootTool* const root_tool,
                                double zrange_lo, double zrange_up,
                                double offset_xval,
                                double offset_yval,
                                double offset_oval,
                                string title_xaxis,
                                string title_yaxis,
                                string title_oaxis) const
{
    TH2D* th2d = GenTH2D(offset_xval, offset_yval, offset_oval);
    th2d->SetAxisRange(zrange_lo, zrange_up, "Z");

    th2d->Draw("colz");
    gPad->Update();
    TPaletteAxis* palette = (TPaletteAxis*) th2d->GetListOfFunctions()->FindObject("palette");
    palette->SetX1NDC(0.86);
    palette->SetX2NDC(0.89);
    
    th2d->GetXaxis()->SetTitleSize(0.05);
    th2d->GetYaxis()->SetTitleSize(0.05);
    th2d->GetXaxis()->SetLabelSize(0.05);
    th2d->GetYaxis()->SetLabelSize(0.05);
    
    root_tool->GetTCanvas()->Print(outfig.c_str());
    

    delete th2d;
}

GraphDataNerr2d* const HistData2d::GenRandomEvt(int rand_seed) const
{
    TRandom3* trand = new TRandom3(rand_seed);
    vector<double> xval_vec;
    vector<double> yval_vec;

    double tbinfwidth_x = GetBinWidthX();
    double tbinfwidth_y = GetBinWidthY();
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetHi2d()->GetIbinX(ibin);
        long ibin_y = GetHi2d()->GetIbinY(ibin);
        double bin_center_x = GetHi2d()->GetBinCenterXFromIbinX(ibin_x);
        double bin_center_y = GetHi2d()->GetBinCenterYFromIbinY(ibin_y);
        
        double bin_lo_x = bin_center_x - 0.5 * tbinfwidth_x;
        double bin_lo_y = bin_center_y - 0.5 * tbinfwidth_y;
        double count_wpe = trand->Poisson(GetOvalElm(ibin_x, ibin_y));
        
        for(long ievt = 0; ievt < count_wpe; ievt ++){
            double xval_evt = bin_lo_x + trand->Uniform() * tbinfwidth_x;
            double yval_evt = bin_lo_y + trand->Uniform() * tbinfwidth_y;
            xval_vec.push_back(xval_evt);
            yval_vec.push_back(yval_evt);
        }
    }

    GraphDataNerr2d* gdata2d = new GraphDataNerr2d;
    gdata2d->Init(xval_vec.size());
    gdata2d->SetXvalArr(xval_vec);
    gdata2d->SetOvalArr(yval_vec);
    delete trand;
    return gdata2d;
}


double HistData2d::GetOffsetXFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetXvalLo();
    } else if ("ed" == offset_tag){
        offset = GetXvalUp();
    } else if ("md" == offset_tag){
        offset = ( GetXvalLo() + GetXvalUp() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


double HistData2d::GetOffsetYFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetYvalLo();
    } else if ("ed" == offset_tag){
        offset = GetYvalUp();
    } else if ("md" == offset_tag){
        offset = ( GetYvalLo() + GetYvalUp() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;        
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


double HistData2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValMin() + GetOvalArr()->GetValMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

//
// static
//

void HistData2d::ReadInfo(string file,
                          long* nbin_xval_ptr,
                          double* xval_lo_ptr,
                          double* xval_up_ptr,
                          long* nbin_yval_ptr,
                          double* yval_lo_ptr,
                          double* yval_up_ptr,
                          string* format_ptr)
{
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    long nbin_yval = 0;
    double yval_lo = 0.0;
    double yval_up = 0.0;
    string format = "";
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
        if(4 != ncolumn){
            continue;
        }
        if("nbin_xval_" == split_arr[1]){
            nbin_xval = atoi(split_arr[3].c_str());
        }
        if("xval_lo_" == split_arr[1]){
            xval_lo = atof(split_arr[3].c_str());
        }
        if("xval_up_" == split_arr[1]){
            xval_up = atof(split_arr[3].c_str());
        }

        if("nbin_yval_" == split_arr[1]){
            nbin_yval = atoi(split_arr[3].c_str());
        }
        if("yval_lo_" == split_arr[1]){
            yval_lo = atof(split_arr[3].c_str());
        }
        if("yval_up_" == split_arr[1]){
            yval_up = atof(split_arr[3].c_str());
        }
        
        if("format" == split_arr[1]){
            format = split_arr[3];
        }        
        
        delete [] split_arr;
    }
    MiIolib::DelReadFile(line_arr);

    *nbin_xval_ptr = nbin_xval;
    *xval_lo_ptr = xval_lo;
    *xval_up_ptr = xval_up;
    *nbin_yval_ptr = nbin_yval;
    *yval_lo_ptr = yval_lo;
    *yval_up_ptr = yval_up;    
    *format_ptr = format;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}



//
// protected
//

void HistData2d::NullHistData2d()
{
    if(NULL != hi2d_) {delete hi2d_; hi2d_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
}

void HistData2d::NewOvalArrAsDataArrayNerr1d()
{
    oval_arr_ = new DataArrayNerr1d;
}

void HistData2d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void HistData2d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

void HistData2d::NewHi2d()
{
    hi2d_ = new HistInfo2d;
}

void HistData2d::IsHi2dNotNull() const
{
    if(NULL == GetHi2d()){
        MPrintErrClass("bad GetHi2d() (=NULL)");
        abort();
    }
}

void HistData2d::IsOvalArrNotNull() const
{
    if(NULL == GetOvalArr()){
        MPrintErrClass("bad GetOvalArr() (=NULL)");
        abort();
    }

}

void HistData2d::IsValidIbinX(long ibin_xval) const
{
    GetHi2d()->IsValidIbinX(ibin_xval);
}

void HistData2d::IsValidIbinY(long ibin_yval) const
{
    GetHi2d()->IsValidIbinY(ibin_yval);
}

void HistData2d::IsValidRangeX(double xval) const
{
    GetHi2d()->IsValidRangeX(xval);
}

void HistData2d::IsValidRangeY(double yval) const
{
    GetHi2d()->IsValidRangeY(yval);
}

