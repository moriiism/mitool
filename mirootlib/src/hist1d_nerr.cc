#include "mir_hist1d_nerr.h"

//
// public
//

// Init
void HistDataNerr1d::Init(long nbin_xval,
                          double xval_lo,
                          double xval_up)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(nbin_xval);    
}

void HistDataNerr1d::Init(const HistInfo1d* const hist_info)
{
    NullHistData1d();
    NewHi1d();
    GetHi1dNonConst()->InitSetByNbin(hist_info->GetLo(),
                                     hist_info->GetUp(),
                                     hist_info->GetNbin());
    NewOvalArrAsDataArrayNerr1d();
    GetOvalArrNonConst()->Init(hist_info->GetNbin());
}

HistDataNerr1d* const HistDataNerr1d::Clone() const
{
    HistDataNerr1d* obj_new = new HistDataNerr1d;
    obj_new->Copy(this);
    return obj_new;
}

void HistDataNerr1d::Load(string file)
{
    NullHistData1d();

    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);
    Init(nbin_xval, xval_lo, xval_up);
    
    if("x,y" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
    string* line_arr = NULL;
    long nline = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &nline);
    if(nline != nbin_xval){
        char msg[kLineSize];
        sprintf(msg, "nline != nbin_xval");
        MPrintErrClass(msg);
        abort();
    }
    double xval = 0.0;
    double oval = 0.0;
    for(long iline = 0; iline < nline; iline ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[iline]);
        if(2 != ncolumn){
            MPrintErrClass("ncolumn != 2");
            abort();
        }
        istringstream iss(line_arr[iline]);
        iss >> xval >> oval;
        long ibin = GetIbin(xval);
        SetOvalElm(ibin, oval);
    }
    MiIolib::DelReadFile(line_arr);
}

const DataArrayNerr1d* const HistDataNerr1d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void HistDataNerr1d::PrintData(FILE* fp, string format,
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
                    0.0);
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    0.0);
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval, GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    GetOvalElm(ibin) - offset_oval, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenter(ibin) - offset_xval,
                    GetXvalBinWidth()/2., -1 * GetXvalBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}


HistDataNerr1d* const HistDataNerr1d::GenHd1MaxInBin(long nbin_new) const
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
    
    HistDataNerr1d* h1d_new = new HistDataNerr1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByLarger( GetBinCenter(ibin), GetOvalElm(ibin) );
    }

    return h1d_new;
}

TH1D* const HistDataNerr1d::GenTH1D(double offset_xval,
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
    }
    char xtitle[kLineSize];
    sprintf(xtitle, "offset = %e", offset_xval);
    th1d->SetXTitle(xtitle);

    char ytitle[kLineSize];
    sprintf(ytitle, "offset = %e", offset_oval);
    th1d->SetYTitle(ytitle);
  
    return th1d;
}

void HistDataNerr1d::MkTH1Fig(string outfig,
                              MirRootTool* const root_tool,
                              double offset_xval,
                              double offset_oval) const
{
    TH1D* th1d = GenTH1D(offset_xval, offset_oval);
    th1d->Draw("HIST");
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete th1d;
}

void HistDataNerr1d::FillRandom(const MirFunc* const func,
                                const double* const func_par,
                                int rand_seed)
{
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenter(ibin);
        double oval = func->Eval1d(xval, func_par);
        double oval_rand = trand->PoissonD(oval);
        SetOvalElm(ibin, oval_rand);
    }
    delete trand;
}


void HistDataNerr1d::FillRandom(const HistData1d* const hist_data, int rand_seed)
{
    Init(hist_data->GetNbinX(), hist_data->GetXvalLo(), hist_data->GetXvalUp());
    
    TRandom3* trand = new TRandom3(rand_seed);
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        double oval_rand = trand->PoissonD(hist_data->GetOvalElm(ibin));
        SetOvalElm(ibin, oval_rand);
    }
    delete trand;
}

HistDataNerr1d* HistDataNerr1d::GenSubHist(long ibinx_st, long ibinx_ed) const
{
    HistDataNerr1d* hd1d_sub = new HistDataNerr1d;
    long nbinx_sub = ibinx_ed - ibinx_st + 1;
    hd1d_sub->Init(nbinx_sub, GetBinLo(ibinx_st), GetBinUp(ibinx_ed));
    for(long ibinx = 0; ibinx < nbinx_sub; ibinx ++){
        hd1d_sub->SetOvalElm(ibinx, GetOvalElm(ibinx_st + ibinx));
    }
    return hd1d_sub;
}
