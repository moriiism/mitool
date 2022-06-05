#ifndef MORIIISM_MITOOL_MIFITSLIB_FITS_H_
#define MORIIISM_MITOOL_MIFITSLIB_FITS_H_

#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
//#include "mi_rand.h"
#include "mi_sort.h"
#include "mif_img_info.h"

namespace MifFits
{

    int GetNaxis(string infile);
    int GetAxisSize(string infile, int idim);
    
    int InFitsImageF(string infile,
                     const MifImgInfo* const img_info,
                     int* const bitpix_ptr,
                     float** const data_arr_ptr);
    int InFitsImageD(string infile,
                     const MifImgInfo* const img_info,
                     int* const bitpix_ptr,
                     double** const data_arr_ptr);
    
    int InFitsCubeF(string infile,
                    const MifImgInfo* const img_info,
                    int* const bitpix_ptr,
                    float** const data_arr_ptr);
    int InFitsCubeD(string infile,
                    const MifImgInfo* const img_info,
                    int* const bitpix_ptr,
                    double** const data_arr_ptr);

    int InFits4dF(string infile,
                  const MifImgInfo* const img_info,
                  int* const bitpix_ptr,
                  float** const data_arr_ptr);
    int InFits4dD(string infile,
                  const MifImgInfo* const img_info,
                  int* const bitpix_ptr,
                  double** const data_arr_ptr);
    
    
    int OutFitsImageF(string outdir, string outfile_head, string tag,
                      int naxis,
                      int bitpix,
                      const long* const naxes,
                      const float* const data_arr);
    int OutFitsImageF(string outfile,
                      int naxis,
                      int bitpix,
                      const long* const naxes,
                      const float* const data_arr);
    
    int OutFitsImageD(string outdir, string outfile_head, string tag,
                      int naxis,
                      int bitpix,
                      const long* const naxes,
                      const double* const data_arr);
    int OutFitsImageD(string outfile,
                      int naxis,
                      int bitpix,
                      const long* const naxes,
                      const double* const data_arr);    
    
    int OutFitsCubeF(string outdir, string outfile_head, string tag,
                     int naxis,
                     int bitpix,
                     const long* const naxes,
                     const float* const data_arr);
    int OutFitsCubeF(string outfile,
                     int naxis,
                     int bitpix,
                     const long* const naxes,
                     const float* const data_arr);
    
    int OutFitsCubeD(string outdir, string outfile_head, string tag,
                     int naxis,
                     int bitpix,
                     const long* const naxes,
                     const double* const data_arr);
    int OutFitsCubeD(string outfile,
                     int naxis,
                     int bitpix,
                     const long* const naxes,
                     const double* const data_arr);        
    
}  // namespace MifFits

#endif // MORIIISM_MITOOL_MIFITSLIB_FITS_H_
