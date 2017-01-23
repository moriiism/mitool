#include "mir_graph3d_nerr.h"

//
// public
//

void GraphDataNerr3d::Init(long ndata)
{
    NullGraphData3d();
    NewXvalArrAsDataArrayNerr1d();
    NewYvalArrAsDataArrayNerr1d();
    NewOvalArrAsDataArrayNerr1d();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
}

GraphDataNerr3d* const GraphDataNerr3d::Clone() const
{
    GraphDataNerr3d* obj_new = new GraphDataNerr3d;
    obj_new->Copy(this);
    return obj_new;
}

void GraphDataNerr3d::Load(string file)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, yval, oval;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(3 != ncolumn){
            MPrintWarnClass("ncolumn != 3");
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> yval >> oval;
        SetPoint(idata, xval, yval, oval);
    }
    MiIolib::DelReadFile(line_arr);
}


void GraphDataNerr3d::Load(string file, string format)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, yval, oval;
    if("x,y,z" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
    MiIolib::DelReadFile(line_arr);
}

const DataArrayNerr1d* const GraphDataNerr3d::GetXvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetXvalArrNonConst());
}

const DataArrayNerr1d* const GraphDataNerr3d::GetYvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetYvalArrNonConst());
}

const DataArrayNerr1d* const GraphDataNerr3d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayNerr1d*>(GetOvalArrNonConst());
}

void GraphData3d::PrintData(FILE* fp, string format,
                            double offset_xval,
                            double offset_yval,
                            double offset_oval) const
{
    long ndata = GetNdata();
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


TGraph2D* const GraphDataNerr3d::GenTGraph2D(double offset_xval,
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

