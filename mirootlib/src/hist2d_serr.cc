#include "mir_hist2d_serr.h"

//
// public
//

void HistDataSerr2d::Init(long nbin_xval, double xval_lo, double xval_up,
                          long nbin_yval, double yval_lo, double yval_up)
{
    Null();
    SetInfo(nbin_xval, xval_lo, xval_up,
            nbin_yval, yval_lo, yval_up);
    long nbin = nbin_xval * nbin_yval;
    NewOvalArrAsDataArraySerr1d();
    GetOvalArrNonConst()->Init(nbin);
}

// SetData
void HistDataSerr2d::SetData(long nbin_xval, long nbin_yval, 
                             const double* const oval,
                             const double* const oval_serr)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    if(GetNbinY() != nbin_yval){
        MPrintErrClass("GetNbinY() != nbin_yval");
        abort();
    }
    GetOvalArrNonConst()->SetValAndSerr(nbin_xval * nbin_yval, oval, oval_serr);
}


// InitSet
void HistDataSerr2d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                             long nbin_yval, double yval_lo, double yval_up,
                             const double* const oval,
                             const double* const oval_serr)
{
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);
    SetData(nbin_xval, nbin_yval, oval, oval_serr);
}

void HistDataSerr2d::InitSet(const TH2D* const th2d)
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
    double* oval_serr = new double [nbin];
    for(long ibiny = 1; ibiny <= th2d->GetNbinsY(); ibiny ++){  
        for(long ibinx = 1; ibinx <= th2d->GetNbinsX(); ibinx ++){
            long ibin_h2d = ibinx - 1 + nbin_xval * (ibiny - 1);
            oval[ibin_h2d]  = th2d->GetBinContent(ibinx, ibiny);
            oval_serr[ibin_h2d] = th2d->GetBinError(ibinx, ibiny);
        }
    }
    SetData(nbin_xval, nbin_yval, oval, oval_serr);
    delete [] oval;
    delete [] oval_serr;
}

void HistDataSerr2d::SetOvalSerrElm(long ibin_xval, long ibin_yval, double oval_serr)
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        GetOvalArrNonConst()->SetValSerrElm(ibin, oval_serr);
    } else {
        num_serr_outer_ ++;
    }
}

void HistDataSerr2d::FillByMax(double xval, double yval,
                               double oval,
                               double oval_serr)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMax(ibin,
                                        oval,
                                        oval_serr);
    } else {
        num_serr_outer_ ++;
    }
}

void HistDataSerr2d::FillByMin(double xval, double yval,
                               double oval,
                               double oval_serr)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMin(ibin,
                                        oval,
                                        oval_serr);
    } else {
        num_serr_outer_ ++;
    }
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

    GraphDataSerr3d* gdata3d = new GraphDataSerr3d;
    gdata3d->Load(file, format);
    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
        SetOvalSerrElm(ibin_x, ibin_y, gdata3d->GetOvalSerrElm(idata) );
    }
    delete gdata3d;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


//
// operation
//

