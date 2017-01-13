#include "mir_graph2d_serr.h"

//
// public
//

// init

void GraphDataSerr2d::Init()
{
    NullGraphData2d();
    NewXvalArrAsDataArraySerr1d();
    NewOvalArrAsDataArraySerr1d();
    SetFlagXvalSorted(0);
}

// xval
void GraphDataSerr2d::SetXvalAndSerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetXvalArrNonConst()->InitSetValAndSerr(ndata, val, val_serr);
}

void GraphDataSerr2d::SetXvalAndSerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetXvalArrNonConst()->InitSetValAndSerr(val, val_serr);
}

// oval
void GraphDataSerr2d::SetOvalAndSerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetOvalArrNonConst()->InitSetValAndSerr(ndata, val, val_serr);
}

void GraphDataSerr2d::SetOvalAndSerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetOvalArrNonConst()->InitSetValAndSerr(val, val_serr);
}


void GraphDataSerr2d::SetPoint(long idata,
                               double xval, double xval_serr,
                               double oval, double oval_serr)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValSerrElm(idata, xval_serr);
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValSerrElm(idata, oval_serr);
}

void GraphDataSerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataSerr2d* const GraphDataSerr2d::Clone() const
{
    GraphDataSerr2d* obj_new = new GraphDataSerr2d;
    obj_new->Copy(this);
    return obj_new;
}



void GraphDataSerr2d::Load(string file)
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
        if(4 != ncolumn){
            MPrintWarnClass("ncolumn != 4");
        }
        istringstream iss(line_arr[idata]);
        double xval, xval_serr, oval, oval_serr;
        iss >> xval >> xval_serr >> oval >> oval_serr;
        SetPoint(idata, xval, xval_serr, oval, oval_serr);
    }
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void GraphDataSerr2d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    double xval, xval_serr, oval, oval_serr;
    if("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MPrintWarnClass("ncolumn != 4");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval >> oval_serr;
            SetPoint(idata, xval, xval_serr, oval, oval_serr);
        }
    } else if("x,y,ye" == format){
        xval_serr = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MPrintWarnClass("ncolumn != 3");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval >> oval_serr;
            SetPoint(idata, xval, xval_serr, oval, oval_serr);
        }
    } else if("x,xe,y" == format){
        oval_serr = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MPrintWarnClass("ncolumn != 3");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval;
            SetPoint(idata, xval, xval_serr, oval, oval_serr);
        }
    } else if("x,y" == format){
        xval_serr = 0.0;
        oval_serr = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(2 != ncolumn){
                MPrintWarnClass("ncolumn != 2");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval;
            SetPoint(idata, xval, xval_serr, oval, oval_serr);
        }
    } else {
        MPrintErrClass("bad format");
        abort();
    }
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void GraphDataSerr2d::Sort()
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
    double* xval_org      = new double [ndata];
    double* xval_serr_org = new double [ndata];
    double* oval_org      = new double [ndata];
    double* oval_serr_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        xval_org[idata]      = GetXvalElm(idata);
        xval_serr_org[idata] = GetXvalSerrElm(idata);
        oval_org[idata]      = GetOvalElm(idata);    
        oval_serr_org[idata] = GetOvalSerrElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    TMath::Sort(ndata, xval_org, index, kFALSE);

    for(long idata = 0; idata < ndata; idata++){
        SetPoint(idata,
                 xval_org[index[idata]], xval_serr_org[index[idata]],
                 oval_org[index[idata]], oval_serr_org[index[idata]]);
    }

    delete [] xval_org;
    delete [] xval_serr_org;
    delete [] oval_org;
    delete [] oval_serr_org;
    delete [] index;
  
    SetFlagXvalSorted(1);
    if(0 < g_flag_verbose){
        MPrintInfoClass("sorted.");
    }
}



// get

const DataArraySerr1d* const GraphDataSerr2d::GetXvalArr() const
{
    const DataArray1d* xval_arr = GraphData2d::GetXvalArr();
    return dynamic_cast<const DataArraySerr1d*>(xval_arr);
}
    
const DataArraySerr1d* const GraphDataSerr2d::GetOvalArr() const
{
    const DataArray1d* oval_arr = GraphData2d::GetOvalArr();
    return dynamic_cast<const DataArraySerr1d*>(oval_arr);
}


// get Range Qdp

