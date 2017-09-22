#ifndef MORIIISM_MITOOL_MITIMINGLIB_TIMECONV_H_
#define MORIIISM_MITOOL_MITIMINGLIB_TIMECONV_H_

#include "mir_physpar.h"
#include "mir_graph2d_nerr.h"
#include "mir_graph2d_serr.h"
#include "mir_graph2d_terr.h"
#include "mir_hist1d_nerr.h"
#include "mir_hist1d_serr.h"
#include "mir_hist1d_terr.h"

// time converter

namespace TimeConv{

    double JdToMjd(double jd);
    double MjdToJd(double mjd);
    double SecToMjd(double time, double mjd_ref);
    double DayToMjd(double time, double mjd_ref);
    double MjdToSec(double time_mjd, double mjd_ref);
    double MjdToDay(double time_mjd, double mjd_ref);
    
    double TimeToMjd(double time, double mjd_ref, string tunit);
    double MjdToTime(double time_mjd, double mjd_ref, string tunit);

    DataArray1d* const GenTimeToMjd(
        const DataArray1d* const data_arr,
        double mjd_ref, string tunit);
    DataArray1d* const GenMjdToTime(
        const DataArray1d* const data_arr,
        double mjd_ref, string tunit);
    DataArray1d* const GenTimeToMjd_DataArray1d(
        const DataArray1d* const data_arr,
        double mjd_ref, string tunit);
    DataArray1d* const GenMjdToTime_DataArray1d(
        const DataArray1d* const data_arr,
        double mjd_ref, string tunit);
    DataArraySerr1d* const GenTimeToMjd_DataArraySerr1d(
        const DataArraySerr1d* const data_arr,
        double mjd_ref, string tunit);
    DataArraySerr1d* const GenMjdToTime_DataArraySerr1d(
        const DataArraySerr1d* const data_arr,
        double mjd_ref, string tunit);
    DataArrayTerr1d* const GenTimeToMjd_DataArrayTerr1d(
        const DataArrayTerr1d* const data_arr,
        double mjd_ref, string tunit);
    DataArrayTerr1d* const GenMjdToTime_DataArrayTerr1d(
        const DataArrayTerr1d* const data_arr,
        double mjd_ref, string tunit);

    GraphData2d* const GenTimeToMjd(
        const GraphData2d* const g2d,
        double mjd_ref, string tunit);
    GraphData2d* const GenMjdToTime(
        const GraphData2d* const g2d,
        double mjd_ref, string tunit); 
    GraphData2d* const GenTimeToMjd_GraphData2d(
        const GraphData2d* const g2d,
        double mjd_ref, string tunit);
    GraphData2d* const GenMjdToTime_GraphData2d(
        const GraphData2d* const g2d,
        double mjd_ref, string tunit); 
    GraphDataSerr2d* const GenTimeToMjd_GraphDataSerr2d(
        const GraphDataSerr2d* const g2d,
        double mjd_ref, string tunit);
    GraphDataSerr2d* const GenMjdToTime_GraphDataSerr2d(
        const GraphDataSerr2d* const g2d,
        double mjd_ref, string tunit);
    GraphDataTerr2d* const GenTimeToMjd_GraphDataTerr2d(
        const GraphDataTerr2d* const g2d,
        double mjd_ref, string tunit);
    GraphDataTerr2d* const GenMjdToTime_GraphDataTerr2d(
        const GraphDataTerr2d* const g2d,
        double mjd_ref, string tunit);

    HistData1d* const GenTimeToMjd(
        const HistData1d* const h1d,
        double mjd_ref, string tunit);
    HistData1d* const GenMjdToTime(
        const HistData1d* const h1d,
        double mjd_ref, string tunit);
    HistData1d* const GenTimeToMjd_HistData1d(
        const HistData1d* const h1d,
        double mjd_ref, string tunit);
    HistData1d* const GenMjdToTime_HistData1d(
        const HistData1d* const h1d,
        double mjd_ref, string tunit);
    HistDataSerr1d* const GenTimeToMjd_HistDataSerr1d(
        const HistDataSerr1d* const h1d,
        double mjd_ref, string tunit);
    HistDataSerr1d* const GenMjdToTime_HistDataSerr1d(
        const HistDataSerr1d* const h1d,
        double mjd_ref, string tunit);
    HistDataTerr1d* const GenTimeToMjd_HistDataTerr1d(
        const HistDataTerr1d* const h1d,
        double mjd_ref, string tunit);
    HistDataTerr1d* const GenMjdToTime_HistDataTerr1d(
        const HistDataTerr1d* const h1d,
        double mjd_ref, string tunit);
    
    Interval* const GenTimeToMjd(const Interval* const interval,
                                 double mjd_ref, string tunit);
    Interval* const GenMjdToTime(const Interval* const interval,
                                 double mjd_ref, string tunit);
}

#endif // MORIIISM_MITOOL_MITIMINGLIB_TIMECONV_H_

