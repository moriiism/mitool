#include "mir_graph2d_terr.h"

//
// public
//

// Init

void GraphDataTerr2d::Init()
{
    NullGraphData2d();
    NewXvalArrAsDataArrayTerr1d();
    NewOvalArrAsDataArrayTerr1d();
    SetFlagXvalSorted(0);
}

// xval
void GraphDataTerr2d::SetXvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetXvalArrNonConst()->InitSetValAndTerr(ndata, val, val_serr);
}

void GraphDataTerr2d::SetXvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetXvalArrNonConst()->InitSetValAndTerr(val, val_serr);
}

void GraphDataTerr2d::SetXvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_terr_plus,
                                           const double* const val_terr_minus)
{
    GetXvalArrNonConst()->InitSetValAndTerr(ndata,
                                            val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr2d::SetXvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_terr_plus,
                                           vector<double> val_terr_minus)
{
    GetXvalArrNonConst()->InitSetValAndTerr(val,
                                            val_terr_plus,
                                            val_terr_minus);
}


// oval
void GraphDataTerr2d::SetOvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_serr)
{
    GetOvalArrNonConst()->InitSetValAndTerr(ndata, val, val_serr);
}

void GraphDataTerr2d::SetOvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_serr)
{
    GetOvalArrNonConst()->InitSetValAndTerr(val, val_serr);
}

void GraphDataTerr2d::SetOvalAndTerrArrDbl(long ndata,
                                           const double* const val,
                                           const double* const val_terr_plus,
                                           const double* const val_terr_minus)
{
    GetOvalArrNonConst()->InitSetValAndTerr(ndata,
                                            val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr2d::SetOvalAndTerrArrDbl(vector<double> val,
                                           vector<double> val_terr_plus,
                                           vector<double> val_terr_minus)
{
    GetOvalArrNonConst()->InitSetValAndTerr(val,
                                            val_terr_plus,
                                            val_terr_minus);
}

void GraphDataTerr2d::SetPoint(long idata,
                               double xval,
                               double xval_terr_plus,
                               double xval_terr_minus,
                               double oval,
                               double oval_terr_plus,
                               double oval_terr_minus)
{
    GetXvalArrNonConst()->SetValElm(idata, xval);
    GetXvalArrNonConst()->SetValTerrPlusElm(idata, xval_terr_plus);
    GetXvalArrNonConst()->SetValTerrMinusElm(idata, xval_terr_minus);
    GetOvalArrNonConst()->SetValElm(idata, oval);
    GetOvalArrNonConst()->SetValTerrPlusElm(idata, oval_terr_plus);
    GetOvalArrNonConst()->SetValTerrMinusElm(idata, oval_terr_minus);
}

void GraphDataTerr2d::SetOvalErrArrByPoissonErr()
{
    GetOvalArrNonConst()->SetValErrByPoissonErr();
}


GraphDataTerr2d* const GraphDataTerr2d::Clone() const
{
    GraphDataTerr2d* obj_new = new GraphDataTerr2d;
    obj_new->Copy(this);
    return obj_new;
}



void GraphDataTerr2d::Load(string file)
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
        if(6 != ncolumn){
            MPrintWarnClass("ncolumn != 6");
        }
        istringstream iss(line_arr[idata]);
        double xval, xval_terr_plus, xval_terr_minus;
        double oval, oval_terr_plus, oval_terr_minus;
        iss >> xval >> xval_terr_plus >> xval_terr_minus
            >> oval >> oval_terr_plus >> oval_terr_minus;
        SetPoint(idata,
                 xval, xval_terr_plus, xval_terr_minus,
                 oval, oval_terr_plus, oval_terr_minus);
    }
    MirIolib::DelReadFile(line_arr);
    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
}

