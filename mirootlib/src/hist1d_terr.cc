#include "mir_hist1d_terr.h"

//
// public
//

void HistDataTerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    Null();
    SetInfo(nbin_xval, xval_lo, xval_up);
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

// SetData
void HistDataTerr1d::SetData(long nbin_xval,
                             const double* const oval,
                             const double* const oval_terr_plus,
                             const double* const oval_terr_minus)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    GetOvalArrNonConst()->SetValAndTerr(nbin_xval,
                                        oval,
                                        oval_terr_plus,
                                        oval_terr_minus);
}

// InitSet
void HistDataTerr1d::InitSet(long nbin_xval,
                             double xval_lo,
                             double xval_up,
                             const double* const oval,
                             const double* const oval_terr_plus,
                             const double* const oval_terr_minus)
{
    Init(nbin_xval, xval_lo, xval_up);
    SetData(nbin_xval, oval, oval_terr_plus, oval_terr_minus);
}

void HistDataTerr1d::InitSet(const TH1D* const th1d)
{
    Null();
    
    long nbin_xval = th1d->GetNbinsX();
    double xval_lo = th1d->GetXaxis()->GetXmin();
    double xval_up = th1d->GetXaxis()->GetXmax();
    Init(nbin_xval, xval_lo, xval_up);

    double* oval            = new double [nbin_xval];
    double* oval_terr_plus  = new double [nbin_xval];
    double* oval_terr_minus = new double [nbin_xval];    
    for(long ibin = 0; ibin < nbin_xval; ibin ++){
        oval[ibin]      = th1d->GetBinContent(ibin + 1);
        oval_terr_plus[ibin] = th1d->GetBinError(ibin + 1);
        oval_terr_minus[ibin] = -1 * th1d->GetBinError(ibin + 1);
    }
    SetData(nbin_xval, oval, oval_terr_plus, oval_terr_minus);
    delete [] oval;
    delete [] oval_terr_plus;
    delete [] oval_terr_minus;
}

void HistDataTerr1d::SetOvalTerrPlusElm(long ibin,
                                        double oval_terr_plus)
{
    IsOvalNotNull();    
    GetOvalArrNonConst()->SetValTerrPlusElm(ibin, oval_terr_plus);
}

void HistDataTerr1d::SetOvalTerrMinusElm(long ibin,
                                         double oval_terr_minus)
{
    IsOvalNotNull();        
    GetOvalArrNonConst()->SetValTerrMinusElm(ibin, oval_terr_minus);
}


void HistDataTerr1d::FillByMax(double xval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    IsOvalNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMax(ibin,
                                    oval,
                                    oval_terr_plus,
                                    oval_terr_minus);
}

void HistDataTerr1d::FillByMin(double xval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    IsOvalNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMin(ibin,
                                    oval,
                                    oval_terr_plus,
                                    oval_terr_minus);
}

void HistDataTerr1d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


HistDataTerr1d* const HistDataTerr1d::Clone() const
{
    HistDataTerr1d* obj_new = new HistDataTerr1d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataTerr1d::Load(string file)
{
    Null();
    
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);
    Init(nbin_xval, xval_lo, xval_up);

    if("x,y,ye+,ye-" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
    GraphDataTerr2d* gdata2d = new GraphDataTerr2d;
    gdata2d->Load(file, format);
    for(long idata = 0; idata < gdata2d->GetNdata(); idata++){
        long ibin = GetIbin(gdata2d->GetXvalElm(idata));
        SetOvalElm(ibin, gdata2d->GetOvalElm(idata) );
        SetOvalTerrPlusElm(ibin, gdata2d->GetOvalTerrPlusElm(idata) );
        SetOvalTerrMinusElm(ibin, gdata2d->GetOvalTerrMinusElm(idata) );        
    }
    delete gdata2d;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


//
// const functions
//

// get
const DataArrayTerr1d* const HistDataTerr1d::GetOvalArr() const
{
    const DataArray1d* oval_arr = HistData1d::GetOvalArr();
    return dynamic_cast<const DataArrayTerr1d*>(oval_arr);
}

const double* const HistDataTerr1d::GetOvalTerrPlusArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValTerrPlus();
}

const double* const HistDataTerr1d::GetOvalTerrMinusArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValTerrMinus();
}


double HistDataTerr1d::GetOvalTerrPlusElm(long ibin) const
{
    IsOvalNotNull();    
    return GetOvalArr()->GetValTerrPlusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrMinusElm(long ibin) const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValTerrMinusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrPlusElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalTerrPlusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrMinusElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalTerrMinusElm(ibin);
}

void HistDataTerr1d::GenOvalTerrArr(double** const oval_terr_plus_arr_ptr,
                                    double** const oval_terr_minus_arr_ptr,
                                    long* const nbin_ptr) const
{
    long nbin_xval = GetNbinX();
    double* oval_terr_plus_arr = new double [nbin_xval];
    double* oval_terr_minus_arr = new double [nbin_xval];
    for(long ibin = 0; ibin < nbin_xval; ibin++){
        oval_terr_plus_arr[ibin]  = GetOvalArr()->GetValTerrPlusElm(ibin);
        oval_terr_minus_arr[ibin] = GetOvalArr()->GetValTerrMinusElm(ibin);
    }
    *oval_terr_plus_arr_ptr  = oval_terr_plus_arr;
    *oval_terr_minus_arr_ptr = oval_terr_minus_arr;
    *nbin_ptr = nbin_xval;
}

//
// output
//

void HistDataTerr1d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_oval) const
{
    long nbin_xval = GetNbinX();
    if("x,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e\n",
                        GetBinCenterX(ibin) - offset_xval,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe+,xe-,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetBinWidth()/2., -1 * GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenterX(ibin) - offset_xval,
                        GetBinWidth()/2., -1 * GetBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetBinWidth()/2., -1 * GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}

HistDataTerr1d* const HistDataTerr1d::GenHd1MaxInBin(long nbin_new) const
{
    printf("not yet implimented\n");
    abort();
}

GraphDataTerr2d* const HistDataTerr1d::GenGraph2d() const
{
    printf("not yet implimented\n");
    abort();
}

TH1D* const HistDataTerr1d::GenTH1D(double offset_xval,
                                    double offset_oval) const
{

    printf("not yet implimented\n");
    abort();
}
    
// qdp range
void HistDataTerr1d::GetORangeQdp(double* const low_ptr,
                                  double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetOvalArr()->GetValAndErrMin(),
                          GetOvalArr()->GetValAndErrMax(),
                          &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


double HistDataTerr1d::GetOffsetOFromTag(string offset_tag) const
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
