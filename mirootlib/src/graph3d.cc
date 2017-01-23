#include "mir_graph3d.h"

//
// public
//

void GraphData3d::SetXvalArr(const DataArray1d* const val_arr)
{
    GetXvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetYvalArr(const DataArray1d* const val_arr)
{
    GetYvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetOvalArr(const DataArray1d* const val_arr)
{
    GetOvalArrNonConst()->Copy(val_arr);
}

void GraphData3d::SetXvalArr(long ndata, const double* const val)
{
    GetXvalArrNonConst()->SetVal(ndata, val);
}

void GraphData3d::SetXvalArr(vector<double> val)
{
    GetXvalArrNonConst()->SetVal(val);
}

void GraphData3d::SetYvalArr(long ndata, const double* const val)
{
    GetYvalArrNonConst()->SetVal(ndata, val);
}

void GraphData3d::SetYvalArr(vector<double> val)
{
    GetYvalArrNonConst()->SetVal(val);
}
    
void GraphData3d::SetOvalArr(long ndata, const double* const val)
{
    GetOvalArrNonConst()->SetVal(ndata, val);
}

void GraphData3d::SetOvalArr(vector<double> val)
{
    GetOvalArrNonConst()->SetVal(val);
}

void GraphData3d::SetPoint(long idata, double xval, double yval, double oval)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetYvalArrNonConst()->SetValElm(idata, yval);
    GetOvalArrNonConst()->SetValElm(idata, oval);
}

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
    Init(nbin_xval);
    SetXvalArr(xval_vec);
    SetYvalArr(yval_vec);
    SetOvalArr(oval_vec);
}

void GraphData3d::Copy(const GraphData3d* const org)
{
    if(this == org) {abort();}
    if(NULL == org) {abort();}
    
    CopyTitle(org);
    Init(org->GetNdata());
    SetXvalArr(org->GetXvalArr());
    SetYvalArr(org->GetYvalArr());
    SetOvalArr(org->GetOvalArr());
}

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
}


double GraphData3d::GetOffsetXFromTag(string offset_tag) const
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


double GraphData3d::GetOffsetYFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetYvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetYvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetYvalArr()->GetValAndErrMin() +
                   GetYvalArr()->GetValAndErrMax() )/2.;
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


//
// protected
//


// Null

void GraphData3d::NullGraphData3d()
{
    if(NULL != xval_arr_) {delete xval_arr_; xval_arr_ = NULL;}
    if(NULL != yval_arr_) {delete yval_arr_; yval_arr_ = NULL;}
    if(NULL != oval_arr_) {delete oval_arr_; oval_arr_ = NULL;}
}

void GraphData3d::NewXvalArrAsDataArrayNerr1d()
{
    xval_arr_ = new DataArrayNerr1d;
}

void GraphData3d::NewXvalArrAsDataArraySerr1d()
{
    xval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewXvalArrAsDataArrayTerr1d()
{
    xval_arr_ = new DataArrayTerr1d;
}


void GraphData3d::NewYvalArrAsDataArrayNerr1d()
{
    yval_arr_ = new DataArrayNerr1d;
}

void GraphData3d::NewYvalArrAsDataArraySerr1d()
{
    yval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewYvalArrAsDataArrayTerr1d()
{
    yval_arr_ = new DataArrayTerr1d;
}


void GraphData3d::NewOvalArrAsDataArrayNerr1d()
{
    oval_arr_ = new DataArrayNerr1d;
}

void GraphData3d::NewOvalArrAsDataArraySerr1d()
{
    oval_arr_ = new DataArraySerr1d;
}

void GraphData3d::NewOvalArrAsDataArrayTerr1d()
{
    oval_arr_ = new DataArrayTerr1d;
}

