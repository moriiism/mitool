#ifndef MORIIISM_MILIB_FITS_H_
#define MORIIISM_MILIB_FITS_H_

#include "fitsio.h"
#include "mi_str.h"
#include "mi_iolib.h"
#include "mi_rand.h"
#include "mi_linalg.h"
#include "mi_sort.h"
#include "mi_img_info.h"

namespace MiFits
{
    int InFitsImageF(string infile,
                     const MiImgInfo* const img_info,
                     double** const data_arr_ptr);
    int InFitsCubeF(string infile,
                    const MiImgInfo* const img_info,
                    double** const data_arr_ptr);

    int OutFitsImageF(string outdir, string outfile_head, string tag,
                      int naxis, const long* const naxes,
                      const float* const data_arr);
    int OutFitsCubeF(string outdir, string outfile_head, string tag,
                     int naxis, const long* const naxes,
                     const float* const data_arr);

}  // namespace MiFits

#endif // MORIIISM_MILIB_FITS_H_
