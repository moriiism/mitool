#include "mir_graph2d_nerr.h"

//
// public
//

// Init

void GraphDataNerr2d::Init()
{
    NullGraphData2d();
    NewXvalArrAsDataArrayNerr1d();
    NewOvalArrAsDataArrayNerr1d();
    SetFlagXvalSorted(0);
}

// Init & Set
void GraphDataNerr2d::InitSet(const DataArray1d* const xval_arr,
                          const DataArray1d* const oval_arr,
                          int flag_xval_sorted)
{
    Init();
    Set(xval_arr, oval_arr, flag_xval_sorted);
}


// Set xval_arr and oval_arr
void GraphDataNerr2d::SetXvalOvalArr(const DataArray1d* const xval_arr,
                                 const DataArray1d* const oval_arr)
{
    GetXvalArrNonConst()->Copy(xval_arr);
    GetOvalArrNonConst()->Copy(oval_arr);
}


// Set xval_arr
void GraphDataNerr2d::SetXvalArr(const DataArray1d* const val_arr)
{
    GetXvalArrNonConst()->Copy(val_arr);
}

void GraphDataNerr2d::SetXvalArrDbl(long ndata, const double* const val)
{
    GetXvalArrNonConst()->InitSetVal(ndata, val);
}

void GraphDataNerr2d::SetXvalArrDbl(vector<double> val)
{
    GetXvalArrNonConst()->InitSetVal(val);
}

// Set oval_arr
void GraphDataNerr2d::SetOvalArr(const DataArray1d* const val_arr)
{
    GetOvalArrNonConst()->Copy(val_arr);
}

void GraphDataNerr2d::SetOvalArrDbl(long ndata, const double* const val)
{
    GetOvalArrNonConst()->InitSetVal(ndata, val);
}

void GraphDataNerr2d::SetOvalArrDbl(vector<double> val)
{
    GetOvalArrNonConst()->InitSetVal(val);
}

// Set point
void GraphDataNerr2d::SetPoint(long idata, double xval, double oval)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetOvalArrNonConst()->SetValElm(idata, oval);
}

// Init & Set by Func

void GraphDataNerr2d::InitSetByFunc(const MirFunc* const func, const double* const par,
                                long nbin_xval, double xval_lo, double xval_up,
                                string scale)
{
    vector<double> xval_vec;
    vector<double> oval_vec;
    HistInfo1d* hi1d = new HistInfo1d;
    hi1d->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    for(long ibin = 0; ibin < nbin_xval; ibin ++){
        double xval = hi1d->GetBinCenter(ibin, scale);
        xval_vec.push_back(xval);
        double xval_tmp[1];
        xval_tmp[0] = xval;
        double oval = func->Eval(xval_tmp, par);
        oval_vec.push_back(oval);
    }
    delete hi1d;
    Init();
    SetXvalArrDbl(xval_vec);
    SetOvalArrDbl(oval_vec);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    
}

void GraphDataNerr2d::Copy(const GraphDataNerr2d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMirObject(org);
    Init();
    Set(org);
}

GraphDataNerr2d* const GraphDataNerr2d::Clone() const
{
    GraphDataNerr2d* obj_new = new GraphDataNerr2d;
    obj_new->Copy(this);
    return obj_new;
}


void GraphDataNerr2d::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
        if(2 != ncolumn){
            MPrintWarnClass("ncolumn != 2");
        }
        istringstream iss(line_arr[idata]);
        double xval, oval;
        iss >> xval >> oval;
        SetPoint(idata, xval, oval);
    }
    MirIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");        
    }
}

void GraphDataNerr2d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    double xval, oval;
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(2 != ncolumn){
                MPrintWarnClass("ncolumn != 2");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval;
            SetPoint(idata, xval, oval);
        }
    } else {
        MPrintErrClass("bad format");
        abort();
    }
    MirIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
    
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


GraphDataNerr2d* const GraphDataNerr2d::GenGd2dByLoad(string file, string format)
{
    GraphDataNerr2d* gd2d = NULL;
    if("x,y" == format){
        gd2d = new GraphDataNerr2d;
    } else if("x,y,ye" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;        
    } else if("x,xe,y" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,xe,y,ye" == format){
        gd2d = new GraphDataSerr2d;
    } else if("x,xe,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;
    } else if("x,xe+,xe-,y" == format){
        gd2d = new GraphDataTerr2d;
    } else if("x,xe+,xe-,y,ye" == format){
        gd2d = new GraphDataTerr2d;        
    } else if("x,xe+,xe-,y,ye+,ye-" == format){
        gd2d = new GraphDataTerr2d;
    } else {
        MPrintErr("bad format");
        abort();
    }
    gd2d->Load(file, format);
    return gd2d;
}


