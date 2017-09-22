#include "mit_timeconv.h"

double TimeConv::JdToMjd(double jd)
{
    double mjd = jd - 2400000.5;
    return mjd;
}

double TimeConv::MjdToJd(double mjd)
{
    double jd = mjd + 2400000.5;
    return jd;
}

double TimeConv::SecToMjd(double time, double mjd_ref)
{
    double time_mjd = mjd_ref + time / kDayToSec;
    return time_mjd;
}

double TimeConv::DayToMjd(double time, double mjd_ref)
{
    double time_mjd = mjd_ref + time;
    return time_mjd;
}

double TimeConv::MjdToSec(double time_mjd, double mjd_ref)
{
    double time = (time_mjd - mjd_ref) * kDayToSec;
    return time;
}

double TimeConv::MjdToDay(double time_mjd, double mjd_ref)
{
    double time = time_mjd - mjd_ref;
    return time;
}


double TimeConv::TimeToMjd(double time, double mjd_ref, string tunit)
{
    double time_mjd = 0.0;
    if("sec" == tunit){
        time_mjd = SecToMjd(time, mjd_ref);
    } else if("day" == tunit){
        time_mjd = DayToMjd(time, mjd_ref);
    } else {
        char msg[kLineSize];
        printf("bad tunit: %s", tunit.c_str());
        MPrintErr(msg);
        abort();
    }
    return time_mjd;
}


double TimeConv::MjdToTime(double time_mjd, double mjd_ref, string tunit)
{
    double time = 0.0;
    if("sec" == tunit){
        time = MjdToSec(time_mjd, mjd_ref);
    } else if("day" == tunit){
        time = MjdToDay(time_mjd, mjd_ref);
    } else {
        printf("error bad\n");
        abort();
    }
    return time;
}


DataArray1d* const TimeConv::GenTimeToMjd(const DataArray1d* const data_arr,
                                          double mjd_ref, string tunit)
{
    DataArray1d* data_arr_new = NULL;
    if("DataArray1d" == data_arr->GetClassName()){
        data_arr_new = GenTimeToMjd_DataArray1d(
            data_arr, mjd_ref, tunit);
    } else if ("DataArraySerr1d" == data_arr->GetClassName()){
        data_arr_new = GenTimeToMjd_DataArraySerr1d(
            dynamic_cast<const DataArraySerr1d* const>(data_arr), mjd_ref, tunit);
    } else if ("DataArrayTerr1d" == data_arr->GetClassName()){
        data_arr_new = GenTimeToMjd_DataArrayTerr1d(
            dynamic_cast<const DataArrayTerr1d* const>(data_arr), mjd_ref, tunit);
    } else {
        abort();
    }
    return data_arr_new;
}


DataArray1d* const TimeConv::GenMjdToTime(const DataArray1d* const data_arr,
                                          double mjd_ref, string tunit)
{
    DataArray1d* data_arr_new = NULL;
    if("DataArray1d" == data_arr->GetClassName()){
        data_arr_new = GenMjdToTime_DataArray1d(
            data_arr, mjd_ref, tunit);
    } else if ("DataArraySerr1d" == data_arr->GetClassName()){
        data_arr_new = GenMjdToTime_DataArraySerr1d(
            dynamic_cast<const DataArraySerr1d* const>(data_arr), mjd_ref, tunit);
    } else if ("DataArrayTerr1d" == data_arr->GetClassName()){
        data_arr_new = GenMjdToTime_DataArrayTerr1d(
            dynamic_cast<const DataArrayTerr1d* const>(data_arr), mjd_ref, tunit);
    } else {
        abort();
    }
    return data_arr_new;
}


DataArray1d* const TimeConv::GenTimeToMjd_DataArray1d(
    const DataArray1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArray1d* data_arr_new = new DataArrayNerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = TimeToMjd(data_arr->GetValElm(idata), mjd_ref, tunit);
        data_arr_new->SetValElm(idata, val_new);
    }
    return data_arr_new;
}


DataArray1d* const TimeConv::GenMjdToTime_DataArray1d(
    const DataArray1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArray1d* data_arr_new = new DataArrayNerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = MjdToTime(data_arr->GetValElm(idata), mjd_ref, tunit);
        data_arr_new->SetValElm(idata, val_new);
    }
    return data_arr_new;
}


