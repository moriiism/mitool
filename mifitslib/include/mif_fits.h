#ifndef MORIIISM_MIFITSLIB_FITS_H_
#define MORIIISM_MIFITSLIB_FITS_H_

#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mi_rand.h"
#include "mi_sort.h"
//#include "mib_linalg.h"
#include "mif_img_info.h"

namespace MifFits
{
    int InFitsImageF(string infile,
                     const MifImgInfo* const img_info,
                     double** const data_arr_ptr);
    int InFitsCubeF(string infile,
                    const MifImgInfo* const img_info,
                    double** const data_arr_ptr);

    int OutFitsImageF(string outdir, string outfile_head, string tag,
                      int naxis, const long* const naxes,
                      const float* const data_arr);
    int OutFitsCubeF(string outdir, string outfile_head, string tag,
                     int naxis, const long* const naxes,
                     const float* const data_arr);

}  // namespace MifFits

#endif // MORIIISM_MIFITSLIB_FITS_H_
