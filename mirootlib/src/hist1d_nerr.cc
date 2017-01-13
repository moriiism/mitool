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
    SetInfo(nbin_xval, xval_lo, xval_up);
    NewOvalArrAsDataArray1d();
}

void HistData1d::Init(const HistInfo1d* const hist_info)
{
    Init(hist_info->GetNbin(),
         hist_info->GetLo(),
         hist_info->GetUp());
}

// Set
void HistData1d::Set(const HistData1d* const org)
{
    CopyMxkwObject(org);
    Set(org->GetNbinX(),
        org->GetXvalLo(),
        org->GetXvalUp(),
        org->GetOvalArr());
}

void HistData1d::Set(long nbin_xval, double xval_lo, double xval_up,
                     const DataArray1d* const oval_arr)
{
    SetInfo(nbin_xval, xval_lo, xval_up);
    SetData(oval_arr);
}

// Set Info
void HistData1d::SetInfo(long nbin_xval,
                         double xval_lo,
                         double xval_up)
{
    nbin_xval_ = nbin_xval;
    xval_lo_   = xval_lo;
    xval_up_   = xval_up;
}

// SetData
void HistData1d::SetData(const DataArray1d* const oval_arr)
{
    if(GetNbinX() != oval_arr->GetNdata()){
        MPrintErrClass("GetNbinX() != oval_arr->GetNdata()");
        abort();
    }
    GetOvalArrNonConst()->Set(oval_arr);
}

void HistData1d::SetData(long nbin_xval, const double* const oval)
{
    if(GetNbinX() != nbin_xval){
        MPrintErrClass("GetNbinX() != nbin_xval");
        abort();
    }
    GetOvalArrNonConst()->SetVal(nbin_xval, oval);
}

// InitSet
void HistData1d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                         const DataArray1d* const oval_arr)
{
    Init(nbin_xval, xval_lo, xval_up);
    Set(nbin_xval, xval_lo, xval_up, oval_arr);
}

void HistData1d::InitSet(long nbin_xval, double xval_lo, double xval_up,
                         const double* const oval)
{
    Init(nbin_xval, xval_lo, xval_up);
    SetData(nbin_xval, oval);
}


void HistData1d::InitSet(const TH1D* const th1d)
{
    Null();

    long nbin_xval = th1d->GetNbinsX();
    double xval_lo = th1d->GetXaxis()->GetXmin();
    double xval_up = th1d->GetXaxis()->GetXmax();
    Init(nbin_xval, xval_lo, xval_up);

    double* oval = new double [nbin_xval];
    for(long ibin = 0; ibin < nbin_xval; ibin ++){
        oval[ibin] = th1d->GetBinContent(ibin + 1);
    }
    SetData(nbin_xval, oval);
    delete [] oval;
}

void HistData1d::SetOvalElm(long ibin, double oval)
{
    IsOvalNotNull();
    GetOvalArrNonConst()->SetValElm(ibin, oval);
}

void HistData1d::Fill(double xval)
{
    IsOvalNotNull();    
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->Fill(ibin);
}

void HistData1d::Fill(double xval, double weight)
{
    IsOvalNotNull();    
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->Fill(ibin, weight);
}

void HistData1d::FillByMax(double xval, double oval)
{
    IsOvalNotNull();
    long ibin = GetIbin(xval);
    GetOvalArrNonConst()->FillByMax(ibin, oval);
}

void HistData1d::FillByMin(double xval, double oval)
{
    IsOvalNotNull();
    long ibin = GetIbin(xval);    
    GetOvalArrNonConst()->FillByMin(ibin, oval);
}


void HistData1d::SetZero()
{
    IsOvalNotNull();
    GetOvalArrNonConst()->SetZero();
}

void HistData1d::SetOne()
{
    IsOvalNotNull();    
    GetOvalArrNonConst()->SetOne();
}

void HistData1d::SetConst(double constant)
{
    IsOvalNotNull();        
    GetOvalArrNonConst()->SetConst(constant);
}


