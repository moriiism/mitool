#include "mir_hist1d_serr.h"

//
// public
//

void HistDataSerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    Null();
    SetInfo(nbin_xval, xval_lo, xval_up);
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);
}

// SetData
void HistDataSerr1d::SetData(long nbin_xval,
                             const double* const oval,
                             const double* const oval_serr)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    GetOvalArrNonConst()->SetValAndSerr(nbin_xval,
                                        oval,
                                        oval_serr);
}


// InitSet
void HistDataSerr1d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                             const double* const oval,
                             const double* const oval_serr)
{
    Init(nbin_xval, xval_lo, xval_up);
    SetData(nbin_xval, oval, oval_serr);
}

void HistDataSerr1d::InitSet(const TH1D* const th1d)
{
    Null();
    
    long nbin_xval = th1d->GetNbinsX();
    double xval_lo = th1d->GetXaxis()->GetXmin();
    double xval_up = th1d->GetXaxis()->GetXmax();
    Init(nbin_xval, xval_lo, xval_up);

    double* oval      = new double [nbin_xval];
    double* oval_serr = new double [nbin_xval];
    for(long ibin = 0; ibin < nbin_xval; ibin ++){
        oval[ibin]      = th1d->GetBinContent(ibin + 1);
        oval_serr[ibin] = th1d->GetBinError(ibin + 1);
    }
    SetData(nbin_xval, oval, oval_serr);
    delete [] oval;
    delete [] oval_serr;
}

void HistDataSerr1d::SetOvalSerrElm(long ibin, double oval_serr)
{
    IsOvalNotNull();
    GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);

}

void HistDataSerr1d::FillByMax(double xval,
                               double oval,
                               double oval_serr)
{
    IsOvalNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMax(ibin, oval, oval_serr);
}

void HistDataSerr1d::FillByMin(double xval,
                               double oval,
                               double oval_serr)
{
    IsOvalNotNull();    
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
    Null();

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

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

//
// operation
//

void HistDataSerr1d::Min(const HistDataSerr1d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
    DataArraySerr1d** data_array_arr = new DataArraySerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArraySerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Min(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistDataSerr1d::Max(const HistDataSerr1d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
    DataArraySerr1d** data_array_arr = new DataArraySerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArraySerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Max(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}


void HistDataSerr1d::Add(const HistDataSerr1d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
    DataArraySerr1d** data_array_arr = new DataArraySerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArraySerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Add(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistDataSerr1d::AMean(const HistDataSerr1d* const* const hist_data_arr,
                           int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
    DataArraySerr1d** data_array_arr = new DataArraySerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArraySerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->AMean(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

int HistDataSerr1d::WMean(const HistDataSerr1d* const hist_data1,
                          const HistDataSerr1d* const hist_data2,
                          vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    vector<long> index_bad_vec;
    GetOvalArrNonConst()->WMean(hist_data1->GetOvalArr(),
                                hist_data2->GetOvalArr(),
                                &index_bad_vec);
    *index_bad_vec_ptr = index_bad_vec;
    return index_bad_vec.size();
}

int HistDataSerr1d::WMean(const HistDataSerr1d* const* const hist_data_arr,
                          int nhist,
                          vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
    DataArraySerr1d** data_array_arr = new DataArraySerr1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArraySerr1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    vector<long> index_bad_vec;    
    GetOvalArrNonConst()->WMean(data_array_arr, nhist, &index_bad_vec);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
    return index_bad_vec.size();
}



//
// const functions
//

// get
const DataArraySerr1d* const HistDataSerr1d::GetOvalArr() const
{
    const DataArray1d* oval_arr = HistData1d::GetOvalArr();
    return dynamic_cast<const DataArraySerr1d*>(oval_arr);
}

const double* const HistDataSerr1d::GetOvalSerrArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValSerr();
}

double HistDataSerr1d::GetOvalSerrElm(long ibin) const
{
    IsOvalNotNull();    
    return GetOvalArr()->GetValSerrElm(ibin);
}

double HistDataSerr1d::GetOvalSerrElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalSerrElm(ibin);
}


void HistDataSerr1d::GenOvalSerrArr(double** const oval_serr_arr_ptr,
                                    long* const nbin_ptr) const
{
    long nbin_xval = GetNbinX();
    double* oval_serr_arr = new double [nbin_xval];
    for(long ibin = 0; ibin < nbin_xval; ibin++){
        oval_serr_arr[ibin] = GetOvalArr()->GetValSerrElm(ibin);
    }
    *oval_serr_arr_ptr = oval_serr_arr;
    *nbin_ptr = nbin_xval;
}

//
// output
//

void HistDataSerr1d::PrintData(FILE* fp, string format,
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
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe,y" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval);
        }
    } else if ("x,xe,y,ye" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin));
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin),
                    -1 * GetOvalSerrElm(ibin) );
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
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetBinWidth()/2., -1 * GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval,
                    GetOvalSerrElm(ibin) );
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetBinWidth()/2., -1 * GetBinWidth()/2.,
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
        h1d_new->FillByMax(GetBinCenterX(ibin),
                           GetOvalElm(ibin),
                           GetOvalSerrElm(ibin));
    }

    return h1d_new;
}

GraphDataSerr2d* const HistDataSerr1d::GenGraph2d() const
{
    long nbin_xval = GetNbinX();
    double xval_lo = GetXvalLo();
    double xval_up = GetXvalUp();    
    
    double* xval_arr = new double [nbin_xval];
    double* xval_err_arr = new double [nbin_xval];
    double xval_step = (xval_up - xval_lo)/ nbin_xval;
  
    for(long index_xval = 0; index_xval < nbin_xval; index_xval++){
        double xval = xval_lo + (index_xval + 0.5) * xval_step;
        xval_arr[index_xval] = xval;
        xval_err_arr[index_xval] = xval_step / 2.;
    }
    GraphDataSerr2d* g2d = new GraphDataSerr2d;
    g2d->Init();
    g2d->SetXvalAndSerrArrDbl(nbin_xval,
                              xval_arr,
                              xval_err_arr);
    g2d->SetOvalAndSerrArrDbl(nbin_xval,
                              GetOvalArrDbl(),
                              GetOvalSerrArrDbl());
    g2d->SetFlagXvalSorted(1);
    delete [] xval_arr;
    delete [] xval_err_arr;
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
        double xval = GetBinCenterX(ibin);
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

void HistDataSerr1d::GetORangeQdp(double* const low_ptr,
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

void HistDataSerr1d::FillRandom(const MirFunc* const func,
                                const MirFuncPar* const func_par,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenterX(ibin);
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
        double xval = GetBinCenterX(ibin);
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


double HistDataSerr1d::GetOffsetOFromTag(string offset_tag) const
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



