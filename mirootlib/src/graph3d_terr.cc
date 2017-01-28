#include "mir_graph3d_terr.h"

//
// public
//

// Init

void GraphDataTerr3d::Init(long ndata)
{
    NullGraphData3d();
    NewXvalArrAsDataArrayTerr1d();
    NewYvalArrAsDataArrayTerr1d();
    NewOvalArrAsDataArrayTerr1d();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
}

void GraphDataTerr3d::SetXvalTerrArr(long ndata, const double* const val_serr)
{
    GetXvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void GraphDataTerr3d::SetXvalTerrArr(vector<double> val_serr)
{
    GetXvalArrNonConst()->SetValTerr(val_serr);
}

void GraphDataTerr3d::SetXvalTerrArr(long ndata,
                                     const double* const val_terr_plus,
                                     const double* const val_terr_minus)
{
    GetXvalArrNonConst()->SetValTerr(ndata,
                                     val_terr_plus,
                                     val_terr_minus);
}
    
void GraphDataTerr3d::SetXvalTerrArr(vector<double> val_terr_plus,
                                     vector<double> val_terr_minus)
{
   GetXvalArrNonConst()->SetValTerr(val_terr_plus,
                                    val_terr_minus);
}
    
void GraphDataTerr3d::SetYvalTerrArr(long ndata, const double* const val_serr)
{
    GetYvalArrNonConst()->SetValTerr(ndata, val_serr);
}
    
void GraphDataTerr3d::SetYvalTerrArr(vector<double> val_serr)
{
    GetYvalArrNonConst()->SetValTerr(val_serr);
}

void GraphDataTerr3d::SetYvalTerrArr(long ndata,
                                     const double* const val_terr_plus,
                                     const double* const val_terr_minus)
{
    GetYvalArrNonConst()->SetValTerr(ndata,
                                     val_terr_plus,
                                     val_terr_minus);
}

void GraphDataTerr3d::SetYvalTerrArr(vector<double> val_terr_plus,
                                     vector<double> val_terr_minus)
{
   GetYvalArrNonConst()->SetValTerr(val_terr_plus,
                                    val_terr_minus);
}
    
void GraphDataTerr3d::SetOvalTerrArr(long ndata, const double* const val_serr)
{
    GetOvalArrNonConst()->SetValTerr(ndata, val_serr);
}

void GraphDataTerr3d::SetOvalTerrArr(vector<double> val_serr)
{
    GetOvalArrNonConst()->SetValTerr(val_serr);
}

void GraphDataTerr3d::SetOvalTerrArr(long ndata,
                                     const double* const val_terr_plus,
                                     const double* const val_terr_minus)
{
    GetOvalArrNonConst()->SetValTerr(ndata,
                                     val_terr_plus,
                                     val_terr_minus);
}

void GraphDataTerr3d::SetOvalTerrArr(vector<double> val_terr_plus,
                                     vector<double> val_terr_minus)
{
    GetOvalArrNonConst()->SetValTerr(val_terr_plus,
                                     val_terr_minus);
}

void GraphDataTerr3d::SetPoint(long idata,
                               double xval,
                               double xval_terr_plus,
                               double xval_terr_minus,
                               double yval,
                               double yval_terr_plus,
                               double yval_terr_minus,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValTerrPlusElm(idata, xval_terr_plus);
    GetXvalArrNonConst()->SetValTerrMinusElm(idata, xval_terr_minus);
    GetYvalArrNonConst()->SetValElm(idata, yval);
    GetYvalArrNonConst()->SetValTerrPlusElm(idata, yval_terr_plus);
    GetYvalArrNonConst()->SetValTerrMinusElm(idata, yval_terr_minus);
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValTerrPlusElm(idata, oval_terr_plus);
    GetOvalArrNonConst()->SetValTerrMinusElm(idata, oval_terr_minus);    
}


void GraphDataTerr3d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataTerr3d* const GraphDataTerr3d::Clone() const
{
    GraphDataTerr3d* obj_new = new GraphDataTerr3d;
    obj_new->Copy(this);
    return obj_new;
}


void GraphDataTerr3d::Load(string file)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_terr_plus, xval_terr_minus;
    double yval, yval_terr_plus, yval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(9 != ncolumn){
            MPrintErrClass("ncolumn != 9");
            abort();
        }
        istringstream iss(line_arr[idata]);
        iss >> xval >> xval_terr_plus >> xval_terr_minus
            >> yval >> yval_terr_plus >> yval_terr_minus
            >> oval >> oval_terr_plus >> oval_terr_minus;
        SetPoint(idata,
                 xval, xval_terr_plus, xval_terr_minus,
                 yval, yval_terr_plus, yval_terr_minus,
                 oval, oval_terr_plus, oval_terr_minus);
    }
    MiIolib::DelReadFile(line_arr);
}

void GraphDataTerr3d::Load(string file, string format)
{
    NullGraphData3d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_terr_plus, xval_terr_minus;
    double yval, yval_terr_plus, yval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    if("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
            if(9 != ncolumn){
                MPrintErrClass("ncolumn != 9");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> yval >> yval_terr_plus >> yval_terr_minus
                >> oval >> oval_terr_plus >> oval_terr_minus;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     yval, yval_terr_plus, yval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,y,z,ze+,ze-" == format){
        xval_terr_plus  = 0.0;
        xval_terr_minus = 0.0;
        yval_terr_plus  = 0.0;
        yval_terr_minus = 0.0;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MPrintErrClass("ncolumn != 5");
                abort();
            }
            istringstream iss(line_arr[idata]);
            iss >> xval
                >> yval
                >> oval >> oval_terr_plus >> oval_terr_minus;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     yval, yval_terr_plus, yval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
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

const DataArrayTerr1d* const GraphDataTerr3d::GetXvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetXvalArrNonConst());
}

const DataArrayTerr1d* const GraphDataTerr3d::GetYvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetYvalArrNonConst());
}

const DataArrayTerr1d* const GraphDataTerr3d::GetOvalArr() const
{
    return dynamic_cast<const DataArrayTerr1d*>(GetOvalArrNonConst());
}

void GraphDataTerr3d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_yval,
                                double offset_oval) const
{
    long ndata = GetNdata();

    if("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp,
                    "%.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e  "
                    "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalTerrPlusElm(idata),
                    GetXvalTerrMinusElm(idata),
                    GetYvalElm(idata) - offset_yval,
                    GetYvalTerrPlusElm(idata),
                    GetYvalTerrMinusElm(idata),
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else {
        char msg[kLineSize];
        sprintf(msg, "format(=%s)", format.c_str());
        MPrintErrClass(msg);
        abort();
    }
}