void GraphDataTerr2d::Load(string file, string format)
{
    Null();
    
    string* line_arr = NULL;
    long ndata = 0;
    MirIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init();
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
    
    double xval, xval_terr_plus, xval_terr_minus;
    double oval, oval_terr_plus, oval_terr_minus;
    if("x,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(2 != ncolumn){
                MPrintWarnClass("ncolumn != 2");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,y,ye" == format){
        double oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MPrintWarnClass("ncolumn != 3");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> oval >> oval_serr;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            oval_terr_plus = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MPrintWarnClass("ncolumn != 4");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval
                >> oval >> oval_terr_plus >> oval_terr_minus;
            xval_terr_plus  = 0.0;
            xval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe,y" == format){
        double xval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(3 != ncolumn){
                MPrintWarnClass("ncolumn != 3");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval;
            xval_terr_plus  = xval_serr; 
            xval_terr_minus = -1 * xval_serr; 
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe,y,ye" == format){
        double xval_serr, oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MPrintWarnClass("ncolumn != 4");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr >> oval >> oval_serr;
            xval_terr_plus = xval_serr;
            xval_terr_minus = -1 * xval_serr;
            oval_terr_plus = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);            
        }
    } else if("x,xe,y,ye+,ye-" == format){
        double xval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MPrintWarnClass("ncolumn != 5");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_serr
                >> oval >> oval_terr_plus >> oval_terr_minus;
            xval_terr_plus = xval_serr;
            xval_terr_minus = -1 * xval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(4 != ncolumn){
                MPrintWarnClass("ncolumn != 4");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval;
            oval_terr_plus  = 0.0;
            oval_terr_minus = 0.0;            
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y,ye" == format){
        double oval_serr;
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(5 != ncolumn){
                MPrintWarnClass("ncolumn != 5");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval >> oval_serr;
            oval_terr_plus  = oval_serr;
            oval_terr_minus = -1 * oval_serr;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
                     oval, oval_terr_plus, oval_terr_minus);
        }
    } else if("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MirStr::GetNcolumn(line_arr[idata]);
            if(6 != ncolumn){
                MPrintWarnClass("ncolumn != 6");
            }
            istringstream iss(line_arr[idata]);
            iss >> xval >> xval_terr_plus >> xval_terr_minus
                >> oval >> oval_terr_plus >> oval_terr_minus;
            SetPoint(idata,
                     xval, xval_terr_plus, xval_terr_minus,
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


void GraphDataTerr2d::Sort()
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
    double* xval_terr_plus_org = new double [ndata];
    double* xval_terr_minus_org = new double [ndata];
    double* oval_org      = new double [ndata];
    double* oval_terr_plus_org = new double [ndata];
    double* oval_terr_minus_org = new double [ndata];
    for(long idata = 0; idata < ndata; idata++){
        xval_org[idata]            = GetXvalElm(idata);
        xval_terr_plus_org[idata]  = GetXvalTerrPlusElm(idata);
        xval_terr_minus_org[idata] = GetXvalTerrMinusElm(idata);
        oval_org[idata]            = GetOvalElm(idata);    
        oval_terr_plus_org[idata]  = GetOvalTerrPlusElm(idata);
        oval_terr_minus_org[idata] = GetOvalTerrMinusElm(idata);
    }

    long* index = new long [ndata];  // to store sort result
    TMath::Sort(ndata, xval_org, index, kFALSE);

    for(long idata = 0; idata < ndata; idata++){
        SetPoint(idata,
                 xval_org[index[idata]],
                 xval_terr_plus_org[index[idata]],
                 xval_terr_minus_org[index[idata]],
                 oval_org[index[idata]],
                 oval_terr_plus_org[index[idata]],
                 oval_terr_minus_org[index[idata]] );
    }
    
    delete [] xval_org;
    delete [] xval_terr_plus_org;
    delete [] xval_terr_minus_org;
    delete [] oval_org;
    delete [] oval_terr_plus_org;
    delete [] oval_terr_minus_org;
    delete [] index;
    
    SetFlagXvalSorted(1);
    if(0 < g_flag_verbose){
        MPrintInfoClass("sorted.");
    }
}


//
// const functions
//

// get

const DataArrayTerr1d* const GraphDataTerr2d::GetXvalArr() const
{
    const DataArray1d* xval_arr = GraphData2d::GetXvalArr();
    return dynamic_cast<const DataArrayTerr1d*>(xval_arr);
};

const DataArrayTerr1d* const GraphDataTerr2d::GetOvalArr() const
{
    const DataArray1d* oval_arr = GraphData2d::GetOvalArr();
    return dynamic_cast<const DataArrayTerr1d*>(oval_arr);
};

// get Range Qdp

void GraphDataTerr2d::GetXRangeQdp(double* const low_ptr, double* const up_ptr) const
{
    double low, up;
    MirMath::GetRangeQdp(GetXvalArr()->GetValAndErrMin(), GetXvalArr()->GetValAndErrMax(), &low, &up);
    *low_ptr = low;
    *up_ptr  = up;
    if(0 < g_flag_verbose){
        MPrintInfo("done.");
    }
}

void GraphDataTerr2d::GetORangeQdp(double* const low_ptr, double* const up_ptr) const
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

void GraphDataTerr2d::PrintData(FILE* fp, string format,
                                double offset_xval, double offset_oval) const
{
    long ndata = GetNdata();
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
                    (GetOvalTerrPlusElm(idata) - GetOvalTerrMinusElm(idata))/2.);
        }
    } else if ("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval,
                    (GetOvalTerrPlusElm(idata) - GetOvalTerrMinusElm(idata))/2.);
        }
    } else if ("x,xe,y" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval);
        }
    } else if ("x,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else if ("x,xe,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    (GetXvalTerrPlusElm(idata) - GetXvalTerrMinusElm(idata))/2.,
                    GetOvalElm(idata) - offset_oval,
                    GetOvalTerrPlusElm(idata),
                    GetOvalTerrMinusElm(idata));
        }
    } else if ("x,xe+,xe-,y,ye+,ye-" == format){
        for(long idata = 0; idata < ndata; idata ++){
            fprintf(fp, "%.15e  %.15e  %.15e  %.15e  %.15e  %.15e\n",
                    GetXvalElm(idata) - offset_xval,
                    GetXvalTerrPlusElm(idata),
                    GetXvalTerrMinusElm(idata),
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


TGraphAsymmErrors* const GraphDataTerr2d::GenTGraph(double offset_xval, double offset_oval) const
{
    long ndata = GetNdata();
    double* xval_arr = new double [ndata];
    double* oval_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_arr[idata] = GetXvalElm(idata) - offset_xval;
        oval_arr[idata] = GetOvalElm(idata) - offset_oval;
    }

    double* xval_terr_plus_arr  = new double [ndata];
    double* xval_terr_minus_arr = new double [ndata];    
    double* oval_terr_plus_arr  = new double [ndata];
    double* oval_terr_minus_arr = new double [ndata];
    for(long idata = 0; idata < ndata; idata ++){
        xval_terr_plus_arr[idata]  = GetXvalTerrPlusElm(idata);
        xval_terr_minus_arr[idata] = -1 * GetXvalTerrMinusElm(idata);
        oval_terr_plus_arr[idata]  = GetOvalTerrPlusElm(idata);
        oval_terr_minus_arr[idata] = -1 * GetOvalTerrMinusElm(idata);
    }

    TGraphAsymmErrors* tgraph = new TGraphAsymmErrors(ndata,
                                                      xval_arr, oval_arr,
                                                      xval_terr_minus_arr,
                                                      xval_terr_plus_arr,
                                                      oval_terr_minus_arr,
                                                      oval_terr_plus_arr);
    delete [] xval_arr;
    delete [] oval_arr;
    delete [] xval_terr_plus_arr;
    delete [] xval_terr_minus_arr;    
    delete [] oval_terr_plus_arr;
    delete [] oval_terr_minus_arr;        

    if(0 < g_flag_verbose){
        MPrintInfoClass("done.");
    }
    return tgraph;
}


Interval* const GraphDataTerr2d::GenInterval() const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
        tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
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

Interval* const GraphDataTerr2d::GenIntervalAboveThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) > threshold){
            tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
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

Interval* const GraphDataTerr2d::GenIntervalBelowThreshold(double threshold) const
{
    vector<double> tstart_vec;
    vector<double> tstop_vec;
    for(long idata = 0; idata < GetNdata(); idata ++){
        if(GetOvalElm(idata) < threshold){
            tstart_vec.push_back(GetXvalElm(idata) + GetXvalTerrMinusElm(idata));
            tstop_vec.push_back(GetXvalElm(idata) + GetXvalTerrPlusElm(idata));
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


double GraphDataTerr2d::GetOffsetXFromTag(string offset_tag) const
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

double GraphDataTerr2d::GetOffsetOFromTag(string offset_tag) const
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