void GraphDataNerr2d::ReadInfo(string file, int* flag_xval_sorted_ptr)
{
    int flag_xval_sorted = 0;
    
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
        if("flag_xval_sorted_" == split_arr[1]){
            flag_xval_sorted = atoi(split_arr[3].c_str());
        }
        delete [] split_arr;
    }
    MirIolib::DelReadFile(line_arr);

    *flag_xval_sorted_ptr = flag_xval_sorted;
}


void GraphDataNerr2d::Sort()
{
    if(1 == GetFlagXvalSorted()){
        MPrintInfoClass("It has been already sorted. Then return.");
        return;
    }
    if(NULL == GetXvalArr() || NULL == GetOvalArr()){
        MPrintErrClass("GetXvalArr() == NULL or GetOvalArr() == NULL");
        abort();
    }

    long ndata = GetNdata();
    double* xval_org = new double [ndata];
    double* oval_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        xval_org[idata] = GetXvalElm(idata);
        oval_org[idata] = GetOvalElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    TMath::Sort(ndata, xval_org, index, kFALSE);
  
    for(long idata = 0; idata < ndata; idata++){
        SetPoint(idata, xval_org[index[idata]], oval_org[index[idata]]);
    }

    delete [] xval_org; xval_org = NULL;
    delete [] oval_org; oval_org = NULL;
    delete [] index; index = NULL;

    SetFlagXvalSorted(1);
    if(0 < g_flag_verbose){
        MPrintInfoClass("sorted.");
    }
}



//
// stat
//

double GraphDataNerr2d::GetXvalAtOvalMin() const
{
    long loc_min = GetOvalArr()->GetLocValMin();
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return GetXvalArr()->GetValElm(loc_min);
}

double GraphDataNerr2d::GetXvalAtOvalMax() const
{
    long loc_max = GetOvalArr()->GetLocValMax();
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return GetXvalArr()->GetValElm(loc_max);
}

double GraphDataNerr2d::GetOvalAtXvalMin() const
{
    long loc_min = GetXvalArr()->GetLocValMin();
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return GetOvalArr()->GetValElm(loc_min);
}

double GraphDataNerr2d::GetOvalAtXvalMax() const
{
    long loc_max = GetXvalArr()->GetLocValMax();
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return GetOvalArr()->GetValElm(loc_max);
}


