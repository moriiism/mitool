#include "mir_graph3d_terr.h"

//
// public
//

// Init

void GraphDataTerr3d::Init()
{
    Null();
    NewXvalArrAsDataArrayTerr1d();
    NewYvalArrAsDataArrayTerr1d();
    NewOvalArrAsDataArrayTerr1d();
}

// set xval
void GraphDataTerr3d::SetXvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetXvalArrNonConst()->InitSetValAndTerr(ndata, val, val_serr);
}

void GraphDataTerr3d::SetXvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetXvalArrNonConst()->InitSetValAndTerr(val, val_serr);
}

void GraphDataTerr3d::SetXvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_terr_plus,
                                           const double* const val_terr_minus)
{
    GetXvalArrNonConst()->InitSetValAndTerr(ndata,
                                            val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr3d::SetXvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_terr_plus,
                                           vector<double> val_terr_minus)
{
    GetXvalArrNonConst()->InitSetValAndTerr(val,
                                            val_terr_plus,
                                            val_terr_minus);
}


// Set yval_arr
void GraphDataTerr3d::SetYvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetYvalArrNonConst()->InitSetValAndTerr(ndata, val, val_serr);
}

void GraphDataTerr3d::SetYvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetYvalArrNonConst()->InitSetValAndTerr(val, val_serr);
}

void GraphDataTerr3d::SetYvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_terr_plus,
                                           const double* const val_terr_minus)
{
    GetYvalArrNonConst()->InitSetValAndTerr(ndata,
                                            val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr3d::SetYvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_terr_plus,
                                           vector<double> val_terr_minus)
{
    GetYvalArrNonConst()->InitSetValAndTerr(val, val_terr_plus, val_terr_minus);
}


// Set oval_arr
void GraphDataTerr3d::SetOvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetOvalArrNonConst()->InitSetValAndTerr(ndata, val, val_serr);
}

void GraphDataTerr3d::SetOvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetOvalArrNonConst()->InitSetValAndTerr(val, val_serr);
}

void GraphDataTerr3d::SetOvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_terr_plus,
                                           const double* const val_terr_minus)
{
    GetOvalArrNonConst()->InitSetValAndTerr(ndata,
                                            val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr3d::SetOvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_terr_plus,
                                           vector<double> val_terr_minus)
{
    GetOvalArrNonConst()->InitSetValAndTerr(val, val_terr_plus, val_terr_minus);
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
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
    double xval, xval_terr_plus, xval_terr_minus;
    double yval, yval_terr_plus, yval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
        if(9 != ncolumn){
            MPrintWarnClass("ncolumn != 9");
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
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphDataTerr3d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetYvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);    
    double xval, xval_terr_plus, xval_terr_minus;
    double yval, yval_terr_plus, yval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    if("x,xe+,xe-,y,ye+,ye-,z,ze+,ze-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(9 != ncolumn){
                MPrintWarnClass("ncolumn != 9");
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
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MPrintWarnClass("ncolumn != 5");
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
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

//
// const functions
//

// get

const DataArrayTerr1d* const GraphDataTerr3d::GetXvalArr() const
{
    const DataArray1d* xval_arr = GraphData3d::GetXvalArr();
    return dynamic_cast<const DataArrayTerr1d*>(xval_arr);
}

const DataArrayTerr1d* const GraphDataTerr3d::GetYvalArr() const
{
    const DataArray1d* yval_arr = GraphData3d::GetYvalArr();    
    return dynamic_cast<const DataArrayTerr1d*>(yval_arr);
}

const DataArrayTerr1d* const GraphDataTerr3d::GetOvalArr() const
{
    const DataArray1d* oval_arr = GraphData3d::GetOvalArr();        
    return dynamic_cast<const DataArrayTerr1d*>(oval_arr);
}


// output

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
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

double GraphDataTerr3d::GetOffsetXFromTag(string offset_tag) const
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


double GraphDataTerr3d::GetOffsetYFromTag(string offset_tag) const
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


double GraphDataTerr3d::GetOffsetOFromTag(string offset_tag) const
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