void HistData1d::SetOneAtInterval(const Interval* const interval)
{
    IsOvalNotNull();            
    if(1 != interval->IsOrdered()){
        MPrintErrClass("bad interval.");
        abort();
    }

    Interval* interval_hist = new Interval;
    interval_hist->InitSet(xval_lo_, xval_up_);
    Interval* interval_and = new Interval;
    interval_and->And(interval, interval_hist);

    GetOvalArrNonConst()->SetZero();
    for(long iterm = 0; iterm < interval_and->GetNterm(); iterm++){
        double xlo = interval_and->GetTstartElm(iterm);
        double xup = interval_and->GetTstopElm(iterm);
        printf("GetIbin(xlo) = %ld\n", GetIbin(xlo));
        printf("GetIbin(xup) = %ld\n", GetIbin(xup));
        long ibin_x_lo = (long) MxkwMath::GetMax((double) GetIbin(xlo), 0.0);
        long ibin_x_up = (long) MxkwMath::GetMin((double) GetIbin(xup), (double) (nbin_xval_ - 1) );
        
        for(long ibin = ibin_x_lo; ibin <= ibin_x_up; ibin ++){
            SetOvalElm(ibin, 1);
        }
    }

    delete interval_hist;
    delete interval_and;
}


void HistData1d::SetByFunc(const MxkwFunc* const func, const double* const par)
{
    for(int ibin = 0; ibin < GetNbinX(); ibin ++){
        double xval = GetBinCenterX(ibin);
        double xval_tmp[1];
        xval_tmp[0] = xval;
        double oval = func->Eval(xval_tmp, par);
        SetOvalElm(ibin, oval);
    }
}


void HistData1d::SetByGraphData2d(const GraphData2d* const g2d)
{
    HistData1d* h1d_sum = new HistData1d;
    h1d_sum->Init(GetNbinX(), GetXvalLo(), GetXvalUp());
    HistData1d* h1d_num = new HistData1d;
    h1d_num->Init(GetNbinX(), GetXvalLo(), GetXvalUp());
    for(long idata = 0; idata < g2d->GetNdata(); idata ++){
        h1d_sum->Fill(g2d->GetXvalElm(idata), g2d->GetOvalElm(idata));
        h1d_num->Fill(g2d->GetXvalElm(idata));
    }
    HistData1d* h1d_amean = new HistData1d;
    h1d_amean->Init(GetNbinX(), GetXvalLo(), GetXvalUp());
    vector<long> index_bad_vec;
    h1d_amean->Div(h1d_sum, h1d_num, &index_bad_vec);
    Set(h1d_amean);

    delete h1d_sum;
    delete h1d_num;
    delete h1d_amean;
}

// Init & Set by hist1d, only if xval_arr of graph2d is equally-spaced.
void HistData1d::InitSetByGraphData2d(const GraphData2d* const g2d)
{
    if(1 != g2d->GetFlagXvalSorted()){
        MPrintErrClass("Not soted.");
        abort();
    }
    if(1 != g2d->IsEqualSpaceX()){
        MPrintErrClass("Not equally-spaced.");
        abort();
    }
    long npoint = g2d->GetNdata();
    if(npoint < 2){
        MPrintErrClass("npoint < 2.");
        abort();
    }

    Null();
    long nbin_xval = npoint;
    double xval_min = g2d->GetXvalArr()->GetValMin();
    double xval_max = g2d->GetXvalArr()->GetValMax();
    double delta_xval = (xval_max - xval_min) / (npoint - 1);
    double xval_lo = xval_min - 0.5 * delta_xval;
    double xval_up = xval_max + 0.5 * delta_xval;
    Init(nbin_xval, xval_lo, xval_up);
    SetData(g2d->GetOvalArr());
}

void HistData1d::Copy(const HistData1d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMxkwObject(org);
    Init(org->GetNbinX(),
         org->GetXvalLo(),
         org->GetXvalUp());
    Set(org);
}

HistData1d* const HistData1d::Clone() const
{
    HistData1d* obj_new = new HistData1d;
    obj_new->Copy(this);
    return obj_new;
}

