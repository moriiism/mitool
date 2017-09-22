#ifndef MORIIISM_MITOOL_MIROOTLIB_DATA1D_OPE_H_
#define MORIIISM_MITOOL_MIROOTLIB_DATA1D_OPE_H_

#include "mir_interval.h"
#include "mir_data1d_nerr.h"
#include "mir_data1d_serr.h"
#include "mir_data1d_terr.h"

namespace DataArray1dOpe
{
    DataArray1d* const GenDa1dByLoad(string file, string format);

    void DelDa1dArr(DataArray1d** const da1d_arr, int narr);
    
    // For one DataArray1d    
    void GetNot(const DataArray1d* const data_array,
                DataArray1d* const data_array_out);
    void GetScale(const DataArray1d* const data_array,
                  double scale, double offset,
                  DataArrayNerr1d* const data_array_out);
    void GetScale(const DataArray1d* const data_array,
                  double scale, double offset,
                  DataArraySerr1d* const data_array_out);
    void GetScale(const DataArray1d* const data_array,
                  double scale, double offset,
                  DataArrayTerr1d* const data_array_out);
    
    // For two DataArray1d
    void GetMin(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayNerr1d* const data_array_out);
    void GetMin(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArraySerr1d* const data_array_out);
    void GetMin(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayTerr1d* const data_array_out);
    
    void GetMax(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayNerr1d* const data_array_out);
    void GetMax(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArraySerr1d* const data_array_out);
    void GetMax(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayTerr1d* const data_array_out);
    
    void GetAdd(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayNerr1d* const data_array_out);
    void GetAdd(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArraySerr1d* const data_array_out);
    
    void GetSub(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayNerr1d* const data_array_out);
    void GetSub(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArraySerr1d* const data_array_out);
    
    void GetMul(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArrayNerr1d* const data_array_out);
    void GetMul(const DataArray1d* const data_array1,
                const DataArray1d* const data_array2,
                DataArraySerr1d* const data_array_out);
    
    int GetDiv(const DataArray1d* const data_array_num,
               const DataArray1d* const data_array_den,
               DataArrayNerr1d* const mask_sel_array_out,
               DataArrayNerr1d* const data_array_out);
    int GetDiv(const DataArray1d* const data_array_num,
               const DataArray1d* const data_array_den,
               DataArrayNerr1d* const mask_sel_array_out,
               DataArraySerr1d* const data_array_out);
    
    void GetAMean(const DataArray1d* const data_array1,
                  const DataArray1d* const data_array2,
                  DataArrayNerr1d* const data_array_out);
    void GetAMean(const DataArray1d* const data_array1,
                  const DataArray1d* const data_array2,
                  DataArraySerr1d* const data_array_out);
    
    int GetWMean(const DataArray1d* const data_array1,
                 const DataArray1d* const data_array2,
                 DataArrayNerr1d* const mask_sel_array_out,
                 DataArraySerr1d* const data_array_out);

    int GetSubAddRatio(const DataArray1d* const data_array1,
                       const DataArray1d* const data_array2,
                       DataArrayNerr1d* const mask_sel_array_out,
                       DataArrayNerr1d* const data_array_out);

    int GetSubAddRatio(const DataArray1d* const data_array1,
                       const DataArray1d* const data_array2,
                       DataArrayNerr1d* const mask_sel_array_out,
                       DataArraySerr1d* const data_array_out);

    // For N DataArray1d
    void GetMin(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* const data_array_out);
    void GetMin(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* const data_array_out);
    void GetMin(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayTerr1d* const data_array_out);
    
    void GetMax(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* const data_array_out);
    void GetMax(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* const data_array_out);
    void GetMax(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayTerr1d* const data_array_out);
    
    void GetSum(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* const data_array_out);
    void GetSum(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* const data_array_out);
    
    void GetAMean(const DataArray1d* const* const data_array_arr,
                  int ndata_array,
                  DataArrayNerr1d* const data_array_out);
    void GetAMean(const DataArray1d* const* const data_array_arr,
                  int ndata_array,
                  DataArraySerr1d* const data_array_out);
    
    int GetWMean(const DataArray1d* const* const data_array_arr,
                 int ndata_array,
                 DataArrayNerr1d* const mask_sel_array_out,
                 DataArraySerr1d* const data_array_out);
    
    void GetVariance(const DataArray1d* const* const data_array_arr,
                     int ndata_array,
                     DataArrayNerr1d* const data_array_out);
    void GetStddev(const DataArray1d* const* const data_array_arr,
                   int ndata_array,
                   DataArrayNerr1d* const data_array_out);
    void GetUnbiasedVariance(const DataArray1d* const* const data_array_arr,
                             int ndata_array,
                             DataArrayNerr1d* const data_array_out);
    void GetSqrtOfUnbiasedVariance(const DataArray1d* const* const data_array_arr,
                                   int ndata_array,
                                   DataArrayNerr1d* const data_array_out);
    void GetRMS(const DataArray1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* const data_array_out);
    void GetMedian(const DataArray1d* const* const data_array_arr,
                   int ndata_array,
                   DataArrayNerr1d* const data_array_out);
                   
    void GetSumWithMask(const DataArray1d* const* const data_array_arr,
                        const DataArray1d* const* const mask_array_arr,
                        int ndata_array,
                        DataArrayNerr1d* const data_array_out);
    void GetSumWithMask(const DataArray1d* const* const data_array_arr,
                        const DataArray1d* const* const mask_array_arr,
                        int ndata_array,
                        DataArraySerr1d* const data_array_out);
    
    void GetAMeanWithMask(const DataArray1d* const* const data_array_arr,
                          const DataArray1d* const* const mask_array_arr,
                          int ndata_array,
                          DataArrayNerr1d* const data_array_out);
    void GetAMeanWithMask(const DataArray1d* const* const data_array_arr,
                          const DataArray1d* const* const mask_array_arr,
                          int ndata_array,
                          DataArraySerr1d* const data_array_out);
    
    int GetWMeanWithMask(const DataArray1d* const* const data_array_arr,
                         const DataArray1d* const* const mask_array_arr,
                         int ndata_array,
                         DataArrayNerr1d* const mask_sel_array_out,
                         DataArraySerr1d* const data_array_out);

    int IsFormatSame(const DataArray1d* const data_array1,
                     const DataArray1d* const data_array2);
    int IsFormatSame(const DataArray1d* const* const data_array_arr,
                     int ndata_array);
    
    // Select
    void GetSelectDa1dByInterval(const DataArray1d* const data_array,
                                 const Interval* const interval,
                                 DataArrayNerr1d* const data_array_out);
    void GetSelectDa1dByInterval(const DataArray1d* const data_array,
                                 const Interval* const interval,
                                 DataArraySerr1d* const data_array_out);
    void GetSelectDa1dByInterval(const DataArray1d* const data_array,
                                 const Interval* const interval,
                                 DataArrayTerr1d* const data_array_out);

    void GenSelectDa1dArrByIntervalNerr(const DataArray1d* const data_array,
                                        const Interval* const interval,
                                        DataArray1d*** const data_array_arr_ptr);
    void GenSelectDa1dArrByIntervalSerr(const DataArray1d* const data_array,
                                        const Interval* const interval,
                                        DataArray1d*** const data_array_arr_ptr);
    void GenSelectDa1dArrByIntervalTerr(const DataArray1d* const data_array,
                                        const Interval* const interval,
                                        DataArray1d*** const data_array_arr_ptr);

} // namespace DataArray1dOpe

#endif // MORIIISM_MITOOL_MIROOTLIB_DATA1D_OPE_H_
