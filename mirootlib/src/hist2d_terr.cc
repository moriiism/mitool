#include "mir_hist2d_terr.h"

//
// public
//

void HistDataTerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)
{
    Null();
    SetInfo(nbin_xval, xval_lo, xval_up,
            nbin_yval, yval_lo, yval_up);
    long nbin = nbin_xval * nbin_yval;
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(nbin);
}


// SetData
void HistDataTerr2d::SetData(long nbin_xval, long nbin_yval, 
                             const double* const oval,
                             const double* const oval_terr_plus,
                             const double* const oval_terr_minus)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    if(GetNbinY() != nbin_yval){
        MPrintErrClass("GetNbinY() != nbin_yval");
        abort();
    }
    GetOvalArrNonConst()->SetValAndTerr(nbin_xval * nbin_yval,
                                        oval, oval_terr_plus,
                                        oval_terr_minus);
}

void HistDataTerr2d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                             long nbin_yval, double yval_lo, double yval_up,
                             const double* const oval,
                             const double* const oval_terr_plus,
                             const double* const oval_terr_minus)
{
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);
    SetData(nbin_xval, nbin_yval,
            oval, oval_terr_plus, oval_terr_minus);
}


void HistDataTerr2d::InitSet(const TH2D* const th2d)
{
    Null();

    long nbin_xval = th2d->GetNbinsX();
    double xval_lo = th2d->GetXaxis()->GetXmin();
    double xval_up = th2d->GetXaxis()->GetXmax();
    long nbin_yval = th2d->GetNbinsY();
    double yval_lo = th2d->GetYaxis()->GetXmin();
    double yval_up = th2d->GetYaxis()->GetXmax();
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);

    long nbin = nbin_xval * nbin_yval;
    double* oval = new double [nbin];
    double* oval_terr_plus = new double [nbin];
    double* oval_terr_minus = new double [nbin];    
    for(long ibiny = 1; ibiny <= th2d->GetNbinsY(); ibiny ++){  
        for(long ibinx = 1; ibinx <= th2d->GetNbinsX(); ibinx ++){
            long ibin_h2d = ibinx - 1 + nbin_xval * (ibiny - 1);
            oval[ibin_h2d]      = th2d->GetBinContent(ibinx, ibiny);
            oval_terr_plus[ibin_h2d] = th2d->GetBinError(ibinx, ibiny);
            oval_terr_minus[ibin_h2d] = -1 * th2d->GetBinError(ibinx, ibiny);
        }
    }
    SetData(nbin_xval, nbin_yval,
            oval, oval_terr_plus, oval_terr_minus);
    delete [] oval;
    delete [] oval_terr_plus;
    delete [] oval_terr_minus;
}

void HistDataTerr2d::SetOvalTerrElm(long ibin_xval, long ibin_yval,
                                    double oval_serr)
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        GetOvalArrNonConst()->SetValTerrElm(ibin, oval_serr);
    } else {
        num_terr_outer_ ++;
    }
}

void HistDataTerr2d::SetOvalTerrElm(long ibin_xval, long ibin_yval,
                                    double oval_terr_plus,
                                    double oval_terr_minus)
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        GetOvalArrNonConst()->SetValTerrPlusElm(ibin, oval_terr_plus);
        GetOvalArrNonConst()->SetValTerrMinusElm(ibin, oval_terr_minus);
    } else {
        num_terr_outer_ ++;
    } 
}


void HistDataTerr2d::FillByMax(double xval, double yval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMax(ibin,
                                        oval,
                                        oval_terr_plus,
                                        oval_terr_minus);
    } else {
        num_terr_outer_ ++;
    } 
}

void HistDataTerr2d::FillByMin(double xval, double yval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMin(ibin,
                                        oval,
                                        oval_terr_plus,
                                        oval_terr_minus);
    } else {
        num_terr_outer_ ++;
    } 
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
    Null();

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

    if("x,y,z,ze+,ze-" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
    GraphDataTerr3d* gdata3d = new GraphDataTerr3d;
    gdata3d->Load(file, format);
    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
        SetOvalTerrElm(ibin_x, ibin_y,
                       gdata3d->GetOvalTerrPlusElm(idata),
                       gdata3d->GetOvalTerrMinusElm(idata));
    }
    delete gdata3d;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