void HistData1d::Load(string file)
{
    Null();

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
    GraphData2d* gdata2d = new GraphData2d;
    gdata2d->Load(file, format);
    for(long idata = 0; idata < gdata2d->GetNdata(); idata++){
        long ibin = GetIbin(gdata2d->GetXvalElm(idata));
        SetOvalElm(ibin, gdata2d->GetOvalElm(idata) );
    }
    delete gdata2d;

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


HistData1d* const HistData1d::GenHd1dByLoad(string file)
{
    HistData1d* hd1d = NULL;
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    ReadInfo(file, &nbin_xval, &xval_lo, &xval_up, &format);
    
    if("x,y" == format){
        hd1d = new HistData1d;
    } else if("x,y,ye" == format){
        hd1d = new HistDataSerr1d;
    } else if("x,y,ye+,ye-" == format){
        hd1d = new HistDataTerr1d;        
    } else {
        MPrintErr("bad format");
        abort();
    }
    hd1d->Load(file);
    return hd1d;
}
    
void HistData1d::ReadInfo(string file, 
                          long* nbin_xval_ptr,
                          double* xval_lo_ptr,
                          double* xval_up_ptr,
                          string* format_ptr)
{
    long nbin_xval = 0;
    double xval_lo = 0.0;
    double xval_up = 0.0;
    string format = "";
    
    string* line_arr = NULL;
    long ndata = 0;
    MxkwIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MxkwStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
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
        if("format" == split_arr[1]){
            format = split_arr[3];
        }        
        
        delete [] split_arr;
    }
    MxkwIolib::DelReadFile(line_arr);

    *nbin_xval_ptr = nbin_xval;
    *xval_lo_ptr = xval_lo;
    *xval_up_ptr = xval_up;
    *format_ptr = format;

    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


//
// operation
//

void HistData1d::Not(const HistData1d* const hist_data)
{
    Init(hist_data->GetNbinX(),
         hist_data->GetXvalLo(),
         hist_data->GetXvalUp());
    GetOvalArrNonConst()->Not(hist_data->GetOvalArr());
}

void HistData1d::Scale(const HistData1d* const hist_data,
                       double scale, double offset)
{
    Init(hist_data->GetNbinX(),
         hist_data->GetXvalLo(),
         hist_data->GetXvalUp());
    GetOvalArrNonConst()->Scale(hist_data->GetOvalArr(),
                                scale, offset);
}

void HistData1d::Min(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->Min(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData1d::Min(const HistData1d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::Max(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->Max(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}


void HistData1d::Max(const HistData1d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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


void HistData1d::Add(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->Add(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData1d::Add(const HistData1d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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



void HistData1d::Sub(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->Sub(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

void HistData1d::Mul(const HistData1d* const hist_data1,
                     const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->Mul(hist_data1->GetOvalArr(),
                              hist_data2->GetOvalArr());
}

int HistData1d::Div(const HistData1d* const hist_data_num,
                    const HistData1d* const hist_data_den,
                    vector<long>* const index_bad_vec_ptr)
{
    Init(hist_data_num->GetNbinX(),
         hist_data_num->GetXvalLo(),
         hist_data_num->GetXvalUp());

    vector<long> index_bad_vec;
    GetOvalArrNonConst()->Div(hist_data_num->GetOvalArr(),
                              hist_data_den->GetOvalArr(),
                              &index_bad_vec);
    *index_bad_vec_ptr = index_bad_vec;
    return index_bad_vec.size();
}

void HistData1d::AMean(const HistData1d* const hist_data1,
                       const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->AMean(hist_data1->GetOvalArr(),
                                hist_data2->GetOvalArr());
}

void HistData1d::AMean(const HistData1d* const* const hist_data_arr,
                       int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::SubAddRatio(const HistData1d* const hist_data1,
                             const HistData1d* const hist_data2)
{
    Init(hist_data1->GetNbinX(),
         hist_data1->GetXvalLo(),
         hist_data1->GetXvalUp());
    GetOvalArrNonConst()->SubAddRatio(hist_data1->GetOvalArr(),
                                      hist_data2->GetOvalArr());
}


void HistData1d::Variance(const HistData1d* const* const hist_data_arr,
                          int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::Stddev(const HistData1d* const* const hist_data_arr,
                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::UnbiasedVariance(const HistData1d* const* const hist_data_arr,
                                  int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::SqrtOfUnbiasedVariance(const HistData1d* const* const hist_data_arr,
                                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::RMS(const HistData1d* const* const hist_data_arr,
                     int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

void HistData1d::Median(const HistData1d* const* const hist_data_arr,
                        int nhist)
{
    Init(hist_data_arr[0]->GetNbinX(),
         hist_data_arr[0]->GetXvalLo(),
         hist_data_arr[0]->GetXvalUp());
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

// get internal of oval_arr_
const double* const HistData1d::GetOvalArrDbl() const
{
    IsOvalNotNull();
    return GetOvalArr()->GetVal();
}


double HistData1d::GetOvalElm(long ibin) const
{
    IsOvalNotNull();
    return GetOvalArr()->GetValElm(ibin);
}

double HistData1d::GetOvalElmAtX(double xval) const
{
    long ibin = GetIbin(xval);
    return GetOvalElm(ibin);
}

double HistData1d::GetXvalAtOvalMin() const
{
    return GetBinCenterX(GetOvalArr()->GetLocValMin());
}
    
double HistData1d::GetXvalAtOvalMax() const
{
    return GetBinCenterX(GetOvalArr()->GetLocValMax());
}

long HistData1d::GetIbin(double xval) const
{
    double delta_xval = (xval_up_ - xval_lo_) / nbin_xval_;
    long ibin = static_cast<long>( floor((xval - xval_lo_) / delta_xval) );
    return ibin;
}

long HistData1d::GetIbinWithHalfBinShifted(double xval) const
{
    double delta_xval = (xval_up_ - xval_lo_) / nbin_xval_;
    double xval_lo_half_bin_shifted = xval_lo_ + 0.5 * delta_xval;
    long ibin = static_cast<long>( floor((xval - xval_lo_half_bin_shifted) / delta_xval) );
    return ibin;
}

double HistData1d::GetBinCenterX(long ibin) const
{
    double delta_xval = (xval_up_ - xval_lo_) / nbin_xval_;
    double bin_center = xval_lo_ + (ibin + 0.5) * delta_xval;
    return bin_center;
}

double HistData1d::GetBinLoX(long ibin) const
{
    double delta_xval = (xval_up_ - xval_lo_) / nbin_xval_;
    double bin_lo = xval_lo_ + ibin * delta_xval;
    return bin_lo;
}

double HistData1d::GetBinUpX(long ibin) const
{
    double delta_xval = (xval_up_ - xval_lo_) / nbin_xval_;
    double bin_up = xval_lo_ + (ibin + 1) * delta_xval;
    return bin_up;
}

double HistData1d::GetOvalIntPolLin(double xval) const
{
    //int ret = IsValidRangeX(xval);
    //if(1 != ret){
    //    char msg[kLineSize];
    //    sprintf(msg, "bad xval(=%e)", xval);
    //    MPrintErrClass(msg);
    //    abort();
    //}
    double ans = 0.0;
    long index_xval = GetIbinWithHalfBinShifted(xval);
    if (-1 < index_xval && index_xval < nbin_xval_ - 1){
        ans = MxkwMath::IntPolLin(xval,
                                  GetBinCenterX(index_xval),
                                  GetBinCenterX(index_xval + 1),
                                  GetOvalElm(index_xval),
                                  GetOvalElm(index_xval + 1) );
    } else {
        if(0 < g_flag_verbose){
            MPrintWarnClass("bad xval, then just return 0.0");
        }
        ans = 0.0;
    }
    return ans;
}


double HistData1d::GetIntegral(double xval_lo, double xval_up) const
{
    GraphData2d* g2d_out = GenGraph2d();
    double ans = g2d_out->GetIntegral(xval_lo, xval_up);
    delete g2d_out;
    return ans;
}

void HistData1d::GenXvalArr(double** const xval_arr_ptr,
                            long* const nbin_ptr) const
{
    double* xval_arr = new double [nbin_xval_];
    for(long ibin = 0; ibin < nbin_xval_; ibin++){
        xval_arr[ibin] = GetBinCenterX(ibin);
    }
    *xval_arr_ptr = xval_arr;
    *nbin_ptr = nbin_xval_;
}

void HistData1d::GenOvalArr(double** const oval_arr_ptr,
                            long* const nbin_ptr) const
{
    double* oval_arr = new double [nbin_xval_];
    for(long ibin = 0; ibin < nbin_xval_; ibin++){
        oval_arr[ibin] = GetOvalArr()->GetValElm(ibin);
    }
    *oval_arr_ptr = oval_arr;
    *nbin_ptr = nbin_xval_;
}


//
// output
//

void HistData1d::Save(string outfile, string format,
                      double offset_xval,
                      double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp, format);
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void HistData1d::SaveData(string outfile, string format,
                          double offset_xval,
                          double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void HistData1d::PrintInfo(FILE* fp, string format) const
{
    fprintf(fp, "#\n");
    fprintf(fp, "# nbin_xval_  = %ld\n", nbin_xval_);
    fprintf(fp, "# xval_lo_    = %e\n", xval_lo_);
    fprintf(fp, "# xval_up_    = %e\n", xval_up_);
    fprintf(fp, "# format      = %s\n", format.c_str());
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
}


void HistData1d::PrintData(FILE* fp, string format,
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
                    0.0);
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    0.0);
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval, GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
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
                    GetOvalElm(ibin) - offset_oval, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long ibin = 0; ibin < nbin_xval; ibin ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetBinCenterX(ibin) - offset_xval,
                    GetBinWidth()/2., -1 * GetBinWidth()/2.,
                    GetOvalElm(ibin) - offset_oval, 0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}

void HistData1d::SaveRoot(string outfile,
                          double offset_xval,
                          double offset_oval) const
{
    TFile* tfile = new TFile(outfile.c_str(), "new");
    TH1D* th1d = GenTH1D(offset_xval, offset_oval);
    th1d->Write();
    delete th1d;
    delete tfile;
}


HistData1d* const HistData1d::GenHd1MaxInBin(long nbin_new) const
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

    HistData1d* h1d_new = new HistData1d;
    h1d_new->Init(nbin_new, GetXvalLo(), GetXvalUp());
  
    for(long ibin = 0; ibin < GetNbinX(); ibin ++){
        h1d_new->FillByMax( GetBinCenterX(ibin), GetOvalElm(ibin) );
    }

    return h1d_new;
}

GraphData2d* const HistData1d::GenGraph2d() const
{
    double* xval_arr = NULL;
    long nbin_g2d;
    GenXvalArr(&xval_arr, &nbin_g2d);

    GraphData2d* g2d = new GraphData2d;
    g2d->Init();
    g2d->SetXvalArrDbl(nbin_g2d, xval_arr);
    g2d->SetOvalArrDbl(nbin_g2d, GetOvalArrDbl());
    g2d->SetFlagXvalSorted(1);
    delete [] xval_arr;
    return g2d;
}

TH1D* const HistData1d::GenTH1D(double offset_xval,
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
    for(long ibin = 0; ibin < nbin_xval_; ibin++){
        double xval = GetBinCenterX(ibin);
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

void HistData1d::MkTH1Fig(string outfig,
                          MxkwRootTool* const root_tool,
                          double offset_xval,
                          double offset_oval) const
{
    TH1D* th1d = GenTH1D(offset_xval, offset_oval);
    th1d->Draw();
    root_tool->GetTCanvas()->Print(outfig.c_str());
    delete th1d;
}

void HistDataNerr1d::GetORangeQdp(double* const low_ptr,
                                  double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetOvalArr()->GetValMin(),
                         GetOvalArr()->GetValMax(),
                         &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
}

double HistDataNerr1d::GetOffsetOFromTag(string offset_tag) const
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