void GraphDataSerr2d::GetXRangeQdp(double* const low_ptr, double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetXvalArr()->GetValAndErrMin(), GetXvalArr()->GetValAndErrMax(), &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphDataSerr2d::GetORangeQdp(double* const low_ptr, double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetOvalArr()->GetValAndErrMin(), GetOvalArr()->GetValAndErrMax(), &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}



//
// output
//

void GraphDataSerr2d::PrintData(FILE* fp, string format,
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
                    GetOvalSerrElm(idata));
        }
    } else if ("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalSerrElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalSerrElm(idata));
        }
    } else if ("x,xe,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalSerrElm(idata),
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalSerrElm(idata), -1 * GetXvalSerrElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalSerrElm(idata), -1 * GetOvalSerrElm(idata));
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

TGraphErrors* const GraphDataSerr2d::GenTGraph(double offset_xval,
                                               double offset_yval) const
{
    long ndata = GetNdata();
    double* xval_arr = new double [ndata];
    double* oval_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_arr[idata] = GetXvalElm(idata) - offset_xval;
        oval_arr[idata] = GetOvalElm(idata) - offset_yval;
    }    
    TGraphErrors* tgraph = new TGraphErrors(ndata,
                                            xval_arr,
                                            oval_arr,
                                            GetXvalSerrArrDbl(),
                                            GetOvalSerrArrDbl());
    delete [] xval_arr;
    delete [] oval_arr;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tgraph;
}

Interval* const GraphDataSerr2d::GenInterval() const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        tstart_vec.push_back(GetXvalElm(idata) - GetXvalSerrElm(idata));
        tstop_vec.push_back(GetXvalElm(idata) + GetXvalSerrElm(idata));
    }

    Interval* interval = new Interval;
    interval->InitSet(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(), term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}

Interval* const GraphDataSerr2d::GenIntervalAboveThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) > threshold){
            tstart_vec.push_back(GetXvalElm(idata) - GetXvalSerrElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalSerrElm(idata));
        }
    }

    Interval* interval = new Interval;
    interval->InitSet(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(), term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}

Interval* const GraphDataSerr2d::GenIntervalBelowThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) < threshold){
            tstart_vec.push_back(GetXvalElm(idata) - GetXvalSerrElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalSerrElm(idata));
        }
    }

    Interval* interval = new Interval;
    interval->InitSet(tstart_vec, tstop_vec);
    double* term_half_width_arr = interval->GenTermHalfWidth();
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(), term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}

double GraphDataSerr2d::GetOffsetXFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetXvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetXvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetXvalArr()->GetValAndErrMin() + GetXvalArr()->GetValAndErrMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

double GraphDataSerr2d::GetOffsetOFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetOvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetOvalArr()->GetValAndErrMin() + GetOvalArr()->GetValAndErrMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

void GraphDataSerr2d::GetValBinned(vector<double> xval_vec,
                                   vector<double> xval_serr_vec,
                                   vector<double> oval_vec,
                                   vector<double> oval_serr_vec,
                                   double* xval_bin_center_ptr,
                                   double* xval_bin_half_width_ptr,
                                   double* wmean_ptr,
                                   double* wmean_err_ptr)
{
    double* oval_arr = MirMath::GenArray(oval_vec);
    double* oval_serr_arr = MirMath::GenArray(oval_serr_vec);
    double wmean = 0.0;
    double wmean_err = 0.0;
    vector<long> index_bad_vec;
    MirMath::GetWMean(oval_vec.size(),
                       oval_arr,
                       oval_serr_arr,
                       &wmean,
                       &wmean_err,
                       &index_bad_vec);
    delete [] oval_arr;
    delete [] oval_serr_arr;

    double xval_min = MirMath::GetMin(xval_vec);
    double xval_max = MirMath::GetMax(xval_vec);
    long index_min = MirMath::GetLocMin(xval_vec);
    long index_max = MirMath::GetLocMax(xval_vec);
            
    double xval_lo = xval_min - xval_serr_vec[index_min];
    double xval_up = xval_max + xval_serr_vec[index_max];
    double xval_bin_center = (xval_lo + xval_up) / 2.;
    double xval_bin_half_width = (xval_up - xval_lo) / 2.;

    *xval_bin_center_ptr = xval_bin_center;
    *xval_bin_half_width_ptr = xval_bin_half_width;
    *wmean_ptr = wmean;
    *wmean_err_ptr = wmean_err;
}