void GraphDataNerr2d::GetXRangeQdp(double* const low_ptr, double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetXvalArr()->GetValMin(), GetXvalArr()->GetValMax(), &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphDataNerr2d::GetORangeQdp(double* const low_ptr, double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetOvalArr()->GetValMin(), GetOvalArr()->GetValMax(), &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}


//
// output
//

void GraphDataNerr2d::Save(string outfile, string format,
                       double offset_xval, double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp);
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphDataNerr2d::SaveData(string outfile, string format,
                           double offset_xval, double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphDataNerr2d::PrintInfo(FILE* fp) const
{
    fprintf(fp, "#\n");
    fprintf(fp, "# ndata = %ld\n", GetNdata());
    fprintf(fp, "# flag_xval_sorted_ = %d\n", flag_xval_sorted_);
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
}

void GraphDataNerr2d::PrintData(FILE* fp, string format,
                            double offset_xval, double offset_oval) const
{
    long ndata = GetXvalArr()->GetNdata();
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0, 0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


TGraph* const GraphDataNerr2d::GenTGraph(double offset_xval, double offset_oval) const
{
    long ndata = GetNdata();
    double* xval_arr = new double [ndata];
    double* oval_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_arr[idata] = GetXvalElm(idata) - offset_xval;
        oval_arr[idata] = GetOvalElm(idata) - offset_oval;
    }
    TGraph* tgraph = new TGraph(ndata, xval_arr, oval_arr);
    delete [] xval_arr;
    delete [] oval_arr;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tgraph;
}


// ichiji hokan

double GraphDataNerr2d::GetOvalIntPolLin(double xval) const
{
    if(1 != GetFlagXvalSorted()){
        MPrintErrClass("1 != GetFlagXvalSorted()");
        abort();
    }
    long ndata = GetNdata();
    if(ndata < 2){
        MPrintErrClass("bad ndata");
        abort();
    }

    double ans = 0.0;    
    if( xval < GetXvalElm(0) || GetXvalElm(ndata - 1) < xval ){
        if(0 < g_flag_verbose){        
            MPrintWarnClass("bad xval, then just return 0.0");
        }
        ans = 0.0;
    } else {
        int index_near = TMath::BinarySearch(ndata, GetXvalArrDbl(), xval);
        ans = MirMath::IntPolLin(xval,
                                  GetXvalElm(index_near),
                                  GetXvalElm(index_near + 1),
                                  GetOvalElm(index_near),
                                  GetOvalElm(index_near + 1) );
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return ans;
}


// trapezoid approximation

double GraphDataNerr2d::GetIntegral(double xval_lo, double xval_up) const
{
    if(1 != GetFlagXvalSorted()){
        MPrintErrClass("1 != GetFlagXvalSorted()");
        abort();
    }
    long ndata = GetNdata();
    if(ndata < 2){
        MPrintErrClass("ndata < 2");
        abort();
    }
    if(xval_lo < GetXvalElm(0) || GetXvalElm(ndata - 1) < xval_lo ){
        MPrintErrClass("xval_lo is not within the graph range.");
        abort();
    }
    if(xval_up < GetXvalElm(0) || GetXvalElm(ndata - 1) < xval_up ){
        MPrintErrClass("xval_up is not within the graph range.");
        abort();
    }
    
    double ans = 0.0;
    if(xval_lo < xval_up){
        ans = GetIntegralInner(xval_lo, xval_up);
    } else if (xval_lo > xval_up){
        ans = -1 * GetIntegralInner(xval_up, xval_lo);
    } else {
        ans = 0.0;
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return ans;
}

double GraphDataNerr2d::GetOffsetXFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetXvalArr()->GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetXvalArr()->GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetXvalArr()->GetValMin() + GetXvalArr()->GetValMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

double GraphDataNerr2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValMin() + GetOvalArr()->GetValMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


int GraphDataNerr2d::IsEqualSpaceX() const
{
    int retval = 1;
    long ndata = GetNdata();
    if(ndata < 3){
        MPrintInfoClass("ndata < 3, then equal spacing is not defined, but return 1.");
        retval = 1;
        return retval;
    }
    double delta_xval0 = GetXvalElm(1) - GetXvalElm(0);
    for(long idata = 1; idata < ndata - 1; idata ++){
        double delta_xval_this = GetXvalElm(idata + 1) - GetXvalElm(idata);
        if( fabs(delta_xval_this - delta_xval0) > DBL_MIN ){
            retval = 0;
            return retval;
        }
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return retval;
}


//
// protected
//

void GraphDataNerr2d::Null()
{
    if(NULL != xval_arr_) {delete xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
    flag_xval_sorted_ = 0;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphDataNerr2d::NewXvalArrAsDataArray1d()
{
    xval_arr_ = new DataArray1d;
}

void GraphDataNerr2d::NewXvalArrAsDataArraySerr1d()
{
    xval_arr_ = new DataArraySerr1d;
}

void GraphDataNerr2d::NewXvalArrAsDataArrayTerr1d()
{
    xval_arr_ = new DataArrayTerr1d;
}


void GraphDataNerr2d::NewOvalArrAsDataArray1d()
{
    oval_arr_ = new DataArray1d;
}

void GraphDataNerr2d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void GraphDataNerr2d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

// 
// private
//

double GraphDataNerr2d::GetIntegralInner(double xval_lo, double xval_up) const
{
    if(1 != GetFlagXvalSorted()){
        MPrintErrClass("1 != GetFlagXvalSorted()");
        abort();
    }
    if(xval_lo > xval_up){
        MPrintErrClass("xval_lo > xval_up");
        abort();
    }
    double oval_lo = GetOvalIntPolLin(xval_lo);
    double oval_up = GetOvalIntPolLin(xval_up);

    Interval* interval = new Interval;
    interval->InitSet(xval_lo, xval_up);
    GraphDataNerr2d* g2d_sel = new GraphDataNerr2d;
    GraphDataNerr2dOpe::GetSelectG2dByInterval(this,
                                           interval,
                                           g2d_sel);

    // add two points
    vector<double> vec_xval;
    vector<double> vec_oval;
    vec_xval.push_back(xval_lo);
    vec_oval.push_back(oval_lo);
    for(int idata = 0; idata < g2d_sel->GetNdata(); idata++){
        vec_xval.push_back(g2d_sel->GetXvalElm(idata));
        vec_oval.push_back(g2d_sel->GetOvalElm(idata));
    }
    vec_xval.push_back(xval_up);
    vec_oval.push_back(oval_up);
    GraphDataNerr2d* g2d_new = new GraphDataNerr2d;
    g2d_new->Init();
    g2d_new->SetXvalArrDbl(vec_xval);
    g2d_new->SetOvalArrDbl(vec_oval);
    delete interval;
    delete g2d_sel;
    g2d_new->Sort();

    double ans = g2d_new->GetIntegralByTrapezoidApprox();
    delete g2d_new;
    return ans;
}

double GraphDataNerr2d::GetIntegralByTrapezoidApprox() const
{
    if(1 != GetFlagXvalSorted()){
        MPrintErrClass("1 != GetFlagXvalSorted()");
        abort();
    }
    long ndata = GetNdata();
    if(ndata < 2){
        MPrintErrClass("ndata < 2");
        abort();
    }
    double ans = 0.0;
    for(int idata = 0; idata < ndata - 1; idata ++){
        ans += ( GetOvalElm(idata) + GetOvalElm(idata + 1) ) *
            ( GetXvalElm(idata + 1) - GetXvalElm(idata) ) / 2.0;
    }
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    
    return ans;
}
