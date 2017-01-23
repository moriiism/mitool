#include "mir_graph2d_serr.h"

//
// public
//

// init

void GraphDataSerr2d::Init(long ndata)
{
    NullGraphData2d();
    NewXvalArrAsDataArraySerr1d();
    NewOvalArrAsDataArraySerr1d();
    SetFlagXvalSorted(0);
    GetXvalArrNonConst()->Init(ndata);
    GetOvalArrNonConst()->Init(ndata);
}

void GraphDataSerr2d::SetXvalSerrArr(long ndata, const double* const val_serr)
{
    GetXvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr2d::SetXvalSerrArr(vector<double> val_serr)
{
    GetXvalArrNonConst()->SetValSerr(val_serr);
}

void GraphDataSerr2d::SetOvalSerrArr(long ndata, const double* const val_serr)
{
    GetOvalArrNonConst()->SetValSerr(ndata, val_serr);
}

void GraphDataSerr2d::SetOvalSerrArr(vector<double> val_serr)
{
    GetOvalArrNonConst()->SetValSerr(val_serr);
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
    NullGraphData2d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    for(long idata = 0; idata < ndata; idata ++){
        int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
        if(4 != ncolumn){
            MPrintWarnClass("ncolumn != 4");
        }
        istringstream iss(line_arr[idata]);
        double xval, xval_serr, oval, oval_serr;
        iss >> xval >> xval_serr >> oval >> oval_serr;
        SetPoint(idata, xval, xval_serr, oval, oval_serr);
    }
    MiIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
    
}

void GraphDataSerr2d::Load(string file, string format)
{
    NullGraphData2d();
    
    string* line_arr = NULL;
    long ndata = 0;
    MiIolib::GenReadFileSkipComment(file, &line_arr, &ndata);
    Init(ndata);
    double xval, xval_serr, oval, oval_serr;
    if("x,xe,y,ye" == format){
        for(long idata = 0; idata < ndata; idata ++){
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
            int ncolumn = MiStr::GetNcolumn(line_arr[idata]);
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
    MiIolib::DelReadFile(line_arr);

    int flag_xval_sorted = 0;
    ReadInfo(file, &flag_xval_sorted);
    SetFlagXvalSorted(flag_xval_sorted);
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
}

const DataArraySerr1d* const GraphDataSerr2d::GetXvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetXvalArrNonConst());
}
    
const DataArraySerr1d* const GraphDataSerr2d::GetOvalArr() const
{
    return dynamic_cast<const DataArraySerr1d*>(GetOvalArrNonConst());
}

double GraphDataSerr2d::GetXvalSerrElm(long idata) const
{
    return GetXvalArr()->GetValSerrElm(idata);
}

double GraphDataSerr2d::GetOvalSerrElm(long idata) const
{
    return GetOvalArr()->GetValSerrElm(idata);
}

void GraphDataSerr2d::PrintData(FILE* fp, string format,
                                double offset_xval,
                                double offset_oval) const
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
                                            GetXvalArr()->GetValSerr(),
                                            GetOvalArr()->GetValSerr());
    delete [] xval_arr;
    delete [] oval_arr;
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
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(),
                                                 term_half_width_arr);

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
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(),
                                                 term_half_width_arr);

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
    double term_half_width_min = MirMath::GetMin(interval->GetNterm(),
                                                 term_half_width_arr);

    double tdiff = term_half_width_min / 10.; 
    interval->Clean(tdiff);

    delete [] term_half_width_arr;
    return interval;
}