void HistDataSerr2d::Min(const HistDataSerr2d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
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

void HistDataSerr2d::Max(const HistDataSerr2d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
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


void HistDataSerr2d::Add(const HistDataSerr2d* const* const hist_data_arr,
                         int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
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

void HistDataSerr2d::AMean(const HistDataSerr2d* const* const hist_data_arr,
                           int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
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

int HistDataSerr2d::WMean(const HistDataSerr2d* const hist_data1,
                          const HistDataSerr2d* const hist_data2,
                          vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
         
    vector<long> index_bad_vec;
    GetOvalArrNonConst()->WMean(hist_data1->GetOvalArr(),
                                hist_data2->GetOvalArr(),
                                &index_bad_vec);
    *index_bad_vec_ptr = index_bad_vec;
    return index_bad_vec.size();
}

int HistDataSerr2d::WMean(const HistDataSerr2d* const* const hist_data_arr,
                          int nhist,
                          vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
         
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
const DataArraySerr1d* const HistDataSerr2d::GetOvalArr() const
{
    const DataArray1d* oval_arr = HistData2d::GetOvalArr();
    return dynamic_cast<const DataArraySerr1d*>(oval_arr);
}

const double* const HistDataSerr2d::GetOvalSerrArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValSerr();
}

double HistDataSerr2d::GetOvalSerrElm(long ibin_xval, long ibin_yval) const
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    double oval_serr = 0.0;
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        oval_serr = GetOvalArr()->GetValSerrElm(ibin);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xval(=%ld) or ibin_yval(=%ld)\n",
                ibin_xval, ibin_yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_serr;
}

double HistDataSerr2d::GetOvalSerrElmAtXY(double xval, double yval) const
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    double oval_serr = 0.0;
    if(1 == ret){
        long ibin_x = GetIbinXFromX(xval);
        long ibin_y = GetIbinYFromY(yval);
        oval_serr = GetOvalSerrElm(ibin_x, ibin_y);
    } else {
     char msg[kLineSize];
        sprintf(msg, "bad xval(=%e) or yval(=%e)\n",
                xval, yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval_serr;
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

// calc_mode  : "add", "integral", "amean"
// error_mode: gauss, poisson, zero
HistDataSerr1d* const HistDataSerr2d::GenProjectX(long ibin_ylo, long ibin_yup,
                                                  string calc_mode, string error_mode) const
{
    int ret = IsValidIbinY(ibin_ylo) * IsValidIbinY(ibin_yup);
    if(1 != ret){
        char msg[kLineSize];
        sprintf(msg, "bad ibin_ylo(=%ld) or ibin_yup(=%ld)\n",
                ibin_ylo, ibin_yup);
        MPrintErrClass(msg);
        abort();
    }
    HistDataSerr1d* h1d = new HistDataSerr1d;
    h1d->Init(GetNbinX(), GetXvalLo(), GetXvalUp());
    for(long ibin_xval = 0; ibin_xval < GetNbinX(); ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj;
        double val_proj_err;
    
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   GetBinWidthY(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        h1d->SetOvalElm(ibin_xval, val_proj);
        h1d->SetOvalSerrElm(ibin_xval, val_proj_err);
    }
    return h1d;
}

// calc_mode  : "add", "integral", "amean"
// error_mode: gauss, poisson, zero
HistDataSerr1d* const HistDataSerr2d::GenProjectY(long ibin_xlo, long ibin_xup,
                                                  string calc_mode, string error_mode) const
{
    int ret = IsValidIbinX(ibin_xlo) * IsValidIbinX(ibin_xup);
    if(1 != ret){
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xlo(=%ld) or ibin_xup(=%ld)\n",
                ibin_xlo, ibin_xup);
        MPrintErrClass(msg);
        abort();
    }
    
    HistDataSerr1d* h1d = new HistDataSerr1d;
    h1d->Init(GetNbinY(), GetYvalLo(), GetYvalUp());
    for(long ibin_yval = 0; ibin_yval < GetNbinY(); ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        double* tmp_err_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
            tmp_err_arr[ibin_tmp] = GetOvalSerrElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj;
        double val_proj_err;
        GetProject(nbin_tmp,
                   tmp_arr, tmp_err_arr,
                   calc_mode, error_mode,
                   GetBinWidthX(),
                   &val_proj, &val_proj_err);
        delete [] tmp_arr;
        delete [] tmp_err_arr;
        h1d->SetOvalElm(ibin_yval, val_proj);
        h1d->SetOvalSerrElm(ibin_yval, val_proj_err);
    }
    return h1d;
}


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
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);
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
        GetBinCenterXYFromIbin(ibin, &xval, &yval);
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
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
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        double xval = GetBinCenterXFromIbinX(ibin_x);
        double yval = GetBinCenterYFromIbinY(ibin_y);

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
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        double xval = GetBinCenterXFromIbinX(ibin_x);
        double yval = GetBinCenterYFromIbinY(ibin_y);
        
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
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        
        // poisson error
        double oval_rand = trand->PoissonD(hist_data->GetOvalElm(ibin_x, ibin_y));
        double oval_err = sqrt(oval_rand);
        SetOvalElm(ibin_x, ibin_y, oval_rand);
        SetOvalSerrElm(ibin_x, ibin_y, oval_err);
    }
    delete trand;
}


double HistDataSerr2d::GetOffsetOFromTag(string offset_tag) const
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



//
// private
//

// calc_mode  : "add", "integral", "amean"
// error_mode: gauss, poisson, zero
void HistDataSerr2d::GetProject(long ndata,
                                const double* const array,
                                const double* const array_err,
                                string calc_mode, string error_mode,
                                double bin_width,
                                double* const val_proj_ptr,
                                double* const val_proj_err_ptr) const
{
    string func_name = "HistDataSerr2d::GetAddForProject()";
  
    double val_proj;
    double val_proj_err;
    if("add" == calc_mode || "integral" == calc_mode){
        if("gauss" == error_mode){
            MirMath::GetAdd(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            val_proj = MirMath::GetAdd(ndata, array);
            val_proj_err = sqrt(val_proj);
        } else if("zero" == error_mode){
            val_proj = MirMath::GetAdd(ndata, array);
            val_proj_err = 0.0;
        } else {
            printf("%s: error: error_mode (=%s)\n", func_name.c_str(), error_mode.c_str());
            exit(1);
        }

        if("integral" == calc_mode){
            val_proj *= bin_width;
            val_proj_err *= bin_width;
        }

    } else if ("amean" == calc_mode){
        if("gauss" == error_mode){
            MirMath::GetAMean(ndata, array, array_err, &val_proj, &val_proj_err);
        } else if("poisson" == error_mode){
            double val_add = MirMath::GetAdd(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = sqrt(val_add) / ndata;
        } else if("zero" == error_mode){
            double val_add = MirMath::GetAdd(ndata, array);
            val_proj = val_add / ndata;
            val_proj_err = 0.0;
        } else {
            printf("%s: error: error_mode (=%s)\n", func_name.c_str(), error_mode.c_str());
            exit(1);
        }
    
    } else {
        printf("%s: error: calc_mode (=%s)\n", func_name.c_str(), calc_mode.c_str());
        exit(1);
    }

    *val_proj_ptr = val_proj;
    *val_proj_err_ptr = val_proj_err;
}

