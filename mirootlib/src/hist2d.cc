#include "mir_hist2d.h"

//
// public
//

void HistData2d::Init(long nbin_xval, double xval_lo, double xval_up,
                      long nbin_yval, double yval_lo, double yval_up)

{
    Null();
    SetInfo(nbin_xval, xval_lo, xval_up,
            nbin_yval, yval_lo, yval_up);
    long nbin = nbin_xval * nbin_yval;
    NewOvalArrAsDataArray1d();
    GetOvalArrNonConst()->Init(nbin);
}

void HistData2d::Init(const HistInfo2d* const hist_info)
{
    Init(hist_info->GetNbinX(), hist_info->GetLoX(), hist_info->GetUpX(),
         hist_info->GetNbinY(), hist_info->GetLoY(), hist_info->GetUpY());
}

// Set
void HistData2d::Set(const HistData2d* const org)
{
    CopyMirObject(org);
    Set(org->GetNbinX(),
        org->GetXvalLo(),
        org->GetXvalUp(),
        org->GetNbinY(),
        org->GetYvalLo(),
        org->GetYvalUp(),
        org->GetOvalArr());
}

void HistData2d::Set(long nbin_xval, double xval_lo, double xval_up,
                     long nbin_yval, double yval_lo, double yval_up,
                     const DataArray1d* const oval_arr)
{
    SetInfo(nbin_xval, xval_lo, xval_up,
            nbin_yval, yval_lo, yval_up);
    SetData(oval_arr);
}


// InitSet
void HistData2d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const DataArray1d* const oval_arr)
{
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);
    Set(nbin_xval, xval_lo, xval_up,
        nbin_yval, yval_lo, yval_up,
        oval_arr);
}

// Set Info
void HistData2d::SetInfo(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up)
{
    nbin_xval_ = nbin_xval;
    xval_lo_   = xval_lo;
    xval_up_   = xval_up;
    nbin_yval_ = nbin_yval;
    yval_lo_   = yval_lo;
    yval_up_   = yval_up;    
}

// SetData
void HistData2d::SetData(const DataArray1d* const oval_arr)
{
    if(GetNbinX() * GetNbinY() != oval_arr->GetNdata()){
        MPrintErrClass("GetNbinX() * GetNbinY() != oval_arr->GetNdata()");
        abort();
    }
    GetOvalArrNonConst()->Set(oval_arr);
}


void HistData2d::SetData(long nbin_xval, long nbin_yval, 
                         const double* const oval)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    if(GetNbinY() != nbin_yval){
        MPrintErrClass("GetNbinY() != nbin_yval");
        abort();
    }
    GetOvalArrNonConst()->SetVal(nbin_xval * nbin_yval, oval);
}

// InitSet
void HistData2d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                         long nbin_yval, double yval_lo, double yval_up,
                         const double* const oval)
{
    Init(nbin_xval, xval_lo, xval_up,
         nbin_yval, yval_lo, yval_up);
    SetData(nbin_xval, nbin_yval, oval);
}


void HistData2d::InitSet(const TH2D* const th2d)
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
    for(long ibiny = 1; ibiny <= th2d->GetNbinsY(); ibiny ++){  
        for(long ibinx = 1; ibinx <= th2d->GetNbinsX(); ibinx ++){
            long ibin_h2d = ibinx - 1 + nbin_xval * (ibiny - 1);
            oval[ibin_h2d] = th2d->GetBinContent(ibinx, ibiny);
        }
    }
    SetData(nbin_xval, nbin_yval, oval);
    delete [] oval;
}


void HistData2d::SetOvalElm(long ibin_xval, long ibin_yval, double oval)
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        GetOvalArrNonConst()->SetValElm(ibin, oval);
    } else {
        num_outer_ ++;
    }
}

void HistData2d::Fill(double xval, double yval)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->Fill(ibin);
    } else {
        num_outer_ ++;
    }
}

void HistData2d::Fill(double xval, double yval, double weight)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->Fill(ibin, weight);
    } else {
        num_outer_ ++;        
    }
}

void HistData2d::FillByMax(double xval, double yval, double oval)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMax(ibin, oval);
    } else {
        num_outer_ ++;        
    }
}

