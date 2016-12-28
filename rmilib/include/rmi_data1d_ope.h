#ifndef MORIIISM_MILIB_DATA1D_OPE_H_
#define MORIIISM_MILIB_DATA1D_OPE_H_

#include "mi_data1d_nerr.h"
#include "mi_data1d_serr.h"
#include "mi_data1d_terr.h"

namespace DataArray1dOpe
{
    DataArray1d* const GenDa1dByLoad(string file, string format);
    
    void GetNot(const DataArrayNerr1d* const data_array,
                DataArrayNerr1d* data_array_out);
    
    void GetScale(const DataArrayNerr1d* const data_array,
                  double scale, double offset,
                  DataArrayNerr1d* data_array_out);
    void GetScale(const DataArraySerr1d* const data_array,
                  double scale, double offset,
                  DataArraySerr1d* data_array_out);
    void GetScale(const DataArrayTerr1d* const data_array,
                  double scale, double offset,
                  DataArrayTerr1d* data_array_out);

    // For two DataArray1d
    void GetMin(const DataArrayNerr1d* const data_array1,
                const DataArrayNerr1d* const data_array2,
                DataArrayNerr1d* data_array_out);
    void GetMin(const DataArraySerr1d* const data_array1,
                const DataArraySerr1d* const data_array2,
                DataArraySerr1d* data_array_out);
    void GetMin(const DataArrayTerr1d* const data_array1,
                const DataArrayTerr1d* const data_array2,
                DataArrayTerr1d* data_array_out);
    
    void GetMax(const DataArrayNerr1d* const data_array1,
                const DataArrayNerr1d* const data_array2,
                DataArrayNerr1d* data_array_out);
    void GetMax(const DataArraySerr1d* const data_array1,
                const DataArraySerr1d* const data_array2,
                DataArraySerr1d* data_array_out);
    void GetMax(const DataArrayTerr1d* const data_array1,
                const DataArrayTerr1d* const data_array2,
                DataArrayTerr1d* data_array_out);
    
    void GetAdd(const DataArrayNerr1d* const data_array1,
                const DataArrayNerr1d* const data_array2,
                DataArrayNerr1d* data_array_out);
    void GetAdd(const DataArraySerr1d* const data_array1,
                const DataArraySerr1d* const data_array2,
                DataArraySerr1d* data_array_out);
    
    void GetSub(const DataArrayNerr1d* const data_array1,
                const DataArrayNerr1d* const data_array2,
                DataArrayNerr1d* data_array_out);
    void GetSub(const DataArraySerr1d* const data_array1,
                const DataArraySerr1d* const data_array2,
                DataArraySerr1d* data_array_out);
    
    void GetMul(const DataArrayNerr1d* const data_array1,
                const DataArrayNerr1d* const data_array2,
                DataArrayNerr1d* data_array_out);
    void GetMul(const DataArraySerr1d* const data_array1,
                const DataArraySerr1d* const data_array2,
                DataArraySerr1d* data_array_out);
    
    long GetDiv(const DataArrayNerr1d* const data_array_num,
                const DataArrayNerr1d* const data_array_den,
                vector<long>* const index_bad_vec_ptr,
                DataArrayNerr1d* data_array_out);
    long GetDiv(const DataArraySerr1d* const data_array_num,
                const DataArraySerr1d* const data_array_den,
                vector<long>* const index_bad_vec_ptr,
                DataArraySerr1d* data_array_out);
    
    void GetAMean(const DataArrayNerr1d* const data_array1,
                  const DataArrayNerr1d* const data_array2,
                  DataArrayNerr1d* data_array_out);
    void GetAMean(const DataArraySerr1d* const data_array1,
                  const DataArraySerr1d* const data_array2,
                  DataArraySerr1d* data_array_out);
    
    long GetWMean(const DataArraySerr1d* const data_array1,
                  const DataArraySerr1d* const data_array2,
                  vector<long>* const index_bad_vec_ptr,
                  DataArraySerr1d* data_array_out);

    long GetSubAddRatio(const DataArrayNerr1d* const data_array1,
                        const DataArrayNerr1d* const data_array2,
                        vector<long>* const index_bad_vec_ptr,
                        DataArrayNerr1d* data_array_out);

    long GetSubAddRatio(const DataArraySerr1d* const data_array1,
                        const DataArraySerr1d* const data_array2,
                        vector<long>* const index_bad_vec_ptr,
                        DataArraySerr1d* data_array_out);

    // For N DataArray1d
    void GetMin(const DataArrayNerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* data_array_out);
    void GetMin(const DataArraySerr1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* data_array_out);
    void GetMin(const DataArrayTerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayTerr1d* data_array_out);
    
