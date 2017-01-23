#include "mir_graph3d_serr.h"

//
// public
//

// Init

void GraphDataSerr3d::Init(long ndata)
{
    NullGraphData3d();
    NewXvalArrAsDataArraySerr1d();
    NewYvalArrAsDataArraySerr1d();
    NewOvalArrAsDataArraySerr1d();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
}

void GraphDataSerr3d::SetXvalSerrArr(long ndata, const double* const val_serr)
{
    GetXvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetXvalSerrArr(vector<double> val_serr)
{
    GetXvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr3d::SetYvalSerrArr(long ndata, const double* const val_serr)
{
    GetYvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetYvalSerrArr(vector<double> val_serr)
{
    GetYvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr3d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr3d::SetOvalSerrArr(vector<double> val_serr)
{
    GetOvalArrNonConst()->SetValSerr(val_serr);
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
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
    MiIolib::DelReadFile(line_arr);
}


void GraphDataSerr3d::Load(string file, string format)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_serr, yval, yval_serr, oval, oval_serr;
    if("x,xe,y,ye,z,ze" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
    MiIolib::DelReadFile(line_arr);
}


//
// const functions
//

const DataArraySerr1d* const GraphDataSerr3d::GetXvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetXvalArrNonConst());
}

const DataArraySerr1d* const GraphDataSerr3d::GetYvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetYvalArrNonConst());
}

const DataArraySerr1d* const GraphDataSerr3d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double GraphDataSerr3d::GetXvalSerrElm(long idata) const
{
    return GetXvalArr()->GetValSerrElm(idata);
}

double GraphDataSerr3d::GetYvalSerrElm(long idata) const
{
    return GetYvalArr()->GetValSerrElm(idata);
}

double GraphDataSerr3d::GetOvalSerrElm(long idata) const
{
    return GetOvalArr()->GetValSerrElm(idata);
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
}

TGraph2DErrors* const GraphDataSerr3d::GenTGraph2D(double offset_xval,
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