DataArraySerr1d* const TimeConv::GenTimeToMjd_DataArraySerr1d(
    const DataArraySerr1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArraySerr1d* data_arr_new = new DataArraySerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = TimeToMjd(data_arr->GetValElm(idata), mjd_ref, tunit);
        double val_serr_new = TimeToMjd(data_arr->GetValSerrElm(idata), 0.0, tunit);
        data_arr_new->SetValElm(idata, val_new);
        data_arr_new->SetValSerrElm(idata, val_serr_new);
    }
    return data_arr_new;
}


DataArraySerr1d* const TimeConv::GenMjdToTime_DataArraySerr1d(
    const DataArraySerr1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArraySerr1d* data_arr_new = new DataArraySerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = MjdToTime(data_arr->GetValElm(idata), mjd_ref, tunit);
        double val_serr_new = MjdToTime(data_arr->GetValSerrElm(idata), 0.0, tunit);
        data_arr_new->SetValElm(idata, val_new);
        data_arr_new->SetValSerrElm(idata, val_serr_new);
    }
    return data_arr_new;
}

DataArrayTerr1d* const TimeConv::GenTimeToMjd_DataArrayTerr1d(
    const DataArrayTerr1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArrayTerr1d* data_arr_new = new DataArrayTerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = TimeToMjd(data_arr->GetValElm(idata), mjd_ref, tunit);
        double val_terr_plus_new = TimeToMjd(data_arr->GetValTerrPlusElm(idata), 0.0, tunit);
        double val_terr_minus_new = TimeToMjd(data_arr->GetValTerrMinusElm(idata), 0.0, tunit);
        data_arr_new->SetValElm(idata, val_new);
        data_arr_new->SetValTerrPlusElm(idata, val_terr_plus_new);
        data_arr_new->SetValTerrMinusElm(idata, val_terr_minus_new);
    }
    return data_arr_new;
}


DataArrayTerr1d* const TimeConv::GenMjdToTime_DataArrayTerr1d(
    const DataArrayTerr1d* const data_arr,
    double mjd_ref, string tunit)
{
    DataArrayTerr1d* data_arr_new = new DataArrayTerr1d;
    data_arr_new->Init(data_arr->GetNdata());
    for(int idata = 0; idata < data_arr->GetNdata(); idata ++){
        double val_new = MjdToTime(data_arr->GetValElm(idata), mjd_ref, tunit);
        double val_terr_plus_new = MjdToTime(data_arr->GetValTerrPlusElm(idata), 0.0, tunit);
        double val_terr_minus_new = MjdToTime(data_arr->GetValTerrMinusElm(idata), 0.0, tunit);
        data_arr_new->SetValElm(idata, val_new);
        data_arr_new->SetValTerrPlusElm(idata, val_terr_plus_new);
        data_arr_new->SetValTerrMinusElm(idata, val_terr_minus_new);
    }
    return data_arr_new;
}


GraphData2d* const TimeConv::GenTimeToMjd(const GraphData2d* const g2d,
                                          double mjd_ref, string tunit)
{
    GraphData2d* g2d_new = NULL;
    if("GraphData2d" == g2d->GetClassName()){
        g2d_new = GenTimeToMjd_GraphData2d(
            g2d, mjd_ref, tunit);
    } else if ("GraphDataSerr2d" == g2d->GetClassName()){
        g2d_new = GenTimeToMjd_GraphDataSerr2d(
            dynamic_cast<const GraphDataSerr2d* const>(g2d), mjd_ref, tunit);
    } else if ("GraphDataTerr2d" == g2d->GetClassName()){
        g2d_new = GenTimeToMjd_GraphDataTerr2d(
            dynamic_cast<const GraphDataTerr2d* const>(g2d), mjd_ref, tunit);
    } else {
        abort();
    }
    return g2d_new;
}

