#include "mir_graph3d.h"

//
// public
//

// Init

void GraphData3d::Init()
{
    Null();
    NewXvalArrAsDataArray1d();
    NewYvalArrAsDataArray1d();
    NewOvalArrAsDataArray1d();
}

void GraphData3d::Set(const GraphData3d* const org)
{
    CopyMirObject(org);
    Set(org->GetXvalArr(),
        org->GetYvalArr(),
        org->GetOvalArr());
}


void GraphData3d::Set(const DataArray1d* const xval_arr,
                      const DataArray1d* const yval_arr,
                      const DataArray1d* const oval_arr)
{
    GetXvalArrNonConst()->Copy(xval_arr);
    GetYvalArrNonConst()->Copy(yval_arr);
    GetOvalArrNonConst()->Copy(oval_arr);
}

// Init & Set
void GraphData3d::InitSet(const DataArray1d* const xval_arr,
                          const DataArray1d* const yval_arr,
                          const DataArray1d* const oval_arr)
{
    Init();
    Set(xval_arr, yval_arr, oval_arr); 
}


// Set xval_arr
void GraphData3d::SetXvalArr(const DataArray1d* const val_arr)
{
    GetXvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetXvalArrDbl(long ndata, const double* const val)
{
    GetXvalArrNonConst()->InitSetVal(ndata, val);
}

void GraphData3d::SetXvalArrDbl(vector<double> val)
{
    GetXvalArrNonConst()->InitSetVal(val);
}

// Set yval_arr
void GraphData3d::SetYvalArr(const DataArray1d* const val_arr)
{
    GetYvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetYvalArrDbl(long ndata, const double* const val)
{
    GetYvalArrNonConst()->InitSetVal(ndata, val);
}

void GraphData3d::SetYvalArrDbl(vector<double> val)
{
    GetYvalArrNonConst()->InitSetVal(val);
}

// Set oval_arr
void GraphData3d::SetOvalArr(const DataArray1d* const val_arr)
{
    GetOvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetOvalArrDbl(long ndata, const double* const val)
{
    GetOvalArrNonConst()->InitSetVal(ndata, val);
}

void GraphData3d::SetOvalArrDbl(vector<double> val)
{
    GetOvalArrNonConst()->InitSetVal(val);
}

// Set point
void GraphData3d::SetPoint(long idata, double xval, double yval, double oval)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetYvalArrNonConst()->SetValElm(idata, yval);
    GetOvalArrNonConst()->SetValElm(idata, oval);
}

// Init & Set by Func
void GraphData3d::InitSetByFunc(const MirFunc* const func, const double* const par,
                                long nbin_xval, double xval_lo, double xval_up,
                                long nbin_yval, double yval_lo, double yval_up,
                                string scale_xval, string scale_yval)
{
    vector<double> xval_vec;
    vector<double> yval_vec;
    vector<double> oval_vec;
    HistInfo1d* hi1d_xval = new HistInfo1d;
    hi1d_xval->InitSetByNbin(xval_lo, xval_up, nbin_xval);
    HistInfo1d* hi1d_yval = new HistInfo1d;
    hi1d_yval->InitSetByNbin(yval_lo, yval_up, nbin_yval);
    for(long ibin_x = 0; ibin_x < nbin_xval; ibin_x ++){
        for(long ibin_y = 0; ibin_y < nbin_yval; ibin_y ++){
            double xval = hi1d_xval->GetBinCenter(ibin_x, scale_xval);
            double yval = hi1d_yval->GetBinCenter(ibin_y, scale_yval);
            xval_vec.push_back(xval);
            yval_vec.push_back(yval);
            double xval_tmp[2];
            xval_tmp[0] = xval;
            xval_tmp[1] = yval;
            double oval = func->Eval(xval_tmp, par);
            oval_vec.push_back(oval);
        }
    }
    delete hi1d_xval;
    delete hi1d_yval;
    Init();
    SetXvalArrDbl(xval_vec);
    SetYvalArrDbl(yval_vec);
    SetOvalArrDbl(oval_vec);
}

void GraphData3d::Copy(const GraphData3d* const org)
{
    if(this == org) {return;}
    if(NULL == org) {return;}
    
    CopyMirObject(org);
    Init();
    Set(org);
}

GraphData3d* const GraphData3d::Clone() const
{
    GraphData3d* obj_new = new GraphData3d;
    obj_new->Copy(this);
    return obj_new;
}

// Load
void GraphData3d::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    double xval, yval, oval;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
        if(3 != ncolumn){
            MPrintWarnClass("ncolumn != 3");
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> yval >> oval;
        SetPoint(idata, xval, yval, oval);
    }
    MirIolib::DelReadFile(line_arr);
}


void GraphData3d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
    double xval, yval, oval;
    if("x,y,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MPrintWarnClass("ncolumn != 3");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> yval >> oval;
            SetPoint(idata, xval, yval, oval);
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

//
// stat
//

double GraphData3d::GetYvalAtXvalMin() const
{
    long loc_min = GetXvalArr()->GetLocValMin();
    return GetYvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetYvalAtXvalMax() const
{
    long loc_max = GetXvalArr()->GetLocValMax();
    return GetYvalArr()->GetValElm(loc_max);
}


double GraphData3d::GetOvalAtXvalMin() const
{
    long loc_min = GetXvalArr()->GetLocValMin();
    return GetOvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetOvalAtXvalMax() const
{
    long loc_max = GetXvalArr()->GetLocValMax();
    return GetOvalArr()->GetValElm(loc_max);
}


double GraphData3d::GetXvalAtYvalMin() const
{
    long loc_min = GetYvalArr()->GetLocValMin();
    return GetXvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetXvalAtYvalMax() const
{
    long loc_max = GetYvalArr()->GetLocValMax();
    return GetXvalArr()->GetValElm(loc_max);
}


double GraphData3d::GetOvalAtYvalMin() const
{
    long loc_min = GetYvalArr()->GetLocValMin();
    return GetOvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetOvalAtYvalMax() const
{
    long loc_max = GetYvalArr()->GetLocValMax();
    return GetOvalArr()->GetValElm(loc_max);
}


double GraphData3d::GetXvalAtOvalMin() const
{
    long loc_min = GetOvalArr()->GetLocValMin();
    return GetXvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetXvalAtOvalMax() const
{
    long loc_max = GetOvalArr()->GetLocValMax();
    return GetXvalArr()->GetValElm(loc_max);
}


double GraphData3d::GetYvalAtOvalMin() const
{
    long loc_min = GetOvalArr()->GetLocValMin();
    return GetYvalArr()->GetValElm(loc_min);
}

double GraphData3d::GetYvalAtOvalMax() const
{
    long loc_max = GetOvalArr()->GetLocValMax();
    return GetYvalArr()->GetValElm(loc_max);
}

// output

void GraphData3d::Save(string outfile, string format,
                       double offset_xval,
                       double offset_yval,
                       double offset_oval) const
{
    FILE* fp = fopen(outfile.c_str(), "w");
    PrintData(fp, format, offset_xval, offset_yval, offset_oval);
    fclose(fp);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphData3d::PrintData(FILE* fp, string format,
                            double offset_xval,
                            double offset_yval,
                            double offset_oval) const
{
    long ndata = GetXvalArr()->GetNdata();
    if("x,y,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,                    
                    GetOvalElm(idata) - offset_oval,
                    0.0);
        }
    } else if ("x,xe,y,ye,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,                    
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetYvalElm(idata) - offset_yval,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else if ("x,xe,y,ye,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0,
                    GetYvalElm(idata) - offset_yval,
                    0.0,
                    GetOvalElm(idata) - offset_oval,
                    0.0, 0.0);
        }
    } else if ("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    0.0, 0.0,
                    GetYvalElm(idata) - offset_yval,
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


TGraph2D* const GraphData3d::GenTGraph2D(double offset_xval,
                                         double offset_yval,
                                         double offset_oval) const
{
    long ndata = GetNdata();
    double* xval_arr = new double [ndata];
    double* yval_arr = new double [ndata];
    double* oval_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_arr[idata] = GetXvalElm(idata) - offset_xval;
        yval_arr[idata] = GetYvalElm(idata) - offset_yval;
        oval_arr[idata] = GetOvalElm(idata) - offset_oval;
    }
    TGraph2D* tgraph = new TGraph2D(ndata, xval_arr, yval_arr, oval_arr);
    delete [] xval_arr;
    delete [] yval_arr;
    delete [] oval_arr;
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tgraph;
}

double GraphData3d::GetOffsetXFromTag(string offset_tag) const
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


double GraphData3d::GetOffsetYFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetYvalArr()->GetValMin();
    } else if ("ed" == offset_tag){
        offset = GetYvalArr()->GetValMax();
    } else if ("md" == offset_tag){
        offset = ( GetYvalArr()->GetValMin() + GetYvalArr()->GetValMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;        
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}

double GraphData3d::GetOffsetOFromTag(string offset_tag) const
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


//
// protected
//


// Null

void GraphData3d::Null()
{
    if(NULL != xval_arr_) {delete xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
}

void GraphData3d::NewXvalArrAsDataArray1d()
{
    xval_arr_ = new DataArray1d;
}

void GraphData3d::NewXvalArrAsDataArraySerr1d()
{
    xval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewXvalArrAsDataArrayTerr1d()
{
    xval_arr_ = new DataArrayTerr1d;
}


void GraphData3d::NewYvalArrAsDataArray1d()
{
    yval_arr_ = new DataArray1d;
}

void GraphData3d::NewYvalArrAsDataArraySerr1d()
{
    yval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewYvalArrAsDataArrayTerr1d()
{
    yval_arr_ = new DataArrayTerr1d;
}


void GraphData3d::NewOvalArrAsDataArray1d()
{
    oval_arr_ = new DataArray1d;
}

void GraphData3d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

