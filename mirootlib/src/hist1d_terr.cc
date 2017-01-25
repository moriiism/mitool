#include "mir_hist1d_terr.h"

//
// public
//

void HistDataTerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

void HistDataTerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArrayTerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataTerr1d::SetOvalTerrArr(long ndata, const double* const val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void HistDataTerr1d::SetOvalTerrArr(vector<double> val_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_serr);
}

void HistDataTerr1d::SetOvalTerrArr(long ndata,
                                    const double* const val_terr_plus,
                                    const double* const val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(ndata, val_terr_plus, val_terr_minus);
}

void HistDataTerr1d::SetOvalTerrArr(vector<double> val_terr_plus,
                                    vector<double> val_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerr(val_terr_plus, val_terr_minus);
}

void HistDataTerr1d::SetOvalTerrElm(long ibin,
                                    double oval_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrElm(ibin, oval_serr);
}


void HistDataTerr1d::SetOvalTerrPlusElm(long ibin,
                                        double oval_terr_plus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrPlusElm(ibin, oval_terr_plus);
}

void HistDataTerr1d::SetOvalTerrMinusElm(long ibin,
                                         double oval_terr_minus)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValTerrMinusElm(ibin, oval_terr_minus);
}


void HistDataTerr1d::FillByMax(double xval,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    IsOvalArrNotNull();
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
    IsOvalArrNotNull();
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
    NullHistData1d();
    
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
}

const DataArrayTerr1d* const HistDataTerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetOvalArrNonConst());
}

double HistDataTerr1d::GetOvalSerrElm(long ibin) const
{
    IsOvalArrNotNull();    
    return GetOvalArr()->GetValSerrElm(ibin);
}


double HistDataTerr1d::GetOvalTerrPlusElm(long ibin) const
{
    IsOvalArrNotNull();    
    return GetOvalArr()->GetValTerrPlusElm(ibin);
}

double HistDataTerr1d::GetOvalTerrMinusElm(long ibin) const
{
    IsOvalArrNotNull();
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

void HistDataTerr1d::PrintData(FILE* fp, string format,
                               double offset_xval,
                               double offset_oval) const
{
    long nbin_xval = GetNbinX();
    if("x,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalTerrPlusElm(ibin),
                    GetOvalTerrMinusElm(ibin) );
        }
    } else if ("x,xe+,xe-,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            if(1 == MirMath::IsSame(GetOvalTerrPlusElm(ibin),
                                     -1 * GetOvalTerrMinusElm(ibin)) ){
                fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                        GetBinCenter(ibin) - offset_xval,
                        GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                        GetOvalElm(ibin) - offset_oval,
                        GetOvalTerrPlusElm(ibin) );
            } else {
                abort();
            }
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
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
    if(nbin_new > GetNbinX()){
        MPrintErrClass("bad nbin_new");
        abort();
    }
    if(nbin_new < 1){
        MPrintErrClass("bad nbin_new");
        abort();
    }
    if(0 != GetNbinX() % nbin_new){
        MPrintErrClass("bad nbin_new");
        abort();
    }

    HistDataTerr1d* h1d_new = new HistDataTerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByMax(GetBinCenter(ibin),
                           GetOvalElm(ibin),
                           GetOvalTerrPlusElm(ibin),
                           GetOvalTerrMinusElm(ibin));
    }
    return h1d_new;
}

GraphDataTerr2d* const HistDataTerr1d::GenGraph2d() const
{
    long nbin_xval = 0;
    double* xval_arr = NULL;
    double* xval_serr_arr = NULL;
    GetHi1d()->GenValArr(&xval_arr, &nbin_xval);
    GetHi1d()->GenValSerrArr(&xval_serr_arr, &nbin_xval);
    GraphDataTerr2d* g2d = new GraphDataTerr2d;
    g2d->Init(nbin_xval);
    g2d->SetXvalArr(nbin_xval, xval_arr);
    g2d->SetXvalTerrArr(nbin_xval, xval_serr_arr);
    g2d->SetOvalArr(nbin_xval, GetOvalArr()->GetVal());
    g2d->SetOvalTerrArr(nbin_xval,
                        GetOvalArr()->GetValTerrPlus(),
                        GetOvalArr()->GetValTerrMinus());
    g2d->SetFlagXvalSorted(1);
    delete [] xval_arr;
    delete [] xval_serr_arr;
    return g2d;
}

TH1D* const HistDataTerr1d::GenTH1D(double offset_xval,
                                    double offset_oval) const
{
    long nbin_xval = GetNbinX();
    double xval_lo = GetXvalLo();
    double xval_up = GetXvalUp();
    
    string name = GetTitle();
    TH1D* th1d = new TH1D(name.c_str(), name.c_str(),
                          nbin_xval,
                          xval_lo - offset_xval,
                          xval_up - offset_xval);
    for(long ibin = 0; ibin < nbin_xval; ibin++){
        double xval = GetBinCenter(ibin);
        th1d->Fill(xval - offset_xval,
                   GetOvalElm(ibin) - offset_oval);
        th1d->SetBinError(ibin + 1, GetOvalSerrElm(ibin));
    }	
    char xtitle[kLineSize];
    sprintf(xtitle, "offset = %e", offset_xval);
    th1d->SetXTitle(xtitle);

    char ytitle[kLineSize];
    sprintf(ytitle, "offset = %e", offset_oval);
    th1d->SetYTitle(ytitle);
    return th1d;
}