GraphData2d* const TimeConv::GenMjdToTime(const GraphData2d* const g2d,
                                          double mjd_ref, string tunit)
{
    GraphData2d* g2d_new = NULL;
    if("GraphData2d" == g2d->GetClassName()){
        g2d_new = GenMjdToTime_GraphData2d(
            g2d, mjd_ref, tunit);
    } else if ("GraphDataSerr2d" == g2d->GetClassName()){
        g2d_new = GenMjdToTime_GraphDataSerr2d(
            dynamic_cast<const GraphDataSerr2d* const>(g2d), mjd_ref, tunit);
    } else if ("GraphDataTerr2d" == g2d->GetClassName()){
        g2d_new = GenMjdToTime_GraphDataTerr2d(
            dynamic_cast<const GraphDataTerr2d* const>(g2d), mjd_ref, tunit);
    } else {
        abort();
    }
    return g2d_new;
}


GraphData2d* const TimeConv::GenTimeToMjd_GraphData2d(
    const GraphData2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphData2d* g2d_new = new GraphDataNerr2d;
    DataArray1d* xval_arr_new = GenTimeToMjd(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}

GraphData2d* const TimeConv::GenMjdToTime_GraphData2d(
    const GraphData2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphData2d* g2d_new = new GraphDataNerr2d;
    DataArray1d* xval_arr_new = GenMjdToTime(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}



GraphDataSerr2d* const TimeConv::GenTimeToMjd_GraphDataSerr2d(
    const GraphDataSerr2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphDataSerr2d* g2d_new = new GraphDataSerr2d;
    DataArraySerr1d* xval_arr_new = GenTimeToMjd_DataArraySerr1d(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}

GraphDataSerr2d* const TimeConv::GenMjdToTime_GraphDataSerr2d(
    const GraphDataSerr2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphDataSerr2d* g2d_new = new GraphDataSerr2d;
    DataArraySerr1d* xval_arr_new = GenMjdToTime_DataArraySerr1d(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}


GraphDataTerr2d* const TimeConv::GenTimeToMjd_GraphDataTerr2d(
    const GraphDataTerr2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphDataTerr2d* g2d_new = new GraphDataTerr2d;
    DataArrayTerr1d* xval_arr_new = GenTimeToMjd_DataArrayTerr1d(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}

GraphDataTerr2d* const TimeConv::GenMjdToTime_GraphDataTerr2d(
    const GraphDataTerr2d* const g2d,
    double mjd_ref, string tunit)
{
    GraphDataTerr2d* g2d_new = new GraphDataTerr2d;
    DataArrayTerr1d* xval_arr_new = GenMjdToTime_DataArrayTerr1d(g2d->GetXvalArr(), mjd_ref, tunit);
    g2d_new->Init(g2d->GetNdata());
    g2d_new->SetXvalArr(xval_arr_new);
    g2d_new->SetOvalArr(g2d->GetOvalArr());
    g2d_new->SetFlagXvalSorted(g2d->GetFlagXvalSorted());
    delete xval_arr_new;
    return g2d_new;
}


// -----------

HistData1d* const TimeConv::GenTimeToMjd(
    const HistData1d* const h1d,
    double mjd_ref, string tunit)
{
    HistData1d* h1d_new = NULL;
    if("HistData1d" == h1d->GetClassName()){
        h1d_new = GenTimeToMjd_HistData1d(
            h1d, mjd_ref, tunit);
    } else if ("HistDataSerr1d" == h1d->GetClassName()){
        h1d_new = GenTimeToMjd_HistDataSerr1d(
            dynamic_cast<const HistDataSerr1d* const>(h1d), mjd_ref, tunit);
    } else if ("HistDataTerr1d" == h1d->GetClassName()){
        h1d_new = GenTimeToMjd_HistDataTerr1d(
            dynamic_cast<const HistDataTerr1d* const>(h1d), mjd_ref, tunit);
    } else {
        abort();
    }
    return h1d_new;
}

HistData1d* const TimeConv::GenMjdToTime(
    const HistData1d* const h1d,
    double mjd_ref, string tunit)
{
    HistData1d* h1d_new = NULL;
    if("HistData1d" == h1d->GetClassName()){
        h1d_new = GenMjdToTime_HistData1d(
            h1d, mjd_ref, tunit);
    } else if ("HistDataSerr1d" == h1d->GetClassName()){
        h1d_new = GenMjdToTime_HistDataSerr1d(
            dynamic_cast<const HistDataSerr1d* const>(h1d), mjd_ref, tunit);
    } else if ("HistDataTerr1d" == h1d->GetClassName()){
        h1d_new = GenMjdToTime_HistDataTerr1d(
            dynamic_cast<const HistDataTerr1d* const>(h1d), mjd_ref, tunit);
    } else {
        abort();
    }
    return h1d_new;
}

   
HistData1d* const TimeConv::GenTimeToMjd_HistData1d(
    const HistData1d* const h1d,
    double mjd_ref, string tunit)
{
    HistData1d* h1d_new = new HistDataNerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = TimeToMjd(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = TimeToMjd(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}

    
HistData1d* const TimeConv::GenMjdToTime_HistData1d(
    const HistData1d* const h1d,
    double mjd_ref, string tunit)
{
    HistData1d* h1d_new = new HistDataNerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = MjdToTime(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = MjdToTime(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}

    
HistDataSerr1d* const TimeConv::GenTimeToMjd_HistDataSerr1d(
    const HistDataSerr1d* const h1d,
    double mjd_ref, string tunit)
{
    HistDataSerr1d* h1d_new = new HistDataSerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = TimeToMjd(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = TimeToMjd(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}

    
HistDataSerr1d* const TimeConv::GenMjdToTime_HistDataSerr1d(
    const HistDataSerr1d* const h1d,
    double mjd_ref, string tunit)
{
    HistDataSerr1d* h1d_new = new HistDataSerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = MjdToTime(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = MjdToTime(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}

    
HistDataTerr1d* const TimeConv::GenTimeToMjd_HistDataTerr1d(
    const HistDataTerr1d* const h1d,
    double mjd_ref, string tunit)
{
    HistDataTerr1d* h1d_new = new HistDataTerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = TimeToMjd(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = TimeToMjd(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}

   
HistDataTerr1d* const TimeConv::GenMjdToTime_HistDataTerr1d(
    const HistDataTerr1d* const h1d,
    double mjd_ref, string tunit)
{
    HistDataTerr1d* h1d_new = new HistDataTerr1d;
    long nbin_xval = h1d->GetNbinX();
    double xval_lo_new = MjdToTime(h1d->GetXvalLo(), mjd_ref, tunit);
    double xval_up_new = MjdToTime(h1d->GetXvalUp(), mjd_ref, tunit);
    h1d_new->Init(nbin_xval, xval_lo_new, xval_up_new);
    h1d_new->SetOvalArr(h1d->GetOvalArr());
    return h1d_new;
}


Interval* const TimeConv::GenTimeToMjd(const Interval* const interval,
                                       double mjd_ref, string tunit)
{
    long nterm = interval->GetNterm();
    double* tstart_arr = new double [nterm];
    double* tstop_arr = new double [nterm];
    for (long iterm = 0; iterm < nterm; iterm++){
        tstart_arr[iterm] = TimeToMjd(interval->GetTstartElm(iterm),
                                      mjd_ref, tunit);
        tstop_arr[iterm] = TimeToMjd(interval->GetTstopElm(iterm),
                                     mjd_ref, tunit);
    }
    Interval* interval_new = new Interval;
    interval_new->Init(nterm);
    interval_new->Set(nterm,
                      tstart_arr,
                      tstop_arr);
    delete [] tstart_arr;
    delete [] tstop_arr;
    return interval_new;
}


Interval* const TimeConv::GenMjdToTime(const Interval* const interval,
                                       double mjd_ref, string tunit)
{
    long nterm = interval->GetNterm();
    double* tstart_arr = new double [nterm];
    double* tstop_arr = new double [nterm];
    for (long iterm = 0; iterm < nterm; iterm++){
        tstart_arr[iterm] = MjdToTime(interval->GetTstartElm(iterm),
                                      mjd_ref, tunit);
        tstop_arr[iterm] = MjdToTime(interval->GetTstopElm(iterm),
                                     mjd_ref, tunit);
    }
    Interval* interval_new = new Interval;
    interval_new->Init(nterm);
    interval_new->Set(nterm,
                      tstart_arr,
                      tstop_arr);
    delete [] tstart_arr;
    delete [] tstop_arr;
    return interval_new;
}
