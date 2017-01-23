#include "mir_graph2d.h"

//
// public
//

void GraphData2d::SetXvalArr(const DataArray1d* const val_arr)
{
    GetXvalArrNonConst()->Copy(val_arr);
}

void GraphData2d::SetOvalArr(const DataArray1d* const val_arr)
{
    GetOvalArrNonConst()->Copy(val_arr);
}

void GraphData2d::SetXvalArr(long ndata, const double* const val)
{
    GetXvalArrNonConst()->SetVal(ndata, val);
}

void GraphData2d::SetXvalArr(vector<double> val)
{
    GetXvalArrNonConst()->SetVal(val);
}

void GraphData2d::SetOvalArr(long ndata, const double* const val)
{
    GetOvalArrNonConst()->SetVal(ndata, val);
}

void GraphData2d::SetOvalArr(vector<double> val)
{
    GetOvalArrNonConst()->SetVal(val);
}

void GraphData2d::SetPoint(long idata, double xval, double oval)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetOvalArrNonConst()->SetValElm(idata, oval);
}

void GraphData2d::InitSetByFunc(const MirFunc* const func, const double* const par,
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

    Init(nbin_xval);
    DataArrayNerr1d* da1d_x = new DataArrayNerr1d;
    da1d_x->Init(nbin_xval);
    da1d_x->SetVal(xval_vec);
    DataArrayNerr1d* da1d_o = new DataArrayNerr1d;
    da1d_o->Init(nbin_xval);
    da1d_o->SetVal(oval_vec);
    SetXvalArr(da1d_x);
    SetOvalArr(da1d_o);
    delete da1d_x;
    delete da1d_o;
}

void GraphData2d::Copy(const GraphData2d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetNdata());
    SetFlagXvalSorted(org->GetFlagXvalSorted());
    SetXvalArr(org->GetXvalArr());
    SetOvalArr(org->GetOvalArr());
}


long GraphData2d::GetNdata() const
{
    long ndata = 0;
    if(GetXvalArr()->GetNdata() == GetOvalArr()->GetNdata()){
        ndata = GetXvalArr()->GetNdata();
    } else {
        char msg[kLineSize];
        sprintf(msg, "GetXvalArr()->GetNdata() != GetOvalArr()->GetNdata()");
        MPrintErrClass(msg);
        abort();
    }
    return ndata;
}

double GraphData2d::GetXvalAtOvalMin() const
{
    long loc_min = GetOvalArr()->GetLocValMin();
    return GetXvalArr()->GetValElm(loc_min);
}

double GraphData2d::GetXvalAtOvalMax() const
{
    long loc_max = GetOvalArr()->GetLocValMax();
    return GetXvalArr()->GetValElm(loc_max);
}

double GraphData2d::GetOvalAtXvalMin() const
{
    long loc_min = GetXvalArr()->GetLocValMin();
    return GetOvalArr()->GetValElm(loc_min);
}

double GraphData2d::GetOvalAtXvalMax() const
{
    long loc_max = GetXvalArr()->GetLocValMax();
    return GetOvalArr()->GetValElm(loc_max);
}


//
// output
//

void GraphData2d::Save(string outfile, string format,
                       double offset_xval, double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintInfo(fp);
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void GraphData2d::SaveData(string outfile, string format,
                           double offset_xval, double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_oval);
    fclose(fp);
}

void GraphData2d::PrintInfo(FILE* fp) const
{
    fprintf(fp, "#\n");
    fprintf(fp, "# ndata = %ld\n", GetNdata());
    fprintf(fp, "# flag_xval_sorted_ = %d\n", flag_xval_sorted_);
    fprintf(fp, "#\n");
    fprintf(fp, "\n");
}

// ichiji hokan

double GraphData2d::GetOvalIntPolLin(double xval) const
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
        ans = 0.0;
    } else {
        int index_near = TMath::BinarySearch(ndata, GetXvalArr()->GetVal(), xval);
        ans = MirMath::IntPolLin(xval,
                                  GetXvalElm(index_near),
                                  GetXvalElm(index_near + 1),
                                  GetOvalElm(index_near),
                                  GetOvalElm(index_near + 1) );
    }
    return ans;
}


double GraphData2d::GetOffsetXFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetXvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetXvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetXvalArr()->GetValAndErrMin() +
                   GetXvalArr()->GetValAndErrMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

double GraphData2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValAndErrMin() +
                   GetOvalArr()->GetValAndErrMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

int GraphData2d::IsEqualSpaceX() const
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
    return retval;
}


//
// static
//


void GraphData2d::ReadInfo(string file, int* flag_xval_sorted_ptr)
{
    int flag_xval_sorted = 0;
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileComment(file, &line_arr, &ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = 0;
        string* split_arr = NULL;
        MiStr::GenSplit(line_arr[idata], &ncolumn, &split_arr);
        if(4 != ncolumn){
            continue;
        }
        if("flag_xval_sorted_" == split_arr[1]){
            flag_xval_sorted = atoi(split_arr[3].c_str());
        }
        delete [] split_arr;
    }
    MiIolib::DelReadFile(line_arr);

    *flag_xval_sorted_ptr = flag_xval_sorted;
}

//
// protected
//

void GraphData2d::NullGraphData2d()
{
    if(NULL != xval_arr_) {delete xval_arr_; xval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
    flag_xval_sorted_ = 0;
}

void GraphData2d::NewXvalArrAsDataArrayNerr1d()
{
    xval_arr_ = new DataArrayNerr1d;
}

void GraphData2d::NewXvalArrAsDataArraySerr1d()
{
    xval_arr_ = new DataArraySerr1d;
}

void GraphData2d::NewXvalArrAsDataArrayTerr1d()
{
    xval_arr_ = new DataArrayTerr1d;
}

void GraphData2d::NewOvalArrAsDataArrayNerr1d()
{
    oval_arr_ = new DataArrayNerr1d;
}

void GraphData2d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void GraphData2d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