void HistData2d::FillByMin(double xval, double yval, double oval)
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 == ret){    
        long ibin = GetIbinFromXY(xval, yval);
        GetOvalArrNonConst()->FillByMin(ibin, oval);
    } else {
        num_outer_ ++;        
    }
}

void HistData2d::SetZero()
{
    IsOvalNotNull();
    GetOvalArrNonConst()->SetZero();
}

void HistData2d::SetOne()
{
    IsOvalNotNull();
    GetOvalArrNonConst()->SetOne();
}

void HistData2d::SetConst(double constant)
{
    IsOvalNotNull();    
    GetOvalArrNonConst()->SetConst(constant);
}

void HistData2d::SetOneAtIntervalXY(const Interval* const interval_x,
                                    const Interval* const interval_y)
{
    IsOvalNotNull();    
    if(1 != interval_x->IsOrdered()){
        MPrintErrClass("bad interval_x.");
        abort();
    }
    if(1 != interval_y->IsOrdered()){
        MPrintErrClass("bad interval_y.");
        abort();
    }
    Interval* interval_x_hist = new Interval;
    interval_x_hist->InitSet(xval_lo_, xval_up_);
    Interval* interval_x_and = new Interval;
    interval_x_and->And(interval_x, interval_x_hist);

    Interval* interval_y_hist = new Interval;
    interval_y_hist->InitSet(yval_lo_, yval_up_);
    Interval* interval_y_and = new Interval;
    interval_y_and->And(interval_y, interval_y_hist);

    GetOvalArrNonConst()->SetZero();
    for(long iterm_x = 0; iterm_x < interval_x_and->GetNterm(); iterm_x++){
        for(long iterm_y = 0; iterm_y < interval_y_and->GetNterm(); iterm_y++){
            double xlo = interval_x_and->GetTstartElm(iterm_x);
            double xup = interval_x_and->GetTstopElm(iterm_x);
            double ylo = interval_y_and->GetTstartElm(iterm_y);
            double yup = interval_y_and->GetTstopElm(iterm_y);

            printf("GetIbinX(xlo) = %ld\n", GetIbinXFromX(xlo));
            printf("GetIbinX(xup) = %ld\n", GetIbinXFromX(xup));
            printf("GetIbinY(ylo) = %ld\n", GetIbinYFromY(ylo));
            printf("GetIbinY(yup) = %ld\n", GetIbinYFromY(yup));

            long ibin_x_lo = (long) MirMath::GetMax((double) GetIbinXFromX(xlo), 0.0);
            long ibin_x_up = (long) MirMath::GetMin((double) GetIbinXFromX(xup),
                                                     (double) (nbin_xval_ - 1) );
            long ibin_y_lo = (long) MirMath::GetMax((double) GetIbinYFromY(ylo), 0.0);
            long ibin_y_up = (long) MirMath::GetMin((double) GetIbinYFromY(yup),
                                                     (double) (nbin_yval_ - 1) );
            
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
            double xval = GetBinCenterXFromIbinX(ibinx);
            double yval = GetBinCenterYFromIbinY(ibiny);
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
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMirObject(org);
    Init(org->GetNbinX(),
         org->GetXvalLo(),
         org->GetXvalUp(),
         org->GetNbinY(),
         org->GetYvalLo(),
         org->GetYvalUp());
    Set(org);
}


HistData2d* const HistData2d::Clone() const
{
    HistData2d* obj_new = new HistData2d;
    obj_new->Copy(this);
    return obj_new;
}

void HistData2d::Load(string file)
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

    if("x,y,z" != format){
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
    GraphData3d* gdata3d = new GraphData3d;
    gdata3d->Load(file, format);
    for(long idata = 0; idata < gdata3d->GetNdata(); idata++){
        long ibin_x = GetIbinXFromX(gdata3d->GetXvalElm(idata));
        long ibin_y = GetIbinYFromY(gdata3d->GetYvalElm(idata));
        SetOvalElm(ibin_x, ibin_y, gdata3d->GetOvalElm(idata) );
    }
    delete gdata3d;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


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
    MirIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MirStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
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
    MirIolib::DelReadFile(line_arr);

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
// operation
//

void HistData2d::Not(const HistData2d* const hist_data)
{
    Init(hist_data->GetNbinX(),
         hist_data->GetXvalLo(),
         hist_data->GetXvalUp(),
         hist_data->GetNbinY(),
         hist_data->GetYvalLo(),
         hist_data->GetYvalUp());
    GetOvalArrNonConst()->Not(hist_data->GetOvalArr());
}

void HistData2d::Scale(const HistData2d* const hist_data,
                       double scale, double offset)
{
    Init(hist_data->GetNbinX(),
         hist_data->GetXvalLo(),
         hist_data->GetXvalUp(),
         hist_data->GetNbinY(),
         hist_data->GetYvalLo(),
         hist_data->GetYvalUp());
    GetOvalArrNonConst()->Scale(hist_data->GetOvalArr(),
                                scale, offset);
}

void HistData2d::Min(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->Min(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData2d::Min(const HistData2d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Min(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::Max(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->Max(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}


void HistData2d::Max(const HistData2d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Max(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}


void HistData2d::Add(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->Add(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData2d::Add(const HistData2d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Add(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}



void HistData2d::Sub(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->Sub(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData2d::Mul(const HistData2d* const hist_data1,
                     const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->Mul(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

int HistData2d::Div(const HistData2d* const hist_data_num,
                    const HistData2d* const hist_data_den,
                    vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data_num->GetNbinX(),
         hist_data_num->GetXvalLo(),
         hist_data_num->GetXvalUp(),
         hist_data_num->GetNbinY(),
         hist_data_num->GetYvalLo(),
         hist_data_num->GetYvalUp());
    vector<long> index_bad_vec;
    GetOvalArrNonConst()->Div(hist_data_num->GetOvalArr(),
                              hist_data_den->GetOvalArr(),
                              &index_bad_vec);
    *index_bad_vec_ptr = index_bad_vec;
    return index_bad_vec.size();
}

void HistData2d::AMean(const HistData2d* const hist_data1,
                       const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->AMean(hist_data1->GetOvalArr(),
                                hist_data2->GetOvalArr());
}

void HistData2d::AMean(const HistData2d* const* const hist_data_arr,
                       int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->AMean(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::SubAddRatio(const HistData2d* const hist_data1,
                             const HistData2d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp(),
         hist_data1->GetNbinY(),
         hist_data1->GetYvalLo(),
         hist_data1->GetYvalUp());
    GetOvalArrNonConst()->SubAddRatio(hist_data1->GetOvalArr(),
                                      hist_data2->GetOvalArr());
}


void HistData2d::Variance(const HistData2d* const* const hist_data_arr,
                          int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Variance(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::Stddev(const HistData2d* const* const hist_data_arr,
                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Stddev(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::UnbiasedVariance(const HistData2d* const* const hist_data_arr,
                                  int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->UnbiasedVariance(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::SqrtOfUnbiasedVariance(const HistData2d* const* const hist_data_arr,
                                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->SqrtOfUnbiasedVariance(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::RMS(const HistData2d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->RMS(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}

void HistData2d::Median(const HistData2d* const* const hist_data_arr,
                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp(),
         hist_data_arr[0]->GetNbinY(),
         hist_data_arr[0]->GetYvalLo(),
         hist_data_arr[0]->GetYvalUp());
    DataArray1d** data_array_arr = new DataArray1d* [nhist];
    for(int ihist = 0; ihist < nhist; ihist++){
        data_array_arr[ihist] = new DataArray1d;
        data_array_arr[ihist]->Copy(hist_data_arr[ihist]->GetOvalArr());
    }
    GetOvalArrNonConst()->Median(data_array_arr, nhist);
    
    for(int ihist = 0; ihist < nhist; ihist++){
        delete data_array_arr[ihist]; data_array_arr[ihist] = NULL;
    }
    delete [] data_array_arr; data_array_arr = NULL;
}


//
// const functions
//

long HistData2d::GetIbin(long ibin_xval, long ibin_yval) const
{
    IsValidIbinX(ibin_xval);
    IsValidIbinY(ibin_yval);
    long ibin = ibin_xval + nbin_xval_ * ibin_yval;
    return ibin;
}

long HistData2d::GetIbinX(long ibin) const
{
    long ibin_xval = ibin % nbin_xval_;
    IsValidIbinX(ibin_xval);
    return ibin_xval;
}

long HistData2d::GetIbinY(long ibin) const
{
    long ibin_yval = ibin / nbin_xval_;
    IsValidIbinY(ibin_yval);
    return ibin_yval;
}

long HistData2d::GetIbinXFromX(double xval) const
{
    IsValidRangeX(xval);
    double delta_xval = GetBinWidthX();
    long ibin_xval = static_cast<long>( floor((xval - xval_lo_) / delta_xval) );
    return ibin_xval;
}

long HistData2d::GetIbinYFromY(double yval) const
{
    IsValidRangeY(yval);
    double delta_yval = GetBinWidthY();
    long ibin_yval = static_cast<long>( floor((yval - yval_lo_) / delta_yval) );
    return ibin_yval;
}

long HistData2d::GetIbinFromXY(double xval, double yval) const
{
    IsValidRangeX(xval);
    IsValidRangeY(yval);
    long ibin_xval = GetIbinXFromX(xval);
    IsValidIbinX(ibin_xval);
    long ibin_yval = GetIbinYFromY(yval);
    IsValidIbinY(ibin_yval);
    long ibin = GetIbin(ibin_xval, ibin_yval);
    return ibin;
}


double HistData2d::GetBinCenterXFromIbinX(long ibin_xval) const
{
    IsValidIbinX(ibin_xval);
    double delta_xval = GetBinWidthX();
    double bin_center = xval_lo_ + (ibin_xval + 0.5) * delta_xval;
    return bin_center;
}

double HistData2d::GetBinCenterYFromIbinY(long ibin_yval) const
{
    IsValidIbinY(ibin_yval);    
    double delta_yval = GetBinWidthY();
    double bin_center = yval_lo_ + (ibin_yval + 0.5) * delta_yval;
    return bin_center;
}

double HistData2d::GetBinCenterXFromIbin(long ibin) const
{
    long ibin_xval = GetIbinX(ibin);
    IsValidIbinX(ibin_xval);    
    double bin_center = GetBinCenterXFromIbinX(ibin_xval);
    return bin_center;
}

double HistData2d::GetBinCenterYFromIbin(long ibin) const
{
    long ibin_yval = GetIbinY(ibin);
    IsValidIbinY(ibin_yval);
    double bin_center = GetBinCenterYFromIbinY(ibin_yval);
    return bin_center;
}

void HistData2d::GetBinCenterXYFromIbin(long ibin,
                                        double* const xval_ptr,
                                        double* const yval_ptr) const
{
    double bin_center_xval = GetBinCenterXFromIbin(ibin);
    double bin_center_yval = GetBinCenterYFromIbin(ibin);
    *xval_ptr = bin_center_xval;
    *yval_ptr = bin_center_yval;
}


long HistData2d::GetIbinX_WithHalfBinShifted(double xval) const
{
    IsValidRangeX(xval);
    double delta_xval = GetBinWidthX();
    double xval_lo_half_bin_shifted = xval_lo_ + 0.5 * delta_xval;
    long ibin_xval = static_cast<long>( floor((xval - xval_lo_half_bin_shifted) / delta_xval) );
    return ibin_xval;
}

long HistData2d::GetIbinY_WithHalfBinShifted(double yval) const
{
    IsValidRangeX(yval);
    double delta_yval = GetBinWidthY();
    double yval_lo_half_bin_shifted = yval_lo_ + 0.5 * delta_yval;
    long ibin_yval = static_cast<long>( floor((yval - yval_lo_half_bin_shifted) / delta_yval) );
    return ibin_yval;
}




// get internal of oval_arr_
const double* const HistData2d::GetOvalArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetVal();
}

double HistData2d::GetOvalElm(long ibin_xval, long ibin_yval) const
{
    IsOvalNotNull();
    int ret = IsValidIbinX(ibin_xval) * IsValidIbinY(ibin_yval);
    double oval = 0.0;
    if(1 == ret){
        long ibin = GetIbin(ibin_xval, ibin_yval);
        oval = GetOvalArr()->GetValElm(ibin);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xval(=%ld) or ibin_yval(=%ld)\n",
                ibin_xval, ibin_yval);
        MPrintErrClass(msg);
        abort();
    }
    return oval;
}


double HistData2d::GetOvalElmAtXY(double xval, double yval) const
{
    IsOvalNotNull();
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    double oval = 0.0;
    if(1 == ret){
        long ibin_x = GetIbinXFromX(xval);
        long ibin_y = GetIbinYFromY(yval);
        oval = GetOvalElm(ibin_x, ibin_y);
    } else {
        char msg[kLineSize];
        sprintf(msg, "bad xval(=%e) or yval(=%e)\n",
                xval, yval);
        MPrintErrClass(msg);
        abort();
    } 
    return oval;
}

// stat
double HistData2d::GetXvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double xval = GetBinCenterXFromIbin(ibin);
    return xval;
}
    
double HistData2d::GetXvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double xval = GetBinCenterXFromIbin(ibin);
    return xval;
}


double HistData2d::GetYvalAtOvalMin() const
{
    long ibin = GetOvalArr()->GetLocValMin();
    double yval = GetBinCenterYFromIbin(ibin);
    return yval;
}
    
double HistData2d::GetYvalAtOvalMax() const
{
    long ibin = GetOvalArr()->GetLocValMax();
    double yval = GetBinCenterYFromIbin(ibin);
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
        GetBinCenterXYFromIbin(ibin, &xval, &yval);
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


// calc_mode : "add", "integral", "amean", "min", "max"
HistData1d* const HistData2d::GenProjectX(long ibin_ylo, long ibin_yup,
                                          string calc_mode) const
{
    int ret = IsValidIbinY(ibin_ylo) * IsValidIbinY(ibin_yup);
    if(1 != ret){
        char msg[kLineSize];
        sprintf(msg, "bad ibin_ylo(=%ld) or ibin_yup(=%ld)\n",
                ibin_ylo, ibin_yup);
        MPrintErrClass(msg);
        abort();
    }
    
    HistData1d* h1d = new HistData1d;
    h1d->Init(nbin_xval_, xval_lo_, xval_up_);
    for(long ibin_xval = 0; ibin_xval < nbin_xval_; ibin_xval++){
        long nbin_tmp = ibin_yup - ibin_ylo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_yval = ibin_ylo; ibin_yval <= ibin_yup; ibin_yval++){
            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, GetBinWidthY(),
                   &val_proj);
        delete [] tmp_arr;
        h1d->SetOvalElm(ibin_xval, val_proj);
    }
    return h1d;
}

// calc_mode : "add", "integral", "amean", "min", "max"
HistData1d* const HistData2d::GenProjectY(long ibin_xlo, long ibin_xup,
                                          string calc_mode) const
{
    int ret = IsValidIbinX(ibin_xlo) * IsValidIbinX(ibin_xup);
    if(1 != ret){
        char msg[kLineSize];
        sprintf(msg, "bad ibin_xlo(=%ld) or ibin_xup(=%ld)\n",
                ibin_xlo, ibin_xup);
        MPrintErrClass(msg);
        abort();
    }

    HistData1d* h1d = new HistData1d;
    h1d->Init(nbin_yval_, yval_lo_, yval_up_);
    for(long ibin_yval = 0; ibin_yval < nbin_yval_; ibin_yval++){
        long nbin_tmp = ibin_xup - ibin_xlo + 1;
        double* tmp_arr = new double [nbin_tmp];
        long ibin_tmp = 0;
        for(long ibin_xval = ibin_xlo; ibin_xval <= ibin_xup; ibin_xval++){
            tmp_arr[ibin_tmp] = GetOvalElm(ibin_xval, ibin_yval);
            ibin_tmp ++;
        }
        double val_proj = 0.0;
        GetProject(nbin_tmp, tmp_arr,
                   calc_mode, GetBinWidthX(),
                   &val_proj);
        delete [] tmp_arr;
        h1d->SetOvalElm(ibin_yval, val_proj);
    }
    return h1d;
}


double HistData2d::GetOvalIntPolLin(double xval, double yval) const
{
    int ret = IsValidRangeX(xval) * IsValidRangeY(yval);
    if(1 != ret){
        char msg[kLineSize];
        sprintf(msg, "bad xval(=%e) or yval(=%e)\n",
                xval, yval);
        MPrintErrClass(msg);
        PrintInfo(stdout, "");
        abort();
    }
    double ans = 0.0;
    long index_xval = GetIbinX_WithHalfBinShifted(xval);
    long index_yval = GetIbinY_WithHalfBinShifted(yval);
    
    if (-1 < index_xval && index_xval < nbin_xval_ - 1 &&
        -1 < index_yval && index_yval < nbin_yval_ - 1   ){
        long index_xval0 = index_xval;
        long index_xval1 = index_xval0 + 1;
        long index_yval0 = index_yval;
        long index_yval1 = index_yval0 + 1;

        long index0 = index_xval0 + index_yval0 * nbin_xval_;
        long index1 = index0 + 1;
        long index2 = index0 + nbin_xval_ + 1;
        long index3 = index0 + nbin_xval_;
        
        ans = MirMath::IntPolLin(xval, yval,
                                  GetBinCenterXFromIbinX(index_xval0),
                                  GetBinCenterXFromIbinX(index_xval1),
                                  GetBinCenterYFromIbinY(index_yval0),
                                  GetBinCenterYFromIbinY(index_yval1),
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
    fprintf(fp, "# nbin_xval_  = %ld\n", nbin_xval_);
    fprintf(fp, "# xval_lo_    = %e\n", xval_lo_);
    fprintf(fp, "# xval_up_    = %e\n", xval_up_);
    fprintf(fp, "# nbin_yval_  = %ld\n", nbin_yval_);
    fprintf(fp, "# yval_lo_    = %e\n", yval_lo_);
    fprintf(fp, "# yval_up_    = %e\n", yval_up_);
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
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval,
                    yval_bin_center - offset_yval,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0);
        }
    } else if ("x,xe,y,ye,z" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval);
        }
    } else if ("x,y,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, 
                    yval_bin_center - offset_yval, 
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);            
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    xval_bin_center - offset_xval, GetBinWidthX()/2.,
                    yval_bin_center - offset_yval, GetBinWidthY()/2.,
                    GetOvalElm(ibin_x, ibin_y) - offset_oval, 0.0, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long ibin = 0; ibin < nbin; ibin ++){
            double xval_bin_center, yval_bin_center;
            GetBinCenterXYFromIbin(ibin, &xval_bin_center, &yval_bin_center);
            long ibin_x = GetIbinX(ibin);
            long ibin_y = GetIbinY(ibin);            
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

HistData2d* const HistData2d::GenHd2MaxInBin(long nbinx_new, long nbiny_new) const
{
    if(nbinx_new > GetNbinX()){
        MPrintErrClass("bad nbinx_new");
        abort();
    }
    if(nbinx_new < 1){
        MPrintErrClass("bad nbinx_new");
        abort();
    }
    if(0 != GetNbinX() % nbinx_new){
        MPrintErrClass("bad nbinx_new");
        abort();
    }

    if(nbiny_new > GetNbinY()){
        MPrintErrClass("bad nbiny_new");
        abort();
    }
    if(nbiny_new < 1){
        MPrintErrClass("bad nbiny_new");
        abort();
    }
    if(0 != GetNbinY() % nbiny_new){
        MPrintErrClass("bad nbiny_new");
        abort();
    }
    
    HistData2d* h2d_new = new HistData2d;
    h2d_new->Init(nbinx_new, GetXvalLo(), GetXvalUp(),
                  nbiny_new, GetYvalLo(), GetYvalUp());
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        double xval = GetBinCenterXFromIbin(ibin);
        double yval = GetBinCenterYFromIbin(ibin);
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        h2d_new->FillByMax(xval, yval, GetOvalElm(ibin_x, ibin_y) );
    }
    return h2d_new;
}


GraphData3d* const HistData2d::GenGraph3d() const
{
    long nbin = nbin_xval_ * nbin_yval_;
    double* xval_arr = NULL;
    double* yval_arr = NULL;
    long nbin_g3d;
    GenXYvalArr(&xval_arr, &yval_arr, &nbin_g3d);
    
    GraphData3d* g3d = new GraphData3d;
    g3d->Init();
    g3d->SetXvalArrDbl(nbin_g3d, xval_arr);
    g3d->SetYvalArrDbl(nbin_g3d, yval_arr);
    g3d->SetOvalArrDbl(nbin, GetOvalArrDbl());
    delete [] xval_arr;
    delete [] yval_arr;
    return g3d;
}


TH2D* const HistData2d::GenTH2D(double offset_xval,
                                double offset_yval,
                                double offset_oval,
                                string title_xaxis,
                                string title_yaxis,
                                string title_oaxis,
                                string style) const
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
    }
    char xtitle[kLineSize];
    if("def" == style){
        sprintf(xtitle, "%s (offset = %e)", title_xaxis.c_str(), offset_xval);
    } else if("pub" == style){
        sprintf(xtitle, "%s", title_xaxis.c_str());
    }
    th2d->SetXTitle(xtitle);

    char ytitle[kLineSize];
    if("def" == style){
        sprintf(ytitle, "%s (offset = %e)", title_yaxis.c_str(), offset_yval);
    } else if("pub" == style){
        sprintf(ytitle, "%s", title_yaxis.c_str());
    }
    th2d->SetYTitle(ytitle);

    char ztitle[kLineSize];
    if("def" == style){
        sprintf(ztitle, "%s (offset = %e)", title_oaxis.c_str(), offset_oval);
    } else if("pub" == style){
        sprintf(ztitle, "%s", title_oaxis.c_str());
    }
    th2d->SetZTitle(ztitle);
    
    return th2d;
}



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
    TH2D* th2d = GenTH2D(offset_xval, offset_yval, offset_oval,
                         title_xaxis, title_yaxis, title_oaxis,
                         style);
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
    TH2D* th2d = GenTH2D(offset_xval, offset_yval, offset_oval,
                         title_xaxis, title_yaxis, title_oaxis);
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



//
// generate HistData2d adding margin region in x and y directions
//

HistData2d* const HistData2d::GenHd2AddMargin(double margin_xval, double margin_yval) const
{
    long nbin_xval_margin = (long) ceil(margin_xval / GetBinWidthX());
    long nbin_yval_margin = (long) ceil(margin_yval / GetBinWidthY());
  
    double xval_lo_new = GetXvalLo() - nbin_xval_margin * GetBinWidthX();
    double xval_up_new = GetXvalUp() + nbin_xval_margin * GetBinWidthX();
    double yval_lo_new = GetYvalLo() - nbin_yval_margin * GetBinWidthY();
    double yval_up_new = GetYvalUp() + nbin_yval_margin * GetBinWidthY();
    long nbin_xval_new = GetNbinX() + 2 * nbin_xval_margin;
    long nbin_yval_new = GetNbinY() + 2 * nbin_yval_margin;

    HistData2d* hd2_new = new HistData2d;
    hd2_new->Init(nbin_xval_new, xval_lo_new, xval_up_new,
                  nbin_yval_new, yval_lo_new, yval_up_new);
    hd2_new->SetZero();

    for(long ibin = 0; ibin < GetNbin(); ibin++){
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        double xval = GetBinCenterXFromIbinX(ibin_x);
        double yval = GetBinCenterYFromIbinY(ibin_y);

        long ibin_x_new = hd2_new->GetIbinXFromX(xval);
        long ibin_y_new = hd2_new->GetIbinYFromY(yval);
        hd2_new->SetOvalElm(ibin_x_new,
                            ibin_y_new,
                            GetOvalElm(ibin_x, ibin_y));
    }
    return hd2_new;
}


GraphData2d* const HistData2d::GenRandomEvt(int rand_seed) const
{
    TRandom3* trand = new TRandom3(rand_seed);
    vector<double> xval_vec;
    vector<double> yval_vec;

    double tbinfwidth_x = GetBinWidthX();
    double tbinfwidth_y = GetBinWidthY();
    for(long ibin = 0; ibin < GetNbin(); ibin ++){
        long ibin_x = GetIbinX(ibin);
        long ibin_y = GetIbinY(ibin);
        double bin_center_x = GetBinCenterXFromIbinX(ibin_x);
        double bin_center_y = GetBinCenterYFromIbinY(ibin_y);
        
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

    GraphData2d* gdata2d = new GraphData2d;
    gdata2d->Init();
    gdata2d->SetXvalArrDbl(xval_vec);
    gdata2d->SetOvalArrDbl(yval_vec);

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
// protected
//

void HistData2d::Null()
{
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    long nbin_yval = 0;
    double yval_lo = 0.0;
    double yval_up = 0.0;
    SetInfo(nbin_xval, xval_lo, xval_up,
            nbin_yval, yval_lo, yval_up);
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void HistData2d::NewOvalArrAsDataArray1d()
{
    oval_arr_ = new DataArray1d;
}

void HistData2d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void HistData2d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

int HistData2d::IsValidIbinX(long ibin_xval) const
{
    int status = 0;
    if(ibin_xval < 0 || ibin_xval > GetNbinX() - 1){
        if(0 < g_flag_verbose){
            char msg[kLineSize];
            sprintf(msg, "bad ibin_xval (=%ld) against GetNbinX() (=%ld)",
                    ibin_xval, GetNbinX());
            MPrintWarnClass(msg);
        }
        status = 0;
    } else {
        status = 1;
    }
    return status;
}

int HistData2d::IsValidIbinY(long ibin_yval) const
{
    int status = 0;
    if(ibin_yval < 0 || ibin_yval > GetNbinY() - 1){
        if(0 < g_flag_verbose){
            char msg[kLineSize];
            sprintf(msg, "bad ibin_yval (=%ld) against GetNbinY() (=%ld)",
                    ibin_yval, GetNbinY());
            MPrintWarnClass(msg);
        }
        status = 0;
    } else {
        status = 1;
    }
    return status;
}

int HistData2d::IsValidRangeX(double xval) const
{
    int status = 0;
    if(xval < GetXvalLo() || GetXvalUp() < xval){
        if(0 < g_flag_verbose){        
            char msg[kLineSize];
            sprintf(msg, "bad xval (=%e), which is not within %e and %e.",
                    xval, GetXvalLo(), GetXvalUp());
            MPrintWarnClass(msg);
        }
        status = 0;
    } else {
        status = 1;
    }
    return status;
}

int HistData2d::IsValidRangeY(double yval) const
{
    int status = 0;
    if(yval < GetYvalLo() || GetYvalUp() < yval){
        if(0 < g_flag_verbose){        
            char msg[kLineSize];
            sprintf(msg, "bad yval (=%e), which is not within %e and %e.",
                    yval, GetYvalLo(), GetYvalUp());
            MPrintWarnClass(msg);
        }
        status = 0;
    } else {
        status = 1;
    }
    return status;
}

int HistData2d::IsOvalNotNull() const
{
    if(NULL == GetOvalArr()){
        MPrintErrClass("bad GetOvalArr() (=NULL)");
        abort();
    }
    return 1;
}

//
// private
//

// calc_mode: "add", "integral", "amean", "min", "max"
void HistData2d::GetProject(long ndata,
                            const double* const array,
                            string calc_mode, double bin_width,
                            double* const val_proj_ptr) const
{
    double val_proj ;
    if("add" == calc_mode){
        val_proj = MirMath::GetAdd(ndata, array);
    } else if ("integral" == calc_mode){
        val_proj = MirMath::GetAdd(ndata, array);
        val_proj *= bin_width;
    } else if ("amean" == calc_mode){
        double val_add = MirMath::GetAdd(ndata, array);
        val_proj = val_add / ndata;
    } else if ("min" == calc_mode){
        val_proj = MirMath::GetMin(ndata, array);
    } else if ("max" == calc_mode){
        val_proj = MirMath::GetMax(ndata, array);
    } else {
        MPrintErrClass("bad calc_mode");
        abort();
    }
    *val_proj_ptr = val_proj;
}