    void GetMax(const DataArrayNerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* data_array_out);
    void GetMax(const DataArraySerr1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* data_array_out);
    void GetMax(const DataArrayTerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayTerr1d* data_array_out);
    
    void GetAdd(const DataArrayNerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* data_array_out);
    void GetAdd(const DataArraySerr1d* const* const data_array_arr,
                int ndata_array,
                DataArraySerr1d* data_array_out);
    
    void GetAMean(const DataArrayNerr1d* const* const data_array_arr,
                  int ndata_array,
                  DataArrayNerr1d* data_array_out);
    void GetAMean(const DataArraySerr1d* const* const data_array_arr,
                  int ndata_array,
                  DataArraySerr1d* data_array_out);
    
    long GetWMean(const DataArraySerr1d* const* const data_array_arr,
                  int ndata_array,
                  vector<long>* const index_bad_vec_ptr,
                  DataArraySerr1d* data_array_out);
    
    void GetVariance(const DataArrayNerr1d* const* const data_array_arr,
                     int ndata_array,
                     DataArrayNerr1d* data_array_out);
    void GetStddev(const DataArrayNerr1d* const* const data_array_arr,
                   int ndata_array,
                   DataArrayNerr1d* data_array_out);
    void GetUnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
                             int ndata_array,
                             DataArrayNerr1d* data_array_out);
    void GetSqrtOfUnbiasedVariance(const DataArrayNerr1d* const* const data_array_arr,
                                   int ndata_array,
                                   DataArrayNerr1d* data_array_out);
    void GetRMS(const DataArrayNerr1d* const* const data_array_arr,
                int ndata_array,
                DataArrayNerr1d* data_array_out);
    void GetMedian(const DataArrayNerr1d* const* const data_array_arr,
                   int ndata_array,
                   DataArrayNerr1d* data_array_out);
                   
    void GetAddWithMask(const DataArrayNerr1d* const* const data_array_arr,
                        const DataArrayNerr1d* const* const mask_array_arr,
                        int ndata_array,
                        DataArrayNerr1d* data_array_out);
    void GetAddWithMask(const DataArraySerr1d* const* const data_array_arr,
                        const DataArrayNerr1d* const* const mask_array_arr,
                        int ndata_array,
                        DataArraySerr1d* data_array_out);
    
    void GetAMeanWithMask(const DataArrayNerr1d* const* const data_array_arr,
                          const DataArrayNerr1d* const* const mask_array_arr,
                          int ndata_array,
                          DataArrayNerr1d* const nvalid_array_out,
                          DataArrayNerr1d* data_array_out);
    void GetAMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
                          const DataArrayNerr1d* const* const mask_array_arr,
                          int ndata_array,
                          DataArrayNerr1d* const nvalid_array_out,
                          DataArraySerr1d* data_array_out);
    
    long GetWMeanWithMask(const DataArraySerr1d* const* const data_array_arr,
                          const DataArrayNerr1d* const* const mask_array_arr,
                          int ndata_array,
                          vector<long>* const index_bad_vec_ptr,
                          DataArraySerr1d* const nvalid_array_out,
                          DataArraySerr1d* data_array_out);

    int IsFormatSame(const DataArrayNerr1d* const data_array1,
                     const DataArrayNerr1d* const data_array2);
    int IsFormatSame(const DataArrayNerr1d* const* const data_array_arr,
                     int ndata_array);
    int IsFormatSame(const DataArraySerr1d* const* const data_array_arr,
                     int ndata_array);
    int IsFormatSame(const DataArrayTerr1d* const* const data_array_arr,
                     int ndata_array);
    
    // Select
    void GetSelectDa1dByInterval(const DataArrayNerr1d* const data_array,
                                 const Interval* const interval,
                                 DataArrayNerr1d* const data_array_out);
    void GetSelectDa1dByInterval(const DataArraySerr1d* const data_array,
                                 const Interval* const interval,
                                 DataArraySerr1d* const data_array_out);
    void GetSelectDa1dByInterval(const DataArrayTerr1d* const data_array,
                                 const Interval* const interval,
                                 DataArrayTerr1d* const data_array_out);
    void GenSelectDa1dArrByInterval(const DataArrayNerr1d* const data_array,
                                    const Interval* const interval,
                                    DataArrayNerr1d*** data_array_arr_ptr);
    void GenSelectDa1dArrByInterval(const DataArraySerr1d* const data_array,
                                    const Interval* const interval,
                                    DataArraySerr1d*** data_array_arr_ptr);
    void GenSelectDa1dArrByInterval(const DataArrayTerr1d* const data_array,
                                    const Interval* const interval,
                                    DataArrayTerr1d*** data_array_arr_ptr);    

} // namespace DataArray1dOpe

#endif // MORIIISM_MILIB_DATA1D_OPE_H_
