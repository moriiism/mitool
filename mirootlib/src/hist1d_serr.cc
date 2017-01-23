#include "mir_hist1d_serr.h"

//
// public
//

void HistDataSerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

void HistDataSerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

void HistDataSerr1d::SetOvalSerrElm(long ibin, double oval_serr)
{
    IsOvalArrNotNull();
    GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);

}

void HistDataSerr1d::FillByMax(double xval,
                               double oval,
                               double oval_serr)
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMax(ibin, oval, oval_serr);
}

void HistDataSerr1d::FillByMin(double xval,
                               double oval,
                               double oval_serr)
{
    IsOvalArrNotNull();    
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMin(ibin, oval, oval_serr);
}


void HistDataSerr1d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}

HistDataSerr1d* const HistDataSerr1d::Clone() const
{
    HistDataSerr1d* obj_new = new HistDataSerr1d;
    obj_new->Copy(this);
    return obj_new;
}


void HistDataSerr1d::Load(string file)
{
    NullHistData1d();

    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);    
    Init(nbin_xval, xval_lo, xval_up);

    if("x,y,ye" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
    GraphDataSerr2d* gdata2d = new GraphDataSerr2d;
    gdata2d->Load(file, format);
    for(long idata = 0; idata < gdata2d->GetNdata(); idata++){
        long ibin = GetIbin(gdata2d->GetXvalElm(idata));
        SetOvalElm(ibin, gdata2d->GetOvalElm(idata) );
        SetOvalSerrElm(ibin, gdata2d->GetOvalSerrElm(idata) );
    }
    delete gdata2d;
}


const DataArraySerr1d* const HistDataSerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double HistDataSerr1d::GetOvalSerrElm(long ibin) const
{
    IsOvalArrNotNull();
    return GetOvalArr()->GetValSerrElm(ibin);
}

double HistDataSerr1d::GetOvalSerrElmAtX(double xval) const
{
    IsOvalArrNotNull();
    long ibin = GetIbin(xval);
    return GetOvalSerrElm(ibin);
}

void HistDataSerr1d::PrintData(FILE* fp, string format,
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
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
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
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
  
}


HistDataSerr1d* const HistDataSerr1d::GenHd1MaxInBin(long nbin_new) const
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

    HistDataSerr1d* h1d_new = new HistDataSerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByMax(GetBinCenter(ibin),
                           GetOvalElm(ibin),
                           GetOvalSerrElm(ibin));
    }

    return h1d_new;
}

GraphDataSerr2d* const HistDataSerr1d::GenGraph2d() const
{
    long nbin_xval = 0;
    double* xval_arr = NULL;
    double* xval_serr_arr = NULL;
    GetHi1d()->GenValArr(&xval_arr, &nbin_xval);
    GetHi1d()->GenValSerrArr(&xval_serr_arr, &nbin_xval);
    GraphDataSerr2d* g2d = new GraphDataSerr2d;
    g2d->Init(nbin_xval);
    g2d->SetXvalArr(nbin_xval, xval_arr);
    g2d->SetXvalSerrArr(nbin_xval, xval_serr_arr);
    g2d->SetOvalArr(nbin_xval, GetOvalArr()->GetVal());
    g2d->SetOvalSerrArr(nbin_xval, GetOvalArr()->GetValSerr());
    g2d->SetFlagXvalSorted(1);
    delete [] xval_arr;
    delete [] xval_serr_arr;
    return g2d;
}

TH1D* const HistDataSerr1d::GenTH1D(double offset_xval,
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

void HistDataSerr1d::FillRandom(const MirFunc* const func,
                                const MirFuncPar* const func_par,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par->GetPar());

        // poisson error
        double oval_rand = trand->PoissonD(oval);
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete trand;
}

void HistDataSerr1d::FillRandom(const MirFunc* const func,
                                const MirFuncPar* const func_par,
                                const MirFunc* const func_sigma,
                                const MirFuncPar* const func_par_sigma,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par->GetPar());
        
        // gaussian error
        double sigma = func_sigma->Eval1d(xval, func_par_sigma->GetPar());
        double oval_rand = trand->Gaus(oval, sigma);
        double oval_err = sigma;
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete trand;
}


void HistDataSerr1d::FillRandom(const HistData1d* const hist_data, int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp());
    
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        // poisson error
        double oval_rand = trand->PoissonD(hist_data->GetOvalElm(ibin));
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin, oval_rand);
        SetOvalSerrElm(ibin, oval_err);
    }
    delete trand;
}