//
// operation
//

void HistDataTerr2d::Min(const HistDataTerr2d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
    DataArrayTerr1d** data_array_arr = new DataArrayTerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArrayTerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Min(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistDataTerr2d::Max(const HistDataTerr2d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
    DataArrayTerr1d** data_array_arr = new DataArrayTerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArrayTerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Max(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}


//
// const functions
//

// get

const DataArrayTerr1d* const HistDataTerr2d::GetOvalArr() const
{
    const DataArray1d* oval_arr = HistData2d::GetOvalArr();    
    return dynamic_cast<const DataArrayTerr1d*>(oval_arr);
}

const double* const HistDataTerr2d::GetOvalTerrPlusArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValTerrPlus();
}

const double* const HistDataTerr2d::GetOvalTerrMinusArrDbl() const
{
    IsOvalNotNull();    
    return GetOvalArr()->GetValTerrMinus();
}

double HistDataTerr2d::GetOvalTerrPlusElm(long ibin_xval, long ibin_yval) const
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    double oval_terr_plus = 0.0;
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        oval_terr_plus = GetOvalArr()->GetValTerrPlusElm(ibin);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xval(=%ld) or ibin_yval(=%ld)\n",
                ibin_xval, ibin_yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_terr_plus;
}

double HistDataTerr2d::GetOvalTerrMinusElm(long ibin_xval, long ibin_yval) const
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    double oval_terr_minus = 0.0;
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        oval_terr_minus = GetOvalArr()->GetValTerrMinusElm(ibin);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xval(=%ld) or ibin_yval(=%ld)\n",
                ibin_xval, ibin_yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_terr_minus;
}


double HistDataTerr2d::GetOvalTerrPlusElmAtXY(double xval, double yval) const
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    double oval_terr_plus = 0.0;
    if(1 == ret){
        long ibin_x = GetIbinXFromX(xval);
        long ibin_y = GetIbinYFromY(yval);
        oval_terr_plus = GetOvalTerrPlusElm(ibin_x, ibin_y);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad xval(=%e) or yval(=%e)\n",
                xval, yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_terr_plus;
}


double HistDataTerr2d::GetOvalTerrMinusElmAtXY(double xval, double yval) const
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    double oval_terr_minus = 0.0;
    if(1 == ret){
        long ibin_x = GetIbinXFromX(xval);
        long ibin_y = GetIbinYFromY(yval);
        oval_terr_minus = GetOvalTerrMinusElm(ibin_x, ibin_y);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad xval(=%e) or yval(=%e)\n",
                xval, yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_terr_minus;
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


//
// output
//

void HistDataTerr2d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_yval,
                               double offset_oval) const
{
    long nbin = GetNbin();
    if("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);
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


GraphDataTerr3d* const HistDataTerr2d::GenGraph3d() const
{
    long nbin = GetNbin();
    double* xval_arr = NULL;
    double* yval_arr = NULL;
    double* xval_serr_arr = NULL;
    double* yval_serr_arr = NULL;
    long nbin_g3d;
    long nbin_g3d_tmp;
    GenXYvalArr(&xval_arr, &yval_arr, &nbin_g3d);
    GenXYvalSerrArr(&xval_serr_arr, &yval_serr_arr, &nbin_g3d_tmp);

    GraphDataTerr3d* g3d = new GraphDataTerr3d;
    g3d->Init();
    g3d->SetXvalAndTerrArrDbl(nbin, xval_arr, xval_serr_arr);
    g3d->SetYvalAndTerrArrDbl(nbin, yval_arr, yval_serr_arr);
    g3d->SetOvalAndTerrArrDbl(nbin, GetOvalArrDbl(),
                              GetOvalTerrPlusArrDbl(),
                              GetOvalTerrMinusArrDbl());
    delete [] xval_arr;
    delete [] yval_arr;
    delete [] xval_serr_arr;
    delete [] yval_serr_arr;
    return g3d;
}


double HistDataTerr2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValAndErrMin() + GetOvalArr()->GetValAndErrMax() ) / 2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

