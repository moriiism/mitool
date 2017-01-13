#include "mir_graph3d_serr.h"

//
// public
//

// Init

void GraphDataSerr3d::Init()
{
    Null();
    NewXvalArrAsDataArraySerr1d();
    NewYvalArrAsDataArraySerr1d();
    NewOvalArrAsDataArraySerr1d();
}

// set xval_arr
void GraphDataSerr3d::SetXvalAndSerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetXvalArrNonConst()->InitSetValAndSerr(ndata, val, val_serr);
}


void GraphDataSerr3d::SetXvalAndSerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetXvalArrNonConst()->InitSetValAndSerr(val, val_serr);
}


// set yval_arr
void GraphDataSerr3d::SetYvalAndSerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetYvalArrNonConst()->InitSetValAndSerr(ndata, val, val_serr);
}


void GraphDataSerr3d::SetYvalAndSerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetYvalArrNonConst()->InitSetValAndSerr(val, val_serr);
}


// set oval_arr
void GraphDataSerr3d::SetOvalAndSerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetOvalArrNonConst()->InitSetValAndSerr(ndata, val, val_serr);
}

void GraphDataSerr3d::SetOvalAndSerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetOvalArrNonConst()->InitSetValAndSerr(val, val_serr);
}

void GraphDataSerr3d::SetPoint(long idata,
                               double xval, double xval_serr,
                               double yval, double yval_serr,
                               double oval, double oval_serr)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValSerrElm(idata, xval_serr);
    GetYvalArrNonConst()->SetValElm(idata, yval);
    GetYvalArrNonConst()->SetValSerrElm(idata, yval_serr);    
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValSerrElm(idata, oval_serr);
}


void GraphDataSerr3d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataSerr3d* const GraphDataSerr3d::Clone() const
{
    GraphDataSerr3d* obj_new = new GraphDataSerr3d;
    obj_new->Copy(this);
    return obj_new;
}

void GraphDataSerr3d::Load(string file)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
        if(6 != ncolumn){
            MPrintWarnClass("ncolumn != 6");
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> xval_serr
            >> yval >> yval_serr
            >> oval >> oval_serr;
        SetPoint(idata,
                 xval, xval_serr,
                 yval, yval_serr,
                 oval, oval_serr);
    }
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}


void GraphDataSerr3d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    if("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(6 != ncolumn){
                MPrintWarnClass("ncolumn != 6");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr
                >> yval >> yval_serr
                >> oval >> oval_serr;
            SetPoint(idata,
                     xval, xval_serr,
                     yval, yval_serr,
                     oval, oval_serr);
        }
    } else if("x,y,z,ze" == format){
        xval_serr = 0.0;
        yval_serr = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MPrintWarnClass("ncolumn != 4");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval
                >> yval
                >> oval >> oval_serr;
            SetPoint(idata,
                     xval, xval_serr,
                     yval, yval_serr,
                     oval, oval_serr);
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
// const functions
//

// get

const DataArraySerr1d* const GraphDataSerr3d::GetXvalArr() const
{
    const DataArray1d* xval_arr = GraphData3d::GetXvalArr();    
    return dynamic_cast<const DataArraySerr1d*>(xval_arr);
}

const DataArraySerr1d* const GraphDataSerr3d::GetYvalArr() const
{
    const DataArray1d* yval_arr = GraphData3d::GetYvalArr();        
    return dynamic_cast<const DataArraySerr1d*>(yval_arr);
}

const DataArraySerr1d* const GraphDataSerr3d::GetOvalArr() const
{
    const DataArray1d* oval_arr = GraphData3d::GetOvalArr();    
    return dynamic_cast<const DataArraySerr1d*>(oval_arr);
}


// output

void GraphDataSerr3d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_yval,
                                double offset_oval) const
{
    long ndata = GetNdata();
    if("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalSerrElm(idata),
                    GetYvalElm(idata) - offset_yval,
                    GetYvalSerrElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalSerrElm(idata));
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

TGraph2DErrors* const GraphDataSerr3d::GenTGraph2DErrors(double offset_xval,
                                                         double offset_yval,
                                                         double offset_oval) const
{
    long ndata = GetNdata();
    double* xval_arr = new double [ndata];
    double* yval_arr = new double [ndata];
    double* oval_arr = new double [ndata];
    double* xval_serr_arr = new double [ndata];
    double* yval_serr_arr = new double [ndata];
    double* oval_serr_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_arr[idata] = GetXvalElm(idata) - offset_xval;
        yval_arr[idata] = GetYvalElm(idata) - offset_yval;
        oval_arr[idata] = GetOvalElm(idata) - offset_oval;
        xval_serr_arr[idata] = GetXvalSerrElm(idata);
        yval_serr_arr[idata] = GetYvalSerrElm(idata);
        oval_serr_arr[idata] = GetOvalSerrElm(idata);
    }
    TGraph2DErrors* tgraph = new TGraph2DErrors(ndata,
                                                xval_arr,
                                                yval_arr,
                                                oval_arr,
                                                xval_serr_arr,
                                                yval_serr_arr,
                                                oval_serr_arr);
    delete [] xval_arr;
    delete [] yval_arr;
    delete [] oval_arr;
    delete [] xval_serr_arr;
    delete [] yval_serr_arr;
    delete [] oval_serr_arr;
    return tgraph;
}

double GraphDataSerr3d::GetOffsetXFromTag(string offset_tag) const
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


double GraphDataSerr3d::GetOffsetYFromTag(string offset_tag) const
{
    double offset = 0.0;
    if("st" == offset_tag){
        offset = GetYvalArr()->GetValAndErrMin();
    } else if ("ed" == offset_tag){
        offset = GetYvalArr()->GetValAndErrMax();
    } else if ("md" == offset_tag){
        offset = ( GetYvalArr()->GetValAndErrMin() + GetYvalArr()->GetValAndErrMax() )/2.;
    } else if ("no" == offset_tag){
        offset = 0.0;        
    } else {
        offset = atof(offset_tag.c_str());
    }
    return offset;
}


double GraphDataSerr3d::GetOffsetOFromTag(string offset_tag) const
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

